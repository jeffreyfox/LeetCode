/*
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R

And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);

convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR". 
*/

// period is 2*numRows-2
// when numRows = 1, the resulting string is the same as original one.
class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows == 1) return s;
        string result = s;
        int p= 2*numRows-2;
        int k = 0, n = s.size();
        for(int ir = 0; ir < numRows; ++ir) {
            for(int j = ir; j < n; j += p) {
                result[k++] = s[j];
                if(ir > 0 && ir < numRows-1) { //not first or last row
                    int idx = j+p-2*ir;
                    if(idx < n) result[k++] = s[idx]; //need to check if idx < n!
                }
            }
        }
        return result;
    }
};

