/// Use an additional counter 

public class Solution {
    public int removeDuplicates(int[] nums) {
        //i: current element under investigation (jump over duplicates)
        //j: one past the end of processed array
        int n = nums.length;
        if (n <= 1) return n;
        int i = 0, j = 0;
        int count = 1;
        while (i < n) {
            count = 1;
            while (i < n-1 && nums[i+1] == nums[i]) { i++; count++;}
            nums[j++] = nums[i];
            if (count > 1) nums[j++] = nums[i];
            i++;
        }
        return j;
    }
}
