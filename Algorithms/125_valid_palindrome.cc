/*
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Note:
Have you consider that the string might be empty? This is a good question to ask during an interview.

For the purpose of this problem, we define empty string as valid palindrome. 
*/

// Solution 1. Two pointers, O(n).
// ignore cases, so use toLower to convert to lower case
// isAlphaNumeric checks whether character is alpha-numeric

class Solution {
public:
    bool isPalindrome(string s) {
        if(s.empty()) return true;
        int n = s.size();
        int i(0), j(n-1);
        while (i < j) {
            if (!isAlphaNumeric(s[i])) i++;
            else if (!isAlphaNumeric(s[j])) j--;
            else if(toLower(s[i]) != toLower(s[j])) return false;
            else {i++; j--; } //equal, move on
        }
        return true;
    }
    bool isAlphaNumeric(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
    }
    char toLower(char c) {
        if(c >= 'A' && c <= 'Z') return c-'A'+'a';
        else return c;
    }
};

// Solution 2. Use another while loop inside, similar to quick-sort implementation.
// Note the ++i in isAphaNumeric, not i++
// If put two sentinels at front and end (s = 'a' + s + 'a';), then can save the boundary checks in the two inner while loop.

class Solution {
public:
    bool isPalindrome(string s) {
        if(s.empty()) return true;
        int n = s.size();
        int i(-1), j(n);
        while (i < j) {
            while (!isAlphaNumeric(s[++i])) if (i == j) return true;
            while (!isAlphaNumeric(s[--j])) if (j == i) return true;
            
            // i and j point to first meaningful characeter
            if (!isSame(s[i], s[j])) return false;
        }
        return true;
    }
    bool isAlphaNumeric(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
    }
    bool isSame(char c1, char c2) {
        if (c1 == c2) return true;
        if (c1 >= 'A' && c1 <= 'Z') return c2 == c1 + 32;
        if (c1 >= 'a' && c1 <= 'z') return c2 == c1 - 32;
    }
};

