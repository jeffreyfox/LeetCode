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
