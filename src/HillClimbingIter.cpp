#include "../include/GeneSequence.h"

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
