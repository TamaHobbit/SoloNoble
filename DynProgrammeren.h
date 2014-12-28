
#include <unordered_map>
#include <list>
#include <tuple>

typedef unordered_map<bordKengetal,bool> hashTabel;
typedef unordered_map<bordKengetal,bool>::iterator stellingsInformatie;

hashTabel alleKennis;

typedef list<tuple<int,int,richting>>::iterator mogelijkeZet;

list<tuple<int,int,richting>> alleMogelijkeZetten(){
  list<tuple<int,int,richting>> gevondenZetten;
  for( int y = 0; y < 7; ++y ){  
    for( int x = 0; x < 7; ++x ){
      if( gaten[x][y] == open ){
        if( y > 1 && gaten[x][y-1] == knikker && gaten[x][y-2] == knikker ){
          gevondenZetten.push_front( make_tuple( x, y-2, onder ) );
        }
        if( x < 6 && gaten[x+1][y] == knikker && gaten[x+2][y] == knikker ){
          gevondenZetten.push_front( make_tuple( x+2, y, links ) );
        }
        if( y < 6 && gaten[x][y+1] == knikker && gaten[x][y+2] == knikker ){
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

bool stellingTeRedden(){
  bordKengetal huidigeOpstelling = encodeerBord();
  stellingsInformatie alBekend = alleKennis.find ( huidigeOpstelling );
  if( alBekend != alleKennis.end() ){ //gevonden in de map, dus al geweest
    bool resultaat = alBekend->second;
    alleKennis[huidigeOpstelling] = resultaat;
    return resultaat;
  } else {
    list<tuple<int,int,richting>> mogelijkheden = alleMogelijkeZetten();
    if( mogelijkheden.empty() ){
      bool resultaat = gewonnen();
      alleKennis[huidigeOpstelling] = resultaat;
      return resultaat;
    } else {
      for( mogelijkeZet it = mogelijkheden.begin(); it != mogelijkheden.end(); ++it ){
        doeZet( get<0>(*it), get<1>(*it), get<2>(*it) );
        bool resultaat = stellingTeRedden();
        alleKennis[huidigeOpstelling] = resultaat;
        zetTerug( get<0>(*it), get<1>(*it), get<2>(*it) );
        return resultaat;
      }
    }
  }
}
