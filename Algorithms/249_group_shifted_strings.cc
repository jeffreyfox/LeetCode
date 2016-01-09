/*
Given a string, we can "shift" each of its letter to its successive letter, for example: "abc" -> "bcd". We can keep "shifting" which forms the sequence:

"abc" -> "bcd" -> ... -> "xyz"

Given a list of strings which contains only lowercase alphabets, group all strings that belong to the same shifting sequence.

For example, given: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"],
Return:

[
  ["abc","bcd","xyz"],
  ["az","ba"],
  ["acef"],
  ["a","z"]
]

Note: For the return value, each inner list's elements must follow the lexicographic order.
*/

// Convert each string to its "canonical form", which is shifted form such that first letter is 'a'. Use a dictionary to store the canonical form and associated entries in result vector. When seeing a new word, search in the map. If found, simply insert to the correct places, otherwise, insert to map, and append the new entry to the result vector.
// Caveats: when doing shifts, better shift towards 'a', not 'z', because 'z' is lying close to the end 127, and addition 'z' + 'z' can cause overflow (if char is implmemented as signed int in the machine). On the other hand 'a' is far from the left end 0 or -127, so it is safe.

class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        vector<vector<string> > result;
        unordered_map<string, int> dict;
        for(auto c : strings) {
            string s = convert(c);
            if(!dict.count(s)) { //not found
                dict[s] = result.size();
                result.push_back(vector<string>(1, c));
            } else { //found
                result[dict[s]].push_back(c);
            }
        }
        for(int i = 0; i < result.size(); ++i)
            sort(result[i].begin(), result[i].end());
        return result;
    }
    string convert(const string& s) {
        if(s.empty() || s[0] == 'a') return s;
        string t = s;
        int os = s[0] - 'a'; //offset
        for(int i = 0; i < t.size(); ++i) {
            t[i] -= os;
            if(t[i] < 'a') t[i] += 26;
        }
        return t;
    }
};


