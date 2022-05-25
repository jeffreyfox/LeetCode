/*
Suppose you are at a party with n people (labeled from 0 to n - 1) and among them, there may exist one celebrity. The definition of a celebrity is that all the other n - 1 people know him/her but he/she does not know any of them.

Now you want to find out who the celebrity is or verify that there is not one. The only thing you are allowed to do is to ask questions like: "Hi, A. Do you know B?" to get information of whether A knows B. You need to find out the celebrity (or verify there is not one) by asking as few questions as possible (in the asymptotic sense).

You are given a helper function bool knows(a, b) which tells you whether A knows B. Implement a function int findCelebrity(n), your function should minimize the number of calls to knows.

Note: There will be exactly one celebrity if he/she is in the party. Return the celebrity's label if there is a celebrity in the party. If there is no celebrity, return -1.
*/

// Forward declaration of the knows API.
bool knows(int a, int b);


/* Solution 1. Linear time solution O(n).
For two person i and j, check knows(i, j). Two outcomes:
1. if i knows j, then for sure i is not celebrity
2. if i does not know j, then for sure j is not celebrity.
Thus for each comparison, we can rule out one person.

We can do a linear run, each time compare the next person with the current celebrity candidate. In the end, we will have one candidate x.
Then we simply check if everyone knows x, and x does not know anyone.

One optimization is that in the first pass, we already checked that x does not know every one after x. So the second loop only checks people before x.

the last two loops can be combined into one
    for(int i = 0; i < n; ++i)
        if((i < x && knows(x, i)) || !knows(i, x) ) return -1;
*/

class Solution {
public:
    int findCelebrity(int n) {
        int x = 0;
        for(int i = 0; i < n; ++i)
            if(knows(x, i))  x = i;
        for(int i = 0; i < x; ++i)
            if(knows(x, i)) return -1;
        for(int i = 0; i < n; ++i)
            if(!knows(i, x)) return -1;
        return x;
    }
};

// Solution 2. Divide and conquer solution O(nlgn) time. O(lgn) space for the recursive calls.

class Solution {
public:
    int findCelebrity(int n) {
        int x = helper(0, n-1);
        if(x == -1) return -1;
        for(int i = 0; i < n; ++i)  {
            if(x == i) continue;
            if(knows(x, i) || !knows(i, x) ) return -1;
        }
        return x;
    }
    //check possible celebrity among [i .. j]
    int helper(int i, int j) {
        if(j == i) return i;
        int mid = (i+j)/2;
        int x1 = helper(i, mid);
        int x2 = helper(mid+1, j);
        if(x1 == -1) return x2;
        if(x2 == -1) return x1;
        if(knows(x1, x2)) return x2;
        else return x1;
    }
};

// Solution 3. similar to divide and conquer, but use auxiliary vector, O(n) space.

class Solution {
public:
    int findCelebrity(int n) {
        vector<int> curr(n, 0), next;
        for(int i = 0; i < n; ++i) curr[i] = i;
        while(curr.size() > 1) {
            for(int i = 0; i+1 < curr.size(); i += 2) {
                bool fwd = knows(curr[i], curr[i+1]);
                bool bwd = knows(curr[i+1], curr[i]);
                if(fwd ^ bwd) {
                    if(fwd) next.push_back(curr[i+1]);
                    else next.push_back(curr[i]);
                }
            }
            if(curr.size() & 1) next.push_back(curr.back());
            curr.swap(next);
            next.clear();
        }
        //finally check the only possible candidate
        if(curr.empty()) return -1;
        int j = curr[0];
        for(int k = 0; k < n; ++k) {
            if(k == j) continue;
            if(!knows(k, j) || knows(j, k)) return -1;
        }
        return j;
    }
};

