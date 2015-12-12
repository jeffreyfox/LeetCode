/*
Implement strStr().

Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
*/

/// Classical pattern search problem. 
/// Solution 1. Brute-force solution, O(MN) in the worst case

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        int i(0), j(0);
        for(i = 0; i < n && j < m; ++i) {
            if(haystack[i] == needle[j]) j++;
            else { i-=j; j = 0; }
        }
        if(j == m) return i-j;
        else return -1;
    }
};

// Solution 2. A varient of brute-force solution
class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size(), i(0), j(0);
        while(i < n && j < m) {
            if(haystack[i] == needle[j]) { i++; j++; }
            else {i = i-j+1; j = 0; }
        }
        if(j == m) return i-j;
        else return -1;
    }
};

// Solution 3. KMP algorithm with transfer function.
/*
We define the transfer function f[j] = k as the length of longest prefix of p[0 .. j-1] such that
f[0 .. k-1] == f[j-k .. j-1], 0 <= k < j
we don't allow k to equal j to avoid the trivial case where prefix is the string itself.
Therefore, whenever we see a mismatch between t[i] and p[j], we can directly make j jump to k = f[j], and i stays unchanged, so that t[i] is compared with p[k] (we know for sure that p[0 .. k-1] matches with t[i-k, i-1].
One corner case is that when mismatch happens at first character of pattern, i.e. j = 0. In this case we just increment i and keep j unchanged.

e.g. 01234   5
     abcab | cabd
     abcab | d    mismatch at j = 5, f[5] = 2
     01234   5   
=>   abcab | cabd
        ab | cabd
        01   23   j jumps to f[j] = 2

How to build transfer function for the pattern strign? We use an elegant dynamic programming approach. Say we know f[j-1] = k, now we calculate f[j], where we need to examine p[j-1].
We simply compare p[j-1] with p[k].
If they are equal, then we found that f[j] = k+1.
e.g. abcabc,  f[5] = 2 (ab), then f[6] = 3 because p[3] = [5] = c.
If they are not equal, we need to continue searching f[k] until k is less than zero. e
e.g. acadaca x acadaca d, f[15] = 7 (acadaca), for f[16], since p[7] != p[16], we need to examine f[7]. Since f[7] = 3 (aca), and p[4] = p[16], we know f[16] = 4 (acad)
Boundary case: f[0] = -1 for later convenience, f[1] = 0.

Thus we have come up with the following loop:
    f[0] = -1; f[1] = 0;
    for(int j = 2; j <= m; ++j) { //length j
        char c = needle[j-1];
        int k = f[j-1]; //result for previous
        while(k >= 0 && needle[k] != c) k = f[k];
        f[j] = k+1; //either k = -1, or needle[k] == c
    }

We can further optimize, and let k be the f value for the last calculation. Initially, k = f[1] = 0.
After each calculation, we update k's value by k = k+1, and then assign it to f[j].
Two case:
1. k = -1 after while loop, which indicates no such prefix exists, in this case by definition f[j] = 0, we let f[j] = ++k which is OK.
2. k >= 0 after while loop, which we know that needle[k] == c. This means that the maximum prefix for for pj is p[0..k] including k, and thus f[j] = ++k is also OK.
This has lead to the following loop:
    f[0] = -1; f[1] = 0; k = 0; // k is result for previous
    for(int j = 2; j <= m; ++j) { //length j
        while(k >= 0 && needle[k] != needle[j-1]) k = f[k];
        f[j] = ++k; //after while loop, either k = -1, or needle[k] == needle[j-1]
    }
*/

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        vector<int> f(m+1, -1); //jump position for p[0. i-1) of length i
        f[1] = 0; 
        for(int j = 2; j <= m; ++j) { //length j, f[1] will lead to 0
            char c = needle[j-1];
            int k = f[j-1];
            while(k >= 0 && needle[k] != c) k = f[k];
            f[j] = k+1; //either f[k] = -1, or t[f[k]] = c
        }
        int i(0), j(0);
        while(i < n && j < m) {
            if(haystack[i] == needle[j]) { i++; j++; }
            else if(j == 0) i++;
            else j = f[j];
        }
        return (j == m) ? i-j : -1;
    }
};

//slightly optimized KMP.

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        vector<int> f(m+1, -1); //jump position for p[0. i-1) of length i
        int k = -1; //k is result from previous step
        for(int j = 1; j <= m; ++j) { //length j, f[1] will lead to 0
            while(k >= 0 && needle[k] != needle[j-1]) k = f[k];
            f[j] = ++k; //either f[k] = -1, or t[f[k]] = c
        }
        int i(0), j(0);
        while(i < n && j < m) {
            if(haystack[i] == needle[j]) { i++; j++; }
            else if(j == 0) i++;
            else j = f[j];
        }
        return (j == m) ? i-j : -1;
    }
};

