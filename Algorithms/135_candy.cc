/*
There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

    Each child must have at least one candy.
    Children with a higher rating get more candies than their neighbors.

What is the minimum candies you must give? 
*/

/*
Solution 1. Two passes, once from left to right, once reverse. Keep an array storing current candies assigned to each kid. If see a higher rating than previous, assign 1 more candy compared to previous, otherwise assign 1.
*/

class Solution {
public:
    int candy(vector<int>& ratings) {
        if(ratings.empty()) return 0;
        int n = ratings.size();
        if(n == 1) return 1;
        vector<int> candies(n, 1);
        int tot = 0;
        for(int i = 1; i < n; ++i) {
            if(ratings[i] > ratings[i-1])  candies[i] = candies[i-1] + 1;
        }
        tot += candies[n-1];
        for(int i = n-2; i >= 0; --i) {
            if(ratings[i] > ratings[i+1])  candies[i] = max(candies[i], candies[i+1] + 1);
            tot += candies[i];
        }
        return tot;
    }
};

/*
Solution 2. O(n) one pass and O(1) space. Keep a variable curr for candies assigned to current kid. Three cases:
1. If new kid has higher rating, increment curr, and add it to total.
2. If equal rating, give only one candy and add it to total.
3. If smaller, then use another pointer j to scan forward and find the streak of descending ratings. Then start assigning candies 1, 2, ... starting from end of streak to i. Position i is special in that we might need to increment its current assigned value to satisfy the right side.
rating:    2 5 8 6 4 2 1 2
candy:    1 2 3 4 3 2 1 2  = > 1 2 5 4 3 2 1.
                     i          j-1  j
rating:    2 5 8 6 7 8
candy:    1 2 3 2 1 2   = > unchanged.
                     i    j-1  j
Two ways to sum up the candies in the descending streak, one is decrement curr and add it to total until curr == 0. The other is to use formula for sums : 1+2+...+n , the first one turns out to be faster in the test examples.
*/

class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if(n <= 1) return n;
        int curr = 1, total = 1; //one candy to first kid
        int i = 1, j = 0;
        while(i < n) {
            if(ratings[i] == ratings[i-1]) {
                curr = 1; total += curr; i++;
            } else if(ratings[i] > ratings[i-1]) {
                curr += 1; total += curr; i++;
            } else { //a[i] < a[i-1]
                j = i+1;
                while(j < n && ratings[j] < ratings[j-1]) j++;
                //descending streak from i-1 to j-1 (candies 1, 2, ..., j-i, max(j-i+1, a[i-1]))
                //i should be maximum of j-i and a[i]
                total += max(j-i+1 - curr, 0); //give extra candies to a[i-1] if necessary
                curr = j-i;
                while(curr > 0) total += curr--;
                //total += (j-i+1)*(j-i)/2;
                curr = 1;
                i = j;
            }
        }
        return total;
    }
};

/*
Solution 3. An old solution similar to Solution 2 but unecessarily uses a stack

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

