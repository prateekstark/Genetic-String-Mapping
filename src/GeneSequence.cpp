#include "../include/GeneSequence.h"
//
// extern time_t startingTime, currentTime;
// extern int timeLimit;
// extern vector<string> answerReport;
// extern int costReport;


time_t startingTime, currentTime;
int timeLimit;
vector<string> answerReport;
int costReport = -1;
bool reversed = 0;
bool answerReverse = 0;

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
	for(int i = 0; i < k; i++){
		if (str[i] == '-')
			answer += cc;
	}

	//adding up matching costs
	for(int i = 0; i < k; i++){
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

	for(int i = 0; i < maxLength; i++) {
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
		for(int j = 0; j < tempNum - 1; j++) {
			str2 = "";
			string s = convertNumberToBinary(j, k);
			for(int l = 0; l < s.size(); l++) {
				if(s.at(l) == '1'){
					str2 = str2 + "-";
				}
				else{
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
