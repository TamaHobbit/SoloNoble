
#include <unordered_set>
#include <list>
#include <tuple>
#include <stack>

unordered_set<bordKengetal> alleKennis;
stack<tuple<int,int,richting>> huidigePad;

// Voor alle lege gaten, kijk of daarnaast twee knikkers op een rij zitten
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
// "throw true" als de oplossing is gevonden, zodat huidigePad nog steeds de zetten bevat
void stellingTeRedden(){
  // encodeert de opstelling in 1 int, zodanig dat symmetrische stelling ook hetzelfde kengetal geven
  bordKengetal huidigeOpstelling = encodeerBord();

  // kijk of we hem al hebben gezien
  unordered_set<bordKengetal>::iterator alBekend = alleKennis.find ( huidigeOpstelling );
  if( alBekend != alleKennis.end() ){
    return;
  }

  // oplossing gevonden
  if( gewonnen() ){
    throw true;
  }

  // probeer alle zetten in de huidige opstelling
  doeVoorMogelijkeZetten([] (int x, int y, richting r){
    doeZet( x, y, r );
    huidigePad.push( make_tuple(x,y,r) );

    // recursie
    stellingTeRedden();

    zetTerug( x, y, r );
    huidigePad.pop();
  });

  // opslaan dat we deze al hebben gezien
  alleKennis.insert( huidigeOpstelling );
}

