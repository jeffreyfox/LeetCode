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

// use a double-ended queue, break the string into tokens, 
// when see a '.', do nothing
// when see a "..", pop back element from queue (if not empty)
// when see a normal word, push to back of queue
// Then process queue and construct return string
// if queue is empty, then return "/".

class Solution {
public:
    string simplifyPath(string path) {
        string result;
        if(path == "") return result;
        int n = path.size();
        deque<string> s;
        int i = 0;
        while(i < n) {
            if(path[i] == '/') { i++; continue; }
            //find string
            int j = i+1;
            while(j < n && path[j] != '/') j++;
            //[i, j) is the string
            string tmp = path.substr(i, j-i);
            if(tmp == "..") {
                if(!s.empty()) s.pop_back();
            } else if(tmp == ".") ;
            else s.push_back(tmp);
            i = j+1;
        }
        if(s.empty()) return "/";
        while(!s.empty()) {
            result += "/" + s.front();
            s.pop_front();
        }
        return result;
    }
};

