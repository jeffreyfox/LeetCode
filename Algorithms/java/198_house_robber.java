/// Dynamic programming solution
public class Solution {
    public int rob(int[] nums) {
        int n = nums.length;
        if (n == 0) return 0;
        
        int[] max_inc = new int[n+1]; //max gain for robbing first i houses with additional constraint of robbing last house (i = 0 .. n)
        int[] max_all = new int[n+1]; //max gain for robbing first i houses
        
        max_inc[0] = max_all[0] = 0; //max gain for robbing 0 houses
        max_inc[1] = max_all[1] = nums[0]; //max gain for robbing first house
        
        for (int i = 2; i <= n; ++i) { //max gain for robbing first i houses
            max_inc[i] = nums[i-1] + max_all[i-2];  //be careful of nums index!
            max_all[i] = Math.max(max_inc[i], max_all[i-1]); 
        }
        return max_all[n];
    }
}
