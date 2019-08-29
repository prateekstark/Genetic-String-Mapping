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
			startSequence.at(tempMinIndex) = startSequence.at(tempMinIndex).substr(0, startSequence.at(tempMinIndex).size() - 1);
			startSequence[tempMinIndex].insert(startSequence[tempMinIndex].begin() + i, '-');
		}
	}
	return startSequence;
}

int GeneSequence::computeCostVectorModified(vector<string> v){
	int maxLen = 0;
	for(int i=0;i<v.size();i++){
		if(maxLen < v.at(i).size()){
			maxLen = v.at(i).size();
		}
	}

	for(int i=0;i<v.size();i++){
		while(v.at(i).size() != maxLen){
			v.at(i) = v.at(i) + '-';
		}
	}
	return computeCostVector(v);
}


vector<string> GeneSequence::hillClimbingVectorOneIter(vector<string> myStrings){
	vector<string> startSequence = myStrings;
	int stepCost = computeCostVectorModified(startSequence);
	vector<string> tempStringVector = startSequence;
	vector<string> tempMinVector = startSequence;
	for(int i=0;i<startSequence.size();i++){
		for(int j=startSequence.at(i).size();j>=0;j--){
			tempStringVector = startSequence;
			tempStringVector.at(i).insert(tempStringVector.at(i).begin() + j, '-');
			if(computeCostVectorModified(tempStringVector) < stepCost){
				tempMinVector = tempStringVector;
				stepCost = computeCostVectorModified(tempMinVector);
			}
		}
	}
	// printStringVector(tempMinVector);
	return tempMinVector;
}

bool GeneSequence::twoSequenceEqual(vector<string> s1, vector<string> s2){
	if(s1.size() != s2.size()){
		return 0;
	}
	for(int i=0;i<s1.size();i++){
		if(s1.at(i).size() != s2.at(i).size()){
			return 0;
		}
	}
	return 1;
}

vector<vector<string> > GeneSequence::generateHillClimbingVectorBest(vector<string> myStrings){
	vector<string> startSequence = myStrings;
	vector<string> tempSequence;
	vector<vector<string> > bestSequences;
	int stepCost = computeCostVectorModified(startSequence);
	for(int i=0;i<startSequence.size();i++){
		for(int j=0;j<startSequence.at(i).size();j++){
			tempSequence = startSequence;
			tempSequence.at(i).insert(tempSequence.at(i).begin() + j, '-');
			if(computeCostVectorModified(tempSequence) < stepCost){
				bestSequences.clear();
				bestSequences.push_back(tempSequence);
				stepCost = computeCostVectorModified(tempSequence);
			}
			else if(computeCostVectorModified(tempSequence) == stepCost){
				bestSequences.push_back(tempSequence);
			}
		}
	}
	return bestSequences;
}

vector<string> GeneSequence::generateLocalMinima(vector<string> myStrings){
	vector<string> startSequence = myStrings;
	vector<string> tempSequence;
	vector<vector<string> > bestStates;
	vector<vector<string> > tempBest;
	int tempCost1, tempCost2;
	int tempInt;
	for(int i=0;i<10;i++){
		tempInt = bestStates.size();
		for(int j=0;j<tempInt;j++){
			tempCost1 = computeCostVectorModified(bestStates.at(i));
			tempBest = generateHillClimbingVectorBest(bestStates.at(i));
			// if()
		}
	}
}




vector<string> GeneSequence::hillClimbingVectorLimit(vector<string> myStrings){
	vector<string> minSequence = myStrings;
	vector<string> startSequence = myStrings;
	minSequence = hillClimbingVectorOneIter(minSequence);
	while(!twoSequenceEqual(minSequence, startSequence)){
		startSequence = minSequence;
		minSequence = hillClimbingVectorOneIter(minSequence);
	}
	return minSequence;
}

