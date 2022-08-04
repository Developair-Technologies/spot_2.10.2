// -*- coding: utf-8 -*-
// Copyright (C) 2014-2021 Laboratoire de Recherche et Développement
// de l'Epita.
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
#include <spot/twa/twagraph.hh>
#include <spot/tl/print.hh>
#include <spot/misc/bddlt.hh>
#include <spot/twa/bddprint.hh>
#include <spot/misc/escape.hh>
#include <vector>
#include <deque>

using namespace std::string_literals;

namespace spot
{

  void
  twa_graph::apply_permutation(std::vector<unsigned> permut)
  {
    for (auto& e : edges())
    {
      e.acc.apply_permutation(permut);
    }
  }

  std::string twa_graph::format_state(unsigned n) const
  {
    if (is_univ_dest(n))
      {
        std::stringstream ss;
        bool notfirst = false;
        for (unsigned d: univ_dests(n))
          {
            if (notfirst)
              ss << '&';
            notfirst = true;
            ss << format_state(d);
          }
        return ss.str();
      }

    auto named = get_named_prop<std::vector<std::string>>("state-names");
    if (named && n < named->size())
      return (*named)[n];

    auto prod = get_named_prop
      <std::vector<std::pair<unsigned, unsigned>>>("product-states");
    if (prod && n < prod->size())
      {
        auto& p = (*prod)[n];
        std::stringstream ss;
        ss << p.first << ',' << p.second;
        return ss.str();
      }

    return std::to_string(n);
  }

  void
  twa_graph::release_formula_namer(namer<formula>* namer,
                                   bool keep_names)
  {
    if (keep_names)
      {
        auto v = new std::vector<std::string>(num_states());
        auto& n = namer->names();
        unsigned ns = n.size();
        assert(n.size() <= v->size());
        for (unsigned i = 0; i < ns; ++i)
          {
            auto f = n[i];
            if (f)
              (*v)[i] = str_psl(f);
          }
        set_named_prop("state-names", v);
      }
    delete namer;
  }

  /// \brief Merge universal destinations
  ///
  /// If several states have the same universal destination, merge
  /// them all.  Also remove unused destination, and any redundant
  /// state in each destination.
  void twa_graph::merge_univ_dests()
  {
    auto& g = get_graph();
    auto& dests = g.dests_vector();
    auto& edges = g.edge_vector();

    std::vector<unsigned> old_dests;
    std::swap(dests, old_dests);
    std::vector<unsigned> seen(old_dests.size(), -1U);
    internal::univ_dest_mapper<twa_graph::graph_t> uniq(g);

    auto fixup = [&](unsigned& in_dst)
      {
        unsigned dst = in_dst;
        if ((int) dst >= 0)       // not a universal edge
          return;
        dst = ~dst;
        unsigned& nd = seen[dst];
        if (nd == -1U)
          nd = uniq.new_univ_dests(old_dests.data() + dst + 1,
                                   old_dests.data() + dst + 1 + old_dests[dst]);
        in_dst = nd;
      };

    unsigned tend = edges.size();
    for (unsigned t = 1; t < tend; t++)
      {
        if (g.is_dead_edge(t))
          continue;
        fixup(edges[t].dst);
      }
    fixup(init_number_);
  }

