/*
All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

For example,

Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",

Return:
["AAAAACCCCC", "CCCCCAAAAA"].
*/

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

/// Similar approach to solution 1, except we use 2-digit code for each character, thus resulting in 20-bit hash code for 
/// the substring, represented by an integer (32 bits). 
/// Use a function to return the hash code for the 4 characters, we only requires 2 bits. We can use a trick to return the hash value:
/// hash = (s[i] - 'A' + 1) % 5. This way, ACGT returns 1 3 2 0 respectively.

/// First calculate the hash code for the first 9 digit, when we add a new digit, we multiply by 4 (radix-4 hash code), or
/// equivalently, << 2. How to strip off the highest character when moving to next? Notice that we only have 20 bits, and 
/// we simply turn off the highest 12 bits, so we mask with Ox000FFFFF.

// Another optimization is to use an array to store the hash table (can use char if counts are less than 256 to save space). Note that using vector<int> increases runtime from 20 ms to 100 ms. But using vector<char> is only 12 ms.

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> result;
        char dict[1048576] = {0}; //hash => counts (assume counts < 256).
        int n = s.size();
        const int LEN = 10;
        if(n <= LEN) return result;
        int hashval = 0;
        for(int i = 0; i < LEN-1; ++i) {
            hashval = (hashval << 2) | (s[i] - 'A' + 1) % 5;
        }
        for(int i = LEN-1; i < n; ++i) {
            //remove two leading bits, and shift to right by two and add next hash value
            hashval = ((hashval << 2) & 0x000FFFFF) | (s[i] - 'A' + 1) % 5;
            if(dict[hashval]++ == 1) result.push_back(s.substr(i-LEN+1, LEN));
        }
        return result;
    }
};

