/*
The set [1,2,3,…,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):

    "123"
    "132"
    "213"
    "231"
    "312"
    "321"

Given n and k, return the kth permutation sequence.

Note: Given n will be between 1 and 9 inclusive.
*/

/* Solution using modular relation to determine the most significant digit and moving downward. This solution does not print the numbers in lexigraphical order.
 Maintain an array storing whether a particular digit has been used or not (e.g. used[2] denotes char '3'). Use a helper function to find the K-th unused character.
 k-- to make k start from 0
 e.g. n = 4
 1... (3!)  k = 0 - 5 (k / 3! = 0)
 2... (3!)  k = 6 - 11 (k / 3! = 1)
 3... (3!)  k = 12 - 17 (k / 3! = 2)
 4... (3!)  k = 18 - 23 (k / 3! = 3)
Caveats: the next permutation algorithm does not pass here due to TLE: has to move forward one step at a time!
*/

class Solution {
public:
    string getPermutation(int n, int k) {
        int fact = 1;
        for(int i = 1; i <= n; ++i) fact *= i;
        k = (k-1) % fact;
        vector<int> used(n, false);
        string result(n, '0');
        for(int i = 0; i < n; ++i) { //from MSD to LSD
            fact = fact / (n-i);
            int j = k / fact;
            int idx = findUnused(used, j);
            used[idx] = true;
            result[i] = idx + '1';
            k %= fact;
        }
        return result;
    }

    int findUnused(const vector<int>& used, int i) {
        for(int j = 0; j < used.size(); ++j) {
            if(!used[j]) {
                if(i-- == 0) return j;
            }
        }
        return -1;
    }
};

/*
Solution 2 using a bit status number.
Caveat:
 When testring if a digit is unset, use
 !(x & (1 << n)). not ~ , because inverting boolean and inverting bit number are totally different things!
 ! 1 = !(true) = false
 ~ 1 = -2 = true!
*/

class Solution {
public:
    string getPermutation(int n, int k) {
        int fact = 1;
        for(int i = 1; i <= n; ++i) fact *= i;
        k = (k-1) % fact;
        int state = 0; //used state: digit i means whether k+1 has been used
        string result(n, '0');
        for(int i = 0; i < n; ++i) { //from MSD to LSD
            fact = fact / (n-i);
            int j = k / fact;
            int idx = findUnused(state, j);
            state |= (1 << idx);
            result[i] = idx + '1';
            k %= fact;
        }
        return result;
    }

    int findUnused(int state, int i) {
        for(int j = 0; j < 32; ++j) {
            if(!(state & (1 << j))) {
                if(i-- == 0) return j;
            }
        }
        return 32;
    }
};

// Solution 3 using a string storing unused characters, when a character is used, remove the character
// Notice the usage of two STL functions: iota and string::erase

class Solution {
public:
    string getPermutation(int n, int k) {
        string dict(n, '0');
        iota(dict.begin(), dict.end(), '1'); // dict = '1234...n'
        int fact = 1;
        for(int i = 1; i <= n; ++i) fact *= i;
        k = (k-1) % fact;
        string result(n, '0');
        for(int i = 0; i < n; ++i) { //from MSD to LSD
            fact = fact / (n-i);
            int j = k / fact;
            result[i] = dict[j];
            dict.erase(j, 1); //erase j-th character
            k %= fact;
        }
        return result;
    }
};


