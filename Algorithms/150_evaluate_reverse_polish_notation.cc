/*
Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Some examples:

  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
*/

/// Use a stack. Pushing numbers to stack. When seeing an operator, pop two numbers, operate, and put value back to stack.
/// caveat: when evaluating integer numbers, take care of possible positive/negative signs!

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> s;
        for (const auto &t : tokens) {
            if (t == "+" || t == "-" || t == "*" || t == "/") {
                int v2 = s.top(); s.pop();
                int v1 = s.top(); s.pop();
                int v = 0;
                if (t == "+")  v = v1 + v2;
                else if (t == "-") v = v1 - v2;
                else if (t == "*") v = v1 * v2;
                else if (t == "/") v = v1 / v2;
                s.push(v);
            } else {
                s.push(stoi(t));            
            }
        }
        return s.top();
    }
};
