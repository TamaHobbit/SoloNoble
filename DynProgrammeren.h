
#include <unordered_map>

typedef unordered_map<eightBite,bool> hashTabel;
typedef unordered_map<eightBite,bool>::iterator stellingsInformatie;

hashTabel alleKennis;

bool stellingTeRedden(){
  eightBite huidigeOpstelling = BordKengetal::encodeerBord();
  stellingsInformatie alBekend = alleKennis.find ( huidigeOpstelling );
  if( alBekend != alleKennis.end() ){ //gevonden in de map, dus al geweest
    return *alBekend;
  } else {
    return false;//todo recursie
  }
}
