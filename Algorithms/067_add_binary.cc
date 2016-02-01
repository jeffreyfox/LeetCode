/*
Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100". 
*/

// General solution that works for binary (R = 2), octal (R = 8) and hexadecimal (R = 16)  systems.

class Solution {
public:
    string addBinary(string a, string b) {
        const int R = 2; //radix for binary system (R = 8/16 for oct/hex)
        int m = a.size(), n = b.size();
        int l = max(m, n);
        string c(l, '0');
        int carry(0), sum(0); 
        for (int i = 0; i < l; ++i) {
            int v1 = (i < m) ? char2int(a[m-1-i]) : 0;
            int v2 = (i < n) ? char2int(b[n-1-i]) : 0;
            sum = carry + v1 + v2;
            carry = sum / R;
            sum = sum % R;
            c[l-1-i] = int2char(sum);
        }
        if (carry > 0) c = "1" + c;
        return c;
    }
    
    int char2int(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        return 0;
    }
    
    char int2char(int n) {
        if (n >= 0  && n <= 9)  return n + '0';
        if (n >= 10 && n <= 15) return n - 10 + 'A';
        return '0';
    }
};

/* Another solution using bit operator to calculate sum and carry
            sum = v1 ^ v2 ^ carry;
            carry = (v1 & v2) | (v1 & carry) | (v2 & carry);

// An alternative is use:
            sum = v1 + v2 + carry;
            carry = sum / 2;
            sum %= 2;
*/

class Solution {
public:
    string addBinary(string a, string b) {
        int l1 = a.size(), l2 = b.size();
        int l = max(l1, l2);
        string result(l, '0');
        int sum = 0, carry = 0;
        //i counts from right to left
        for(int i = 0; i < l; ++i) {
            int v1 = (i >= l1) ? 0 : a[l1-i-1] - '0';
            int v2 = (i >= l2) ? 0 : b[l2-i-1] - '0';
            sum = v1 ^ v2 ^ carry;
            carry = (v1 & v2) | (v1 & carry) | (v2 & carry);
            result[l-i-1] = sum + '0';
        }
        if(carry > 0) result = '1' + result;
        return result;
    }
};
