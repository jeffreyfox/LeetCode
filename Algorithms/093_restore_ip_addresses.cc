/*
Given a string containing only digits, restore it by returning all possible valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter) 
*/

// 2021. Recursive solution with cleaner clode.
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        if (s.empty()) return {};
        vector<string> result;
        vector<int> tmp; // indices of breaks
        search(s, 0, tmp, result);
        return result;
    }
    string GenerateString(const string &s, const vector<int> &tmp) {
        string res = s;
        for (int k = 2; k >= 0; --k) {  // no need to add . for tmp[3]
            res.insert(tmp[k], ".");
        }
        return res;
    }
    // Start searching from s[i]
    void search(const string &s, int i, vector<int> &tmp, vector<string> &result) {
        if (i == s.size() && tmp.size() == 4) {
            result.push_back(GenerateString(s, tmp));
            return;
        }
        if (tmp.size() == 4 || i == s.size()) return;
        
        tmp.push_back(0);
        for (int len = 1; len <= 3; ++len) {
            if (i + len > s.size()) break;
            const string t = s.substr(i, len);
            if (isValid(t)) {
                tmp.back() = i + len;
                search(s, i + len, tmp, result);
            }
        }
        tmp.pop_back();
    }
    
    int toInt(const string s) {
        int v = 0;
        for (const auto c: s) {
            v = 10*v + (c - '0');
        }
        return v;
    }
        
    bool isValid(const string s) {
        int v = toInt(s);
        if (s.size() == 1) return v >= 0 && v <= 9;
        if (s.size() == 2) return v >= 10 && v <= 99;
        if (s.size() == 3) return v >= 100 && v <= 255;
        return false;        
    }
};

// 2015
// Recursive solution #1.
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> result;
        if(s.empty()) return result;
        string tmp;
        dfs(s, 0, 0, tmp, result);
        return result;
    }
    void dfs(const string& s, int i, int count, string tmp, vector<string>& result) {
        int n = s.size();
        if(i == n && count == 4) {
            result.push_back(tmp);
            return;
        }
        if(i == n || count == 4) return;
        if(i != 0) tmp += '.';
        if(s[i] == '0') {
            dfs(s, i+1, count+1, tmp+'0', result);
            return;
        }
        for(int k = i, val = 0; k < n; k++) {
            val = val*10 + (s[k] - '0');
            if(val >= 256) break;
            tmp += s[k];
            dfs(s, k+1, count+1, tmp, result);
        }
   }
};

// Recursive solution #2. 
// Need to add 4 periods, last one has to be after last character.
// store positions of periods (index of character right before newly added period), and reconstruct the string when valid solutions are found
// Caveat: string::insert function argument is the index which the new character is inserted before.
// Another caveat: ip address segments cannot have leading zeros, except .0. case, others like .03. or .00. are illegal. Need to filter them out

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> ret;
        vector<int> dotPos(4, -1); //dot positions in the s
        restore(s, 0, 0, dotPos, ret);
        return ret;
    }
    //checking substring starting at s[i] for dot number k (0-3), add values to dotPos
    void restore(const string& s, int i, int k, vector<int>& dotPos, vector<string>& ret) {
       if (k == 4) { //already placing 4 dots (one at the end)
          //onlyd add when i reaches the end
          if (i == s.size()) ret.push_back(construct(s, dotPos));
          return;
       }
       if (i == s.size()) return;
       int v = 0;
       for (int j = i; j < s.size(); ++j) {
          v = 10*v + s[j] - '0';
          if(v >= 256) break;
          dotPos[k] = j; //dot is after j's position
          restore(s, j+1, k+1, dotPos, ret);
          if(s[i] == '0') break; //if leading character is '0', do not continue loop ('.00.' is illegal IP segment)
       }
    }
    string construct(const string& s, const vector<int>& dotPos) {
        string ret = s;
        ret.insert(dotPos[2]+1, 1, '.');
        ret.insert(dotPos[1]+1, 1, '.');
        ret.insert(dotPos[0]+1, 1, '.');
        return ret;
    }

};

