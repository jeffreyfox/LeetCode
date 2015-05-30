/// Dynamic programming solution with 3 passes of linear house-robber problem

public class Solution {
    public int rob(int[] nums) {
        int n = nums.length;
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        
        int max1 = robUtil(nums, 1, n-2); //skip two ends (0 and n-1)
        int max2 = robUtil(nums, 1, n-1); //skip left end
        int max3 = robUtil(nums, 0, n-2); //skip right end
        
        return Math.max(max1, Math.max(max2, max3));
    }
    
    // linear rob problem for a subset of houses from lo to hi
    private int robUtil(int[] nums, int lo, int hi) {
        int n = hi - lo + 1;
        if (n == 0) return 0;
        
        int[] max_inc = new int[n+1]; //max gain for robbing first i houses with additional constraint of robbing last house (i = 0 .. n)
        int[] max_all = new int[n+1]; //max gain for robbing first i houses
        
        max_inc[0] = max_all[0] = 0; //max gain for robbing 0 houses
        max_inc[1] = max_all[1] = nums[lo]; //max gain for robbing first house
        
        for (int i = 2; i <= n; ++i) { //max gain for robbing first i houses
            max_inc[i] = nums[lo+i-1] + max_all[i-2];  //be careful of nums index!
            max_all[i] = Math.max(max_inc[i], max_all[i-1]); 
        }
        return max_all[n];
    }
}
