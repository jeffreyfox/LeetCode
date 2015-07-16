/// Just minic the elementary school multiplication method
///      1 2 3 4   (num[2], outer loop)
///    x   5 6 7   (num[1], inner loop)
/// -------------
///      8 6 3 8
///    7 4 0 4
///  6 1 7 0
/// -------------
///  6 9 9 6 7 8
/// product of num1[i] and num2[j] should be aligned to num[i+j+1], because:
/// l - 1 - (l1-1-i + l2-1-j) = i+j+1
/// each time inner loop is done, the carry should go to num[i].
/// In the end, strip off the leading zeros of the string
class Solution {
public:
    string multiply(string num1, string num2) {
        int l1 = num1.size(), l2 = num2.size();
        int l = l1+l2;
        string num(l, '0');
        int carry = 0, prod = 0;
        for (int i = l1-1; i >= 0; --i) {
            carry = 0;
            for (int j = l2-1; j >= 0; --j) {
                prod = (num1[i] - '0') * (num2[j] - '0') + (num[i+j+1] - '0') + carry;
                carry = prod / 10;
                prod = prod % 10;
                num[i+j+1] = prod + '0';
            }
            num[i] = carry + '0';
        }
        
        //find first_not_of ('0')
        int k = 0;
        for (k = 0; k < l; ++k) 
            if (num[k] != '0') break;
        if (k == l) return "0";
        else return num.substr(k, l-k);
    }
};
