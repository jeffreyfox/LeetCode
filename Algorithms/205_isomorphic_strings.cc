//Use hash map, has to scan twice (forward and backward) !
'class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int n = s.size();
        map<char, char> tbl_f, tbl_r; //forward and reverse table
        for(int i = 0; i < n; ++i) {
            int c1 = s[i], c2 = t[i];
            if(tbl_f.find(c1) == tbl_f.end()) //not found, insert to map
                tbl_f[c1] = c2;
            else if(tbl_f[c1] != c2) //found, not the same
                 return false;
            
            if(tbl_r.find(c2) == tbl_r.end()) //not found, insert to map
                tbl_r[c2] = c1;
            else if(tbl_r[c2] != c1) //found, not the same
                 return false;
        }

        return true;
    }
};