  void twa_graph::merge_edges()
  {
    set_named_prop("highlight-edges", nullptr);
    g_.remove_dead_edges_();
    if (!is_existential())
      merge_univ_dests();

    auto& trans = this->edge_vector();
    unsigned orig_size = trans.size();
    unsigned tend = orig_size;

    // When two transitions have the same (src,colors,dst),
    // we can marge their conds.
    auto merge_conds_and_remove_false = [&]()
    {
      typedef graph_t::edge_storage_t tr_t;
      g_.sort_edges_([](const tr_t& lhs, const tr_t& rhs)
      {
        if (lhs.src < rhs.src)
          return true;
        if (lhs.src > rhs.src)
          return false;
        if (lhs.dst < rhs.dst)
          return true;
        if (lhs.dst > rhs.dst)
          return false;
        return lhs.acc < rhs.acc;
        // Do not sort on conditions, we'll merge
        // them.
      });

      unsigned out = 0;
      unsigned in = 1;

      // Skip any leading false edge.
      while (in < tend && trans[in].cond == bddfalse)
        ++in;
      if (in < tend)
        {
          ++out;
          if (out != in)
            trans[out] = trans[in];
          for (++in; in < tend; ++in)
            {
              if (trans[in].cond == bddfalse) // Unusable edge
                continue;
              // Merge edges with the same source, destination, and
              // colors.  (We test the source last, because this is the
              // most likely test to be true as edges are ordered by
              // sources and then destinations.)
              if (trans[out].dst == trans[in].dst
                  && trans[out].acc == trans[in].acc
                  && trans[out].src == trans[in].src)
                {
                  trans[out].cond |= trans[in].cond;
                }
              else
                {
                  ++out;
                  if (in != out)
                    trans[out] = trans[in];
                }
            }
        }
      if (++out != tend)
        {
          tend = out;
          trans.resize(tend);
        }
    };

    // When two transitions have the same (src,cond,dst), we can marge
    // their colors.  This only works for Fin-less acceptance.
    //
    // FIXME: We could should also merge edges when using
    // fin_acceptance, but the rule for Fin sets are different than
    // those for Inf sets, (and we need to be careful if a set is used
    // both as Inf and Fin)
    auto merge_colors = [&]()
    {
      if (tend < 2 || acc().uses_fin_acceptance())
        return;
      typedef graph_t::edge_storage_t tr_t;
      g_.sort_edges_([](const tr_t& lhs, const tr_t& rhs)
      {
        if (lhs.src < rhs.src)
          return true;
        if (lhs.src > rhs.src)
          return false;
        if (lhs.dst < rhs.dst)
          return true;
        if (lhs.dst > rhs.dst)
          return false;
        bdd_less_than_stable lt;
        return lt(lhs.cond, rhs.cond);
        // Do not sort on acceptance, we'll merge them.
      });

      // Start on the second position and try to merge it into the
      // first one
      unsigned out = 1;
      unsigned in = 2;

      for (; in < tend; ++in)
        {
          // Merge edges with the same source, destination,
          // and conditions.  (We test the source last, for the
          // same reason as above.)
          if (trans[out].dst == trans[in].dst
              && trans[out].cond.id() == trans[in].cond.id()
              && trans[out].src == trans[in].src)
            {
              trans[out].acc |= trans[in].acc;
            }
          else
            {
              ++out;
              if (in != out)
                trans[out] = trans[in];
            }
        }
      if (++out != tend)
        {
          tend = out;
          trans.resize(tend);
        }
    };

    // These next two lines used to be done in the opposite order in
    // 2.9.x and before.
    //
    // However merging colors first is more likely to
    // make parallel non-deterministic transition disappear.
    //
    // Consider:
    //           (1)--a-{1}--->(2)
    //           (1)--a-{2}--->(2)
    //           (1)--!a-{1}-->(2)
    // If colors are merged first, the first two transitions become one,
    // and the result is more deterministic:
    //           (1)--a-{1,2}->(2)
    //           (1)--!a-{1}-->(2)
    // If conditions were merged first, we would get the following
    // non-deterministic transitions instead:
    //           (1)--1-{1}--->(2)
    //           (1)--a-{2}--->(2)
    merge_colors();
    merge_conds_and_remove_false();

    // Merging some edges may turn a non-deterministic automaton
    // into a deterministic one.
    if (prop_universal().is_false() && tend != orig_size)
      prop_universal(trival::maybe());
    g_.chain_edges_();
  }

  unsigned twa_graph::merge_states()
  {
    if (!is_existential())
      throw std::runtime_error(
          "twa_graph::merge_states() does not work on alternating automata");

    typedef graph_t::edge_storage_t tr_t;
    g_.sort_edges_([](const tr_t& lhs, const tr_t& rhs)
    {
      if (lhs.src < rhs.src)
        return true;
      if (lhs.src > rhs.src)
        return false;
      if (lhs.acc < rhs.acc)
        return true;
      if (lhs.acc > rhs.acc)
        return false;
      if (bdd_less_than_stable lt; lt(lhs.cond, rhs.cond))
        return true;
      if (rhs.cond != lhs.cond)
        return false;
      // The destination must be sorted last
      // for our self-loop optimization to work.
      return lhs.dst < rhs.dst;
    });
    g_.chain_edges_();

    const unsigned nb_states = num_states();
    std::vector<unsigned> remap(nb_states, -1U);
    for (unsigned i = 0; i != nb_states; ++i)
      {
        auto out1 = out(i);
        for (unsigned j = 0; j != i; ++j)
          {
            auto out2 = out(j);
            if (std::equal(out1.begin(), out1.end(), out2.begin(), out2.end(),
                           [](const edge_storage_t& a,
                              const edge_storage_t& b)
                           { return ((a.dst == b.dst
                                      || (a.dst == a.src && b.dst == b.src))
                                     && a.data() == b.data()); }))
            {
              remap[i] = (remap[j] != -1U) ? remap[j] : j;

              // Because of the special self-loop tests we use above,
              // it's possible that i can be mapped to remap[j] even
              // if j was last compatible states found.  Consider the
              // following cases, taken from an actual test case:
              // 18 is equal to 5, 35 is equal to 18, but 35 is not
              // equal to 5.
              //
              // State: 5
              // [0&1&2] 8 {3}
              // [!0&1&2] 10 {1}
              // [!0&!1&!2] 18 {1}
              // [!0&!1&2] 19 {1}
              // [!0&1&!2] 20 {1}
              //
              // State: 18
              // [0&1&2] 8 {3}
              // [!0&1&2] 10 {1}
              // [!0&!1&!2] 18 {1} // self-loop
              // [!0&!1&2] 19 {1}
              // [!0&1&!2] 20 {1}
              //
              // State: 35
              // [0&1&2] 8 {3}
              // [!0&1&2] 10 {1}
              // [!0&!1&!2] 35 {1} // self-loop
              // [!0&!1&2] 19 {1}
              // [!0&1&!2] 20 {1}
              break;
            }
          }
      }

    for (auto& e: edges())
      if (remap[e.dst] != -1U)
        e.dst = remap[e.dst];

    if (remap[get_init_state_number()] != -1U)
      set_init_state(remap[get_init_state_number()]);

    unsigned st = 0;
    for (auto& s: remap)
      if (s == -1U)
        s = st++;
      else
        s = -1U;

    unsigned merged = num_states() - st;
    if (merged)
      defrag_states(remap, st);
    return merged;
  }

