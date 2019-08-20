#include<iostream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;

int totalCost(vector<string> strings, vector<vector<int> > costMap){

}

string convertNumberToBinary(int n){
    string answer = "";
    while(n != 0){
        answer = to_string(n%2) + answer;
        n = n/2;
    }
    return answer;
}

class GeneSequence{
public:
    vector<string> strings;
    vector<vector<int> > costMap;
    GeneSequence(vector<string> stringSequence, vector<vector<int> > inputCostMap){
        this->strings = stringSequence;
        this->costMap = inputCostMap;
    }

    void printStringVector(){
        for(int i=0;i<strings.size();i++){
            cout<<strings.at(i)<<endl;
        }
    }

    void printCostMap(){
        for(int i=0;i<costMap.size();i++){
            for(int j=0;j<costMap.at(0).size();j++){
                cout<<costMap.at(i).at(j)<<" ";
            }
            cout<<endl;
        }
    }

    void insertString(string str){
        strings.push_back(str);
    }

    void balanceString(){
        int maxStringSize = 0;
        for(int i=0;i<strings.size();i++){
            if(strings.at(i).size() > maxStringSize){
                maxStringSize = strings.at(i).size();
            }
        }
        for(int i=0;i<strings.size();i++){
            if(strings.at(i).size() < maxStringSize){
                while(strings.at(i).size() != maxStringSize){
                    strings.at(i) = strings.at(i) + "-";
                }
            }
        }
    }


    vector<string> bruteForceDivide(vector<string> balancedStrings){
        string tempString;
        vector<string> bruteDividedStrings;
        for(int i=0;i<balancedStrings.size();i++){
            tempString = "";
            for(int j=0;j<balancedStrings.at(i).size();j++){
                if(balancedStrings.at(i).at(j) == 'A'){
                    tempString = tempString + "A---";
                }
                if(balancedStrings.at(i).at(j) == 'B'){
                    tempString = tempString + "-B--";
                }
                if(balancedStrings.at(i).at(j) == 'C'){
                    tempString = tempString + "--C-";
                }
                if(balancedStrings.at(i).at(j) == 'D'){
                    tempString = tempString + "---D";
                }
            }
            bruteDividedStrings.push_back(tempString);
        }
        return bruteDividedStrings;
    }

    vector<string> reduceBruteDividedString(vector<string> bruteDividedStrings){
        bool flag = 0;
        for(int i=0;i<bruteDividedStrings.at(0).size();i++){
            flag = 0;
            for(int j=0;j<bruteDividedStrings.size();j++){
                if(bruteDividedStrings.at(j).at(i) != '-'){
                    flag = 1;
                }
            }
            if(!flag){
                for(int k=0;k<bruteDividedStrings.size();k++){
                    bruteDividedStrings.at(k).erase(bruteDividedStrings.at(k).begin()+i);
                    i--;
                }
            }
        }
        return bruteDividedStrings;
    }

    int computeCost(string equiLengthStr1, string equiLengthStr2){
        if(equiLengthStr1.size() != equiLengthStr2.size()){
            cerr<<"Length Not Same!"<<endl;
        }
        int answer = 0;
        int index1, index2;
        for(int i=0;i<equiLengthStr1.size();i++){
            if(equiLengthStr1.at(i) = 'A'){
                index1 = 0;
            }
            if(equiLengthStr1.at(i) = 'C'){
                index1 = 1;
            }
            if(equiLengthStr1.at(i) = 'T'){
                index1 = 2;
            }
            if(equiLengthStr1.at(i) = 'G'){
                index1 = 3;
            }
            if(equiLengthStr1.at(i) = '-'){
                index1 = 4;
            }
            if(equiLengthStr2.at(i) = 'A'){
                index2 = 0;
            }
            if(equiLengthStr2.at(i) = 'C'){
                index2 = 1;
            }
            if(equiLengthStr2.at(i) = 'T'){
                index2 = 2;
            }
            if(equiLengthStr2.at(i) = 'G'){
                index2 = 3;
            }
            if(equiLengthStr2.at(i) = '-'){
                index2 = 4;
            }
            answer = answer + costMap.at(index1).at(index2);
        }
    }



    int computeCostString(string str){
        int answer = 0;
        for(int i=0;i<n-1;i++){
            for(int j=i+1;j<n;j++){
                if(str.at(i) = 'A'){
                    index1 = 0;
                }
                if(str.at(i) = 'C'){
                    index1 = 1;
                }
                if(str.at(i) = 'T'){
                    index1 = 2;
                }
                if(str.at(i) = 'G'){
                    index1 = 3;
                }
                if(str.at(i) = '-'){
                    index1 = 4;
                }
                if(str.at(j) = 'A'){
                    index2 = 0;
                }
                if(str.at(j) = 'C'){
                    index2 = 1;
                }
                if(str.at(j) = 'T'){
                    index2 = 2;
                }
                if(str.at(j) = 'G'){
                    index2 = 3;
                }
                if(str.at(j) = '-'){
                    index2 = 4;
                }
            }
            answer = answer + costMap.at(index1).at(index2);
        }
    }

    vector<string> minimumCost(){
        vector<string> tempVector = strings;
        int maxLength = 0;
        for(int i=0;i<tempVector.size();i++){
            if(maxLength < tempVector.at(i).size()){
                maxLength = tempVector.at(i).size();
            }
        }
        string tempString;
        int tempCost;
        int tempNum;
        string tempBest;
        string str2;
        for(int i=0;i<maxLength;i++){
            tempString = "";
            for(int j=0;j<tempVector.size();j++){
                if(tempVector.at(j).size() > i){
                    tempString = tempString + tempVector.at(j).at(i);
                }
            }
            tempCost = computeCostString(tempString);
            tempNum = pow(2, tempString.size());
            for(int k=0;k<tempNum-1;k++){
                str2 = "";
                string s = convertNumberToBinary(tempNum);
                for(int l=0;l<tempString.size();l++){
                    if(tempString.at(l) == '1'){
                        str2 = str2 + "-";
                    }
                    else{
                        str2 = str2 + tempString.at(l);
                    }
                }
                if(computeCostString(str2) < tempCost){
                    tempBest = str2;
                    tempCost = computeCostString(str2);
                }
            }
            int index = 0;
            for(int j=0;j<tempVector.size();j++){
                if(tempVector.at(j).size() > i){
                    tempVector.at(j).insert(tempVector.at(j).begin() + i, tempBest.at(index));
                    index++;
                }
            }
        }
        return tempVector;
    }
};

int main(){
    int n, i, j;
    // GeneSequence* genes = new GeneSequence();
    string tempString;
    vector<string> myStrings;
    cin>>n;
    vector<vector<int> > costMap;
    for(i=0;i<n;i++){
        cin>>tempString;
        myStrings.push_back(tempString);
    }
    int tempInt;
    for(i=0;i<5;i++){
        vector<int> tempVector;
        for(j=0;j<5;j++){
            cin>>tempInt;
            tempVector.push_back(tempInt);
        }
        costMap.push_back(tempVector);
    }
    GeneSequence* genes = new GeneSequence(myStrings, costMap);
    genes->balanceString();
    genes->printStringVector();

    return 0;
}
