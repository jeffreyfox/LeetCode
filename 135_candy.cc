/*
The idea is as follows: assign as few candies as possible. First assign 1 candy to the first kid, 
then go through the kid one by one. If we encounter kids in increasing rating value, we simply 
increment the candy number for each kid and we are done. But if we encounter kids in decreasing 
rating value, we need to fix previous candy values to avoid zero or negative candies to the current kid. 
Thus I use a stack to keep track of the kids with decreasing ratings, so that we can give more candies 
to them when the 2nd requirement is violated. I use a subroutine clearStack to count the actual number 
of candies required for these kids. For each kid, there are three cases:

1. current kid has higher rating than previous kid: in this case, we assign one more candy to this kid. 
Also pop all previous kids out (and count candies for them), and push current kid's candy number
2. current kid has equal rating to previous kid: we just assign 1 candy to this kid. Use the same stack operation as 1.
3. current kid has less rating to previous kid: we also assign only 1 candy to this kid temporarily, 
and push it to stack (to be fixed later)
I also use a sentinel in the end of ratings to trigger clearStack at the last element.

Time O(n), space O(n)
*/
class Solution {
public:
    int candy(vector<int>& ratings) {
        ratings.insert(ratings.end(), INT_MAX); //sentinel
        int n = ratings.size();
        if(n <= 1) return n;
        int sum(0), curr(0);
        stack<int> s;
        s.push(1); //candy for first kid
        for(int k = 1; k < n; ++k) {
            if(ratings[k] >= ratings[k-1]) { //larger than previous
                if(ratings[k] == ratings[k-1]) curr = 1;
                else curr = s.top()+1;
                sum += clearStack(s); //count all previous
                s.push(curr); //push current candy number in stack (not count yet)
            } else { //smaller than previous
                s.push(1); //just give one candy to this kid, not count yet
            }
        }

        return sum;
    }
    
    int clearStack(stack<int>& s) {
        int sum = 0;
        int curr(0), last(0);
        while(!s.empty()) {
            int curr = s.top(); s.pop();
            if(curr <= last) curr = last+1;
            sum += curr;
            last = curr;
        }
        return sum;
    }
};
