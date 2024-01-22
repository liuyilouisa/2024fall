//
// Created by 13584 on 2024/1/14.
//

#ifndef PROJECT1_INCLUDE_GAME_BLOCK_H_
#define PROJECT1_INCLUDE_GAME_BLOCK_H_

#include "common.h"
#include "utils/display.h"

#define LIB_SIZE 2

typedef struct{
  double x,y;
} Center;

typedef struct {
  double x,y;
  Center center;
  double r;
  SDL_Texture *texture_block;
} Block;

extern Block next_block;
extern Block this_block;
extern Block last_block;

#endif //PROJECT1_INCLUDE_GAME_BLOCK_H_
