#include <assert.h>

#include "game.h"
#include "move.h"
#include "solver.h"
#include "util.h"

class MiniMax : public Solver {
 public:
  int solve(Game *node, int depth, move_t *best_move) {
    if (depth == 0) {
      return evaluate_state(node);
    }

    auto moves = node->list_legal_moves();
    if (moves.size() == 0) {
      return evaluate_state(node);
    }

    bool is_maxie = node->get_cur_player() == MAXIE;
    bool is_minie = node->get_cur_player() == MINIE;

    int cur_best = is_maxie ? NINF : PINF;
    for (move_t move : moves) {
      Game *child = node->make_move(move);
      move_t child_best_move;  // placeholder
      int value = solve(child, depth - 1, &child_best_move);

      if ((is_maxie && value > cur_best) || (is_minie && value < cur_best)) {
        cur_best = value;
        *best_move = move;
      }

      delete child;
    }

    assert(cur_best != NINF);
    assert(cur_best != PINF);

    return cur_best;
  }
};
