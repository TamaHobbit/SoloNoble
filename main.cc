#include <iostream>
using namespace std;

const char open = 'O';
const char knikker = 'X';
const char bestaatNiet = ' ';

char gaten[7][7];

#include "BordKengetal.h"
#include "Spelen.h"
#include "DynProgrammeren.h"

//deze worden Interface.h

void printBord(){
  for( int y = 0; y < 7; ++y ){  
    for( int x = 0; x < 7; ++x ){
      cout << gaten[x][y];
    }
    cout << "\n";
  }
}



int main(){
  
  cout << endl << "Speel door bijvoorbeeld \"3 1 onder\" [enter] in te toetsen. Dat is ook een geldige eerste zet." << endl;
  cout << "Richtingen heten boven, rechts, onder, links" << endl << endl;

  beginSituatie();
  
  //de invoer variabelen
  int xInvoer, yInvoer;
  string richtingInvoer;
  richting echteRichting;
  
  while( !cin.eof() ){
    printBord();
    cout << "Kengetal: " << encodeerBord() << endl;
    cout << "Mogelijke zetten: " << endl;
    
    list<tuple<int,int,richting>> mogelijkheden = alleMogelijkeZetten();
    for( mogelijkeZet it = mogelijkheden.begin(); it != mogelijkheden.end(); ++it ){
      cout << get<0>(*it) << " " << get<1>(*it) << endl;
    }

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
  return 0;
}
