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
  
  //de invoer variabelen
  int xInvoer, yInvoer;
  string richtingInvoer;
  richting echteRichting;
  
  while( !cin.eof() && !gewonnen() ){
    toonSituatie();

    cin >> xInvoer;
    cin >> yInvoer;
    cin >> richtingInvoer;
    
    if( richtingInvoer == "boven" ){
      echteRichting = boven;
    } else if( richtingInvoer == "rechts" ){
      echteRichting = rechts;
    } else if( richtingInvoer == "onder" ){
      echteRichting = onder;
    } else if( richtingInvoer == "links" ){
      echteRichting = links;
    } else {
      cout << "Ongeldige richting; Richtingen heten boven, rechts, onder, links" << endl;
    }

    if( zetKan( xInvoer, yInvoer, echteRichting ) ){
      doeZet( xInvoer, yInvoer, echteRichting );
    } else {
      cout << endl << "Dat kan niet." << endl;
    }
  }
  //todo ook stoppen als er geen zetten meer mogelijk zijn, 
  //zodat je niet het programma hoeft te force quitten
  cout << "Je hebt gewonnen!" << endl; 
  return 0;
}
