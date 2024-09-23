//
// Created by 13584 on 2024/1/14.
//

#ifndef PROJECT1_INCLUDE_GAME_PLAYER_H_
#define PROJECT1_INCLUDE_GAME_PLAYER_H_

#include "common.h"

#define PLAYER_INIT_X 297
#define PLAYER_INIT_Y 469
#define PLAYER_W 16
#define PLAYER_H 57
#define PLAYER_dx 1.0
#define PLAYER_dy 0.4
#define TIME_MAX 800
#define G 0.7

typedef struct {
  SDL_Texture *texture;
  double x,y;
  double dx,dy;
} Player;

void init_player(Player *player);
void do_player(Player *player);
void draw_jump(Player *player);

extern double jump_lenth;
extern SDL_Rect rect_player;

#endif //PROJECT1_INCLUDE_GAME_PLAYER_H_
