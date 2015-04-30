// Not-so-smart solution, using a stack.
// Time O(n), space O(n)

class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if(n == 0) return 0;
        if(n == 1) return 1;
        
        int peak = 0; //local peak of rating
        int curr = 1; // number of candies for the current kid
        int tot = curr; //total number of candies
        for(int i = 1; i < n; ++i) {
            if(ratings[i] < ratings[i-1]) { //smaller or equal rating than previous
                if(curr > 1) {curr = 1; tot += curr; peak = i; }
                else { //give one more candy to all kids between peak and i
                    curr = 1;
                    tot += (i-peak+1);
                }
            } else if(ratings[i] > ratings[i-1]) { //larger rating than previous
                peak = i;
                tot += ++curr; //increment candy for current kid
            } else { //equal
                peak = i;
                curr = 1;
                tot += curr;
            }
        }
        return tot;
    }
};
