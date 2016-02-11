/*
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"

Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S. 
*/

/*
The string T can have duplicated characters, so need to maintain a count for each unique character. 
We also need to keep track of which characters have been seen during the scan. We could use two maps, 
but a more elegant way is to use one map intialized as the count in T, and as we scan S and see a character in T, 
we decrement the individual count. As we scan the S, we also maintain the left side of the window as "istart", 
and increment it as needed. There are several things to consider:
1. how to distinguish between characters appearing in T and not? (e.g. "D" v.s. "A")
2. how to know whether we have all the characters we need to construct T?

For Q1, we can use an index vector (dict[256]) to store the occurrences of each alphabet in T, and for other alphabets,  initialized as 0. 
When scanning, we have two pointers i and istart, i will decrement dict, and istart will increment dict, we can prove that 
the dict[c] entries for characters not in T will never become positive. 
For Q2, we maintain another variable "count", initialized as T.len(), and decremented only when we have seen a "useful" character. 
"useful" means character appearing in T and also not redundant. How to know if it is redundant or not? We can check the individual 
count is negative or not. When count == 0, we know that s[istart, i] covers T.
The next step is to check if we could move istart to the right and remove some redundant characters. This can be checked by individual 
count ++dict[s[istart]] <= 0. After this step, s[istart, i] is the minimum window seen so far containing T, by definition, 
s[istart] for sure is needed for T. Next is to continue scanning forward. This gives 16ms solution.

An optimization (16ms=>12ms): we remove s[istart], update the counts (dict and count), and move on. Once count == 0 again, 
we go back to previous step again. Because we know for sure that we don't need s[istart] in later searches, so we can remove it 
and update count. This can avoid many uncessary executiong of if(count == 0) part.

The code can be further shortened: in the while loop:
while(++dict[s[istart] <= 0) istart++;
and then only do: istart++;
*/

class Solution {
public:
    string minWindow(string s, string t) {
        if(t.empty() || s.empty()) return "";
        int slen = s.size();
        vector<int> dict(256, 0);
        for(auto c : t) {
            if(dict[c] < 0) dict[c] = 1;
            else dict[c] ++;
        }
        int count = t.size();
        int istart = 0, minS = -1, minL = INT_MAX;
        for(int i = 0; i < slen; i++) {
            char c = s[i];
            --dict[c];
            if(dict[c] >= 0) count--;
            if(count == 0) {
                while(dict[s[istart]] < 0) {
                    dict[s[istart]]++;
                    istart++;
                }
                //dict[s[istart]] == 0
                if(minL > i-istart+1) { minS = istart, minL = i-istart+1; }
                //remove first char (for sure it is in s)
                dict[s[istart]]++;   istart++;
                count = 1;
            }
        }
        return (minS == -1) ? "" : s.substr(minS, minL);
    }
};

// Solution 2, similar idea to solution 1, but use a map
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> dict;
        int count = t.size(), istart = 0, minL = INT_MAX, minS = -1;
        for(auto c : t) dict[c]++;
        for(int i = 0; i < s.size(); i++) {
            char c = s[i];
            if(!dict.count(c)) continue; //not a character in t
            
            if(--dict[c] >= 0) --count;
            if(count == 0) { //found one
                while(!dict.count(s[istart]) || dict[s[istart]] < 0) {
                    if(dict.count(s[istart])) dict[s[istart]]++;
                    istart++; //remove characters not in t, or redundant ones
                }
                int len = i-istart+1;
                if(len < minL) { minS = istart;  minL = len; }
                dict[s[istart++]]++;  //remove istart
                count = 1; //update count
            }
        }
        return minS == -1 ? "" : s.substr(minS, minL);
    }
};

/*
Another solution is to use a queue to store (position in S of) T's characters seen so far, see below:
*/
/// An old solution using queue
/// Use a window to slide from left to right
/// Use counts to store the occurrences of characters needed to complete (when we see a character that is in t, we decrement the corresponding
/// count in counts. The values can become negative, indicating that the character is in excess.
/// Use a queue to store the current window, the queue is maintained in the following way:
/// 1. when we see a character that is in t, add it to end of queue
/// 2. If the new character in (1) is the same as the front of queue, and a is in excess we pop front (e.g. S = abea.. T = ab, but not: 
/// S = abea.. T = aab, where second a in S is required).
/// 3. when count is zero, we calculate the length, update minL if needed
/// 4. when we pop and push, we incre/decre counts[c], and depending on its sign, update cnt acoordingly.

class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> counts(256, 0);
        int cnt = 0; // number of characters required to completely include t.
        for (int i = 0; i < t.size(); i++) { 
            counts[t[i]]++; 
            cnt++;
        }
        int minl = INT_MAX, mini = 0;
        deque<int> q;
        
        for(int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (t.find(c) == string::npos) continue;
            
            counts[c]--;
            if(counts[c] >= 0) cnt--;
            else if (s[q.front()] == c) {
                counts[c]++;
                q.pop_front();
            }
            q.push_back(i);
            
            if (cnt == 0) {
                while (counts[s[q.front()]] < 0) {
                    counts[s[q.front()]]++;
                    q.pop_front();
                }
                int len = q.back()-q.front()+1;
                if (len < minl) { minl = len; mini = q.front(); }
            }
        }
        if (minl == INT_MAX) return string();
        else return s.substr(mini, minl);
    }
};
