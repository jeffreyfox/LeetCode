/// Use a hash map (set) to record all numbers and check if we encounter a previous one (loop).
/// If found a "1" then is a happy number, otherwise not.
class Solution {
public:
    bool isHappy(int n) {
        set<int> occur;
        occur.insert(n);
        while(1) {
            n = next(n);
            if(n == 1) return true;
            if(occur.find(n) != occur.end()) return false;
            occur.insert(n);
        }
    }
    
    int next(int n) {
        int sum = 0;
        while(n > 0) {
            int res = n % 10;
            sum += res*res;
            n = n / 10;
        }
        return sum;
    }
};
