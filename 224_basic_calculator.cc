// Basic calculator, with "+-" and parentheses, no "*/"
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
