/*
You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).
*/

// words may contain duplicates, so use a map (counts) to count occurrences of each unique word, use occurs to count words seen so far in s
// e.g. words = ["a", "a", "b"], then counts = { "a" => 2, "b" => 1 }
// let the length of each word to be L, then has to do L passes, each time searching starts from s[l], l = 0 .. l-1.
// Each pass, use two pointers to track the sliding window boundaries. grab a subtring of length L once at a time. If reaching the maximum window size (L*nwords), then slide left (i) one L step. When counts == occurs (size equal && individual elements equal), then found a valid index

// Be cautious, j is not the end of the window, but j+L is!, so length of window is actually j-i+1.
// Don't need to maintain a separate total count, since when comparing counts and occurs, first it compares the size

// e.g.
// s = b a r f o o t h e f o o b a r m a n  ,  counts = {bar => 1, foo => 1}
//    [b a r]f o o t h e f o o b a r m a n  ,  i = 0, j = 0, occurs = {bar => 1}
//    [b a r f o o]t h e f o o b a r m a n  ,  i = 0, j = 3, occurs = {bar => 1, foo = 1},  found '0'
//     b a r[f o o t h e]f o o b a r m a n  ,  i = 3, j = 6, break since the is not in words, occurs = {}
//     b a r f o o t h e[f o o]b a r m a n  ,  i = 9, j = 12, occurs = {foo => 1}
//     b a r f o o t h e[f o o b a r]m a n  ,  i = 9, j = 15, occurs = {foo => 1, bar = 1}, found '9'
//     b a r f o o t h e f o o[b a r m a n] ,  i = 12, j = 18, break since the is not in words, occurs = {}

/*
Only use one map to store the counts, when see the string, reduce the individual counts, when it reaches zero we know that we have exactly the amount we need.
simpler than 074, since the window can only contain words in dictionary, and also the counts should not exceed the total counts in dictionary (no excessive words). 
So here we keep this loop invariant and use it to simplify our routines.
Maintain a dict that counts the occurrences of all words in word vector. the trick is to recover dict for each sub runs. 
Each time we move i, we update dict, each time we move istart, we recover dict, in the end, when both i and istart reaches end, 
we recovered the original dict.

When seeing a new string at i, check several cases:
1. if not seen in dict, then the previous searches [istart, i) are invalid, just move istart forward to i and pop all words seen, 
and update count properly.
2. if in dict, then decrement the count, if it is excessive word, then move istart to pop out words until the count is zero 
(meaning no excessive). 
3. if not excessive, simply go on.
4. if count == 0, then we have found one window, insert to result.
*/

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        if(s.empty() || words.empty()) return result;
        int wl = words[0].size();
        if(wl == 0) return result;
        int slen = s.size();
        
        unordered_map<string, int> dict;
        for(auto s : words) dict[s]++;
        
        for(int j = 0; j < wl; j++) {
            int i = j, istart = j, count = words.size();
            //loop invariant: [istart, i) contains no words not in dict, no excessive words
            while(i + wl <= slen) {
                string str = s.substr(i, wl);
                if(!dict.count(str)) { //not found, reset start, i, and count
                    while(istart < i) { //for sure istart is contained in dict
                        ++dict[s.substr(istart, wl)];
                        istart += wl;
                    }
                    i += wl;
                    istart = i;
                    count = words.size();
                    continue;
                }
                dict[str]--;
                if(dict[str] >= 0) count--;
                while(dict[str] < 0) {
                    if(++dict[s.substr(istart, wl)] > 0) count++;
                    istart += wl;
                }

                if(count == 0) {
                    result.push_back(istart);
                    dict[s.substr(istart, wl)]++;
                    istart += wl; //move forward
                    count = 1;
                }
                i += wl;  //move forward
            }
            //increment istart to mantain correct counting in dict and count
            while(istart + wl <= slen) {
                ++dict[s.substr(istart, wl)];
                istart += wl;
            }
        }
        return result;
    }
};

// an old solution, similar to min window, use only one dict to store the counting information. The key is to restore the information after each run.

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
         vector<int> result;
         int nwords = words.size();
         if(nwords == 0) return result;
         int lword = words[0].size();
         if(s.empty()) return result;
         unordered_map<string, int> dict, count;
         int total_count = 0;
         int n = s.size();
         for(size_t i = 0; i < nwords; ++i)
             dict[words[i]]++;
        
         for(size_t i = 0; i < lword; ++i) {
             total_count = nwords;
             count = dict;
             int jstart = i, j = i;
             while(j + lword <= n) {
                 string str = s.substr(j, lword);
                 if(count.find(str) == count.end()) {
                     total_count = nwords;
                     count.clear();
                     jstart = j + lword;
                 } else {
                     total_count ++;
                     count[str] ++;
                     int c = dict[str];
                     while(count[str] > c) {
                         string tmp = s.substr(jstart, lword);
                         count[tmp] --;
                         total_count --;
                         jstart += lword;
                     }
                 }
                 if(total_count == words.size()) result.push_back(jstart);
                 j += lword;
             }
         }
         return result;
    }
};

