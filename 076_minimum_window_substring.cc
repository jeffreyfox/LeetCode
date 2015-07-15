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
