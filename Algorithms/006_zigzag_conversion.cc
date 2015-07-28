// period is 2*numRows-2
// when numRows = 1, the resulting string is the same as original one.
class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows == 1) return s;
        int n = s.size();
        int T = numRows + numRows - 2; //period
        string str(n, '0');
        int k = 0;
        // line 1
        for (int i = 0; i < n; i += T)  str[k++] = s[i];
        // line 2 to line numRows-1
        for (int j = 1; j < numRows-1; ++j) { //j is offset
            for (int i = j; i < n; i += T) {
                str[k++] = s[i];
                int u = i+T-2*j;
                if (u < n) str[k++] = s[u]; //need to check if u is within bound!
            }
        }
        //line numRows
        for (int i = numRows-1; i < n; i += T) str[k++] = s[i];
        return str;
    }

};
