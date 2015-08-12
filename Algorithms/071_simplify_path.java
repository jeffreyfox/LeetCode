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

// Use java's split function with delimiter "/". Need to check against empty string when "/" is at beginning or end

public class Solution {
    public String simplifyPath(String path) {
        String ret = new String();
        String[] tokens = path.split("/");
        Stack<String> st = new Stack<String>();
        for (String s : tokens) {
            if (s.equals(".") || s.equals("")) continue;
            else if (s.equals("..")) {
                if(!st.empty()) st.pop();
            } else st.push(s);
        }
        if (!st.empty()) {
            for (String s : st) 
                ret += "/" + s;
        } else ret = "/";
        return ret;
    }
}
