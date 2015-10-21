#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <list>
#include <tuple>
#include <stack>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include <fstream>
using namespace std;

const char open = 'O';
const char knikker = 'X';
const char bestaatNiet = ' ';

char gaten[7][7];

#include "BordKengetal.h"
#include "Spelen.h"
#include "DynProgrammeren.h"
#include "Interface.h"
#include "TwoClickOrDrag.h"
#include "SDLscherm.h"

/*
int main(){
	basic_ifstream<char> dataFile("solutions.bin", ios::in | ios::binary);
	vector<bordKengetal> allSolutions;
	bordKengetal currentNumber;

  // Dahl loop, or N-and-a-half loop
  for( ; dataFile.read(reinterpret_cast<char*>(&currentNumber),8), dataFile.good(); ){
    allSolutions.push_back(currentNumber);
    cout << currentNumber << endl;
  }

	cout << allSolutions.size() << endl;
}
*/

int main() {
  basic_ofstream<char> dataFile("solutions.bin", ios::out | ios::binary);

  beginSituatie();
  bordKengetal current = 105976010262080;//encodeerBord();
  uint64_t totalSolutions = 0;
  stellingTeReddenBlocking(current, totalSolutions);

  cout << "Done, " << totalSolutions << " solutions" << endl;
  vector<bordKengetal> allSolutions;
  allSolutions.reserve(totalSolutions);

  for(auto kvp : alleKennis){
  	if( kvp.second ){
  		allSolutions.push_back(kvp.first);
  	}
  }
  assert(allSolutions.size() == totalSolutions);

  const size_t solutionBytes = allSolutions.size() * sizeof(allSolutions[0]);
  if( !dataFile.write(reinterpret_cast<char*>(&allSolutions[0]), solutionBytes) ){
    cout << "Writing to file failed" << endl;
  }
  
  dataFile.close();
  for(auto s : allSolutions){
   	cout << s << endl;
  }

  return 0;
}

