
#include <unordered_map>
#include <list>
#include <tuple>
#include <stack>

typedef unordered_map<bordKengetal,bool> hashTabel;
typedef unordered_map<bordKengetal,bool>::iterator stellingsInformatie;

hashTabel alleKennis;

stack<tuple<int,int,richting>> huidigePad;

list<tuple<int,int,richting>> alleMogelijkeZetten(){
  list<tuple<int,int,richting>> gevondenZetten;
  for( int y = 0; y < 7; ++y ){  
    for( int x = 0; x < 7; ++x ){
      if( gaten[x][y] == open ){
        if( y > 1 && gaten[x][y-1] == knikker && gaten[x][y-2] == knikker ){
          gevondenZetten.push_front( make_tuple( x, y-2, onder ) );
        }
        if( x < 5 && gaten[x+1][y] == knikker && gaten[x+2][y] == knikker ){
          gevondenZetten.push_front( make_tuple( x+2, y, links ) );
        }
        if( y < 5 && gaten[x][y+1] == knikker && gaten[x][y+2] == knikker ){
          gevondenZetten.push_front( make_tuple( x, y+2, boven ) );
        }
        if( x > 1 && gaten[x-1][y] == knikker && gaten[x-2][y] == knikker ){
          gevondenZetten.push_front( make_tuple( x-2, y, rechts ) );
        }
      }
    }
  }
  return gevondenZetten;
}

void doeVoorMogelijkeZetten(std::function<void(int,int,richting)> todo){
  for( int y = 0; y < 7; ++y ){  
    for( int x = 0; x < 7; ++x ){
      if( gaten[x][y] == open ){
        if( y > 1 && gaten[x][y-1] == knikker && gaten[x][y-2] == knikker ){
          todo( x, y-2, onder );
        }
        if( x < 5 && gaten[x+1][y] == knikker && gaten[x+2][y] == knikker ){
          todo( x+2, y, links );
        }
        if( y < 5 && gaten[x][y+1] == knikker && gaten[x][y+2] == knikker ){
          todo( x, y+2, boven );
        }
        if( x > 1 && gaten[x-1][y] == knikker && gaten[x-2][y] == knikker ){
          todo( x-2, y, rechts );
        }
      }
    }
  }
}

// Kijkt recursief (met Depth-first search) of de stelling nog te winnen valt door 
// steeds een zet te doen, zichzelf aan te roepen, en dan de zet terug te doen
// elke stelling hoeft maar 1 keer worden bekeken (of een punt- of lijnsymmetrishe )
void stellingTeRedden(){
  bordKengetal huidigeOpstelling = encodeerBord();

  stellingsInformatie alBekend = alleKennis.find ( huidigeOpstelling );
  if( alBekend != alleKennis.end() ){ //gevonden in de map, dus al geweest
    return;
  }

  if( gewonnen() ){
    throw true;
  }

  doeVoorMogelijkeZetten([] (int x, int y, richting r){
    doeZet( x, y, r );
    huidigePad.push( make_tuple(x,y,r) );

    // recursie
    stellingTeRedden();

    zetTerug( x, y, r );
    huidigePad.pop();
  });
}

