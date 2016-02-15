/*
Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .

You may assume that the given expression is always valid.

Some examples:

"1 + 1" = 2
" 2-1 + 2 " = 3
"(1+(4+5+2)-3)+(6+8)" = 23

Note: Do not use the eval built-in library function. 
*/

// Solution 1. Basic calculator, with "+-" and parentheses, no "*/"
// Two stacks, one for number and one for operators (can use one, where operator can be stored by an integer sign)
// 1. when seeing a digit, update number
// 2. when seeing a + or -, update result
// 3. when seeing a '(', push result and operator to stack, reset num, res, and op
// 4. when seeing a ')', first update res, and then pop num, res from stack, update res again (e.g. calculate 2 + (...)).
// Finally after loop, update res if no '+' or '-' is seen in the string (e.g. (3))

class Solution {
public:
    int calculate(string s) {
        stack<int> nums;
        stack<char> ops;
        int res = 0;
        int num = 0;
        char op = '+';
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] >= '0' && s[i] <= '9') {
                num = num*10 + (s[i] - '0');
            } else if (s[i] == '+' || s[i] == '-') {
                res = (op == '+') ? res + num : res - num;
                num = 0;
                op = s[i];
            } else if (s[i] == '(') {
                nums.push(res); ops.push(op); //push number and sign to stack
                num = 0; res = 0; op = '+';
            } else if (s[i] == ')') {
                res = (op == '+') ? res + num : res - num;
                op = ops.top(); ops.pop();
                num = nums.top(); nums.pop();
                res = (op == '+') ? num + res : num - res;
                num = 0;
            }
        }
        if (num != 0)
            res = (op == '+') ? res + num : res - num;
        return res;
    }

};

// Solution 2. Use only one stack, push sign (1/-1) and value to the same stack, when pop, pop twice

class Solution {
public:
    int calculate(string s) {
        stack<int> st;
        int res = 0, num = 0, sgn = 1;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] >= '0' && s[i] <= '9') num = num*10 + (s[i] - '0');
            else if (s[i] == '+' || s[i] == '-') {
                res += sgn*num;
                sgn = (s[i] == '+') ? 1 : -1;
                num = 0; //reset num
            } else if (s[i] == '(') {
                st.push(res); st.push(sgn);
                num = 0; res = 0; sgn = 1; //reset
            } else if (s[i] == ')') {
                res += sgn*num; //add last number first
                res *= st.top(); st.pop(); //pop out sign
                res += st.top(); st.pop(); //pop out number
                num = 0; //reset num
            }
        }
        if (num != 0) res += sgn*num;
        return res;
    }
};

