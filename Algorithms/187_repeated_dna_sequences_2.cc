/// Similar approach to solution 1, except we use 2-digit code for each character, thus resulting in 20-bit hash code for 
/// the substring, represented by an integer (32 bits). 
/// Use a function to return the hash code for the 4 characters, we only requires 2 bits
/// First calculate the hash code for the first 9 digit, when we add a new digit, we multiply by 4 (radix-4 hash code), or
/// equivalently, << 2. How to strip off the highest character when moving to next? Notice that we only have 20 bits, and 
/// we simply turn off the highest 12 bits, so we mask with Ox000FFFFF.

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> ret;
        int n = s.size();
        if(n < 10) return ret;
        map<int, int> count;
        int hash = 0;
        for(int i = 0; i < 9; ++i) {
            int v = char2num(s[i]);
            hash = (hash << 2) | v;
        }
        for(int i = 9; i < n; ++i) {
            int v = char2num(s[i]);
            hash = (hash << 2) & 0x000FFFFF | v;
            count[hash]++;
            if(count[hash] == 2) ret.push_back(s.substr(i-9, 10));
        }
        return ret;
    }
    
    int char2num(char c) {
        if      (c == 'A') return 0;
        else if (c == 'C') return 1;
        else if (c == 'G') return 2;
        else               return 3;
    }
};
