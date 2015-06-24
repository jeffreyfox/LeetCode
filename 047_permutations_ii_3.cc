// iterative solution

class Solution {
public:
    
    //store previously visited partial permutations in strings, say 1 2 3 => "123"
    //assume numbers only have one digit, will not work e.g have 11
    vector<vector<int> > permuteUnique(vector<int> &num) {
		set<string> table; //table for occuured parital permutation's code
		string code; //code for occurred partial permutations
		int n = num.size();
		vector<vector<int> > ret;
		if(n == 0) return ret;
		int k = 0;
		vector<int> perm(n, -1); //one permutation (storing indices)
		vector<bool> chosen(n, false); //whether num[i] has been chosen
		while(k >= 0) {
			if(perm[k] != -1) chosen[perm[k]] = false;
			if(perm[k] != -1) code.resize(code.size()-1);

			perm[k] ++;
			
			while(perm[k] < n && (chosen[perm[k]] || table.find(code+char(num[perm[k]]+48)) != table.end())) perm[k] ++;
			//while(perm[k] < n && chosen[perm[k]] ) perm[k] ++;
	
			if(perm[k] < n)  { // found one unused index
				code = code + char(num[perm[k]]+48);
				table.insert(code);
				if(k == n-1) { // assembled one permutation
					vector<int> vect(n, 0);
					for(int j = 0; j < n; ++j) vect[j] = num[perm[j]];
					ret.push_back(vect);
				} else {
					chosen[perm[k]] = true;
					k++;
					perm[k] = -1; //can be put into else
				}
			} else { //not found
				//perm[k] = -1;
				k--;
			}
		}

		return ret;
	}
};
