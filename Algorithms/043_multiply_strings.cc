/*
Given two numbers represented as strings, return multiplication of the numbers as a string.

Note: The numbers can be arbitrarily large and are non-negative.
*/

/// Just minic the elementary school multiplication method
///      1 2 3 4   (num2, outer loop)
///    x   5 6 7   (num1, inner loop)
/// -------------
///      8 6 3 8
///    7 4 0 4
///  6 1 7 0
/// -------------
///  6 9 9 6 7 8
/// If nums1 and num2 have l1 and l2 digits, without carry over, the product will have l1+l2-1 digits. In this way, product of num1[i] and num2[j] should be aligned to num[i+j].
/// Start from the bottom up. Update the result in-place (instead of creating intermediate strings to store the products)
/// each time inner loop is done, the carry should go to result[i-1] or additional carry digit.

class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0") return "0";
        int l1 = num1.size(), l2 = num2.size();
        string result(l1+l2-1, '0'); // result has l1+l2-1 digits
        int sum = 0, carry = 0;
        for(int i = l1-1; i >= 0; --i) {
            carry = 0;
            for(int j = l2-1; j >= 0; --j) {
                sum = (num1[i] - '0')*(num2[j] - '0') + (result[i+j] - '0') + carry;
                carry = sum / 10;
                sum %= 10;
                result[i+j] = sum + '0';
            }
            if(carry > 0) {
                if(i > 0) result[i-1] = carry + '0'; 
                else result = char(carry + '0') + result;
            }
        }
        
        return result;
    }
};

// Another solution, create an intemediate string for products, shift the products to correct positions by appending proper number of zeroes, and add products together. Optimization on the for loops, so that roughly strings of similar lengths are added. But still very slow ...
class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0") return "0";
        int l1 = num1.size(), l2 = num2.size();
        string result = "0";
        for(int k = 0; k < l1+l2-1; ++k) {
            for(int i = max(0, k-l2+1); i <= min(k, l1-1); ++i) {
                int j = k-i;
                char c1 = num1[l1-i-1], c2 = num2[l2-j-1];
                string prod = num2str((c1-'0')*(c2-'0'));
                prod.append(k, '0');
                result = add(result, prod);
            }
        }
        return result;
    }
    
    string num2str(int num) {
        if(num == 0) return "0";
        string result;
        while(num) {
            result = char(num % 10 + '0') + result;
            num /= 10;
        }
        return result;
    }

    string add(const string& num1, const string& num2) {
        int l1 = num1.size(), l2 = num2.size();
        int l = max(l1, l2);
        string result(l, '0');
        int sum = 0, carry = 0;
        for(int i = 0; i < l; ++i) {
            if(i >= l1) sum = (num2[l2-i-1] - '0') + carry;
            else if(i >= l2) sum = (num1[l1-i-1] - '0') + carry;
            else sum = (num1[l1-i-1]-'0') + (num2[l2-i-1]-'0') + carry;
            carry = sum / 10;
            sum %= 10;
            result[l-i-1] = sum + '0';
         }
         if(carry == 1) result = '1' + result;
         return result;
    }
};

// A better solution by multiplying string to each integer number, and adding the result together. The key is function:
// string multiply(const string& num, int d)

class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0") return "0";
        string result = "0";
        if(num1.size() < num2.size()) num1.swap(num2); //longer one first
        int l1 = num1.size(), l2 = num2.size();
        for(int i = 0; i < l2; ++i) {
            string prod = multiply(num1, num2[l2-i-1]-'0');
            prod.append(i, '0');
            result = add(prod, result);
        }
        return result;
    }
    
    string num2str(int num) {
        if(num == 0) return "0";
        string result;
        while(num) {
            result = char(num % 10 + '0') + result;
            num /= 10;
        }
        return result;
    }

    string multiply(const string& num, int d) {
        if(d == 0) return "0";
        else if(d == 1) return num;
        int n = num.size();
        string result(n, '0');
        int sum = 0, carry = 0;
        for(int i = 0; i < n; ++i) {
            sum = (num[n-i-1] - '0')*d + carry;
            carry = sum / 10;
            sum %= 10;
            result[n-i-1] = sum + '0';
        }
        if(carry > 0) result = char(carry + '0') + result;
        return result;
    }

    string add(const string& num1, const string& num2) {
        int l1 = num1.size(), l2 = num2.size();
        int l = max(l1, l2);
        string result(l, '0');
        int sum = 0, carry = 0;
        for(int i = 0; i < l; ++i) {
            if(i >= l1) sum = (num2[l2-i-1] - '0') + carry;
            else if(i >= l2) sum = (num1[l1-i-1] - '0') + carry;
            else sum = (num1[l1-i-1]-'0') + (num2[l2-i-1]-'0') + carry;
            carry = sum / 10;
            sum %= 10;
            result[l-i-1] = sum + '0';
         }
         if(carry == 1) result = '1' + result;
         return result;
    }
};
