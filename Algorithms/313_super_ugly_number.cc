/*
Write a program to find the nth super ugly number.

Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k. For example, [1, 2, 4, 7, 8, 13, 14, 16, 19, 26, 28, 32] is the sequence of the first 12 super ugly numbers given primes = [2, 7, 13, 19] of size 4.

Note:
(1) 1 is a super ugly number for any given primes.
(2) The given numbers in primes are in ascending order.
(3) 0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000.
*/

// Solution 1. Similar to ugly number.
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        if(n == 1) return 1;
        vector<int> ugly(n, 0);
        int np = primes.size(); //number of primes
        vector<int> idx(np, 0); //indices in ugly for numbers being multiplied by each prime
        vector<int> val(np, 1); //next values for each prime
        int next = 1;
        for(int i = 0; i < n; ++i) {
            ugly[i] = next; 
            next = INT_MAX; //to find minimum for next
            for(int j = 0; j < np; ++j) { //scan possible values for next
                if(val[j] == ugly[i]) val[j] = ugly[idx[j]++] * primes[j]; //move to next index
                next = min(val[j], next);
            }
        }
        return ugly[n-1];        
    }
};

// Solution 2. Using a min-queue

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
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        if(n == 1) return 1;
        vector<int> ugly(n, 1);
        priority_queue<Element, vector<Element>, isGreater> min_queue;
        for(auto k : primes) {
            min_queue.push(Element(k, k, 0));
        }
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

