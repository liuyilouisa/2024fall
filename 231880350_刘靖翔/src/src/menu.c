//
// Created by 13584 on 2024/1/9.
//
#include "menu.h"
#include "utils/input.h"
#include "utils/display.h"
#include "game/game.h"

static Widget *widgets;
static long long int selection;
Mix_Music *bgm;

void do_menu_logic() {
//  printf("opening menu\n");
  SDL_Event event;
  init_widgets();
//  bgm = Mix_LoadMUS("./res/sound/menu.mp3");
//  Mix_PlayMusic(bgm,100);
  while (!app.keyboard[SDL_SCANCODE_ESCAPE] && SDL_WaitEvent(&event)) {
    do_event(event);

    do_widgets();

    draw_menu();
  }
//  Mix_FreeMusic(bgm);
  quit_widgets();
}

static void draw_menu() {
  clear();

  blit_image(texture_title, 150, 120);

  for (int i = 0; i < NUM_WIDGETS; ++i) {
    blit_text("./res/font/pixel.ttf", widgets[i].text, WIDGET_X, WIDGET_Y_TOP + WIDGET_Y_GAP * i, SIZE, black);
  }

  if (selection == 1) {
    blit_image(texture_pointer, WIDGET_X - 100, WIDGET_Y_TOP + WIDGET_Y_GAP - 10);
  } else if (selection == 0) {
    blit_image(texture_pointer, WIDGET_X - 100, WIDGET_Y_TOP - 10);
  } else if (selection == 2) {
    blit_image(texture_pointer, WIDGET_X - 100, WIDGET_Y_TOP + WIDGET_Y_GAP * (int) selection - 10);
  }

  present();

  SDL_SetRenderDrawColor(app.renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(app.renderer);
}

static void init_widgets() {
  widgets = malloc(NUM_WIDGETS * sizeof(Widget));
  widgets[0] = (Widget) {"Start", WIDGET_X, WIDGET_Y_TOP, action_start};
  widgets[1] = (Widget) {"Quit", WIDGET_X, WIDGET_Y_TOP + WIDGET_Y_GAP, action_quit};
  widgets[2] = (Widget) {"Rank", WIDGET_X, WIDGET_Y_TOP + WIDGET_Y_GAP * 2, action_rank};
  selection = 0;
}

static void quit_widgets() {
  free(widgets);
}

static void do_widgets() {
  if (app.keyboard[SDL_SCANCODE_UP] || app.keyboard[SDL_SCANCODE_LEFT]) {
    prev_widget();
  }
  if (app.keyboard[SDL_SCANCODE_DOWN] || app.keyboard[SDL_SCANCODE_RIGHT]) {
    next_widget();
  }
  if (app.keyboard[SDL_SCANCODE_SPACE] || app.keyboard[SDL_SCANCODE_RETURN]) {
    act_widget();
  }
}

static void prev_widget() {
  selection = (selection - 1 + NUM_WIDGETS) % NUM_WIDGETS;
}

static void next_widget() {
  selection = (selection + 1) % NUM_WIDGETS;
}

static void act_widget() {
  Mix_Chunk *select=Mix_LoadWAV("./res/sound/MENU_Select.mp3");
  Mix_PlayChannel(-1,select,0);
  Action action = widgets[selection].action;
  if (action) {
    action();
  }
  Mix_FreeChunk(select);
}

static void action_start() {
//  printf("Start.\n");
//  Mix_FreeMusic(bgm);
  Mix_HaltMusic();
  do_game_logic();
  Mix_PlayMusic(bgm,100);
}

static void action_quit() {
//  printf("Exited.\n");
//  Mix_FreeMusic(bgm);
  app.keyboard[SDL_SCANCODE_ESCAPE] = true;
}

static void action_rank() {
  SDL_Event event;
  app.keyboard[SDL_SCANCODE_SPACE] = false;
  while (!app.keyboard[SDL_SCANCODE_ESCAPE] && SDL_WaitEvent(&event)) {
    do_event(event);

    if (app.keyboard[SDL_SCANCODE_SPACE]) {
      app.keyboard[SDL_SCANCODE_SPACE] = false;
      break;
    }

    draw_rank();
  }
}
static void draw_rank() {
  clear();
  FILE *RankList;
  Rank rank[5];
  init_rank(rank);
  RankList = fopen("./RankList.txt", "r+");
  if (RankList == NULL) { HANDLE_ERROR("Get RankList") }
  for (int i = 0; i < 5; ++i) {
    char str[25];
    fscanf(RankList, "%15s %d", rank[i].name, &rank[i].score);
    sprintf(str, "%s             %d", rank[i].name, rank[i].score);
    blit_text("./res/font/pixel.ttf", str, WIDGET_X - 50, 300 + WIDGET_Y_GAP * i, SIZE, black);
  }
  blit_text("./res/font/pixel.ttf", "Rank", WIDGET_X - 20, 100, 100, black);
  present();
  quit_rank(rank);
  fclose(RankList);
}
void init_rank(Rank *rk) {
  for (int i = 0; i < 5; ++i) {
    rk[i].score = 0;
    rk[i].name = calloc(15, sizeof(char));
  }
}
void quit_rank(Rank *rk) {
  for (int i = 0; i < 5; ++i) {
    rk[i].score = 0;
    free(rk[i].name);
  }
}