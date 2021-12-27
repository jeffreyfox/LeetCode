/*
Implement atoi to convert a string to an integer.

Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.

Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible to gather all the input requirements up front.

The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.

The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.

If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.

If no valid conversion could be performed, a zero value is returned. If the correct value is out of the range of representable values, INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.
*/

/// Use a dfa (deterministic finite state automaton to process input string).
/// Stop when state goes to -1 and return the value obtained so far (do not return 0)
/// Be aware of overflow!

class Solution {
public:
    enum CharType {SPACE=0, SIGN, DIGIT, OTHER};
    enum StateType {
        ST_START=0,
        ST_SIGN,
        ST_DIGIT
    };
   
    int myAtoi(string s) {
        Init();
        int state = ST_START;
        int sign = 1, num = 0;
        for (auto c : s) {
            state = dfa[state][getCharType(c)];
            if (state == -1) return sign * num;
            else if (c == '+') sign = 1;
            else if (c == '-') sign = -1;
            else if (c >= '0' && c <= '9') {
                int d = c - '0';
                if ((INT_MAX - d) / 10 < num) return (sign == 1) ? INT_MAX : INT_MIN; 
                num = 10*num + (c - '0');
            }
        }
        return sign * num;
    }
    
    CharType getCharType(char c) {
        if (c == '+' || c == '-') return SIGN;
        if (c >= '0' && c <= '9') return DIGIT;
        if (c == ' ') return SPACE;
        return OTHER;
    }
    void Init() {
        dfa.resize(ST_DIGIT+1, vector<int>(OTHER+1, -1));
        dfa[ST_START][SPACE] = ST_START;
        dfa[ST_START][SIGN] = ST_SIGN;
        dfa[ST_START][DIGIT] = ST_DIGIT;
        dfa[ST_SIGN][DIGIT] = ST_DIGIT;
        dfa[ST_DIGIT][DIGIT] = ST_DIGIT;
    }
private:
    vector<vector<int>> dfa;
};

/// Solution without using dfa. First ignore all trailing spaces, then read possible signs, then read digits until a non-digit character appears or reaching the end. Be aware of overflow!

class Solution {
public:
    int myAtoi(string str) {
        int ret = 0;
        int n = str.size();
        int i = 0;
        while(i < n && str[i] == ' ') i++;
        if(i == n) return 0;
        int sgn = 1;
        if(str[i] == '-') { sgn = -1; i++; }
        else if (str[i] == '+') { i++; }
        for(; i < n; i++) {
           char c = str[i];
           if(c >= '0' && c <= '9') {
               int num = c - '0';
               if((INT_MAX - num) / 10 < ret) return sgn == -1 ? INT_MIN : INT_MAX;
               ret = ret*10 + num;
           } else return sgn*ret;
        }
        return sgn*ret;
    }
};
