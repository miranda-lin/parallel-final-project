#ifndef SOLVER_H
#define SOLVER_H

#include "game.h"
#include "move.h"

class Solver {
 public:
  virtual int solve(Game *node, int depth, move_t *best_move) = 0;

  Solver() {}

 protected:
  int evaluate_state(Game *node);
};

#endif
