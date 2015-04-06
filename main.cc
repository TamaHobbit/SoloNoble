#include <iostream>
using namespace std;

const char open = 'O';
const char knikker = 'X';
const char bestaatNiet = ' ';

char gaten[7][7];

#include "BordKengetal.h"
#include "Spelen.h"
#include "DynProgrammeren.h"
#include "Interface.h"
#include "SDLscherm.h"

int main(){

  beginSituatie();
  
  //SpelerMagSpelen();

  //LosMaarOp();

  SDLscherm scherm;
  scherm.Run();
  
  return 0;
}
