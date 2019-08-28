#include "../include/GeneSequence.h"

int main() {
	int vsize, k, cc, i, j;
	float timeLimit;
	string tempString;
	vector<string> myStrings;
	vector<vector<int> > costMap;

	cin >> timeLimit;											// input for the time limit of the runtime of the code

	cin >> vsize;												// input for vocabulary size and its letters

	char dumpComma;
	vector<char> myVocabulary(vsize, '*');
	for (i = 0; i < vsize-1; i++)
		cin >> myVocabulary[i] >> dumpComma;
	cin >> myVocabulary[vsize - 1];
	myVocabulary.push_back('-');

	cin >> k;													// input for number of strings and the strings
	for (i = 0; i < k; i++) {
		cin >> tempString;
		myStrings.push_back(tempString);
	}

	cin >> cc;													// input for conversion cost

	int tempInt;												// input for matching cost matrix
	for (i = 0; i < vsize + 1; i++) {
		vector<int> tempVector;
		for (j = 0; j < vsize + 1; j++) {
			cin >> tempInt;
			tempVector.push_back(tempInt);
		}
		costMap.push_back(tempVector);
	}
	GeneSequence* genes = new GeneSequence(vsize+1, myVocabulary, k, myStrings, cc, costMap);
	//genes->balanceStrings();
	vector<string> answer = genes->hillClimbing();
	for(int i=0;i<answer.size();i++){
		cout<<answer[i]<<endl;
	}


	//TODO Handle # input ?
	return 0;
}
