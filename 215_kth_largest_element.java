/// Quick-sort order statistics. Expected running time O(n)
/// Can use 3-color sort for partition for better performance when duplicated entries exist

public class Solution {
    public int findKthLargest(int[] nums, int k) {
        return findKthUtil(nums, 0, nums.length-1, k);
    }
    
    //find Kth largest form nums[lo .. hi]
    private int findKthUtil(int[] nums, int lo, int hi, int k) {
        if (lo == hi) return nums[lo];
        int q = partition(nums, lo, hi);
        int r = q - lo + 1;
        if (k == r) return nums[q];
        else if (k < r) return findKthUtil(nums, lo, q-1, k);
        else return findKthUtil(nums, q+1, hi, k-r);
    }
    
    //partition nums[lo .. hi] around pivot nums[lo], reverse sort
    private int partition(int[] nums, int lo, int hi) {
        if(lo == hi) return lo;
        int i = lo, j = hi+1;
        int x = nums[lo];
        while (true) {
            while (nums[++i] > x) if (i == hi) break;
            while (nums[--j] < x);
            if (i < j) swap(nums, i, j);
            else break;
        }
        swap(nums, lo, j);
        return j;
    }
    
    private void swap(int[] nums, int i, int j) {
        int t = nums[i];
        nums[i] = nums[j];
        nums[j] = t;
    }
}
