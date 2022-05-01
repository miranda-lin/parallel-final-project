#include "game.h"
#include "move.h"
#include "parasolver.h"

class ParaMiniMax : public ParaSolver {
 public:
  int solve(Game *node, int depth, move_t *best_move) {
    if (depth == 0) {
      return evaluate_state(node);
    }

    auto moves = node->list_legal_moves();

    int cur_best;
    bool has_best = false;
#pragma omp parallel
    for (move_t move : moves) {
      Game *child = node->make_move(move);
      move_t child_best_move;  // placeholder
      int value = solve(child, depth - 1, &child_best_move);

      if (!has_best || (node->get_cur_player() == MAXIE && value > cur_best) ||
          (node->get_cur_player() == MINIE && value < cur_best)) {
        cur_best = value;
        *best_move = move;

        has_best = true;
      }

      delete child;
    }
#pragma omp barrier

    return cur_best;
  }
};
