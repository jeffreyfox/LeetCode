/*
 * A valid number consists of several fields:
 *    -28.82e-20 
 * 00012222233334444  

 * Fields 0 and 4 are spaces and can appear >=0 times, thus: \s*
 * Field 1 is either plus or minus sign, and can appear zero or one times, thus:  [\+\-]?
 * Field 2 is the coefficient part, can be one of the following:
 * - integers (a sequence of digits) 20348
 * - integers plus a dot: 20345.
 * - floating points: 2.304
 * - dot followed by digits: .234
 * It should not accept a single dot (.). 
 * Depending on whether a dot is the first character we can break it into two cases:
 * - first character is a digit, so the dot and fractional points can be absent, thus: \d+(\.\d*)?
 * - second character is a dot, it has to be followed by at least one digit, thus: \.\d+
 * thus field 2 is: \d+ (\.\d*)? | \.\d+ 
 * Field 3 is the exponential part. It consists of several parts: 
 * - the e/EXPO character: [eE]
 * - the sign (either + or - or missing): [\+\-]?
 * - the exponent as a sequence of numbers (at least one): \d+.
 * field 3 can be absent or appear only one time, thus: ([eE][\+\-]?\d+)?
 * Thus the regular expression for the valid number is:
 *  \s* [\+\-]? (\d+(\.\d*)?|\.\d+) ([eE][\+\-]?\d+)? \s*  (spaces in between are added for clarity and should be removed)
 * 0..0 1  .. 1 2      ..         2 3     ..        3 4..4
 */

// Use finite automaton. Read charater one by one, depending on the current state and character read, jump to the next state
// 9 states,  and 6 types of charaters defined in CharType
// Small trick: add a space after string s, so we only need to check if state == 8 in the end. 
// Alternative: not add a space, and instead check if state is one of 2,4,7,8 in the end.
class Solution {
public:
    enum CharType { SPACE=0, DIGIT, DOT, SIGN, EXPO, OTHER };

    bool isNumber(string s) {
        s += ' ';
        initDFA();
        int state = 0;
        for (int i = 0; i < s.size() && state >= 0; ++i)
            state = dfa[state][getType(s[i])];
        
        return state == 8;
    }

    void initDFA() {
        dfa.resize(9, vector<int>(6, -1));
        // state 0: has only seen spaces so far, expects another space, a digit, a dot, or a sign
        dfa[0][SPACE] = 0;
        dfa[0][DIGIT] = 2;
        dfa[0][DOT]   = 3;
        dfa[0][SIGN]  = 1;
        // state 1: has read a sign (+/-), expects a digit, or a dot
        dfa[1][DIGIT] = 2;
        dfa[1][DOT]   = 3;
        // state 2: has read a digit in coeffient part, expects another digit, a dot, a e/E, or space
        dfa[2][SPACE] = 8;
        dfa[2][DIGIT] = 2;
        dfa[2][DOT]   = 4;
        dfa[2][EXPO]  = 5;
        // state 3: has read a dot (.) before reading any digit, only expects a digit as fractional part only
        dfa[3][DIGIT] = 4;
        // state 4: has read a dot (.) after reading at least one digit, expects a digit, or e/E, or space
        dfa[4][SPACE] = 8;
        dfa[4][DIGIT] = 4;
        dfa[4][EXPO]  = 5;
        // state 5: has read a e/E in exponent field, expects a sign, or a digit
        dfa[5][DIGIT] = 7;
        dfa[5][SIGN]  = 6;
        // state 6: has read a sign in exponent field, expects a digit
        dfa[6][DIGIT] = 7;
        // state 7: has read a digit in exponent field, expects another digit, or space
        dfa[7][SPACE] = 8;
        dfa[7][DIGIT] = 7;
        // state 8: has read a trailing space, expects another space
        dfa[8][SPACE] = 8; 
    }

    int getType(char c) {
        if (c == ' ' || c == '\t') return SPACE;
        if (c >= '0' && c <= '9')  return DIGIT;
        if (c == '.')              return DOT;
        if (c == '+' || c == '-')  return SIGN;
        if (c == 'e' || c == 'E')  return EXPO;
        return OTHER;
    }

    vector<vector<int> > dfa;
};
