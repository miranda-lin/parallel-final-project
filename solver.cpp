#include "solver.h"

int Solver::evaluate_state(Game *node) {
  int score = 0;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (node->get_square(i, j) == MAXIE) {
        score++;
      } else if (node->get_square(i, j) == MINIE) {
        score--;
      }
    }
  }
  return score;
};
