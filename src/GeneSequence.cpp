#include "../include/GeneSequence.h"

// constructor
GeneSequence::GeneSequence(int vocSize, vector<char> vocab, int kin, vector<string> stringSequence, int ccin, vector<vector<int> > inputCostMap) {
	this->strings = stringSequence;
	this->costMap = inputCostMap;
	this->vocabulary = vocab;
	this->cc = ccin;
	this->k = kin;
	this->vsize = vocSize;

}

// prints the saved costmap
void GeneSequence::printCostMap() {
	for (int i = 0; i < costMap.size(); i++) {
		for (int j = 0; j < costMap[0].size(); j++) {
			cout << costMap[i][j] << " ";
		}
		cout << endl;
	}
}

// finds the character index in the vocabulary
int GeneSequence::findInVocabulary(char c){
	for (int i = 0; i < vsize; i++)
	{
		if (vocabulary[i] == c)
			return i;
	}
	return -1;
}

// inserts a new string in the main string vector
void GeneSequence::insertString(string str) {
	strings.push_back(str);
}

// appends extra '-'s at each string to reach max length
vector<string> GeneSequence::balanceStrings(vector<string> str){
	int maxStringSize = 0;
	for (int i = 0; i < str.size(); i++){
		if (str[i].size() > maxStringSize){
			maxStringSize = str[i].size();
		}
	}
	for(int i = 0; i < str.size(); i++){
		if(str[i].size() < maxStringSize){
			while (str[i].size() != maxStringSize){
				str[i] = str[i] + "-";
			}
		}
	}
	return str;
}

