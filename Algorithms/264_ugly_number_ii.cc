/*
Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.

Note that 1 is typically treated as an ugly number.

Hint:

    The naive approach is to call isUgly for every number until you reach the nth one. Most numbers are not ugly. Try to focus your effort on generating only the ugly ones.
    An ugly number must be multiplied by either 2, 3, or 5 from a smaller ugly number.
    The key is how to maintain the order of the ugly numbers. Try a similar approach of merging from three sorted lists: L1, L2, and L3.
    Assume you have Uk, the kth ugly number. Then Uk+1 must be Min(L1 * 2, L2 * 3, L3 * 5).
*/

// Solution: http://www.geeksforgeeks.org/ugly-numbers/
// All ugly numbers are built from the following three lists:
// (1) 1x2 2x2 3x2 4x2 5x2 6x2 8x2
// (2) 1x3 2x3 3x3 4x3 5x3 6x3 8x3
// (3) 1x5 2x5 3x5 4x5 5x5 6x5 8x5
// Where (1) is built from the exact ugly number sequence multiple by 2, and similar for (2) and (3). So we could use dynamic programming to generate the next ugly number from previous ones. The key is to maintain the order.
// To solve this, we keep track of which is the last ugly number used in each list, for example, 4 in (1), 3 in (2), and 2 in (5), then the next ugly number will be the minimum of 4x2, 3x3, and 2x5. We found the minimum is 4x2 from (1), then we advance pointer in (1) to 5. We store all the previous ugly numbers in an array so that we can use three pointers to point to the approapriate entry in the array and easily find the next ugly number for each list by advancing the pointers. 
// There might be duplicates in the lists, so we need to test each list.

// A simple solution with many array addressing (a bit slower)
class Solution {
public:
    int nthUglyNumber(int n) {
        if(n == 1) return 1;
        int mult2 = 1, mult3 = 1, mult5 = 1;
        vector<int> ugly(n, 1);
        int i2 = 0, i3 = 0, i5 = 0; //index in ugly array
        for(int i = 1; i < n; ++i) {
            ugly[i] = min(min(ugly[i2]*2, ugly[i3]*3), ugly[i5]*5);
            if(ugly[i] == ugly[i2]*2) i2++;
            if(ugly[i] == ugly[i3]*3) i3++;
            if(ugly[i] == ugly[i5]*5) i5++;
        }
        return ugly[n-1];
    }
};

// A faster version avoiding array addressing by using intermediate variable mult and next
class Solution {
public:
    int nthUglyNumber(int n) {
        if(n == 1) return 1;
        int mult2 = 1, mult3 = 1, mult5 = 1;
        vector<int> ugly(n, 1);
        int i2 = 0, i3 = 0, i5 = 0; //index in ugly array
        for(int i = 1; i < n; ++i) {
            int next = min(min(mult2*2, mult3*3), mult5*5);
            ugly[i] = next;
            if(next == mult2*2) mult2 = ugly[++i2];
            if(next == mult3*3) mult3 = ugly[++i3];
            if(next == mult5*5) mult5 = ugly[++i5];
        }
        return ugly[n-1];
    }
};

// A solution using priority queue
struct Element {
    int val;
    int prime;
    int index;
    Element() : val(0), prime(0), index(0) {}
    Element(int v, int p, int i) : val(v), prime(p), index(i) {}
};

class isGreater
{
public:
    bool operator() (const Element& e1, const Element &e2) {
        return e1.val > e2.val;    
    }
};


class Solution {
public:
    int nthUglyNumber(int n) {
        if(n == 1) return 1;
        vector<int> ugly(n, 1);
        priority_queue<Element, vector<Element>, isGreater> min_queue;
        min_queue.push(Element(2, 2, 0));
        min_queue.push(Element(3, 3, 0));
        min_queue.push(Element(5, 5, 0));
        for(int i = 1; i < n; ++i) {
            int val = min_queue.top().val;
            while(min_queue.top().val == val) { //remove all duplicates
                Element next = min_queue.top();
                min_queue.pop();
                ugly[i] = next.val;
                next.val = ugly[++next.index]*next.prime;
                min_queue.push(next);
            }
        }
        return ugly[n-1];
    }
};
