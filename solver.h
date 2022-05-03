#ifndef SOLVER_H
#define SOLVER_H

#include "game.h"
#include "move.h"

#define DISC_WEIGHT 1
#define CORNER_DISC_WEIGHT 1000
#define MOVE_WEIGHT 100

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
    int score = 0;

    // count discs
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        if (node->get_square(i, j) == MAXIE) {
          score += DISC_WEIGHT;
        } else if (node->get_square(i, j) == MINIE) {
          score -= DISC_WEIGHT;
        }
      }
    }

    // count corner discs
    for (int i = 0; i < 4; i++) {
      coord_t disc = CORNER_DISCS[i];
      if (node->get_square(disc.row, disc.col) == MAXIE) {
        score += CORNER_DISC_WEIGHT;
      } else if (node->get_square(disc.row, disc.col) == MINIE) {
        score -= CORNER_DISC_WEIGHT;
      }
    }

    // count legal moves
    int num_legal_moves = node->list_legal_moves().size();
    if (node->get_cur_player() == MAXIE) {
      score += num_legal_moves * MOVE_WEIGHT;
    } else {
      score -= num_legal_moves * MOVE_WEIGHT;
    }

    return score;
  };
};

#endif
