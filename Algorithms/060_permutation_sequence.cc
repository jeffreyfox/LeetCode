// Use modular relation to determine the most significant digit and moving downward. Maintain an array storing whether a particular digit
// has been used or not (e.g. used[2] denotes char '3'). Use a helper function to find the K-th unused character.
// k-- to make k start from 0
// e.g. n = 4
// 1... (3!)  k = 0 - 5 (k / 3! = 0)
// 2... (3!)  k = 6 - 11 (k / 3! = 1)
// 3... (3!)  k = 12 - 17 (k / 3! = 2)
// 4... (3!)  k = 18 - 23 (k / 3! = 3)

class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> used(n, false);
        string ret(n, '0');
        int fac = 1; //fac = n!
        int x = n;
        while (x) fac *= x--;
        int i = 0;
        k--; //start from 0
        while(n) {
            fac /= n; //fac = (n-1)!
            ret[i++] = getKthUnusedChar(used, k/fac);
            k = k % fac;
            n--;
        }
        return ret;
    }

    //find k-th unused
    char getKthUnusedChar(vector<int>& used, int k) {
        for (int i = 0; i < used.size(); i++) {
            if(!used[i]) k--;
            if(k == -1) {
                used[i] = true;
                return '0'+i+1;
            }
        }
        return '0';
    }
};
