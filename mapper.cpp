#include<iostream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;

//int totalCost(vector<string> strings, vector<vector<int> > costMap) {
//
//}

string convertNumberToBinary(int n, int len) {
	string answer = "";
	while (n != 0) {
		answer = to_string(n % 2) + answer;
		n = n / 2;
	}

	while (answer.size() < len)
		answer = '0' + answer;

	return answer;
}

string convertNumberToBinarySimple(int n) {
	string answer = "";
	while (n != 0) {
		answer = to_string(n % 2) + answer;
		n = n / 2;
	}
	return answer;
}


class MyState{
public:
	vector<int> state;
	vector<string> orientation;
	int cost;
	MyState(){
		vector<int> state;
		vector<string> orientation;
		this->cost = 0;
	}
};


class statePriorityQueue{

};



class GeneSequence {
public:
	vector<string> strings;
	vector<vector<int> > costMap;
	vector<char> vocabulary;
	int cc;
	int k;
	int vsize;
	// constructor
	GeneSequence(int vocSize, vector<char> vocab, int kin, vector<string> stringSequence, int ccin, vector<vector<int> > inputCostMap) {
		this->strings = stringSequence;
		this->costMap = inputCostMap;
		this->vocabulary = vocab;
		this->cc = ccin;
		this->k = kin;
		this->vsize = vocSize;
		
	}
	//Printing the present state for debugging
	
	// void printPresentState(){
	// 	for(int i=0;i<this->state.size();i++){
	// 		cout<<state.at(i)<<" ";
	// 	}
	// 	cout<<endl;
	// }

	// prints all the strings in the scenario
	void printStringVector() {
		for (int i = 0; i < strings.size(); i++) {
			cout << strings.at(i) << endl;
		}
	}

	// prints the saved costmap
	void printCostMap() {
		for (int i = 0; i < costMap.size(); i++) {
			for (int j = 0; j < costMap[0].size(); j++) {
				cout << costMap[i][j] << " ";
			}
			cout << endl;
		}
	}

	// finds the character index in the vocabulary
	int findInVocabulary(char c){
		for (int i = 0; i < vsize; i++)
		{
			if (vocabulary[i] == c)
				return i;
		}
		return -1;
	}

	// inserts a new string in the main string vector
	void insertString(string str) {
		strings.push_back(str);
	}

	// appends extra '-'s at each string to reach max length
	void balanceStrings() {
		int maxStringSize = 0;
		for (int i = 0; i < strings.size(); i++) {
			if (strings[i].size() > maxStringSize) {
				maxStringSize = strings[i].size();
			}
		}
		for (int i = 0; i < strings.size(); i++) {
			if (strings[i].size() < maxStringSize) {
				while (strings[i].size() != maxStringSize) {
					strings[i] = strings[i] + "-";
				}
			}
		}
	}

	// adds 3 '-'s for each character in the string to inculcate all the cases
	vector<string> bruteForceDivide(vector<string> balancedStrings) {
		string tempString;
		vector<string> bruteDividedStrings;
		for (int i = 0; i < balancedStrings.size(); i++) {
			tempString = "";
			for (int j = 0; j < balancedStrings[i].size(); j++) {
				if (balancedStrings[i][j] == 'A') {
					tempString = tempString + "A---";
				}
				if (balancedStrings[i][j] == 'B') {
					tempString = tempString + "-B--";
				}
				if (balancedStrings[i][j] == 'C') {
					tempString = tempString + "--C-";
				}
				if (balancedStrings[i][j] == 'D') {
					tempString = tempString + "---D";
				}
			}
			bruteDividedStrings.push_back(tempString);
		}
		return bruteDividedStrings;
	}

	bool twoVectorsEqual(vector<int> v1, vector<int> v2){
		if(v1.size() == v2.size()){
			for(int i=0;i<v1.size();i++){
				if(v1.at(i) != v2.at(i)){
					return 0;
				}
			}
			return 1;
		}
		return 0;
	}

	int computeStepCost(vector<int> initialState, vector<int> finalState, vector<string> initialOrientation, int step){
		int answer = 0;
		string tempString = "";
		printStringVector(initialOrientation);
		vector<string> tempOrientation = getNextOrientation(initialState, finalState, step - 1 , initialOrientation);
		printStringVector(tempOrientation);
		for(int j=0;j<step;j++){
			tempString = "";
			for(int i=0;i<tempOrientation.size();i++){
				tempString = tempString + tempOrientation[i][j];
			}
			answer = answer + computeCostString(tempString);
		}
		return answer;
	}

	vector<string> getNextOrientation(vector<int> initialState, vector<int> finalState, int step, vector<string> initialOrientation){
		vector<string> tempOrientation = initialOrientation;
		for(int i=0;i<tempOrientation.size();i++){
			if(finalState[i] - initialState[i] != 1){
				tempOrientation[i].insert(tempOrientation[i].begin() + step, '-');
			}
		}
		return tempOrientation;
	}

	//In a vector of states, is a particular state present?
	int isStatePresent(vector<MyState*> stateSequence, vector<int> key_state){
		for(int i=0;i<stateSequence.size();i++){
			if(twoVectorsEqual(stateSequence.at(i)->state, key_state)){
				return i;
			}
		}
		return -1;
	}

