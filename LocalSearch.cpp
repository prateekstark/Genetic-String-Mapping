#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
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


class MyState {
public:
	vector<string> orientation;
	//vector<int> lengths;

	MyState()
	{
		/*for (string s : orientation)
			lengths.push_back(s.size());*/
	}

	MyState(vector<string> curr_orientation) {
		this->orientation = curr_orientation;
		/*for (string s : orientation)
			lengths.push_back(s.size());*/
	}
};



class GeneSequence {
public:
	vector<string> strings;
	vector<vector<int> > costMap;
	vector<char> vocabulary;
	int cc;
	int k = 0;
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
	int findInVocabulary(char c) {
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


	bool twoVectorsEqual(vector<int> v1, vector<int> v2) {
		if (v1.size() == v2.size()) {
			for (int i = 0; i < v1.size(); i++) {
				if (v1.at(i) != v2.at(i)) {
					return 0;
				}
			}
			return 1;
		}
		return 0;
	}

	void printVector(vector<int> v) {
		for (int i = 0; i < v.size(); i++) {
			cout << v[i] << " ";
		}
		cout << endl;
	}

	void printStringVector(vector<string> v) {
		for (int i = 0; i < v.size(); i++) {
			cout << v[i] << endl;
		}
	}

	//computes the total cost of a set of characters represented in the string
	int computeCostString(string str) {
		int answer = 0;
		int index1 = -1;
		int index2 = -1;
		bool allDashes = true;

		//adding up conversion costs;
		for (int i = 0; i < k; i++)
		{
			if (str[i] == '-')
				answer += cc;
			else
				allDashes = false;
		}

		// if (allDashes)
		// 	return -1;

		//adding up matching costs
		for (int i = 0; i < k; i++) {
			index1 = findInVocabulary(str[i]);
			for (int j = i + 1; j < k; j++) {

				index2 = findInVocabulary(str[j]);
				answer = answer + costMap[index1][index2];
			}
		}

		return answer;
	}

	int stateCost(MyState state)
	{
		int cost = 0;
		vector<int> lengths;
		int maxlength = 0;

		for (string s : state.orientation)
		{
			lengths.push_back(s.size());
			if (s.size() > maxlength)
				maxlength = s.size();
		}

		for (int i = 0; i < maxlength; i++)
		{
			string posString;

			for (int j = 0; j < k; j++)
			{
				if (lengths[j] - 1 < i)
				{
					posString.push_back('-');
				}
				else
				{
					posString.push_back(state.orientation[j][i]);
				}
			}
			int stringCost = computeCostString(posString);

			// if (stringCost == -1)
			// 	return -1;

			cost += stringCost;
		}

		return cost;
	}


	MyState generateChild(MyState parent, int num)
	{
		int i = 0;
		for (i = 0; i < k; i++)
		{
			if (parent.orientation[i].size() < num)
				num = num - parent.orientation[i].size() - 1;
			else
				break;
		}

		MyState child(parent.orientation);
		child.orientation[i].insert(child.orientation[i].begin() + num, '-');

		return child;
	}


	MyState randomState(MyState startState)
	{
		MyState randState(startState.orientation);
		int len = randState.orientation.size();
		int maxlen = 0;

		for (int i = 0; i < len; i++)								// finding the maximum length
		{
			if (startState.orientation[i].size() > maxlen)
				maxlen = startState.orientation[i].size();
		}

		for (int i = 0; i < len; i++)
		{
			int numDashes = rand() % (maxlen - randState.orientation[i].size() + 2);			//random number of dashes with relation
																								//to the string length
			for (int j = 0; j < numDashes; j++)													// inserting them at rand positions
			{
				int randomPos = rand() % (randState.orientation[i].size() + 1);
				randState.orientation[i].insert(randState.orientation[i].begin() + randomPos, '-');
			}
		}

		return randState;
	}


	int localSearch(MyState startState)
	{
		MyState parent = startState;

		//int childCost = stateCost(child);

		MyState child;
		MyState globalMinChild = startState;

		int globalMinCost = -1;

		for (long long x = 0; x < 1000; x++)
		{
			int minCost = -1;
			bool minimaFound = false;
			while (!minimaFound)
			{
				minimaFound = true;
				int minChildIndex = -1;
				minCost = stateCost(parent);
				MyState minChild;

				int sumLengths = 0;
				for (string s : parent.orientation)
					sumLengths += s.size() + 1;

				for (int i = 0; i < sumLengths; i++)
				{
					child = generateChild(parent, i);
					int childCost = stateCost(child);

					if (childCost <= minCost)
					{
						//cout << "Lower cost found: " << endl;
						//printStringVector(child.orientation);
						// cout << "Cost: " << childCost << endl;
						minChildIndex = i;
						minChild = child;
						minCost = childCost;
						minimaFound = false;
					}
				}

				if (minChildIndex != -1)
					parent = minChild;
			}

			if (minCost < globalMinCost || globalMinCost == -1)
			{
				globalMinChild = parent;
				globalMinCost = minCost;

				cout << "New minima converged at --" << endl;
				printStringVector(parent.orientation);
				cout << "Cost: " << globalMinCost << endl << endl;
			}

			parent = randomState(startState);

			// cout << "Starting randomly with --" << endl;
			// printStringVector(parent.orientation);
			// cout << endl;
		}

		return globalMinCost;
	}
};

int main() {

	time_t timestart, timeend;
	time(&timestart);

	int vsize, k, cc, i, j;
	float timeLimit;
	string tempString;
	vector<string> myStrings;
	vector<vector<int> > costMap;
	vector<int> goalTuple;
	vector<int> zeroTuple;

	cin >> timeLimit;											// input for the time limit of the runtime of the code

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

	GeneSequence* genes = new GeneSequence(vsize + 1, myVocabulary, k, myStrings, cc, costMap);
	MyState startState(myStrings);

	int finalCost1 = genes->localSearch(startState);

	for (int i = 0; i < k; i++)
		reverse(startState.orientation[i].begin(), startState.orientation[i].end());

	int finalCost2 = genes->localSearch(startState);

	cout << "Forward final cost: " << finalCost1 << endl;
	cout << "Backward final cost: " << finalCost2 << endl;

	time(&timeend);
	cout << "Time taken: " << double(timeend - timestart) << setprecision(5) << "s" << endl;


	return 0;
}
