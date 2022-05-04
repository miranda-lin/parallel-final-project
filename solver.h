#ifndef SOLVER_H
#define SOLVER_H

#include <assert.h>

#include "game.h"
#include "move.h"
#include "util.h"

#define DISC_WEIGHT 1
#define CORNER_DISC_WEIGHT 1000

coord_t TOP_LEFT = (coord_t){0, 0};
coord_t TOP_RIGHT = (coord_t){0, COLS - 1};
coord_t BOTTOM_LEFT = (coord_t){ROWS - 1, 0};
coord_t BOTTOM_RIGHT = (coord_t){ROWS - 1, COLS - 1};
coord_t CORNER_DISCS[] = {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};

class Solver {
 public:
  virtual int solve(Game *node, int depth, move_t *best_move) = 0;

  Solver() {}

 protected:
  int evaluate_state(Game *node) {
    // count discs
    int disc_score = 0;
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        if (node->get_square(i, j) == MAXIE) {
          disc_score++;
        } else if (node->get_square(i, j) == MINIE) {
          disc_score--;
        }
      }
    }

    // count corner discs
    int corner_disc_score = 0;
    for (int i = 0; i < 4; i++) {
      coord_t disc = CORNER_DISCS[i];
      if (node->get_square(disc.row, disc.col) == MAXIE) {
        corner_disc_score++;
      } else if (node->get_square(disc.row, disc.col) == MINIE) {
        corner_disc_score--;
      }
    }

    int score =
        (DISC_WEIGHT * disc_score) + (CORNER_DISC_WEIGHT * corner_disc_score);
    assert(score != PINF);

    return score;
  };
};

#endif
