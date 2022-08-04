// -*- coding: utf-8 -*-
// Copyright (C) 2017-2018, 2020-2021 Laboratoire de Recherche et
// Développement de l'Epita (LRDE).
//
// This file is part of Spot, a model checking library.
//
// Spot is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// Spot is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
// License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "config.h"

#include <utility>

#include <spot/misc/timer.hh>
#include <spot/twaalgos/game.hh>
#include <spot/misc/bddlt.hh>
#include <spot/twaalgos/sccinfo.hh>

namespace spot
{
  namespace
  {
    static const std::vector<bool>*
    ensure_game(const const_twa_graph_ptr& arena, const char* fnname)
    {
      auto owner = arena->get_named_prop<std::vector<bool>>("state-player");
      if (!owner)
        throw std::runtime_error
          (std::string(fnname) + ": automaton should define \"state-player\"");
      if (owner->size() != arena->num_states())
        throw std::runtime_error
          (std::string(fnname) + ": \"state-player\" should have "
           "as many states as the automaton");
      return owner;
    }

    static const std::vector<bool>*
    ensure_parity_game(const const_twa_graph_ptr& arena, const char* fnname)
    {
      bool max, odd;
      arena->acc().is_parity(max, odd, true);
      if (!(max && odd))
        throw std::runtime_error
          (std::string(fnname) +
           ": arena must have max-odd acceptance condition");
      for (const auto& e : arena->edges())
        if (!e.acc)
          throw std::runtime_error
            (std::string(fnname) + ": arena must be colorized");
      return ensure_game(arena, fnname);
    }

    // Internal structs
    // winning regions for env and player
    struct winner_t
    {
      std::vector<bool> has_winner_;
      std::vector<bool> winner_;

      inline bool operator()(unsigned v, bool p)
      {
        // returns true if player p wins v
        // false otherwise
        if (!has_winner_[v])
          return false;

        return winner_[v] == p;
      }

      inline void set(unsigned v, bool p)
      {
        has_winner_[v] = true;
        winner_[v] = p;
      }

      inline void unset(unsigned v)
      {
        has_winner_[v] = false;
      }

      inline bool winner(unsigned v)
      {
        assert(has_winner_.at(v));
        return winner_[v];
      }
    }; // winner_t

    // When using scc decomposition we need to track the
    // changes made to the graph
    struct edge_stash_t
    {
      edge_stash_t(unsigned num, unsigned dst, acc_cond::mark_t acc) noexcept
        : e_num(num),
          e_dst(dst),
          e_acc(acc)
      {
      }
      const unsigned e_num, e_dst;
      const acc_cond::mark_t e_acc;
    }; // edge_stash_t

    // Internal structs used by parity_game
    // Struct to change recursive calls to stack
    struct work_t
    {
      work_t(unsigned wstep_, unsigned rd_, unsigned min_par_,
             unsigned max_par_) noexcept
        : wstep(wstep_),
          rd(rd_),
          min_par(min_par_),
          max_par(max_par_)
      {
      }
      const unsigned wstep, rd, min_par, max_par;
    }; // work_t

    // Collects information about an scc
    // Used to detect special cases
    struct subgame_info_t
    {
      typedef std::set<unsigned, std::greater<unsigned>> all_parities_t;

      subgame_info_t() noexcept
      {
      }

      subgame_info_t(bool empty, bool one_parity, bool one_player0,
                     bool one_player1, all_parities_t parities) noexcept
        : is_empty(empty),
          is_one_parity(one_parity),
          is_one_player0(one_player0),
          is_one_player1(one_player1),
          all_parities(parities)
      {};
      bool is_empty; // empty subgame
      bool is_one_parity; // only one parity appears in the subgame
      // todo : Not used yet
      bool is_one_player0; // one player subgame for player0 <-> p==false
      bool is_one_player1; // one player subgame for player1 <-> p==true
      all_parities_t all_parities;
    }; // subgame_info_t


    // A class to solve parity games
    // The current implementation is inspired by
    // by oink however without multicore and adapted to transition based
    // acceptance
    class parity_game
    {
    public:

