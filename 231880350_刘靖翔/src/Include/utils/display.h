//
// Created by 13584 on 2024/1/11.
//

#ifndef PROJECT1_INCLUDE_UTILS_DISPLAY_H_
#define PROJECT1_INCLUDE_UTILS_DISPLAY_H_

#include "common.h"
#include "game/game.h"
#include "game/block.h"

#define FPS 90
#define FRAME_LENTH (1000/FPS)

extern SDL_Color black;
extern SDL_Color white;
extern SDL_Texture *texture_player;
extern SDL_Texture *texture_rect_1;
extern SDL_Texture *texture_circle_1;
extern SDL_Texture *texture_pointer;
extern SDL_Texture *texture_title;
extern SDL_Texture *texture_rect_2;
extern SDL_Texture *texture_circle_2;
extern SDL_Texture *texture_circle_music;
extern SDL_Texture *texture_circle_alter;
extern SDL_Texture *texture_bg_alter;

void clear();

void init_display();
void quit_display();

void present();

void blit_image(SDL_Texture *texture,int x, int y);
void blit_player(int x,int y);
void blit_text(const char *file,const char *text,int x,int y,int size,SDL_Color color);

#endif //PROJECT1_INCLUDE_UTILS_DISPLAY_H_
