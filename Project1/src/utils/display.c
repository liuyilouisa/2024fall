//
// Created by 13584 on 2024/1/11.
//
#include "utils/display.h"
#include "common.h"

SDL_Color black;
SDL_Color white;
SDL_Texture *texture_player=NULL;
SDL_Texture *texture_rect_1=NULL;
SDL_Texture *texture_circle_1=NULL;
SDL_Texture *texture_pointer=NULL;
SDL_Texture *texture_title=NULL;
SDL_Texture *texture_circle_2=NULL;
SDL_Texture *texture_rect_2=NULL;
SDL_Texture *texture_circle_music=NULL;
SDL_Texture *texture_circle_alter=NULL;
SDL_Texture *texture_bg_alter=NULL;


void clear(){
  SDL_SetRenderDrawColor(app.renderer,0xff,0xff,0xff,0xff);
  SDL_RenderClear(app.renderer);
}

void init_display(){
  app.window = SDL_CreateWindow("I wanna 跳一跳",WINDOW_X,WINDOW_Y,WINDOW_W,WINDOW_H,SDL_WINDOW_SHOWN);
  app.renderer = SDL_CreateRenderer(app.window,-1,SDL_RENDERER_ACCELERATED);
  black =(SDL_Color){0,0,0,0};
  white =(SDL_Color){0xff,0xff,0xff,0xff};
  texture_player= IMG_LoadTexture(app.renderer,"./res/image/player.jpg");
  texture_rect_1= IMG_LoadTexture(app.renderer,"./res/image/rect_1.jpg");
  texture_circle_1= IMG_LoadTexture(app.renderer,"./res/image/circle_1.jpg");
  texture_pointer= IMG_LoadTexture(app.renderer,"./res/image/pointer.jpg");
  texture_title= IMG_LoadTexture(app.renderer,"./res/image/title.jpg");
  texture_circle_2= IMG_LoadTexture(app.renderer,"./res/image/circle_2.jpg");
  texture_rect_2= IMG_LoadTexture(app.renderer,"./res/image/rect_2.jpg");
  texture_circle_music= IMG_LoadTexture(app.renderer,"./res/image/circle_music.jpg");
  texture_circle_alter= IMG_LoadTexture(app.renderer,"./res/image/circle_alter.jpg");
  texture_bg_alter = IMG_LoadTexture(app.renderer,"./res/image/background_alter.jpg");

  SDL_QueryTexture(texture_player, NULL, NULL, &rect_player.w, &rect_player.h);

}
void quit_display(){
  SDL_DestroyWindow(app.window);
  SDL_DestroyRenderer(app.renderer);
  SDL_DestroyTexture(texture_title);
  SDL_DestroyTexture(texture_player);
  SDL_DestroyTexture(texture_rect_1);
  SDL_DestroyTexture(texture_pointer);
  SDL_DestroyTexture(texture_circle_2);
  SDL_DestroyTexture(texture_rect_2);
  SDL_DestroyTexture(texture_circle_1);
  SDL_DestroyTexture(texture_circle_music);
  SDL_DestroyTexture(texture_circle_alter);
  SDL_DestroyTexture(texture_bg_alter);

  SDL_DestroyTexture(this_block.texture_block);
  SDL_DestroyTexture(next_block.texture_block);
  SDL_DestroyTexture(last_block.texture_block);
}

void present() {
  SDL_RenderPresent(app.renderer);
}

void blit_image(SDL_Texture *texture, int x, int y) {
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
  SDL_RenderCopy(app.renderer, texture, NULL, &rect);
}

void blit_player(int x,int y){
  rect_player.x=x;
  rect_player.y=y;
  SDL_RenderCopy(app.renderer,texture_player,NULL,&rect_player);
}

void blit_text(const char *file, const char *text, int x, int y, int size, SDL_Color color) {
  TTF_Font *font = NULL;
  font = TTF_OpenFont(file, size);
  if (font == NULL) { HANDLE_ERROR_TEXT("Get File") }
  SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(app.renderer, surface);
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
  SDL_RenderCopy(app.renderer, texture, NULL, &rect);

  TTF_CloseFont(font);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}
