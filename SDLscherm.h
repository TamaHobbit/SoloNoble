const int resolution_X = 1024, resolution_Y = 1024;

class SDLscherm {
public:

  std::atomic<bool> canStillWin { true };
  std::atomic<bool> isCalculating { false };

  std::condition_variable gamestateChangedCondition;
  std::thread calculate_thread;
  std::mutex gamestate_mutex;

  std::condition_variable calculationFinishedCondition;
  std::thread display_thread;

  //std::future<bool> calculate_future;

  SDLscherm() : calculate_thread(&SDLscherm::CalculatingThread, this), clickState(*this) {
    InitSDL();
    InitPictures();
  }

  void Run(){
    bool quit = false;
    SDL_Event event;

    UpdateDisplay();
    while (!quit) {
      SDL_WaitEvent(&event);
      switch(event.type) {
        case SDLK_ESCAPE:
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_MOUSEBUTTONDOWN:
          clickState.MouseDown(FindPinForPosition(std::make_pair(event.button.x, event.button.y)));
          break;
        case SDL_MOUSEBUTTONUP:
          clickState.MouseUp(FindPinForPosition(std::make_pair(event.button.x, event.button.y)));
          break;
      }
      SDL_RenderPresent(renderer);
    }
  }

  void CalculatingThread(){
    while(true){
      std::unique_lock<std::mutex> lk(gamestate_mutex);
      gamestateChangedCondition.wait( lk,[this]{
        return isCalculating.load();
      } );
      const bool calcResult = IsSolveable();
      lk.unlock();
      canStillWin = calcResult;
      isCalculating = false;
    }
  }

  void UpdateDisplay(){
    SDL_RenderCopy(renderer, boardTexture, nullptr, nullptr);
    if( isCalculating ){
      DisplayTick(processingTexture);
    } else if( canStillWin ){
      DisplayTick( tickTexture );
    } else {
      DisplayTick( crossTexture );
    }
    DisplayPins();
  }

  void DisplayPins(){
    //std::unique_lock<std::mutex> lk(gamestate_mutex);
    for( int y = 0; y < 7; ++y ){  
      for( int x = 0; x < 7; ++x ){
        if( gaten[x][y] == knikker ){
          auto location = GetScreenLocationForHole(x, y);
          ApplySurface(location.first, location.second, pinTexture);
        }
      }
    }
  }

  void DisplayTick(SDL_Texture * tickTexture){
    ApplySurface(750, 150, tickTexture);
  }

  std::pair<int,int> FindPinForPosition(std::pair<int,int> mousePosition){
    auto pins = std::make_pair((mousePosition.first-squareStartPosX)/clickSquareSizeX, (mousePosition.second-squareStartPosY)/clickSquareSizeY);
    //printf("Position %i, %i maps to %i, %i\n", mousePosition.first, mousePosition.second, pins.first, pins.second);
    return pins;
  }

  bool ownPiece(std::pair<int,int> mouseTile){
    if( !onBoard(mouseTile) ){
      return false;
    }
    return gaten[mouseTile.first][mouseTile.second] == knikker;
  }

  void select(std::pair<int,int> mouseTile){}
  void deselect(){}

  bool validMove(std::pair<int,int> from, std::pair<int,int> to){
    //printf("Checking move: %i, %i to %i, %i\n", from.first, from.second, to.first, to.second);
    if( !onBoard(from) || !onBoard(to) ){
      return false;
    }
    return zetKan(from.first, from.second, to.first, to.second);
  }

  bool onBoard(std::pair<int,int> tileIndex){
    return tileIndex.first >= 0 && tileIndex.first < 7 && tileIndex.second >= 0 && tileIndex.second < 7;
  }

  void makeMove(std::pair<int,int> from, std::pair<int,int> to){
    std::unique_lock<std::mutex> lk(gamestate_mutex);
    //printf("Doing move: %i, %i to %i, %i\n", from.first, from.second, to.first, to.second);
    doeZet(from.first, from.second, to.first, to.second);
    isCalculating = true;
    UpdateDisplay();
    lk.unlock();
    gamestateChangedCondition.notify_one();
  }

  ~SDLscherm(){
    isCalculating = false;

    CleanUp(boardTexture);
    CleanUp(pinTexture);
    CleanUp(tickTexture);
    CleanUp(crossTexture);
    CleanUp(processingTexture);
    CleanUp(renderer);
    CleanUp(window);

    IMG_Quit();
    SDL_Quit();

    if( calculate_thread.joinable() ){
      calculate_thread.join();
    }
    if( display_thread.joinable() ){
      display_thread.join();
    }
  }

private:
  const int clickSquareSizeX = 127;
  const int squareStartPosX = 56;
  const int clickSquareSizeY = 125;
  const int squareStartPosY = 54;

  SDL_Window * window { nullptr };
  SDL_Renderer * renderer { nullptr };

