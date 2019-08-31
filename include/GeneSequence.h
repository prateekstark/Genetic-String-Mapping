#include "UCSState.h"
#include "HillClimbingState.h"

extern time_t startingTime, currentTime;
extern int timeLimit;
extern vector<string> answerReport;
extern int costReport;



class GeneSequence{
public:
	vector<string> strings;
	vector<vector<int> > costMap;
	vector<char> vocabulary;
	int cc;
	int k;
	int vsize;
	// constructor
	GeneSequence(int vocSize, vector<char> vocab, int kin, vector<string> stringSequence, int ccin, vector<vector<int> > inputCostMap);

	// prints the saved costmap
	void printCostMap();

	// finds the character index in the vocabulary
	int findInVocabulary(char c);

	// inserts a new string in the main string vector
	void insertString(string str);

	// appends extra '-'s at each string to reach max length
	vector<string> balanceStrings(vector<string> str);

	// adds 3 '-'s for each character in the string to inculcate all the cases
	vector<string> bruteForceDivide(vector<string> balancedStrings);

    // Computing cost of next step... parentCost will not be counted..
	int computeStepCost(vector<int> initialState, vector<int> finalState, vector<string> initialOrientation, int step);

	//Given initial orienation, initial state and the final state we find the next orientation

	vector<string> getNextOrientation(vector<int> initialState, vector<int> finalState, int step, vector<string> initialOrientation);
    //In a vector of states, is a particular state present?
	int isStatePresent(vector<UCSState*> stateSequence, vector<int> key_state);

	//is stack(vector) present in hay(vector<vector<int> > v)
	bool isHayPresentInStack(vector<int> hay, vector<vector<int> > stack);

	//Generating children states
	vector<vector<int> > childrenState(vector<int> curr_state, vector<int> goalState);

    //If elements in priority queue are arranged in Decreasing cost and we want to add an element, there where will it add.
	int getIndexInPriorityQueue(vector<UCSState*> myUCSState, UCSState* newState);

    //Implementing Djakstra
	vector<string> djakstra();

	// reduces extra '-'s in the brute force adjusted strings
	vector<string> reduceBruteDividedString(vector<string> bruteDividedStrings);

	vector<string> insertDashAtLast(vector<string> v);

	vector<string> hillClimbingOneIter(vector<string> myStrings);

	vector<string> hillClimbing();

	// compute cost between two equal length strings
	int computeCost(string equiLengthStr1, string equiLengthStr2);

	int computeCostVector(vector<string> v);

	//computes the total cost of a set of characters represented in the string
	int computeCostString(string str);

	// minimizes the total cost by greedy local search
	void minimumCost();

	int stateCost(HillClimbingState state);

	HillClimbingState generateChild(HillClimbingState parent, int num, int maxlen);

	HillClimbingState randomState(HillClimbingState startState);

	int localSearch(HillClimbingState startState, int longestLength);

	int computeCostVectorModified(vector<string> v);

	vector<string> hillClimbingVectorOneIter(vector<string> myStrings);

	vector<string> hillClimbingVector();

	vector<string> addDashRandom(vector<string> v);

	vector<string> beamSearch();

	vector<string> hillClimbingVectorLimit(vector<string> myStrings);

	bool twoSequenceEqual(vector<string> s1, vector<string> s2);

	HillClimbingState GeneSequencerandomState(HillClimbingState startState);

	bool checkDead(HillClimbingState state);

	int maxStringLength(vector<string> v);

	vector<vector<string> > generateHillClimbingVectorBest(vector<string> myStrings);

	vector<string> generateLocalMinima(vector<string> myStrings);

};