	bool isHayPresentInStack(vector<int> hay, vector<vector<int> > stack){
		for(int i=0;i<stack.size();i++){
			if(twoVectorsEqual(stack[i], hay)){
				return 1;
			}
		}
		return 0;
	}

	//Generating children states
	vector<vector<int> > childrenState(vector<int> curr_state, vector<int> goalState){
		vector<vector<int> > answer;
		if(twoVectorsEqual(curr_state, goalState)){
			return answer;
		}
		int n = curr_state.size();
		string tempString;
		
		for(int i=1;i<pow(2, n);i++){
			vector<int> tempState;
			tempString = convertNumberToBinary(i, n);
			// cout<<tempString;
			for(int j=0;j<n;j++){
				if(tempString.at(j) == '1' && curr_state[j] < goalState[j]){
					tempState.push_back(curr_state.at(j) + 1);
				}
				else{
					tempState.push_back(curr_state.at(j));
				}
			}
			if(!isHayPresentInStack(tempState, answer) && !twoVectorsEqual(curr_state, tempState)){
				answer.push_back(tempState);	
			}
			
		}
		return answer;
	}


	int getIndexInPriorityQueue(vector<MyState*> myState, MyState* newState){
		int tempI = 0;
		for(int i=0;i<myState.size();i++){
			if(myState.at(i)->cost < newState->cost){
				tempI = myState.at(i)->cost;
			}
		}
		return tempI;
	}
	void printVector(vector<int> v){
		for(int i=0;i<v.size();i++){
			cout<<v[i]<<" ";
		}
		cout<<endl;
	}

	void printStringVector(vector<string> v){
		for(int i=0;i<v.size();i++){
			cout<<v[i]<<endl;
		}
	}

	vector<string> djakstra(){
		vector<int> curr_state;
		vector<int> goalState;
		vector<string> stringSequence = strings;
		int step = 0;
		for(int i=0;i<stringSequence.size();i++){
			curr_state.push_back(0);
			goalState.push_back(stringSequence.at(i).size());
		}
		printVector(curr_state);
		printVector(goalState);

		// vector<MyState*> stateVisited;
		// return stringSequence;
		vector<MyState*> priority_queue;
		vector<int> level;
		MyState* tempState = new MyState();
		// stateVisited.push_back(curr_state);
		tempState->state = curr_state;
		tempState->orientation = stringSequence;
		tempState->cost = 0;
		priority_queue.push_back(tempState);
		level.push_back(0);
		vector<int> tempInsertState;
		vector<vector<int> > tempChildren;
		int tempLevel;
		int tempCost;
		int dashInsertCost = 0;
		int tempIndex;
		int final_cost = 10000;
		vector<int> a;
		while(priority_queue.size() != 0){
			tempState = priority_queue.at(priority_queue.size() - 1);
			tempLevel = level.at(level.size() - 1);
			tempCost = tempState->cost;
			// cout<<tempCost;
			// return stringSequence;
			tempChildren = childrenState(tempState->state, goalState);
			// return stringSequence;
			// for(int k=0;k<tempChildren.size();k++){
			// 	for(int l=0;l<tempChildren[k].size();l++){
			// 		cout<<tempChildren[k][l]<<" ";
			// 	}
			// 	cout<<endl;
			// }
			//Done debugging till this point!
			if(twoVectorsEqual(tempState->state, goalState)){
				if(final_cost > tempState->cost){
					final_cost = tempState->cost;
					stringSequence = tempState->orientation;
				}
				continue;
			}
			// return stringSequence;


			for(int i=0;i<tempChildren.size();i++){
				tempInsertState = tempChildren[i];
				printVector(tempInsertState);
				MyState* newState;
				newState->state = tempInsertState;
				newState->cost = computeStepCost(tempState->state, tempInsertState, tempState->orientation, tempLevel + 1);
				// cout<<newState->cost<<endl;
				// return stringSequence;
				printVector(tempState->state);
				printVector(tempInsertState);
				printStringVector(tempState->orientation);
				vector<string> tempOrientation1(getNextOrientation(tempState->state, tempInsertState, tempLevel, tempState->orientation));
				newState->orientation;
				// newState->orientation = getNextOrientation(tempState->state, tempInsertState, tempLevel, tempState->orientation);
				printStringVector(newState->orientation);
				return stringSequence;
				// if(isStatePresent(stateVisited, tempInsertState) == -1){
				// stateVisited.push_back(newState);
				tempIndex = getIndexInPriorityQueue(priority_queue, newState);
				priority_queue.insert(priority_queue.begin() + tempIndex, newState);
				level.insert(level.begin() + tempIndex, tempLevel + 1);
				// }
				// else{
				// 	int tempIndex1 = isStatePresent(stateVisited, tempInsertState);
				// 	if(stateVisited[tempIndex1]->cost > newState->cost){
				// 		stateVisited[tempIndex1]->cost = newState->cost;
				// 		stateVisited[tempIndex1]->orientation = newState->orientation;
				// 		for(int i=0;i<priority_queue.size();i++){
				// 			if(twoVectorsEqual(priority_queue.at(i)->state, newState->state)){
				// 				priority_queue.at(i)->cost = newState->cost;
				// 				priority_queue.at(i)->orientation = newState->orientation;
				// 			}
				// 		}
				// 	}
				// }
			}
			priority_queue.pop_back();
			level.pop_back();		
		}
		return stringSequence;
	}

