/*
Given a string s, return all the palindromic permutations (without duplicates) of it. Return an empty list if no palindromic permutation could be form.

For example:

Given s = "aabb", return ["abba", "baab"].

Given s = "abc", return [].

Hint:

    If a palindromic permutation exists, we just need to generate the first half of the string.
    To generate all distinct permutations of a (half of) string, use a similar approach from: Permutations II or Next Permutation.

*/

// Scan whole word, count occurrences of each character. Only one character is allowed to have odd count. Otherwise return empty set.
// construct half string as half the count of each character. No need to sort the string because we construct it from c = 0 to c = 255.
// Store the middle character as a string (either single character, or empty string). And call nextPermutation to find the next one. Need a reverse function.
// Caveats:
// Need to handle corner cases where the half string is empty! It will result in infinite loops in nextPermutation if there is no checking.
// Alternatively can check this at the beginning (by checking whether the length of s is 1).

class Solution {
public:
    vector<string> generatePalindromes(string s) {
        vector<string> result;
        if(s.empty()) return result;
        if(s.size() == 1) {
            result.push_back(s); return result;
        }
        vector<int> counts(256, 0);
        for(auto c : s) counts[c] ++;
        int nodds = 0;
        string odd = "";
        s = "";
        for(int c = 0; c < 256; ++c) {
            if(counts[c] & 1) {
                odd += c;
                if(++nodds > 1) return result; //no solution
            } 
            if (counts[c] > 0)
                s += string(counts[c]/2, c);
        }
        result.push_back(s+odd+reverse(s));
        while(nextPermutation(s)) result.push_back(s+odd+reverse(s));
        return result;
    }
    
    string reverse(const string& s) {
        string t = s;
        int i(0), j(s.size()-1);
        while(i < j) {
            swap(t[i++], t[j--]);
        }
        return t;
    }
    bool nextPermutation(string& s) {
        if(s.empty()) return false;
        int n = s.size();
        int k = n-2, l = n-1;
        while(k >= 0 && s[k] >= s[k+1]) k--;
        //k is the last k such that nums[k] < nums[k+1]
        if(k == -1) { //no next, just return false
            return false;
        }
        while(l > k && s[l] <= s[k]) l--;
        //l is the last l such that nums[l] > nums[k]
        //swap nums[k] and nums[l]
        swap(s[k], s[l]);
        //sort numbers after k
        int i = k+1, j = n-1;
        while(i < j) swap(s[i++], s[j--]);
        return true;
    }
};
