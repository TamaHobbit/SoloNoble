

typedef unsigned long long eightBite;

class BordKengetal {
  const eightBite getal;

public:
  BordKengetal(eightBite g) : getal(g) {
  }

  static BordKengetal encodeerBord(){
    eightBite bedacht = 0;
    
    // octant bovenlinks en -rechts
    for( int x = 2; x <= 4; x += 2 ){ //links, dan rechts
      for( int y = 3; y >= 0; --y ){
        bedacht |= (gaten[3][y] == knikker);
        bedacht <<= 1;
      }
      for( int y = 2; y >= 0; --y ){
        bedacht |= (gaten[x][y] == knikker);
        bedacht <<= 1;
      }
      bedacht <<= 1;
    }
    /*
    // octant rechtsboven en -onder
    for( int y = 2; y <= 4; y += 2 ){ //boven, dan onder
      for( int x = 3; x <= 6; ++x ){
        bedacht |= (gaten[x][3] == knikker);
        bedacht <<= 1;
      }
      for( int x = 4; x <= 6; ++x ){
        bedacht |= (gaten[x][y] == knikker);
        bedacht <<= 1;
      }
      bedacht <<= 1;
    }
    
    // octant onderrechts en -links
    for( int x = 4; x >= 2; x -= 2 ){ //rechts, dan links
      for( int y = 3; y <= 6; ++y ){
        bedacht |= (gaten[3][y] == knikker);
        bedacht <<= 1;
      }
      for( int y = 4; y <= 6; ++y ){
        bedacht |= (gaten[x][y] == knikker);
        bedacht <<= 1;
      }
      bedacht <<= 1;
    }

    // octant linksonder en -boven
    for( int y = 4; y >= 2; y -= 2 ){ //onder, dan boven
      for( int x = 3; x >= 0; --x ){
        bedacht |= (gaten[x][3] == knikker);
        bedacht <<= 1;
      }
      for( int x = 2; x >= 0; --x ){
        bedacht |= (gaten[x][y] == knikker);
        bedacht <<= 1;
      }
      //niet meer opschuiven!
    }
*/
    return BordKengetal(bedacht);
  }

  friend ostream& operator<<( ostream& links, const BordKengetal & rechts ){
    return links << rechts.getal;
  }
};




