/*
Given a non-negative number represented as an array of digits, plus one to the number.

The digits are stored such that the most significant digit is at the head of the list.
*/

// Optimization: copy digits to result, and then stop when carry == 0

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> result;
        if(digits.empty()) return result;
        int n = digits.size();
        result = digits;
        int carry = 1, sum = 0;
        for(int i = n-1; i >= 0 && carry > 0; i--) {
            sum = digits[i] + carry;
            carry = sum / 10;
            sum %= 10;
            result[i] = sum; //update result
        }
        if(carry > 0) result.insert(result.begin(), 1); //add a leading 1
        return result;
    }
};
