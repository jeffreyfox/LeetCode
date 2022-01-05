/*
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
*/

// Use a stack. When seeing a left parenthesis, push to stack; otherwise check against top of stack
// After reaching the end of string, need to check if stack is empty! (e.g. '[' is not valid)

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (auto c : s) {
            if (c == '(' || c == '{' || c == '[') st.push(c);
            else if (st.empty() || !isMatch(st.top(), c)) return false;
            else st.pop();            
        }
        return st.empty();
    }

    char isMatch(char c1, char c2) {
        if (c1 == '{' && c2 == '}') return true;
        if (c1 == '[' && c2 == ']') return true;
        if (c1 == '(' && c2 == ')') return true;
        return false;
    }
};
