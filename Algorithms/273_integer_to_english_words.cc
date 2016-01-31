/*
Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 231 - 1.

For example,

123 -> "One Hundred Twenty Three"
12345 -> "Twelve Thousand Three Hundred Forty Five"
1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

Hint:

    Did you see a pattern in dividing the number into chunk of words? For example, 123 and 123000.
    Group the number by thousands (3 digits). You can write a helper function that takes a number less than 1000 and convert just that chunk to words.
    There are many edge cases. What are some good test cases? Does your code work with input such as 0? Or 1000010? (middle chunk is zero and should not be printed out)
*/

// Break into 1000 chunks, consider many edge cases.

const vector<string> ones = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
const vector<string> tens = {"Zero", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
const vector<string> bases = {"", "Thousand", "Million", "Billion"};

class Solution {
public:
    string numberToWords(int num) {
        if(num == 0) return "Zero";
        string str;
        int base = 1000000000;
        int k = 3;
        while(base) {
            if(num >= base) {
                int v = num / base;
                if(!str.empty()) str += " ";
                if(k > 0) str += numberBelow1000(v) + " " + bases[k];
                else str += numberBelow1000(v);
                num %= base;
            }
            base /= 1000;
            k--;
        }
        return str;
    }
    
    string numberBelow1000(int num) {
        string str;
        
        int d1 = num / 100; 
        num %= 100;
        if(d1 != 0) str += ones[d1] + " Hundred";
        if(num == 0) ;
        else if(num < 20) str += (str.empty() ? ones[num] : " " + ones[num]);
        else { // num >= 20
            int d2 = num / 10, d3 = num % 10;
            if(d2 != 0) str += (str.empty() ? tens[d2] : " " + tens[d2]);
            if(d3 != 0) str += (str.empty() ? ones[d3] : " " + ones[d3]);
        }
        return str;
    }
};

