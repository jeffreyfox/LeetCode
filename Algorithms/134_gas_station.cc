/*There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

Note:
The solution is guaranteed to be unique. 
*/

/*
Two pass DP solution using an auxiliary array to store minimum required gas from 0 to other sites. O(n) space.
To be able to complete circuit at a site i, we need to traverse i to 0, and then from 0 to i. The idea is to first figure out
the minimum amount of gas needed when traveling from site 0 to site i (required[i]). 
The second pass, we calculate the remaining gases traveling from site i to 0 (starting with an empty tank). We do it in reverse order.
If at a given site i the remaining gases are larger than the pre-calculated minimum aount of gas needed at that site, then we know for sure that we can complete the circuit at site i.
the net consumption of gas from site i-1 to i is: amount of gas available at site i-1 (gas[i-1]) - gas cost between i-1 and i (cost[i-1]) + leftovers in tank at site i-1 (leftover).
If the net consumption is positive, then the minimum required gas at site i-1 is enough. If it is negative, then we need additional gas to cover the cost from i-1 to i, thus: required[i] = required[i-1] + (net < 0 ? -net : 0);
Similarly, if the net consumption is positive, we have more leftovers, otherwise we have 0. thus: leftover = (net > 0 ? net : 0);
*/

class Solution {
    
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size(); //assume n >= 2
        vector<int> required(n, 0); //minimum required gas from 0 to i
        int leftover(0);  //leftover gas from 0 to i
        for(int i = 1; i < n; ++i) {
            int net = gas[i-1]-cost[i-1]+leftover;
            required[i] = required[i-1] + (net < 0 ? -net : 0);
            leftover = (net > 0 ? net : 0);
        }
        int remaining(0); //leftover from i to 0
        for(int i = n-1; i >= 0; --i) {
           remaining += (gas[i] - cost[i]);
           if(remaining >= required[i]) return i;
        }
        return -1;
    }
};

/*
O(1) space greedy solution. 2 passes.
Start from 0, move forward and record the lowest level in the tank (could be negative), and the associated site position. Say i, this means that, tank will reach lowest level after visiting site i, when reaching site i+1. 
If the lowest level is non-negative, then we can complete circuit at site 0. Just return 0.
Second pass starts form site i+1, and traverse to 0. Calculate the residue amount of gas after reaching 0. If the residue amount is larger than the deficit from 0 to i, then we can complete circle from site i+1.
*/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int leftover = 0, min_left = 0, min_pos = -1;
        for(int i = 0; i < gas.size(); ++i) {
            leftover += gas[i] - cost[i];
            if(leftover < min_left) {  min_left = leftover, min_pos = i; }
        }
        if(min_left >= 0) return 0;
        int residue = 0;
        for(int j = min_pos+1; j < gas.size(); ++j) {
            residue += gas[j] - cost[j];
        }
        if(residue + min_left >= 0) return min_pos+1;
        else return -1;
    }
};

/*
O(1) space greedy solution. Only 1 pass.
We can improve from the last solution by noting that we can calculate residue and leftover in the same loop. When we see a smaller tank level, we reset residue to zero. The calculation for residue is effectively the same as previous solution.
*/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int leftover = 0, min_left = 0, min_pos = -1, residue = 0;
        for(int i = 0; i < gas.size(); ++i) {
            int net = gas[i] - cost[i];
            leftover += net;
            residue += net;
            if(leftover < min_left) { 
                min_left = leftover;
                min_pos = i; 
                residue = 0;
            } 
        }
        if(residue + min_left >= 0) return min_pos+1;
        else return -1;
    }
};

