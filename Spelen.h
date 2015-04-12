enum richting {
  boven, rechts, onder, links
};

bool zetKan(int x, int y, richting springKant){
  switch( springKant ){
    case boven:
      return y > 1 && gaten[x][y-1] == knikker && gaten[x][y-2] == open;
    case rechts:
      return x < 5 && gaten[x+1][y] == knikker && gaten[x+2][y] == open;
    case onder:
      return y < 5 && gaten[x][y+1] == knikker && gaten[x][y+2] == open;
    case links:
      return x > 1 && gaten[x-1][y] == knikker && gaten[x-2][y] == open;
  }
  return false;
}

bool zetKan(int x, int y, int toX, int toY){
  if( toX == x ){
    if( toY == y-2 ){
      return zetKan(x,y,boven);
    }
    if( toY == y+2 ){
      return zetKan(x,y,onder);
    }
  }
  if( toY == y ){
    if( toX == x-2 ){
      return zetKan(x,y,links);
    }
    if( toX == x+2 ){
      return zetKan(x,y,rechts);
    }
  }
  return false;
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

bool holeIsOnBoard(int x, int y){
  return !( (x < 2 || x > 4) && (y < 2 || y > 4) );
}

void beginSituatie(){
  for( int y = 0; y < 7; ++y ){  
    for( int x = 0; x < 7; ++x ){
      if( holeIsOnBoard(x,y) ){
        gaten[x][y] = knikker;
      } else {
        gaten[x][y] = bestaatNiet;
      }
    }
  }
  gaten[3][3] = open;
}

void doeZet(int x, int y, int toX, int toY){
  if( toX == x ){
    if( toY == y-2 ){
      doeZet(x,y,boven);
    }
    if( toY == y+2 ){
      doeZet(x,y,onder);
    }
  }
  if( toY == y ){
    if( toX == x-2 ){
      doeZet(x,y,links);
    }
    if( toX == x+2 ){
      doeZet(x,y,rechts);
    }
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

void zetTerug(int x, int y, int toX, int toY){
  int middleX = (x + toX) / 2;
  int middleY = (y + toY) / 2;
  gaten[x][y] = knikker;
  gaten[middleX][middleY] = knikker;
  gaten[toX][toY] = open;
}

bool gewonnen(){
  for( int y = 0; y < 7; ++y ){  
    for( int x = 0; x < 7; ++x ){
      if( (x == 3 && y == 3) != (gaten[x][y] == knikker) ){
        return false;
      }
    }
  }
  return true;
}

bool gewonnen(bordKengetal state){
  bordKengetal middleMask = gatMask(3,3);
  return state == middleMask;
}