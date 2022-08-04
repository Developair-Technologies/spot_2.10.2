// -*- coding: utf-8 -*-
// Copyright (C) 2021 Laboratoire de Recherche et Développement
// de l'Epita (LRDE).
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

#pragma once

#include <spot/twa/twagraph.hh>

namespace spot
{
  /// todo
  /// Comment je faire au mieux pour expliquer mealy dans les doc

  /// \brief Checks whether or not the automaton is a mealy machine
  ///
  /// \param m The automaton to be verified
  /// \note A mealy machine must have the named property \"synthesis-outputs\"
  /// and have a \"true\" as acceptance condition
  SPOT_API bool
  is_mealy(const const_twa_graph_ptr& m);

  /// \brief Checks whether or not the automaton is a separated mealy machine
  ///
  /// \param m The automaton to be verified
  /// \note A separated mealy machine is a mealy machine machine with all
  /// transitions having the form (in)&(out) where in[out] is a bdd over
  /// input[output] propositions of m
  SPOT_API bool
  is_separated_mealy(const const_twa_graph_ptr& m);

  /// \brief Checks whether or not the automaton is a split mealy machine
  ///
  /// \param m The automaton to be verified
  /// \note A split mealy machine is a mealy machine machine with the named
  /// property \"state-player\". Moreover the underlying automaton
  /// must be alternating between the player and the env. Transitions
  /// leaving env[player] states can only be labeled by
  /// input[output] propositions.
  SPOT_API bool
  is_split_mealy(const const_twa_graph_ptr& m);

  /// \brief Checks whether or not a mealy machine is input deterministic
  ///
  /// \param m The automaton to be verified
  /// \note works all mealy machines, no matter whether they are split
  /// or separated or neither of neither of them.
  /// \note A machine is input deterministic if none of the states
  /// has two outgoing transitions that can agree on a assignement
  /// of the input propositions.
  SPOT_API bool
  is_input_deterministic_mealy(const const_twa_graph_ptr& m);


  /// \brief make each transition in a separated mealy machine a
  /// 2-step transition.
  ///
  /// \param m separated mealy machine to be split
  /// \return returns the equivalent split mealy machine if not done inplace
  /// @{
  SPOT_API twa_graph_ptr
  split_separated_mealy(const const_twa_graph_ptr& m);

  SPOT_API void
  split_separated_mealy_here(const twa_graph_ptr& m);
  /// @}

  /// \brief the inverse of split_separated_mealy
  SPOT_API twa_graph_ptr
  unsplit_mealy(const const_twa_graph_ptr& m);

  /// \brief reduce an (in)completely specified mealy machine
  ///        Based on signature inclusion or equality. This is not guaranteed
  ///        to find the minimal number of states but is usually faster.
  ///        This also comes at another drawback:
  ///        All applicable sequences have to be infinite. Finite
  ///        traces are disregarded
  /// \param mm The mealy machine to be minimized, has to be unsplit
  /// \param output_assignment Whether or not to use output assignment
  /// \return A specialization of \c mm. Note that if mm is separated,
  /// the returned machine is separated as well.
  /// \note See todo TACAS22 Effective reductions of mealy machines
  /// @{
  SPOT_API twa_graph_ptr
  reduce_mealy(const const_twa_graph_ptr& mm,
               bool output_assignment = false);

  SPOT_API void
  reduce_mealy_here(twa_graph_ptr& mm,
                    bool output_assignment = false);
  /// @}

  /// \brief Minimizes a split (in)completely specified mealy machine
  /// The approach is described in \todo TACAS
  /// \param premin Use reduce_mealy before applying the
  ///               main algorithm if demanded AND
  ///               the original machine has no finite trace.
  ///               -1 : Do not use;
  ///                0 : Use without output assignment;
  ///                1 : Use with output assignment
  /// \return Returns a split mealy machines which is a minimal
  /// speciliazation of the original machine
  SPOT_API twa_graph_ptr
  minimize_mealy(const const_twa_graph_ptr& mm, int premin = -1);


  /// \brief Test if the split mealy machine \a right is a specialization of
  /// the split mealy machine \a left.
  ///
  /// That is all input sequences valid for left
  /// must be applicable for right and the induced sequence of output signals
  /// of right must imply the ones of left
  SPOT_API bool
  is_split_mealy_specialization(const_twa_graph_ptr left,
                                const_twa_graph_ptr right,
                                bool verbose = false);
}