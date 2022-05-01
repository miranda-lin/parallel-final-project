#ifndef PARA_SOLVER_H
#define PARA_SOLVER_H

#include <omp.h>

#include "solver.h"

class ParaSolver : public Solver {
 public:
  virtual int solve(Game *node, int depth, move_t *best_move) = 0;

  ParaSolver() {}

 protected:
  int evaluate_state(Game *node) {
    int score = 0;

#pragma omp parallel for collapse(2)
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        if (node->get_square(i, j) == MAXIE) {
          score++;
        } else if (node->get_square(i, j) == MINIE) {
          score--;
        }
      }
    }
#pragma omp barrier

    return score;
  };
};

#endif
