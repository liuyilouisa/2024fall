//
// Created by 13584 on 2024/1/11.
//

#ifndef PROJECT1_INCLUDE_UTILS_INPUT_H_
#define PROJECT1_INCLUDE_UTILS_INPUT_H_

#include "common.h"

void do_event(SDL_Event event);
static void do_keydown(SDL_KeyboardEvent key);
static void do_keyup(SDL_KeyboardEvent key);
static void do_quit(SDL_QuitEvent quit);
static void do_mousedown(SDL_MouseButtonEvent button);
static void do_mouseup(SDL_MouseButtonEvent button);
void clear_keyboard();

#endif //PROJECT1_INCLUDE_UTILS_INPUT_H_
