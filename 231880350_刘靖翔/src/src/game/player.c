//
// Created by 13584 on 2024/1/14.
//
#include "game/player.h"
#include "math.h"
#include "utils/display.h"
#include "game/game.h"

double jump_lenth;
SDL_Rect rect_player;

void init_player(Player *player) {
  player->x = PLAYER_INIT_X;
  player->y = PLAYER_INIT_Y;
  player->dx = 0;
  player->dy = 0;
  jump = false;
  app.keyboard[SDL_SCANCODE_SPACE] = false;
}

void draw_jump(Player *player) {
  double dv = player->dx;
  int time = 2 * (int) (dv / G);
  jump_lenth = player->x;

  for (int i = 1; i <= time; ++i) {
    dv -= G;
    player->x += player->dx;
    player->y -= player->dy + dv + 0.1;
    do_draw_game();
    SDL_Delay(7);
  }
  jump_lenth = player->x - jump_lenth;
}

void do_player(Player *player) {
  unsigned int time;
  if (app.keyboard[SDL_SCANCODE_SPACE] && !running) {
    running = true;
    start = SDL_GetTicks();
  }
  if (app.keyboard[SDL_SCANCODE_SPACE] && running) {
    double tem = rect_player.h;
    rect_player.h = (int) (rect_player.h / 1.00005);
    double delta = tem - rect_player.h;
    player->y += delta;
  }
  if (!app.keyboard[SDL_SCANCODE_SPACE] && running) {

    Mix_Chunk *sjp = Mix_LoadWAV("./res/sound/Jump.mp3");
    Mix_PlayChannel(-1, sjp, 0);

    rect_player.h = PLAYER_H;
    player->y = PLAYER_INIT_Y;
    running = false;
    time = SDL_GetTicks() - start;
    if (time > TIME_MAX) { time = TIME_MAX; }
    player->dx = pow((time + 1000.0) / 1000.0, 4) * PLAYER_dx;
    player->dy = pow((time + 1000.0) / 1000.0, 4) * PLAYER_dy;

    draw_jump(player);

    jump = true;
    Mix_FreeChunk(sjp);
    return;
  }
}

