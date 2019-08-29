#include "../include/Helper.h"


string convertNumberToBinary(int n, int len){
	string answer = "";
	while (n != 0) {
		answer = to_string(n%2) + answer;
		n = n/2;
	}

	while (answer.size() < len)
		answer = '0' + answer;

	return answer;
}

string convertNumberToBinarySimple(int n){
	string answer = "";
	while (n != 0) {
		answer = to_string(n%2) + answer;
		n = n/2;
	}
	return answer;
}

//Returns true if two vectors are equal
bool twoVectorsEqual(vector<int> v1, vector<int> v2){
	if(v1.size() == v2.size()){
		for(int i=0;i<v1.size();i++){
			if(v1.at(i) != v2.at(i)){
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

//Printing an <int> vector and a <string> vector
void printVector(vector<int> v){
	for(int i=0;i<v.size();i++){
		cout<<v[i]<<" ";
	}
	cout<<endl;
}

void printStringVector(vector<string> v){
	for(int i=0;i<v.size();i++){
		cout<<v[i]<<endl;
	}
}
