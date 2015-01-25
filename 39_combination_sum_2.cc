//non iterative solution (faster)
class Solution {
public:
	vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
		vector<vector<int> > ret;
		if(candidates.empty()) return ret;
		
		vector<int> sorted = sort(candidates);
	
		//maximum possible numbers target/ min(sorted)
		int n = sorted.size();
		int csize = std::ceil(target/sorted[0]); //no zero!
		vector<int> choice(csize, -1); //stores the indices of a solution in sorted array
		int k = 0; // the k-th number
		int sum = 0; // accumulated sum
		while(k >= 0) {
			if(k == csize) { // target > sums
				k--;
				continue;
			}
			if(choice[k] == -1) { //first time for k-th number
				choice[k] = ((k > 0) ? choice[k-1] : 0); //start from same number before
			} else { //not the first time
				int prev = sorted[choice[k]];
				sum -= prev; //remove sum
				choice[k] ++;
			}
		
			if(choice[k] == n) { // searched till the end
			    choice[k] = -1; //reset
				k--;
				continue;
			}
			//found one
			sum += sorted[choice[k]]; //update sum
			
			//sum exceeding or equal to target
			if(sum >= target) {
				if(sum == target) ret.push_back(construct(choice, sorted));
				sum -= sorted[choice[k]];
				choice[k] = -1;
				k--;
			} else { //check next number
				k++;
			}
		}
		return ret;
	}
	
	//construct vector from choices
	vector<int> construct(const vector<int>& choice, const vector<int>& sorted) {
		vector<int> ret;
		for(int j = 0; j < choice.size(); ++j) {
			if(choice[j] != -1) ret.push_back(sorted[choice[j]]);
			else break; //can break if found an invalid -1 entry
		}
	return ret;
	}
	//insertion sort
	vector<int> sort(vector<int>& num) {
		vector<int> sorted = num;
		int n = sorted.size();
		int i, j;
		for(i = 1; i < n; ++i) {
			j = i;
			int key = sorted[j];
			while( j >= 1 && sorted[j-1] > key) {
				sorted[j] = sorted[j-1]; //shift to right by 1
				j--;
			}
			sorted[j] = key;
		}
		return sorted;
	}
};
