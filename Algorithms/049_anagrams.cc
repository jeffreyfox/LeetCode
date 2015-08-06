// Sort the original string. Use a map structure to store whether the sorted string has occurred.
// Optimizations: 
// 1. Do not store sorted strings in another array, rather just sort them on the fly and insert into map
// 2. After finding the string in the map, set the index of it to -1, so that next time will not add it again the next time.
// Caveats:
// 1. std::sort function does not return the sorted string! Instead sort the string in-place.
// 2. When there is only one string, return empty array
// 3. When multiple anagrams are present, return all of them, e.g. "ab", "ba", "bcd", "dcb" => return all of them
class Solution {
public:
     vector<string> anagrams(vector<string>& strs) {
        vector<string> ret;
        if (strs.empty()) return ret;
        int n = strs.size();
        if (n == 1) return ret;

        map<string, int> table;
        for (int i = 0; i < n; ++i) {
           string s = strs[i];
           sort(s.begin(), s.end());

           map<string, int>::iterator it = table.find(s);
           if(it == table.end()) table[s] = i;
           else { //found duplicates
               if (table[s] >= 0) {
                  ret.push_back(strs[it->second]); // add first one (only once)
                  table[s] = -1;
               }
               ret.push_back(strs[i]);
           }
        }
        return ret;
    }
};
