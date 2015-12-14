/*
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high.

For example,
Given low = "50", high = "100", return 3. Because 69, 88, and 96 are three strobogrammatic numbers.

Note:
Because the range might be a large number, the low and high numbers are represented as string. 
*/

/*
Idea is to find the number of strobogrammatic strings between [0, num] for a given number num. Then the count between range [low, high] is basically the difference between two runs, one for [0, high] and one for [0, low]. One corner case here is that if low is strobogrammatic, we need to exclude it from the count.

maintain a mapping from a number to its strobogrammatic counterparts, e.g. 0 => 0, 1 => 1, 6 => 9, 8 => 8, 9 => 6.

helper functions:
1. isStrobogrammatic(string num): check whether a string is strobogramatic or not. 
2. stroboLengthN(int n): return number of all strobogrammatic numbers of given length n (including leading zeros). 
3. stroboBelow(int v, int d): for a given 1 or 2 digit number v, return number of strobogrammatic numbers <= v that also has 1 or 2 digits, including numbers with leading zeros (e.g. "0", or "00").
4. sameLengthBelow(string str, bool countZero): a recursive function to find the number of strobogrammatic numbers <= str and has the same length as str. If countZero is set as true, we include numbers with leading zeros, e.g. 0880 is counted for sameLengthBelow(1981, true).

For a number of length n represented by num, the strobogrammatic numbers between [0, num] are:
1. Strings with length less than n (obtained by a loop calling stroboLenghtN).
2. Strings with length n, and most significant digit (MSD) < num[0], and digits 1 to n-2 can be any strobogrammatic strings of length n-2. This part can be calculated by multiplying results from stroboBelow(int v, int d) and stroboLengthN(n-2).
3. If num[0] is 0, 1, 6, 8, 9. Then we can also have strings with length n, and MSD = num[0]. The number of such strings can be calculated by recursively calling stroboBelow(str) for the substring num[1 .. n-1].
3'. In 3 we might be overcounting one number, e.g. when num = 98485, then we overcounted 98486, we need to decrement count. This only happens when num[n-1] is smaller than the counterpart of num[0], and num[1 .. n-1] is strobogrammatic number. 

corner cases:

1. low is equal to hi, return whether high is a strobogrammatic string.
2. low is large than hi, then return 0. Use a function to test if low is larger than hi.
*/

class Solution {
public:
    Solution() {
        mapping = {0, 1, -1, -1, -1, -1, 9, -1, 8, 6};
    }
    int strobogrammaticInRange(string low, string high) {
        if(low == high) return isStrobogrammatic(high);
        if(isLarger(low, high)) return 0;
        int count1 = countBelow(low);
        int count2 = countBelow(high);
        if(isStrobogrammatic(low)) count1--;
        return count2 - count1;
    }
    bool isLarger(const string& a, const string& b) {
        int m = a.size(), n = b.size();
        if(m != n) return m > n;
        for(int i = 0; i < m; ++i) {
            if(a[i] > b[i]) return true;
            if(a[i] < b[i]) return false;
        }
        return false; //equal, false
    }

    //count strobo numbers from 0 to num including num
    int countBelow(string num) {
        int count = 1; //"0"
        for(int n = 1; n < num.size(); ++n) {
            int tmp = stroboLengthN(n);
            if(n == 1) count += tmp-1; //not include zero 
            else count += tmp-tmp/5; //not include zero
        }
        count += sameLengthStroboBelow(num, false);
        return count;
    }
    //count strobogrammatic numbers <= str, with the same length as str (starting with "0" or "1" depending on countZero)
    int sameLengthStroboBelow(string str, bool countZero) {
	    int n = str.size();
        int count = 0;
        if(n == 1) {
            int v = str[0]-'0';
            count = stroboBelow(v, 1);
            if(!countZero) count --;
        } else if (n == 2) {
            int v = (str[0]-'0')*10 + (str[1]-'0');
            count = stroboBelow(v, 2);
            if(!countZero) count --;
        } else {
            int v1 = (str[0]-'0'), v2 = (str[n-1]-'0');
            //count strobo with first digit being 1 .. v1-1.
            if(v1 > 0) {
                int tmp = stroboBelow(v1*10-1, 2);
                if(!countZero) tmp--;
                count += tmp*stroboLengthN(n-2); 
            }
            string sub = str.substr(1, n-2);
            if(mapping[v1] >= 0) count += sameLengthStroboBelow(sub, true);
            if(v2 < mapping[v1] && isStrobogrammatic(sub)) count--; //avoid overcounting
        }
        return count;
    }

    // number of strobos <= v with d digits (including "0" or "00").
    // v is a number between 0-9 (when d = 1) or 0-99 (when d = 2).
    // 1d strobos: "0", "1", "8"
    // 2d strobos: "00", "11", "69", "88", "96"
    int stroboBelow(int v, int d) {
       int count = 0;
       if(d == 1) {
           if(v < 1) count = 1;
           else if(v < 8) count = 2;
           else count = 3;
       } else if(d == 2) {
           if(v < 11) count = 1;
           else if(v < 69) count = 2; //11
           else if(v < 88) count = 3;
           else if(v < 96) count = 4;
           else count = 5;     
       }
       return count;
    }

    //count strobo for digit n (can have leading zeros)
    int stroboLengthN(int n) {
        if(n == 0) return 0;
        int count = (n % 2 == 1) ? 3 : 5;
        while(n > 2) {
            n -= 2;
            count *= 5;  
        }
        return count;
    }

    bool isStrobogrammatic(string num) {
        int n = num.size();
        for(int i = 0; i < n/2; ++i) {
            char c1 = num[i];
            char c2 = num[n-i-1];
            if( (c1 == '0' && c2 == '0') ||
                (c1 == '1' && c2 == '1') ||
                (c1 == '6' && c2 == '9') ||
                (c1 == '8' && c2 == '8') ||
                (c1 == '9' && c2 == '6') ) continue;
            return false;
        }
        if(n % 2 == 1) {
            char c = num[n/2];
            if(c != '0' && c != '1' && c != '8') return false;
        }
        return true;
    }
    vector<int> mapping;
};
