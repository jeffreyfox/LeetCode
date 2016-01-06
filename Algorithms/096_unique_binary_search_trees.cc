/*
Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

*/

// Dynamic programming. The ways of forming tree of size n can be found by choosing each of the n elements as root, which divides the others as left and right subtrees.

class Solution {
public:
    int numTrees(int n) {
        if(n < 0) return 0;
        if(n == 0 || n == 1) return 1;
        vector<int> count(n+1, 0); //store counts from i=0 to n
        count[0] = count[1] = 1;
        //calculate number of unique trees of size i
        for(int i = 2; i <= n; ++i) {
            //pick k-th number as root, then k elements as left-tree, i-k-1 elements as right-tree
            for(int k = 0; k < i; ++k) {
                count[i] += count[k]*count[i-k-1];
            }
        }
        return count[n];
    }
};

