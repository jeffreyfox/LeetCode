// Two pointers. Track the first 0 and the last 0.
// Compute the number of flowers that can be planted based on the length of the 0 streaks. Needs to pay special attention to boundary
// conditions.
// N 0's between two 1's: the max planted flowers are (N-1) / 2.
// Iff one side of the 0's is at the boundary and N is even, we can place an addtional one (e.g. 0 0 0 0 1 => 2 flowers)
// Iff two sides of the 0's are at the boundary and N is odd, we can place an addtional one (e.g. 0 0 0 => 2 flowers)
// Another approach is to apply greedy approach and plant flowers as we scan the vector immediately when allowed to do so. After that continue scanning.

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int i = 0, j = 0;
        int size = flowerbed.size();
        int n_allowed = 0;
        while (i < size) {
            while (i < size && flowerbed[i] == 1) i++;
            // i points to the first 0
            if (i == size) break;
            int j = i;
            while (j < size && flowerbed[j] == 0) j++;
            // j points to one element past the last 0.
            n_allowed += (j - i - 1)/ 2;
            if ((i == 0 || j == size) && (j - i) % 2 == 0) n_allowed++;
            if ((i == 0 && j == size) && (j - i) % 2 == 1) n_allowed++;
            i = j;
        }
        return n_allowed >= n;
    }
};