vector<string> GeneSequence::addDashRandom(vector<string> v){
	int stringNumber;
	int stringIndex;
	vector<int> probability;
	int maxLen = 0;
	int sum = 0;
	for(int i=0;i<v.size();i++){
		probability.push_back(v.at(i).size());
		if(maxLen < v.at(i).size()){
			maxLen = v.at(i).size();
		}
	}
	// cout<<"Hello";
	for(int i=0;i<v.size();i++){
		probability[i] = maxLen - probability[i];
		sum = sum + probability[i];
		probability[i] = sum;
	}
	// for(int i=0;i<probability.size();i++){
	// 	cout<<probability[i]<<" ";
	if(sum == 0){
		return v;
	}
	int randomToss = rand()%sum;
	for(int i=0;i<v.size();i++){
		if(randomToss<probability[i]){
			stringNumber = i;
			break;
		}
	}
	stringIndex = rand()%(v.at(stringNumber).size());
	v.at(stringNumber).insert(v.at(stringNumber).begin() + stringIndex, '-');
	return v;
}

vector<string> GeneSequence::hillClimbingVector(){
	vector<string> startSequence = strings;
	vector<string> minSequence = strings;
	vector<string> tempSequence = strings;
	int tempMinCost = computeCostVectorModified(minSequence);
	vector<string> beam;
	for(int i=0;i<100;i++){
		tempSequence = hillClimbingVectorOneIter(minSequence);
		if(computeCostVectorModified(tempSequence) < tempMinCost){
			minSequence = tempSequence;
			tempMinCost = computeCostVectorModified(tempSequence);
		}
		minSequence = addDashRandom(minSequence);
	}
	cout<<computeCostVectorModified(minSequence)<<endl;
	printStringVector(balanceStrings(minSequence));
	return minSequence;
}

vector<string> GeneSequence::beamSearch(){
	vector<string> startSequence = strings;
	vector<string> minSequence = strings;
	int tempMinCost = computeCostVectorModified(minSequence);
	vector<vector<string> > beam;
	beam.push_back(startSequence);
	for(int i=0;i<23;i++){
		beam.push_back(addDashRandom(minSequence));
	}
	vector<string> tempSequence;
	int tempInt1, tempInt2, randomNumber;
	vector<string> tempVector;
	for(int i=0;i<2000;i++){
		for(int m=0;m<24;m++){
			tempSequence = hillClimbingVectorLimit(beam[m]);
			if(computeCostVectorModified(tempSequence) < tempMinCost){
				beam[m] = tempSequence;
			}
			else{
				for(int l=0;l<24;l++){
					beam.push_back(addDashRandom(beam[m]));
				}
			}
		}

		for(int j=0;j<12;j++){
			for(int l=j+1;l<beam.size();l++){
				tempInt1 = computeCostVectorModified(beam[j]);
				tempInt2 = computeCostVectorModified(beam[l]);
				if(tempInt1 > tempInt2){
					tempVector = beam[j];
					beam[j] = beam[l];
					beam[l] = tempVector;
				}
			}
		}
		for(int z=12;z<24;z++){
			randomNumber = rand()%(beam.size());
			if(randomNumber > 24){
				beam[z] = beam[randomNumber];
			}
			else{
				z--;
			}
		}

		while(beam.size() != 24){
			beam.pop_back();
		}
	}
	int minCost = computeCostVectorModified(beam[0]);
	int minIndex = 0;
	for(int i=0;i<24;i++){
		if(minCost > computeCostVectorModified(beam[i])){
			minCost = computeCostVectorModified(beam[i]);
			minIndex = i;
		}
	}
	cout<<minCost<<endl;
	printStringVector(balanceStrings(beam[minIndex]));
	return beam[minIndex];
}

vector<string> GeneSequence::hillClimbing(){
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
	// cout<<"hello"<<endl;
	cout<<computeCostVector(answer)<<endl;
	printStringVector(answer);
	return answer;
}
