//
// Created by 13584 on 2024/1/9.
//

#ifndef PROJECT1_INCLUDE_COMMON_H_
#define PROJECT1_INCLUDE_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_keyboard.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mouse.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_events.h"

#define WINDOW_X 100
#define WINDOW_Y 100
#define WINDOW_W 640
#define WINDOW_H 800

#define HANDLE_ERROR(msg) printf(msg ":%s\n",SDL_GetError());\
exit(EXIT_FAILURE);

#define HANDLE_ERROR_IMAGE(msg) printf(msg ":%s\n",IMG_GetError());\
exit(EXIT_FAILURE);

#define HANDLE_ERROR_TEXT(msg) printf(msg ":%s\n",TTF_GetError());\
exit(EXIT_FAILURE);

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool *keyboard;
} App;

extern App app;
extern unsigned int start;
extern bool running;

#endif //PROJECT1_INCLUDE_COMMON_H_
