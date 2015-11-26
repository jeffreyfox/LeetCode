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
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if(isLeft(c)) st.push(c);
            else if (st.empty() || !match(st.top(), c)) return false; //is right, no match
            else st.pop(); //match, pop out
        }
        return st.empty();
    }
    
    bool isLeft(char c) {
        return c == '(' || c == '[' || c == '{';
    }
    bool isRight(char c) {
        return c == '(' || c == '[' || c == '{';
    }
    bool match(char c1, char c2) {
        return (c1 == '(' && c2 == ')') ||
                (c1 == '[' && c2 == ']') ||
                (c1 == '{' && c2 == '}');
    }
};
