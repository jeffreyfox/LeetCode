/*
Given a string, determine if a permutation of the string could form a palindrome.

For example,
"code" -> False, "aab" -> True, "carerac" -> True.

Hint:

    Consider the palindromes of odd vs even length. What difference do you notice?
    Count the frequency of each character.
    If each character occurs even number of times, then it must be a palindrome. How about character which occurs odd number of times?
*/

// count occurences of each word. check wheather even or odd.

class Solution {
public:
    bool canPermutePalindrome(string s) {
        int n = s.size(); 
        if(n <= 1) return true;
        vector<bool> odd(256,false);
        for(int i = 0; i < n; ++i) {
            char c = s[i];
            odd[c] = ! odd[c];
        }
        int nodds = 0;
        for(int i = 0; i < 256; ++i) {
            if(odd[i]) nodds ++;
            if(nodds > 1) return false;
        }
        return true;
    }
};
