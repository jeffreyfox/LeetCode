// use an append function. Deal with one, five, ten
class Solution {
public:
    string intToRoman(int num) {
        string s;
        int n = 0;
        if (num >= 1000) { append(s, num/1000, 'M', 'Y', 'Z'); num %= 1000; }
        if (num >= 100)  { append(s, num/100,  'C', 'D', 'M'); num %= 100;  }
        if (num >= 10)   { append(s, num/10,   'X', 'L', 'C'); num %= 10;   }
        if (num >= 1)    { append(s, num/1,    'I', 'V', 'X'); }
        return s;
    }
    //c1 is for one, c2 is for five, c3 is for ten
    void append(string& s, int d, char c1, char c2, char c3) {
        if (d == 0) return;
        else if (d <= 3) s += string(d, c1);
        else if (d == 4) { s += c1; s += c2;  }
        else if (d == 5) s += c2;
        else if (d <= 8) { s += c2; s += string(d-5, c1); }
        else if (d == 9) { s += c1; s += c3; }
    }
};
