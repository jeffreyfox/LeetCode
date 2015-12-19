/*
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
*/

/* Solution implementing an algorithm to generate permutation sequence in lexigraphical order
How is lexigraphical order generated?

For the permutations with the same prefix, the following sub permutations should also be in lexigraphical order, e.g.
13245, 13254, 13425, 13452 ... (same prefix 13, then 2,4,5 are permutaed in lexi-order as well).

For a group of numbers, the first one in the lexi-order is the ascending sequence, the last one is the descending sequence.

We scan right to left, if we see a subsequence that is descending, that part is already the last one of its own lexi-order. For example:

1,2,5,4,3. What is next step? Since we finished the last three positions, we need to proccess 2, basically move to the next larger one, 3.
How to find 3 ? we utilize the descending order of array 5,4,3 we search from right to left and find the first element larger than 2, and it will be the next one. We simply swap it with 2, and the resulting array 5,4,2 will still be descending. We need to reverse it to make it ascending (as the first permutation in the new sub-array 2,4,5). Therefore, here is the whole procedure:

1. Find the largest index k such that a[k] < a[k + 1]. If no such index exists, the permutation is the last permutation.
2. Find the largest index l greater than k such that a[k] < a[l].
3. Swap the value of a[k] with that of a[l].
4. Reverse the sequence from a[k + 1] up to and including the final element a[n].

Since the comparisons are strict, we will not perform unecessary swaps in the case of duplicated ent
ries. So the algorithm works for duplicated entries as well.
*/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int k = n-2, l = n-1;
        while(k >= 0 && nums[k] >= nums[k+1]) k--;
        //k is the last k such that nums[k] < nums[k+1]
        if(k == -1) { //no next, just reverse it to 1st lexi-order
            int i = 0, j = n-1;
            while(i < j) swap(nums[i++], nums[j--]);
            return;
        }
        while(l > k && nums[l] <= nums[k]) l--;
        //l is the last l such that nums[l] > nums[k]
        //swap nums[k] and nums[l]
        swap(nums[k], nums[l]);
        //sort numbers after k
        int i = k+1, j = n-1;
        while(i < j) swap(nums[i++], nums[j--]);
    }
};

