#include "../include/GeneSequence.h"

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
	int tempStepCost;
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
			tempStepCost = computeStepCost(tempState->state, tempInsertState, tempState->orientation, tempLevel + 1);
			if(tempStepCost <= final_cost){
				newState = new UCSState(tempInsertState, getNextOrientation(tempState->state, tempInsertState, tempLevel, tempState->orientation), tempStepCost);
				tempIndex = getIndexInPriorityQueue(priority_queue, newState);
				priority_queue.insert(priority_queue.begin() + tempIndex, newState);
				level.insert(level.begin() + tempIndex, tempLevel + 1);
			}
			// printStringVector(newState->orientation);
		}
		priority_queue.pop_back();
		level.pop_back();
	}
	printStringVector(stringSequence);
	return stringSequence;
}
