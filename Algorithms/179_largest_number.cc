string int2str(int num) {
    if(num == 0) return string("0"); //edge case!
    int r = 0;
    string str;
    while(num) {
        r = num % 10;
        str = char(r+'0') + str;
        num /= 10;
    }
    return str;
}
    
class Solution {
public:
    struct { //return true if a needs to be placed in front of b
        bool operator() (int a, int b) {
            string sa = int2str(a), sb = int2str(b);
            return (sa+sb > sb+sa);
        }
    } myCompare;
    
    string largestNumber(vector<int> &num) {
        sort(num.begin(), num.end(), myCompare);
        if(num[0] == 0) return "0"; //edge case: all zeros

        string str;
        for(unsigned k = 0; k < num.size(); ++k) str += int2str(num[k]);
        return str;
    }
};
