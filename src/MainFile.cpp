#include "../include/GeneSequence.h"
time_t startingTime, currentTime;
int timeLimit;
vector<string> answerReport;
int costReport = -1;


int main(){

	time_t timestart, timeend;

	int vsize, k, cc, i, j;
	float execTime;
	string tempString;
	vector<string> myStrings;
	vector<vector<int> > costMap;
	vector<int> goalTuple;
	vector<int> zeroTuple;

	cin >> execTime;											// input for the time limit of the runtime of the code

	cin >> vsize;												// input for vocabulary size and its letters

	char dumpComma;
	vector<char> myVocabulary(vsize, '*');
	for (i = 0; i < vsize - 1; i++)
		cin >> myVocabulary[i] >> dumpComma;
	cin >> myVocabulary[vsize - 1];
	myVocabulary.push_back('-');


	cin >> k;													// input for number of strings and the strings
	for (i = 0; i < k; i++) {
		cin >> tempString;
		myStrings.push_back(tempString);
		goalTuple.push_back(tempString.length());
		zeroTuple.push_back(0);
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

	char hash;													// ipnut for the last hash
	cin >> hash;

	time(&timestart);
	startingTime = timestart;
	timeLimit = (int)(execTime * 60 - 5);

	GeneSequence* genes = new GeneSequence(vsize + 1, myVocabulary, k, myStrings, cc, costMap);
	HillClimbingState startState(myStrings);
	// int maxlen = (genes->maxStringLength(myStrings))*vsize;
	int maxlen = genes->maxStringLength(myStrings) + 15;

	int finalCost1 = genes->localSearch(startState, maxlen);

	for (int i = 0; i < k; i++)
		reverse(startState.orientation[i].begin(), startState.orientation[i].end());

	cout << "STARTED REVERSE" << endl;

	int finalCost2 = genes->localSearch(startState, maxlen);

	// cout << "Forward final cost: " << finalCost1 << endl;
	// cout << "Backward final cost: " << finalCost2 << endl;

	printStringVector(answerReport);
	cout << costReport << endl;
	time(&timeend);
	cout << "Time taken: " << double(timeend - timestart) << setprecision(5) << "s" << endl;
	return 0;
}
