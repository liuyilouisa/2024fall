//
// Created by 13584 on 2024/1/12.
//
#include "game/game.h"
#include "utils/input.h"
#include "utils/display.h"
#include "game/player.h"
#include "game/block.h"

static Player player;

int block_gap;
int count;
int level;

Mix_Music *M1;
Mix_Music *M2;
Mix_Chunk *gg;

bool redirection;
bool jump;
bool survive;
bool move;
bool new_record;
bool music;
int alter;

void do_game_logic() {
  survive = true;
  redirection = false;
  move = false;
  music = false;
  alter = 0;
  level = 0;

  M1 = Mix_LoadMUS("./res/sound/circle_music.mp3");
  M2 = Mix_LoadMUS("./res/sound/alter.mp3");

  init_player(&player);

  init_block();

  count = 0;

  while (!app.keyboard[SDL_SCANCODE_ESCAPE] && survive) {
    do_game_input();
    do_player(&player);
    if (jump) {
      check_player();
      if (redirection) {
        if (music) {
          Mix_HaltMusic();
          music = false;
        }
        if(next_block.texture_block==texture_circle_alter)alter++;
        if (!(alter%2)) {
          Mix_HaltMusic();
          black = (SDL_Color) {0, 0, 0, 0};
        }
//        printf("gap:%d jump_l:%d\n", block_gap, (int) jump_lenth);
        draw_back((int) jump_lenth, &player);
        shift_block();
        generate_block(block_gap);
        count++;
        if (this_block.texture_block == texture_circle_music && !music && !alter) {
          Mix_PlayMusic(M1, 0);
          music = true;
        }
        if (alter % 2) {
          black = white;
          Mix_PlayMusic(M2, 0);
        }
        if (this_block.texture_block == texture_rect_2 || this_block.texture_block == texture_circle_2) {
          count *= 1.5;
        }
      }
      jump = false;
    }
    do_draw_game();
    do_fps();
  }
  Mix_FreeMusic(M1);
  Mix_FreeMusic(M2);
  if (alter) {
    black = (SDL_Color) {0, 0, 0, 0};
    alter = false;
  }
  do_game_over();

  clear();
}

static void do_game_over() {
  SDL_Event event;
  do_ranklist();
  draw_game_over();
  while (!app.keyboard[SDL_SCANCODE_ESCAPE] && SDL_WaitEvent(&event)) {
    do_event(event);

    draw_game_over();

    if (app.keyboard[SDL_SCANCODE_SPACE]) {
      app.keyboard[SDL_SCANCODE_SPACE] = false;
      break;
    }
  }
  Mix_FreeChunk(gg);
}

static void draw_game_over() {
  clear();
  char buf[35];
  if (new_record) {
    sprintf(buf, "New record: %u", count);
    blit_text("./res/font/pixel.ttf", buf, 100, 250, 64, black);
  } else {
    sprintf(buf, "Score: %u", count);
    blit_text("./res/font/pixel.ttf", buf, 150, 250, 64, black);
  }
  blit_text("./res/font/pixel.ttf", "Game over.", 125, 150, 80, black);
  blit_text("./res/font/pixel.ttf", "Press space to continue.", 80, 550, 40, black);
  present();
}

static void do_ranklist() {
  new_record = false;
  Rank rank[5];
  init_rank(rank);
  FILE *RankList;
  RankList = fopen("./RankList.txt", "r+");
  if (RankList == NULL) { HANDLE_ERROR("Get RankList") }
  for (int i = 0; i < 5; ++i) {
    fscanf(RankList, "%15s %15d", rank[i].name, &rank[i].score);
  }
  for (int i = 0; i < 5; ++i) {
    if (count > rank[i].score) {
      new_record = true;
      for (int j = 4; j >= i + 1; --j) {
        rank[j].score = rank[j - 1].score;
      }
      rank[i].score = count;
      break;
    }
  }
  fseek(RankList, 0, SEEK_SET);
  for (int i = 0; i < 5; ++i) {
    fprintf(RankList, "%s %d\n", rank[i].name, rank[i].score);
  }
  fclose(RankList);
  quit_rank(rank);
}

static void do_game_input() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    do_event(event);
  }
}

void do_draw_game() {
  if (alter%2) {
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
    SDL_RenderClear(app.renderer);
    blit_image(texture_bg_alter, 0, 0);
  } else {
    clear();
  }
  if (count > 0 && !move) { blit_image(last_block.texture_block, (int) last_block.x, (int) last_block.y); }
  blit_image(this_block.texture_block, (int) this_block.x, (int) this_block.y);
  blit_image(next_block.texture_block, (int) next_block.x, (int) next_block.y);
  blit_player((int) player.x, (int) player.y);
  char buf[16];
  sprintf(buf, "Score: %u", count);
  blit_text("./res/font/pixel.ttf", buf, 10, 10, 64, black);
  present();
}

