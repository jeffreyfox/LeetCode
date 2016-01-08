/*
Description:

Count the number of prime numbers less than a non-negative number, n.
*/

// Sieve of Eratosthenes

// Solution 1. Not optimized solution.
class Solution {
public:
    int countPrimes(int n) {
        if(n < 2) return 0;
        vector<bool> prime(n, true); //is prime: [0, n-1]
        for(int i = 2; i*i < n; ++i) {
            for(int j = i; i*j < n; ++j) {
                prime[i*j] = false;
            }
        }
        int count = 0;
        for(int i = 2; i < n; ++i)  count += prime[i];
        return count;
    }
};

// Solution 2. Optimize solution.
class Solution {
public:
    int countPrimes(int n) {
        if(n < 2) return 0;
        vector<bool> prime(n, true); //is prime: [0, n-1]
        for(int i = 2; i*i < n; ++i) {
            if(!prime[i]) continue; //don't need to visit non-prime numbers again!
            for(int j = i*i; j < n; j += i) { // use j as index rather than i*j
                prime[j] = false;
            }
        }
        int count = 0;
        for(int i = 2; i < n; ++i)
            if(prime[i]) count ++;
        return count;
    }
};


