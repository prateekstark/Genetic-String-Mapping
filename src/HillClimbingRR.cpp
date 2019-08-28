#include "../include/GeneSequence.h"

int GeneSequence::stateCost(HillClimbingState state){
    int cost = 0;
    vector<int> lengths;
    int maxlength = 0;
    for (string s : state.orientation){
        lengths.push_back(s.size());
        if (s.size() > maxlength)
            maxlength = s.size();
    }

    for (int i = 0; i < maxlength; i++){
        string posString;
        for (int j = 0; j < k; j++){
            if (lengths[j] - 1 < i){
                posString.push_back('-');
            }
            else{
                posString.push_back(state.orientation[j][i]);
            }
        }
        int stringCost = computeCostString(posString);

        cost += stringCost;
    }

    return cost;
}


HillClimbingState GeneSequence::generateChild(HillClimbingState parent, int num){
    int i;
    for(i = 0; i < this->k; i++){
        if (parent.orientation[i].size() < num){
            num = num - parent.orientation[i].size() - 1;
        }
        else{
            break;
        }
    }
    HillClimbingState child(parent.orientation);
    child.orientation[i].insert(child.orientation[i].begin() + num, '-');
    return child;
}


HillClimbingState GeneSequence::randomState(HillClimbingState startState){
    HillClimbingState randState(startState.orientation);
    int len = randState.orientation.size();
    int maxlen = 0;
    for (int i = 0; i < len; i++){								// finding the maximum length
        if (startState.orientation[i].size() > maxlen)
            maxlen = startState.orientation[i].size();
    }
    for (int i = 0; i < len; i++){
        int numDashes = rand() % (maxlen - randState.orientation[i].size() + 2);			//random number of dashes with relation
                                                                                            //to the string length
        for (int j = 0; j < numDashes; j++){													// inserting them at rand positions
            int randomPos = rand() % (randState.orientation[i].size() + 1);
            randState.orientation[i].insert(randState.orientation[i].begin() + randomPos, '-');
        }
    }
    return randState;
}


int GeneSequence::localSearch(HillClimbingState startState){
    HillClimbingState parent = startState;

    HillClimbingState child;
    HillClimbingState globalMinChild = startState;

    int globalMinCost = -1;

    for (long long x = 0; x < 1000; x++){
        int minCost = -1;
        bool minimaFound = false;
        while (!minimaFound){
            minimaFound = true;
            int minChildIndex = -1;
            minCost = stateCost(parent);
            HillClimbingState minChild;
            int sumLengths = 0;
            for (string s : parent.orientation)
                sumLengths += s.size() + 1;

            for (int i = 0; i < sumLengths; i++){
                child = generateChild(parent, i);
                int childCost = stateCost(child);

                if (childCost <= minCost){
                    //cout << "Lower cost found: " << endl;
                    //printStringVector(child.orientation);
                    // cout << "Cost: " << childCost << endl;
                    minChildIndex = i;
                    minChild = child;
                    minCost = childCost;
                    minimaFound = false;
                }
            }

            if (minChildIndex != -1){
                parent = minChild;
            }
        }

        if (minCost < globalMinCost || globalMinCost == -1){
            globalMinChild = parent;
            globalMinCost = minCost;
            cout << "New minima converged at --" << endl;
            printStringVector(parent.orientation);
            cout << "Cost: " << globalMinCost << endl << endl;
        }

        parent = randomState(startState);
    }
    return globalMinCost;
}
