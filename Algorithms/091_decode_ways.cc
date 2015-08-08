// use two helper functions: 
// num(c): whether c itself is legal (1) or not (0)
// num(c1, c2): whether c1c2 together is legal (1) or not (0). e.g. 15 => 1, 56 => 0
// Dynamic programming, when checking s[i], see if we can form s[0..i-1] + s[i] or s[0..i-2] + s[i-1]s[i]
// Only use two variables storing last and lastlast, instead of a vector

class Solution {
public:
    int numDecodings(string s) {
        int val(0);
        int n = s.size();
        if (n == 0) return 0;
        if (n == 1) return num(s[0]);
        if (n == 2) return num(s[0])*num(s[1]) + num(s[0], s[1]);
        int lastlast = num(s[0]), last = num(s[0])*num(s[1]) + num(s[0], s[1]);
        for (int i = 2; i < n; ++i) {
            val = lastlast*num(s[i-1],s[i]) + last*num(s[i]);
            lastlast = last;
            last = val;
        }
        return val;
    }

    int num(char c) {
       return c == '0' ? 0 : 1;
    }
    int num(char c1, char c2) {
        if (c1 == '0') return 0;
        else if (c2 == '0') return (c1 == '1' || c1 == '2') ? 1 : 0;
        else {
            int v = 10*(c1-'0')+(c2-'0');
            return v <= 26 ? 1 : 0;
        }
    }

};