      bool solve(const twa_graph_ptr &arena)
      {
        // todo check if reordering states according to scc is worth it
        set_up(arena);
        // Start recursive zielonka in a bottom-up fashion on each scc
        subgame_info_t subgame_info;
        for (c_scc_idx_ = 0; c_scc_idx_ < info_->scc_count(); ++c_scc_idx_)
          {
            // Useless SCCs are winning for player 0.
            if (!info_->is_useful_scc(c_scc_idx_))
              {
                for (unsigned v: c_states())
                  {
                    w_.set(v, false);
                    // The strategy for player 0 is to take the first
                    // available edge.
                    if ((*owner_ptr_)[v] == false)
                      for (const auto &e : arena_->out(v))
                        {
                          s_[v] = arena_->edge_number(e);
                          break;
                        }
                  }
                continue;
              }
            // Convert transitions leaving edges to self-loops
            // and check if trivially solvable
            subgame_info = fix_scc();
            // If empty, the scc was trivially solved
            if (!subgame_info.is_empty)
              {
                // Check for special cases
                if (subgame_info.is_one_parity)
                  one_par_subgame_solver(subgame_info, max_abs_par_);
                else
                  {
                    // "Regular" solver
                    max_abs_par_ = *subgame_info.all_parities.begin();
                    w_stack_.emplace_back(0, 0, 0, max_abs_par_);
                    zielonka();
                  }
              }
          }
        // All done -> restore graph, i.e. undo self-looping
        restore();

        assert(std::all_of(w_.has_winner_.cbegin(), w_.has_winner_.cend(),
                           [](bool b)
                           { return b; }));
        assert(std::all_of(s_.cbegin(), s_.cend(),
                           [](unsigned e_idx)
                           { return e_idx > 0; }));

        // Put the solution as named property
        region_t &w = *arena->get_or_set_named_prop<region_t>("state-winner");
        strategy_t &s = *arena->get_or_set_named_prop<strategy_t>("strategy");
        w.swap(w_.winner_);
        s.resize(s_.size());
        std::copy(s_.begin(), s_.end(), s.begin());

        clean_up();
        return w[arena->get_init_state_number()];
      }

    private:

      // Returns the vector of states currently considered
      // i.e. the states of the current scc
      // c_scc_idx_ is set in the 'main' loop
      inline const std::vector<unsigned> &c_states()
      {
        assert(info_);
        return info_->states_of(c_scc_idx_);
      }

      void set_up(const twa_graph_ptr &arena)
      {
        owner_ptr_ = ensure_parity_game(arena, "solve_parity_game()");
        arena_ = arena;
        unsigned n_states = arena_->num_states();
        // Resize data structures
        subgame_.clear();
        subgame_.resize(n_states, unseen_mark);
        w_.has_winner_.clear();
        w_.has_winner_.resize(n_states, 0);
        w_.winner_.clear();
        w_.winner_.resize(n_states, 0);
        s_.clear();
        s_.resize(n_states, -1);
        // Init
        rd_ = 0;
        max_abs_par_ = arena_->get_acceptance().used_sets().max_set() - 1;
        info_ = std::make_unique<scc_info>(arena_);
        // Every edge leaving an scc needs to be "fixed"
        // at some point.
        // We store: number of edge fixed, original dst, original acc
        change_stash_.clear();
        change_stash_.reserve(info_->scc_count() * 2);
      }

      // Checks if an scc is empty and reports the occurring parities
      // or special cases
      inline subgame_info_t
      inspect_scc(unsigned max_par)
      {
        subgame_info_t info;
        info.is_empty = true;
        info.is_one_player0 = true;
        info.is_one_player1 = true;
        for (unsigned v : c_states())
          {
            if (subgame_[v] != unseen_mark)
              continue;

            bool multi_edge = false;
            for (const auto &e : arena_->out(v))
              if (subgame_[e.dst] == unseen_mark)
                {
                  info.is_empty = false;
                  unsigned this_par = e.acc.max_set() - 1;
                  if (this_par <= max_par)
                    {
                      info.all_parities.insert(this_par);
                      multi_edge = true;
                    }
                }
            if (multi_edge)
              {
                // This state has multiple edges, so it is not
                // a one player subgame for !owner
                if ((*owner_ptr_)[v])
                  info.is_one_player1 = false;
                else
                  info.is_one_player0 = false;
              }
          } // v
        assert(info.all_parities.size() || info.is_empty);
        info.is_one_parity = info.all_parities.size() == 1;
        // Done
        return info;
      }

