/*
 You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).
*/

// Use two level of hash maps
// Instead of storing map<string, int> for counts, first build an index map for all strings, then store the counts in corresponding indices of the count vector:
// e.g. [foo, bar, the] =>  counts = vector<int> (3, 0),  counts = [1, 1, 1], where IdxMap has (foo=>0, bar=>1, the=>2).
// Turns out to be slower than solution 1...

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ret;
        if(words.empty()) return ret;
        
        map<string, int> idxMap; //string index map
        //count occurrences of individual words and save to idxMap temporarily
        for(int i = 0; i < words.size(); ++i) {
            idxMap[words[i]]++;
        }
        int nUniq = idxMap.size(); //number of unique words
        vector<int> counts(nUniq); //counts of each unique word
        vector<int> occurs(nUniq); //occurrences of each word in s
        int tot_cnt(0), tot_occ(0);
        int idx = 0;
        for(map<string, int>::iterator it = idxMap.begin(); it != idxMap.end(); ++it) {
            counts[idx] = it->second;
            tot_cnt += it->second;
            it->second = idx++; //assign index to each word
        }
        int L = words[0].size(); //word length
        for (int l = 0; l < L; ++l) { //do L passes
            int i = l, j = l;
            occurs.assign(nUniq, 0); // clear occurences vector
            tot_occ = 0;
            //scan each substring of length L
            while(j+L <= s.size()) {
                string t = s.substr(j, L);
                map<string, int>::iterator it = idxMap.find(t);
                if(it == idxMap.end()) { //not found such word
                    i = j = j+L;
                    occurs.assign(nUniq, 0); 
                    tot_occ = 0;
                    continue;
                }
                occurs[it->second] ++; //found such word
                tot_occ ++;
                if(j == i + L*words.size()) { //reached max size of window
                    string t2 = s.substr(i, L);
                    map<string, int>::iterator it2 = idxMap.find(t2);
                    if(it2 != idxMap.end()) { occurs[it2->second] --; tot_occ --; }
                    i += L; //move left side of window forward by L
                }
                if(tot_occ == tot_cnt && occurs == counts) ret.push_back(i);
                j += L;
            }
        }
        return ret;
    }
};
