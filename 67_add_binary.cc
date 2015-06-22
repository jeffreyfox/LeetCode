// code works for binary and hex and oct systems, except need to change R to 8 or 16 
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