      // Checks if an scc can be trivially solved,
      // that is, all vertices of the scc belong to the
      // attractor of a transition leaving the scc
      inline subgame_info_t
      fix_scc()
      {
        auto scc_acc = info_->acc_sets_of(c_scc_idx_);
        // We will override all parities of edges leaving the scc
        bool added[] = {false, false};
        unsigned par_pair[2];
        unsigned scc_new_par = std::max(scc_acc.max_set(), 1u);
        if (scc_new_par&1)
          {
            par_pair[1] = scc_new_par;
            par_pair[0] = scc_new_par+1;
          }
        else
          {
            par_pair[1] = scc_new_par+1;
            par_pair[0] = scc_new_par;
          }
        acc_cond::mark_t even_mark({par_pair[0]});
        acc_cond::mark_t odd_mark({par_pair[1]});

        // Only necessary to pass tests
        max_abs_par_ = std::max(par_pair[0], par_pair[1]);

        for (unsigned v : c_states())
          {
            assert(subgame_[v] == unseen_mark);
            for (auto &e : arena_->out(v))
              {
                // The outgoing edges are taken finitely often
                // -> disregard parity
                if (info_->scc_of(e.dst) != c_scc_idx_)
                  {
                    // Edge leaving the scc
                    change_stash_.emplace_back(arena_->edge_number(e),
                                               e.dst, e.acc);
                    if (w_.winner(e.dst))
                      {
                        // Winning region of player -> odd
                        e.acc = odd_mark;
                        added[1] = true;
                      }
                    else
                      {
                        // Winning region of env -> even
                        e.acc = even_mark;
                        added[0] = true;
                      }
                    // Replace with self-loop
                    e.dst = e.src;
                  }
              } // e
          } // v

        // Compute the attractors of the self-loops/transitions leaving scc
        // These can be directly added to the winning states
        // Note: attractors can not intersect therefore the order in which
        // they are computed does not matter
        unsigned dummy_rd;

        for (bool p : {false, true})
          if (added[p])
            attr(dummy_rd, p, par_pair[p], true, par_pair[p]);

        if (added[0] || added[1])
          // Fix "negative" strategy
          for (unsigned v : c_states())
            if (subgame_[v] != unseen_mark)
              s_[v] = std::abs(s_[v]);

        return inspect_scc(unseen_mark);
      } // fix_scc

      inline bool
      attr(unsigned &rd, bool p, unsigned max_par,
           bool acc_par, unsigned min_win_par)
      {
        // Computes the attractor of the winning set of player p within a
        // subgame given as rd.
        // If acc_par is true, max_par transitions are also accepting and
        // the subgame count will be increased
        // The attracted vertices are directly added to the set

        // Increase rd meaning we create a new subgame
        if (acc_par)
          rd = ++rd_;
        // todo replace with a variant of topo sort ?
        // As proposed in Oink! / PGSolver
        // Needs the transposed graph however

        assert((!acc_par) || (acc_par && (max_par&1) == p));
        assert(!acc_par || (0 < min_win_par));
        assert((min_win_par <= max_par) && (max_par <= max_abs_par_));

        bool grown = false;
        // We could also directly mark states as owned,
        // instead of adding them to to_add first,
        // possibly reducing the number of iterations.
        // However by making the algorithm complete a loop
        // before adding it is like a backward bfs and (generally) reduces
        // the size of the strategy
        static std::vector<unsigned> to_add;

        assert(to_add.empty());

        do
          {
            if (!to_add.empty())
              {
                grown = true;
                for (unsigned v : to_add)
                  {
                    // v is winning
                    w_.set(v, p);
                    // Mark if demanded
                    if (acc_par)
                      {
                        assert(subgame_[v] == unseen_mark);
                        subgame_[v] = rd;
                      }
                  }
              }
            to_add.clear();

            for (unsigned v : c_states())
              {
                if ((subgame_[v] < rd) || (w_(v, p)))
                  // Not in subgame or winning
                  continue;

                bool is_owned = (*owner_ptr_)[v] == p;
                bool wins = !is_owned;
                // Loop over out-going

                // Optim: If given the choice,
                // we seek to go to the "oldest" subgame
                // That is the subgame with the lowest rd value
                unsigned min_subgame_idx = -1u;
                for (const auto &e: arena_->out(v))
                  {
                    unsigned this_par = e.acc.max_set() - 1;
                    if ((subgame_[e.dst] >= rd) && (this_par <= max_par))
                      {
                        // Check if winning
                        if (w_(e.dst, p)
                            || (acc_par && (min_win_par <= this_par)))
                          {
                            assert(!acc_par || (this_par < min_win_par) ||
                                   (acc_par && (min_win_par <= this_par) &&
                                    ((this_par&1) == p)));
                            if (is_owned)
                              {
                                wins = true;
                                if (acc_par)
                                  {
                                    s_[v] = arena_->edge_number(e);
                                    if (min_win_par <= this_par)
                                      // max par edge
                                      // change sign -> mark as needs
                                      // to be possibly fixed
                                      s_[v] = -s_[v];
                                    break;
                                  }
                                else
                                  {
                                    //snapping
                                    if (subgame_[e.dst] < min_subgame_idx)
                                      {
                                        s_[v] = arena_->edge_number(e);
                                        min_subgame_idx = subgame_[e.dst];
                                        if (!p)
                                          // No optim for env
                                          break;
                                      }
                                  }
                              }// owned
                          }
                        else
                          {
                            if (!is_owned)
                              {
                                wins = false;
                                break;
                              }
                          } // winning
                      } // subgame
                  }// for edges
                if (wins)
                  to_add.push_back(v);
              } // for v
          } while (!to_add.empty());
        // done

        assert(to_add.empty());
        return grown;
      }

