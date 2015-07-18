class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        vector<int> ret(n, 0);
        int carry = 1;
        for (int i = n-1; i >=0; --i) {
            int sum = digits[i] + carry;
            ret[i] = sum % 10;
            carry = sum / 10;
        }
        if (carry == 1) ret.insert(ret.begin(), 1);
        return ret;
    }
};
