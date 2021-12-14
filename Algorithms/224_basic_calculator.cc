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

// 2021. Elegant solution from https://www.youtube.com/watch?v=081AqOuasw0.
// Use a stack.
// We can use a variable to track the sign (1 or -1).
// When there are no brackets, we can compute results on the fly and no stack is needed. We keep track of rolling sum and the sign.
// Initially, sum = 0, sign = 1. When we see a number, add it to the sum (apply the sign seen one step before).
/// When there are brackets, we need a stack to store the sum and the sign, e.g. 2-(3+4). When see the left bracket '(', we need to save 2 and - to the stack and
// compute 3+4 on the fly.
// When we see a right bracket ')', we reach the end of this level. The current sum 7 needs to be applied to the operand in the stack. Here we have sum = 7 and
// 2 and - in the stack. We pop the two and apply them to 7 and get -5.

class Solution {
public:
    int calculate(string s) {
        stack<int> st;
        int sign = 1, sum = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ' ') continue;
            if (s[i] == '+') sign = 1;
            else if (s[i] == '-') sign = -1;
            else if (s[i] >= '0' && s[i] <= '9') {
                int num = 0;
                while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
                    num = 10*num + (s[i] - '0');
                    i++;
                }
                sum += sign * num;
                i--;
            } else if (s[i] == '(') {
                st.push(sum);
                st.push(sign);
                sum = 0; sign = 1;
            } else if (s[i] == ')') {
                sign = st.top(); st.pop();
                sum = st.top() + sign * sum;  st.pop();
            }            
        }
        return sum;
    }
};

// 2015.
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