      // We need to check if transitions that are accepted due
      // to their parity remain in the winning region of p
      inline bool
      fix_strat_acc(unsigned rd, bool p, unsigned min_win_par, unsigned max_par)
      {
        for (unsigned v : c_states())
          {
            // Only current attractor and owned
            // and winning vertices are concerned
            if ((subgame_[v] != rd) || !w_(v, p)
                || ((*owner_ptr_)[v] != p) || (s_[v] > 0))
              continue;

            // owned winning vertex of attractor
            // Get the strategy edge
            s_[v] = -s_[v];
            const auto &e_s = arena_->edge_storage(s_[v]);
            // Optimization only for player
            if (!p && w_(e_s.dst, p))
              // If current strat is admissible -> nothing to do
              // for env
              continue;

            // This is an accepting edge that is no longer admissible
            // or we seek a more desirable edge (for player)
            assert(min_win_par <= e_s.acc.max_set() - 1);
            assert(e_s.acc.max_set() - 1 <= max_par);

            // Strategy heuristic : go to the oldest subgame
            unsigned min_subgame_idx = -1u;

            s_[v] = -1;
            for (const auto &e_fix : arena_->out(v))
              {
                if (subgame_[e_fix.dst] >= rd)
                  {
                    unsigned this_par = e_fix.acc.max_set() - 1;
                    // This edge must have less than max_par,
                    // otherwise it would have already been attracted
                    assert((this_par <= max_par)
                           || ((this_par&1) != (max_par&1)));
                    // if it is accepting and leads to the winning region
                    // -> valid fix
                    if ((min_win_par <= this_par)
                        && (this_par <= max_par)
                        && w_(e_fix.dst, p)
                        && (subgame_[e_fix.dst] < min_subgame_idx))
                      {
                        // Max par edge to older subgame found
                        s_[v] = arena_->edge_number(e_fix);
                        min_subgame_idx = subgame_[e_fix.dst];
                      }
                  }
              }
            if (s_[v] == -1)
              // NO fix found
              // This state is NOT won by p due to any accepting edges
              return true; // true -> grown
          }
        // Nothing to fix or all fixed
        return false; // false -> not grown == all good
      }

