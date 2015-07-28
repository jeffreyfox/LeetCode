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
