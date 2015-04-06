#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int resolution_X = 1024, resolution_Y = 1024;

class SDLscherm {
public:

  SDLscherm(){
    InitSDL();
    InitPictures();
  }

  void Run(){
    bool quit = false;
    SDL_Event event;

    while (!quit) {
      SDL_WaitEvent(&event);
      switch(event.type) {
      case SDL_QUIT:
         quit = true;
         break;
      }
      SDL_RenderCopy(renderer, boardTexture, nullptr, nullptr);
      SDL_RenderPresent(renderer);
    }
  }

  ~SDLscherm(){
    if( boardTexture != nullptr ){
      SDL_DestroyTexture(boardTexture);
    }
    if( boardImage != nullptr ){
      SDL_FreeSurface(boardImage);
    }
    if( renderer != nullptr ){
      SDL_DestroyRenderer(renderer);
    }
    if( window != nullptr){
      SDL_DestroyWindow(window);
    }

    IMG_Quit();
    SDL_Quit();
  }

private:
  SDL_Window * window { nullptr };
  SDL_Renderer * renderer { nullptr };

  SDL_Surface * boardImage { nullptr };
  SDL_Texture * boardTexture { nullptr };

  void InitSDL(){
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow("SDL2 Displaying Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resolution_X, resolution_Y, 0);
    if (window == nullptr){
      SDL_ShowSimpleMessageBox(0, "Window init error", SDL_GetError(), window);
    }    
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr){
      SDL_ShowSimpleMessageBox(0, "Renderer init error", SDL_GetError(), window);
    }
  }

  void InitPictures(){
    LoadImage("gfx/board-empty.jpg", boardImage, boardTexture);
  }

  void LoadImage(std::string filename, SDL_Surface *& imageptr, SDL_Texture *& textureptr){
    imageptr = IMG_Load(filename.c_str());
    if (imageptr == nullptr){ 
      SDL_ShowSimpleMessageBox(0, "Image init error", SDL_GetError(), window);
      return;
    }
    textureptr = SDL_CreateTextureFromSurface(renderer, imageptr);
    if (textureptr == nullptr){
      SDL_ShowSimpleMessageBox(0, "Texture init error", SDL_GetError(), window);
    }
  }
};