      inline void zielonka()
      {
        while (!w_stack_.empty())
          {
            auto this_work = w_stack_.back();
            w_stack_.pop_back();

            switch (this_work.wstep)
              {
              case (0):
                {
                  assert(this_work.rd == 0);
                  assert(this_work.min_par == 0);

                  unsigned rd;
                  assert(this_work.max_par <= max_abs_par_);

                  // Check if empty and get parities
                  subgame_info_t subgame_info =
                    inspect_scc(this_work.max_par);

                  if (subgame_info.is_empty)
                    // Nothing to do
                    break;
                  if (subgame_info.is_one_parity)
                    {
                      // Can be trivially solved
                      one_par_subgame_solver(subgame_info, this_work.max_par);
                      break;
                    }

                  // Compute the winning parity boundaries
                  // -> Priority compression
                  // Optional, improves performance
                  // Highest actually occurring
                  unsigned max_par = *subgame_info.all_parities.begin();
                  unsigned min_win_par = max_par;
                  while ((min_win_par > 2) &&
                         (!subgame_info.all_parities.count(min_win_par-1)))
                    min_win_par -= 2;
                  assert(max_par > 0);
                  assert(!subgame_info.all_parities.empty());
                  assert(min_win_par > 0);

                  // Get the player
                  bool p = min_win_par&1;
                  assert((max_par&1) == (min_win_par&1));
                  // Attraction to highest par
                  // This increases rd_ and passes it to rd
                  attr(rd, p, max_par, true, min_win_par);
                  // All those attracted get subgame_[v] <- rd

                  // Continuation
                  w_stack_.emplace_back(1, rd, min_win_par, max_par);
                  // Recursion
                  w_stack_.emplace_back(0, 0, 0, min_win_par-1);
                  // Others attracted will have higher counts in subgame
                  break;
                }
              case (1):
                {
                  unsigned rd = this_work.rd;
                  unsigned min_win_par = this_work.min_par;
                  unsigned max_par = this_work.max_par;
                  assert((min_win_par&1) == (max_par&1));
                  bool p = min_win_par&1;
                  // Check if the attractor of w_[!p] is equal to w_[!p]
                  // if so, player wins if there remain accepting transitions
                  // for max_par (see fix_strat_acc)
                  // This does not increase but reuse rd
                  bool grown = attr(rd, !p, max_par, false, min_win_par);
                  // todo investigate: A is an attractor, so the only way that
                  // attr(w[!p]) != w[!p] is if the max par "exit" edges lead
                  // to a trap for player/ exit the winning region of the
                  // player so we can do a fast check instead of the
                  // generic attr computation which only needs to be done
                  // if the fast check is positive

                  // Check if strategy needs to be fixed / is fixable
                  if (!grown)
                    // this only concerns parity accepting edges
                    grown = fix_strat_acc(rd, p, min_win_par, max_par);
                  // If !grown we are done, and the partitions are valid

                  if (grown)
                    {
                      // Reset current game without !p attractor
                      for (unsigned v : c_states())
                        if (!w_(v, !p) && (subgame_[v] >= rd))
                          {
                            // delete ownership
                            w_.unset(v);
                            // Mark as unseen
                            subgame_[v] = unseen_mark;
                            // Unset strat for testing
                            s_[v] = -1;
                          }
                      w_stack_.emplace_back(0, 0, 0, max_par);
                      // No need to do anything else
                      // the attractor of !p of this level is not changed
                    }
                  break;
                }
              default:
                throw std::runtime_error("No valid workstep");
              } // switch
          } // while
      } // zielonka

      // Undo change to the graph made along the way
      inline void restore()
      {
        // "Unfix" the edges leaving the sccs
        // This is called once the game has been solved
        for (auto &e_stash : change_stash_)
          {
            auto &e = arena_->edge_storage(e_stash.e_num);
            e.dst = e_stash.e_dst;
            e.acc = e_stash.e_acc;
          }
        // Done
      }

      // Empty all internal variables
      inline void clean_up()
      {
        info_ = nullptr;
        subgame_.clear();
        w_.has_winner_.clear();
        w_.winner_.clear();
        s_.clear();
        rd_ = 0;
        max_abs_par_ = 0;
        change_stash_.clear();
      }

      // Dedicated solver for special cases
      inline void one_par_subgame_solver(const subgame_info_t &info,
                                         unsigned max_par)
      {
        assert(info.all_parities.size() == 1);
        // The entire subgame is won by the player of the only parity
        // Any edge will do
        // todo optim for smaller circuit
        // This subgame gets its own counter
        ++rd_;
        unsigned rd = rd_;
        unsigned one_par = *info.all_parities.begin();
        bool winner = one_par & 1;
        assert(one_par <= max_par);

        for (unsigned v : c_states())
          {
            if (subgame_[v] != unseen_mark)
              continue;
            // State of the subgame
            subgame_[v] = rd;
            w_.set(v, winner);
            // Get the strategy
            assert(s_[v] == -1);
            for (const auto &e : arena_->out(v))
              {
                unsigned this_par = e.acc.max_set() - 1;
                if ((subgame_[e.dst] >= rd) && (this_par <= max_par))
                  {
                    assert(this_par == one_par);
                    // Ok for strat
                    s_[v] = arena_->edge_number(e);
                    break;
                  }
              }
            assert((0 < s_[v]) && (s_[v] < unseen_mark));
          }
        // Done
      }

      const unsigned unseen_mark = std::numeric_limits<unsigned>::max();

      twa_graph_ptr arena_;
      const std::vector<bool> *owner_ptr_;
      unsigned rd_;
      winner_t w_;
      // Subgame array similar to the one from oink!
      std::vector<unsigned> subgame_;
      // strategies for env and player; For synthesis only player is needed
      // We need a signed value here in order to "fix" the strategy
      // during construction
      std::vector<long long> s_;

