/*
Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, +, -, *, / operators and empty spaces . The integer division should truncate toward zero.

You may assume that the given expression is always valid.

Some examples:

"3+2*2" = 7
" 3/2 " = 1
" 3+5 / 2 " = 5

Note: Do not use the eval built-in library function. 
*/

// Basic calculator II, with "+-*/" but no parentheses
// No stack solution:
// 1. when seeing an integer, run all the way to the end of integer and get the value. If it is after a '*' or '/', immediately calculate the 
//    result and update num. Otherwise, initialize num to the value.
// 2. when seeing a '+' or '-', add the preceding number (value stored in num and sign stored in sign) to res
// 3. when seeing a '*' or '/', update last operator
// Remember to reset num after processing "+-*/"

// Also, after loop, need to add final num to res, and return
// Another tiny variation is to add a '+' in the end of string, and then can return res 
class Solution {
public:
    int calculate(string s) {
        int res = 0;
        int num = 0;
        char op = '+';
        int sign = 1;
        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            if (isDigit(c)) {
                int val = c - '0';
                int j = i+1;
                while (j < s.size() && isDigit(s[j])) {
                    val = val*10 + s[j] - '0';
                    j++;
                }
                if (op == '*') num = num * val;
                else if (op == '/') num = num / val;
                else num = val;
                i = j-1;
            } else if (c == '+' || c == '-') {
                res += num*sign;
                sign = (c == '+') ? 1 : -1;
                num = 0;
                op = c;
            } else if (c == '*' || c == '/') {
                op = c;
            } 
        }

        return res + num*sign;
    }

    bool isDigit(char c) { return c >= '0' && c <= '9'; }
};

