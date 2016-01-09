/*
Write a function to generate the generalized abbreviations of a word.

Example:

Given word = "word", return the following list (order does not matter):

["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]
*/

// Standard DFS. 
// Caveat: no two numbers can appear together!, e.g. 21d is not legal.

class Solution {
public:
    vector<string> generateAbbreviations(string word) {
        if(word.empty()) return vector<string>(1, "");
        vector<string> result;
        string tmp;
        dfs(word, 0, tmp, result);
        return result;
    }
    void dfs(const string& word, int i, string tmp, vector<string>& result) {
        int n = word.size();
        if(i == n) {
            result.push_back(tmp);
            return;
        }
        dfs(word, i+1, tmp+word[i], result); //take the character (no encoding)
        for(int k = i; k < n; ++k) {
            int len = k-i+1;
            if(k < n-1) dfs(word, k+2, tmp+num2str(len)+word[k+1], result); //take len characters and convert to number
            else dfs(word, k+1, tmp+num2str(len), result);
        }
    }
    string num2str(int n) {
        if(n == 0) return "0";
        string s;
        while(n) {
            char c = n % 10 + '0';
            s = c + s;
            n /= 10;
        }
        return s;
    }
};

