#ifndef MOVE_H
#define MOVE_H

#include "player.h"

struct coord_t {
  int row;
  int col;
};

struct move_t {
  Player player;
  coord_t loc;
};

#endif
