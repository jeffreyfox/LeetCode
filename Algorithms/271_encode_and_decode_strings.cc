/*
Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.

Machine 1 (sender) has the function:

string encode(vector<string> strs) {
  // ... your code
  return encoded_string;
}
Machine 2 (receiver) has the function:
vector<string> decode(string s) {
  //... your code
  return strs;
}
So Machine 1 does:

string encoded_string = encode(strs);
and Machine 2 does:

vector<string> strs2 = decode(encoded_string);
strs2 in Machine 2 should be the same as strs in Machine 1.

Implement the encode and decode methods.

Note:
The string may contain any possible characters out of 256 valid ascii characters. Your algorithm should be generalized enough to work on any possible characters.
Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.
Do not rely on any library method such as eval or serialize methods. You should implement your own encode/decode algorithm.
*/

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));

// Solution using delimiter and escape character
// use ',' as delimiter, if ',' appears in string, use '\' to escape it, also use '\' to escape itself, so
// ',' is delimiter
// when see a '\', get the next character as the real character
// e.g., for "i love new,york" we will get: ",i,love,new\,york,"

class Codec {
public:
    const char ESCAP = 92;
    const char DELIM = ',';
    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        string s;
        for(int i = 0; i < strs.size(); ++i) {
           s += DELIM; //add delimiter
           for(auto c : strs[i]) {
               if(c == DELIM || c == ESCAP) s += ESCAP; //escape character '\'
               s += c;
           }
           s += DELIM; //add delimiter
        }
        return s;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> strs;
        if(s.empty()) return strs;
        int n = s.size();
        int i = 0;
        while(i < n) { //i points to first ','
            int j = i+1;
            string tmp;
            while(s[j] != DELIM) {
                if(s[j] == ESCAP) tmp += s[++j]; //read next char
                else tmp += s[j];
                j++;
            }
            strs.push_back(tmp);
            i = j+1;
        }
        return strs;
    }
};

