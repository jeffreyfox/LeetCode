/*
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4. 
*/

/*
 Dynamic programming, use a table to store the length of longest valid parentheses of s's substring of length i (i = 0 .. n) that ends at s[i].
The result will be the maximum length among all such strings.
 We scan all characters, for i-th character, when we see a ')' we start checking the substring s[0..i-1] of length i. We already know the maximum length of s[0..i), so we check the character before that, if it is '(', then we have found a matching bracket, we further add the part before that '(' is there is any. Be attention of case of possible array out of bound.

  s: 0    ..       j   ...    i-1  i
         [ ... ]  '('   [ ... ]   ')'
*/ 

// Caveats:
// In this scheme, when checking s[i], we are calculating mp[i+1], not mp[i].
// Do not confuse mp[i] and s[i]
// Indexing: mp[i-len-1] not mp[i-len]
// should return max_len, not mp[n]

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        if(n <= 1) return 0;
        vector<int> mp(n+1, 0); //mp[n]: the length of lvp substring of s[0..n-1] that ends at s[n-1].
        int max_len = 0;
        for(int i = 0; i < n; ++i) {
            if(s[i] == ')') {
                int len = mp[i]; //check previous substring
                if(mp[len] >= i || s[i-len-1] != '(') mp[i+1] = 0; //no valid substring ending at s[i]
                else mp[i+1] = len + mp[i-len-1] + 2;
                max_len = max(max_len, mp[i+1]);
            }
        }
        return max_len;
    }
};

// Another solution with stack
/* Stack stores the position of last unmatched position so far, when seeing a ')' start checking the top of stack. If it is a ')', we found a match, and calculate the length from the current top, not if matched, insert the current ')' to the stack indicating the new "end" of unmatched position.
 For example, s=())(())
s[0]: '(', stack: 0
s[1]: ')', pop stack 0 and found a match, now stack is empty, len = 1+1 = 2;
s[2]: ')', stack empty, no match, just push ')' position 2 to stack
s[3]: '(', push to stack, now 2, 3
s[4]: '(', push to stack, now 2, 3, 4
s[5]: ')', matched 4 in stack, len = 2, now stack is 2,3
s[6]: ')', matched 3 in stack, len = 4, now stack is 2.
*/
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        if(n <= 1) return 0;
        deque<int> st; //stack storing indices
        int max_len = 0;
        for(int i = 0; i < n; ++i) {
            char c = s[i];
            if(c == '(' || st.empty()) st.push_back(i);
            else { //c is ')' and st not empty
                int j = st.back(); st.pop_back();
                if(s[j] != '(') st.push_back(i); //not matched
                else { //matched, pop out and get one pos left of valid substring
                    int len = st.empty() ? i+1 : i-st.back();
                    max_len = max(max_len, len);
                }
            }
        }
        return max_len;
    }
};

// Another solution with a sentinel element (-1) to avoid st.empty() checks
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        if(n <= 1) return 0;
        deque<int> st; //stack storing indices
        st.push_back(-1); //sentinel element to avoid st.empty() checks
        int max_len = 0;
        for(int i = 0; i < n; ++i) {
            char c = s[i];
            if(c == '(') st.push_back(i);
            else { //c is ')' and st not empty
                int j = st.back(); st.pop_back();
                if(j == -1 || s[j] != '(') st.push_back(i); //not matched (need to check if j == -1!)
                else { //matched, pop out and get one pos left of valid substring
                    int len = i-st.back(); //if sentinel is back, then is i+1
                    max_len = max(max_len, len);
                }
            }
        }
        return max_len;
    }
};
