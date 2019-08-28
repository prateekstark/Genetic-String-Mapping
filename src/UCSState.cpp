#include "../include/UCSState.h"

UCSState::UCSState(){
	this->cost = 0;
}

UCSState::UCSState(vector<int> curr_state, vector<string> curr_orientation, int curr_cost){
	this->state = curr_state;
	this->orientation = curr_orientation;
	this->cost = curr_cost;
}
