

typedef long long eightBite;

class BordKengetal {
  const eightBite getal;

public:
  BordKengetal(eightBite g) : getal(g) {
  }

  static BordKengetal encodeerBord(){
    eightBite bedacht = 0;
    
    // octant bovenlinks
    for( int y = 3; y >= 0; --y ){
      bedacht |= (gaten[3][y] == knikker);
      bedacht <<= 1;
    }
    for( int y = 2; y >= 0; --y ){
      bedacht |= (gaten[2][y] == knikker);
      bedacht <<= 1;
    }
    bedacht << 8; //opschuiven zodat we ruimte hebben voor de volgende octant

    // octant bovenrechts
    for( int y = 3; y >= 0; --y ){
      bedacht |= (gaten[3][y] == knikker);
      bedacht <<= 1;
    }
    for( int y = 2; y >= 0; --y ){
      bedacht |= (gaten[4][y] == knikker);
      bedacht <<= 1;
    }
    bedacht << 8;
    
    
    return BordKengetal(bedacht);
  }

  friend ostream& operator<<( ostream& links, const BordKengetal & rechts ){
    return links << rechts.getal;
  }
};




