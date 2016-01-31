/*
You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -, you and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a move and therefore the other person will be the winner.

Write a function to determine if the starting player can guarantee a win.

For example, given s = "++++", return true. The starting player can guarantee a win by flipping the middle "++" to become "+--+".

Follow up:
Derive your algorithm's runtime complexity.
*/

// Solution 1. Backtracking. Remember to retrace.

class Solution {
public:
    bool canWin(string s) {
        if(s.empty()) return false;
        if(s.size() == 1) return false;
        return canWinUtil(s);
    }
    bool canWinUtil(string& s) {
        int n = s.size();
        for(int i = 0; i < n-1; i++) { //try all possibilities
            if(s[i] == '+' && s[i+1] == '+') {
                s[i] = s[i+1] = '-';
                bool wins = !canWinUtil(s);
                s[i] = s[i+1] = '+'; //retrace
                if(wins) return true;
            }
        }
        return false;
    }
};

// Solution 2. Dynamic programming. Store previous solutions in an unordered_map

class Solution {
public:
    bool canWin(string s) {
        if(s.empty()) return false;
        if(s.size() == 1) return false;
        return canWinUtil(s);
    }
    bool canWinUtil(string& s) {
        if(dp.count(s)) return dp[s];
        bool wins = false;
        int n = s.size();
        for(int i = 0; i < n-1; i++) { //try all possibilities
            if(s[i] == '+' && s[i+1] == '+') {
                s[i] = s[i+1] = '-';
                wins = !canWinUtil(s);
                s[i] = s[i+1] = '+'; //retrace
                if(wins) break;
            }
        }
        dp[s] = wins;
        return wins;
    }
    unordered_map<string, bool> dp;
};

