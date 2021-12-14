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
        int sign = 1, sum = 0, num = 0;
        char op = ' ';
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '+' || s[i] == '-') {
                sum = sum + sign * num;
                num = 0;
                sign = (s[i] == '+') ? 1 : -1;
                op = ' ';
            } else if (s[i] == '*' || s[i] == '/') {
                op = s[i];
            } else if (isNumeric(s[i])) {
                int new_num = 0;
                while (i < s.size() && isNumeric(s[i])) {
                    new_num = 10*new_num + (s[i] - '0');
                    i++;
                }
                i--;
                if (op == '*') num = num * new_num;
                else if (op == '/') num = num / new_num;
                else num = new_num;
            }           
        }
        sum = sum + sign * num;
        return sum;
    }
    
    bool isNumeric(char c) {
        return c >= '0' && c <= '9';
    }
};

