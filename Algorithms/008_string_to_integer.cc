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
    enum CharType {SPACE, SIGN, DIGIT, OTHER};
    //states: 
    // 0: only space read
    // 1: sign read
    // 2: digit read
    // -1: error
    int myAtoi(string str) {
        vector<vector<int> > dfa(3, vector<int>(4, -1));
        dfa[0][SPACE] = 0;
        dfa[0][SIGN] = 1;
        dfa[0][DIGIT] = 2;
        dfa[1][DIGIT] = 2;
        dfa[2][DIGIT] = 2;
        int sgn = 1;
        int ret = 0; 
        int state = 0;
        for(size_t i = 0; i < str.size(); ++i) {
            char c = str[i];
            int type = getType(c);
            state = dfa[state][type];
            if(state == 1) sgn = (c == '-' ? -1 : 1);
            else if(state == 2) {
               int num = c - '0';
               if((INT_MAX - num) / 10 < ret) return (sgn == 1) ? INT_MAX : INT_MIN;
               ret = ret*10 + num;
            } else if(state == -1) {
               return sgn*ret; //return current calcualted value
            }
        }
        return sgn*ret;
    }
    CharType getType(char c) {
        if(c >= '0' && c <= '9') return DIGIT;
        else if(c == '+' || c == '-') return SIGN;
        else if(c == ' ') return SPACE;
        else return OTHER;
    }
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