  unsigned twa_graph::merge_states_of(bool stable,
                                      const std::vector<bool>* to_merge_ptr)
  {
    if (!is_existential())
      throw std::runtime_error(
          "twa_graph::merge_states() does not work on alternating automata");

    typedef graph_t::edge_storage_t tr_t;
    if (stable)
      g_.sort_edges_of_<true>([](const tr_t& lhs, const tr_t& rhs)
      {
        if (lhs.acc < rhs.acc)
          return true;
        if (lhs.acc > rhs.acc)
          return false;
        if (bdd_less_than_stable lt; lt(lhs.cond, rhs.cond))
          return true;
        if (rhs.cond != lhs.cond)
          return false;
        // The destination must be sorted last
        // for our self-loop optimization to work.
        return lhs.dst < rhs.dst;
      });
    else
      g_.sort_edges_of_<false>([](const tr_t& lhs, const tr_t& rhs)
      {
        if (lhs.acc < rhs.acc)
          return true;
        if (lhs.acc > rhs.acc)
          return false;
        if (bdd_less_than lt; lt(lhs.cond, rhs.cond))
          return true;
        if (rhs.cond != lhs.cond)
          return false;
        // The destination must be sorted last
        // for our self-loop optimization to work.
        return lhs.dst < rhs.dst;
      });

    // Associates a hash value to a vector of classes
    std::unordered_map<size_t, std::vector<std::set<unsigned>>> equiv_class_;

    auto hash_state_ = [&](unsigned s)->size_t
      {
        // Hash the edges
        // bottle_neck?
        size_t h = fnv<size_t>::init;
        for (const edge_storage_t& e : out(s))
          {
            h ^= knuth32_hash(e.dst);
            h ^= knuth32_hash(e.cond.id());
            h ^= e.acc.hash();
            h = wang32_hash(h);
          }
        return h;
      };

    const unsigned nb_states = num_states();

    std::vector<unsigned> comp_classes_; // Classes to be merged
    for (unsigned i = 0; i != nb_states; ++i)
      {
        if (to_merge_ptr && !(*to_merge_ptr)[nb_states])
          continue;

        size_t hi = hash_state_(i);
        auto equal_to_i_ = [&, outi = out(i)](unsigned j)
          {
            auto outj = out(j);
            return std::equal(outi.begin(), outi.end(),
                              outj.begin(), outj.end(),
                              [](const edge_storage_t& a,
                                 const edge_storage_t& b)
                              { return ((a.dst == b.dst
                                         || (a.dst == a.src && b.dst == b.src))
                                         && a.data() == b.data()); });
          };
        comp_classes_.clear();
        // get all compatible classes
        // Candidate classes share a hash
        // A state is compatible to a class if it is compatble
        // to any of its states
        auto& cand_classes = equiv_class_[hi];
        unsigned n_c_classes = cand_classes.size();
        // Built it in "reverse order" the idx of
        // classes to be merged
        for (unsigned nc = n_c_classes - 1; nc < n_c_classes; --nc)
          if (std::any_of(cand_classes[nc].begin(),
                          cand_classes[nc].end(),
                          [&](unsigned j)
                          {return equal_to_i_(j); }))
            comp_classes_.push_back(nc);
        // Possible results:
        // 1) comp_classes_ is empty -> i gets its own class
        // 2) fuse together all comp_classes and add i
        if (comp_classes_.empty())
          cand_classes.emplace_back(std::set<unsigned>({i}));
        else
          {
            // Lowest idx
            auto& base_class = cand_classes[comp_classes_.back()];
            comp_classes_.pop_back(); // Keep this one
            for (unsigned compi : comp_classes_)
              {
                // fuse with base and delete
                base_class.insert(cand_classes[compi].begin(),
                                  cand_classes[compi].end());
                std::swap(cand_classes[compi], cand_classes.back());
                cand_classes.pop_back();
              }
            // finally add the current state that caused all the merging
            base_class.emplace_hint(base_class.end(), i);
          }
      };

    // Now we have equivalence classes
    // and a state can only be in exactly one.
    // (Otherwise the classes would have fused)
    // For each equiv class we take the first state as representative
    // and redirect all incoming edges to this one.
    std::vector<unsigned> remap(nb_states, -1U);
    for (const auto& [_, class_v] : equiv_class_)
      for (const auto& aclass : class_v)
        {
          (void)_; // please some versions of GCC
          unsigned rep = *aclass.begin();
          for (auto it = ++aclass.begin(); it != aclass.end(); ++it)
            remap[*it] = rep;
        }

    for (auto& e: edges())
      if (remap[e.dst] != -1U)
        e.dst = remap[e.dst];

    if (remap[get_init_state_number()] != -1U)
      set_init_state(remap[get_init_state_number()]);

    unsigned st = 0;
    for (auto& s: remap)
      if (s == -1U)
        s = st++;
      else
        s = -1U;

    defrag_states(remap, st);
    return remap.size() - st;
  }

