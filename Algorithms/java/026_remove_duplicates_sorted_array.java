public class Solution {
    public int removeDuplicates(int[] nums) {
        //i: current element under investigation (jump over duplicates)
        //j: one past the end of processed array
        int n = nums.length;
        if (n <= 1) return n;
        int i = 0, j = 0;
        while (i < n) {
            while (i < n-1 && nums[i+1] == nums[i]) i++;
            nums[j++] = nums[i++];
        }
        return j;
    }
}