static void init_block() {
  this_block.x = BLOCK_INIT_X;
  this_block.y = BLOCK_INIT_Y;
  this_block.center = (Center) {BLOCK_INIT_CX, BLOCK_INIT_CY};
  this_block.texture_block = texture_rect_1;
  this_block.r = R;

  next_block.texture_block = texture_circle_1;
  next_block.x = this_block.x + 200;
  next_block.y = this_block.y - 80;
  next_block.center.x = this_block.center.x + 200;
  next_block.center.y = this_block.center.y - 80;
  next_block.r = R;

  block_gap = 200;
}

static void draw_back(int gap, Player *p) {
  for (int i = gap; i > 0; --i) {
    this_block.x--;
    this_block.y += 0.4;
    this_block.center.x--;
    this_block.center.y += 0.4;
    next_block.x--;
    next_block.y += 0.4;
    next_block.center.x--;
    next_block.center.y += 0.4;
    p->x--;
    p->y += 0.4;
    move = true;
    do_draw_game();
    move = false;
  }
}

static void shift_block() {
  last_block.texture_block = this_block.texture_block;
  this_block.texture_block = next_block.texture_block;
  last_block.x = this_block.x;
  last_block.y = this_block.y;
  this_block.x = next_block.x;
  this_block.y = next_block.y;
  this_block.center.x = next_block.center.x;
  this_block.center.y = next_block.center.y;
  this_block.r = next_block.r;
}

static void generate_block(double gap) {
  srand(SDL_GetTicks());

  gap = rand() % 70 + BLOCK_W;

  next_block.x = this_block.x + gap;
  next_block.y = this_block.y - gap * 0.4;
  next_block.center.x = this_block.center.x + gap;
  next_block.center.y = this_block.center.y + gap * 0.4;
//
//  printf("this:%f,%f; ", this_block.x, this_block.y);
//  printf("next:%f,%f; ", next_block.x, next_block.y);
//  printf("last:%f,%f\n", last_block.x, last_block.y);

  int rad = rand() % 100;
  if (count > 2 && count < 20)level = 1;
  if (count > 20 && count < 100)level = 2;
  if (count > 100)level = 3;
  switch (level) {
    case 0:
      if (rad < 50) {
        next_block.texture_block = texture_circle_1;
        next_block.r = R;
      } else {
        next_block.texture_block = texture_rect_1;
        next_block.r = R;
      }
      break;
    case 1:
      if (rad < 20) {
        next_block.texture_block = texture_rect_1;
        next_block.r = R;
      } else if (rad < 40) {
        next_block.texture_block = texture_circle_1;
        next_block.r = R;
      } else if (rad < 60) {
        next_block.texture_block = texture_rect_2;
        next_block.r = R - 15;
      } else if (rad < 80) {
        next_block.texture_block = texture_circle_2;
        next_block.r = R - 15;
      } else if (rad < 90) {
        next_block.texture_block = texture_circle_music;
        next_block.r = R;
      } else {
        next_block.texture_block = texture_circle_alter;
        next_block.r = R;
      }
      break;
    case 2:
      if (rad < 10) {
        next_block.texture_block = texture_rect_1;
        next_block.r = R;
      } else if (rad < 20) {
        next_block.texture_block = texture_circle_1;
        next_block.r = R;
      } else if (rad < 50) {
        next_block.texture_block = texture_rect_2;
        next_block.r = R - 15;
      } else if (rad < 80) {
        next_block.texture_block = texture_circle_2;
        next_block.r = R - 15;
      } else if (rad < 90) {
        next_block.texture_block = texture_circle_music;
        next_block.r = R;
      } else {
        next_block.texture_block = texture_circle_alter;
        next_block.r = R;
      }
    case 3:
      if (rad < 30) {
        next_block.texture_block = texture_rect_2;
        next_block.r = R - 15;
      } else if (rad < 60) {
        next_block.texture_block = texture_circle_2;
        next_block.r = R - 15;
      } else if (rad < 80) {
        next_block.texture_block = texture_circle_music;
        next_block.r = R;
      } else{
        next_block.texture_block = texture_circle_alter;
        next_block.r = R;
      }
      break;
    default:HANDLE_ERROR("level")
  }

}

static void check_player() {
  if (((player.x + PLAYER_W) >= (next_block.center.x - next_block.r + 5))
      && (player.x <= (next_block.center.x + next_block.r + 5))) {
    redirection = true;
//    printf("in next_block ");
    if (((player.x + PLAYER_W) >= (next_block.center.x - 5))
        && (player.x <= (next_block.center.x + 15))) {
      count++;
    }
    return;
  } else if (((player.x + PLAYER_W) >= (this_block.center.x - this_block.r))
      && (player.x <= (this_block.center.x + this_block.r))) {
    redirection = false;
//    printf("in this_block ");
    return;
  } else {
    survive = false;
    redirection = false;
    gg = Mix_LoadWAV("./res/sound/gg.mp3");
    Mix_PlayChannel(-1, gg, 0);
    return;
  }
}

static void do_fps() {
  SDL_Delay(FRAME_LENTH);
}
