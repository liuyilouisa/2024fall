//
// Created by 13584 on 2024/1/11.
//
#include "utils/input.h"
#include "common.h"

void do_event(SDL_Event event) {
  switch (event.type) {
    case SDL_QUIT:do_quit(event.quit);
      return;
    case SDL_KEYDOWN:do_keydown(event.key);
      break;
    case SDL_KEYUP:do_keyup(event.key);
      break;
    case SDL_MOUSEBUTTONDOWN:do_mousedown(event.button);
      break;
    case SDL_MOUSEBUTTONUP:do_mouseup(event.button);
      break;
    default:break;
  }
}

static void do_keydown(SDL_KeyboardEvent key){
  app.keyboard[key.keysym.scancode] = true;
}

static void do_keyup(SDL_KeyboardEvent key){
  app.keyboard[key.keysym.scancode] = false;
}

static void do_quit(SDL_QuitEvent quit){
  app.keyboard[SDL_SCANCODE_ESCAPE] = true;
}

static void do_mousedown(SDL_MouseButtonEvent button){
  printf("mouse at:%d,%d\n",button.x,button.y);
}

static void do_mouseup(SDL_MouseButtonEvent button){

}

void clear_keyboard(){
  for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
    app.keyboard[i]=false;
  }
}