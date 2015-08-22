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
        deque<int> st; //stack
        for(size_t i = 0; i < tokens.size(); ++i) {
            const string& str = tokens[i];
            if(str == "+" || str == "-" || str == "*" || str == "/") {
                 int num2 = st.back(); st.pop_back();
                 int num1 = st.back(); st.pop_back();
                 if(str == "+") st.push_back(num1+num2);
                 else if(str == "-") st.push_back(num1-num2);
                 else if(str == "*") st.push_back(num1*num2);
                 else if(str == "/") st.push_back(num1/num2);
            } else {
                 st.push_back(eval(str));
            }
        }
        return st.back();
    }
    int eval(const string& str) {
        int v = 0;
        int sign = 1;
        for(size_t i = 0; i < str.size(); ++i) {
            if(i == 0 && (str[i] == '-' || str[i] == '+')) sign = (str[i] == '+') ? 1 : -1;
            else v = v*10 + (str[i] - '0');
        }
        return sign*v;
    }
};
