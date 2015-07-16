// iterative solution

class Solution {
public:
    vector<vector<int> > permute(vector<int> &num) {
        int n = num.size();
        vector<vector<int> > ret;
        if(n == 0) return ret;
        int k = 0;
        vector<int> perm(n, -1); //one permutation (storing indices)
        vector<bool> chosen(n, false); //whether num[i] has been chosen
        while(k >= 0) {
            if(perm[k] != -1) chosen[perm[k]] = false;
            perm[k] ++;
            while(perm[k] < n && chosen[perm[k]]) perm[k] ++;
            
	        if(perm[k] < n)  { // found one unused index
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
			  // perm[k] = -1;
	           k--;
            }
        }
        
        return ret;
    }
};

