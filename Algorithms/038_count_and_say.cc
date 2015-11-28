/*
The count-and-say sequence is the sequence of integers beginning as follows:
1, 11, 21, 1211, 111221, ...

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.

Given an integer n, generate the nth sequence.

Note: The sequence of integers will be represented as a string. 
*/

/// Iterative solution, can place the countAndSay(string&) function directly into for loop to reduce unecessary function call cost
// Caveat: in num2str, should be res = c + res, not res += c + res;

class Solution {
public:
    string countAndSay(int n) {
        string res = "1";
        for(int i = 1; i < n; ++i) {
            res = countAndSay(res);
        }
        return res;
    }
    
    string countAndSay(const string& str) {
        int n = str.size();
        int count = 1;
        string res;
        for(int i = 1; i < n; ++i) {
            if(str[i] == str[i-1]) count++;
            else {
                res += num2str(count) + str[i-1];
                count = 1; //new character
            }
        }
        res += num2str(count) + str[n-1];
        return res;
    }

    string num2str(int n) {
        if(n == 0) return "0";
        string res;
        while(n) {
            res = char(n % 10 + '0') + res;
            n /= 10;
        }
        return res;
    }
};

/// An old solution, use the last string, and scan from left to right to find the number of duplicated entries, and append count as string
class Solution {
public:
    string countAndSay(int n) {
        if (n <= 0) return "";
        if (n == 1) return "1";
        string s = countAndSay(n-1);
        string ret;
        int size = s.size();
        int i = 0, j = 0;
        char c = '\0';
        while(i < size) {
            char c = s[i];
            while(j < size && s[j] == c) j++;
            int cnt = j-i;
            ret += num2str(cnt) + c;
            i = j;
        }
        return ret;
    }
    string num2str(int n) {
        string ret;
        while(n) {
            ret = char('0' + (n % 10)) + ret;
            n /= 10;
        }
        return ret;
    }

};
