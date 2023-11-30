class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        d = {}
        for i, val in enumerate(nums):
            res = target - val
            idx = d.get(res, -1)
            if idx >= 0:
                return [idx, i]
            d[val] = i
        return [-1, -1]
