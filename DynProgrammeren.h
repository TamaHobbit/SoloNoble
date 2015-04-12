map<bordKengetal, bool> alleKennis;
stack<tuple<int,int,richting>> huidigePad;

// Voor alle lege gaten, kijk of daarnaast twee knikkers op een rij zitten
bool doeVoorMogelijkeZetten(bordKengetal state, std::function<bool(int,int,int,int)> todo){
  for( int y = 0; y < 7; ++y ){  
    for( int x = 0; x < 7; ++x ){
      if( !holeIsOnBoard(x,y) ){
        continue;
      }
      if( !isBezet(state, x, y) ){
        if( y > 1 && isBezet(state, x, y-1) && isBezet(state,x,y-2) ){
          if( todo( x, y-2, x, y ) ){
            return true;
          }
        }
        if( x < 5 && isBezet(state, x+1, y) && isBezet(state, x+2, y) ){
          if( todo( x+2, y, x, y ) ){
            return true;
          }
        }
        if( y < 5 && isBezet(state, x, y+1) && isBezet(state, x, y+2) ){
          if( todo( x, y+2, x, y ) ){
            return true;
          }
        }
        if( x > 1 && isBezet(state, x-1, y) && isBezet(state, x-2, y) ){
          if( todo( x-2, y, x, y ) ){
            return true;
          }
        }
      }
    }
  }
  return false;
}

void stellingTeRedden(bordKengetal encodedBoard, std::atomic<bool> & result, std::atomic<bool> & calculationCancelled){
  if( calculationCancelled ){
    return;
  }

  // kijk of we hem al hebben gezien
  map<bordKengetal, bool>::const_iterator alBekend = alleKennis.find ( encodedBoard );
  if( alBekend != alleKennis.end() ){
    result = alBekend->second;
    return;
  }

  // oplossing gevonden
  if( gewonnen(encodedBoard) ){
    alleKennis[ encodedBoard ] = true;
    result = true;
    return;
  }

  // probeer alle zetten in de huidige opstelling
  if( doeVoorMogelijkeZetten(encodedBoard, [encodedBoard, &calculationCancelled, &result] (int x, int y, int toX, int toY){
    bordKengetal nextState = doeZet( encodedBoard, x, y, toX, toY );
    stellingTeRedden(nextState, result, calculationCancelled);
    return !calculationCancelled && result;
  }) ){
    alleKennis[ encodedBoard ] = true;
    return;
  }

  // opslaan dat we deze al volledig hebben uitgeprobeerd
  if( !calculationCancelled ){
    alleKennis[ encodedBoard ] = false;
    result = false;
  }
}

