// Recursive dfs solution.

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> ret;
        if(digits.empty()) return ret;
        int n = digits.size();
        string s(n, '0');
        dfs(digits, 0, s, ret);
        return ret;
    }
    
    //generate letters for the number at digits[d]
    void dfs(string& digits, int d, string& s, vector<string>& ret) {
        if (d == digits.size()) {
            ret.push_back(s); 
            return; 
        }
        char c = digits[d];
        for (int i = 0; i < numLetters(c); ++i) {
            s[d] = letter(c, i);
            dfs(digits, d+1, s, ret);
        }
    }
    
    int numLetters(char c) {
        return (c == '7' || c == '9') ? 4 : 3;
    }
    
    int letter(char c, int i) {
        if (c == '2') return 'a' + i;
        else if (c == '3') return 'd' + i;
        else if (c == '4') return 'g' + i;
        else if (c == '5') return 'j' + i;
        else if (c == '6') return 'm' + i;
        else if (c == '7') return 'p' + i;
        else if (c == '8') return 't' + i;
        else if (c == '9') return 'w' + i;
        else return ' ';
    }
    
};
