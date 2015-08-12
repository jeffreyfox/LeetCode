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

// break the string into tokens, add to a queue; when seeing a "..", pop from queue (if not empty)
// Then process queue and construct return string
// if queue is empty, then return "/".

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> tokens;
        if(path.empty()) return string();
        deque<string> q; //double ended queue
        path += "/";
        int n = path.size();

        int i = 0, j = 0;
        for (int i = 1; i < n; ++i) {
            if (path[i] == '/') { //found another '/'
                int len = i-j-1;
                if (len == 0) { j = i; continue; }
                string s = path.substr(j+1, len);
                if (s == ".") ;
                else if (s == "..") {
                    if (!q.empty()) q.pop_back();
                } else q.push_back(s);
                j = i;
            }
        }
        
        if(q.empty()) return "/";

        string ret;
        while (!q.empty()) {
            ret += "/" + q.front();
            q.pop_front();
        }
        return ret;
    }
};
