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

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ret;
        if(words.empty()) return ret;
        map<string, int> counts; //counts of each unique word
        map<string, int> occurs; //occurrences of each word in s
        for(int i = 0; i < words.size(); ++i) {
            counts[words[i]]++;
        }
        int L = words[0].size(); //word length
        for (int l = 0; l < L; ++l) { //do L passes
            int i = l, j = l;
            occurs.clear(); // clear occurences map
            //scan each substring of length L
            while(j+L <= s.size()) {
                string t = s.substr(j, L);
                if(counts.count(t) == 0) { //not found such word
                    i = j = j+L;
                    occurs.clear();
                    continue;
                }
                occurs[t] ++; //found such word
                if(j == i + L*words.size()) { //reached max size of window
                    string t2 = s.substr(i, L);
                    if(counts.count(t2) > 0) occurs[t2] --;
                    i += L; //move left side of window forward by L
                }
                if(occurs == counts) ret.push_back(i);
                j += L;
            }
        }
        return ret;
    }
};
