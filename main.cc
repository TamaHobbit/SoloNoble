#include <iostream>
using namespace std;

const char open = 'O';
const char knikker = 'X';
const char bestaatNiet = ' ';

char gaten[7][7];

#include "BordKengetal.h"

void printBord(){
  for( int y = 0; y < 7; ++y ){  
    for( int x = 0; x < 7; ++x ){
      cout << gaten[x][y];
    }
    cout << "\n";
  }
}

void beginSituatie(){
  for( int y = 0; y < 7; ++y ){  
    for( int x = 0; x < 7; ++x ){
      if( (x < 2 || x > 4) && (y < 2 || y > 4) ){
        gaten[x][y] = bestaatNiet;
      } else {
        gaten[x][y] = knikker;
      }
    }
  }
  gaten[3][3] = open;
}

enum richting {
  boven, rechts, onder, links
};

bool zetKan(int x, int y, richting springKant){
  switch( springKant ){
    case boven:
      return y > 1 && gaten[x][y-1] == knikker && gaten[x][y-2] == open;
    case rechts:
      return x < 6 && gaten[x+1][y] == knikker && gaten[x+2][y] == open;
    case onder:
      return y < 6 && gaten[x][y+1] == knikker && gaten[x][y+2] == open;
    case links:
      return x > 1 && gaten[x-1][y] == knikker && gaten[x-2][y] == open;
  }
}

void doeZet(int x, int y, richting springKant){
  gaten[x][y] = open;
  switch( springKant ){
    case boven:
      gaten[x][y-1] = open;
      gaten[x][y-2] = knikker;
      return;
    case rechts:
      gaten[x+1][y] = open;
      gaten[x+2][y] = knikker;
      return;
    case onder:
      gaten[x][y+1] = open;
      gaten[x][y+2] = knikker;
      return;
    case links:
      gaten[x-1][y] = open;
      gaten[x-2][y] = knikker;
      return;
  }
}

void zetTerug(int x, int y, richting springKant){
  gaten[x][y] = knikker;
  switch( springKant ){
    case boven:
      gaten[x][y-1] = knikker;
      gaten[x][y-2] = open;
      return;
    case rechts:
      gaten[x+1][y] = knikker;
      gaten[x+2][y] = open;
      return;
    case onder:
      gaten[x][y+1] = knikker;
      gaten[x][y+2] = open;
      return;
    case links:
      gaten[x-1][y] = knikker;
      gaten[x-2][y] = open;
      return;
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
    cout << "Kengetal: " << BordKengetal::encodeerBord() << endl;
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
