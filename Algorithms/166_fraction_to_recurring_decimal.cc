/*
Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

For example,

    Given numerator = 1, denominator = 2, return "0.5".
    Given numerator = 2, denominator = 1, return "2".
    Given numerator = 2, denominator = 3, return "0.(6)".
*/

// Use a table to track the first occuring position of residue, add corresponding quotient to decimal string, also take care of sign
// caveat: use long for all integer variables to avoid integer overflow!

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        long a = numerator, b = denominator; //use long to avoid overflow!
        bool negative = (a < 0 && b > 0) || (a > 0 && b < 0);
        a = abs(a), b = abs(b); //get absolute value
        long q = a / b, r = a % b;
        string integer = int2str(q);
        if(negative) integer = '-' + integer;
        if(r == 0) return integer;
        
        string decimal;
        int i = 0; //position of decimal
        unordered_map<long, int> table; // the place in decimal that a given r value has appeared the first time
        do {
            q = (r*10) / b;
            if(!table.count(r)) { // not found
                table[r] = i;
                decimal += char(q + '0');
            } else { //found!
                int j = table[r];
                decimal.insert(j, "(");
                decimal += ")";
                break;
            }
            r = (r*10) % b; //update r
            i++; //update i
        } while(r);
        return integer + "." + decimal;
    }

    string int2str(long val) {
        string s;
        do {
            s = char(val % 10 + '0') + s;
            val /= 10;
        } while(val);
        return s;
    }
};
