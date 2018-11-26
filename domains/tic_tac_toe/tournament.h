// Copyright 2018 The Darwin Neuroevolution Framework Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <core/darwin.h>
#include <core/evolution.h>
#include <core/parallel_for_each.h>
#include <core/properties.h>

namespace tic_tac_toe {

struct TournamentConfig : public core::PropertySet {
  PROPERTY(eval_games, int, 10, "Number of evaluation games");
  PROPERTY(rematches, bool, true, "Play both-side rematches?");
};

enum class GameOutcome {
  FirstPlayerWins,
  SecondPlayerWins,
  Draw,
};

GameOutcome reverseOutcome(GameOutcome outcome);

class GameRules : public core::NonCopyable {
 public:
  virtual GameOutcome play(const darwin::Genotype* player1,
                           const darwin::Genotype* player2) const = 0;

  virtual float score(GameOutcome outcome) const = 0;
};

class Tournament : public core::NonCopyable {
 public:
  Tournament(const core::PropertySet& config, GameRules* game);

  void evaluatePopulation(darwin::Population* population);

 private:
  TournamentConfig config_;
  GameRules* game_;
};

}  // namespace tic_tac_toe
