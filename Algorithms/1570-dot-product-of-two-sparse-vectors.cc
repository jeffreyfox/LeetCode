/*
Given two sparse vectors, compute their dot product.

Implement class SparseVector:

SparseVector(nums) Initializes the object with the vector nums
dotProduct(vec) Compute the dot product between the instance of SparseVector and vec
A sparse vector is a vector that has mostly zero values, you should store the sparse vector efficiently and compute the dot product between two SparseVector.

Follow up: What if only one of the vectors is sparse?

 

Example 1:

Input: nums1 = [1,0,0,2,3], nums2 = [0,3,0,4,0]
Output: 8
Explanation: v1 = SparseVector(nums1) , v2 = SparseVector(nums2)
v1.dotProduct(v2) = 1*0 + 0*3 + 0*0 + 2*4 + 3*0 = 8
Example 2:

Input: nums1 = [0,1,0,0,0], nums2 = [0,0,0,0,2]
Output: 0
Explanation: v1 = SparseVector(nums1) , v2 = SparseVector(nums2)
v1.dotProduct(v2) = 0*0 + 1*0 + 0*0 + 0*0 + 0*2 = 0
Example 3:

Input: nums1 = [0,1,0,0,2,0,0], nums2 = [1,0,0,0,3,0,4]
Output: 6
 

Constraints:

n == nums1.length == nums2.length
1 <= n <= 10^5
0 <= nums1[i], nums2[i] <= 100
*/

class SparseVector {
public:    
    SparseVector(vector<int> &nums) {
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != 0) dict[i] = nums[i];
        }
    }
        
    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec) {
        int len1 = dict.size(), len2 = vec.dict.size();
        int result = 0;
        if (len1 < len2) {
            for (const auto [idx, val] : dict) {
                auto iter = vec.dict.find(idx);
                if (iter != vec.dict.end())  result += val * iter->second;
            }
        } else {
            for (const auto [idx, val] : vec.dict) {
                auto iter = dict.find(idx);
                if (iter != dict.end())  result += val * iter->second;
            }
        }
        return result;
    }
protected:
    // position and value.
    unordered_map<int, int> dict;
};

// Your SparseVector object will be instantiated and called as such:
// SparseVector v1(nums1);
// SparseVector v2(nums2);
// int ans = v1.dotProduct(v2);
