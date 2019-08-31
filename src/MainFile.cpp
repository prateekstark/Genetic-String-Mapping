#include "../include/GeneSequence.h"

extern time_t startingTime, currentTime;
extern int timeLimit;
extern vector<string> answerReport;
extern int costReport;
extern bool reversed;
extern bool answerReverse;
int main(int argc, char *argv[]){
	// cout<<argc<<endl;
	// return 0;
	if(argc == 3){

		string inputFileName(argv[1]);
		string outputFileName(argv[2]);
		ifstream inputFile(inputFileName);
		string line;
		time_t timestart, timeend;

		int vsize, k, cc, i, j;
		float execTime;
		string tempString;
		vector<string> myStrings;
		vector<vector<int> > costMap;
		vector<int> goalTuple;
		vector<int> zeroTuple;
		char dumpComma;
		getline(inputFile, line);
		// cout<<line<<endl;										// input for the time limit of the runtime of the code
		execTime = stof(line);

		getline(inputFile, line);
		vsize = stoi(line);												// input for vocabulary size and its letters
		vector<char> myVocabulary(vsize, '*');
		getline(inputFile, line);
		int tempIndex = 0;
		for (i = 0; i < vsize; i++){
			myVocabulary[i] = line.at(tempIndex);
			tempIndex = tempIndex + 3;
		}
		myVocabulary.push_back('-');
		// for(int i=0;i<myVocabulary.size();i++){
		// 	cout<<myVocabulary[i]<<" ";
		// }
		// cout<<endl;
		getline(inputFile, line);
		k = stoi(line);													// input for number of strings and the strings

		for (i = 0; i < k; i++){
			getline(inputFile, line);
			tempString = line;
			tempString.erase(remove(tempString.begin(), tempString.end(),' '), tempString.end());

			myStrings.push_back(tempString.substr(0, tempString.size() - 1));
			goalTuple.push_back(tempString.length());
			zeroTuple.push_back(0);
		}
		getline(inputFile, line);
		cc = stoi(line);													// input for conversion cost
		string falseString;
		int tempInt;											// input for matching cost matrix
		for (i = 0; i < vsize + 1; i++) {
			vector<int> tempVector;
			// getline(inputFile, line);
			tempIndex = 0;
			for (j = 0; j < vsize + 1; j++){
				inputFile >> tempInt;
				// tempIndex = tempIndex + 2;
				tempVector.push_back(tempInt);
			}
			costMap.push_back(tempVector);
		}
		// for(int i=0;i<costMap.size();i++){
		// 	for(int j=0;j<costMap[0].size();j++){
		// 		cout<<costMap[i][j]<<" ";
		// 	}
		// 	cout<<endl;
		// }
		char hash;
		inputFile.close();
		time(&timestart);
		startingTime = timestart;
		timeLimit = (int)(execTime * 60 - 5);
		// cout<<myStrings[2].size()<<endl;.
		GeneSequence* genes = new GeneSequence(vsize + 1, myVocabulary, k, myStrings, cc, costMap);
		HillClimbingState startState(myStrings);
		int maxlen = genes->maxStringLength(myStrings) + 15;
		int finalCost1 = genes->localSearch(startState, maxlen);

		for (int i = 0; i < k; i++)
			reverse(startState.orientation[i].begin(), startState.orientation[i].end());
		reversed = 1;
		int finalCost2 = genes->localSearch(startState, maxlen);
		answerReport = genes->balanceStrings(answerReport);
		ofstream outputFile(outputFileName);
		for(int i=0;i<answerReport.size();i++){
			if(answerReverse){
				reverse(answerReport[i].begin(), answerReport[i].end());
			}
			outputFile << answerReport[i] << endl;

		}
		cout << costReport << endl;
		time(&timeend);
	}
	else{
		cerr<<"Wrong Arguments"<<endl;
	}
	return 0;
}
