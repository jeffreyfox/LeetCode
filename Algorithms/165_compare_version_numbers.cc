/*
Compare two version numbers version1 and version2.
If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.

You may assume that the version strings are non-empty and contain only digits and the . character.
The . character does not represent a decimal point and is used to separate number sequences.
For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.

Here is an example of version numbers ordering:

0.1 < 1.1 < 1.2 < 13.37
*/

// C++ version without using any system libraries (iterative solution).
// Use two pointers to scan two version numbers. Calculate integer value on the fly until encountering a '.' or end of string
// Caveats:
// 1.1 > 1 (longer one is larger), but 1.0 = 1. Need to extract the next number for empty strings, which is set as zero.

class Solution {
public:
    int compareVersion(string version1, string version2) {
        int m = version1.size();
        int n = version2.size();
        int i = 0, j = 0;
        while (i < m || j < n) {
            int num1 = 0, num2 = 0;
            while (i < m && version1[i] != '.') {
                num1 = num1*10 + (version1[i]-'0');
                i++;
            }
            while (j < n && version2[j] != '.') {
                num2 = num2*10 + (version2[j]-'0');
                j++;
            }
            if      (num1 > num2) return  1;
            else if (num1 < num2) return -1;
            i++; j++; //remember to increment i and j!
        }
        return 0; //equal
    }
};

// Another solution. Recursive.
class Solution {
public:
    int compareVersion(string version1, string version2) {
        return compareVersion(version1, version2, 0, 0);
    }
    int compareVersion(const string& version1, const string& version2, int i, int j) {
        if(i >= version1.size() && j >= version2.size()) return 0; //termination
        //now neither has reached end
        int v1 = 0, v2 = 0;
        while(i < version1.size() && version1[i] != '.') {
            v1 = v1*10 + (version1[i++] - '0');
        }
        while(j < version2.size() && version2[j] != '.') {
            v2 = v2*10 + (version2[j++] - '0');
        }
        if(v1 > v2) return 1;
        else if(v1 < v2) return -1;
        return compareVersion(version1, version2, i+1, j+1); //equal, compare next
    }
};

