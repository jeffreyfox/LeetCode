/*
An abbreviation of a word follows the form <first letter><number><last letter>. Below are some examples of word abbreviations:

a) it                      --> it    (no abbreviation)

     1
b) d|o|g                   --> d1g

              1    1  1
     1---5----0----5--8
c) i|nternationalizatio|n  --> i18n

              1
     1---5----0
d) l|ocalizatio|n          --> l10n

Assume you have a dictionary and given a word, find whether its abbreviation is unique in the dictionary. A word's abbreviation is unique if no other word from the dictionary has the same abbreviation.

Example:

Given dictionary = [ "deer", "door", "cake", "card" ]

isUnique("dear") -> false
isUnique("cart") -> true
isUnique("cane") -> false
isUnique("make") -> true
*/

// Your ValidWordAbbr object will be instantiated and called as such:
// ValidWordAbbr vwa(dictionary);
// vwa.isUnique("hello");
// vwa.isUnique("anotherWord");

// Solution 1. Use a map from abbreviated string to the set of original strings (260ms).
// e.g. dictionary = [ "deer", "door", "cake", "card" ]
// dict = 
//  d2r => (deer, door)
//  c2e => (cake)
//  c2d => (card)
// To check the new word, return unique if either of the two cases:
// 1. the abbreviated form does not exist in the map (e.g. candy).
// 2. the abbreviated form exists, but its set contains only the original word (e.g. cake).
	
class ValidWordAbbr {
public:
    ValidWordAbbr(vector<string> &dictionary) {
        for(auto s : dictionary) {
            dict[getAbbr(s)].insert(s);
        }
    }

    bool isUnique(string word) {
        auto it = dict.find(getAbbr(word));
        return it == dict.end() || (it->second.size() == 1 && it->second.count(word));
    }
    string getAbbr(string s) {
        int n = s.size();
        if(n <= 2) return s;
        else return s[0] + num2str(n-2) + s[n-1];
    }
    //n is positive integer
    string num2str(unsigned n) {
        if(n == 0) return "0";
        string s;
        while(n) {
            char c = n % 10 + '0';
            s = c + s;
            n /= 10;
        }
        return s;
    }
    unordered_map<string, unordered_set<string> > dict;
};

// Solution 2. Optimized, do not store the string as the key, but the hashed value (200ms).
class ValidWordAbbr {
public:
    ValidWordAbbr(vector<string> &dictionary) {
        for(auto s : dictionary) {
            dict[hash(s)].insert(s);
        }
    }

    bool isUnique(string word) {
        auto it = dict.find(hash(word));
        return it == dict.end() || (it->second.size() == 1 && it->second.count(word));
    }
    int hash(string s) {
        int n = s.size();
        if(n == 0) return -1;
        if(n == 1) return s[0]-'a';
        return s[0]+s[n-1]*26+n*676;
    }

    unordered_map<int, unordered_set<string> > dict;
};

// Solution 3. Further optimized, do not store the set of strings matching the hash value. Just store a single string. If a hash is associated with two different strings, then for sure there is no unique abbr. for this entry. Use empty string to represent this case.
class ValidWordAbbr {
public:
    ValidWordAbbr(vector<string> &dictionary) {
        for(auto s : dictionary) {
            int t = hash(s);
            if(!dict.count(t)) dict[t] = s;
            else if(dict[t] != s) dict[t] = "";
        }
    }

    bool isUnique(string word) {
        if(word == "") return true;
        auto it = dict.find(hash(word));
        return it == dict.end() || (it->second == word);
    }
    int hash(string s) {
        return s.front()+s.back()*26+s.size()*676;
    }

    unordered_map<int, string> dict;
};

