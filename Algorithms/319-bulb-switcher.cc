// Simply counting the number of square numbers

class Solution {
public:
    int bulbSwitch(int n) {
        int k = 1;
        int result = 0;
        while (k*k <= n) {
            result ++;
            k++;
        }
        return result;
    }
};