	// reduces extra '-'s in the brute force adjusted strings
	vector<string> reduceBruteDividedString(vector<string> bruteDividedStrings) {
		bool flag = 0;
		for (int i = 0; i < bruteDividedStrings[0].size(); i++) {
			flag = 0;
			for (int j = 0; j < bruteDividedStrings.size(); j++) {
				if (bruteDividedStrings[j][i] != '-') {
					flag = 1;
				}
			}
			if (!flag) {
				for (int k = 0; k < bruteDividedStrings.size(); k++) {
					bruteDividedStrings[k].erase(bruteDividedStrings.at(k).begin() + i);
					i--;
				}
			}
		}
		return bruteDividedStrings;
	}

	// compute cost between two equal length strings
	int computeCost(string equiLengthStr1, string equiLengthStr2) {
		if (equiLengthStr1.size() != equiLengthStr2.size()) {
			cerr << "Length Not Same!" << endl;
		}
		int answer = 0;
		int index1, index2;
		for (int i = 0; i < equiLengthStr1.size(); i++) {
			if (equiLengthStr1.at(i) = 'A') {
				index1 = 0;
			}
			if (equiLengthStr1.at(i) = 'C') {
				index1 = 1;
			}
			if (equiLengthStr1.at(i) = 'T') {
				index1 = 2;
			}
			if (equiLengthStr1.at(i) = 'G') {
				index1 = 3;
			}
			if (equiLengthStr1.at(i) = '-') {
				index1 = 4;
			}
			if (equiLengthStr2.at(i) = 'A') {
				index2 = 0;
			}
			if (equiLengthStr2.at(i) = 'C') {
				index2 = 1;
			}
			if (equiLengthStr2.at(i) = 'T') {
				index2 = 2;
			}
			if (equiLengthStr2.at(i) = 'G') {
				index2 = 3;
			}
			if (equiLengthStr2.at(i) = '-') {
				index2 = 4;
			}
			answer = answer + costMap.at(index1).at(index2);
		}
	}


	//computes the total cost of a set of characters represented in the string
	int computeCostString(string str) {
		int answer = 0;
		int index1 = -1;
		int index2 = -1;

		//adding up conversion costs;
		for (int i = 0; i < k; i++)
		{
			if (str[i] == '-')
				answer += cc;
		}

		//adding up matching costs
		for (int i = 0; i < k; i++) {
			index1 = findInVocabulary(str[i]);
			for (int j = i+1; j < k; j++) {

				index2 = findInVocabulary(str[j]);
				answer = answer + costMap[index1][index2];
			}
		}

		return answer;
	}

	// minimizes the total cost by greedy local search
	//vector<string> minimumCost() {
	void minimumCost()
	{
		vector<string> tempVector = strings;
		int maxLength = 0;
		for (int i = 0; i < tempVector.size(); i++) {
			if (maxLength < tempVector.at(i).size()) {
				maxLength = tempVector.at(i).size();
			}
		}

		string tempString;
		int tempCost;
		int tempNum;
		string tempBest;
		string str2;

		for (int i = 0; i < maxLength; i++) {
			tempString = "";
			for (int j = 0; j < tempVector.size(); j++) {
				
				if (tempVector.at(j).size() > i) {
					tempString = tempString + tempVector.at(j).at(i);
				}
				else
					tempString += '-';
			}

			tempCost = computeCostString(tempString);
			tempBest = tempString;
			tempNum = pow(2, tempString.size());

			for (int j = 0; j < tempNum - 1; j++) {
				str2 = "";
				string s = convertNumberToBinary(j, k);
				for (int l = 0; l < s.size(); l++) {
					if (s.at(l) == '1') {
						str2 = str2 + "-";
					}
					else {
						str2 = str2 + tempString[l];
					}
				}

				int cost = computeCostString(str2);
				if (cost < tempCost) {
					tempBest = str2;
					tempCost = cost;
				}
			}

			/*int index = 0;
			for (int j = 0; j < tempVector.size(); j++) {
				if (tempVector.at(j).size() > i) {
					tempVector.at(j).insert(tempVector.at(j).begin() + i, tempBest.at(index));
					index++;
				}
			}*/
			// updating the main vector of strings now (the copy recorded in the function)
			for (int j = 0; j < k; j++){
				if (tempBest[j] == '-'){
					tempVector[j].insert(tempVector[j].begin() + i, '-');
				}
			}
		}
		//return tempVector;

		strings = tempVector;
	}
};

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
	vector<string> answer = genes->djakstra();
	for(int i=0;i<answer.size();i++){
		cout<<answer[i]<<endl;
	}


	//TODO Handle # input ?
	return 0;
}