      // Informations about sccs andthe current scc
      std::unique_ptr<scc_info> info_;
      unsigned max_abs_par_; // Max parity occurring in the current scc
      // Info on the current scc
      unsigned c_scc_idx_;
      // Fixes made to the sccs that have to be undone
      // before returning
      std::vector<edge_stash_t> change_stash_;
      // Change recursive calls to stack
      std::vector<work_t> w_stack_;
    };

  } // anonymous


  bool solve_parity_game(const twa_graph_ptr& arena)
  {
    parity_game pg;
    return pg.solve(arena);
  }

  bool solve_game(const twa_graph_ptr& arena)
  {
    bool dummy1, dummy2;
    auto& acc = arena->acc();
    if (acc.is_t())
      return solve_safety_game(arena);
    if (!arena->acc().is_parity(dummy1, dummy2, true))
      throw std::runtime_error
        ("solve_game(): unsupported acceptance condition.");
    return solve_parity_game(arena);
  }

  void pg_print(std::ostream& os, const const_twa_graph_ptr& arena)
  {
    auto owner = ensure_parity_game(arena, "pg_print");

    unsigned ns = arena->num_states();
    unsigned init = arena->get_init_state_number();
    os << "parity " << ns - 1 << ";\n";
    std::vector<bool> seen(ns, false);
    std::vector<unsigned> todo({init});
    while (!todo.empty())
      {
        unsigned src = todo.back();
        todo.pop_back();
        if (seen[src])
          continue;
        seen[src] = true;
        os << src << ' ';
        os << arena->out(src).begin()->acc.max_set() - 1 << ' ';
        os << (*owner)[src] << ' ';
        bool first = true;
        for (auto& e: arena->out(src))
          {
            if (!first)
              os << ',';
            first = false;
            os << e.dst;
            if (!seen[e.dst])
              todo.push_back(e.dst);
          }
        if (src == init)
          os << " \"INIT\"";
        os << ";\n";
      }
  }

  void alternate_players(spot::twa_graph_ptr& arena,
                         bool first_player, bool complete0)
  {
    auto um = arena->acc().unsat_mark();
    if (!um.first && complete0)
      throw std::runtime_error
        ("alternate_players(): Cannot complete monitor.");

    unsigned sink_env = 0;
    unsigned sink_con = 0;

    std::vector<bool> seen(arena->num_states(), false);
    unsigned init = arena->get_init_state_number();
    std::vector<unsigned> todo({init});
    auto owner = new std::vector<bool>(arena->num_states(), false);
    (*owner)[init] = first_player;
    while (!todo.empty())
      {
        unsigned src = todo.back();
        todo.pop_back();
        seen[src] = true;
        bdd missing = bddtrue;
        for (const auto& e: arena->out(src))
          {
            bool osrc = (*owner)[src];
            if (complete0 && !osrc)
              missing -= e.cond;

            if (!seen[e.dst])
              {
                (*owner)[e.dst] = !osrc;
                todo.push_back(e.dst);
              }
            else if ((*owner)[e.dst] == osrc)
              {
                delete owner;
                throw std::runtime_error
                  ("alternate_players(): Odd cycle detected.");
              }
          }
        if (complete0 && !(*owner)[src] && missing != bddfalse)
          {
            if (sink_env == 0)
              {
                sink_env = arena->new_state();
                sink_con = arena->new_state();
                owner->push_back(true);
                owner->push_back(false);
                arena->new_edge(sink_con, sink_env, bddtrue, um.second);
                arena->new_edge(sink_env, sink_con, bddtrue, um.second);
              }
            arena->new_edge(src, sink_con, missing, um.second);
          }
      }

    arena->set_named_prop("state-player", owner);
  }

  twa_graph_ptr
  highlight_strategy(twa_graph_ptr& aut,
                     int player0_color,
                     int player1_color)
  {
    auto owner = ensure_game(aut, "highlight_strategy()");
    region_t* w = aut->get_named_prop<region_t>("state-winner");
    strategy_t* s = aut->get_named_prop<strategy_t>("strategy");
    if (!w)
      throw std::runtime_error
        ("highlight_strategy(): "
         "winning region unavailable, solve the game first");
    if (!s)
      throw std::runtime_error
        ("highlight_strategy(): strategy unavailable, solve the game first");

    unsigned ns = aut->num_states();
    auto* hl_edges = aut->get_or_set_named_prop<std::map<unsigned, unsigned>>
      ("highlight-edges");
    auto* hl_states = aut->get_or_set_named_prop<std::map<unsigned, unsigned>>
      ("highlight-states");

    if (unsigned sz = std::min(w->size(), s->size()); sz < ns)
      ns = sz;

    for (unsigned n = 0; n < ns; ++n)
      {
        int color = (*w)[n] ? player1_color : player0_color;
        if (color == -1)
          continue;
        (*hl_states)[n] = color;
        if ((*w)[n] == (*owner)[n])
          (*hl_edges)[(*s)[n]] = color;
      }

    return aut;
  }