  SDL_Texture * boardTexture { nullptr };
  SDL_Texture * pinTexture { nullptr };
  SDL_Texture * tickTexture { nullptr };
  SDL_Texture * crossTexture { nullptr };
  SDL_Texture * processingTexture { nullptr };

  TwoClickOrDrag<SDLscherm> clickState;

  const std::map<std::pair<int,int>,std::pair<int,int>> holeToPositionMap {
    { std::pair<int,int>(2,0), std::pair<int,int>(370,96) }, // (x,y) position -> (xPixels, yPixels)
    { std::pair<int,int>(3,0), std::pair<int,int>(496,97) },
    { std::pair<int,int>(4,0), std::pair<int,int>(626,98) },
    { std::pair<int,int>(2,1), std::pair<int,int>(366,226) },
    { std::pair<int,int>(3,1), std::pair<int,int>(495,225) },
    { std::pair<int,int>(4,1), std::pair<int,int>(622,224) },
    { std::pair<int,int>(0,2), std::pair<int,int>(112,356) },
    { std::pair<int,int>(1,2), std::pair<int,int>(239,354) },
    { std::pair<int,int>(2,2), std::pair<int,int>(366,352) },
    { std::pair<int,int>(3,2), std::pair<int,int>(493,350) },
    { std::pair<int,int>(4,2), std::pair<int,int>(625,348) },
    { std::pair<int,int>(5,2), std::pair<int,int>(751,350) },
    { std::pair<int,int>(6,2), std::pair<int,int>(877,350) },
    { std::pair<int,int>(0,3), std::pair<int,int>(111,483) },
    { std::pair<int,int>(1,3), std::pair<int,int>(236,484) },
    { std::pair<int,int>(2,3), std::pair<int,int>(364,483) },
    { std::pair<int,int>(4,3), std::pair<int,int>(624,479) },
    { std::pair<int,int>(5,3), std::pair<int,int>(750,478) },
    { std::pair<int,int>(6,3), std::pair<int,int>(877,473) },
    { std::pair<int,int>(0,4), std::pair<int,int>(115,604) },
    { std::pair<int,int>(1,4), std::pair<int,int>(239,606) },
    { std::pair<int,int>(2,4), std::pair<int,int>(368,605) },
    { std::pair<int,int>(3,4), std::pair<int,int>(495,604) },
    { std::pair<int,int>(4,4), std::pair<int,int>(620,604) },
    { std::pair<int,int>(5,4), std::pair<int,int>(750,605) },
    { std::pair<int,int>(6,4), std::pair<int,int>(876,606) },
    { std::pair<int,int>(2,5), std::pair<int,int>(363,737) },
    { std::pair<int,int>(3,5), std::pair<int,int>(493,737) },
    { std::pair<int,int>(4,5), std::pair<int,int>(620,737) },
    { std::pair<int,int>(2,6), std::pair<int,int>(367,862) },
    { std::pair<int,int>(3,6), std::pair<int,int>(490,864) },
    { std::pair<int,int>(4,6), std::pair<int,int>(621,862) },
    { std::pair<int,int>(3,3), std::pair<int,int>(496,480) } //middle pin
  };

  std::pair<int,int> GetScreenLocationForHole(int xPos, int yPos){
    //return std::pair<int, int>(xPos*127 + 112, yPos*125 + 108 - xPos*2); //approximation
    return holeToPositionMap.at(std::pair<int,int>(xPos,yPos));
  }

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
    LoadImage("gfx/board-empty.jpg", boardTexture);
    LoadImage("gfx/pin.gif", pinTexture);
    LoadImage("gfx/tick.gif", tickTexture);
    LoadImage("gfx/cross.gif", crossTexture);
    LoadImage("gfx/processing.gif", processingTexture);
  }

  void LoadImage(std::string filename, SDL_Texture *& textureptr){
    SDL_Surface * imageptr = IMG_Load(filename.c_str());
    if (imageptr == nullptr){ 
      SDL_ShowSimpleMessageBox(0, "Image init error", SDL_GetError(), window);
      return;
    }
    textureptr = SDL_CreateTextureFromSurface(renderer, imageptr);
    if (textureptr == nullptr){
      SDL_ShowSimpleMessageBox(0, "Texture init error", SDL_GetError(), window);
    }
  }

  void ApplySurface(const int x, const int y, SDL_Texture * source) {
    int w, h;
    SDL_QueryTexture(source, NULL, NULL, &w, &h);
    SDL_Rect offset {x, y, w, h};
    SDL_RenderCopy( renderer, source, nullptr, &offset );
  }

  void CleanUp(SDL_Texture * texture){
    if( texture != nullptr ){
      SDL_DestroyTexture(texture);
    }
  }

  void CleanUp(SDL_Renderer * renderer){
    if( renderer != nullptr ){
      SDL_DestroyRenderer(renderer);
    }
  }

  void CleanUp(SDL_Window * window){
    if( window != nullptr){
      SDL_DestroyWindow(window);
    }
  }
};
