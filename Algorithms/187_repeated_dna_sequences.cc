/// Use a hash code for the length-10 substring. 3 digit code for each character, so that a total of 30 digits, 
/// which can be represented by an integer (32 bits). 
/// Only 4 characters occuring, 'A', 'C', 'G', 'T' has different last three digits, thus use last three digits (c & 0b111)
/// First calculate the hash code for the first 9 digit, when we add a new digit, we multiply by 8 (radix-8 hash code), or
/// equivalently, << 3. How to strip off the highest character when moving to next? Notice that we only have 30 bits, and 
/// we simply turn off the highest 2 bits, so that we mask with Ox3FFFFFFF.

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> ret;
        int n = s.size();
        if(n < 10) return ret;
        map<int, int> count;
        int hash = 0;
        for(int i = 0; i < 9; ++i) {
            hash = (hash << 3) | (s[i] & 7);
        }
        for(int i = 9; i < n; ++i) {
            hash = ((hash << 3) & 0x3FFFFFFF) | (s[i] & 7);
            count[hash]++;
            if(count[hash] == 2) ret.push_back(s.substr(i-9, 10));
        }
        return ret;
    }
};
