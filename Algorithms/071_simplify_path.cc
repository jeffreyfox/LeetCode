/*
Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"

click to show corner cases.
Corner Cases:

    Did you consider the case where path = "/../"?
    In this case, you should return "/".
    Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
    In this case, you should ignore redundant slashes and return "/home/foo".
*/

// use a stack (implememted by a vector), break the string into tokens, 
// when see a '.', do nothing
// when see a "..", pop element from top of stack (if not empty)
// when see a normal word, push to stack
// Then process stack and construct return string
// if the stack is empty, then return "/".

class Solution {
public:
    string simplifyPath(string path) {
        std::vector<string> st;
        int n = path.size(), i = 0, j = 0;
        while (i < n && j < n) {
            // i points to the next non '/.
            while (i < n && path[i] == '/') i++;
            if (i == n) break;
            
            // j points to the next '/.
            j = i;
            while (j < n && path[j] != '/') j++;
            const string s = path.substr(i, j-i);
            if (s == "..") {
                if (!st.empty()) st.pop_back();
            } else if (s != ".") {
                st.push_back(s);
            }
            i = j;
        }
        
        if (st.empty()) return "/";
        
        string result = "";
        for (auto s : st) {
            result.append("/");
            result.append(s);
        }
        return result;
    }
};
