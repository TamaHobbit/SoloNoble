unordered_set<bordKengetal> alleKennis;
stack<tuple<int,int,richting>> huidigePad;

// Voor alle lege gaten, kijk of daarnaast twee knikkers op een rij zitten
void doeVoorMogelijkeZetten(bordKengetal state, std::function<void(int,int,int,int)> todo){
  for( int y = 0; y < 7; ++y ){  
    for( int x = 0; x < 7; ++x ){
      if( !holeIsOnBoard(x,y) ){
        continue;
      }
      if( !isBezet(state, x, y) ){
        if( y > 1 && isBezet(state, x, y-1) && isBezet(state,x,y-2) ){
          todo( x, y-2, x, y );
        }
        if( x < 5 && isBezet(state, x+1, y) && isBezet(state, x+2, y) ){
          todo( x+2, y, x, y );
        }
        if( y < 5 && isBezet(state, x, y+1) && isBezet(state, x, y+2) ){
          todo( x, y+2, x, y );
        }
        if( x > 1 && isBezet(state, x-1, y) && isBezet(state, x-2, y) ){
          todo( x-2, y, x, y );
        }
      }
    }
  }
}

// Kijkt recursief (met Depth-first search) of de stelling nog te winnen valt door 
// steeds een zet te doen, zichzelf aan te roepen, en dan de zet terug te doen
// elke stelling hoeft maar 1 keer worden bekeken (of een punt- of lijnsymmetrishe )
// "throw true" als de oplossing is gevonden, zodat huidigePad nog steeds de zetten bevat
void stellingTeRedden(bordKengetal encodedBoard){
  // kijk of we hem al hebben gezien
  
  unordered_set<bordKengetal>::iterator alBekend = alleKennis.find ( encodedBoard );
  if( alBekend != alleKennis.end() ){
    return;
  }

  // oplossing gevonden
  if( gewonnen(encodedBoard) ){
    throw true;
  }

  // probeer alle zetten in de huidige opstelling
  doeVoorMogelijkeZetten(encodedBoard, [encodedBoard] (int x, int y, int toX, int toY){
    //huidigePad.push( make_tuple(x,y,toX,toY) );

    // recursie
    stellingTeRedden(doeZet( encodedBoard, x, y, toX, toY ));

    //huidigePad.pop();
  });

  // opslaan dat we deze al hebben gezien
  alleKennis.insert( encodedBoard );
}