  void twa_graph::purge_unreachable_states(shift_action* f, void* action_data)
  {
    unsigned num_states = g_.num_states();
    // The TODO vector serves two purposes:
    // - it is a stack of state to process,
    // - it is a set of processed states.
    // The lower 31 bits of each entry is a state on the stack. (The
    // next usable entry on the stack is indicated by todo_pos.)  The
    // 32th bit (i.e., the sign bit) of todo[x] indicates whether
    // states number x has been seen.
    std::vector<unsigned> todo(num_states, 0);
    const unsigned seen = 1U << (sizeof(unsigned)*8-1);
    const unsigned mask = seen - 1;
    unsigned todo_pos = 0;
    for (unsigned i: univ_dests(get_init_state_number()))
      {
        todo[i] |= seen;
        todo[todo_pos++] |= i;
      }
    do
      {
        unsigned cur = todo[--todo_pos] & mask;
        todo[todo_pos] ^= cur;        // Zero the state
        for (auto& t: g_.out(cur))
          for (unsigned dst: univ_dests(t.dst))
            if (!(todo[dst] & seen))
              {
                todo[dst] |= seen;
                todo[todo_pos++] |= dst;
              }
      }
    while (todo_pos > 0);
    // Now renumber each used state.
    unsigned current = 0;
    for (auto& v: todo)
      if (!(v & seen))
        v = -1U;
      else
        v = current++;
    if (current == todo.size())
      return;                        // No unreachable state.

    // Removing some non-deterministic dead state could make the
    // automaton universal.
    if (prop_universal().is_false())
      prop_universal(trival::maybe());
    if (prop_complete().is_false())
      prop_complete(trival::maybe());

    if (f)
      (*f)(todo, action_data);

    defrag_states(todo, current);
  }

