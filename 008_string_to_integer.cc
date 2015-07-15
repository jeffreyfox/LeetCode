/// Use a dfa (deterministic finite state automaton to process input string).
/// Stop when state goes to -1 and return the value obtained so far (do not return 0)
/// Be aware of overflow!

class Solution {
public:
    enum CharType { SPACE=0, SIGN, DIGIT, OTHER };
    //states:
    //0: leading space, 1: sign, 2: digits, 3: trailing space
    int myAtoi(string str) {
        vector<vector<int> > dfa(4, vector<int>(4, -1));
        dfa[0][SPACE] = 0;
        dfa[0][SIGN] = 1;
        dfa[0][DIGIT] = 2;

        dfa[1][DIGIT] = 2;

        dfa[2][DIGIT] = 2;
        dfa[2][SPACE] = 3;

        dfa[3][SPACE] = 3;

        int state = 0;
        long val = 0;
        int sgn = 1;
        for (int i = 0; i < str.size() && state >= 0; ++i) {
            char c = str[i];
            state = dfa[state][getType(c)];
            if (state == 1) {
               if (c == '-') sgn = -1;
            }
            if (state == 2) {
               long nval = val*10 + (c-'0');
               if (nval < val) return (sgn == 1) ? INT_MAX : INT_MIN; //overflow
               val = nval;
            }
        }
      //  if (state == -1) return 0; //wrong input
        if (sgn == 1 && val > INT_MAX) return INT_MAX;
        if (sgn == -1 && val > long(INT_MAX) + 1) return INT_MIN;
        return (sgn == 1) ? val : -val;
    }

    int getType(char c) {
        if (c == ' ') return 0;
        else if (c == '+' || c == '-') return 1;
        else if (c >= '0' && c <= '9') return 2;
        else return 3;
    }

};
