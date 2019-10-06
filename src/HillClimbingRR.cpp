#include "../include/GeneSequence.h"

extern bool answerReverse;
extern bool reversed;


int GeneSequence::stateCost(HillClimbingState state){
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
        //  return -1;

        cost += stringCost;
    }

    return cost;
}
HillClimbingState GeneSequence::generateChild(HillClimbingState parent, int num, int maxlen){
    bool isValid = true;
    int i = 0;
    for (i = 0; i < k; i++)
    {
        if (parent.orientation[i].size() < num)
            num = num - parent.orientation[i].size() - 1;
        else
            break;
    }

    HillClimbingState child(parent.orientation);
    if(child.orientation[i].size() == maxlen && num == maxlen)
        isValid = false;
    child.orientation[i].insert(child.orientation[i].begin() + num, '-');

    return child;
}

int GeneSequence::maxStringLength(vector<string> v){
    int maxlen = 0;
    for(int i=0 ; i<v.size() ; i++)
    {
        if(v[i].size() > maxlen)
            maxlen = v[i].size();
    }
    return maxlen;
}



bool GeneSequence::checkDead(HillClimbingState state){
    int maxlen = maxStringLength(state.orientation);
    for(int i=0 ; i<state.orientation.size() ; i++)
    {
        if(state.orientation[i].size() == maxlen)
        {
            if(state.orientation[i][state.orientation[i].size() - 1] == '-')
                return true;
        }
    }
    return false;
}

HillClimbingState GeneSequence::randomState(HillClimbingState startState){
    HillClimbingState randState(startState.orientation);
    int len = randState.orientation.size();
    int maxlen = maxStringLength(startState.orientation);

    for (int i = 0; i < len; i++)
    {
        int numDashes = rand() % (maxlen - randState.orientation[i].size() + 2);            //random number of dashes with relation
                                                                                            //to the string length
        for (int j = 0; j < numDashes; j++)                                                 // inserting them at rand positions
        {
            int randomPos = rand() % (randState.orientation[i].size() + 1);
            randState.orientation[i].insert(randState.orientation[i].begin() + randomPos, '-');
        }
    }

    return randState;
}

int GeneSequence::localSearch(HillClimbingState startState, int longestLength){
    HillClimbingState parent = startState;

    //int childCost = stateCost(child);

    HillClimbingState child;
    HillClimbingState globalMinChild = startState;

    int globalMinCost = -1;

    for (long long x = 0; x < 4000; x++)
    {
        int minCost = -1;
        bool minimaFound = false;
        while (!minimaFound)
        {
            minimaFound = true;
            int minChildIndex = -1;
            minCost = stateCost(parent);
            HillClimbingState minChild;
            int sidewaysMoves = 10;

            int sumLengths = 0;
            int deadend = -1;
            int maxlen = 0;
            for (string s : parent.orientation)
            {
                sumLengths += s.size() + 1;
                if(s.size()>maxlen)
                {
                    maxlen = s.size();
                }
            }

            for (int i = 0; i < sumLengths ; i++)
            {
                // pair<HillClimbingState,bool> childPair = generateChild(parent, i, maxlen);
                // child = childPair.first;
                // if(!childPair.second)
                //  continue;
                child = generateChild(parent, i, maxlen);
                if(checkDead(child))
                    continue;

                int childCost = stateCost(child);

                if (childCost < minCost && maxStringLength(child.orientation) <= longestLength && sidewaysMoves > 0)
                {
                    // cout << "Lower cost found: " << endl;
                    // printStringVector(child.orientation);
                    // cout << "Cost: " << childCost << endl;
                    if(childCost == minCost)
                        sidewaysMoves--;
                    minChildIndex = i;
                    minChild = child;
                    minCost = childCost;
                    minimaFound = false;
                    if (minCost < globalMinCost || globalMinCost == -1)
                    {
                        globalMinChild = parent;
                        globalMinCost = minCost;
                        if(globalMinCost < costReport || costReport == -1)
                        {
                            costReport = globalMinCost;
                            answerReport = globalMinChild.orientation;
                            if(reversed){
                                answerReverse = 1;
                            }
                            else{
                                answerReverse = 0;
                            }
                        }
                    }
                    time(&currentTime);
                    if((int)(currentTime - startingTime) >= timeLimit)
                        return globalMinCost;
                }
            }

            if (minChildIndex != -1)
                parent = minChild;
        }

        if (minCost < globalMinCost || globalMinCost == -1)
        {
            globalMinChild = parent;
            globalMinCost = minCost;
            if(globalMinCost < costReport || costReport == -1)
            {
                costReport = globalMinCost;
                answerReport = globalMinChild.orientation;
                if(reversed){
                    answerReverse = 1;
                }
                else{
                    answerReverse = 0;
                }
            }

            // cout << "New minima converged at --" << endl;
            // printStringVector(parent.orientation);
            // cout << "Cost: " << globalMinCost << endl << endl;
        }
        parent = randomState(startState);

    }

    return globalMinCost;
}