  void twa_graph::purge_dead_states()
  {
    unsigned num_states = g_.num_states();
    std::vector<unsigned> useful(num_states, 0);

    // Make a DFS to compute a topological order.
    std::vector<unsigned> order;
    order.reserve(num_states);

    bool purge_unreachable_needed = false;

    if (is_existential())
      {
        std::vector<std::pair<unsigned, unsigned>> todo; // state, edge
        useful[get_init_state_number()] = 1;
        todo.emplace_back(init_number_, g_.state_storage(init_number_).succ);
        do
          {
            unsigned src;
            unsigned tid;
            std::tie(src, tid) = todo.back();
            if (tid == 0U)
              {
                todo.pop_back();
                order.emplace_back(src);
                continue;
              }
            auto& t = g_.edge_storage(tid);
            todo.back().second = t.next_succ;
            unsigned dst = t.dst;
            if (useful[dst] != 1 && t.cond != bddfalse)
              {
                todo.emplace_back(dst, g_.state_storage(dst).succ);
                useful[dst] = 1;
              }
          }
        while (!todo.empty());
      }
    else
      {
        // state, edge, begin, end
        std::vector<std::tuple<unsigned, unsigned,
                               const unsigned*, const unsigned*>> todo;
        auto& dests = g_.dests_vector();

        auto beginend = [&](const unsigned& dst,
                            const unsigned*& begin, const unsigned*& end)
          {
            if ((int)dst < 0)
              {
                begin = dests.data() + ~dst + 1;
                end = begin + dests[~dst];
              }
            else
              {
                begin = &dst;
                end = begin + 1;
              }
          };
        {
          const unsigned* begin;
          const unsigned* end;
          beginend(init_number_, begin, end);
          todo.emplace_back(init_number_, 0U, begin, end);
        }

        for (;;)
          {
            unsigned& tid = std::get<1>(todo.back());
            const unsigned*& begin = std::get<2>(todo.back());
            const unsigned*& end = std::get<3>(todo.back());
            if (tid == 0U && begin == end)
              {
                unsigned src = std::get<0>(todo.back());
                todo.pop_back();
                // Last transition from a state?
                if ((int)src >= 0 && (todo.empty()
                                      || src != std::get<0>(todo.back())))
                  order.emplace_back(src);
                if (todo.empty())
                  break;
                else
                  continue;
              }
            unsigned dst = *begin++;
            if (begin == end)
              // that was the last destination, update the stack for
              // the next edge.
              {
                do
                  tid = g_.edge_storage(tid).next_succ;
                while (tid && g_.edge_storage(tid).cond == bddfalse);
                if (tid != 0)
                  beginend(g_.edge_storage(tid).dst, begin, end);
              }
            if (useful[dst] != 1)
              {
                auto& ss = g_.state_storage(dst);
                unsigned succ = ss.succ;
                while (succ && g_.edge_storage(succ).cond == bddfalse)
                  succ = g_.edge_storage(succ).next_succ;
                if (succ == 0U)
                  continue;
                useful[dst] = 1;
                const unsigned* begin;
                const unsigned* end;
                beginend(g_.edge_storage(succ).dst, begin, end);
                todo.emplace_back(dst, succ, begin, end);
              }
          }
      }

    // At this point, all reachable states with successors are marked
    // as useful.
    for (;;)
      {
        bool univ_edge_erased = false;
        // Process states in topological order to mark those without
        // successors as useless.
        for (auto s: order)
          {
            auto t = g_.out_iteraser(s);
            bool useless = true;
            while (t)
              {
                // An edge is useful if all its
                // destinations are useful.
                bool usefuledge = true;
                for (unsigned d: univ_dests(t->dst))
                  if (!useful[d])
                    {
                      usefuledge = false;
                      break;
                    }
                // Erase any useless edge
                if (!usefuledge)
                  {
                    if (is_univ_dest(t->dst))
                      univ_edge_erased = true;
                    t.erase();
                    continue;
                  }
                // if we have a edge to a useful state, then the
                // state is useful.
                useless = false;
                ++t;
              }
            if (useless)
              useful[s] = 0;
          }
        // If we have erased any universal destination, it is possible
        // that we have have created some new dead states, so we
        // actually need to redo the whole thing again until there is
        // no more universal edge to remove.  Also we might have
        // created some unreachable states, so we will simply call
        // purge_unreachable_states() later to clean this.
        if (!univ_edge_erased)
          break;
        else
          purge_unreachable_needed = true;
      }

    // Is the initial state actually useful?  If not, make this an
    // empty automaton by resetting the graph.
    bool usefulinit = true;
    for (unsigned d: univ_dests(init_number_))
      if (!useful[d])
        {
          usefulinit = false;
          break;
        }
    if (!usefulinit)
      {
        g_ = graph_t();
        init_number_ = new_state();
        prop_universal(true);
        prop_complete(false);
        prop_stutter_invariant(true);
        prop_weak(true);
        return;
      }

    // Renumber each used state.
    unsigned current = 0;
    for (unsigned s = 0; s < num_states; ++s)
      if (useful[s])
        useful[s] = current++;
      else
        useful[s] = -1U;
    if (current == num_states)
      return;                        // No useless state.

    // Removing some non-deterministic dead state could make the
    // automaton universal.  Likewise for non-complete.
    if (prop_universal().is_false())
      prop_universal(trival::maybe());
    if (prop_complete().is_false())
      prop_complete(trival::maybe());

    defrag_states(useful, current);

    if (purge_unreachable_needed)
      purge_unreachable_states();
  }

