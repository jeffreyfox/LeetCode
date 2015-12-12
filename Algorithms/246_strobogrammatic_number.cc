/*
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to determine if a number is strobogrammatic. The number is represented as a string.

For example, the numbers "69", "88", and "818" are all strobogrammatic.
*/

// Checking front and end. Do not forget the middle character if length is odd.

class Solution {
public:
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
};

