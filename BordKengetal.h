#include <algorithm>

typedef uint64_t bordKengetal;

// geeft het bordKengetal voor de opstelling die precies 90 graden gedraaid is t.o.v. invoer
bordKengetal draai90( bordKengetal invoer ){
  return (invoer << 16) | (invoer >> (64-16));
}

// geeft het bordKengetal voor de opstelling die gespiegeld is in x of y as 
// (welke makkelijker is, aangezien we ook draaien hoeven we er maar 1)
bordKengetal flip( bordKengetal invoer ){
  return 0;// todo
}

// draait invoer alle 4 kanten op en geeft het kleinste kengetal terug
// 3 1 onder, 1 3 rechts, 5 3 links en 3 5 boven
// hebben deze kengetallen, maar alleen de eerste wordt nu gebruikt
//11429853275466170110
//18374403900871450270
//18374297935438348030
//18374403899254570750
bordKengetal kleinsteEquivalente( bordKengetal invoer ){
  bordKengetal gedraaid[4];
  for(int i = 0; i < 4; ++i){
    gedraaid[i] = invoer;
    invoer = draai90( invoer );
  }
  sort( gedraaid, gedraaid + 4 );
  return gedraaid[0];
}

// deelt het bord op in 8 gelijke, overlappende stukken van 7 bits elk
// elk stuk wordt op een volgorde als bits in een bordKengetal gestopt
bordKengetal encodeerBord(){
  bordKengetal bedacht = 0;

  // octant bovenlinks en -rechts
  for( int x = 2; x <= 4; x += 2 ){ //links, dan rechts
    for( int y = 3; y >= 0; --y ){ //in deze eerste for zit geen x, want de middellijn is gelijk in beide octanten
      bedacht |= (gaten[3][y] == knikker);
      bedacht <<= 1;
    }
    for( int y = 2; y >= 0; --y ){
      bedacht |= (gaten[x][y] == knikker);
      bedacht <<= 1;
    }
    // deze bit is altijd 0 (1 per 8-tal)
    bedacht <<= 1;
  }
  
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
    if( y == 4 ){ //laatste niet meer opschuiven!
      bedacht <<= 1;
    }
  }
  
  bedacht = kleinsteEquivalente( bedacht );
  return bordKengetal(bedacht);
}
