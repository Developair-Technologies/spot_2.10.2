# -*- mode: python; coding: utf-8 -*-
# Copyright (C) 2021 Laboratoire de Recherche et Développement
# de l'Epita
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

# A shared variable caused the 2nd call to ltl_to_game to give an incorrect
# result.
for i in range(0, 2):
    gi = spot.synthesis_info()
    gi.s = spot.synthesis_info.algo_LAR
    game = spot.ltl_to_game("(Ga) <-> (Fb)", ["b"], gi)
    assert not spot.solve_game(game)

# A game can have only inputs
game = spot.ltl_to_game("GFa", [])
assert(game.to_str() == """HOA: v1
States: 3
Start: 0
AP: 1 "a"
acc-name: parity max odd 6
Acceptance: 6 Inf(5) | (Fin(4) & (Inf(3) | (Fin(2) & (Inf(1) | Fin(0)))))
properties: trans-labels explicit-labels state-acc colored complete
properties: deterministic
spot-state-player: 0 1 1
--BODY--
State: 0 {1}
[!0] 1
[0] 2
State: 1 {4}
[t] 0
State: 2 {5}
[t] 0
--END--""")