  void twa_graph::defrag_states(std::vector<unsigned>& newst,
                                unsigned used_states)
  {
    if (!is_existential())
      {
        // Running defrag_states() on alternating automata is tricky,
        // because we want to
        // #1 rename the regular states
        // #2 rename the states in universal destinations
        // #3 get rid of the unused universal destinations
        // #4 merge identical universal destinations
        //
        // graph::degrag_states() actually does only #1. It could
        // do #2, but that would prevent us from doing #3 and #4.  It
        // cannot do #3 and #4 because the graph object does not know
        // what an initial state is, and our initial state might be
        // universal.
        //
        // As a consequence this code preforms #2, #3, and #4 before
        // calling graph::degrag_states() to finish with #1.  We clear
        // the "dests vector" of the current automaton, recreate all
        // the new destination groups using a univ_dest_mapper to
        // simplify and unify them, and extend newst with some new
        // entries that will point the those new universal destination
        // so that graph::defrag_states() does not have to deal with
        // universal destination in any way.
        auto& g = get_graph();
        auto& dests = g.dests_vector();

        // Clear the destination vector, saving the old one.
        std::vector<unsigned> old_dests;
        std::swap(dests, old_dests);
        // dests will be updated as a side effect of declaring new
        // destination groups to uniq.
        internal::univ_dest_mapper<twa_graph::graph_t> uniq(g);

        // The newst entry associated to each of the old destination
        // group.
        std::vector<unsigned> seen(old_dests.size(), -1U);

        // Rename a state if it denotes a universal destination.  This
        // function has to be applied to the destination of each edge,
        // as well as to the initial state.  The need to work on the
        // initial state is the reason it cannot be implemented in
        // graph::defrag_states().
        auto fixup = [&](unsigned& in_dst)
          {
            unsigned dst = in_dst;
            if ((int) dst >= 0)       // not a universal edge
              return;
            dst = ~dst;
            unsigned& nd = seen[dst];
            if (nd == -1U)      // An unprocessed destination group
              {
                // store all renamed destination states in tmp
                std::vector<unsigned> tmp;
                auto begin = old_dests.data() + dst + 1;
                auto end = begin + old_dests[dst];
                while (begin != end)
                  {
                    unsigned n = newst[*begin++];
                    if (n == -1U)
                      continue;
                    tmp.emplace_back(n);
                  }
                if (tmp.empty())
                  {
                    // All destinations of this group were marked for
                    // removal.  Mark this universal transition for
                    // removal as well.  Is this really what we expect?
                    nd = -1U;
                  }
                else
                  {
                    // register this new destination group, add it to
                    // newst, and use the index in newst to relabel
                    // the state so that graph::degrag_states() will
                    // eventually update it to the correct value.
                    nd = newst.size();
                    newst.emplace_back(uniq.new_univ_dests(tmp.begin(),
                                                           tmp.end()));
                  }
              }
            in_dst = nd;
          };
        fixup(init_number_);
        for (auto& e: edges())
          fixup(e.dst);
      }

    if (auto* names = get_named_prop<std::vector<std::string>>("state-names"))
      {
        unsigned size = names->size();
        for (unsigned s = 0; s < size; ++s)
          {
            unsigned dst = newst[s];
            if (dst == s || dst == -1U)
              continue;
            assert(dst < s);
            (*names)[dst] = std::move((*names)[s]);
          }
        names->resize(used_states);
      }
    if (auto hs = get_named_prop<std::map<unsigned, unsigned>>
        ("highlight-states"))
      {
        std::map<unsigned, unsigned> hs2;
        for (auto p: *hs)
          {
            unsigned dst = newst[p.first];
            if (dst != -1U)
              hs2[dst] = p.second;
          }
        std::swap(*hs, hs2);
      }
    if (auto os = get_named_prop<std::vector<unsigned>>("original-states"))
      {
        unsigned size = os->size();
        for (unsigned s = 0; s < size; ++s)
          {
            unsigned dst = newst[s];
            if (dst == s || dst == -1U)
              continue;
            assert(dst < s);
            (*os)[dst] = (*os)[s];
          }
        os->resize(used_states);
      }
    if (auto dl = get_named_prop<std::vector<unsigned>>("degen-levels"))
      {
        unsigned size = dl->size();
        for (unsigned s = 0; s < size; ++s)
          {
            unsigned dst = newst[s];
            if (dst == s || dst == -1U)
              continue;
            assert(dst < s);
            (*dl)[dst] = (*dl)[s];
          }
        dl->resize(used_states);
      }
    if (auto ss = get_named_prop<std::vector<unsigned>>("simulated-states"))
      {
        for (auto& s : *ss)
          {
            if (s >= newst.size())
              s = -1U;
            else
              s = newst[s];
          }
      }
    init_number_ = newst[init_number_];
    g_.defrag_states(newst, used_states);
  }

  void twa_graph::remove_unused_ap()
  {
    if (ap().empty())
      return;
    bdd all = ap_vars();
    for (auto& e: g_.edges())
      {
        all = bdd_exist(all, bdd_support(e.cond));
        if (all == bddtrue)    // All APs are used.
          return;
      }
    auto d = get_dict();
    while (all != bddtrue)
      {
        unregister_ap(bdd_var(all));
        all = bdd_high(all);
      }
  }

  void twa_graph::copy_state_names_from(const const_twa_graph_ptr& other)
  {
    if (other == shared_from_this())
      return;

    auto orig = get_named_prop<std::vector<unsigned>>("original-states");
    auto lvl = get_named_prop<std::vector<unsigned>>("degen-levels");
    auto sims = get_named_prop<std::vector<unsigned>>("simulated-states");

    assert(!lvl || orig);

    if (orig && sims)
      throw std::runtime_error("copy_state_names_from(): original-states and "
                               "simulated-states are both set");

    if (orig && orig->size() != num_states())
      throw std::runtime_error("copy_state_names_from(): unexpected size "
                               "for original-states");
    if (lvl && lvl->size() != num_states())
      throw std::runtime_error("copy_state_names_from(): unexpected size "
                               "for degen-levels");

    if (sims && sims->size() != other->num_states())
      throw std::runtime_error("copy_state_names_from(): unexpected size "
                               "for simulated-states");

    auto names = std::unique_ptr<std::vector<std::string>>
      (new std::vector<std::string>);
    unsigned ns = num_states();
    unsigned ons = other->num_states();

    for (unsigned s = 0; s < ns; ++s)
      {
        std::string newname = "";
        if (sims)
          {
            for (unsigned t = 0; t < ons; ++t)
              {
                if (s == (*sims)[t])
                  newname += other->format_state(t) + ',';
              }
            assert(!newname.empty());
            newname.pop_back(); // remove trailing comma
            newname = '[' + newname + ']';
          }
        else
          {
            unsigned other_s = orig ? (*orig)[s] : s;
            if (other_s >= ons)
              throw std::runtime_error("copy_state_names_from(): state does not"
                                       " exist in source automaton");
            newname = other->format_state(other_s);
            if (lvl)
              newname += '#' + std::to_string((*lvl)[s]);
          }
        names->emplace_back(newname);
      }

    set_named_prop("state-names", names.release());
  }

