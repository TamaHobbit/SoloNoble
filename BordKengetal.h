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
  
  return kleinsteEquivalente( bedacht );
}

bordKengetal holeMasks[49] = {
  0, 0, 144115188075855872, 1157425104234217472, 562949953421312, 0, 0, 
  0, 0, 288230376151711744, 2314850208468434944, 1125899906842624, 0, 0, 
  2, 4, 576460752303423496, 4629700416936869888, 2260595906707456, 4398046511104, 2199023255552, 
  4112, 8224, 16448, 9259542123273814144ul, 70643622084608, 35321811042304, 17660905521152, 
  512, 1024, 526336, 1077936128, 34493956096, 17179869184, 8589934592, 
  0, 0, 262144, 538968064, 67108864, 0, 0, 
  0, 0, 131072, 269484032, 33554432, 0, 0 
};

bordKengetal gatMask(int targetX, int targetY){
  return holeMasks[targetY*7+targetX];
}

//used to populate table above
bordKengetal berekenGatMask(int targetX, int targetY){
  bordKengetal toFlip = 0;

  for( int x = 2; x <= 4; x += 2 ){ //links, dan rechts
    for( int y = 3; y >= 0; --y ){ //in deze eerste for zit geen x, want de middellijn is gelijk in beide octanten
      if( targetX == 3 && targetY == y ){
        toFlip |= 1;
      }
      toFlip <<= 1;
    }
    for( int y = 2; y >= 0; --y ){
      if( targetX == x && targetY == y ){
        toFlip |= 1;
      }
      toFlip <<= 1;
    }
    // deze bit is altijd 0 (1 per 8-tal)
    toFlip <<= 1;
  }
  
  // octant rechtsboven en -onder
  for( int y = 2; y <= 4; y += 2 ){ //boven, dan onder
    for( int x = 3; x <= 6; ++x ){
      if( targetX == x && targetY == 3 ){
        toFlip |= 1;
      }
      toFlip <<= 1;
    }
    for( int x = 4; x <= 6; ++x ){
      if( targetX == x && targetY == y ){
        toFlip |= 1;
      }
      toFlip <<= 1;
    }
    toFlip <<= 1;
  }
  
  // octant onderrechts en -links
  for( int x = 4; x >= 2; x -= 2 ){ //rechts, dan links
    for( int y = 3; y <= 6; ++y ){
      if( targetX == 3 && targetY == y ){
        toFlip |= 1;
      }
      toFlip <<= 1;
    }
    for( int y = 4; y <= 6; ++y ){
      if( targetX == x && targetY == y ){
        toFlip |= 1;
      }
      toFlip <<= 1;
    }
    toFlip <<= 1;
  }

  // octant linksonder en -boven
  for( int y = 4; y >= 2; y -= 2 ){ //onder, dan boven
    for( int x = 3; x >= 0; --x ){
      if( targetX == x && targetY == 3 ){
        toFlip |= 1;
      }
      toFlip <<= 1;
    }
    for( int x = 2; x >= 0; --x ){
      if( targetX == x && targetY == y ){
        toFlip |= 1;
      }
      toFlip <<= 1;
    }
    if( y == 4 ){ //laatste niet meer opschuiven!
      toFlip <<= 1;
    }
  }
  return toFlip;
}

bordKengetal doeZet(bordKengetal state, int x, int y, int toX, int toY){
  int middleX = (x + toX) / 2;
  int middleY = (y + toY) / 2;
  state ^= gatMask(x,y);
  state ^= gatMask(middleX, middleY);
  state ^= gatMask(toX, toY);
  return kleinsteEquivalente(state);
}

bool isBezet(bordKengetal state, int x, int y){
  return state & gatMask(x,y);
}

bool magZet(bordKengetal state, int x, int y, int toX, int toY){
  assert(x >= 0 && x < 7 && y >= 0 && y < 7);
  assert(toX >= 0 && toX < 7 && toY >= 0 && toY < 7);
  if( x == toX ){
    if( !(y == toY-2 || y == toY + 2) ){
      return false;
    }
  } else if( y == toY ) {
    if( !(x == toX-2 || x == toX + 2) ){
      return false;
    }
  } else {
    return false;
  }
  int middleX = (x + toX) / 2;
  int middleY = (y + toY) / 2;
  return isBezet(state, x, y) && isBezet(state, middleX, middleY) && !isBezet(state, toX, toY);
}
