/*
Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

Example: 19 is a happy number

    12 + 92 = 82
    82 + 22 = 68
    62 + 82 = 100
    12 + 02 + 02 = 1
*/

/// Use a hash map (set) to record all numbers and check if we encounter a previous one (loop).
/// If found a "1" then is a happy number, otherwise not.
class Solution {
public:
    bool isHappy(int n) {
        if(n == 0) return false;
        if(n == 1) return true;
        unordered_set<int> dict;
        dict.insert(1);
        while(dict.count(n) == 0) {
            dict.insert(n);
            n = calc(n);
        }
        return n == 1;
    }
    
    int calc(int n) {
        int result = 0;
        while(n) {
            int r = n % 10;
            result += r*r;
            n /= 10;
        }
        return result;
    }
};
