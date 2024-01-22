//
// Created by 13584 on 2024/1/9.
//

#ifndef PROJECT1_INCLUDE_MENU_H_
#define PROJECT1_INCLUDE_MENU_H_

#include "common.h"
#include "utils/input.h"
#include "utils/display.h"
#include "game/game.h"

#define NUM_WIDGETS 3
#define WIDGET_X 240
#define WIDGET_Y_TOP 480
#define WIDGET_Y_GAP 70
#define SIZE 60

#define SIZE_OF_TITLE 100

void do_menu_logic();

static void draw_menu();

typedef void (*Action)();

typedef struct {
  char const *text;
  int x,y;
  Action action;
} Widget;

typedef struct {
  char *name;
  int score;
} Rank;



static void init_widgets();

static void quit_widgets();

static void do_widgets();

static void prev_widget();

static void next_widget();

static void act_widget();

static void action_start();

static void action_quit();

static void action_rank();

static void draw_rank();

void init_rank(Rank *rk);

void quit_rank(Rank *rk);

#endif //PROJECT1_INCLUDE_MENU_H_
