/*
Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.
*/

// Solution 1:
// Scan from left to right. Get the value of next character and compare with current one.
// If current one is larger, add to sum and move forward one step
// If current one is smaller, add (next-curr) and move forward two steps

class Solution {
public:
    int romanToInt(string s) {
        int n = s.size();
        int val = 0;
        for (int i = 0; i < n; ++i) {
            int curr = char2num(s[i]);
            int next = (i < n-1) ? char2num(s[i+1]) : 0;
            if (next > curr) {val += next-curr; i++; }
            else val += curr;
        }
        return val;
    }
    
    int char2num(char c) {
        switch (c) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50; 
            case 'C': return 100;
            case 'D': return 500; 
            case 'M': return 1000; 
            default:  return 0;
        }
    }
};

// Solution 2:
// Scan from right to left. check current value against last value
// If current value is larger or equal than last value, add to sum (e.g. XI, add 10)
// If current value is smaller, substract from sum (e.g. IX, subract 1)
// Underlying assumption is that we won't have invalid string like "IVX"

class Solution {
public:
    int romanToInt(string s) {
        int n = s.size();
        int val = 0;
        int last(0), curr(0);
        for (int i = n-1; i >= 0; --i) {
            curr = char2num(s[i]);
            if (curr >= last) val += curr;
            else val -= curr;
            last = curr;
        }
        return val;
    }
    
    int char2num(char c) {
        switch (c) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50; 
            case 'C': return 100;
            case 'D': return 500; 
            case 'M': return 1000; 
            default:  return 0;
        }
    }
};