// adds 3 '-'s for each character in the string to inculcate all the cases
vector<string> GeneSequence::bruteForceDivide(vector<string> balancedStrings) {
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

// Computing cost of next step... parentCost will not be counted..
int GeneSequence::computeStepCost(vector<int> initialState, vector<int> finalState, vector<string> initialOrientation, int step){
	int answer = 0;
	string tempString = "";
	vector<string> tempOrientation = getNextOrientation(initialState, finalState, step - 1 , initialOrientation);
	int tempDash = 0;
	for(int j=0;j<step;j++){
		tempString = "";
		tempDash = 0;
		for(int i=0;i<tempOrientation.size();i++){
			tempString = tempString + tempOrientation[i][j];
			if(tempOrientation[i][j] == '-'){
				tempDash++;
			}
		}
		answer = answer + computeCostString(tempString) + (tempDash*cc);
	}
	return answer;
}

//Given initial orienation, initial state and the final state we find the next orientation
vector<string> GeneSequence::getNextOrientation(vector<int> initialState, vector<int> finalState, int step, vector<string> initialOrientation){
	vector<string> tempOrientation = initialOrientation;
	for(int i=0;i<tempOrientation.size();i++){
		if(finalState[i] - initialState[i] != 1){
			tempOrientation[i].insert(tempOrientation[i].begin() + step, '-');
		}
	}
	return tempOrientation;
}

//In a vector of states, is a particular state present?
int GeneSequence::isStatePresent(vector<UCSState*> stateSequence, vector<int> key_state){
	for(int i=0;i<stateSequence.size();i++){
		if(twoVectorsEqual(stateSequence.at(i)->state, key_state)){
			return i;
		}
	}
	return -1;
}

//is stack(vector) present in hay(vector<vector<int> > v)
bool GeneSequence::isHayPresentInStack(vector<int> hay, vector<vector<int> > stack){
	for(int i=0;i<stack.size();i++){
		if(twoVectorsEqual(stack[i], hay)){
			return 1;
		}
	}
	return 0;
}

//Generating children states
vector<vector<int> > GeneSequence::childrenState(vector<int> curr_state, vector<int> goalState){
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

//If elements in priority queue are arranged in Decreasing cost and we want to add an element, there where will it add.
int GeneSequence::getIndexInPriorityQueue(vector<UCSState*> myUCSState, UCSState* newState){
	int tempI = 0;
	for(int i=0;i<myUCSState.size();i++){
		if(myUCSState.at(i)->cost < newState->cost){
			tempI = i;
		}
	}
	return tempI;
}

//Implementing Djakstra
vector<string> GeneSequence::djakstra(){
	vector<int> curr_state;
	vector<int> goalState;
	vector<string> stringSequence = strings;
	int step = 0;
	for(int i=0;i<stringSequence.size();i++){
		curr_state.push_back(0);
		goalState.push_back(stringSequence.at(i).size());
	}

	vector<UCSState*> priority_queue;
	vector<int> level;
	UCSState* tempState = new UCSState();
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
	UCSState* newState;
	vector<int> a;
	while(priority_queue.size() != 0){
		tempState = priority_queue.at(priority_queue.size() - 1);
		tempLevel = level.at(level.size() - 1);
		tempCost = tempState->cost;
		tempChildren = childrenState(tempState->state, goalState);
		if(twoVectorsEqual(tempState->state, goalState)){
			// cout<<tempState->cost<<"iamgreat"<<endl;
			if(final_cost > tempState->cost){
				// cout<<"hello";
				final_cost = tempState->cost;
				cout<<final_cost<<endl;
				stringSequence = tempState->orientation;
			}
		}

		for(int i=0;i<tempChildren.size();i++){
			tempInsertState = tempChildren[i];
			// cout<<tempLevel<<" ";
			// printVector(tempInsertState);
			newState = new UCSState(tempInsertState, getNextOrientation(tempState->state, tempInsertState, tempLevel, tempState->orientation), computeStepCost(tempState->state, tempInsertState, tempState->orientation, tempLevel + 1));
			// printStringVector(newState->orientation);
			tempIndex = getIndexInPriorityQueue(priority_queue, newState);
			priority_queue.insert(priority_queue.begin() + tempIndex, newState);
			level.insert(level.begin() + tempIndex, tempLevel + 1);
		}
		priority_queue.pop_back();
		level.pop_back();
	}
	return stringSequence;
}

// reduces extra '-'s in the brute force adjusted strings
vector<string> GeneSequence::reduceBruteDividedString(vector<string> bruteDividedStrings) {
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


vector<string> GeneSequence::insertDashAtLast(vector<string> v){
	for(int i=0;i<v.size();i++){
		v.at(i) = v.at(i) + '-';
	}
	return v;
}

vector<string> GeneSequence::hillClimbingOneIter(vector<string> myStrings){
	vector<string> startSequence = myStrings;
	startSequence = this->balanceStrings(startSequence);
	int len = myStrings[0].size();
	int stepCost = computeCostVector(startSequence);
	int tempCost;
	int tempMinCost;
	int tempMinIndex;
	vector<string> tempStringVector = startSequence;
	bool flag = 0;
	for(int i=0;i<len;i++){
		tempMinCost = computeCostVector(startSequence);
		flag = 0;
		for(int j=0;j<startSequence.size();j++){
			if(startSequence.at(j).at(len-1) == '-'){
				tempStringVector = startSequence;
				tempStringVector.at(j) = tempStringVector.at(j).substr(0, tempStringVector.at(j).size() - 1);
				tempStringVector[j].insert(tempStringVector[j].begin() + i, '-');
				tempCost = computeCostVector(tempStringVector);
				if(tempCost < tempMinCost){
					flag = 1;
					tempMinCost = tempCost;
					tempMinIndex = j;
				}
			}
		}
		if(flag){
			// startSequence[tempMinIndex].erase(startSequence[tempMinIndex].end());
			startSequence.at(tempMinIndex) = startSequence.at(tempMinIndex).substr(0, startSequence.at(tempMinIndex).size() - 1);
			startSequence[tempMinIndex].insert(startSequence[tempMinIndex].begin() + i, '-');
		}
	}
	return startSequence;
}

vector<string> GeneSequence::hillClimbing(){
	vector<string> a;
	vector<string> startSequence = strings;
	startSequence = balanceStrings(startSequence);
	int tempCost = computeCostVector(startSequence);
	vector<string> answer;
	vector<string> tempAnswer;
	for(int i=0;i<100;i++){
		tempAnswer = hillClimbingOneIter(startSequence);
		if(computeCostVector(tempAnswer) < tempCost){
			tempCost = computeCostVector(tempAnswer);
			answer = tempAnswer;
		}
		startSequence = insertDashAtLast(startSequence);
	}
	cout<<"hello"<<endl;
	cout<<computeCostVector(answer)<<endl;
	return answer;
}

// compute cost between two equal length strings
int GeneSequence::computeCost(string equiLengthStr1, string equiLengthStr2) {
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

int GeneSequence::computeCostVector(vector<string> v){
	int tempCost = 0;
	string tempString = "";
	for(int i=0;i<v[0].size();i++){
		tempString = "";
		for(int j=0;j<v.size();j++){
			tempString = tempString + v[j][i];
		}
		tempCost = tempCost + computeCostString(tempString);
	}
	return tempCost;
}


//computes the total cost of a set of characters represented in the string
int GeneSequence::computeCostString(string str) {
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
void GeneSequence::minimumCost(){
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