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

void toonZet(tuple<int,int,richting> zet){
  cout << get<0>(zet) << " " << get<1>(zet);
  const auto r = get<2>(zet);
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

void toonSituatie(){
  cout << "-------" << endl;
  printBord();
  cout << "-------" << endl;
  cout << endl << "Kengetal: " << encodeerBord() << endl;
  cout << "Mogelijke zetten: " << endl;
    
  doeVoorMogelijkeZetten([](int x, int y, richting r){
    cout << x << " " << y;
    if( r == boven ){
      cout << " boven" << endl;
    } else if( r == rechts ){
      cout << " rechts" << endl;
    } else if( r == onder ){
      cout << " onder" << endl;
    } else if( r == links ){
      cout << " links" << endl;
    }
  });
  cout << "======Uw zet:======" << endl;
}

void SpelerMagSpelen(){
  //de invoer variabelen
  int xInvoer, yInvoer;
  string richtingInvoer;
  richting echteRichting;
  
  while( !cin.eof() && !gewonnen() ){
    toonSituatie();

    cin >> xInvoer;
    cin >> yInvoer;
    cin >> richtingInvoer;
    
    if( richtingInvoer == "boven" ){
      echteRichting = boven;
    } else if( richtingInvoer == "rechts" ){
      echteRichting = rechts;
    } else if( richtingInvoer == "onder" ){
      echteRichting = onder;
    } else if( richtingInvoer == "links" ){
      echteRichting = links;
    } else {
      cout << "Ongeldige richting; Richtingen heten boven, rechts, onder, links" << endl;
    }

    if( zetKan( xInvoer, yInvoer, echteRichting ) ){
      doeZet( xInvoer, yInvoer, echteRichting );
    } else {
      cout << endl << "Dat kan niet." << endl;
    }
  }
  //todo ook stoppen als er geen zetten meer mogelijk zijn, 
  //zodat je niet het programma hoeft te force quitten
  cout << "Je hebt gewonnen!" << endl; 
}
