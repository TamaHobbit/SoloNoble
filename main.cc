#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <list>
#include <tuple>
#include <stack>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
using namespace std;

const char open = 'O';
const char knikker = 'X';
const char bestaatNiet = ' ';

char gaten[7][7];

#include "BordKengetal.h"
#include "Spelen.h"
#include "DynProgrammeren.h"
#include "Interface.h"
#include "TwoClickOrDrag.h"
#include "SDLscherm.h"

int main(){

  beginSituatie();

  //SDLscherm scherm;
  //scherm.Run();

  IsSolveable();
  
  return 0;
}