  void set_state_players(twa_graph_ptr arena, const region_t& owners)
  {
    set_state_players(arena, region_t(owners));
  }

  void set_state_players(twa_graph_ptr arena, region_t&& owners)
  {
    if (owners.size() != arena->num_states())
      throw std::runtime_error
        ("set_state_players(): There must be as many owners as states");

    arena->set_named_prop<region_t>("state-player",
        new region_t(std::forward<region_t>(owners)));
  }

  void set_state_player(twa_graph_ptr arena, unsigned state, bool owner)
  {
    if (state >= arena->num_states())
      throw std::runtime_error("set_state_player(): invalid state number");

    region_t *owners = arena->get_named_prop<region_t>("state-player");
    if (!owners)
      throw std::runtime_error("set_state_player(): Can only set the state of "
                               "an individual "
                               "state if \"state-player\" already exists.");
    if (owners->size() != arena->num_states())
      throw std::runtime_error("set_state_player(): The \"state-player\" "
                               "vector has a different "
                               "size comparerd to the automaton! "
                               "Called new_state in between?");

    (*owners)[state] = owner;
  }

  const region_t& get_state_players(const_twa_graph_ptr arena)
  {
    region_t *owners = arena->get_named_prop<region_t>
      ("state-player");
    if (!owners)
      throw std::runtime_error
        ("get_state_players(): state-player property not defined, not a game?");

    return *owners;
  }

  bool get_state_player(const_twa_graph_ptr arena, unsigned state)
  {
    if (state >= arena->num_states())
      throw std::runtime_error("get_state_player(): invalid state number");

    region_t* owners = arena->get_named_prop<region_t>("state-player");
    if (!owners)
      throw std::runtime_error
        ("get_state_player(): state-player property not defined, not a game?");

    return (*owners)[state];
  }


  const strategy_t& get_strategy(const_twa_graph_ptr arena)
  {
    auto strat_ptr = arena->get_named_prop<strategy_t>("strategy");
    if (!strat_ptr)
      throw std::runtime_error("get_strategy(): Named prop "
                               "\"strategy\" not set."
                               "Arena not solved?");
    return *strat_ptr;
  }

  void set_strategy(twa_graph_ptr arena, const strategy_t& strat)
  {
    set_strategy(arena, strategy_t(strat));
  }
  void set_strategy(twa_graph_ptr arena, strategy_t&& strat)
  {
    if (arena->num_states() != strat.size())
      throw std::runtime_error("set_strategy(): strategies need to have "
                               "the same size as the automaton.");
    arena->set_named_prop<strategy_t>("strategy",
        new strategy_t(std::forward<strategy_t>(strat)));
  }

  void set_synthesis_outputs(const twa_graph_ptr& arena, const bdd& outs)
  {
    arena->set_named_prop<bdd>("synthesis-outputs", new bdd(outs));
  }

  bdd get_synthesis_outputs(const const_twa_graph_ptr& arena)
  {
    if (auto outptr = arena->get_named_prop<bdd>("synthesis-outputs"))
      return *outptr;
    else
      throw std::runtime_error
          ("get_synthesis_outputs(): synthesis-outputs not defined");
  }

  std::vector<std::string>
  get_synthesis_output_aps(const const_twa_graph_ptr& arena)
  {
    std::vector<std::string> out_names;

    bdd outs = get_synthesis_outputs(arena);

    auto dict = arena->get_dict();

    auto to_bdd = [&](const auto& x)
      {
        return bdd_ithvar(dict->has_registered_proposition(x, arena.get()));
      };

    for (const auto& ap : arena->ap())
      if (bdd_implies(outs, to_bdd(ap)))
        out_names.push_back(ap.ap_name());

    return out_names;
  }


  void set_state_winners(twa_graph_ptr arena, const region_t& winners)
  {
    set_state_winners(arena, region_t(winners));
  }

  void set_state_winners(twa_graph_ptr arena, region_t&& winners)
  {
    if (winners.size() != arena->num_states())
      throw std::runtime_error
        ("set_state_winners(): There must be as many winners as states");

    arena->set_named_prop<region_t>("state-winner",
        new region_t(std::forward<region_t>(winners)));
  }

