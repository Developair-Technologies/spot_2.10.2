#!/usr/bin/python3
# -*- mode: python; coding: utf-8 -*-
# Copyright (C) 2020 Laboratoire de Recherche et Développement de
# l'EPITA.
#
# This file is part of Spot, a model checking library.
#
# Spot is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# Spot is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
# License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

import spot

g = spot.automaton("""HOA: v1 States: 9 Start: 0 AP: 2 "a" "b"
acc-name: Streett 1 Acceptance: 2 Fin(0) | Inf(1) properties:
trans-labels explicit-labels state-acc spot-state-player: 0 1 0 1 0 1
0 1 1 --BODY-- State: 0 {1} [1] 1 [1] 3 State: 1 {1} [1] 2 State: 2
{1} [0] 8 State: 3 {1} [1] 4 State: 4 {1} [0] 5 State: 5 {1} [0] 6
State: 6 {1} [1] 7 State: 7 State: 8 {1} [0] 2 --END--""")

assert spot.solve_parity_game(g) == False

s = spot.highlight_strategy(g).to_str("HOA", "1.1")
assert s == """HOA: v1.1
States: 9
Start: 0
AP: 2 "a" "b"
acc-name: Streett 1
Acceptance: 2 Fin(0) | Inf(1)
properties: trans-labels explicit-labels state-acc !complete
properties: !deterministic exist-branch
spot.highlight.states: 0 5 1 4 2 4 3 5 4 5 5 5 6 5 7 5 8 4
spot.highlight.edges: 2 5 3 4 6 5 8 5 9 4
spot.state-player: 0 1 0 1 0 1 0 1 1
--BODY--
State: 0 {1}
[1] 1
[1] 3
State: 1 {1}
[1] 2
State: 2 {1}
[0] 8
State: 3 {1}
[1] 4
State: 4 {1}
[0] 5
State: 5 {1}
[0] 6
State: 6 {1}
[1] 7
State: 7
State: 8 {1}
[0] 2
--END--"""