  void twa_graph::kill_state(unsigned state)
  {
    auto t = g_.out_iteraser(state);
    while (t)
      t.erase();
    // A complete automaton is unlikely to stay
    // complete after killing a state.
    if (prop_complete().is_true())
      prop_complete(trival::maybe());
    prop_stutter_invariant(trival::maybe());
    // Many properties are preserved by state removal, and may even
    // become true if they were false before and the appropriate
    // states are removed.
    if (prop_universal().is_false())
      prop_universal(trival::maybe());
    if (prop_inherently_weak().is_false())
      prop_inherently_weak(trival::maybe());
    if (prop_weak().is_false())
      prop_weak(trival::maybe());
    if (prop_very_weak().is_false())
      prop_very_weak(trival::maybe());
    if (prop_terminal().is_false())
      prop_terminal(trival::maybe());
    if (prop_unambiguous().is_false())
      prop_unambiguous(trival::maybe());
    if (prop_semi_deterministic().is_false())
      prop_semi_deterministic(trival::maybe());
  }

  void twa_graph::dump_storage_as_dot(std::ostream& out,
                                      const char* opt) const
  {
    bool want_vectors = false;
    bool want_data = false;
    bool want_properties = false;
    if (!opt || !*opt)
      {
        want_vectors = want_data = want_properties = true;
      }
    else
      {
        while (*opt)
          switch (*opt++)
            {
            case 'v':
              want_vectors = true;
              break;
            case 'd':
              want_data = true;
              break;
            case 'p':
              want_properties = true;
              break;
            default:
              throw std::runtime_error
                ("dump_storage_as_dow(): unsupported option '"s + opt[-1] +"'");
            }
      }

    const graph_t& g = get_graph();

    g.dump_storage_as_dot(out, graph_t::DSI_GraphHeader);
    out << "rankdir=BT\n";

    if (want_vectors)
      {
        out << "{rank=same;\n";

        g.dump_storage_as_dot(out, graph_t::DSI_States |
                              graph_t::DSI_EdgesHeader);

        auto edges = g.edge_vector();
        unsigned eend = edges.size();
        out << "<tr><td>cond</td>\n";
        for (unsigned e = 1; e < eend; ++e)
          {
            out << "<td>";
            std::string f = bdd_format_formula(get_dict(), edges[e].cond);
            escape_html(out, f);
            out << "</td>\n";
          }
        out << "</tr>\n<tr><td>acc</td>\n";
        for (unsigned e = 1; e < eend; ++e)
          out << "<td>" << edges[e].acc << "</td>\n";
        out << "</tr>\n";

        g.dump_storage_as_dot(out, graph_t::DSI_EdgesBody
                              | graph_t::DSI_EdgesFooter
                              | graph_t::DSI_Dests);
        out << "}\n";
      }
    if (want_data || want_properties)
      {
        out << "{rank=same;\n";

        if (want_data)
          {
            out << ("meta [label=<\n"
                    "<table border='0' cellborder='0' cellspacing='0'>\n");
            unsigned d = get_init_state_number();
            out << ("<tr><td align='left'>init_state:</td>"
                    "<td align='left' bgcolor='");
            if ((int)d < 0)
              out << "pink'>~" << ~d;
            else
              out << "yellow'>" << d;
            out << ("</td></tr><tr><td align='left'>num_sets:</td>"
                    "<td align='left' >")
                << num_sets()
                << ("</td></tr><tr><td align='left'>acceptance:</td>"
                    "<td align='left' >");
            get_acceptance().to_html(out);
            out << ("</td></tr><tr><td align='left'>ap_vars:</td>"
                    "<td align='left'>");
            escape_html(out, bdd_format_sat(get_dict(), ap_vars()));
            out << "</td></tr></table>>]\n";
          }
        if (want_properties)
          {
            out << ("props [label=<\n"
                    "<table border='0' cellborder='0' cellspacing='0'>\n");
#define print_prop(name)                                                \
            out << ("<tr><td align='left'>" #name ":</td>"              \
                    "<td align='left' >") << name() << "</td></tr>\n";
            print_prop(prop_state_acc);
            print_prop(prop_inherently_weak);
            print_prop(prop_terminal);
            print_prop(prop_weak);
            print_prop(prop_very_weak);
            print_prop(prop_complete);
            print_prop(prop_universal);
            print_prop(prop_unambiguous);
            print_prop(prop_semi_deterministic);
            print_prop(prop_stutter_invariant);
#undef print_prop
            out << "</table>>]\n";

            if (!named_prop_.empty())
              {
                // GraphiViz 2.46.0 has a bug where plain newlines in
                // quoted strings are ignored.  See
                // https://gitlab.com/graphviz/graphviz/-/issues/1931
                // A workaround is to use emit \n instead of the
                // actual new line.
                out << "namedprops [label=\"named properties:\\n";
                for (auto p: named_prop_)
                  escape_html(out, p.first) << "\\n";
                out << "\"]\n";
              }
          }
        out << "}\n";
      }

    if (want_data && want_vectors)
      out << "meta -> states [style=invis]\n";
    if (want_properties && want_vectors)
      {
        out << "props -> edges [style=invis]\n";
        if (!named_prop_.empty())
          {
            out << "namedprops -> edges [style=invis]\n";
            if (!is_existential())
              out << "namedprops -> dests [style=invis]\n";
          }
      }
    g.dump_storage_as_dot(out, graph_t::DSI_GraphFooter);
  }

