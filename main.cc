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



int main(){
  
  beginInstructies();

  beginSituatie();
  
  //SpelerMagSpelen();
  if( stellingTeRedden() ){
    while (!huidigePad.empty()){
      toonZet( huidigePad.top() );
      huidigePad.pop();
    }
  } else {
    cout << "Dit spel is onmogelijk te winnen." << endl;
  }
  
  return 0;
}
