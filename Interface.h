void printBord(){
  for( int y = 0; y < 7; ++y ){  
    for( int x = 0; x < 7; ++x ){
      cout << gaten[x][y];
    }
    cout << "\n";
  }
}

void beginInstructies(){
  cout << endl << "Speel door bijvoorbeeld \"3 1 onder\" [enter] in te toetsen. Dat is ook een geldige eerste zet." << endl;
  cout << "Richtingen heten boven, rechts, onder, links" << endl << endl;
}

void toonSituatie(){
  cout << "-------" << endl;
  printBord();
  cout << "-------" << endl;
  cout << endl << "Kengetal: " << encodeerBord() << endl;
  cout << "Mogelijke zetten: " << endl;
    
  list<tuple<int,int,richting>> mogelijkheden = alleMogelijkeZetten();
  for( mogelijkeZet it = mogelijkheden.begin(); it != mogelijkheden.end(); ++it ){
    cout << get<0>(*it) << " " << get<1>(*it);
    const auto r = get<2>(*it);
    if( r == boven ){
      cout << " boven" << endl;
    } else if( r == rechts ){
      cout << " rechts" << endl;
    } else if( r == onder ){
      cout << " onder" << endl;
    } else if( r == links ){
      cout << " links" << endl;
    }
  }
  cout << "======Uw zet:======" << endl;
}