  namespace
  {
    twa_graph_ptr
    copy(const const_twa_ptr& aut, twa::prop_set p,
         bool preserve_names, unsigned max_states)
    {
      // If the input is a twa_graph and the number of states is not
      // restricted, simply use the make_twa_graph variant for
      // twa_graph.  Not only is this faster, but this is also
      // necessary as a workaround for Swig-3 calling the wrong copy
      // of make_twa_graph because it tests if twa match before
      // testing twa_graph (swig-4 seems fixed).
      const_twa_graph_ptr aut_g =
        std::dynamic_pointer_cast<const twa_graph>(aut);
      if (max_states == -1U && aut_g)
        return make_twa_graph(aut_g, p, preserve_names);

      twa_graph_ptr out = make_twa_graph(aut->get_dict());
      out->copy_acceptance_of(aut);
      out->copy_ap_of(aut);
      out->prop_copy(aut, p);

      std::vector<std::string>* names = nullptr;
      std::set<unsigned>* incomplete = nullptr;

      // Old highlighting maps
      typedef std::map<unsigned, unsigned> hmap;
      hmap* ohstates = nullptr;
      hmap* ohedges = nullptr;
      // New highlighting maps
      hmap* nhstates = nullptr;
      hmap* nhedges = nullptr;

      if (preserve_names)
        {
          names = new std::vector<std::string>;
          out->set_named_prop("state-names", names);

          // If the input is a twa_graph and we were asked to preserve
          // names, also preserve highlights.
          if (aut_g)
            {
              ohstates = aut->get_named_prop<hmap>("highlight-states");
              if (ohstates)
                nhstates = out->get_or_set_named_prop<hmap>("highlight-states");
              ohedges = aut->get_named_prop<hmap>("highlight-edges");
              if (ohedges)
                nhedges = out->get_or_set_named_prop<hmap>("highlight-edges");
            }
        }

      // States already seen.
      state_map<unsigned> seen;
      // States to process
      std::deque<state_map<unsigned>::value_type> todo;

      auto new_state = [&](const state* s) -> unsigned
        {
          auto p = seen.emplace(s, 0);
          if (p.second)
            {
              p.first->second = out->new_state();
              todo.emplace_back(*p.first);
              if (names)
                names->emplace_back(aut->format_state(s));
              if (ohstates)
                {
                  auto q = ohstates->find(aut_g->state_number(s));
                  if (q != ohstates->end())
                    nhstates->emplace(p.first->second, q->second);
                }
            }
          else
            {
              s->destroy();
            }
          return p.first->second;
        };

      out->set_init_state(new_state(aut->get_init_state()));
      while (!todo.empty())
        {
          const state* src1;
          unsigned src2;
          std::tie(src1, src2) = todo.front();
          todo.pop_front();
          for (auto* t: aut->succ(src1))
            {
              unsigned edgenum = 0;
              if (SPOT_UNLIKELY(max_states < out->num_states()))
                {
                  // If we have reached the max number of state, never try
                  // to create a new one.
                  auto i = seen.find(t->dst());
                  if (i == seen.end())
                    {
                      if (!incomplete)
                        incomplete = new std::set<unsigned>;
                      incomplete->insert(src2);
                      continue;
                    }
                  edgenum = out->new_edge(src2, i->second, t->cond(), t->acc());
                }
              else
                {
                  edgenum = out->new_edge(src2, new_state(t->dst()),
                                          t->cond(), t->acc());
                }
              if (ohedges)
                {
                  auto q = ohedges->find(aut_g->edge_number(t));
                  if (q != ohedges->end())
                    nhedges->emplace(edgenum, q->second);
                }
            }
        }


      auto s = seen.begin();
      while (s != seen.end())
        {
          // Advance the iterator before deleting the "key" pointer.
          const state* ptr = s->first;
          ++s;
          ptr->destroy();
        }

      if (incomplete)
        out->set_named_prop("incomplete-states", incomplete);
      return out;
    }
  }

  twa_graph_ptr make_twa_graph(const const_twa_ptr& aut, twa::prop_set p,
                               bool preserve_names, unsigned max_states)
  {
    if (max_states == -1U && !preserve_names)
      if (auto a = std::dynamic_pointer_cast<const twa_graph>(aut))
        return SPOT_make_shared_enabled__(twa_graph, a, p);
    return copy(aut, p, preserve_names, max_states);
  }
}
