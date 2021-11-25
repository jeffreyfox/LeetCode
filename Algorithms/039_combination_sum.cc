/*
Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

Note:

    All numbers (including target) will be positive integers.
    Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
    The solution set must not contain duplicate combinations.

For example, given candidate set 2,3,6,7 and target 7,
A solution set is:
[7]
[2, 2, 3]
*/

// Solution 1. Recursive solution. Need to sort the number first. Use the fact that all numbers are positive, terminate when target < current number.
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<int> tmp;
        vector<vector<int>> result;
        combinationSum(candidates, 0, candidates.size()-1, target, tmp, result);
        return result;
    }
    // pick some numbers from [beg, end]
    void combinationSum(const vector<int>& candidates, int beg, int end, int target, vector<int> &tmp, vector<vector<int>> &result) {
        if (target < 0) return;
        if (target == 0) {
            result.push_back(tmp);
            return;
        }
        for (int j = beg; j <= end; ++j) {
            if (candidates[j] > target) return;
            // pick candidates[j]
            tmp.push_back(candidates[j]);
            combinationSum(candidates, j, end, target-candidates[j], tmp, result);
            tmp.pop_back();
        }
    }        
};

// Solution 2. An old iterative solution. (faster)
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

// 2021.11
// Solution 3. Recursive solution.
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> tmp;
        helper(candidates, 0, candidates.size(), target, &tmp, &result);
        return result;
    }
private:
    void helper(vector<int>& candidates, int beg, int end, int residue, vector<int> *tmp, vector<vector<int>> *result) {
        if (residue < 0) {
            return;
        }
        if (residue == 0) {
            result->push_back(*tmp);
            return;
        }
        for (int j = beg; j < end; ++j) {
            // pick candidates[j]
            tmp->push_back(candidates[j]);
            helper(candidates, j, end, residue - candidates[j], tmp, result);
            tmp->pop_back();
        }
    }
};
