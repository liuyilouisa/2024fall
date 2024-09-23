//
// Created by 13584 on 2024/1/9.
//
#include "main.h"
#include "menu.h"
#include "utils/audio.h"
#include "utils/display.h"

App app;
unsigned int start;
bool running;

int main(int argc,char *argv[]){
  start= 0;
  running = false;
  init_app();
  init_display();
  init_audio();
  init_keyboard();

  atexit(&quit_app);
  atexit(&quit_display);
  atexit(&quit_audio);
  atexit(&quit_keyboard);

  startup();
  do_menu_logic();

  return 0;
}

static void init_app(){
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0){
    HANDLE_ERROR("Init SDL")
  }
  if (!IMG_Init(IMG_INIT_JPG)){
    HANDLE_ERROR("Init Image")
  }
  if (!Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG)){
    HANDLE_ERROR("Init Mixer")
  }
  if (TTF_Init()== -1){
    HANDLE_ERROR("Init TTF")
  }
}
static void quit_app(){
  SDL_Quit();
  IMG_Quit();
  Mix_Quit();
  TTF_Quit();
}

static void init_audio(){
  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,2048);
}
static void quit_audio(){
  Mix_CloseAudio();
}
static void init_keyboard(){
  app.keyboard= calloc(SDL_NUM_SCANCODES,sizeof(bool));
}
static void quit_keyboard(){
  free(app.keyboard);
}

static void startup(){
  clear();
}
