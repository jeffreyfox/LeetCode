//  Use two pointers, i and j.
// i points to first word of a new line, scan j forward until either j reaches end, or accumulated length including j
// (word width + minimun number of spaces) exceeds maxWidth. Then words[i..j) should be placed on the current line. 
// next step let i equal j and iterate again, outer loops checks whether i < n.
// Construct the string for each line based on different cases:
// 1. if j == n, then it is the last row, left justified, so add one space after each word except the last word (j-1)
// 2. if only one word allowed for one line, then left justify the word, and append spaces for padding
// 3. if >1 words are placed in one line in the middle of text, then should distribute spaces properly, say we need to 
//    distribute n spaces in m gaps (m+1 words).
///  (a) each gap has at least n/m spaces
///  (b) the residue n % m, if > 0,  should be distributed evenly from the left to right.
/// For example, 6 spaces should be distributed to 4 gaps as:  2 2 1 1 

// Another caveat is string.append function may give error if argument is 0, so use a wrapper function to append spaces.

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int i = 0, j = 0;
        int n = words.size();
        int totWidth = 0, wordWidth = 0;
        vector<string> ret;
        while (i < n) {
            string s;
            totWidth = wordWidth = words[i].size(); //add first word
            j = i+1;
            while (j < n) {
                wordWidth += words[j].size();
                totWidth += 1+words[j].size();
                if (totWidth > maxWidth) break;
                j++;
            }
            //either j == n or totWidth > maxWidth. construct words from [i .. j)
            int nWords = j-i;
            if (j == n) { // last row
                for (int k = i; k < j; ++k) {
                    s += words[k];
                    if (k < j-1) appendSpace(s, 1);
                }
                appendSpace(s, maxWidth-s.size()); //append padding spaces
            } else if (nWords == 1) { // not last row, only one word
                s = words[i];
                appendSpace(s, maxWidth-s.size()); //append padding spaces
            } else {  //not last row, multiple words
                wordWidth -= words[j].size(); //exclude words[j]
                int ngaps = maxWidth - wordWidth;
                int nsp = ngaps / (nWords-1); //spaces in the middle
                int res = ngaps % (nWords-1); //spaces at the first gap
                for (int k = i; k < j; ++k) {
                    s += words[k];
                    if (k == j-1) continue;
                    if (k-i < res) appendSpace(s, nsp+1); //one more!
                    else appendSpace(s, nsp); 
                }
            }
            ret.push_back(s);
            i = j;
        }
        return ret;
    };

    void appendSpace(string& s, int k) {
        if (k > 0) s.append(k, ' ');
    }

};
