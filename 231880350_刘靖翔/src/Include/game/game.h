//
// Created by 13584 on 2024/1/12.
//

#ifndef PROJECT1_INCLUDE_GAME_H_
#define PROJECT1_INCLUDE_GAME_H_

#include "common.h"
#include "utils/input.h"
#include "utils/display.h"
#include "game/player.h"
#include "time.h"
#include "game/block.h"
#include "menu.h"

#define BLOCK_INIT_X 250
#define BLOCK_INIT_Y 500
#define BLOCK_W 112
#define BLOCK_H 77
#define BLOCK_INIT_CX 306
#define BLOCK_INIT_CY 522

void do_game_logic();

static void do_game_input();
void do_draw_game();
static void do_fps();
static void check_player();
static void generate_block(double gap);
static void init_block();
static void draw_back(int gap,Player *p);
static void shift_block();
static void do_game_over();
static void do_ranklist();
static void draw_game_over();

#define R 30

extern bool jump;

#endif //PROJECT1_INCLUDE_GAME_H_
