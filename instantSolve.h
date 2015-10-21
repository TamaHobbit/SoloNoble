vector<bordKengetal> allSolutions;

void loadSolutions(){
	assert(allSolutions.empty());

	basic_ifstream<char> dataFile("solutions.bin", ios::in | ios::binary);
	allSolutions.reserve(3357032);
	bordKengetal currentNumber;

	// Dahl loop, or N-and-a-half loop
	for( ; dataFile.read(reinterpret_cast<char*>(&currentNumber),8), dataFile.good(); ){
		allSolutions.push_back(currentNumber);
		//cout << currentNumber << endl;
	}

	dataFile.close();
}

bool checkPosition(bordKengetal currentPosition){
	assert(!allSolutions.empty());
	auto element = lower_bound(allSolutions.begin(), allSolutions.end(), currentPosition);
	if( element == allSolutions.end() ){
		return false;
	}
	return (*element) == currentPosition;
}
