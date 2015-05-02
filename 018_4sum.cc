// O(n3) solution, need to take care of duplicated entries (lines 15, 18, and 31)

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        
        vector<vector<int> > ret;
        
        int n = nums.size();
        if(n <= 3) return ret;
        vector<int> sol(4, 0);
        sort(nums.begin(), nums.end());
        
        for(int i = 0; i < n; ++i) { 
            if(i > 0 && nums[i] == nums[i-1]) continue; //ignore duplicates
            
            for(int j = i+1; j < n; ++j) {
                if(j > i+1 && nums[j] == nums[j-1]) continue; //ignore duplicates
                int res = target-(nums[i]+nums[j]);
                int lo = j+1, hi = n-1; //linear search for the other two
           
                while(lo < hi) {
                
                    if(nums[lo] + nums[hi] > res) hi--;
                    else if(nums[lo] + nums[hi] < res) lo++;
                    else { //equal
                        sol[0] = nums[i], sol[1] = nums[j];
                        sol[2] = nums[lo]; sol[3] = nums[hi];
                        ret.push_back(sol);
                        hi--; //just decrement hi to search next (can also increment lo)
                        while(lo < hi && nums[hi] == nums[hi+1]) hi--; //avoid duplicates
                    }
                }
            }
        }
        return ret;
    }
    
    //search target in sorted array nums[k..end)
    int find(vector<int>& nums, int k, int target) {
        int lo = k, hi = nums.size()-1;
        while(lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if(target < nums[mid]) hi = mid-1;
            else if(target > nums[mid]) lo = mid+1;
            else return mid;
        }
        return -1;
    }
};
