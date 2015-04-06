#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int resolution_X = 1024, resolution_Y = 1024;

void runSDL(){
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);

  SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resolution_X, resolution_Y, 0);
  if (window == NULL){
    SDL_ShowSimpleMessageBox(0, "Window init error", SDL_GetError(), window);
  }    
  SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
  if (renderer == NULL){
    SDL_ShowSimpleMessageBox(0, "Renderer init error", SDL_GetError(), window);
  }
  SDL_Surface * image = IMG_Load("gfx/board-empty.jpg");
  if (image == NULL){ 
    SDL_ShowSimpleMessageBox(0, "Image init error", SDL_GetError(), window);
  }
  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
  if (texture == NULL){
    SDL_ShowSimpleMessageBox(0, "Texture init error", SDL_GetError(), window);
  }

  bool quit = false;
  SDL_Event event;

  while (!quit){
     SDL_WaitEvent(&event);
     switch(event.type)
     {
     case SDL_QUIT:
         quit = true;
         break;
     }
     SDL_RenderCopy(renderer, texture, NULL, NULL);
     SDL_RenderPresent(renderer);
  }        

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(image);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  IMG_Quit();
  SDL_Quit();
}