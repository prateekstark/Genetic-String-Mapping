#include "Helper.h"
class UCSState{
public:
	vector<int> state;
	vector<string> orientation;
	int cost;

    UCSState();

    UCSState(vector<int> curr_state, vector<string> curr_orientation, int curr_cost);
};