  void set_state_winner(twa_graph_ptr arena, unsigned state, bool winner)
  {
    if (state >= arena->num_states())
      throw std::runtime_error("set_state_winner(): invalid state number");

    region_t *winners = arena->get_named_prop<region_t>("state-winner");
    if (!winners)
      throw std::runtime_error("set_state_winner(): Can only set the state of "
                               "an individual "
                               "state if \"state-winner\" already exists.");
    if (winners->size() != arena->num_states())
      throw std::runtime_error("set_state_winner(): The \"state-winnerr\" "
                               "vector has a different "
                               "size compared to the automaton! "
                               "Called new_state in between?");

    (*winners)[state] = winner;
  }

  const region_t& get_state_winners(const_twa_graph_ptr arena)
  {
    region_t *winners = arena->get_named_prop<region_t>("state-winner");
    if (!winners)
      throw std::runtime_error
        ("get_state_winners(): state-winner property not defined, not a game?");

    return *winners;
  }

  bool get_state_winner(const_twa_graph_ptr arena, unsigned state)
  {
    if (state >= arena->num_states())
      throw std::runtime_error("get_state_winner(): invalid state number");

    region_t* winners = arena->get_named_prop<region_t>("state-winner");
    if (!winners)
      throw std::runtime_error
        ("get_state_winner(): state-winner property not defined, not a game?");

    return (*winners)[state];
  }


  bool solve_safety_game(const twa_graph_ptr& game)
  {
    if (!game->acc().is_t())
      throw std::runtime_error
        ("solve_safety_game(): arena should have true acceptance");

    auto owners = get_state_players(game);

    unsigned ns = game->num_states();
    auto winners = new region_t(ns, true);
    game->set_named_prop("state-winner", winners);
    auto strategy = new strategy_t(ns, 0);
    game->set_named_prop("strategy", strategy);

    // transposed is a reversed copy of game to compute predecessors
    // more easily.  It also keep track of the original edge iindex.
    struct edge_data {
      unsigned edgeidx;
    };
    digraph<void, edge_data> transposed;
    // Reverse the automaton, compute the out degree of
    // each state, and save dead-states in queue.
    transposed.new_states(ns);
    std::vector<unsigned> out_degree;
    out_degree.reserve(ns);
    std::vector<unsigned> queue;
    for (unsigned s = 0; s < ns; ++s)
      {
        unsigned deg = 0;
        for (auto& e: game->out(s))
          {
            transposed.new_edge(e.dst, e.src, game->edge_number(e));
            ++deg;
          }
        out_degree.push_back(deg);
        if (deg == 0)
          {
            (*winners)[s] = false;
            queue.push_back(s);
          }
      }
    // queue is initially filled with dead-states, which are winning
    // for player 0.  Any predecessor owned by player 0 is therefore
    // winning as well (check 1), and any predecessor owned by player
    // 1 that has all its successors winning for player 0 (check 2) is
    // also winning.  Use queue to propagate everything.
    // For the second check, we decrease out_degree by each edge leading
    // to a state winning for player 0, so if out_degree reaches 0,
    // we have ensured that all outgoing transitions are winning for 0.
    //
    // We use queue as a stack, to propagate bad states in DFS.
    // However it would be ok to replace the vector by a std::deque
    // to implement a BFS and build shorter strategies for player 0.
    // Right no we are assuming that strategies for player 0 have
    // limited uses, so we just avoid the overhead of std::deque in
    // favor of the simpler std::vector.
    while (!queue.empty())
      {
        unsigned s = queue.back();
        queue.pop_back();
        for (auto& e: transposed.out(s))
          {
            unsigned pred = e.dst;
            if (!(*winners)[pred])
              continue;
            // check 1 || check 2
            bool check1 = owners[pred] == false;
            if (check1 || --out_degree[pred] == 0)
              {
                (*winners)[pred] = false;
                queue.push_back(pred);
                if (check1)
                  (*strategy)[pred] = e.edgeidx;
              }
          }
      }
    // Let's fill in the strategy for Player 1.
    for (unsigned s = 0; s < ns; ++s)
      if (owners[s] && (*winners)[s])
        for (auto& e: game->out(s))
          if ((*winners)[e.dst])
            {
              (*strategy)[s] = game->edge_number(e);
              break;
            }

    return (*winners)[game->get_init_state_number()];
  }
}
