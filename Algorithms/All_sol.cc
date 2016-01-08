/**************************************************** 
 ***    312,Hard,Burst Balloons 
 ****************************************************/

/*
Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

Note:
(1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
(2) 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100

Example:

Given [3, 1, 5, 8]

Return 167

    nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
   coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167

Credits:
Special thanks to @dietpepsi for adding this problem and creating all test cases.
*/

/*
Standard dynamic programming. Use dp[i][j] to store the maximum coins for popping balloons [i .. j]. There are l = j-i+1 possibilities, each corresponds to popping k-th balloon at last ( i <= k <= j). The points obtained in this scenario is:

  i-1 i ... k-1 k k+1 ... j j+1
We keep k until the last step, so the coins we get will be the coins won from breaking [i .. k-1], and [k+1 .. j], and in the end, we are left with [i-1, k, j+1], so the last step we get nums[i-1]*nums[k]*nums[j+1].

To avoid array bounds checking, we insert 1 to front and end of the nums array.

We also need to have n+2 dimension for the dp vector.
*/

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.push_back(1);
        nums.insert(nums.begin(), 1);
        //dp[i][j]:  the maximum coins for nums[i .. j], 1 <= i <= j <= n
        vector<vector<int> > dp(n+2, vector<int>(n+2, 0));
        for(int len = 1; len <= n; ++len) {
            for(int i = 1; i + len <= n+1; ++i) {
                int j = i+len-1;
                //now check max for nums[i .. j], try all cases where k breaks last (i <= k <= j)
                for(int k = i; k <= j; ++k) {
                    dp[i][j] = max(dp[i][j], dp[i][k-1] + dp[k+1][j] + nums[i-1]*nums[k]*nums[j+1]);
                }
            }
        }
        return dp[1][n];
    }
};


/**************************************************** 
 ***    308,Hard,Range Sum Query 2D - Mutable 
 ****************************************************/

/*
Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:

Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
update(3, 2, 2)
sumRegion(2, 1, 4, 3) -> 10

Note:

    The matrix is only modifiable by the update function.
    You may assume the number of calls to update and sumRegion function is distributed evenly.
    You may assume that row1 ≤ row2 and col1 ≤ col2.
*/

// Your NumMatrix object will be instantiated and called as such:
// NumMatrix numMatrix(matrix);
// numMatrix.sumRegion(0, 1, 2, 3);
// numMatrix.update(1, 1, 10);
// numMatrix.sumRegion(1, 2, 3, 4);

// 2D binary indexed tree.

class NumMatrix {
public:
    NumMatrix(vector<vector<int>> &matrix) {
        if(matrix.empty() || matrix[0].empty()) {
            m = n = 0;
            return;
        }
        m = matrix.size(); n = matrix[0].size();
        bitsum.resize(m+1, vector<int>(n+1, 0));
        num.resize(m+1, vector<int>(n+1, 0));
        for(int i = 0; i < m; ++i) 
            for(int j = 0; j < n; ++j)
                update(i, j, matrix[i][j]);
    }

    void update(int row, int col, int val) {
        int delta = val - num[++row][++col];
        num[row][col] = val;
        int irow = row, jcol = col;
        while(irow <= m) {
           jcol = col;
           while(jcol <= n) {
               bitsum[irow][jcol] += delta;
               jcol += (jcol & (-jcol));
           }
           irow += (irow & (-irow));
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return getSum(row2, col2) - getSum(row1-1, col2) - getSum(row2, col1-1) + getSum(row1-1, col1-1);
    }

private:
    //get sum from [0, 0] to [row, col]
    int getSum(int row, int col) {
        if(row < 0 || row >= m || col < 0 || col >= n) return 0;
        row++; col++;
        int sum = 0;
        int irow = row, jcol = col;
        while(irow > 0) {
            jcol = col;
            while(jcol > 0) {
                sum += bitsum[irow][jcol];
                jcol -= (jcol & (-jcol));
            }
            irow -= (irow & (-irow));
        }
        return sum;
        
    }
    int m, n;
    vector<vector<int> > bitsum, num;
};


/**************************************************** 
 ***    307,Medium,Range Sum Query - Mutable 
 ****************************************************/

/*
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.
The update(i, val) function modifies nums by updating the element at index i to val.

Example:

Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8

Note:

    The array is only modifiable by the update function.
    You may assume the number of calls to update and sumRange function is distributed evenly.
*/

// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.update(1, 10);
// numArray.sumRange(1, 2);

// Solution using binary indexed tree, find and update both O(logn).
// A little tricky in update function. Need to calculate the difference between current value and old value.
// Also uses 1-based indexing, so need to take care of the offset.

class NumArray {
public:
    NumArray(vector<int> &nums) {
        n = nums.size(); //0 is dummy node
        bitsum.resize(n+1, 0);
        num.resize(n+1, 0);
        for(int i = 0; i < n; ++i) {
           update(i, nums[i]); //i is index in nums
        }
    }

    int sumRange(int i, int j) {
        if(i > j || i < 0 || j >= n) return 0;
        if(i == j) return num[i+1];
        return getSum(j) - getSum(i-1);
    }

    void update(int i, int val) {
        int error = val - num[++i];
        num[i] = val;
        while(i <= n) {
            bitsum[i] += error;
            i += (i & (-i)); 
        }
    }
private:
    //accumulated sum from nums[0 .. i]
    int getSum(int i) {
        if(i < 0 || i >= n) return 0;
        i++;
        int sum = 0;
        while(i > 0) {
            sum += bitsum[i];
            i -= (i & (-i));
        }
        return sum;
    }
    vector<int> num;
    vector<int> bitsum;
    int n;
};


/**************************************************** 
 ***    305,Hard,Number of Islands II 
 ****************************************************/

/*
A 2d grid map of m rows and n columns is initially filled with water. We may perform an addLand operation which turns the water at position (row, col) into a land. Given a list of positions to operate, count the number of islands after each addLand operation. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example:

Given m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]].
Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).

0 0 0
0 0 0
0 0 0

Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.

1 0 0
0 0 0   Number of islands = 1
0 0 0

Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.

1 1 0
0 0 0   Number of islands = 1
0 0 0

Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.

1 1 0
0 0 1   Number of islands = 2
0 0 0

Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.

1 1 0
0 0 1   Number of islands = 3
0 1 0

We return the result as an array: [1, 1, 2, 3]

Challenge:

Can you do it in time complexity O(k log mn), where k is the length of the positions?
*/

// Weighted union find with path compression by halving.
// See Solution to Problem 200 for details.

class UnionFind {
public:
    UnionFind(int N) : n(0) {
        id.resize(N, -1);
        size.resize(N, 0);
    }
    void add(int i) {
        id[i] = i; size[i] = 1;
        n++;
    }
    void uni(int i, int j) {
        if(id[j] == -1) return; //only add valid ones
        while(id[i] != i) { id[i] = id[id[i]]; i = id[i]; }
        while(id[j] != j) { id[j] = id[id[j]]; j = id[j]; }
        if(i != j) {
            if(size[i] < size[j]) { id[i] = j; size[j] += size[i]; }
            else { id[j] = i; size[i] += size[j]; }
            n--;
        }
    }

    int count() const { return n; }

private:
    vector<int> id;
    vector<int> size;
    int n;
};

class Solution {
public:
    vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
        int size = positions.size();
        vector<int> result(size, 0);
        UnionFind uf(m*n);
        for(int i = 0; i < size; ++i) {
            const int &x = positions[i].first, &y = positions[i].second;
            int idx = x*n+y;
            uf.add(idx);
            //check four neighbors
            if(x > 0) uf.uni(idx, idx-n);
            if(x < m-1) uf.uni(idx, idx+n);
            if(y > 0) uf.uni(idx, idx-1);
            if(y < n-1) uf.uni(idx, idx+1);
            result[i] = uf.count();
        }
        return result;
    }
};


/**************************************************** 
 ***    304,Medium,Range Sum Query 2D - Immutable 
 ****************************************************/

/*
Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:

Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12

Note:

    You may assume that the matrix does not change.
    There are many calls to sumRegion function.
    You may assume that row1 ≤ row2 and col1 ≤ col2.
*/

// Your NumMatrix object will be instantiated and called as such:
// NumMatrix numMatrix(matrix);
// numMatrix.sumRegion(0, 1, 2, 3);
// numMatrix.sumRegion(1, 2, 3, 4);

// DP solution similar to the 1D problem (303).

class NumMatrix {
public:
    NumMatrix(vector<vector<int>> &matrix) {
        if(matrix.empty() || matrix[0].empty()) {
            m = n = 0;
            return;
        }
        m = matrix.size(); n = matrix[0].size();
        sum.resize(m+1, vector<int>(n+1, 0));
        for(int i = 1; i <= m; ++i)
            for(int j = 1; j <= n; ++j)
                sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + matrix[i-1][j-1];
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        if(row1 < 0 || row1 >= m || col1 < 0 || col1 >= n) return 0;
        if(row2 < 0 || row2 >= m || col2 < 0 || col2 >= n) return 0;
        return sum[row2+1][col2+1] - sum[row1][col2+1] - sum[row2+1][col1] + sum[row1][col1];
    }
    vector<vector<int> > sum;
    int m, n;
};


/**************************************************** 
 ***    303,Easy,Range Sum Query - Immutable 
 ****************************************************/

/*
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

Example:

Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3

Note:

    You may assume that the array does not change.
    There are many calls to sumRange function.
*/

// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.sumRange(1, 2);

// Since array is immutable, use standard DP. Use an array storing the partial sums. Array has an additional entry in the front storing "0".

class NumArray {
public:
    NumArray(vector<int> &nums) {
        n = nums.size();
        sum.resize(n+1, 0);
        for(int i = 0; i < n; ++i)
            sum[i+1] = sum[i] + nums[i];
    }

    int sumRange(int i, int j) {
        if(i < 0 || i >= n || j < 0 || j > n || i > j) return 0;
        return sum[j+1] - sum[i];
    }
    vector<int> sum; //partial sums
    int n;
};

// Another solution also storing the nums array itself, and optimized for i == j case.

class NumArray {
public:
    NumArray(vector<int> &nums) {
        n = nums.size();
        sum.resize(n+1, 0);
        val.resize(n+1, 0);
        for(int i = 0; i < n; ++i) {
            sum[i+1] = sum[i] + nums[i];
            val[i+1] = nums[i];
        }
    }

    int sumRange(int i, int j) {
        if(i < 0 || i >= n || j < 0 || j > n || i > j) return 0;
        if(i == j) return val[i+1];
        else return sum[j+1] - sum[i];
    }
    vector<int> sum; //partial sums
    vector<int> val; //values
    int n;
};


/**************************************************** 
 ***    302,Hard,Smallest Rectangle Enclosing Black Pixels 
 ****************************************************/

/*
An image is represented by a binary matrix with 0 as a white pixel and 1 as a black pixel. The black pixels are connected, i.e., there is only one black region. Pixels are connected horizontally and vertically. Given the location (x, y) of one of the black pixels, return the area of the smallest (axis-aligned) rectangle that encloses all black pixels.

For example, given the following image:

[
  "0010",
  "0110",
  "0100"
]

and x = 0, y = 2,

Return 6. 
*/

// Standard BFS solution.
class Solution {
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        if(image.empty() || image[0].empty()) return 0;
        xmin = x, xmax = x, ymin = y, ymax = y;
        pixels.push_back(make_pair(x, y));
        image[x][y] = '.'; //sign for visited
        int m = image.size(), n = image[0].size();
        while(!pixels.empty()) {
            x = pixels.front().first;
            y = pixels.front().second;
            pixels.pop_front();
            if(x > 0 && image[x-1][y] == '1') {
                pixels.push_back(make_pair(x-1, y));
                image[x-1][y] = '.';
                xmin = min(xmin, x-1);
            }
            if(x < m-1 && image[x+1][y] == '1') {
                pixels.push_back(make_pair(x+1, y));
                image[x+1][y] = '.';
                xmax = max(xmax, x+1);
            }
            if(y > 0 && image[x][y-1] == '1') {
                pixels.push_back(make_pair(x, y-1));
                image[x][y-1] = '.';
                ymin = min(ymin, y-1);
            }
            if(y < n-1 && image[x][y+1] == '1') {
                pixels.push_back(make_pair(x, y+1));
                image[x][y+1] = '.';
                ymax = max(ymax, y+1);
            }
        }
      /*  for(int i = xmin; i <= xmax; ++i) {
            for(int j = ymin; j <= ymax; ++j) {
                if(image[i][j] == '.') image[i][j] = '1';
            }
        } */
        return (xmax-xmin+1)*(ymax-ymin+1);
    }

    int xmin, xmax, ymin, ymax;
    deque<pair<int, int> > pixels;
};

/*
Binary search solution. There is only one connected region, and we are given a position inside it. If we project the region to 1D (x, or y), we end up with: 00000111110000, where we have a one when there is at least one '1' in the same colum or row.
The starting position is guaranteed to be one of the '1's. So we do two binary searches, once left and once right, to find the boundary between 0 and 1's. We carry out the same algorithm for both row and column, and we get the maximum area.

Use a function to perform the same task for row and colume, and a helper function foundOne.
*/

class Solution {
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        if(image.empty() || image[0].empty()) return 0;
        int xmin(0), xmax(0), ymin(0), ymax(0);
        //'r' means row, 'c' means col
        getBoundaries(image, y, xmin, xmax, 'r');
        getBoundaries(image, x, ymin, ymax, 'c');
        return (xmax-xmin+1)*(ymax-ymin+1);
    }

    void getBoundaries(vector<vector<char> >& image, int pos, int& lb, int& hb, char rc) {
        //binary search, first left then right
        int lo(0), hi(0), mid(0);

        lo = 0, hi = pos-1;
        // [0 .. lo): 0, [lo .. hi] TBD, (hi, pos) 1
        while(lo <= hi) {
            mid = lo + (hi-lo)/2;
            if(foundOne(image, mid, rc)) hi = mid-1;
            else lo = mid+1;
        }
        lb = lo;

        lo = pos+1, hi = (rc == 'r') ? image[0].size()-1 : image.size()-1;
        // [0 .. lo): 1, [lo .. hi] TBD, (hi, pos) 0
        while(lo <= hi) {
            mid = lo + (hi-lo)/2;
            if(foundOne(image, mid, rc)) lo = mid+1;
            else hi = mid-1;
        }
        hb = hi;
    }
    bool foundOne(vector<vector<char> >& image, int pos, char rc) {
        int m = image.size(), n = image[0].size();
        if(rc == 'r') { //we need to search along column
            for(int k = 0; k < m; ++k)
               if(image[k][pos] == '1') return true;
            return false;
         } else { //we need to search along row
            for(int k = 0; k < n; ++k)
               if(image[pos][k] == '1') return true;
            return false;
         }
    }
};

*/


/**************************************************** 
 ***    296,Hard,Best Meeting Point 
 ****************************************************/

/*
A group of two or more people wants to meet and minimize the total travel distance. You are given a 2D grid of values 0 or 1, where each 1 marks the home of someone in the group. The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

For example, given three people living at (0,0), (0,4), and (2,2):

1 - 0 - 0 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0

The point (0,2) is an ideal meeting point, as the total travel distance of 2+2+2=6 is minimal. So return 6.
*/

// Reduce the problem to 2 1D problems. For 1D problem, sort the coordinates, then place the meeting points in the middle, the min distance is thus the sum of pos[n-1] - pos[0], pos[n-2] - pos[1] ... and pos[i+1] - pos[i], pos[i+2]-pos[i] depending on polarity of n.
// Caveats: need to sort the coordinates for row first!

class Solution {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        vector<int> row, col;
        int m = grid.size(), n = grid[0].size();
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(grid[i][j] == 1) { col.push_back(i); row.push_back(j); }
            }
        }
        sort(row.begin(), row.end());
        int distance = 0;
        int n1 = row.size();
        for(int k = 0; k < n1/2; ++k) {
            distance += (row[n1-k-1] - row[k]) + (col[n1-k-1] - col[k]);
        }
        
        return distance;
    }
};


/**************************************************** 
 ***    295,Hard,Find Median from Data Stream 
 ****************************************************/

/*
Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.
Examples:

[2,3,4] , the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

    void addNum(int num) - Add a integer number from the data stream to the data structure.
    double findMedian() - Return the median of all elements so far.

For example:

add(1)
add(2)
findMedian() -> 1.5
add(3) 
findMedian() -> 2

*/

// Solution: use two priority queues, one max-queue and the other min-queue. Store first half of data in max-queue and second half of data in min-queue. Has to take care of corner cases (count == 0)

class MedianFinder {
public:
    MedianFinder() : count(0) {}

    // Adds a number into the data structure.
    void addNum(int num) {
        if(count == 0) maxHeap.push(num);
        else if(count % 2 == 0) { //even number of elements
            if(num <= maxHeap.top()) maxHeap.push(num);
            else {
                minHeap.push(num);
                maxHeap.push(minHeap.top()); //put smallest in minHeap to maxHeap
                minHeap.pop();
            }
        } else { //odd number of elements, maxHeap has the extra one
            if(num >= maxHeap.top()) minHeap.push(num);
            else {
                maxHeap.push(num);
                minHeap.push(maxHeap.top());
                maxHeap.pop();
            }
        }
        count++;
    }

    // Returns the median of current data stream
    double findMedian() {
        if(count == 0) return 0;
        else if(count % 2 == 1) return maxHeap.top();
        else return (maxHeap.top() + minHeap.top())/2.0;
    }

private:    
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int> > minHeap;
    int count;
};

// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();

/**************************************************** 
 ***    292,Easy,Nim Game 
 ****************************************************/

/*
You are playing the following Nim Game with your friend: There is a heap of stones on the table, each time one of you take turns to remove 1 to 3 stones. The one who removes the last stone will be the winner. You will take the first turn to remove the stones.

Both of you are very clever and have optimal strategies for the game. Write a function to determine whether you can win the game given the number of stones in the heap.

For example, if there are 4 stones in the heap, then you will never win the game: no matter 1, 2, or 3 stones you remove, the last stone will always be removed by your friend.

Hint:

    If there are 5 stones in the heap, could you figure out a way to remove the stones such that you will always be the winner?

*/

// Easy.
class Solution {
public:
    bool canWinNim(int n) {
        return n % 4;
    }
};

/**************************************************** 
 ***    291,Hard,Word Pattern II 
 ****************************************************/

/*
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty substring in str.

Examples:

    pattern = "abab", str = "redblueredblue" should return true.
    pattern = "aaaa", str = "asdasdasdasd" should return true.
    pattern = "aabb", str = "xyzabcxzyabc" should return false.

Notes:
You may assume both pattern and str contains only lowercase letters. 
*/

// Backtracking solution using recursive calls.
// Each time grab a character in pattern, and try to match all possibilities in str. Use two maps to store the current mapping relations between the character and str. We need both forward (pat2txt) and backward mapping (txt2pat). 
// The function dfs starts matching pattern[i, end) with str[j, end). If i or j reaches end, we terminate properly.
// Then we take a character from pattern[i], and try to match any strings starting at j in str. There are several cases:
// 1. If pattern[i] is already found in the pat2txt map, then we have to match the same entry for str[j, end). We extract the same size from str (possibly out of str' range, which we need to properly take care of), and compare with the entry pat2txt. If matches we continue to next step by matching pattern[i+1, end) with str[j+len, end). Otherwise, we simply return false.
// 2. If pattern[i] is not found in pat2txt map, then we try all possibilities from str[j, end), i.e. str[j, j+1), str[j, j+2) ...
// For each trials, we need to check if they are already assigned to a mapping formula in txt2pat. If yes, we need to skip it (to ensure bijection relation). Otherwise, we make this the current mapping trial, and insert it to the two maps, and move to next step. After we are done, we erase the entries in the two maps to retrace.
// During the search, whenever we find a valid match, we return true immediately.
// Caveats:
//  if(j+len > n || str.substr(j, len) != sub), the first condition is necessary to avoid going out of bounds!

class Solution {
public:
    bool wordPatternMatch(string pattern, string str) {
        if(pattern.empty()) return str.empty();
        if(str.empty()) return pattern.empty();
        return dfs(pattern, 0, str, 0);
    }

    bool dfs(const string& pattern, int i, const string& str, int j) {
        int m = pattern.size(), n = str.size();
        if(i == m || j == n) return i == m && j == n;
        //read one pattern character
        char c = pattern[i];
        if(!pat2txt.count(c)) { //new character
            //try all possibilities from str[j, end) if that is not already in txt2pat
            for(int len = 1; len <= n-j; ++len) {
                string sub = str.substr(j, len);
                if(txt2pat.count(sub)) continue;
                pat2txt[c] = sub; //insert
                txt2pat[sub] = c; //insert
                if(dfs(pattern, i+1, str, j+len)) return true;
                pat2txt.erase(c); //retrace
                txt2pat.erase(sub); //retrace
            }
        } else { //already found mapping
            string sub = pat2txt[c];
            int len = sub.size();
            if(j+len > n || str.substr(j, len) != sub) return false; //not found match
            if(dfs(pattern, i+1, str, j+len)) return true; //found match, move to next step
        }
        return false; //finished matching
    }

    unordered_map<char, string> pat2txt;
    unordered_map<string, char> txt2pat;
};


/**************************************************** 
 ***    287,Hard,Find the Duplicate Number 
 ****************************************************/

/*
Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.

Note:

    You must not modify the array (assume the array is read only).
    You must use only constant, O(1) extra space.
    Your runtime complexity should be less than O(n2).
    There is only one duplicate number in the array, but it could be repeated more than once.
*/

/*
Recursive solution.  O(nlgn) time.
Use a helper function to find duplicates in nums array in interval [lo, hi], given that the num array has more than hi-lo+1 elements lying in [lo, hi] (pigeon hole principle).
For given lo and hi, we let mid = (lo+hi)/2. We count the # elements <= mid (denoted as smaller), and # elements > mid (denoted as larger). Two cases:
1. [lo, hi] contains even number of integers. If no duplicates, we should find # integers <= mid equal to # integers > mid.
e.g. [2, 7], mid = 4, thus smaller = #[2,3,4] = 3, larger = #[5,6,7] = 3.
If duplicate <= mid, thus we have smaller > larger, otherwise smaller < larger
2. [lo, hi] contains odd number of integers. If no duplicates, we should find # integers <= mid one more than # integers > mid.
e.g. [2, 8], mid = 5, thus smaller = #[2,3,4,5] = 4, larger = #[6,7,8] = 3.
If duplicate <= mid, thus we have smaller > larger, otherwise smaller <= larger
Thus we have come up with the recursive formula:
 - smaller > larger => check again for interval [lo, mid]
 - smaller < larger => check again for interval [mid+1, hi].
Repeat until lo == hi, where we know that duplicate is of course lo (the only possible choice between [lo, hi]).
*/

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        if(nums.empty()) return -1;
        int n = nums.size();
        return findDuplicateHelper(nums, 1, n-1);
    }
    int findDuplicateHelper(vector<int>& nums, int lo, int hi) {
        if(lo > hi) return -1;
        if(lo == hi) return lo;
        int n = nums.size();
        int mid = lo + (hi-lo)/2;
        int small = 0, large = 0;
        for(int i = 0; i < n; ++i) {
            if(nums[i] < lo || nums[i] > hi) continue; //ignore elements out of range [lo, hi]
            if(nums[i] <= mid) small++;
            else large++;
        }
        if(small > large) return findDuplicateHelper(nums, lo, mid);
        else return findDuplicateHelper(nums, mid+1, hi);
    }
};

// Solution 2. Same ideas as 1. Iterative solution.  O(nlgn) time.

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        if(nums.empty()) return -1;
        int n = nums.size();
        int lo = 1, hi = n-1;
        while(lo < hi) {
            int mid = lo + (hi-lo)/2;
            int small = 0, large = 0;
            for(auto it : nums) {
                if(it < lo || it > hi) continue; //ignore elements out of range [lo, hi]
                if(it <= mid) small++;
                else large++;                
            }
            if(small > large) hi = mid;
            else lo = mid+1;
        }
        return lo;
    }
};

/*
Solution 3. Another binary search solution. O(nlgn) time.
For each number i in [1 .. n-1], count number of elements smaller or equal than i, denoted as p[i]. What will we get?
If no duplicate, e.g. [1,2,3,4]. then p[i] = i, for i = 1,.. 4. But if there is a duplicate, e.g. [1,2,2,3,4], we have 
p[1] = 1, p[2] = 3, p[3] = 4, p[4] = 5. p[i] becomes larger than i starting from the duplicated number. Since we only have one unique duplicated number, this observation always holds. Thus we can use binary search to determine i. 
Initially lo = 1, hi = n-1, and mid = (lo+hi)/2. Scan whole array and count number of elements <= mid. if count > mid, then we know that duplicate lies in [lo, mid], so we make hi = mid. Otherwise, we know that we haven't encountered the duplicate yet, and duplicate lies in [mid+1, hi], so we make lo = mid+1. Break when lo == hi, and we return lo.
*/

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        if(nums.empty()) return -1;
        int n = nums.size();
        int lo = 1, hi = n-1;
        while(lo < hi) {
            int mid = lo + (hi-lo)/2;
            int count = 0;
            for(int i = 0; i < n; ++i) {
                if(nums[i] <= mid) count++;
            }
            if(count > mid) hi = mid;
            else lo = mid+1;
        }
        return lo;
    }
};

// Solution 4. Smart solution using cycle detection algorithm in linked-lists
// See http://keithschwarz.com/interesting/code/?dir=find-duplicate

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        int fast = n-1, slow = n-1;
        do {
            fast = nums[fast]-1;
            fast = nums[fast]-1;
            slow = nums[slow]-1;
        } while(fast != slow);
        slow = n-1;
        while(fast != slow) {
            fast = nums[fast]-1;
            slow = nums[slow]-1;
        }
        return slow+1;
    }
};



/**************************************************** 
 ***    285,Medium,Inorder Successor in BST 
 ****************************************************/

/*
Given a binary search tree and a node in it, find the in-order successor of that node in the BST.

Note: If the given node has no in-order successor in the tree, return null. 
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/*
Several cases:
1. If p has right subtree, then just return the minimum in right subtree.
2. Otherwise, need to go to its ancestors. First build a search path from root to p, then search backwards, if found a path going toward left, then the higher one is the successor.
3. If not found such path, that means p is lying at bottom right of tree, and there is no successor. Return NULL.
Caveats:
tree is BST! So don't use backtracking to seach for path, use O(logn) iterative approach utilizing BST properly!

*/

class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if(!root || !p) return NULL;
        if(p->right) return findMin(p->right);
        //need to find path from root to p
        vector<TreeNode*> path;
        bool found = findPath(root, p, path);
        if(!found) return NULL;
        int n = path.size(), i = 0;
        for(i = n-1; i > 0; i--) {
            //is left subtree
            if(path[i-1]->left == path[i]) return path[i-1];
        }
        return NULL;
    }
    bool findPath(TreeNode* root, TreeNode* p, vector<TreeNode*>& path) {
        while(root) {
            path.push_back(root);
            if(root == p) return true;
            else if(p->val < root->val) root = root->left;
            else root = root->right;
        }
        return false;
    }
    TreeNode* findMin(TreeNode* root) {
        while(root->left) root = root->left;
        return root;
    }
};

//Alternative solution using a stack
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if(!root || !p) return NULL;
        if(p->right) return findMin(p->right);
        //need to find path from root to p
        stack<TreeNode*> path;
        bool found = findPath(root, p, path);
        if(!found) return NULL;
        while(!path.empty()) {
            TreeNode *ancestor = path.top(); 
            path.pop(); 
            //is left subtree
            if(!path.empty() && path.top()->left == ancestor) return path.top();
        }
        return NULL;
    }
    bool findPath(TreeNode* root, TreeNode* p, stack<TreeNode*>& path) {
        while(root) {
            path.push(root);
            if(root == p) return true;
            else if(p->val < root->val) root = root->left;
            else root = root->right;
        }
        return false;
    }
    TreeNode* findMin(TreeNode* root) {
        while(root->left) root = root->left;
        return root;
    }
};



/**************************************************** 
 ***    284,Medium,Peeking Iterator 
 ****************************************************/

/*
Given an Iterator class interface with methods: next() and hasNext(), design and implement a PeekingIterator that support the peek() operation -- it essentially peek() at the element that will be returned by the next call to next().

Here is an example. Assume that the iterator is initialized to the beginning of the list: [1, 2, 3].

Call next() gets you 1, the first element in the list.

Now you call peek() and it returns 2, the next element. Calling next() after that still return 2.

You call next() the final time and it returns 3, the last element. Calling hasNext() after that should return false.

Hint:

    Think of "looking ahead". You want to cache the next element.
    Is one variable sufficient? Why or why not?
    Test your design with call order of peek() before next() vs next() before peek().
    For a clean implementation, check out Google's guava library source code. 

Follow up: How would you extend your design to be generic and work with all types, not just integer?
*/

// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
    struct Data;
	Data* data;
public:
	Iterator(const vector<int>& nums);
	Iterator(const Iterator& iter);
	virtual ~Iterator();
	// Returns the next element in the iteration.
	int next();
	// Returns true if the iteration has more elements.
	bool hasNext() const;
};

// Store a cache in peekingIterator. Remember to set and unset the boolean tag.

class PeekingIterator : public Iterator {
public:
        PeekingIterator(const vector<int>& nums) : Iterator(nums) {
            // Initialize any member here.
            // **DO NOT** save a copy of nums and manipulate it directly.
            // You should only use the Iterator interface methods.
            hasPeek = false; 
            peekVal = -1;
        }

    // Returns the next element in the iteration without advancing the iterator.
        int peek() {
            if(!hasPeek) {
                peekVal = Iterator::next();
                hasPeek = true;
            }
            return peekVal;
        }

        // hasNext() and next() should behave the same as in the Iterator interface.
        // Override them if needed.
        int next() {
            if(hasPeek) {
                hasPeek = false;
                return peekVal;
            } else return Iterator::next();
        }

        bool hasNext() const {
            return hasPeek || Iterator::hasNext();
        }
private:
    bool hasPeek;
    int peekVal;
};


/**************************************************** 
 ***    283,Easy,Move Zeroes 
 ****************************************************/

/*
Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].

Note:

    You must do this in-place without making a copy of the array.
    Minimize the total number of operations.
*/

// Solution 1. One loop. Avoid redundant assignments.

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        if(nums.empty()) return;
        int i(0), j(0), n = nums.size();
        for(int i = 0; i < n; ++i) {
            if(nums[i] != 0) {
                if(i != j) {
                    nums[j] = nums[i];
                    nums[i] = 0;
                }
                j++;
            }
        }
    }
};

// Solution 2. Two loops
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        if(nums.empty()) return;
        int i = 0;
        for(int j = i; j < n; ++j) {
           if(nums[j]) nums[i++] = nums[j];
        }
        while(i < n) {
           nums[i++] = 0;
        }
    }
};


/**************************************************** 
 ***    282,Hard,Expression Add Operators 
 ****************************************************/

/*
Given a string that contains only digits 0-9 and a target value, return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.

Examples:

"123", 6 -> ["1+2+3", "1*2*3"] 
"232", 8 -> ["2*3+2", "2+3*2"]
"105", 5 -> ["1*0+5","10-5"]
"00", 0 -> ["0+0", "0-0", "0*0"]
"3456237490", 9191 -> []
*/

/*
Standard DFS solution, several caveats:

1. avoid multiple digits starting from 0, e.g. 03
2. consider precedence of * than + or -.
2+3 ? 4
 will depend on what ? is:
if ? is +/-, then => 5 ? 4
if ? is *, then => 2 + 12

So, at each start of string, we store the previous two numbers and operator. Say 12333, we decided 1 + 2 and is exploring 333.
Then we scan the rest of numbers, and extract one number out (e.g.  we try +/-/* of 3, 33, 333 etc)
when the next operator to try is +/-, then we can safely calculate the previous result, in this case: 3 +/-  3, 33, 333
when the next operator is *, then we need to evaluate * first, in this case we have
1 + 6,  1 + 66, 1 + 666 ...

so we write our dfs in the following format
dfs(num, long i, long a, long b, char op, string partial, vector<string>& result)

Also need to consider how to start, we use "0+0" as starting point. if i == 0, we only try + with the rest of string.
*/

class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> result;
        string partial; //partial solution
        dfs(num, 0, 0, 0, '+', target, partial, result);
        return result;
    }
    long eval(long a, long b, char op) {
        if(op == '+') return a+b;
        else if(op == '-') return a-b;
        else if(op == '*') return a*b;
        else return 0;
    }
    // a op b ?? num[i, n)
    void dfs(const string& num, int i, long a, long b, char op, long target, string& partial, vector<string>& result) {
        int n = num.size();
        if(i == n && eval(a, b, op) == target) {
            result.push_back(partial); return;
        } 
        long number = 0;
        int size = partial.size();
        if(i != 0) partial += '+'; //append an operator
        int jmax = (num[i] == '0') ? i+1 : n;
        for(int j = i; j < jmax; ++j) {
            number = number*10 + (num[j] - '0'); //number from num[i, j]
            partial += num[j];
            if(i == 0) {
                dfs(num, j+1, 0, number, '+', target, partial, result); //starting point, only try '+'
            } else {  
                 long tmpval = eval(a, b, op);
                 partial[size] = '+';
                 dfs(num, j+1, tmpval, number, '+', target, partial, result);
                 partial[size] = '-';
                 dfs(num, j+1, tmpval, number, '-', target, partial, result);
                 partial[size] = '*';
                 dfs(num, j+1, a, b*number, op, target, partial, result); //op can only be '+' or '-', has lower precedence than *
            }
        }
        partial.resize(size); //reset tmp value
    }
};

/*
We further notice that op can never be '*'.Another solution as in the forum uses this fact, and changes sign of b when '-' is chosen. However, this results in slower code for some reason.
*/

class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> result;
        string partial; //partial solution
        dfs(num, 0, 0, 0, target, partial, result);
        return result;
    }

    // a op b ?? num[i, n)
    void dfs(const string& num, int i, long a, long b, long target, string& partial, vector<string>& result) {
        int n = num.size();
        if(i == n && a+b == target) {
            result.push_back(partial); return;
        } 
        long number = 0;
        int size = partial.size();
        if(i != 0) partial += '+'; //append an operator
        int jmax = (num[i] == '0') ? i+1 : n;
        for(int j = i; j < jmax; ++j) {
            number = number*10 + (num[j] - '0'); //number from num[i, j]
            partial += num[j];
            if(i == 0) {
                dfs(num, j+1, 0, number, target, partial, result);
            } else {  
                 partial[size] = '+';
                 dfs(num, j+1, a+b, number, target, partial, result);
                 partial[size] = '-';
                 dfs(num, j+1, a+b, -number, target, partial, result);
                 partial[size] = '*';
                 dfs(num, j+1, a, b*number, target, partial, result); //op can only be '+' or '-', has lower precedence than *
            }
        }
        partial.resize(size); //reset tmp value
    }
};


/**************************************************** 
 ***    281,Medium,Zigzag Iterator 
 ****************************************************/

/*
Given two 1d vectors, implement an iterator to return their elements alternately.

For example, given two 1d vectors:

v1 = [1, 2]
v2 = [3, 4, 5, 6]

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1, 3, 2, 4, 5, 6].

Follow up: What if you are given k 1d vectors? How well can your code be extended to such cases?

Clarification for the follow up question - Update (2015-09-18):
The "Zigzag" order is not clearly defined and is ambiguous for k > 2 cases. If "Zigzag" does not look right to you, replace "Zigzag" with "Cyclic". For example, given the following input:

[1,2,3]
[4,5,6,7]
[8,9]

It should return [1,4,8,2,5,9,3,6,7]. 
*/

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */

// pointer always points to the the next valid value. After robtaining the next value, move pointer to next valid value.

class ZigzagIterator {
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        nums.push_back(v1); 
        nums.push_back(v2);
        n = 2;
        indices.resize(n, 0);        
        arrayIdx = 0;
        while(arrayIdx < n && nums[arrayIdx].empty()) arrayIdx++;
    }

    int next() {
        if(arrayIdx == n) return -1;

        int idx = indices[arrayIdx];
        int val = nums[arrayIdx][idx];

        indices[arrayIdx]++;
        int i = (arrayIdx+1) % n;
        while(i != arrayIdx && indices[i] == nums[i].size()) i = (i+1) % n;
        if(i == arrayIdx && indices[i] == nums[i].size()) arrayIdx = n;
        else arrayIdx = i;

        return val;
    }

    bool hasNext() {
        return arrayIdx < n;
    }
private:
    vector<vector<int> > nums;
    vector<int> indices; //current position in each array
    int arrayIdx; //current array index
    int n; //number of arrays
};


/**************************************************** 
 ***    280,Medium,Wiggle Sort 
 ****************************************************/

/*
Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

For example, given nums = [3, 5, 2, 1, 6, 4], one possible answer is [1, 6, 2, 5, 3, 4]. 
*/

// Linear solution:
/* Scan left to right, two passes
 First pass arranges i and i+1 for even i such that nums[i] >= nums[i+1].
 Second pass arranges i and i+1 for odd i such that nums[i] <= nums[i+1].
 In second pass, we could have (i is odd), then we simply swap i and i+1.
               *                   *
           *                 * \  /
        *           =>      /   *
   *                       *
   (i-1 i) (i+1 
*/

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return;
        for(int i = 0; i+1 < n; i+=2) {
            if(nums[i] > nums[i+1]) swap(nums, i, i+1);
        }
        for(int i = 1; i+1 < n; i+=2) {
            if(nums[i] < nums[i+1]) swap(nums, i, i+1);
        }
    }
    void swap(vector<int>& nums, int i, int j) {
        int t = nums[i];
        nums[i] = nums[j];
        nums[j] = t;
    }
};

// One pass linear solution. We can combine the two passes into one pass.
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return;
        for(int i = 0; i+1 < n; i++) {
            if(!(i & 1) && nums[i] > nums[i+1]) swap(nums, i, i+1);
            if((i & 1) && nums[i] < nums[i+1]) swap(nums, i, i+1);
        }
    }
    void swap(vector<int>& nums, int i, int j) {
        int t = nums[i];
        nums[i] = nums[j];
        nums[j] = t;
    }
};

// Another O(nlgn) solution using sort. First sort, then swap ajacent pairs.
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return;
        sort(nums.begin(), nums.end());
        for(int i = 1; i+1 < n; i+=2) {
            int tmp = nums[i];
            nums[i] = nums[i+1];
            nums[i+1] = tmp;
        }
    }
};

/**************************************************** 
 ***    278,Easy,First Bad Version 
 ****************************************************/

/*
You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.

Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.

You are given an API bool isBadVersion(version) which will return whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API. 
*/

// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

/// Binary search

class Solution {
public:
    int firstBadVersion(int n) {
        if(n == 0) return -1;
        int lo = 1, hi = n;
        //(1 .. lo) good, [lo, hi] TBD, (hi, n) bad
        while(lo <= hi) {
            int mid = lo + (hi - lo)/2;
            if(isBadVersion(mid)) hi = mid - 1;
            else lo = mid + 1;
        }
        return lo;
    }
};

/**************************************************** 
 ***    276,Easy,Paint Fence 
 ****************************************************/

/*
There is a fence with n posts, each post can be painted with one of the k colors.

You have to paint all the posts such that no more than two adjacent fence posts have the same color.

Return the total number of ways you can paint the fence.

Note:
n and k are non-negative integers. 
*/

//Solution: dynamic programming, keep counts for two cases: last two colors are same, and different.

class Solution {
public:
    int numWays(int n, int k) {
        if(n == 0 || k == 0) return 0;
        if(n == 1) return k;
        if(n == 2) return k*k;
        int last_two_same = k, last_two_diff = k*(k-1);
        for(int i = 3; i <= n; ++i) {
            int tmp = last_two_diff;
            last_two_diff = (last_two_same+last_two_diff)*(k-1);
            last_two_same = tmp;
        }
        return last_two_same + last_two_diff;
    }
};

/**************************************************** 
 ***    272,Hard,Closest Binary Search Tree Value II 
 ****************************************************/

/*
Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.

Note:

    Given target value is a floating point.
    You may assume k is always valid, that is: k ≤ total nodes.
    You are guaranteed to have only one unique set of k values in the BST that are closest to the target.

Follow up:
Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?

Hint:

    Consider implement these two helper functions:
        getPredecessor(N), which returns the next smaller node to N.
        getSuccessor(N), which returns the next larger node to N.
    Try to assume that each node has a parent pointer, it makes the problem much easier.
    Without parent pointer we just need to keep track of the path from the root to the current node using a stack.
    You would need two stacks to track the path in finding predecessor and successor node separately.
*/

// First build the stack storing search path for predecessor and successor of target. For predecessor, only insert into stack nodes smaller than target during search, and likewise for successor. nodes equal to the target will be inserted to predecessor (to break tie and avoid duplicated results returned). Then implement the nextSucc and nextPred function to return the next larger/smaller value to target, by poppping/pushing elements from/to stack. Do a merging routine similar to the merge sort to establish the order of k values.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        vector<int> result(k, 0);
        if(!root) return result;
        //build stack for predecessor path
        TreeNode *node = root;
        while(node) {
            if(target < node->val) node = node->left;
            else {
                pred.push(node);
                node = node->right;
            } 
        }
        //build stack for successor path
        node = root;
        while(node) {
            if(target >= node->val) node = node->right;
            else {
                succ.push(node);
                node = node->left;
            }
        }

        TreeNode *p = nextPred(), *s = nextSucc();
        for(int i = 0; i < k; ++i) {
           if(!p) { result[i] =  s->val; s = nextSucc(); } 
           else if(!s) { result[i] =  p->val; p = nextPred(); }
           else if(target - p->val > s->val - target) { result[i] =  s->val; s = nextSucc(); } 
           else { result[i] =  p->val; p = nextPred(); }
        }
        return result;
    }

    TreeNode* nextPred() {
        if(pred.empty()) return NULL;
        TreeNode* node = pred.top(); pred.pop();
        TreeNode *tmp = node->left;
        while(tmp) {
            pred.push(tmp); 
            tmp = tmp->right;
        }
        return node;
    }

    TreeNode* nextSucc() {
        if(succ.empty()) return NULL;
        TreeNode* node = succ.top(); succ.pop();
        TreeNode *tmp = node->right;
        while(tmp) {
            succ.push(tmp); 
            tmp = tmp->left;
        }
        return node;
    }

    stack<TreeNode*> pred, succ; //stack for predecessor and successor paths
};


/**************************************************** 
 ***    269,Hard,Alien Dictionary 
 ****************************************************/

/*
There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you. You receive a list of words from the dictionary, where words are sorted lexicographically by the rules of this new language. Derive the order of letters in this language.

For example,
Given the following words in dictionary,

[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]

The correct order is: "wertf".

Note:

    You may assume all letters are in lowercase.
    If the order is invalid, return an empty string.
    There may be multiple valid order of letters, return any one of them is fine.
*/

// Build a graph containing vertices corresponding letters 'a' to 'z'. Scan the dictionary twice. First time add vertices for seen characters. Second time compare two adjacent strings and add an edge for the pair of characters. 
// Then do a topological sort, and return the result as string. During the topo-sort, also detect whether there is a cycle. If detected, immediately return to calling function which in turn returns "" to main function.
// Use the 3-color scheme in CLRS (white, grey, black) to do topo-sort and cycle detection in one pass.

class Graph {
public:
    Graph()  {
        vertices.resize(26, false);
        adj.resize(26);
        color.resize(26, 0); //0: unvisited, 1: on stack, 2: finished
	hasCycle = false;
    }
    void addVertex(char c) {
        vertices[c-'a'] = true; 
    }
    void addEdge(char c1, char c2) {
        adj[c1-'a'].push_back(c2-'a');
    }

    string topoSort() {
        string s;
        for(int v = 0; v < 26; ++v) {
            if(vertices[v] && color[v] == 0) {
                dfs(v, s);
                if(hasCycle) return "";
            }
        }
        reverse(s.begin(), s.end());
        return s;
    }

    void dfs(int v, string& s) {
        if(hasCycle) return;
        color[v] = 1;
        for(auto w : adj[v]) {
            if(color[w] == 0) dfs(w, s);
            else if(color[w] == 1) { hasCycle = true; return; }
        }
        color[v] = 2;
        //after we are done with v, push back to s.
        s.push_back(v+'a');
    }

private:
    vector<bool> vertices; //vertices (26)
    vector<vector<int> > adj; //adjacency lists 
    vector<int> color; // whether vertices are on stack
    bool hasCycle;
};

class Solution {
public:
    string alienOrder(vector<string>& words) {
        if(words.empty()) return "";
        int n = words.size();
        Graph g;
        for(int i = 0; i < n; ++i)
            for(char c : words[i])
                 g.addVertex(c);

        for(int i = 1; i < n; ++i) {
           int jmax = min(words[i].size(), words[i-1].size());
           for(int j = 0; j < jmax; ++j) {
               if(words[i-1][j] != words[i][j]) { g.addEdge(words[i-1][j], words[i][j]); break;}
           }
        }
        return g.topoSort();
    }
};


/**************************************************** 
 ***    267,Medium,Palindrome Permutation II 
 ****************************************************/

/*
Given a string s, return all the palindromic permutations (without duplicates) of it. Return an empty list if no palindromic permutation could be form.

For example:

Given s = "aabb", return ["abba", "baab"].

Given s = "abc", return [].

Hint:

    If a palindromic permutation exists, we just need to generate the first half of the string.
    To generate all distinct permutations of a (half of) string, use a similar approach from: Permutations II or Next Permutation.

*/

// Scan whole word, count occurrences of each character. Only one character is allowed to have odd count. Otherwise return empty set.
// construct half string as half the count of each character. No need to sort the string because we construct it from c = 0 to c = 255.
// Store the middle character as a string (either single character, or empty string). And call nextPermutation to find the next one. Need a reverse function.
// Caveats:
// Need to handle corner cases where the half string is empty! It will result in infinite loops in nextPermutation if there is no checking.
// Alternatively can check this at the beginning (by checking whether the length of s is 1).

class Solution {
public:
    vector<string> generatePalindromes(string s) {
        vector<string> result;
        if(s.empty()) return result;
        if(s.size() == 1) {
            result.push_back(s); return result;
        }
        vector<int> counts(256, 0);
        for(auto c : s) counts[c] ++;
        int nodds = 0;
        string odd = "";
        s = "";
        for(int c = 0; c < 256; ++c) {
            if(counts[c] & 1) {
                odd += c;
                if(++nodds > 1) return result; //no solution
            } 
            if (counts[c] > 0)
                s += string(counts[c]/2, c);
        }
        result.push_back(s+odd+reverse(s));
        while(nextPermutation(s)) result.push_back(s+odd+reverse(s));
        return result;
    }
    
    string reverse(const string& s) {
        string t = s;
        int i(0), j(s.size()-1);
        while(i < j) {
            swap(t[i++], t[j--]);
        }
        return t;
    }
    bool nextPermutation(string& s) {
        if(s.empty()) return false;
        int n = s.size();
        int k = n-2, l = n-1;
        while(k >= 0 && s[k] >= s[k+1]) k--;
        //k is the last k such that nums[k] < nums[k+1]
        if(k == -1) { //no next, just return false
            return false;
        }
        while(l > k && s[l] <= s[k]) l--;
        //l is the last l such that nums[l] > nums[k]
        //swap nums[k] and nums[l]
        swap(s[k], s[l]);
        //sort numbers after k
        int i = k+1, j = n-1;
        while(i < j) swap(s[i++], s[j--]);
        return true;
    }
};

/**************************************************** 
 ***    266,Easy,Palindrome Permutation 
 ****************************************************/

/*
Given a string, determine if a permutation of the string could form a palindrome.

For example,
"code" -> False, "aab" -> True, "carerac" -> True.

Hint:

    Consider the palindromes of odd vs even length. What difference do you notice?
    Count the frequency of each character.
    If each character occurs even number of times, then it must be a palindrome. How about character which occurs odd number of times?
*/

// count occurences of each word. check wheather even or odd.

class Solution {
public:
    bool canPermutePalindrome(string s) {
        int n = s.size(); 
        if(n <= 1) return true;
        vector<bool> odd(256,false);
        for(int i = 0; i < n; ++i) {
            char c = s[i];
            odd[c] = ! odd[c];
        }
        int nodds = 0;
        for(int i = 0; i < 256; ++i) {
            if(odd[i]) nodds ++;
            if(nodds > 1) return false;
        }
        return true;
    }
};

/**************************************************** 
 ***    265,Hard,Paint House II 
 ****************************************************/

/*
There are a row of n houses, each house can be painted with one of the k colors. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x k cost matrix. For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost of painting house 1 with color 2, and so on... Find the minimum cost to paint all houses.

Note:
All costs are positive integers.

Follow up:
Could you solve it in O(nk) runtime?
*/

/* Dynamic programming. Similar to 256 paint house where k=3. To make it O(nk), we need to find the minimum among k-1 colors out of k colors. To do this in O(k) time, notice that the minimum among k-1 colors has n cases, n-1 of them end up with the minimum elements of the k colors, and the other one end up with the second minimum element. So we just keep track of the minimum and second minimum element of the k colors.
*/

class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        if(costs.empty() || costs[0].empty()) return 0;
        int n = costs.size();
        int ncolor = costs[0].size();
        vector<int> cost_so_far(ncolor, 0);
        vector<int> tmp(ncolor, 0);
        int min_cost = INT_MAX, second_min_cost = INT_MAX;
        int min_cost_color = 0, second_min_cost_color = 0;
        for(int i = 0; i < n; ++i) {
            for(int k = 0; k < ncolor; ++k) {
                if(min_cost_color == k) tmp[k] = cost_so_far[second_min_cost_color] + costs[i][k];
                else tmp[k] = cost_so_far[min_cost_color] + costs[i][k];
            }
            //update min and second_min
            min_cost = INT_MAX, second_min_cost = INT_MAX;
            min_cost_color = 0, second_min_cost_color = 0;
            for(int k = 0; k < ncolor; ++k) {
                if(tmp[k] < min_cost) { 
                    second_min_cost = min_cost; second_min_cost_color = min_cost_color;
                    min_cost = tmp[k]; min_cost_color = k; 
                } else if(tmp[k] < second_min_cost) { 
                    second_min_cost = tmp[k]; second_min_cost_color = k;
                }
            }
            cost_so_far.swap(tmp);
        }
        return min_cost;        
    }
};

/**************************************************** 
 ***    264,Medium,Ugly Number II 
 ****************************************************/

/*
Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.

Note that 1 is typically treated as an ugly number.

Hint:

    The naive approach is to call isUgly for every number until you reach the nth one. Most numbers are not ugly. Try to focus your effort on generating only the ugly ones.
    An ugly number must be multiplied by either 2, 3, or 5 from a smaller ugly number.
    The key is how to maintain the order of the ugly numbers. Try a similar approach of merging from three sorted lists: L1, L2, and L3.
    Assume you have Uk, the kth ugly number. Then Uk+1 must be Min(L1 * 2, L2 * 3, L3 * 5).
*/

// Solution: http://www.geeksforgeeks.org/ugly-numbers/
// All ugly numbers are built from the following three lists:
// (1) 1x2 2x2 3x2 4x2 5x2 6x2 8x2
// (2) 1x3 2x3 3x3 4x3 5x3 6x3 8x3
// (3) 1x5 2x5 3x5 4x5 5x5 6x5 8x5
// Where (1) is built from the exact ugly number sequence multiple by 2, and similar for (2) and (3). So we could use dynamic programming to generate the next ugly number from previous ones. The key is to maintain the order.
// To solve this, we keep track of which is the last ugly number used in each list, for example, 4 in (1), 3 in (2), and 2 in (5), then the next ugly number will be the minimum of 4x2, 3x3, and 2x5. We found the minimum is 4x2 from (1), then we advance pointer in (1) to 5. We store all the previous ugly numbers in an array so that we can use three pointers to point to the approapriate entry in the array and easily find the next ugly number for each list by advancing the pointers. 
// There might be duplicates in the lists, so we need to test each list.

// A simple solution with many array addressing (a bit slower)
class Solution {
public:
    int nthUglyNumber(int n) {
        if(n == 1) return 1;
        int mult2 = 1, mult3 = 1, mult5 = 1;
        vector<int> ugly(n, 1);
        int i2 = 0, i3 = 0, i5 = 0; //index in ugly array
        for(int i = 1; i < n; ++i) {
            ugly[i] = min(min(ugly[i2]*2, ugly[i3]*3), ugly[i5]*5);
            if(ugly[i] == ugly[i2]*2) i2++;
            if(ugly[i] == ugly[i3]*3) i3++;
            if(ugly[i] == ugly[i5]*5) i5++;
        }
        return ugly[n-1];
    }
};

// A faster version avoiding array addressing by using intermediate variable mult and next
class Solution {
public:
    int nthUglyNumber(int n) {
        if(n == 1) return 1;
        int mult2 = 1, mult3 = 1, mult5 = 1;
        vector<int> ugly(n, 1);
        int i2 = 0, i3 = 0, i5 = 0; //index in ugly array
        for(int i = 1; i < n; ++i) {
            int next = min(min(mult2*2, mult3*3), mult5*5);
            ugly[i] = next;
            if(next == mult2*2) mult2 = ugly[++i2];
            if(next == mult3*3) mult3 = ugly[++i3];
            if(next == mult5*5) mult5 = ugly[++i5];
        }
        return ugly[n-1];
    }
};

/**************************************************** 
 ***    263,Easy,Ugly Number 
 ****************************************************/

/*
Write a program to check whether a given number is an ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 6, 8 are ugly while 14 is not ugly since it includes another prime factor 7.

Note that 1 is typically treated as an ugly number. 
*/

// Solution using only one while loop (faster)
class Solution {
public:
    bool isUgly(int num) {
        if(num == 0) return false;
        while(num != 1) {
            if(num % 2 == 0) num /= 2;
            else if(num % 3 == 0) num /= 3;
            else if(num % 5 == 0) num /= 5;
            else return false;
        }
        return true;
    }
};

// Solution using three while loops (slower)
class Solution {
public:
    bool isUgly(int num) {
        if(num == 0) return false;
        while(num % 2 == 0) num /= 2;
        while(num % 3 == 0) num /= 3;
        while(num % 5 == 0) num /= 5;
        return num == 1;
    }
};

/**************************************************** 
 ***    260,Medium,Single Number III 
 ****************************************************/

/*
Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.

For example:

Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].

Note:

    The order of the result is not important. So in the above example, [5, 3] is also correct.
    Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?
*/

// Solution using bit operations. Since the two numbers are different, they should differ by at least one bit position. Say the position is i, then one number should have 0, the other have 1 at this position. We use exlcusive or to find the bits that they differ. Then extract one bit out. And then group the numbers by whether the bit is set or not. We effectively break the problem into two easier problems where each group has only one single number. We calculate the single number for each group separately.

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        vector<int> result(2, 0);
        int val = 0, n = nums.size();
        for(int i = 0; i < n; ++i) {
            val ^= nums[i];
        }
        //val should be non-zero. Extract one none zero digit.
        val = val & (val ^ (val-1)); //now val has only one digit set
        for(int i = 0; i < n; ++i) {
            if(nums[i] & val) result[0] ^= nums[i];
            else result[1] ^= nums[i];
        }
        return result;
    }
};




/**************************************************** 
 ***    259,Medium,3Sum Smaller 
 ****************************************************/

/*
Given an array of n integers nums and a target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.

For example, given nums = [-2, 0, 1, 3], and target = 2.

Return 2. Because there are two triplets which sums are less than 2:

[-2, 0, 1]
[-2, 0, 3]

Follow up:
Could you solve it in O(n2) runtime? 
*/

// Two pointers, similar to 3sum.
// Optimization: break if sum is too large.

class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int count = 0;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for(int i = 0; i < n-2; i++) {
            int res = target - nums[i];
            if(nums[i+1] + nums[i+2] >= res) break;
            int j = i+1, k = n-1;
            while(j < k) {
               if(nums[j] + nums[k] < res) { count += k-j; j++; }
               else k--;
            }
        }
        return count;
    }
};

/**************************************************** 
 ***    257,Easy,Binary Tree Paths 
 ****************************************************/

/*
 Given a binary tree, return all root-to-leaf paths.

For example, given the following binary tree:

   1
 /   \
2     3
 \
  5

All root-to-leaf paths are:

["1->2->5", "1->3"]
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Standard dfs solution (recursive). The numbers can be negative.
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        string tmp;
        if(!root) return result;
        dfs(root, tmp, result);
        return result;
    }
    void dfs(TreeNode *root, string tmp, vector<string>& result) {
        tmp += num2str(root->val);
        if(!root->left && !root->right) {
            result.push_back(tmp);
            return;
        }
        if(root->left) dfs(root->left, tmp+"->", result);
        if(root->right) dfs(root->right, tmp+"->", result);
    }

    string num2str(int n) {
        if(n == 0) return "0";
        int sign = n > 0 ? 1 : -1;
        n = abs(n);
        string s;
        while(n) {
            char c = n % 10 + '0';
            s = c + s;
            n /= 10;
        }
        if(sign == -1) s = "-" + s;
        return s;
    }
};

/**************************************************** 
 ***    256,Medium,Paint House 
 ****************************************************/

/*
There are a row of n houses, each house can be painted with one of the three colors: red, blue or green. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x 3 cost matrix. For example, costs[0][0] is the cost of painting house 0 with color red; costs[1][2] is the cost of painting house 1 with color green, and so on... Find the minimum cost to paint all houses.

Note:
All costs are positive integers.
*/

// Solution: Dynamic programming
// Keep the cost for painting the first k houses with last house colored as R/G/B.
// The k+1 house can choose among R/G/B, with cost as
// cost_so_far[R]:  cost[k+1][R] + min(cost_so_far[G], cost_so_far[B])
// and similar for other two cases.

class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        if(costs.empty() || costs[0].empty()) return 0;
        int n = costs.size();
        vector<int> cost_so_far(3, 0);
        for(int i = 0; i < n; ++i) {
            int t0 = min(cost_so_far[1], cost_so_far[2]) + costs[i][0];
            int t1 = min(cost_so_far[0], cost_so_far[2]) + costs[i][1];
            int t2 = min(cost_so_far[0], cost_so_far[1]) + costs[i][2];
            cost_so_far[0] = t0;
            cost_so_far[1] = t1;
            cost_so_far[2] = t2;
        }
        return min(min(cost_so_far[0], cost_so_far[1]), cost_so_far[2]);
    }
};

/**************************************************** 
 ***    254,Medium,Factor Combinations 
 ****************************************************/

/*
Numbers can be regarded as product of its factors. For example,

8 = 2 x 2 x 2;
  = 2 x 4.

Write a function that takes an integer n and return all possible combinations of its factors.

Note:

    Each combination's factors must be sorted ascending, for example: The factors of 2 and 6 is [2, 6], not [6, 2].
    You may assume that n is always positive.
    Factors should be greater than 1 and less than n.

Examples:
input: 1
output:

[]

input: 37
output:

[]

input: 12
output:

[
  [2, 6],
  [2, 2, 3],
  [3, 4]
]

input: 32
output:

[
  [2, 16],
  [2, 2, 8],
  [2, 2, 2, 4],
  [2, 2, 2, 2, 2],
  [2, 4, 4],
  [4, 8]
]
*/

// Recursive DFS solution. Avoid adding [n] to solution (checking tmp.empty()).
// Also avoid pushing duplicated entries, e.g. [2, 2, 3], [2, 3, 2]. This is done by the j*j <= n condition in the loop.
class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int> > result;
        if(n <= 2) return result; //empty
        vector<int> tmp;
        dfs(n, 2, tmp, result); // start searching factors from 2 to sqrt(n)
        return result;
    }
    void dfs(int n, int i, vector<int>& tmp, vector<vector<int> >& result) {
        tmp.push_back(0);
        if(!tmp.empty()) { //push n itself
            tmp.back() = n;
            result.push_back(tmp);
        }
        //now check factors
        for(int j = i; j*j <= n; ++j) {
            if(n % j != 0) continue; //not a factor
            tmp.back() = j;
            dfs(n/j, j, tmp, result); //now start searching from j
        }
        tmp.pop_back();
    }
};


/**************************************************** 
 ***    253,Medium,Meeting Rooms II 
 ****************************************************/

/*
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return 2. 
*/

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

//Solution 1: sort the ending point according to its coordinate and type (start/end). If ties on coordinate, end goes before start
//Then do sweeping line and count. When see a start point, increment count, otherwise decrement count.

struct EndPoint {
    int val;
    int type; //0 for starting, 1 for ending
    EndPoint(): val(0), type(0) {}
    EndPoint(int v, int t) : val(v), type(t) {}
};

bool compare(const EndPoint& a, const EndPoint& b) {
    if(a.val == b.val) return a.type < b.type;
    else return a.val < b.val;
}


class Solution {
public:

    int minMeetingRooms(vector<Interval>& intervals) {
        int n = intervals.size();
        if(n <= 1) return n;
        vector<EndPoint> points(2*n);
        for(int i = 0; i < n; ++i) {
            points[2*i] = EndPoint(intervals[i].start, 2);
            points[2*i+1] = EndPoint(intervals[i].end, 1);
        }
        sort(points.begin(), points.end(), compare);
        int count = 0, result = 0;
        for(int i = 0; i < 2*n; ++i) {
            if(points[i].type == 2) { //is start point
               count++;
               result = max(result, count);
            } else count--;
        }
        return result;
    }
};


//A simpler solution: use a map to keep order, and count individual points, then iterate orderly through map
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        map<int, int> dict;
        int n = intervals.size();
        if(n <= 1) return n;
        for(int i = 0; i < n; ++i) {
            dict[intervals[i].start]++;
            dict[intervals[i].end]--;
        }
        int count = 0, max_count = 0;
        for(auto it : dict) { //ordered iterator
            count += it.second;
            max_count = max(count, max_count);
        }
        return max_count;
    }
};


/**************************************************** 
 ***    252,Easy,Meeting Rooms 
 ****************************************************/

/*
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), determine if a person could attend all meetings.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return false. 
*/

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

// First sort the interval according to starting times, then check whether each ajacent pair overlaps
// Criteria for not overlap:
// a.start <= b.end OR b.start <= a.end
// Then criteria for overlap is (applying boolean logic)
// a.start > b.end AND b.tart > a.end

bool compare_start(const Interval& a, const Interval& b) {
    return a.start < b.start;    
}

class Solution {
public:
    bool canAttendMeetings(vector<Interval>& intervals) {
        if(intervals.empty()) return true;
        int n = intervals.size();
        if(n == 1) return true;
        sort(intervals.begin(), intervals.end(), compare_start);
        for(int i = 1; i < n; ++i) {
            if(intervals[i].start < intervals[i-1].end && intervals[i-1].start < intervals[i].end) return false;
        }
        return true;
    }
};

/**************************************************** 
 ***    251,Medium,Flatten 2D Vector 
 ****************************************************/

/*
Implement an iterator to flatten a 2d vector.

For example,
Given 2d vector =

[
  [1,2],
  [3],
  [4,5,6]
]

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,2,3,4,5,6].

Hint:

    How many variables do you need to keep track?
    Two variables is all you need. Try with x and y.
    Beware of empty rows. It could be the first few rows.
    To write correct code, think about the invariant to maintain. What is it?
    The invariant is x and y must always point to a valid point in the 2d vector. Should you maintain your invariant ahead of time or right when you need it?
    Not sure? Think about how you would implement hasNext(). Which is more complex?
    Common logic in two different places should be refactored into a common method.

Follow up:
As an added challenge, try to code it using only iterators in C++ or iterators in Java. 
*/

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D i(vec2d);
 * while (i.hasNext()) cout << i.next();
 */

class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d) {
        nums = vec2d;
        n = nums.size();
        index = 0;
        arrayIdx = 0;
        while(arrayIdx < n && nums[arrayIdx].empty()) arrayIdx++;
    }

    int next() {
        if(arrayIdx == n) return -1;
        int val = nums[arrayIdx][index];
        index++;
        if(index == nums[arrayIdx].size()) {
            index = 0;
            arrayIdx ++;
            while(arrayIdx < n && nums[arrayIdx].empty()) arrayIdx ++;
        }
        return val;
    }

    bool hasNext() {
        return arrayIdx < n;
    }

private:
    vector<vector<int> > nums;
    int arrayIdx; //current array index
    int index; //index within current array
    int n; //number of arrays
};


/**************************************************** 
 ***    248,Hard,Strobogrammatic Number III 
 ****************************************************/

/*
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high.

For example,
Given low = "50", high = "100", return 3. Because 69, 88, and 96 are three strobogrammatic numbers.

Note:
Because the range might be a large number, the low and high numbers are represented as string. 
*/

/*
Idea is to find the number of strobogrammatic strings between [0, num] for a given number num. Then the count between range [low, high] is basically the difference between two runs, one for [0, high] and one for [0, low]. One corner case here is that if low is strobogrammatic, we need to exclude it from the count.

maintain a mapping from a number to its strobogrammatic counterparts, e.g. 0 => 0, 1 => 1, 6 => 9, 8 => 8, 9 => 6.

helper functions:
1. isStrobogrammatic(string num): check whether a string is strobogramatic or not. 
2. stroboLengthN(int n): return number of all strobogrammatic numbers of given length n (including leading zeros). 
3. stroboBelow(int v, int d): for a given 1 or 2 digit number v, return number of strobogrammatic numbers <= v that also has 1 or 2 digits, including numbers with leading zeros (e.g. "0", or "00").
4. sameLengthBelow(string str, bool countZero): a recursive function to find the number of strobogrammatic numbers <= str and has the same length as str. If countZero is set as true, we include numbers with leading zeros, e.g. 0880 is counted for sameLengthBelow(1981, true).

For a number of length n represented by num, the strobogrammatic numbers between [0, num] are:
1. Strings with length less than n (obtained by a loop calling stroboLenghtN).
2. Strings with length n, and most significant digit (MSD) < num[0], and digits 1 to n-2 can be any strobogrammatic strings of length n-2. This part can be calculated by multiplying results from stroboBelow(int v, int d) and stroboLengthN(n-2).
3. If num[0] is 0, 1, 6, 8, 9. Then we can also have strings with length n, and MSD = num[0]. The number of such strings can be calculated by recursively calling stroboBelow(str) for the substring num[1 .. n-1].
3'. In 3 we might be overcounting one number, e.g. when num = 98485, then we overcounted 98486, we need to decrement count. This only happens when num[n-1] is smaller than the counterpart of num[0], and num[1 .. n-1] is strobogrammatic number. 

corner cases:

1. low is equal to hi, return whether high is a strobogrammatic string.
2. low is large than hi, then return 0. Use a function to test if low is larger than hi.
*/

class Solution {
public:
    Solution() {
        mapping = {0, 1, -1, -1, -1, -1, 9, -1, 8, 6};
    }
    int strobogrammaticInRange(string low, string high) {
        if(low == high) return isStrobogrammatic(high);
        if(isLarger(low, high)) return 0;
        int count1 = countBelow(low);
        int count2 = countBelow(high);
        if(isStrobogrammatic(low)) count1--;
        return count2 - count1;
    }
    bool isLarger(const string& a, const string& b) {
        int m = a.size(), n = b.size();
        if(m != n) return m > n;
        for(int i = 0; i < m; ++i) {
            if(a[i] > b[i]) return true;
            if(a[i] < b[i]) return false;
        }
        return false; //equal, false
    }

    //count strobo numbers from 0 to num including num
    int countBelow(string num) {
        int count = 1; //"0"
        for(int n = 1; n < num.size(); ++n) {
            int tmp = stroboLengthN(n);
            if(n == 1) count += tmp-1; //not include zero 
            else count += tmp-tmp/5; //not include zero
        }
        count += sameLengthStroboBelow(num, false);
        return count;
    }
    //count strobogrammatic numbers <= str, with the same length as str (starting with "0" or "1" depending on countZero)
    int sameLengthStroboBelow(string str, bool countZero) {
	    int n = str.size();
        int count = 0;
        if(n == 1) {
            int v = str[0]-'0';
            count = stroboBelow(v, 1);
            if(!countZero) count --;
        } else if (n == 2) {
            int v = (str[0]-'0')*10 + (str[1]-'0');
            count = stroboBelow(v, 2);
            if(!countZero) count --;
        } else {
            int v1 = (str[0]-'0'), v2 = (str[n-1]-'0');
            //count strobo with first digit being 1 .. v1-1.
            if(v1 > 0) {
                int tmp = stroboBelow(v1*10-1, 2);
                if(!countZero) tmp--;
                count += tmp*stroboLengthN(n-2); 
            }
            string sub = str.substr(1, n-2);
            if(mapping[v1] >= 0) count += sameLengthStroboBelow(sub, true);
            if(v2 < mapping[v1] && isStrobogrammatic(sub)) count--; //avoid overcounting
        }
        return count;
    }

    // number of strobos <= v with d digits (including "0" or "00").
    // v is a number between 0-9 (when d = 1) or 0-99 (when d = 2).
    // 1d strobos: "0", "1", "8"
    // 2d strobos: "00", "11", "69", "88", "96"
    int stroboBelow(int v, int d) {
       int count = 0;
       if(d == 1) {
           if(v < 1) count = 1;
           else if(v < 8) count = 2;
           else count = 3;
       } else if(d == 2) {
           if(v < 11) count = 1;
           else if(v < 69) count = 2; //11
           else if(v < 88) count = 3;
           else if(v < 96) count = 4;
           else count = 5;     
       }
       return count;
    }

    //count strobo for digit n (can have leading zeros)
    int stroboLengthN(int n) {
        if(n == 0) return 0;
        int count = (n % 2 == 1) ? 3 : 5;
        while(n > 2) {
            n -= 2;
            count *= 5;  
        }
        return count;
    }

    bool isStrobogrammatic(string num) {
        int n = num.size();
        for(int i = 0; i < n/2; ++i) {
            char c1 = num[i];
            char c2 = num[n-i-1];
            if( (c1 == '0' && c2 == '0') ||
                (c1 == '1' && c2 == '1') ||
                (c1 == '6' && c2 == '9') ||
                (c1 == '8' && c2 == '8') ||
                (c1 == '9' && c2 == '6') ) continue;
            return false;
        }
        if(n % 2 == 1) {
            char c = num[n/2];
            if(c != '0' && c != '1' && c != '8') return false;
        }
        return true;
    }
    vector<int> mapping;
};

/**************************************************** 
 ***    247,Medium,Strobogrammatic Number II 
 ****************************************************/

/*
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Find all strobogrammatic numbers that are of length = n.

For example,
Given n = 2, return ["11","69","88","96"]. 
*/

// Solution 1. Recursive. First add solutions with leading zeros and put them in the end of vector. then erase them altogether.

class Solution {
public:
    vector<string> findStrobogrammatic(int n) {
        vector<string> result;
        if(n == 1) {
            result = {"0", "1", "8"};
            return result;
        }
        stroboHelper(n, result);
        //remove ones starting with zero
        int i = 0;
        for(i = 0; i < result.size(); ++i) {
            if(result[i][0] == '0') break;
        }
        result.resize(i);
        return result;
    }
    void stroboHelper(int n, vector<string>& result) {
        if(n == 1) result = {"1", "8", "0"}; 
        else if(n == 2) result = {"11", "69", "88", "96", "00"};
        else {
            vector<string> tmp;
            stroboHelper(n-2, tmp);
            for(auto it : tmp) {
                result.push_back('1'+it+'1');
                result.push_back('6'+it+'9');
                result.push_back('8'+it+'8');
                result.push_back('9'+it+'6');
            }
            for(auto it : tmp) result.push_back('0'+it+'0');
        }
    }
};

// Solution 2. Iterative. Avoid the annoying leading 0 issue by checking whether reaching last step.

class Solution {
public:
    vector<string> findStrobogrammatic(int n) {
        if(n <= 0) return vector<string>();
        if(n == 1) return {"0", "1", "8"};
        if(n == 2) return {"11", "69", "88", "96"};
        vector<string> result;
        if(n % 2 == 1) result = {"0", "1", "8"};
        else result = {"00", "11", "69", "88", "96"};
        vector<string> newresult;
        while(n > 2) {
            n -= 2;
            for(auto it : result) {
                if(n > 2) newresult.push_back('0'+it+'0');
                newresult.push_back('1'+it+'1');
                newresult.push_back('6'+it+'9');
                newresult.push_back('8'+it+'8');
                newresult.push_back('9'+it+'6');
            }
                
            result.swap(newresult);
            newresult.clear();
        }

        return result;
    }
};


/**************************************************** 
 ***    246,Easy,Strobogrammatic Number 
 ****************************************************/

/*
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to determine if a number is strobogrammatic. The number is represented as a string.

For example, the numbers "69", "88", and "818" are all strobogrammatic.
*/

// Checking front and end. Do not forget the middle character if length is odd.

class Solution {
public:
    bool isStrobogrammatic(string num) {
        int n = num.size();
        for(int i = 0; i < n/2; ++i) {
            char c1 = num[i];
            char c2 = num[n-i-1];
            if( (c1 == '0' && c2 == '0') ||
                (c1 == '1' && c2 == '1') ||
                (c1 == '6' && c2 == '9') ||
                (c1 == '8' && c2 == '8') ||
                (c1 == '9' && c2 == '6') ) continue;
            return false;
        }
        if(n % 2 == 1) {
            char c = num[n/2];
            if(c != '0' && c != '1' && c != '8') return false;
        }
        return true;
    }
};


/**************************************************** 
 ***    242,Easy,Valid Anagram 
 ****************************************************/

/*
Given two strings s and t, write a function to determine if t is an anagram of s.

For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false.

Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution to such case?
*/

/// Linear time solution by using a hash table (array indexing)
/// For unicode, we might use an unordered map (real hash table) to save memory space.

class Solution {
public:
    bool isAnagram(string s, string t) {
        int n = s.size();
        if (t.size() != n) return false;
        vector<int> cnt(256, 0);
        for (int i = 0; i < n; ++i) cnt[s[i]]++;
        for (int i = 0; i < n; ++i) {
            cnt[t[i]]--;
            if(cnt[t[i]] < 0) return false;
        }
        return true;
    }
};

// Solution 2. O(nlgn) solution using sorting.

class Solution {
public:
    bool isAnagram(string s, string t) {
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
};

/**************************************************** 
 ***    241,Medium,Different Ways to Add Parentheses 
 ****************************************************/

/*
Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *.

Example 1

Input: "2-1-1".

((2-1)-1) = 0
(2-(1-1)) = 2

Output: [0, 2]

Example 2

Input: "2*3-4*5"

(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10

Output: [-34, -14, -10, -10, 10]
*/

// Dynamic programming solution.
// First parse string and save numbers and operators separately.
// Then start from bottom up, for large string break into small pieces and check all options.

class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        if(input.empty()) return vector<int>();
        vector<int> nums; 
        vector<char> ops;
        parse(input, nums, ops);
        int n = nums.size(); //number of numbers
        //mp[i][j]: outcomes from i (i = [0..n]) numbers starting at j (j = [0 .. n-1]). 
        vector<vector<vector<int> > > mp(n+1, vector<vector<int> >(n, vector<int>()));
        //len = 1 case
        for(int i = 0; i < n; ++i) {
           mp[1][i].push_back(nums[i]);
        }
        for(int len = 2; len <= n; ++len) {
            for (int i = 0; i + len <= n; ++i) {
                int j = i + len - 1; //i start, j end, inclusive
                //try to break it from i+1 .. to j-1
                for(int k = i; k < j; ++k) { // break like this: num[k] | op[k] | num[k+1]
                    for(auto it1 : mp[k-i+1][i]) {
                        for(auto it2 : mp[j-k][k+1]) {
                            mp[len][i].push_back(eval(it1, it2, ops[k]));
                        }
                    }
                }
            }
        }
        return mp[n][0];
    }
    
    int eval(int v1, int v2, char op) {
       if(op == '+') return v1+v2;
       if(op == '-') return v1-v2;
       if(op == '*') return v1*v2;
       return 0;
    }

    void parse(string& input, vector<int>& nums, vector<char>& ops) {
        int val = 0;
        for(int i = 0; i < input.size(); ++i) {
            char c = input[i];
            if(isdigit(c)) {
               val = 10*val + (c - '0');
            } else {
               ops.push_back(c);
               nums.push_back(val);
               val = 0;
            }
        }
        nums.push_back(val); //don't forget last one!
    }
};

// Recursive solution using divide and conquer. Final vector is the cartesian product of two sub-vectors

class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> numbers;
        vector<char> operators;
        int num = 0;
        for(int i = 0; i < input.size(); i++) {
            char c = input[i];
            if(c >= '0' && c <= '9') num = num*10 + (c-'0');
            else {
                numbers.push_back(num);
                operators.push_back(c);
                num = 0;
            }
        }
        numbers.push_back(num);
        
        int n = numbers.size();
        vector<int> ret;
        eval(numbers, operators, 0, n-1, ret);
        return ret;
    }
    
    void eval(vector<int>& numbers, vector<char>& operators, int lo, int hi, vector<int>& vals) {
        vals.clear();
        if(lo == hi) {
            vals.push_back(numbers[lo]); //only one
            return;
        }
        vector<int> v1, v2;
        for(int mid = lo; mid < hi; ++mid) {
            eval(numbers, operators, lo, mid, v1);
            eval(numbers, operators, mid+1, hi, v2);
            for (int j1 = 0; j1 < v1.size(); ++j1) {
                for(int j2 = 0; j2 < v2.size(); ++j2) {
                    vals.push_back(eval(v1[j1], v2[j2], operators[mid]));
                }
            }
        }
    }
    
    int eval(int n1, int n2, char op) {
        switch (op) {
            case '+': return n1 + n2;
            case '-': return n1 - n2;
            case '*': return n1 * n2;
            default : return 0;
        }
    }
};

/**************************************************** 
 ***    239,Hard,Sliding Window Maximum 
 ****************************************************/

/*
Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

Therefore, return the max sliding window as [3,3,5,5,6,7].

Note:
You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for non-empty array.
*/

// A O(k*n) solution.
// For each new number, look further and predict the maximum for the next k steps

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
       int n = nums.size();
       vector<int> ret;
       if(k == 0 || n < k) return ret;
       int m = n-k+1;
       ret.resize(m, INT_MIN);
       //predict the possible maximums according to nums[i]
       for(int i = 0; i < n; ++i) {
          for(int j = max(0, i-k+1); j <= min(i, m-1); ++j) {
             ret[j] = max(ret[j], nums[i]);
          }
       }
       return ret;
    }
};
/*
Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

Therefore, return the max sliding window as [3,3,5,5,6,7].

Note:
You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for non-empty array.
*/

// Linear time (one pass) solution
// Maintain a doubly-ended queue. add newly seen numbers to end of queue. Several operations:
// 1. when we see a new number, pop all the smaller numbers from the back of queue, and then insert the new value. (the new number makes these smaller numbers values stale)
// 2. also check if front of queque is out of the sliding window, if yes then remove front.
// 3. the maximum is simply the front element of queue.

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        int n = nums.size();
        if(n == 0 || k == 0 || n < k) return result;
        result.resize(n-k+1);
        deque<int> q; //position
        for(int i = 0; i < n; ++i) {
            int val = nums[i];
            if(!q.empty() && i-q.front() == k) q.pop_front();
            while(!q.empty() && nums[q.back()] <= val) {
                q.pop_back();
            }
            q.push_back(i);
            if(i >= k-1) result[i-k+1] = nums[q.front()];
        }
        return result;
    }
};

/**************************************************** 
 ***    238,Medium,Product of Array Except Self 
 ****************************************************/

/*
Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].

Solve it without division and in O(n).

For example, given [1,2,3,4], return [24,12,8,6].

Follow up:
Could you solve it with constant space complexity? (Note: The output array does not count as extra space for the purpose of space complexity analysis.)
*/

/// O(n) time, O(1) space solution.
/// Two passes, one from left and one from right
/// Product without self = product of all elements to the left, times product of all elements to the right
/// First pass, calculate products of all elements to the left and save it to ret array
/// Second pass, calculate products of all elements to the right, and multiple to the ret array values
/// when done, return the ret array

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ret(n, 1);
        int t = 1;
        for (int i = 1; i < n; ++i)
            ret[i] = ret[i-1]*nums[i-1];
        for (int i = n-2; i >= 0; --i) {
            t *= nums[i+1];
            ret[i] *= t;
        }
        return ret;
    }
};

/**************************************************** 
 ***    237,Easy,Delete Node in a Linked List 
 ****************************************************/

/*
Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.

Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3, the linked list should become 1 -> 2 -> 4 after calling your function. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/// O(1) solution, just link current node's pointer to the next next node, delete the next node.
/// For safety, do the sanity check to ensure node is not null, or last node in the list.

class Solution {
public:
    void deleteNode(ListNode* node) {
        //first do some sanity check
        if(node == NULL || node->next == NULL) return;
        node->val = node->next->val;
        ListNode* t = node->next;
        node->next = t->next;
        delete t;
    }
};

/**************************************************** 
 ***    236,Medium,Lowest Common Ancestor of a Binary Tree 
 ****************************************************/

/*
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

        _______3______
       /              \
    ___5__          ___1__
   /      \        /      \
   6      _2       0       8
         /  \
         7   4

For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// The tree is not BST, so we can't use value comparison. Instead, we need to examine both subtrees recursively O(n).

// Solution 1. Use two auxiliary vectors storing the search paths from root to the node. 
// Compare the two paths and find the last element both in two paths.

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || !p || !q) return NULL;
        if( !search(root, p, path1) || !search(root, q, path2)) return NULL;
        TreeNode* node = NULL;
        while(!path1.empty() && !path2.empty()) {
            TreeNode* n1 = path1.front(); path1.pop_front();
            TreeNode* n2 = path2.front(); path2.pop_front();
            if(n1 == n2) node = n1;
            else break;
        }
        return node;
    }
    //search p under subtree root
    bool search(TreeNode* root, TreeNode* p, deque<TreeNode*>& path) {
        if(!root) return false;

        path.push_back(root);
        if(root == p) return true;
        //search left and right subtree
        if(search(root->left, p, path) || search(root->right, p, path)) return true;
        path.pop_back(); //retrace
        return false;
    }
    deque<TreeNode*> path1, path2;
};

// Solution 2 without the auxiliary path vector.
// Assumes p and q are not NULL.
// Similar to Solution 1 in that when root is equal to either node, return the root.
// Then call the function for left and right subtrees. If both returns a non NULL value, that means one node is in left sub-tree, and the other is in the right sub-tree. In this case root is the LCA, and we return root.
// In other cases, simply return the value returned by the recursive calls.

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return NULL;
        if(root == p || root == q) return root;
        TreeNode* lca_l = lowestCommonAncestor(root->left, p, q);
        TreeNode* lca_r = lowestCommonAncestor(root->right, p, q);
        if(lca_l && lca_r) return root;
        else return (lca_l ? lca_l : lca_r);
    }
};


/**************************************************** 
 ***    235,Easy,Lowest Common Ancestor of a Binary Search Tree 
 ****************************************************/

/*
Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

        _______6______
       /              \
    ___2__          ___8__
   /      \        /      \
   0      _4       7       9
         /  \
         3   5

For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6. Another example is LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Take advantage of the property of BST. Do it recursively.
// If root is same as either nodes, then root is LCA.
// If the two nodes are one different sides of root, then root is LCA.
// Otherwise recursively go to root's left or right subtree depending on which side of the root the nodes are at.
// Time complexity is O(h), where h is the height of tree.

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || !p || !q) return NULL;
        return LCA(root, p, q);
    }
    TreeNode* LCA(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return NULL;
        if(p == root || q == root) return root; //one is equal to root
        if((p->val < root->val) ^ (q->val < root->val)) return root; //lying on two sides of root
        if(p->val < root->val) return LCA(root->left, p, q);
        else return LCA(root->right, p, q);
    }
};



/**************************************************** 
 ***    231,Easy,Power of Two 
 ****************************************************/

/*
Given an integer, write a function to determine if it is a power of two.
*/

// use bit operations.
// Caveat: need to check if larger than 0!

class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n>0 && !(n&(n-1));
	// return !n && !(n & 0x80000000) && !(n&(n-1))
    }
};

/**************************************************** 
 ***    230,Medium,Kth Smallest Element in a BST 
 ****************************************************/

/*
Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note:
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?

Hint:

    Try to utilize the property of a BST.
    What if you could modify the BST node's structure?
    The optimal runtime complexity is O(height of BST).
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

//First find minimum, and store the search path. Then do inorder traversal k times.
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        if(!root) return 0;
        stack<TreeNode*> path;
        while(root) {
            path.push(root);
            root = root->left;
        }
        TreeNode* node(NULL);
        int i = 1;
        while(1) {
            if(path.empty()) return 0;
            node = path.top(); path.pop();
            if(i == k) return node->val;
            i++;
            node = node->right;
            while(node) {
                path.push(node); node = node->left;
            }
        }
        return 0;
    }
};


/**************************************************** 
 ***    226,Easy,Invert Binary Tree 
 ****************************************************/

/*
Invert a binary tree.

     4
   /   \
  2     7
 / \   / \
1   3 6   9

to

     4
   /   \
  7     2
 / \   / \
9   6 3   1

Trivia:
This problem was inspired by this original tweet by Max Howell:

    Google: 90% of our engineers use the software you wrote (Homebrew), but you can’t invert a binary tree on a whiteboard so fuck off.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == NULL) return NULL;
        //swap left and right children
        swap(root->left, root->right);
        //recursively run invert on subtrees
        invertTree(root->left); //don't have to return the root
        invertTree(root->right);
        return root; //don't forget to return
    }
};


/**************************************************** 
 ***    223,Easy,Rectangle Area 
 ****************************************************/

/*
Find the total area covered by two rectilinear rectangles in a 2D plane.

Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.
Rectangle Area

Assume that the total area is never beyond the maximum possible value of int.
*/

// Key is how to detect two line segments overlap, and how to find the overlap length
// Caveat: should return the *total* area, not the overlapped area!

class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int area1 = (C-A)*(D-B);
        int area2 = (G-E)*(H-F);
        int m = 0, n = 0;
        if(C > E && A < G) m = min(C, G) - max(A, E);
        if(D > F && B < H) n = min(D, H) - max(B, F);
        
        return area1 + area2 - m*n;
    }
};

/**************************************************** 
 ***    221,Medium,Maximal Square 
 ****************************************************/

/*
Given a 2D binary matrix filled with 0's and 1's, find the largest square containing all 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

Return 4. 
*/

// Same idea as maximal rectangle, use routine in finding largest rectangle. Except when calculating area, use min(height, length)^2. See solutions in 085 maximal rectangle

class Solution {
public:
    int maximalSquare(vector<vector<char> > &matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> height(n, 0);
        int max_area = 0;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                height[j] = (matrix[i][j] == '1') ? height[j]+1 : 0;
            }
            max_area = max(max_area, largestSquareArea(height));
        }
        return max_area;
    }

    int largestSquareArea(vector<int>& height) {
        if(height.empty()) return 0;
        height.push_back(0);
        deque<int> s; //stack for positions
        int n = height.size();
        int max_area = 0;
        for(int i = 0; i < n; ++i) {
             while(!s.empty() && height[s.back()] > height[i]) {
                int h = height[s.back()];
                s.pop_back();
                int j = s.empty() ? 0 : s.back()+1;
                int side = min(h, i-j);
                max_area = max(max_area, side*side);
            }
            s.push_back(i);
        }
        return max_area;
    }
};

/**************************************************** 
 ***    218,Hard,The Skyline Problem 
 ****************************************************/

/*
A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo (Figure A), write a program to output the skyline formed by these buildings collectively (Figure B).
Buildings Skyline Contour

The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi], where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively, and Hi is its height. It is guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX, and Ri - Li > 0. You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

For instance, the dimensions of all buildings in Figure A are recorded as: [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .

The output is a list of "key points" (red dots in Figure B) in the format of [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline. A key point is the left endpoint of a horizontal line segment. Note that the last key point, where the rightmost building ends, is merely used to mark the termination of the skyline, and always has zero height. Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.

For instance, the skyline in Figure B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].

Notes:

    The number of buildings in any input list is guaranteed to be in the range [0, 10000].
    The input list is already sorted in ascending order by the left x position Li.
    The output list must be sorted by the x position.
    There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]
*/

// divide and conquer, similar to merge sort.
// The crux is in the merge routine. For a new point, we compare it with the last height of the other array. The merge is designed so no duplicates of x coords will appear. But duplicates for the heights will appear, so need to remove them in the end.

class Solution {
public:
    typedef pair<int, int> Point;

    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        vector<Point> skyline;
        int n = buildings.size();
        getSkyline(buildings, 0, n-1, skyline);
        return skyline;
    }
    void getSkyline(const vector<vector<int>>& buildings, int lo, int hi, vector<Point>& skyline) {
        if(lo > hi) return;
        if(lo == hi) {
            skyline.push_back(make_pair(buildings[lo][0], buildings[lo][2])); //left, height
            skyline.push_back(make_pair(buildings[lo][1], 0)); //right, 0
            return;
        }
        //now divide and conquer
        int mid = lo + (hi-lo)/2;
        vector<Point> left, right;
        getSkyline(buildings, lo, mid, left);
        getSkyline(buildings, mid+1, hi, right);
        merge(left, right, skyline);
    }
    void merge(vector<Point>& v1, vector<Point>& v2, vector<Point>& v) {
        int i = 0, j = 0, m = v1.size(), n = v2.size();
        int last_y1 = 0, last_y2 = 0;
        while(i < m || j < n) {
            int x1 = (i < m) ? v1[i].first : INT_MAX;
            int y1 = (i < m) ? v1[i].second : 0;
            int x2 = (j < n) ? v2[j].first : INT_MAX;
            int y2 = (j < n) ? v2[j].second : 0;
            if(x1 == x2) {
                v.push_back(make_pair(x1, max(y1, y2)));
                last_y1 = y1; last_y2 = y2;
                i++; j++;
            } else if(x1 < x2) {
                v.push_back(make_pair(x1, max(y1, last_y2)));
                last_y1 = y1;
                i++;
            } else {
                v.push_back(make_pair(x2, max(y2, last_y1)));
                last_y2 = y2;
                j++;
            }
        }
        //remove duplicates
        int l = 0;
        for(int k = 0; k < v.size(); ++k) {
            if(k == 0 || v[k].second != v[k-1].second) {
                v[l++] = v[k];
            }
        }
        v.resize(l);
    }
};


// An old solution

// divide and conquer, similar to merge sort.
// two caveats:
// 1. avoid duplicated heights ([1,4], [2, 4] is not allowed)
// 2. avoid duplicated coordinates, e.g. two buildings both span [1, 3] but with different heights, need to check if the current strip has same coordinate as previous
class Solution {
public:
    typedef pair<int, int> Strip;

    vector<pair<int, int> > getSkyline(vector<vector<int> >& buildings) {
        return getSkylineUtil(buildings, 0, buildings.size()-1);
    }

    //get strips for buildings[lo .. hi]
    vector<Strip> getSkylineUtil(const vector<vector<int> >& buildings, int lo, int hi) {
        vector<Strip> ret;
        if (lo > hi) return ret;
        if (lo == hi) {  //only one building
            ret.resize(2);
            ret[0] = make_pair(buildings[lo][0], buildings[lo][2]);
            ret[1] = make_pair(buildings[lo][1], 0);
            return ret;
        }
        int mid = (lo + hi) / 2;
        const vector<Strip>& left  = getSkylineUtil(buildings, lo,   mid);
        const vector<Strip>& right = getSkylineUtil(buildings, mid+1, hi);
        return merge(left, right);
    }
    
    //merge two strips
    vector<Strip> merge(const vector<Strip>& a, const vector<Strip>& b) {
        vector<Strip> ret;
        size_t m = a.size(), n = b.size();
        int side(0);
        int ha(0), hb(0), h(-1), x(INT_MIN), newh(0), newx(0);
        for(size_t i = 0, j = 0; i < m || j < n; ) {
            if(i == m) side = 1; //right
            else if(j == n) side = 0; //left
            else side = (a[i].first < b[j].first) ? 0 : 1;

            if (side == 0) { //picked a strip from a
                newx = a[i].first; 
                ha = a[i].second;  //update ha
                i++;
            } else {
                newx = b[j].first; 
                hb = b[j].second; //update hb
                j++;
            }
            newh = max(ha, hb);
            if (h != newh) { // avoid duplicated height
                if(newx == x) ret.back() = make_pair(newx, newh); //update last entry, avoid duplicated x
                else ret.push_back(make_pair(newx, newh)); //append new entry
                h = newh; //update h
                x = newx; //update x
            }
        }
        return ret;
    }
};

/**************************************************** 
 ***    216,Medium,Combination Sum III 
 ****************************************************/

/*
Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.

Ensure that numbers within the set are sorted in ascending order.

Example 1:

Input: k = 3, n = 7

Output:

[[1,2,4]]


Example 2:

Input: k = 3, n = 9

Output:

[[1,2,6], [1,3,5], [2,3,4]]
*/

/// Solution 1. Recursive solution. Choose number in ascending order, track how many trials we are left, and the next available number to choose.
// Terminate at three conditions:
// 1. Searched beyond number 9.
// 2. Used up all k trials.
// 3. target sum is smaller than the next number i

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int> > result;
        if(k == 0 || n <= 0) return result;
        vector<int> tmp;
        dfs(1, k, n, tmp, result);
    }
    //search starting from i, k numbers left
    void dfs(int i, int k, int target, vector<int>& tmp, vector<vector<int> >& result) {
        if(target == 0 && k == 0) { //target is 0 and we used exactly k numbers
            result.push_back(tmp);
            return;
        }
        if(i == 10 || k < 0 || target < i) return; //used up all numbers or all trials, or target < i.

        tmp.push_back(0);
        for(int j = i; j < 10; ++j) {
            tmp.back() = j;
            dfs(j+1, k-1, target-j, tmp, result);
        }
        tmp.pop_back();
    }
};

// Solution 2. Iterative. Keep a running sum and trial number. The tricky part is how to calculate the partial sums properly. 
// Caveats:
// sum += tmp[i] should be placed after tmp[i] == 10 checks!
// after retracing, need to first subtract the tmp[i] value from sum, so that when tmp[i] is incremented, sum += tmp[i] will give the correct new usm.

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int> > result;
        if(k == 0 || n <= 0) return result;
        vector<int> tmp(k, 0);
        int i = 0; //i-th trial
        int sum = 0;
        while(i >= 0) {
            if(i == k) {
                if(sum == n) result.push_back(tmp); 
                i--; 
                if(i >= 0) sum -= tmp[i]; 
                continue; //retrace
            }
            tmp[i]++;
            if(tmp[i] == 10) { //retrace
                i--; 
                if(i >= 0) sum -= tmp[i]; 
                continue;
            } 
            sum += tmp[i]; //add to sum
            i++;
            if(i < k) tmp[i] = tmp[i-1]; //initialize starting point for next number (for tmp[i]++).
        }
        return result;
    }
};



/**************************************************** 
 ***    214,Hard,Shortest Palindrome 
 ****************************************************/

/*
Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

For example:

Given "aacecaaa", return "aaacecaaa".

Given "abcd", return "dcbabcd".
*/

//Solution 1. O(n2) solution results in TLE.
class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        if(n <= 1) return s;
        int i = 0, j = 0;
        int max_len = 1; //max length palindrome substring s[0.. max_len-1]
        for(i = (n-1)/2; i >= 0; --i) { //search first half only
            //check even case: [i-j .. i i+1 .. i+j+1]
            for(j = 0; i-j >= 0 && s[i-j] == s[i+j+1]; ++j) ;
            if(j == i+1) { max_len = 2*j; break; }
            
            //check odd case: [i-j .. i .. i+j]
            for(j = 0; i - j >= 0 && s[i-j] == s[i+j]; ++j) ;
            if(j == i+1) { max_len = 2*j-1; break; }
        }
        string result;
        for(int k = n-1; k >= max_len; --k) {
            result.push_back(s[k]);
        }
        result += s;
        return result;
    }
};

/*
Solution 2. KMP algorithm. Text is reverse of s, pattern is s, search s in t, and find the last j position before exit. j is the length of the longest palindrome substring.
e.g.
s = aacecaaa
text    = aaacecaa
pattern = aacecaaa
after KMP, we end up with
    01234567
    aaacecaa
     aacecaaa
            j = 7, => lps = "aacecaa"
*/  

class Solution {
public:
    string shortestPalindrome(string s) {
       int n = s.size();
        if(n <= 1) return s;
        string t = s; //text to search, reverse of s
        reverse(t.begin(), t.end());
        //s is pattern
        vector<int> f(n+1, -1); //transfer function
        int k = -1;
        for(int j = 1; j <= n; ++j) {
            while(k >= 0 && s[k] != s[j-1]) k = f[k];
            f[j] = ++k;
        }
        //now start matching
        int i(0), j(0);
        while(i < n && j < n) {
            if(t[i] == s[j]) { i++; j++; } 
            else if(j == 0) i++;
            else j = f[j];
        }
        //previous j characters matched
        if(j == n) return s;
        else return t.substr(0, n-j) + s;
    }
};


/**************************************************** 
 ***    212,Hard,Word Search II 
 ****************************************************/

/*
Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

For example,
Given words = ["oath","pea","eat","rain"] and board =

[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]

Return ["eat","oath"].

Note:
You may assume that all inputs are consist of lowercase letters a-z.

click to show hint.

You would need to optimize your backtracking to pass the larger test. Could you stop backtracking earlier?

If the current candidate does not exist in all words' prefix, you could stop backtracking immediately. What kind of data structure could answer such query efficiently? Does a hash table work? Why or why not? How about a Trie? If you would like to learn how to implement a basic trie, please work on this problem: Implement Trie (Prefix Tree) first.
*/

/*
Use a Trie data-structure. 
 Perform dfs on the board, construct the string formed by the path, see if it is contained as prefix in the Trie, if not, then stop searching. This is the essense of using Trie to speed up search.
 Caveats:
1. in trie element removal, do not remove root.
2. need to avoid duplicated entries in the return array, solution 1 erases the found entries in the Trie, solution 2 implements a found() function to check if the solution is in the array or not.
3. When found a match, need to continue searching! Do not simply return!
*/

// Solution 1.
class Trie {
public:
    struct Node {
        bool isEnd;
        vector<Node*> link;
        Node() : isEnd(false) {
            link.resize(26, NULL);
        }
    };

    Trie() {
        head = new Node();
    }

    ~Trie() {
        eraseNode(head);
    }
    void insert(const string& s) {
        insertUtil(head, s, 0);
    }

    bool exist(const string& s) {
        Node *node = find(head, s, 0);
        return node != NULL && node->isEnd;
    }
    bool existPrefix(const string& s) {
        Node *node = find(head, s, 0);
        return node != NULL;
    }
    void erase(const string& s) {
        eraseUtil(head, s, 0);
    }
private:
    void insertUtil(Node* node, const string& s, int k) {
        if(k == s.size()) { node->isEnd = true; return; }
        int i = s[k] - 'a';
        if(node->link[i] == NULL) node->link[i] = new Node();
        insertUtil(node->link[i], s, k+1);
    }

    Node* eraseUtil(Node* node, const string& s, int k) {
        if(node == NULL) return NULL;
        if(k == s.size()) {
            node->isEnd = false;
        } else {
            int c = s[k] - 'a';
            node->link[c] = eraseUtil(node->link[c], s, k+1);
        }
        if(node != head && !hasLinks(node) && !node->isEnd) {
            delete node; //no nodes below it
            node = NULL;
        }
        return node;
    }
    bool hasLinks(Node* node) {
        if(node == NULL) return false;
        for(int i = 0; i < 26; ++i) 
            if(node->link[i]) return true;
        return false;
    }
    Node* find(Node* node, const string& s, int k) {
        if(node == NULL || k == s.size()) return node;
        int i = s[k] - 'a';
        return find(node->link[i], s, k+1);
    }
    void eraseNode(Node* node) {
        if(!node) return;
        for(int i = 0; i < 26; ++i) eraseNode(node->link[i]);
        delete node;
    }
    Node* head;
};


class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> result;
        if(board.empty() || board[0].empty()) return result;
        int m = board.size(), n = board[0].size();
        string tmp;
        for(auto it : words) t.insert(it);
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                dfs(board, i, j, tmp, result);
            }
        }
        return result;
    }

    void dfs(vector<vector<char>>& board, int i, int j, string& tmp, vector<string>& result) {
        int m = board.size(), n = board[0].size();
        if(i < 0 || i >= m || j < 0 || j >= n) return; //illegal position
        if(board[i][j] == '*') return; //visited
        char c = board[i][j];
        tmp = tmp + c;
        if(t.exist(tmp)) {
            result.push_back(tmp);
            t.erase(tmp);
        }
        board[i][j] = '*';
        if(t.existPrefix(tmp)) {
            dfs(board, i, j+1, tmp, result);
            dfs(board, i, j-1, tmp, result);
            dfs(board, i+1, j, tmp, result);
            dfs(board, i-1, j, tmp, result);
        }
        board[i][j] = c;
        tmp.pop_back();
    }
    Trie t;
};

// Solution 2.
class Trie {
public:
    struct Node {
        bool isKey;
        vector<Node*> links;
        Node() : isKey(false) {
            links.resize(26, NULL);
        }
    };

    Trie() {
        root = new Node();
    }

    ~Trie() {
        eraseNode(root);
    }
    void insert(const string& s) {
        insertUtil(root, s, 0);
    }

    bool exist(const string& s) {
        Node *node = find(root, s, 0);
        return node != NULL && node->isKey;
    }
    bool existPrefix(const string& s) {
        Node *node = find(root, s, 0);
        return node != NULL;
    }
    void erase(const string& s) {
        eraseUtil(root, s, 0);
    }
private:
    void insertUtil(Node* node, const string& s, int k) {
        if(k == s.size()) { node->isKey = true; return; }
        int i = s[k] - 'a';
        if(node->links[i] == NULL) node->links[i] = new Node();
        insertUtil(node->links[i], s, k+1);
    }

    Node* eraseUtil(Node* node, const string& s, int k) {
        if(node == NULL) return NULL;
        if(k == s.size()) {
            node->isKey = false;
        } else {
            int c = s[k] - 'a';
            node->links[c] = eraseUtil(node->links[c], s, k+1);
        }
        if(node != root && !hasLinks(node) && !node->isKey) {
            delete node; //no nodes below it
            node = NULL;
        }
        return node;
    }
    bool hasLinks(Node* node) {
        if(node == NULL) return false;
        for(int i = 0; i < 26; ++i) 
            if(node->links[i]) return true;
        return false;
    }
    Node* find(Node* node, const string& s, int k) {
        if(node == NULL || k == s.size()) return node;
        int i = s[k] - 'a';
        return find(node->links[i], s, k+1);
    }
    void eraseNode(Node* node) {
        if(!node) return;
        for(int i = 0; i < 26; ++i) eraseNode(node->links[i]);
        delete node;
    }
    Node* root;
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> result;
        if(board.empty() || board[0].empty()) return result;
        int m = board.size(), n = board[0].size();
        string tmp;
        for(auto it : words) t.insert(it);
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                dfs(board, i, j, tmp, result);
            }
        }
        return result;
    }

    void dfs(vector<vector<char>>& board, int i, int j, string& tmp, vector<string>& result) {
        int m = board.size(), n = board[0].size();
        if(i < 0 || i >= m || j < 0 || j >= n) return; //illegal position
        if(board[i][j] == '*') return; //visited
        char c = board[i][j];
        tmp = tmp + c;
        if(t.exist(tmp) && !found(result, tmp)) {
            result.push_back(tmp);
        }
        board[i][j] = '*';
        if(t.existPrefix(tmp)) {
            dfs(board, i, j+1, tmp, result);
            dfs(board, i, j-1, tmp, result);
            dfs(board, i+1, j, tmp, result);
            dfs(board, i-1, j, tmp, result);
        }
        board[i][j] = c;
        tmp.pop_back();
    }
    
    bool found(vector<string>& result, string& tmp) {
        for(auto it : result) {
            if(tmp == it) return true;
        }
        return false;
    }
    Trie t;
};



/**************************************************** 
 ***    209,Medium,Minimum Size Subarray Sum 
 ****************************************************/

/*
Given an array of n positive integers and a positive integer s, find the minimal length of a subarray of which the sum ≥ s. If there isn't one, return 0 instead.

For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.

click to show more practice.
More practice:

If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n).
*/

/// Solution 1: sliding window. Move one step further to optimize. O(n)

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        int sum = 0, minL = INT_MAX;
        for(int i = 0, istart = 0; i < n; ++i) {
            sum += nums[i];
            if(sum < s) continue;
            while(sum - nums[istart] >= s) {
                sum -= nums[istart++];
            }
            minL = min(minL, i-istart+1);
            sum -= nums[istart++]; //move one step further
        }
        return minL != INT_MAX ? minL : 0;
    }
};

/// Solution 2: binary search on the accumulative sums. O(nlogn)
// First create the partial sum array, then scan the sum, if the paritial_sum >= s, then we search for the array before the element and find the largest element <= (partial_sum - s). Use binary search
// Since all numbers are positive, if we see partial_sum == s, we can skip the binary search and use i+1 as the length (can't be shorter than nums[0..i].

/// So far, divide and conquer seems not possible...

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if(nums.empty()) return 0;
        //get partial sums
        int n = nums.size();
        vector<int> partial(n, 0);
        partial[0] = nums[0];
        int minL = INT_MAX;
        for(int i = 1; i < n; ++i) {
            partial[i] = partial[i-1] + nums[i];
        }
        for(int i = 0; i < n; ++i) {
            if(partial[i] >= s) {
                //binary search for largest number <= residue in sums[0, i-1];
                int residue = partial[i] - s;
                int lo = 0, hi = i-1, mid = 0;
                while(lo <= hi) {
                    mid = lo + (hi - lo) / 2;
                    if(partial[mid] <= residue) lo = mid+1;
                    else hi = mid-1;
                }
                minL = min(minL, i-hi);
            }
        }
        return minL == INT_MAX ? 0 : minL;
    }
};


/**************************************************** 
 ***    208,Medium,Implement Trie (Prefix Tree) 
 ****************************************************/

/*
Implement a trie with insert, search, and startsWith methods.

Note:
You may assume that all inputs are consist of lowercase letters a-z. 
*/

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");

/// Solution 1, simpler, with delete function (which slows down runtime by 40 ms!)

class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() {
        isKey = false;
        links.resize(26, NULL);
    }

    bool isKey;
    vector<TrieNode*> links;
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        eraseUtil(root);
    }
    // Inserts a word into the trie.
    void insert(string word) {
        insertUtil(root, word, 0);
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode* node = searchUtil(root, word, 0);
        return node != NULL && node->isKey;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode* node = searchUtil(root, prefix, 0);
        return node != NULL;
    }

private:
    //root can never be NULL
    void insertUtil(TrieNode* root, const string& word, int i) {
        if(i == word.size()) { root->isKey = true; return; }
        int c = word[i] - 'a';
        if(!root->links[c]) root->links[c] = new TrieNode();
        insertUtil(root->links[c], word, i+1);
    }
    TrieNode* searchUtil(TrieNode* root, const string& word, int i) {
        if(root == NULL) return NULL;
        if(i == word.size()) return root;
        int c = word[i] - 'a';
        return searchUtil(root->links[c], word, i+1);
    }
    void eraseUtil(TrieNode* root) {
        if(!root) return;
        for(int c = 0; c < 26; ++c) eraseUtil(root->links[c]);
        delete root;
    }
    TrieNode* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");


/// Solution 2, slightly different.

class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() {
        links = new TrieNode*[26];
        for (int i = 0; i < 26; ++i)
            links[i] = NULL;
        isKey = false;
    }
    
    TrieNode** links; //array of pointers
    bool isKey;
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
        root = insert(root, word, 0);
    }

    TrieNode* insert(TrieNode* x, string word, int d) {
        if (x == NULL) { x = new TrieNode(); }
        if (d == word.size()) x->isKey = true;
        else {
            int i = word[d] - 'a';
            x->links[i] = insert(x->links[i], word, d+1);
        }
        return x;
    }
    
    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode *x = search(root, word, 0);
        return (x != NULL && x->isKey);
    }
    
    TrieNode* search(TrieNode* x, string word, int d) {
        if (x == NULL) return NULL;
        if (d == word.length()) return x;
        int i = word[d] -'a';
        return search(x->links[i], word, d+1);
    }
    
    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode* x = search(root, prefix, 0);
        return x != NULL;
    }
    
private:
    TrieNode* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");

/**************************************************** 
 ***    206,Easy,Reverse Linked List 
 ****************************************************/

/*
Reverse a singly linked list.

click to show more hints.
Hint:

A linked list can be reversed either iteratively or recursively. Could you implement both?
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Solution 1. Iterative solution. Use two pointers p and q. Temporary store q's next element.
// remember to set head->next to NULL at last step!

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head) return NULL;
        ListNode* p = head, *q = head->next; //q goes beyond p
        while(q) {
            ListNode *next = q->next;
            q->next = p;
            p = q;
            q = next;
        }
        head->next = NULL;
        return p;
    }
};

// Solution 2. Recursive solution. Set head's next pointer to NULL after calling reverse recursively for it's next. It's next will be assigned after traceback, when processing it's ancestor node.

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head) return NULL;
        if(!head->next) return head;
        ListNode *newhead = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;
        return newhead;
    }
};


/**************************************************** 
 ***    205,Easy,Isomorphic Strings 
 ****************************************************/

/*
Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.

For example,
Given "egg", "add", return true.

Given "foo", "bar", return false.

Given "paper", "title", return true.

Note:
You may assume both s and t have the same length.
*/

//Use two maps, one mapping s to t and the other backwards. Use indices array to mimic map for fast access. 

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if(s.size() != t.size()) return false;
        if(s.empty()) return true;
        int n = s.size();
        vector<int> s2t(256, -1), t2s(256, -1);
        for(int i = 0; i < n; ++i) {
            int a = s[i], b = t[i];
            if(s2t[a] == -1 && t2s[b] == -1) { //new entry, insert to both maps
                s2t[a] = b; t2s[b] = a;
            } else if(s2t[a] == b && t2s[b] == a) continue; //matches, continue
            else return false; //other cases, simply return false.
        }
        return true;
    }
};


/**************************************************** 
 ***    203,Easy,Remove Linked List Elements 
 ****************************************************/

/*
Remove all elements from a linked list of integers that have value val.

Example
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Solution using a dummy head

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if(!head) return NULL;
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode *p = dummy, *q = dummy->next;
        //q is one step ahead of p
        while(q) {
            if(q->val == val) { //delete q
                p->next = q->next;
                delete q;
                q = p->next;
            } else { //just move forward
                p = p->next;
                q = q->next;
            }
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};


/**************************************************** 
 ***    202,Easy,Happy Number 
 ****************************************************/

/*
Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

Example: 19 is a happy number

    12 + 92 = 82
    82 + 22 = 68
    62 + 82 = 100
    12 + 02 + 02 = 1
*/

/// Use a hash map (set) to record all numbers and check if we encounter a previous one (loop).
/// If found a "1" then is a happy number, otherwise not.
class Solution {
public:
    bool isHappy(int n) {
        if(n == 0) return false;
        if(n == 1) return true;
        unordered_set<int> dict;
        dict.insert(1);
        while(dict.count(n) == 0) {
            dict.insert(n);
            n = calc(n);
        }
        return n == 1;
    }
    
    int calc(int n) {
        int result = 0;
        while(n) {
            int r = n % 10;
            result += r*r;
            n /= 10;
        }
        return result;
    }
};

/**************************************************** 
 ***    200,Medium,Number of Islands 
 ****************************************************/

/*
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:

11110
11010
11000
00000

Answer: 1

Example 2:

11000
11000
00100
00011

Answer: 3
*/

//Solution 1: Standard DFS
// Note that we have to check 4 neighbors! Only checking right and bottom is not enough! See the case below:

// 1 1 1
// 0 1 0
// 1 1 1
// Starting from left top corner, if only checking 2 neighbors, we missed the bottom left one, and we end up count = 2.

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        int count = 0;
        for(int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(grid[i][j] == '1') {
                    dfs(grid, i, j);
                    count++;
                }
            }
        }
        return count;
    }
    void dfs(vector<vector<char> >& grid, int i, int j) {
        grid[i][j] = '0';
        //check 4 neighbors
        if(i > 0 && grid[i-1][j] == '1') dfs(grid, i-1, j); //top
        if(j > 0 && grid[i][j-1] == '1') dfs(grid, i, j-1); //left
        if(i < grid.size()-1    && grid[i+1][j] == '1') dfs(grid, i+1, j); //bottom
        if(j < grid[i].size()-1 && grid[i][j+1] == '1') dfs(grid, i, j+1); //right
    }
};

// Solution 2: BFS using a queue
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        int count = 0;
        for(int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(grid[i][j] == '1') {
                    bfs(grid, i, j);
                    count++;
                }
            }
        }
        return count;
    }
    void bfs(vector<vector<char> >& grid, int i, int j) {
        deque<pair<int, int> > q;
        q.push_back(make_pair(i, j)); 
        grid[i][j] = '0';
        while (!q.empty()) {
            int ni = q.front().first;
            int nj = q.front().second;
            q.pop_front();
            //check 4 neighbors
            if(ni > 0 && grid[ni-1][nj] == '1') { grid[ni-1][nj] = '0'; q.push_back(make_pair(ni-1, nj)); } //top
            if(nj > 0 && grid[ni][nj-1] == '1') { grid[ni][nj-1] = '0'; q.push_back(make_pair(ni, nj-1)); } //left
            if(ni < grid.size()-1    && grid[ni+1][nj] == '1') { grid[ni+1][nj] = '0'; q.push_back(make_pair(ni+1, nj)); } //bottom
            if(nj < grid[ni].size()-1 && grid[ni][nj+1] == '1') { grid[ni][nj+1] = '0'; q.push_back(make_pair(ni, nj+1)); } //right
        }
    }
};

// Solution 3: Union find.
// Record the total number of disjoint sets. m*n elements, initially all inactive. Scan the grid, when finding a '1', mark the element as active, and set its id and size attributes in UnionFind class. Maintain a conversion formula from 2D positions to 1D index (i*n+j).
// Use weighted union find with path compression, close to O(n) time complexity.
// Caveats:
// 1. 1D index is i*n+j, not i*m+j!
// 2. we need to check left and top neighbors, can skip bottom and right neighbors. Since we are scanning strictly top-down, left-right. 

class UnionFind {
public:
    UnionFind(int N) : n(0) {
        id.resize(N, -1);
        size.resize(N, 0);
    }
    //add element i as a new set
    void add(int i) {
        id[i] = i;
        size[i] = 1;
        n++;
    }
    //unite two elements
    void unite(int i, int j) {
        while(id[i] != i) { id[i] = id[id[i]]; i = id[i]; }
        while(id[j] != j) { id[j] = id[id[j]]; j = id[j]; }
        if(i != j) {
            if(size[i] < size[j]) { id[i] = j; size[j] += size[i]; }
            else { id[j] = i; size[i] += size[j]; }
            n--;
        }
    }

    int count() const { return n; }

private:
    vector<int> id; //set id
    vector<int> size; //size of each set
    int n; //total number of sets
};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        UnionFind uf(m*n);
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(grid[i][j] == '0') continue;
                int idx = i*n+j;
                uf.add(idx); //add to sets
                if(i > 0 && grid[i-1][j] == '1')  //top neighbor
                    uf.unite(idx, idx-n);
                if(j > 0 && grid[i][j-1] == '1') //left neighbor
                    uf.unite(idx, idx-1);
            }
        }
        return uf.count();        
    }
};


/**************************************************** 
 ***    191,Easy,Number of 1 Bits 
 ****************************************************/

/*
Write a function that takes an unsigned integer and returns the number of ’1' bits it has (also known as the Hamming weight).

For example, the 32-bit integer ’11' has binary representation 00000000000000000000000000001011, so the function should return 3.
*/

// Bit operation.
//    n    = 1010101000
//    n-1  = 1010100111
// n&(n-1) = 1010100000 (removed last 1 digit!)

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        while(n) {
            n = n & (n-1);
            count++;
        }
        return count;
    }
};

/**************************************************** 
 ***    188,Hard,Best Time to Buy and Sell Stock IV 
 ****************************************************/

/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/

/*
What is a transaction? Buy followed by sell. K transactions means a sequence of buy - sell - buy - sell - ... - buy - sell, where no two transations occur on the same date. If a sell and a buy fall on the same date, we can just merge them into one transaction.
So the key is to find non-overlapping intervals each of which has start and end corresponding to buy and sell dates.
Why non-overlapping? Because the problem requires sell before buy a new stock.
Profit is incurred only after selling a pre-purchased stock (e.g. at the end of opening interval)

Here is how to solve it with dynamic programming:
Let the max profit after day j, when performing up to kk transactions be maxProf[j][k]. It can be the maximum of the two scenarios:
1. No selling at day j, so we inherit the max profit after day j-1, maxProf[j-1][k]:
2. max profit after day jj when performing up to k-1 transactions, then buy stock at day jj, and sell at day j. The prior transactions can end at day jj, because in that case we can merge the sell/buy at jj, and instead sell at j, which in total is up to k-1 transactions, and thus also falls into the up to k transactions category. You can also make jj equal to j, and that is simply maxProf[j-1][k] (no transaction on day j). In this case, the max profit will be:
   max( maxProf[jj][k-1] + price[j] - price[jj] ) for all 0 <= jj <= j
 = price[j] + max (maxProf[jj][k-1] - price[jj]) for all 0 <= jj <= j

To avoid calculating the max for all jj's, we can keep a storage called tmpMax for the quantity max(maxProf[jj][k-1] - price[jj]) as j is incremented. So the DP relation can be expressed as:

maxProf[j][k] = max(maxProf[j-1][k], price[j] + tmpMax[j][k-1]),    j > 0 and k > 0
              = 0,   j = 0 or k = 0

tmpMax[j][k] = max(tmpMax[j-1][k], maxProf[j][k-1]-price[j]),  j > 0 and k > 0
             = max(tmpMax[j-1][k], -price[j]),    j > 0 and k = 0   // maxPro[0][-1] = 0
             = -price[0],   j = 0   // maxProf[0][k] = 0

We noticed that maxProf[0][k] and maxProf[j][0] are always zero, and tmpMax[0][k] = -price[0] for all k, so we can initialize the array and later do not iterate over j = 0 and k = 0.
*/

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        int result = 0;
        if(k >= n/2) {
            for(int i = 1; i < n; ++i) {
                result += max(0, prices[i] - prices[i-1]);
            }
            return result;
        }
        vector<vector<int> > maxProf(n, vector<int>(k+1, 0)); //maxProfit performing upto k transactions
        vector<vector<int> > tmpMax(n, vector<int>(k+1, 0)); //max of (maxProf[jj][k] - price[jj]) for all 0 <= jj <= j.

        for(int kk = 0; kk < k; ++kk) tmpMax[0][kk] = -prices[0];

        for(int j = 1; j < n; ++j) {
            tmpMax[j][0] = max(tmpMax[j-1][0], -prices[j]); //handle kk = 0 case
            for(int kk = 1; kk <= k; ++kk) {
                maxProf[j][kk] = max(maxProf[j-1][kk], prices[j] + tmpMax[j][kk-1]);
                tmpMax[j][kk] = max(tmpMax[j-1][kk], maxProf[j][kk]-prices[j]);
            }
        }
        return maxProf[n-1][k];
    }
};

/*
Space optimized solution: we noticed that maxProf[j][k] only requires values at j-1 and k-1, so we can replace the 2D array with 1D, by reducing the dimension for the day. We use the same array to track the maxProfit for kk transactions for the current day, and update it for the next day.
*/

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        int result = 0;
        if(k >= n/2) {
            for(int i = 1; i < n; ++i) {
                result += max(0, prices[i] - prices[i-1]);
            }
            return result;
        }
        vector<int> maxProf(k+1, 0); //maxProfit performing upto k transactions
        vector<int> tmpMax(k+1, -prices[0]); //max of (maxProf[jj][k] - price[jj]) for all 0 <= jj <= j.

        for(int j = 1; j < n; ++j) {
            tmpMax[0] = max(tmpMax[0], -prices[j]); //handle kk = 0 case
            for(int kk = 1; kk <= k; ++kk) {
                maxProf[kk] = max(maxProf[kk], prices[j] + tmpMax[kk-1]);
                tmpMax[kk] = max(tmpMax[kk], maxProf[kk]-prices[j]);
            }
        }
        return maxProf[k];
    }
}

/**************************************************** 
 ***    186,Medium,Reverse Words in a String II 
 ****************************************************/

/*
Given an input string, reverse the string word by word. A word is defined as a sequence of non-space characters.

The input string does not contain leading or trailing spaces and the words are always separated by a single space.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Could you do it in-place without allocating extra space?

Related problem: Rotate Array
*/

// Solution: first reverse the whole string, then scan left to right to reverse each individual words.
// Two pointers.

class Solution {
public:
    void reverseWords(string &s) {
        int n = s.size();
        if(n <= 1) return;
        reverse(s, 0, n);
        int i = 0, j = 0;
        for(int i = 0; i < n;) {
            j = i+1;
            while(j < n && s[j] != ' ') j++;
            reverse(s, i, j); //j points to space
            i = j+1;
        }
    }
    //reverse s[lo, hi)
    void reverse(string &s, int lo, int hi) {
        hi--;
        while(lo < hi) {
            char c = s[lo];
            s[lo] = s[hi];
            s[hi] = c;
            lo++; hi--;
        }
    }
};

/**************************************************** 
 ***    179,Medium,Largest Number 
 ****************************************************/

/*
Given a list of non negative integers, arrange them such that they form the largest number.

For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.

Note: The result may be very large, so you need to return a string instead of an integer.
*/

// Write a customized comparator function to compare two integer string, compare a+b v.s. b+a;
// An improved version from comparing integers, where we need to do int=>string conversions many times.
// Use a comparator class. can also define a bool compare function outside the class.

// Caveats:
// Corner case where nums are filled with "0"s, so we need to check if first character of result is zero.

class Solution {
public:
    struct myClass {
        bool operator() (const string& a, const string& b) {
            return a + b < b + a;
        }
    } compare;

    string largestNumber(vector<int>& nums) {
        string res;
        //assemble res from reverse iteration
        int n = nums.size();
        vector<string> strs(n);
        for(int i = 0; i < n; ++i)  strs[i] = num2str(nums[i]);

        sort(strs.begin(), strs.end(), compare);
        
        for(int i = n-1; i >= 0; --i) {
            res += strs[i];
        }
        if(res[0] == '0') return "0";
        else return res;
    }
    
    string num2str(int num) {
        if(num == 0) return "0";
        string res;
        while(num) {
            int d = num % 10;
            res = char(d + '0') + res;
            num /= 10;
        }
        return res;
    }
};

/**************************************************** 
 ***    174,Hard,Dungeon Game 
 ****************************************************/

/*
The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).

In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.

Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.

For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.
-2 (K) 	-3 	3
-5 	-10 	1
10 	30 	-5 (P)

Notes:

    The knight's health has no upper bound.
    Any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.
*/

/*
Standard dynamic programming. Start from end and scan backwards, calculate the minimum points required at each position.DP solution. Retrace back to top left.
As starting point, set the right and bottom neighbor of P's cell to 1.

  dp[i][j]  | dp[i][j+1]
  _ _ _ _ _ | _ _ _ _ _ _ 
            |
 dp[i+1][j] |  

dp[i][j] stores the minimum points required at position [i][j] in order to reach the princess. We can reach pos[i][j] in two ways, from position [i-1][j] and position [i][j-1], and we can go from the place requiring minimum points. The points required at dp[i-1][j] is simply dp[i][j] - dungeon[i][j], and at least 1, so we have:
dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1])-dungeon[i][j]).
At the boundary, i = m-1 or j = n-1, we replace min by only one of the two neighbors.
At the princess point, we have dp[m-1][n-1] = 1-dungeon[m-1][n-1].
We can use sentinel nodes at the boundary, where all the sentinel values are INT_MAX, but for dp[m-1][n-1] to fit in the formula, we can set dp[m][n-1] and dp[m-1][n] as 1.	

Another solution is to start scanning from top left, but we need to store to variables for each position: the maximum points required at start in order to reach here, and the remaining points at this position.
*/

class Solution {
public:
    int calculateMinimumHP(vector<vector<int> >& dungeon) {
        int m = dungeon.size(), n = dungeon[0].size();
        vector<vector<int> > minHP(m+1, vector<int>(n+1, INT_MAX));
        minHP[m-1][n] = minHP[m][n-1] = 1; //this is the trick!
        for (int i = m-1; i >= 0; i--) {
            for (int j = n-1; j >= 0; j--) {
                minHP[i][j] = max(1, min(minHP[i+1][j], minHP[i][j+1])-dungeon[i][j]);
            }
        }
        return minHP[0][0];
    }
};

/* Same idea as Solution 1 but space optimized */

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size(), n = dungeon[0].size();
        vector<int> dp(n, INT_MAX);
        dp[n-1] = max(1, 1-dungeon[m-1][n-1]);
        //for last row (i == m-1)
        for(int j = n-2; j >= 0; j--)
            dp[j] = max(1, dp[j+1]-dungeon[m-1][j]);

        for (int i = m-2; i >= 0; i--) {
            dp[n-1] = max(1, dp[n-1]-dungeon[i][n-1]);
            for (int j = n-2; j >= 0; j--) {
                dp[j] = max(1, min(dp[j], dp[j+1])-dungeon[i][j]);
            }
        }
        return dp[0];
    }
};



/**************************************************** 
 ***    173,Medium,Binary Search Tree Iterator 
 ****************************************************/

/*
Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree. 
*/

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */

// Push all left spline to a stack.
// When popping, it a node has right subtree, push all left spline of the right child.

class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        pushLeft(root, s);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !s.empty();
    }

    /** @return the next smallest number */
    int next() {
        TreeNode *node = s.back();
        int val = node->val;
        s.pop_back();
        if(node->right) pushLeft(node->right, s);
        return val;
    }
private:
    void pushLeft(TreeNode *root, deque<TreeNode*>& s) {
        while(root) {
            s.push_back(root);
            root = root->left;
        }
    }
    deque<TreeNode*> s; //stack
};


/**************************************************** 
 ***    171,Easy,Excel Sheet Column Number 
 ****************************************************/

/*
Related to question Excel Sheet Column Title

Given a column title as appear in an Excel sheet, return its corresponding column number.

For example:

    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28 
*/

// Iterative solution. Just 26-base counting.
// A-Z  : 1 - 26
//   AAA 
//   111 in 26-base counting

class Solution {
public:
    int titleToNumber(string s) {
        int v = 0;
        for(int i = 0; i < s.size(); ++i) {
            v = v*26+(s[i]-'A'+1);
        }
        return v;
    }
};

/**************************************************** 
 ***    170,Easy,Two Sum III - Data structure design 
 ****************************************************/

/*
Design and implement a TwoSum class. It should support the following operations: add and find.

add - Add the number to an internal data structure.
find - Find if there exists any pair of numbers which sum is equal to the value.

For example,

add(1); add(3); add(5);
find(4) -> true
find(7) -> false
*/

// Solution: use a lookup table to store the counts of each number (can handle duplicates). 
// add is O(1) amortized, just increment count in table
// find needs to traverse all entries in table. Handle two cases: number and residue are the same, and differerent.
// Slight optimization: only check half of cases (i >= j), avoid rechecking the same pair.

class TwoSum {

public:

  // Add the number to an internal data structure.
  void add(int number) {
    dict[number]++;
  }

  // Find if there exists any pair of numbers which sum is equal to the value.
  bool find(int value) {
    for(unordered_map<int, int>::iterator it = dict.begin(); it != dict.end(); ++it) {
      int i = it->first, j = value - i;
      if(j < i) continue;
      if((i == j && it->second > 1) || (i != j && dict.count(j))) return true;
    }
    return false;
  }

private:
  unordered_map<int, int> dict;
};


// Your TwoSum object will be instantiated and called as such:
// TwoSum twoSum;
// twoSum.add(number);
// twoSum.find(value);

/**************************************************** 
 ***    168,Easy,Excel Sheet Column Title 
 ****************************************************/

/*
Given a positive integer, return its corresponding column title as appear in an Excel sheet.

For example:

    1 -> A
    2 -> B
    3 -> C
    ...
    26 -> Z
    27 -> AA
    28 -> AB
*/

/*
Iterative solution. Radix-26 notation, can think of 0 as 0, and Z as A0.
remember to subtract 1.
 ABCD = 1*26^3 + 2*26^2 + 3*26 + 26, 
 ZZZZ = 26*26^3 + 26*26^2 + 26*26 + 26, 
The ZZZZ case, we can not just do / 26, because Z is just 26. But we can do -1, so to extract the last Z, we subtract one from the number, then the last number becomes 25, so when we do % 26, we end up wiht 25. Similarly, when we strip off the last Z, we can't just do / 26, since the last Z will give a 1, we can subtract one, and we are left with 26*26^2 + 26*26 + 26, which is just ZZZ.
*/

class Solution {
public:
    string convertToTitle(int n) {
        string ret;
        while(n) {
            int r = (n - 1) % 26; //r from 0 to 25
            ret = char('A'+r) + ret;
            n = (n - 1) / 26;
        }
        return ret;
    }
};

/**************************************************** 
 ***    167,Medium,Two Sum II - Input array is sorted 
 ****************************************************/

/*
Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2 
*/

// Solution: two pointers, linear search. Time O(n), space O(1).

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
      vector<int> ret(2, -1);
      int n = numbers.size();
      int i = 0, j = n-1;
      while(i < j) {
        int sum = numbers[i] + numbers[j];
        if(sum > target) j--;
        else if(sum < target) i++;
        else {
          ret[0] = i+1; ret[1] = j+1;
          return ret;
        }
      }
      return ret;
    }
};

/**************************************************** 
 ***    165,Easy,Compare Version Numbers 
 ****************************************************/

/*
Compare two version numbers version1 and version2.
If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.

You may assume that the version strings are non-empty and contain only digits and the . character.
The . character does not represent a decimal point and is used to separate number sequences.
For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.

Here is an example of version numbers ordering:

0.1 < 1.1 < 1.2 < 13.37
*/

// C++ version without using any system libraries (iterative solution).
// Use two pointers to scan two version numbers. Calculate integer value on the fly until encountering a '.' or end of string
// Caveats:
// 1.1 > 1 (longer one is larger), but 1.0 = 1. Need to extract the next number for empty strings, which is set as zero.

class Solution {
public:
    int compareVersion(string version1, string version2) {
        int m = version1.size();
        int n = version2.size();
        int i = 0, j = 0;
        while (i < m || j < n) {
            int num1 = 0, num2 = 0;
            while (i < m && version1[i] != '.') {
                num1 = num1*10 + (version1[i]-'0');
                i++;
            }
            while (j < n && version2[j] != '.') {
                num2 = num2*10 + (version2[j]-'0');
                j++;
            }
            if      (num1 > num2) return  1;
            else if (num1 < num2) return -1;
            i++; j++; //remember to increment i and j!
        }
        return 0; //equal
    }
};

// Another solution. Recursive.
class Solution {
public:
    int compareVersion(string version1, string version2) {
        return compareVersion(version1, version2, 0, 0);
    }
    int compareVersion(const string& version1, const string& version2, int i, int j) {
        if(i >= version1.size() && j >= version2.size()) return 0; //termination
        //now neither has reached end
        int v1 = 0, v2 = 0;
        while(i < version1.size() && version1[i] != '.') {
            v1 = v1*10 + (version1[i++] - '0');
        }
        while(j < version2.size() && version2[j] != '.') {
            v2 = v2*10 + (version2[j++] - '0');
        }
        if(v1 > v2) return 1;
        else if(v1 < v2) return -1;
        return compareVersion(version1, version2, i+1, j+1); //equal, compare next
    }
};


/**************************************************** 
 ***    164,Hard,Maximum Gap 
 ****************************************************/

/*
Given an unsorted array, find the maximum difference between the successive elements in its sorted form.

Try to solve it in linear time/space.

Return 0 if the array contains less than 2 elements.

You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.
*/

// Solution using bucket sort.
/*
1. first find the maximum and minimum of the array
2. partition the numbers into n-1 buckets, based on the position in the [min, max] interval. Also put min, max to the buckets
3. According to pigeon-hole, at least one bucket will be empty. And the maximum difference will be straddling across these empty regions (because the legnth is larger than bucket interval, and the difference within a bucket is smaller than bucket interval).
4. Scan all buckets, calculate the difference straddling across all empty buckets, and return the maximum among all of them.

The trick to put max and min to buckets is to avoid array index bound checks (i < 0, i > nb-1). This ensures that the first and last bucket is always filled.

Caveats:
a. max should be the last bucket, should avoid the integer out-of-bounds error.
b. number of buckets should be 1 less of total number of points, so if min/max are included, it should be n-1 !
c. there can be multiple empty buckets, and they can be continuous! So need to keep track of left-most boundary of the continuous empty bucket set.
d. integer/double conversion when doing integer division to find bucket lengths!
e. span / n-1 is wrong, should be span /(n-1)
*/

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if(n < 2) return 0;
        if(n == 2) return abs(nums[0] - nums[1]);
        int minimum = INT_MAX, maximum = INT_MIN;
        for(int i = 0; i < n; ++i) {
            if(nums[i] > maximum) maximum = nums[i];
            if(nums[i] < minimum) minimum = nums[i];
        }
        int span = maximum - minimum;
        if(span == 0) return 0;
        //put the left n numbers into n+1 buckets, tracking the minimum and maximum in each bucket
        int nb = n+1; 
        double bucket_len = double(span) / nb;
        vector<pair<int, int> > buckets(nb, make_pair(-1, -1));
        for(int i = 0; i < n; ++i) {
            int ib = (nums[i] - minimum) / bucket_len;
            //put maximum in last bucket
            if(ib == nb) ib = nb-1;
            if(buckets[ib].first == -1) buckets[ib].first = buckets[ib].second = nums[i];
            else {
                if(nums[i] < buckets[ib].first) buckets[ib].first = nums[i];
                if(nums[i] > buckets[ib].second) buckets[ib].second = nums[i];
            }
        }
        //now scan all buckets and find all empty ones
        int max_diff = INT_MIN, diff = 0;
        int left = -1, right = -1; //left and right boundary of empty space
        for(int ib = 0; ib < nb; ++ib) {
            if(buckets[ib].first == -1) { //can't be first or last bucket
                if(left == -1) left = buckets[ib-1].second;
                right = buckets[ib+1].first;
            } else { //calculate previous
                max_diff = max(max_diff, right - left);
                left = right = -1;
            }
        }
        return max_diff;
    }
};

/**************************************************** 
 ***    161,Medium,One Edit Distance 
 ****************************************************/

/*
Given two strings S and T, determine if they are both one edit distance apart.
*/

/*
one pass solution. Two pointers scanning two arrays.
For s[i] and t[j], If found equal, move forward,
if not equal, then the rest should be the same, three cases:
a) remove s[i] and the rest matches, so we just check isSame for s[i+1, m) and t[j, n). e.g.
   abc[de]   ab[de]
     i          j
b) insert t[j] and the rest matches, so we just check isSame for s[i, m) and t[j+1, n) e.g
   ab[efg]   abd[efg]
      i        j
c) replace s[i] with t[j] and the rest matches, so we just check isSame for s[i+1, m) and t[j+1, n) e.g.
   abe[fg]   abc[fg]
     i         j

Finally, if we break out of loop, which means everything seen so far is matched. We simply check if we still have one and only one unchecked character in either one of the two arrays.

*/

class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int m = s.size(), n = t.size();
        if(m - n < -1 || m -n > 1) return false;
        int i = 0, j = 0;
        while(i < m && j < n) {
            if(s[i] == t[j]) { i++; j++; }
            else return isSame(s, i+1, t, j) || isSame(s, i, t, j+1) || isSame(s, i+1, t, j+1);
        }
        return j == n-1 || i == m-1;
    }
    bool isSame(const string& s, int i, const string& t, int j) {
        int m = s.size(), n = t.size();
        while(i < m && j < n) {
            if(s[i] != t[j]) return false;
            i++; j++;
        }
        return i == m && j == n;
    }
};


/**************************************************** 
 ***    159,Hard,Longest Substring with At Most Two Distinct Characters 
 ****************************************************/

/*
Given a string, find the length of the longest substring T that contains at most 2 distinct characters.

For example, Given s = “eceba”,

T is "ece" which its length is 3. 
*/

// Solution: use a hash table to store the counts of each character, and record the starting index of substring. Do a one-time linear search.
// Also store the count of disctinct characters and update i properly (by checking individual count of each character)
// For each character, increment the individual counts. If newly added, increment count.
// When count > 2, remove leading characters in substring (increment istart), and decrement individual counts in table. If no such character
// occurs, decrement count.
// Since the input is a string, using index table instead of unordered_map leads to better performance.

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        vector<int> dict(256, 0);
        int n = s.size();
        int count = 0; //count of disctinct characters
        int istart = 0; //start of substring
        int max_len = 0; //max length of substring
        for(int i = 0; i < n; ++i) {
            dict[s[i]]++;
            if(dict[s[i]] == 1) count++; //new entry added
            while(count > 2) { //more than 2 disctinct characters, remove some characters in the front
                dict[s[istart]]--;
                if(dict[s[istart]] == 0) count--;
                istart++;
            }
            max_len = max(max_len, i-istart+1);
        }
        return max_len;
    }
};

// A faster version with shorter lines (but less readability)
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        vector<int> dict(256, 0);
        int n = s.size();
        int count = 0; //count of disctinct characters
        int istart = 0; //start of substring
        int max_len = 0; //max length of substring
        for(int i = 0; i < n; ++i) {
            if(++dict[s[i]] == 1) count++; //new entry added
            while(count > 2) { //more than 2 disctinct characters, remove some characters in the front
                if(--dict[s[istart++]] == 0) count--;
            }
            max_len = max(max_len, i-istart+1);
        }
        return max_len;
    }
};


/**************************************************** 
 ***    158,Hard,Read N Characters Given Read4 II - Call multiple times 
 ****************************************************/

/*
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function may be called multiple times. 
*/

// Forward declaration of the read4 API.
int read4(char *buf);

// Since read can be called multiple times, we need to store the characters read but not copied to buf in one read call. There are two changes to simple read function:
// 1. in the end any leftover characters are pushed to the queue
// 2. in the beginning check if queue has leftovers, if yes copy to buffer. Has to handle cases where n is small than the number of leftovers.

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int once = 0, total = 0;
        //if there is anything left in residue, pop out.
        while(!q.empty() && n > 0) {
            *(buf++) = q.front(); q.pop_front();
            total ++;
            n--;
        }
        if(n == 0) return total; //finished
        
        while(n >= 4) {
            once = read4(buf);
            total += once;
            buf += once;
            if(once < 4) return total; //reached end of file
            n -= once;
        }
        if(n > 0) {
            once = read4(buf);
            buf += min(once, n); //move buffer position
            total += min(once, n);
            int leftover = once - n;
            for(int i = 0; i < leftover; ++i) { //has residue, push to queue
                q.push_back(*(buf+i));
            }
        }
        return total;
    }
    
private:
    deque<char> q;
};

/**************************************************** 
 ***    157,Easy,Read N Characters Given Read4 
 ****************************************************/

/*
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function will only be called once for each test case. 
*/

// Forward declaration of the read4 API.
int read4(char *buf);

// Solution: keep track of current buffer write position, and total number of characters read so far. Also decrement n by the number of characters written.

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int once = 0, total = 0;
        while(n >= 4) {
            once = read4(buf);
            total += once; //increment character counter
            buf += once; //move buffer forward
            if(once < 4) return total; //reached end of file
            n -= 4; //for sure read-in 4 characters
        }
        //now n < 4
        if(n > 0) {
            once = read4(buf); //could read end of file
            total += min(once, n);
            buf += min(once, n);
        }
        return total;
    }
};

/**************************************************** 
 ***    154,Hard,Find Minimum in Rotated Sorted Array II 
 ****************************************************/

/*
    Follow up for "Find Minimum in Rotated Sorted Array":
    What if duplicates are allowed?

    Would this affect the run-time complexity? How and why?

Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

The array may contain duplicates.
*/

// General solution that also works for duplicated cases (see comments in problem 153)
// Compare mid with hi, when equals, hi-- (not lo++!)

class Solution {
public:
    int findMin(vector<int>& nums) {
        int lo = 0, hi = nums.size()-1;
        int mid = 0;
        //invariant: [lo, hi] contains minimum
        while(lo < hi) {
            mid = lo + (hi-lo)/2;
            if(nums[mid] < nums[hi]) hi = mid;
            else if(nums[mid] > nums[hi]) lo = mid+1;
            else hi--;
        }
        return nums[lo];
    }
};

/**************************************************** 
 ***    153,Medium,Find Minimum in Rotated Sorted Array 
 ****************************************************/

/*
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

You may assume no duplicate exists in the array.
*/

/*
General solution that also works for duplicated cases.
Binary search. The array can be broken into two parts, 
for example, [4 5 6 7 0 1 2], first part is 4-7, second part is 0-2. If array is unrotated, then only first part exists (corner case). 

There are three anchor points, lo, hi, and mid. Compare nums[mid] with nums[hi].
1. If nums[mid] < nums[hi], then we know for sure that minimum lies on or before mid, so hi = mid (we excluding nums[mid+1, hi]).
2. If nums[mid] > nums[hi], then we know for sure that mid is in first part of array, and array is rotated. This means that minimum lies between mid and hi, so lo = mid+1. Since nums[mid] > nums[hi], nums[mid] cannot be the minimum, so we can exlude it. 
3. If nums[mid] = nums[hi], we can't say where mid lies. It could be left or right. But we can safely exclude nums[hi], since it is a duplicated entry apart from nums[mid]. Thus we simply decrement hi. 
*/

class Solution {
public:
    int findMin(vector<int>& nums) {
        int lo = 0, hi = nums.size()-1;
        int mid = 0;
        //invariant: [lo, hi] contains minimum
        while(lo < hi) {
            mid = lo + (hi-lo)/2;
            if(nums[mid] < nums[hi]) hi = mid;
            else if(nums[mid] > nums[hi]) lo = mid+1;
            else hi--;
        }
        return nums[lo];
    }
};

/**************************************************** 
 ***    152,Medium,Maximum Product Subarray 
 ****************************************************/

/*
Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6. 
*/

// DP solution.
// Keep track of maximum (in terms of absolute value) positive and negative values (initially set as 0)
// Update the values based on the polarity of newly seen element. If max_pos_prod and max_neg_prod are 0, then they are considered uninitialized.
// Caveat: When updating max_pos and max_neg, need to use temporary variables
// Optimization: since we call nums[i] multiply times, save it into a variable x to avoid excessive array indexing cost.

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        int max_pos_prod = 0, max_neg_prod = 0, max_prod = INT_MIN;
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            if(x == 0) {
                max_prod = max(max_prod, 0);
                max_pos_prod = max_neg_prod = 0;
            } else if(x > 0) {
                max_pos_prod = (max_pos_prod > 0) ? max_pos_prod*x : x;
                max_neg_prod = (max_neg_prod < 0) ? max_neg_prod*x : 0;
            } else { //nums[i] < 0
                int tmp_pos = max_pos_prod, tmp_neg = max_neg_prod;
                max_pos_prod = (tmp_neg < 0) ? tmp_neg*x : 0;
                max_neg_prod = (tmp_pos > 0) ? tmp_pos*x : x;
            }
            if(max_pos_prod > 0 && max_prod < max_pos_prod) max_prod = max_pos_prod;
            if(max_neg_prod < 0 && max_prod < max_neg_prod) max_prod = max_neg_prod; //needed for n=1 case with one negative number (max_pos undefined)
        }
        return max_prod;
    }
};

// A slightly different solution, considering n=1 corner case explicitly (so that max_pos will always be valid)
// Corner case: when there is only one negative number, should return itself, not 0.

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0]; //corner case
        int max_pos(0), max_neg(0), max_prod(0);
        int tmp_pos(0), tmp_neg(0);
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            if(x == 0) tmp_pos = tmp_neg = 0;
            else if (x > 0) {
                tmp_pos = (max_pos > 0) ? max_pos*x : x;
                tmp_neg = (max_neg < 0) ? max_neg*x : 0;
            } else {  //x < 0
                tmp_pos = (max_neg < 0) ? max_neg*x : 0;
                tmp_neg = (max_pos > 0) ? max_pos*x : x;
            }
            max_pos = tmp_pos; max_neg = tmp_neg;
            max_prod = max(max_prod, max_pos);
        }
        return max_prod;
    }
};

/**************************************************** 
 ***    151,Medium,Reverse Words in a String 
 ****************************************************/

/*
Given an input string, reverse the string word by word.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Update (2015-02-12):
For C programmers: Try to solve it in-place in O(1) space.

click to show clarification.
Clarification:

    What constitutes a word?
    A sequence of non-space characters constitutes a word.
    Could the input string contain leading or trailing spaces?
    Yes. However, your reversed string should not contain leading or trailing spaces.
    How about multiple spaces between two words?
    Reduce them to a single space in the reversed string.
*/

// Solution 1: kinda in-place. Procedure:
// 1. remove extra spaces and store the shorted string to s[0, end)
// 2. reverse substring s[0, end)
// 3. reverse individual string in s[0, end)
// Two pointers

class Solution {
public:
    void reverseWords(string &s) {
        if(s.empty()) return;
        int n = s.size();
        //1. remove extra spaces
        //end: end of shorted string, scan j
        int i = 0, j = 0;
        int beg = 0, end = 0;
        while(beg < n && s[beg] == ' ') beg++; 
        //beg points to first non-space char or end
        end = 0; //copy string to start
        for(j = beg; j < n; j++) {
            if(s[j] == ' ') continue;
            else { //non-space character, copy
                if(j > beg && s[j-1] == ' ') s[end++] = ' '; //add space
                s[end++] = s[j];
            }
        }
        //2. reverse substr string s[0, end)
        reverse(s, 0, end);
        
        //3. reverse individual words for s[0, end)
        for(i = 0; i < end; i++) {
            if(s[i] == ' ') continue;
            j = i+1;
            while(j < end && s[j] != ' ') j++;
            reverse(s, i, j); //j points to space or s.end()
            i = j;
        }
        s = s.substr(0, end); //copy result to s (can handle end = 0 case)
    }

    //reverse s[lo, hi)
    void reverse(string &s, int lo, int hi) {
        hi--;
        while(lo < hi) {
            char c = s[lo];
            s[lo] = s[hi];
            s[hi] = c;
            lo++; hi--;
        }
    }
};

// Solution 2: Use an auxiliary string vector
// Caveat: size_t i = str.size()-1 is wrong! because it will fail when str is empty(), use int i instead.

class Solution {
public:
    void reverseWords(string &s) {
        vector<string> strs;
        split(s, strs);
        s.clear();
        for (int i = strs.size()-1; i >= 0; i--) {
            s += strs[i];
            if(i > 0) s += " ";
        }
    }
    void split(string& s, vector<string>& strs) {
        s += " ";
        string word;
        for(size_t i = 0; i < s.size(); ++i) {
            char c = s[i];
            if(c != ' ') word += c;
            else if(word != "") {
                strs.push_back(word);
                word = "";
            }
        }
    }
};

/**************************************************** 
 ***    149,Hard,Max Points on a Line 
 ****************************************************/

/*
Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
*/

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */

/// O(n2) solution with hash table.
/// Iterate all points. For each point i, check all points after it (excluding itself). There are three cases:
/// 1. duplicate point as i, track count as n_dup.
/// 2. lying along same vertical line as point i, track count as n_ver
/// 3. lying on a line of a finite slope. maintain a map of slope and count. Track the maximum of counts of all slopes as max_line.
/// After scanning all other points, we have num_dup, num_ver, and max_line. Then the maximum number of points lying across i is: 1 + num_dup + max(max_line, num_ver), where 1 counts point i itself.
/// repeat for all points and update
/// Caveat: when calculating the slope from integer coordinates, convert the numerator to double!

class Solution {
public:
    int maxPoints(vector<Point>& points) {
        int n = points.size();
        if(n <= 2) return n;
        int result = 0;
        unordered_map<double, int> dict;
        for(int i = 0; i < n-1; ++i) { //no need to scan last point
            int num_dup = 0, num_ver = 0, max_line = 0; //# duplicates, # points on same vertical line, max # points on any line
            dict.clear();
            //check all the points from i+1 to n
            for(int j = i+1; j < n; ++j) {
                if(points[j].x == points[i].x) {
                    if(points[j].y == points[i].y) num_dup++; //same point
                    else num_ver++; //on same vertical line
                } else { //calculate slope
                    double slope = double(points[j].y - points[i].y) / (points[j].x - points[i].x);
                    max_line = max(max_line, ++dict[slope]);
                }
            }
            result = max(result, 1 + num_dup + max(max_line, num_ver));
        }
        return result;
    }
};


/// O(n3) solution
/// Check each pair (pi, pj) and count all points lying on the line determined by pi, pj (using colinear function).
// If encountered duplicates, count them as well

class Solution {
public:
    int maxPoints(vector<Point>& points) {
        int n = points.size();
        if(n <= 2) return n;
        int result = 0;
        for(int i = 0; i < n-1; ++i) {
            int num_dup = 1, num_col = 0;
            for(int j = i+1; j < n; ++j) {
                if(points[i].x == points[j].x && points[i].y == points[j].y) {
                    num_dup++;
                    continue;
                }
                num_col = 1; //count point[j]
                for(int k = j+1; k < n; ++k) {
                    if(colinear(points[i], points[j], points[k])) num_col ++;
                }
                result = max(result, num_dup + num_col);
            }
            result = max(result, num_dup); //deal with case where only exist duplicates, no colinear execution
        }
        return result;
    }
    
    bool colinear(Point& p, Point& q, Point& r){
        return (q.y - p.y)*(r.x - q.x) - (r.y - q.y)*(q.x - p.x) == 0;
    }
};


/**************************************************** 
 ***    146,Hard,LRU Cache 
 ****************************************************/

/*
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item. 
*/

/*
 Use a double-linked list, and use a dummy head and tail.
 Maintain a count of elements and capiticy.
 When an element has been touched, move to end of list
 When inserting a new element, first check if reaching maximum capacity. If yes, first delete head element. Then append new element to tail.
 Also included proper delete functions when nodes are removed and in the destructor.
 Caveat:
  1. When using dummy head and tail, should create a new node, not doing this in the constructor:
   ListNode dum1(0), *head = &dum1
  It will cause failure in the set routine when head is referenced. This is because dum1 is a local variable in constructor, and outside this function it will be out-of-scope and later referencing will give segmentation fault error. The correct way is to use new to allocate space on the heap: ListNode *head = new ListNode(-1, 0);
  2. The ListNode should have two data entries, key and value. Value is obvious, key is also needed to find the entry in the map when the entry needs to be erased.
 
*/

class LRUCache{

public:
    struct ListNode {
        ListNode *prev, *next;
        int key, val;
        ListNode(int k, int v) : key(k), val(v), prev(NULL), next(NULL) {}
    };

    LRUCache(int capacity) {
        this->capacity = capacity;
        this->N = 0;
        //dummy head and tail
        head = new ListNode(-1, 0);
        tail = new ListNode(-1, 0);
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCache() {
        ListNode *node = head;
        while(node) {
            ListNode* tmp = node;
            node = node->next;
            delete tmp;
        }
    }

    int get(int key) {
        if(dict.count(key)) {
            ListNode* node = dict[key];
            removeFromList(node);
            appendToList(node);
            return node->val;
        } else return -1;       
    }
    
    void set(int key, int value) {
        if(dict.count(key)) { //found, just update
            ListNode* node = dict[key];
            node->val = value;
            removeFromList(node);
            appendToList(node);
        } else { //not found, insert
            ListNode *node = new ListNode(key, value);
            dict[key] = node;
            appendToList(node);
            N++;
            if(N > capacity) {
               node = head->next;
               removeFromList(node);
               dict.erase(node->key); //erase entry from map
               delete node;
               N--;
            }
        }
    }

private:
    void removeFromList(ListNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    void appendToList(ListNode* node) {
        node->prev = tail->prev;
        node->next = tail;
        tail->prev->next = node;
        tail->prev = node;
    }
    int capacity;
    int N;
    unordered_map<int, ListNode*> dict;
    ListNode *head, *tail;
};
    void appendToTail(ListNode* node) {
        node->prev = tail->prev;
        node->next = tail;
        node->prev->next = node;
        node->next->prev = node;
    }
    void deleteHead() {
        ListNode *tmp = head->next;
        st.erase(tmp->key);
        head->next = tmp->next;
        tmp->next->prev = head;
        delete tmp;
    }
};

/**************************************************** 
 ***    145,Hard,Binary Tree Postorder Traversal 
 ****************************************************/

/*
Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [3,2,1].

Note: Recursive solution is trivial, could you do it iteratively?
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution (easy).
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        postorder(root, ret);
        return ret;
    }
    void postorder(TreeNode *root, vector<int>& ret) {
        if(!root) return;
        postorder(root->left, ret);
        postorder(root->right, ret);
        ret.push_back(root->val);
    }
};

// Iterative solution using a stack (and a tag for each node tracking how many times it has been pushed_to stack.
// Use pair instead of struct for simplicity.
// Slightly improved version. Avoid frequent pop and push operations, instead just update(increment) top's tag value.
// Typically each node will be checked three times, each time the value associated with it will be incremented.
// 1. The 1st time it is checked, push left child to stack if any
// 2. The 2nd time it is checked, push right child to stack if any
// 3. The 3rd time it is checked, we are done with the sub-trees so we can save the node to output and pop it out.

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        deque<pair<TreeNode*, int> > st; //stack
        st.push_back(make_pair(root, 0));
        TreeNode* node;
        while(!st.empty()) {
            int tag = ++st.back().second;
            node = st.back().first;
            if(tag == 1) {
                if(node->left) st.push_back(make_pair(node->left, 0));
            } else if(tag == 2) {
                if(node->right) st.push_back(make_pair(node->right, 0));
            } else {
                result.push_back(node->val);
                st.pop_back();
            }
        }
        return result;
    }
};

// Iterative solution without tag in each node, instead use a pre pointer pointing to the previous node visited, by checking (1) whether previous node is the nodes left or right child, and (2) whether left or right child exist, we determine what we do next.
// There are three cases typically:
// 1. 1st time a node is checked, pre does not equal either children (if any).
// 2. 2nd time a node is checked, we just visited left sub-tree, so pre == node->left
// 3. 3rd time a node is checked, we just visited right sub-tree, so pre == node->rights
// There are also cases where left and/or right child is empty.
// If left child exists and pre is not equal to either children, then we push
// For correct comparison, pre should be initialized as not a NULL value, so we can initialize it as root.

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        deque<TreeNode*> st;
        st.push_back(root);
        TreeNode *pre = root, *node = NULL;
        while(!st.empty()) {
            node = st.back();
            if(node->left && node->left != pre && node->right != pre) {
                st.push_back(node->left);
            } else if(node->right && node->right != pre) {
                st.push_back(node->right);
            } else {
                result.push_back(node->val);
                pre = node;
                st.pop_back();
            }
        }
        return result;
    }
};



/**************************************************** 
 ***    144,Medium,Binary Tree Preorder Traversal 
 ****************************************************/

/*
Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [1,2,3].

Note: Recursive solution is trivial, could you do it iteratively?
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution (easy).

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        if(!root) return ret;
        preorder(root, ret);
        return ret;
    }
    void preorder(TreeNode *root, vector<int>& ret) {
        if(!root) return;
        ret.push_back(root->val);
        preorder(root->left, ret);
        preorder(root->right, ret);
    }
};

// Iterative solution using a stack

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        if(!root) return ret;
        deque<TreeNode*> s; //stack
        s.push_back(root);
        while(!s.empty()) {
            TreeNode *node = s.back(); s.pop_back();
            ret.push_back(node->val);
            if(node->right) s.push_back(node->right);
            if(node->left) s.push_back(node->left);
        }
        return ret;
    }
};

/**************************************************** 
 ***    140,Hard,Word Break II 
 ****************************************************/

/*
Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"]. 
*/

//DP solution: use an array to store whether substring s[i .. end) is breakable.
//Then do a DFS, when checking the conditions, first check if breakable (guaranteed O(1)), and then whether the substring s[i, i+len) is in dictionary (amortize O(1)). 

// Avoid TLE, if string is not breakable at all, return.
// Trick: in if condition, first check breakable, then check wordDict.count() will cause program to run slightly faster, because array look-up is faster than hash table lookup.

class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        vector<string> result;
        if(s.empty() || wordDict.empty()) return result;
        int n = s.size();
        vector<bool> breakable(n+1, false); //whether s[i, n) is breakable?
        breakable[n] = true; //empty string breakable
        for(int i = n-1; i >= 0; --i) {
            for(int len = 1; len <= n-i; ++len) {
                if(breakable[i+len] && wordDict.count(s.substr(i, len))) {
                    breakable[i] = true;
                    break;
                }
            }
        }
	//if string s not breakable, just return (avoid TLE)
        if(!breakable[0]) return result;
        
        string tmp;
        dfs(s, 0, breakable, wordDict, tmp, result);
        return result;
    }
    //check s[k .. end)
    void dfs(string& s, int k, vector<bool>& breakable, unordered_set<string>& wordDict, string tmp, vector<string>& result) {
        int n = s.size();
        if(k == n) {
            result.push_back(tmp);
            return;
        }
        //s's length i substring starting at k
        for(int i = 1; k+i <= n; ++i) {
            string sub = s.substr(k, i);
            if(breakable[k+i] && wordDict.count(sub)) {
                if(tmp == "") dfs(s, k+i, breakable, wordDict, sub, result);
                else dfs(s, k+i, breakable, wordDict, tmp + " " + sub, result);
            }
        }
    }
/*
    // An alternative dfs function passing reference of partial solution tmp. Remember its end position, append new strings, and erase them 
    // using C++'s erase() function.
    void dfs(string& s, int k, vector<bool>& breakable, unordered_set<string>& wordDict, string& tmp, vector<string>& result) {
        int n = s.size();
        if(k == n) {
            result.push_back(tmp);
            return;
        }
        //s's length i substring starting at k
        int j = tmp.size(); //remember tmp's end position
        for(int i = 1; k+i <= n; ++i) {
            string sub = s.substr(k, i);
            if(breakable[k+i] && wordDict.count(sub)) {
                if(tmp == "") tmp = sub;
                else tmp += " " + sub;
                dfs(s, k+i, breakable, wordDict, tmp, result);
                tmp.erase(j); //revert back to original
            }
        }
    }
*/
};
	
// Solution 2. Dynamic programming, but store all the possible breaking points of each substring s[i, n). Checking each substring is breakable simply reduces to checking whether the array for possible breaking points is empty. For string s[i, n), check if s[i, j) is in dictionary and s[j, n) is breakable by dynamic programming.

class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        vector<string> result;
        if(s.empty() || wordDict.empty()) return result;
        int n = s.size();
        vector<vector<int> > breakpos(n+1); //breaking position of s[i, n)
        for(int i = n-1; i >= 0; --i) {
            for(int len = 1; len <= n-i; ++len) {
                if((len == n-i || !breakpos[i+len].empty()) && wordDict.count(s.substr(i, len))) {
                    breakpos[i].push_back(i+len);
                }
            }
        }
        if(breakpos[0].empty()) return result;
        
        string tmp;
        dfs(s, 0, breakpos, tmp, result);
        return result;
    }
    //check s[k .. end)
    void dfs(string& s, int k, vector<vector<int>>& breakpos, string tmp, vector<string>& result) {
        int n = s.size();
        if(k == n) {
            result.push_back(tmp);
            return;
        }
        //s's length i substring starting at k
        for(int j = 0; j < breakpos[k].size(); ++j) {
            int pos = breakpos[k][j];
            if(tmp == "") dfs(s, pos, breakpos, s.substr(k, pos-k), result);
            else dfs(s, pos, breakpos, tmp + " " + s.substr(k, pos-k), result);
        }
    }
};

// Solution 3. Recursive solution with top-down memoization DP. Fastest (4ms) solution.
// Store the possible break solutions for a string in a map (memoization). First search result in map, if not there, do real business.
// To avoid TLE, first check if the word s is breakable or not by examining all its substrings starting at i (ends at s.end()) and see if any belongs to dictionary. If none is in dictionary, then there's no solution.
// If there is solution, then we systematically break the string into 2 parts,with the first part length varying from 1 to n-1. Each time if first part is in dictionary, recursively call wordBreak for second part, and construct the solution for s from the solution of second part.
// Finally, before return, do not forget to write the result to dp table.

class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        //first search in memoization table
        if(dp.count(s)) return dp[s];
        
        vector<string> result;
        int i = 0, n = s.size();
        for(i = 0; i < n; ++i) { //check if s[i, n) is in dict
            if(wordDict.count(s.substr(i))) break;
        }
        if(i == n) return result; //no solution
        
        //now search substrings
        if(wordDict.count(s)) result.push_back(s); //whole string is solution
        for(int len = 1; len < n; ++len) {
            string str = s.substr(0, len);
            if(wordDict.count(str)) {
                vector<string> tmp = wordBreak(s.substr(len), wordDict);
                for(auto it : tmp) {
                    result.push_back(str + " " + it);
                }
            }
        }
        dp[s] = result;
        return result;
    }
    unordered_map<string, vector<string> > dp; //memoization
};


/**************************************************** 
 ***    139,Medium,Word Break 
 ****************************************************/

/*
 Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code". 
*/

/// Dynamic programming, store whether s's length-i substring can be broken into an array. 
/// When found, just break;
/// Optimization: for j goes opposite direction to i, so that we encountered lastly found breakable item first.
/// 4ms.

class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        //if(s.empty()) return true;
        int n = s.size();
        vector<bool> breakable(n+1, false); //whether s[i, n) is breakable
        breakable[n] = true; //s[n, n) is defined to be true
        for(int i = n-1; i >= 0; --i) { //check s[i, n)
            for(int j = i+1; j <= n; ++j) { //check s[i, j) and s[j, n), j direction optimized so that we encountered lastly set breakable[j] first
                if(breakable[j] && wordDict.count(s.substr(i, j-i))) { 
                    breakable[i] = true; 
                    break; 
                }
            }
        }
        return breakable[0];        
    }
};

// Solution 2. Same solution as 1 except starting from beginning
class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n+1,false);
        dp[0]=true;
        for(int i=1; i<=n; i++)  {
            for(int j = i-1; j >= 0; j--) {
                if(dp[j] && wordDict.count(s.substr(j,i-j))) {
                    dp[i]=true;
                    break; //next i
                }
            }
        }
        return dp[n];
    }
};

// Solution 3. DP with memoization
class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        if(breakable.count(s)) return breakable[s];
        if(wordDict.count(s)) {
            breakable[s] = true; //memoization
            return true;
        }
        int n = s.size();
        for(int i = 1; i < n; ++i) {
            if(wordDict.count(s.substr(0, i)) && wordBreak(s.substr(i), wordDict)) {
                breakable[s] = true;
                return true;
            }
        }
        breakable[s] = false;
        return false;
    }
    unordered_map<string, bool> breakable;
};


/**************************************************** 
 ***    138,Hard,Copy List with Random Pointer 
 ****************************************************/

/*
A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list. 
*/

/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */

/// Solution 1: use a hash table storing mapping from old to new nodes. Two passes.
/// First copy the array label/next fields and use a look-up table to store the mapping between old node and new node
/// Then deal with random array. Go through the old array and use the mapped new node link as the random field of new array.

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(head == NULL) return head;
        RandomListNode *newhead = new RandomListNode(head->label);
        RandomListNode *p = head, *q = newhead;
        map<RandomListNode*, RandomListNode*> lookup;
        lookup[p] = q;
        while (p->next) {
            q->next = new RandomListNode(p->next->label);
            lookup[p->next] = q->next;
            p = p->next;
            q = q->next;
        }
        
        //now deal with the random pointer
        p = head;
        q = newhead;
        while(p) {
            q->random = lookup[p->random];
            p = p->next;
            q = q->next;
        }
        return newhead;
    }
};

/// Solution 2. still uses hash table, but one pass, deal with next and random pointers at the same time.

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(!head) return NULL;
        unordered_map<RandomListNode*, RandomListNode*> dict;
        RandomListNode* dummy = new RandomListNode(0);
        RandomListNode *p = head, *q = dummy;
        while(p) {
            if(dict.count(p) == 0) {
                q->next = dict[p] = new RandomListNode(p->label);
            } else q->next = dict[p];
            q = q->next;
            if(!p->random) q->random = NULL;
            else {
                if(dict.count(p->random) == 0) {
                    q->random = dict[p->random] = new RandomListNode(p->random->label);
                } else q->random = dict[p->random];
            }
            p = p->next; //move p to next
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};

/// Solution 3. Very elegant. 3 passes with O(1) space (no hash table). The trick is to insert new nodes right after old node. Set random pointer, and then extract new array from the combined list.

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(!head) return NULL;
        RandomListNode *p = head, *q = NULL;
        //First pass, for each old node insert a new node after p
        while(p) {
            RandomListNode* tmp = p->next;
            p->next = new RandomListNode(p->label);
            p->next->next = tmp;
            p = tmp;
        }
        //Second pass, set random pointer
        p = head;
        while(p) {
            if(!p->random) p->next->random = NULL;
            else p->next->random = p->random->next;
            p = p->next->next;
        }
        //Third pass, extract new list from the combined list
        p = head; q = p->next;
        head = q; //new head to be returned
        while(p) {
            p->next = q->next;
            if(q->next) q->next = q->next->next;
            p = p->next;
            q = q->next;
        }
        return head;
    }
};


/**************************************************** 
 ***    135,Hard,Candy 
 ****************************************************/

/*
There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

    Each child must have at least one candy.
    Children with a higher rating get more candies than their neighbors.

What is the minimum candies you must give? 
*/

/*
Solution 1. Two passes, once from left to right, once reverse. Keep an array storing current candies assigned to each kid. If see a higher rating than previous, assign 1 more candy compared to previous, otherwise assign 1.
*/

class Solution {
public:
    int candy(vector<int>& ratings) {
        if(ratings.empty()) return 0;
        int n = ratings.size();
        if(n == 1) return 1;
        vector<int> candies(n, 1);
        int tot = 0;
        for(int i = 1; i < n; ++i) {
            if(ratings[i] > ratings[i-1])  candies[i] = candies[i-1] + 1;
        }
        tot += candies[n-1];
        for(int i = n-2; i >= 0; --i) {
            if(ratings[i] > ratings[i+1])  candies[i] = max(candies[i], candies[i+1] + 1);
            tot += candies[i];
        }
        return tot;
    }
};

/*
Solution 2. O(n) one pass and O(1) space. Keep a variable curr for candies assigned to current kid. Three cases:
1. If new kid has higher rating, increment curr, and add it to total.
2. If equal rating, give only one candy and add it to total.
3. If smaller, then use another pointer j to scan forward and find the streak of descending ratings. Then start assigning candies 1, 2, ... starting from end of streak to i. Position i is special in that we might need to increment its current assigned value to satisfy the right side.
rating:    2 5 8 6 4 2 1 2
candy:    1 2 3 4 3 2 1 2  = > 1 2 5 4 3 2 1.
                     i          j-1  j
rating:    2 5 8 6 7 8
candy:    1 2 3 2 1 2   = > unchanged.
                     i    j-1  j
Two ways to sum up the candies in the descending streak, one is decrement curr and add it to total until curr == 0. The other is to use formula for sums : 1+2+...+n , the first one turns out to be faster in the test examples.
*/

class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if(n <= 1) return n;
        int curr = 1, total = 1; //one candy to first kid
        int i = 1, j = 0;
        while(i < n) {
            if(ratings[i] == ratings[i-1]) {
                curr = 1; total += curr; i++;
            } else if(ratings[i] > ratings[i-1]) {
                curr += 1; total += curr; i++;
            } else { //a[i] < a[i-1]
                j = i+1;
                while(j < n && ratings[j] < ratings[j-1]) j++;
                //descending streak from i-1 to j-1 (candies 1, 2, ..., j-i, max(j-i+1, a[i-1]))
                //i should be maximum of j-i and a[i]
                total += max(j-i+1 - curr, 0); //give extra candies to a[i-1] if necessary
                curr = j-i;
                while(curr > 0) total += curr--;
                //total += (j-i+1)*(j-i)/2;
                curr = 1;
                i = j;
            }
        }
        return total;
    }
};

/*
Solution 3. An old solution similar to Solution 2 but unecessarily uses a stack

The idea is as follows: assign as few candies as possible. First assign 1 candy to the first kid, 
then go through the kid one by one. If we encounter kids in increasing rating value, we simply 
increment the candy number for each kid and we are done. But if we encounter kids in decreasing 
rating value, we need to fix previous candy values to avoid zero or negative candies to the current kid. 
Thus I use a stack to keep track of the kids with decreasing ratings, so that we can give more candies 
to them when the 2nd requirement is violated. I use a subroutine clearStack to count the actual number 
of candies required for these kids. For each kid, there are three cases:

1. current kid has higher rating than previous kid: in this case, we assign one more candy to this kid. 
Also pop all previous kids out (and count candies for them), and push current kid's candy number
2. current kid has equal rating to previous kid: we just assign 1 candy to this kid. Use the same stack operation as 1.
3. current kid has less rating to previous kid: we also assign only 1 candy to this kid temporarily, 
and push it to stack (to be fixed later)
I also use a sentinel in the end of ratings to trigger clearStack at the last element.

Time O(n), space O(n)
*/

class Solution {
public:
    int candy(vector<int>& ratings) {
        ratings.insert(ratings.end(), INT_MAX); //sentinel
        int n = ratings.size();
        if(n <= 1) return n;
        int sum(0), curr(0);
        stack<int> s;
        s.push(1); //candy for first kid
        for(int k = 1; k < n; ++k) {
            if(ratings[k] >= ratings[k-1]) { //larger than previous
                if(ratings[k] == ratings[k-1]) curr = 1;
                else curr = s.top()+1;
                sum += clearStack(s); //count all previous
                s.push(curr); //push current candy number in stack (not count yet)
            } else { //smaller than previous
                s.push(1); //just give one candy to this kid, not count yet
            }
        }

        return sum;
    }
    
    int clearStack(stack<int>& s) {
        int sum = 0;
        int curr(0), last(0);
        while(!s.empty()) {
            int curr = s.top(); s.pop();
            if(curr <= last) curr = last+1;
            sum += curr;
            last = curr;
        }
        return sum;
    }
};


/**************************************************** 
 ***    134,Medium,Gas Station 
 ****************************************************/

/*
There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

Note:
The solution is guaranteed to be unique. 
*/

/*
Two pass DP solution using an auxiliary array to store minimum required gas from 0 to other sites. O(n) space.
To be able to complete circuit at a site i, we need to traverse i to 0, and then from 0 to i. The idea is to first figure out
the minimum amount of gas needed when traveling from site 0 to site i (required[i]). 
The second pass, we calculate the remaining gases traveling from site i to 0 (starting with an empty tank). We do it in reverse order.
If at a given site i the remaining gases are larger than the pre-calculated minimum aount of gas needed at that site, then we know for sure that we can complete the circuit at site i.
the net consumption of gas from site i-1 to i is: amount of gas available at site i-1 (gas[i-1]) - gas cost between i-1 and i (cost[i-1]) + leftovers in tank at site i-1 (leftover).
If the net consumption is positive, then the minimum required gas at site i-1 is enough. If it is negative, then we need additional gas to cover the cost from i-1 to i, thus: required[i] = required[i-1] + (net < 0 ? -net : 0);
Similarly, if the net consumption is positive, we have more leftovers, otherwise we have 0. thus: leftover = (net > 0 ? net : 0);
*/

class Solution {
    
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size(); //assume n >= 2
        vector<int> required(n, 0); //minimum required gas from 0 to i
        int leftover(0);  //leftover gas from 0 to i
        for(int i = 1; i < n; ++i) {
            int net = gas[i-1]-cost[i-1]+leftover;
            required[i] = required[i-1] + (net < 0 ? -net : 0);
            leftover = (net > 0 ? net : 0);
        }
        int remaining(0); //leftover from i to 0
        for(int i = n-1; i >= 0; --i) {
           remaining += (gas[i] - cost[i]);
           if(remaining >= required[i]) return i;
        }
        return -1;
    }
};

/*
O(1) space greedy solution. 2 passes.
Start from 0, move forward and record the lowest level in the tank (could be negative), and the associated site position. Say i, this means that, tank will reach lowest level after visiting site i, when reaching site i+1. 
If the lowest level is non-negative, then we can complete circuit at site 0. Just return 0.
Second pass starts form site i+1, and traverse to 0. Calculate the residue amount of gas after reaching 0. If the residue amount is larger than the deficit from 0 to i, then we can complete circle from site i+1.

Caveat:
min_pos+1 need to apply modulo N or not? Looks like not, since that corresponds to site 0, but we already identified site 0 with condition min_left >= 0.
*/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int leftover = 0, min_left = 0, min_pos = -1;
        for(int i = 0; i < gas.size(); ++i) {
            leftover += gas[i] - cost[i];
            if(leftover < min_left) {  min_left = leftover, min_pos = i; }
        }
        if(min_left >= 0) return 0;
        int residue = 0;
        for(int j = min_pos+1; j < gas.size(); ++j) {
            residue += gas[j] - cost[j];
        }
        if(residue + min_left >= 0) return min_pos+1;
        else return -1;
    }
};

/*
O(1) space greedy solution. Only 1 pass.
We can improve from the last solution by noting that we can calculate residue and leftover in the same loop. When we see a smaller tank level, we reset residue to zero. The calculation for residue is effectively the same as previous solution.
*/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int leftover = 0, min_left = 0, min_pos = -1, residue = 0;
        for(int i = 0; i < gas.size(); ++i) {
            int net = gas[i] - cost[i];
            leftover += net;
            residue += net;
            if(leftover < min_left) { 
                min_left = leftover;
                min_pos = i; 
                residue = 0;
            } 
        }
        if(residue + min_left >= 0) return (min_pos+1)%gas.size();
        else return -1;
    }
};


/**************************************************** 
 ***    132,Hard,Palindrome Partitioning II 
 ****************************************************/

/*
Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut. 
*/

// Dynamic programming. Store 1-d array indicating the min-cut for s[0, i) prefix. 
// Update the minCuts for substrings as we check the strings.
// j = 0 is needed in this case.

class Solution {
public:
    int minCut(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        vector<int> minCuts(n+1, INT_MAX); //min-cuts for s[0, i)
        minCuts[0] = -1; // define minCut for empty string as -1 for later convenience
        for (int i = 0; i < n; ++i) { //check if s[i] is part of a palindrome substring
            //could s[i] be in the middle of odd-length palindrome?
            for (int j = 0; i >= j && i+j < n && s[i-j] == s[i+j]; ++j) //j = 0 is needed to init minCuts[i+1]
                minCuts[i+j+1] = min(minCuts[i+j+1], minCuts[i-j]+1);
            //could s[i] be in the middle of even-length palindrome?
            for (int j = 0; i >= j && i+j+1 < n && s[i-j] == s[i+j+1]; ++j)
                minCuts[i+j+2] = min(minCuts[i+j+2], minCuts[i-j]+1);
        }
        return minCuts[n];
    }
};


/**************************************************** 
 ***    129,Medium,Sum Root to Leaf Numbers 
 ****************************************************/

/*
Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

    1
   / \
  2   3

The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25. 
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Post-order traversal using a stack.
// Keep a running partial sum, and when reaching a leaf, add the partial sum to total sum.
// First time visiting a node, add value to partial sum. When finished processing left and right subtrees, remove the value from partial sum.
// Caveats: avoid adding value to partial sum multiple times! Only do it when tag == 0.

class Solution {
public:
    int sumNumbers(TreeNode* root) {
        if(!root) return 0;
        int partial_sum(0), total_sum(0);
        deque<pair<TreeNode*, int> > s; //stack
        s.push_back(make_pair(root, 0));
        while(!s.empty()) {
            TreeNode *node = s.back().first;
            int tag = s.back().second;
            if(tag == 0) { //first-time, push left subtree to stack
                partial_sum = partial_sum*10 + node->val; //also calculate partial sum
                s.back().second++;
                if(node->left) s.push_back(make_pair(node->left, 0));
            } else if(tag == 1) { //second-time, push right subtree to stack
                s.back().second++;
                if(node->right) s.push_back(make_pair(node->right, 0));
            } else {  //third-time, process node
                if(!node->left && !node->right) total_sum += partial_sum;
                partial_sum /= 10; //revert to previous value without this node
                s.pop_back();
            }
        }
        return total_sum;
    }
};

// Another solution. Similar, but add pathSums when node has been added.
class Solution {
public:
    int sumNumbers(TreeNode* root) {
        if(!root) return 0;
        stack<pair<TreeNode*, int> > st;
        st.push(make_pair(root, 0));
        int sum = 0, pathSum = root->val;
        while(!st.empty()) {
            TreeNode* node = st.top().first;
            int tag = st.top().second;
            if(tag == 0) {
                st.top().second++;
                if(node->left) { 
                    st.push(make_pair(node->left, 0));
                    pathSum = pathSum*10 + node->left->val;
                }
            } else if(tag == 1) {
                st.top().second++;
                if(node->right) {
                    st.push(make_pair(node->right, 0));
                    pathSum = pathSum*10 + node->right->val;
                }
            } else {
                st.pop();
                if(!node->left && !node->right) sum += pathSum; //leaf node, add to sum
                pathSum /= 10;
            }
        }
        return sum;
    }
};


/**************************************************** 
 ***    128,Hard,Longest Consecutive Sequence 
 ****************************************************/

/*
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity. 
*/

/*
Solution 1. More elegant. Use a hash table for O(1) look-up of each number.
Then scan the array again. First check if element is in set, if not just continue (no need to search a previously erased element). For each entry, scan numbers to left and right to see if they are in the map, count total number of adjacent numbers. At the same time remove them to avoid future redundant search.
e.g. 0 1  3 4 5 6  8 9,
when 4 is found, scan and find 3 and 6, with count = 4, remove all elements from 3 to 6. so next time we see a 5, we won't count again.
*/

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> table;
        int n = nums.size();
        for(int i = 0; i < n; i++) {
            table.insert(nums[i]);
        }
        int max_count = 0;
        for (int i = 0; i < n; ++i) {
            int x = nums[i];
            if(table.count(x) == 0) continue;
            table.erase(x); //remove it
            int cnt = 1;
            while(table.count(--x)) { cnt++; table.erase(x); }
            x = nums[i];
            while(table.count(++x)) { cnt++; table.erase(x); }
            max_count = max(max_count, cnt);
        }
        return max_count;
    }
};

/*
Solution 2. use a map, storing the starting and ending position of each point.[ 2, 3, 4] : 2=>4, 4=>2, 3 does not matter.

For this to work under duplicated entries, we should not visit the same node again. Once it is in the map, do nothing. Otherwise it might mess up the result.

When inserting a new number, check its neighbors to see if there is any neighoring intervals. If there is an interval on the left, update the extreme points. Do the same for the right interval.
*/

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return n;
        int max_len = 0;
        unordered_map<int, int> dict;
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            int left = x, right = x;
            if(dict.count(x)) continue; //avoid revisiting
            dict[x] = x;
            if(dict.count(x-1)) {
               left = dict[x-1];
               dict[left] = x;
               dict[x] = left;
            }
            if(dict.count(x+1)) {
               right = dict[x+1];
               dict[left] = right;
               dict[right] = left;
            }
            max_len = max(right-left+1, max_len);
        }
        return max_len;
    }
};


/**************************************************** 
 ***    127,Medium,Word Ladder 
 ****************************************************/

/*
Given two words (beginWord and endWord), and a dictionary, find the length of shortest transformation sequence from beginWord to endWord, such that:

    Only one letter can be changed at a time
    Each intermediate word must exist in the dictionary

For example,

Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]

As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:

    Return 0 if there is no such transformation sequence.
    All words have the same length.
    All words contain only lowercase alphabetic characters.

*/

/* 
=== Solution 1 ===
One-way BFS from beinWord to endWord. Do not remove elements from the original dictionary! Rather create a new one (unvisited) and remove from it.
Systematically trying the new word by altering one character of the new word. Do not create a new string, rather change the character in-place and revert back to original afterwards.
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
       deque<pair<string, int> > q;
       unordered_set<string> unvisited = wordList;
       int wl = beginWord.size();

       q.push_back(make_pair(beginWord, 1));
       unvisited.erase(beginWord); //remove beginWord to unvisited
       unvisited.insert(endWord); //insert beginWord to unvisited
       while(!q.empty()) {
           string wd = q.front().first;
           int level = q.front().second;
           if(wd == endWord) return level;
           q.pop_front();
           for(int i = 0; i < wl; ++i) {
               char c = wd[i];
               for(char ch = 'a'; ch <= 'z'; ++ch) {
                   if(ch == c) continue;
                   wd[i] = ch;
                   if(unvisited.count(wd))  {
                       q.push_back(make_pair(wd, level+1));
                       unvisited.erase(wd);
                   }
               }
               wd[i] = c; //revert back
           }
       }

       return 0;
    }
};

/*
=== Solution 2 ===
BFS with two sets, one for current level, one for next level, and in the end of each iteration swap the two.
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
       vector<string> current, next;
       int level = 1;
       unordered_set<string> unvisited = wordList;
       int wl = beginWord.size();

       unvisited.erase(beginWord);
       unvisited.insert(endWord);

       current.push_back(beginWord);
       
       while(!current.empty()) {
           for(vector<string>::iterator it = current.begin(); it != current.end(); ++it) {
               string wd = *it;
               for(int i = 0; i < wl; ++i) {
                   char c = wd[i];
                   for(char ch = 'a'; ch <= 'z'; ++ch) {
                       if(ch == c) continue;
                       wd[i] = ch;
                       if(wd == endWord) return level+1;
                       if(unvisited.count(wd))  {
                           next.push_back(wd);
                           unvisited.erase(wd);
                       }
                   }
                   wd[i] = c; //revert back
               }
           }
           current.swap(next);
           next.clear();
           level++;
       }
       return 0;        
    }
};

/*
=== Solution 3 ===
Bi-directional BFS to reduce search space. Start from two ends (begin/end), and only do BFS from the side with smaller search space. 
When we find one string in the search front that belongs to the front of the other side, we have "connected" the two sides.
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
       unordered_set<string> beginSet, nextSet, endSet;
       unordered_set<string> unvisited = wordList;
       int wl = beginWord.size();

       unvisited.erase(beginWord);
       unvisited.erase(endWord);

       beginSet.insert(beginWord);
       endSet.insert(endWord);
       int level = 2;

       while(!beginSet.empty()) {
           //for(unordered_set<string>::iterator it = beginSet.begin(); it != beginSet.end(); ++it) {
           for(auto wd : beginSet) {
               for(int i = 0; i < wl; ++i) {
                   char c = wd[i];
                   for(char ch = 'a'; ch <= 'z'; ++ch) {
                       if(ch == c) continue;
                       wd[i] = ch;
                      if(endSet.count(wd)) return level;
                       if(unvisited.count(wd))  {
                           nextSet.insert(wd);
                           unvisited.erase(wd);
                       }
                   }
                   wd[i] = c; //revert back
               }
           }
           beginSet.swap(nextSet);
           nextSet.clear();
           level++;
           if(beginSet.size() > endSet.size()) beginSet.swap(endSet);
       }
       return 0;
    }
};

/*
=== Solution 4 ===
Bidirectional BFS, recursive solution (64ms!)
*/
class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        unordered_set<string> unvisited = wordList;
        unvisited.erase(beginWord);
        unvisited.erase(endWord);
        unordered_set<string> forwardSet, backwardSet;
        forwardSet.insert(beginWord);
        backwardSet.insert(endWord);
        return ladderLengthUtil(forwardSet, backwardSet, unvisited, 2);
    }
    int ladderLengthUtil(unordered_set<string>& forwardSet, unordered_set<string>& backwardSet, unordered_set<string>& unvisited, int level) {
        if(forwardSet.empty()) return 0;
        if(forwardSet.size() > backwardSet.size()) return ladderLengthUtil(backwardSet, forwardSet, unvisited, level);
        unordered_set<string> next;
        for(auto word : forwardSet) {
            //try all posssibilities
            for(auto it = word.begin(); it != word.end(); ++it) {
                char tmp = *it;
                for(*it = 'a'; *it != 'z'; ++(*it)) {
                    if(*it == tmp) continue;
                    if(backwardSet.count(word)) return level;
                    else if(unvisited.count(word)) { //not visited
                        unvisited.erase(word);
                        next.insert(word);
                    }
                }
                *it = tmp; //revert back
            }
        }
        return ladderLengthUtil(next, backwardSet, unvisited, level+1);
    }
};


/**************************************************** 
 ***    126,Hard,Word Ladder II 
 ****************************************************/

/*
Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:

    Only one letter can be changed at a time
    Each intermediate word must exist in the word list

For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Return

  [
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
  ]

Note:

    All words have the same length.
    All words contain only lowercase alphabetic characters.
*/

/*
https://leetcode.com/discuss/41689/88ms-accepted-solution-with-68ms-word-ladder-88ms-word-ladder

=== Solution 1 ===
Usual BFS, do not change wordList, rather create a new set (unvisited) and operate on it.
Create a predecessor subgraph of the BFS search (each node can have multiple parents, so use a vector for the parent field). The tree structure is stored in the map<string, vector<string> structure called predecessors.
After the map is built, traverse the map from end to begin and reconstruct the ladders. 
*/
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
        vector<vector<string> > result;
        int lword = beginWord.size();
        unordered_set<string> unvisited = wordList;
        unvisited.erase(beginWord);
        unvisited.insert(endWord);
        unordered_set<string> current, next;
        unordered_map<string, vector<string> > predecessors; //predecessor map
        current.insert(beginWord);
        while(!current.empty()) {
            for(auto wd : current) {
                if(wd == endWord) break; //finishes
                unvisited.erase(wd);
                for(int i = 0; i < lword; ++i) {
                    char tmp = wd[i];
                    for(char c = 'a'; c <= 'z'; ++c) {
                        if(c == tmp) continue;
                        wd[i] = c;
                        if(unvisited.count(wd) && current.count(wd) == 0) { //belongs to wordList, and unvisited
                            next.insert(wd);
                            string owd = wd;
                            owd[i] = tmp;
                            predecessors[wd].push_back(owd);
                        }
                    }
                    wd[i] = tmp;
                }
            }

            current.swap(next);
            next.clear();
        }

        //now we have predecessor map, we can build the result using dfs
        vector<string> path;
        dfs(endWord, beginWord, predecessors, path, result);
        return result;
    }
    
    void dfs(const string& word, const string& beginWord, unordered_map<string, vector<string> >& predecessors, vector<string>& path, vector<vector<string> >& result) {
        path.insert(path.begin(), word);
        if(word == beginWord) {
            result.push_back(path);
            path.erase(path.begin());
            return;
        }
        for(auto it : predecessors[word]) {
            dfs(it, beginWord, predecessors, path, result);
        }
        path.erase(path.begin());
    }
};

/*
=== Solution 2 ===
Two way BFS. Instead of storing predecessor, store children map (we can in principle store two predecessor maps for the two direction, but one is much simpler). Since we are going to have multiple predecessor or children, storing children map does not increase the memory usage. Also, children graph makes it easy to construct the ladder path (array push back instead of inserting to front).

Use a tag "found" to check if found. Only construct the ladder when found is set as true.

Use a tag "forward" to keep track of search direction (forwards or backwards)
*/

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
        vector<vector<string> > result;
        
        unordered_set<string> current, opposite, next;
        unordered_map<string, vector<string> > children; //children map
        unordered_set<string> unvisited = wordList;

        unvisited.erase(beginWord);
        unvisited.erase(endWord);

        current.insert(beginWord);
        opposite.insert(endWord);
        bool forward = true;
        bool found = false;

        while(!current.empty()) {
            for(auto word : current) unvisited.erase(word);
            for(auto word : current) {
                //unvisited.erase(word);
                string newWord = word;
                for(auto it = newWord.begin(); it != newWord.end(); ++it) {
                    char tmp = *it;
                    for(*it = 'a'; (*it) <= 'z'; ++(*it)) {
                        if(*it == tmp) continue;
                        if(opposite.count(newWord)) { //found word in opposite search front
                            found = true;
                            if(forward) children[word].push_back(newWord);
                            else children[newWord].push_back(word);
                        } else if(unvisited.count(newWord)/* && !current.count(newWord)*/) { //belongs to wordList, and unvisited
                            next.insert(newWord);
                            if(forward) children[word].push_back(newWord);
                            else children[newWord].push_back(word);
                        }
                    }
                    *it = tmp; //revert
                }
            }
            if(found) break;
            
            current.swap(next);
            next.clear();
            if(current.size() > opposite.size()) { 
                current.swap(opposite);
                forward = !forward;
            }
        }
        //only proceed when found
        if(found) {
            vector<string> path;
            dfs(beginWord, endWord, children, path, result);
        }
        return result;
    }

    void dfs(const string& beginWord, const string& endWord, unordered_map<string, vector<string> >& children, vector<string>& path, vector<vector<string> >& result) {
        path.push_back(beginWord);
        if(beginWord == endWord) {
           result.push_back(path);
           path.pop_back();
           return;
        }
        for(auto it : children[beginWord]) {
            dfs(it, endWord, children, path, result);
        }
        path.pop_back();
    }
};

/*
=== Solution 3 ===
Bi-directional BFS, use recursive to build children graph, rather than interative. 
*/

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
        vector<vector<string> > result;
        
        unordered_set<string> current, opposite;
        unordered_map<string, vector<string> > children; //children map
        unordered_set<string> unvisited = wordList;

        unvisited.erase(beginWord);
        unvisited.erase(endWord);

        current.insert(beginWord);
        opposite.insert(endWord);
        bool found = findLadders(current, opposite, unvisited, children, true);
        
        if(found) {
            vector<string> path;
            dfs(beginWord, endWord, children, path, result);
        }
        return result;
    }

    bool findLadders(unordered_set<string>& current, unordered_set<string>& opposite, unordered_set<string>& unvisited, unordered_map<string, vector<string> >& children, bool forward) {
        if(current.empty()) return false; 
        if(current.size() > opposite.size()) return findLadders(opposite, current, unvisited, children, !forward); //reverse direction
        unordered_set<string> next;
        bool found = false;
        for(auto word : current) unvisited.erase(word); //first erase all words in current from unvisited (avoid double searching)
        for(auto word : current) {
            string newWord = word;
            for(auto it = newWord.begin(); it != newWord.end(); ++it) {
                char tmp = *it;
                for(*it = 'a'; (*it) <= 'z'; ++(*it)) {
                    if(*it == tmp) continue;
                    if(opposite.count(newWord)) { //found word in opposite search front
                        found = true;
                        if(forward) children[word].push_back(newWord);
                        else children[newWord].push_back(word);
                    } else if(unvisited.count(newWord)) { //belongs to wordList, and unvisited
                        next.insert(newWord);
                        if(forward) children[word].push_back(newWord);
                        else children[newWord].push_back(word);
                    }
                }
                *it = tmp; //revert
            }
        }
        
        if(found) return true; //stop here
        else return findLadders(next, opposite, unvisited, children, forward);
    }

    void dfs(const string& beginWord, const string& endWord, unordered_map<string, vector<string> >& children, vector<string>& path, vector<vector<string> >& result) {
        path.push_back(beginWord);
        if(beginWord == endWord) {
           result.push_back(path);
           path.pop_back();
           return;
        }
        for(auto it : children[beginWord]) {
            dfs(it, endWord, children, path, result);
        }
        path.pop_back();
    }
};

/**************************************************** 
 ***    124,Hard,Binary Tree Maximum Path Sum 
 ****************************************************/

/*
Given a binary tree, find the maximum path sum.

The path may start and end at any node in the tree.

For example:
Given the below binary tree,

       1
      / \
     2   3

Return 6. 
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/*
Recursive solution. 
Maximum path sum of tree rooted at x is the maximum of three cases:
 1. maximum path sum of x's left subtree (not passing x), if x's left subtree exists
 2. maximum path sum of x's right subtree (not passing x), if x's right subtree exists
 3. maximum path crossing x (x->val + maximum path from x's left child to anywhere in x's left subtree + maximum path from x's right child to anywhere in x's right subtree)
Note that the node values can be negative, so in case 3, so, some sub-paths can be length 0 (e.g. in case 3)

Therefore, we store a maximum path sum for a path originating from the root, and ending at any nodes (including the root itself), as mfr (maximum from root). The function returns the maximum path sum of the tree and also sets the mfr value by the reference.
maxPathSum(root) =  maximum of :
1) maxPathSum(root->left) if left exists
2) maxPathSum(root->right) if right exits
3) root->val (has to include root) + max(0, mfr(root->left)) + max(0, mfr(root->right)). Because the mfr can be negative for a subtree, we should compare it with 0 before addition.
Finally, we need to update the mfr of the root, which is simply:
root->val + maximum of 0, mfr(root->left), andmfr(root->right).

We initialize all values as INT_MIN.
*/

class Solution {
public:

    int maxPathSum(TreeNode* root) {
        if(!root) return 0;
        int mfr = INT_MIN; //max from root
        return maxPathHelper(root, mfr);
    }
    int maxPathHelper(TreeNode* root, int& mfr) {
        int mfr_left = INT_MIN, mfr_right = INT_MIN;
        int mp_left = INT_MIN, mp_right = INT_MIN;
        if(root->left) mp_left = maxPathHelper(root->left, mfr_left);
        if(root->right) mp_right = maxPathHelper(root->right, mfr_right);
        mfr = root->val + max(max(mfr_left, mfr_right), 0);

        int maximum = root->val + max(0, mfr_left) + max(0, mfr_right);
        maximum = max(maximum, mp_left);
        maximum = max(maximum, mp_right);
        return maximum;
    }
};

/*
A simplified version. For each subtree only calculate the maximum path originating from root, but keep a global maxSum variable that calculates the maximum path sum for each subtree. Update the maxSum for each subtree.
*/

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        if(!root) return 0;
        int maxSum = INT_MIN;
        maxFromRoot(root, maxSum);
        return maxSum;
    }
    int maxFromRoot(TreeNode* root, int& maxSum) {
        if(!root) return INT_MIN;
        int left = max(maxFromRoot(root->left, maxSum), 0);
        int right = max(maxFromRoot(root->right, maxSum), 0);
        maxSum = max(maxSum, root->val + left + right); //update maxSum
        return root->val + max(left, right);
    }
};

/*
Can further simplify, and put maxSum as a class member.
*/

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        if(!root) return 0;
        maxFromRoot(root);
        return maxSum;
    }
    int maxFromRoot(TreeNode* root) {
        if(!root) return INT_MIN;
        int left = max(maxFromRoot(root->left), 0);
        int right = max(maxFromRoot(root->right), 0);
        maxSum = max(maxSum, root->val + left + right); //update maxSum
        return root->val + max(left, right);
    }
    int maxSum = INT_MIN;
};



/**************************************************** 
 ***    123,Hard,Best Time to Buy and Sell Stock III 
 ****************************************************/

/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/

/// Dynamic programmming solution that extends to general k cases.
class Solution {
public:
    int maxProfit(vector<int> &prices) {
		int n = prices.size();
		if(n <= 1) return 0;
		int numTrans = 2; //number of transactions
		//mp[k][j] is maximum prof at the end of day j after performing at most k transactions
		vector<vector<int> > mp(numTrans+1, vector<int>(n, 0)); 
		int maxAll = 0; //maximum of all posibilities
		//maxProf[k][j] is the maximum of two cases:
		// a. no selling at day j, so upto k transactions (including 1,2,...k) at end of day j-1: mp[k][j-1]
		// b. selling at day j: for some jj < j, perform upto k-1 transactions at jj, and buy at jj and sell at day j,
		// the profit is the maximum of mp[k-1][jj] + prices[j] - prices[jj] among all 0 <= jj < j. Thus:
		// mp[k][j] = max( mp[k][j-1], prices[j] + max(mp[k-1][jj]-prices[jj], for all jj < j) )
		// when we increase j, we keep a variable tmpMax storing the last term and update properly.
		// The clever part is to take prices[j] out of the maximum expression of jj.
		for(int k = 1; k <= numTrans; ++k) {
			int tmpMax = mp[k-1][0] - prices[0]; //k = 1, tmpMax = mp[k-1][0] - prices[0];
			for(int j = 1; j < n; ++j) {
				mp[k][j] = max(mp[k][j-1], tmpMax+prices[j]);
				tmpMax = max(tmpMax, mp[k-1][j]-prices[j]);
				maxAll = max(maxAll, mp[k][j]);
			}
		}
		return maxAll;
    }
};

/// Space optimized DP solution. Use only one array, and a temporary variable old to store value from last k

class Solution {
public:
    int maxProfit(vector<int> &prices) {
		int n = prices.size();
		if(n <= 1) return 0;
		int numTrans = 2; //number of transactions
		//mp[j] is maximum prof at the end of day j after performing at most k transactions
		vector<int> mp(n, 0); 
		int maxAll = 0; //maximum of all posibilities
		//maxProf[k][j] is the maximum of two cases:
		// a. no selling at day j, so upto k transactions (including 1,2,...k) at end of day j-1: mp[k][j-1]
		// b. selling at day j: for some jj < j, perform upto k-1 transactions at jj, and buy at jj and sell at day j,
		// the profit is the maximum of mp[k-1][jj] + prices[j] - prices[jj] among all 0 <= jj < j. Thus:
		// mp[k][j] = max( mp[k][j-1], prices[j] + max(mp[k-1][jj]-prices[jj], for all jj < j) )
		// when we increase j, we keep a variable tmpMax storing the last term and update properly.
		// The clever part is to take prices[j] out of the maximum expression of jj.
		
		for(int k = 1; k <= numTrans; ++k) {
			int tmpMax = mp[0] - prices[0]; //k = 1, tmpMax = mp[k-1][0] - prices[0];
			for(int j = 1; j < n; ++j) {
			    int old = mp[j]; //mp[k-1][j]
				mp[j] = max(mp[j-1], tmpMax+prices[j]);
				tmpMax = max(tmpMax, old-prices[j]);
				maxAll = max(maxAll, mp[j]);
			}
		}
		return maxAll;
    }
};


/**************************************************** 
 ***    122,Medium,Best Time to Buy and Sell Stock II 
 ****************************************************/

/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/

/// Allow infinte transitions. Very simple. Just add up all positive differences!

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int max_profit = 0;
        for (int i = 1; i < prices.size(); ++i) {
            int diff = prices[i] - prices[i-1];
            if (diff > 0) max_profit += diff;
        }
        return max_profit;
    }
};

/**************************************************** 
 ***    121,Medium,Best Time to Buy and Sell Stock 
 ****************************************************/

/*
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.
*/

/// Greedy one pass O(n) solution:

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        int max_so_far = 0, max_all = 0;
        for(int i = 1; i < n; ++i) {
            int change = prices[i] - prices[i-1];
            if(max_so_far <= 0) max_so_far = change;
            else max_so_far += change;
            max_so_far = max(0, max_so_far);
            max_all = max(max_so_far, max_all);
        }
        return max_all;
    }
};

/**************************************************** 
 ***    117,Hard,Populating Next Right Pointers in Each Node II 
 ****************************************************/

/*
Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

Note:

    You may only use constant extra space.

For example,
Given the following binary tree,

         1
       /  \
      2    3
     / \    \
    4   5    7

After calling your function, the tree should look like:

         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \    \
    4-> 5 -> 7 -> NULL
*/

/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */

// General solution that works for all kinds of trees
// Use a dummy head in current layer.
// Use last layer to help progress the current layer

// Solution 1. Use two dummy heads. Progress layer by layer. Use last layer to help traverse current layer. Remember to set the tail's next to NULL when finishing one layer.

class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        //two dummy heads
        TreeLinkNode* phead = new TreeLinkNode(0);
        TreeLinkNode* qhead = new TreeLinkNode(0);
        TreeLinkNode *p = phead, *q = qhead;
        phead->next = root; root->next = NULL;
        while(phead->next) {
            p = p->next;
            while(p && !p->left && !p->right)  p = p->next;
            if(!p) {
                q->next = NULL; //set tail pointer
                phead->next = qhead->next;
                p = phead;
                q = qhead;
                continue;
            }
            if(p->left) {
                q->next = p->left;
                q = q->next;
            }
            if(p->right) {
                q->next = p->right;
                q = q->next;
            }
        }
        delete phead, qhead;
    }
};

// Solution 2. An old solution with the same idea.

class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        TreeLinkNode dum1(0), *head(&dum1); //dummy head
        TreeLinkNode *last(root), *curr(NULL); //head of last row, and curr tail node
        while(last) {
            curr = head;
            while(last) {
                if(!last->left && !last->right) {
                    last = last->next;
                    continue;
                }
                curr->next = (last->left ? last->left : last->right);
                curr = curr->next;
                if(curr == last->left && last->right) {
                    curr->next = last->right;
                    curr = curr->next;
                }
                last = last->next;
            }
            last = head->next; //move to new row
            head->next = NULL; //reset to NULL!
        }
    }
};

/**************************************************** 
 ***    116,Medium,Populating Next Right Pointers in Each Node 
 ****************************************************/

/*
Given a binary tree

    struct TreeLinkNode {
      TreeLinkNode *left;
      TreeLinkNode *right;
      TreeLinkNode *next;
    }

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

    You may only use constant extra space.
    You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).

For example,
Given the following perfect binary tree,

         1
       /  \
      2    3
     / \  / \
    4  5  6  7

After calling your function, the tree should look like:

         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL
*/

/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */

// General solution that works for all kinds of trees
// Use a dummy head in current layer.
// Use last layer to help progress the current layer

// Solution 1. Use two dummy heads. Progress layer by layer. Use last layer to help traverse current layer. Remember to set the tail's next to NULL when finishing one layer.

class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        //two dummy heads
        TreeLinkNode* phead = new TreeLinkNode(0);
        TreeLinkNode* qhead = new TreeLinkNode(0);
        TreeLinkNode *p = phead, *q = qhead;
        phead->next = root; root->next = NULL;
        while(phead->next) {
            p = p->next;
            while(p && !p->left && !p->right)  p = p->next;
            if(!p) {
                q->next = NULL; //set tail pointer
                phead->next = qhead->next;
                p = phead;
                q = qhead;
                continue;
            }
            if(p->left) {
                q->next = p->left;
                q = q->next;
            }
            if(p->right) {
                q->next = p->right;
                q = q->next;
            }
        }
        delete phead, qhead;
    }
};

// Solution 2. An old solution with the same idea.

class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        TreeLinkNode dum1(0), *head(&dum1); //dummy head
        TreeLinkNode *last(root), *curr(NULL); //head of last row, and curr tail node
        while(last) {
            curr = head;
            while(last) {
                if(!last->left && !last->right) {
                    last = last->next;
                    continue;
                }
                curr->next = (last->left ? last->left : last->right);
                curr = curr->next;
                if(curr == last->left && last->right) {
                    curr->next = last->right;
                    curr = curr->next;
                }
                last = last->next;
            }
            last = head->next; //move to new row
            head->next = NULL; //reset to NULL!
        }
    }
};

/**************************************************** 
 ***    115,Hard,Distinct Subsequences 
 ****************************************************/

/*
Given a string S and a string T, count the number of distinct subsequences of T in S.

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3. 
*/

/*
dynamic programming with various possible optimizations

Let dp[i][j] denote number of distinct subsequencies for s[0, i), and t[0, j). Then the distinct subsequency can be constructed from two cases:
a) s[0, j-1) and t[0, j), or, removing s[i-1]
b) s[0, i-1) and t[0, j-1) and if s[i-1] == t[j-1].
Boundary case:
s[i][0] = 1 for all i >= 0, e.g. "" and "", or "ab" and "".
s[0][j] = 0 for all j > 0, e.g. "" and "abc"

1. Scan t as outer loop, use a 2D array. This is less efficient.
2. Scan t as outer loop, use a 1D array and a prev variable. need to properly update prev.

3. Scan s as outer loop, use a 2D array.
4. Scan s as outer loop, use two 1D arrays.
*/

/*
Solution 1. Scan t as outer loop, use a 2D array. This is less efficient.
*/

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = t.size(), n = s.size();
        //outer loop: t, inner loop s
        //dp[i][j]: num-distinct for s[0..j) and t[0..i)
        vector<vector<int> > dp(m+1, vector<int>(n+1, 0));
        for(int j = 0; j <= n; ++j) dp[0][j] = 1;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
               dp[i+1][j+1] = dp[i+1][j] + (t[i] == s[j] ? dp[i][j] : 0);
            }
        }
        return dp[m][n];
    }
};

/*
Solution 2. Scan t as outer loop, use a 1D array and a prev variable. need to properly update prev.
*/

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = t.size(), n = s.size();
        //dp[j] at step i: num-distinct for s[0..j) and t[0..i)
        vector<int> dp(n+1, 1);  //initially 1
        int prev = 0;
        for(int i = 0; i < m; ++i) {
            prev = dp[0];
            dp[0] = 0; //dp[0] means number for t and "", only when t == "", dp[0] = 1, otherwise dp[0] = 0
            for(int j = 0; j < n; ++j) {
               int tmp = dp[j+1];
               dp[j+1] = dp[j] + (t[i] == s[j] ? prev : 0);
               prev = tmp;
            }
        }
        return dp[n];
    }
};

/*
Solution 3. Scan s as outer loop, use a 2D array. can further optimized second loop as j <= min(i, n), but runtime does not get shorter.
*/

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        vector<vector<int> > dp(m+1, vector<int>(n+1, 0));
        dp[0][0] = 1;
        for(int i = 1; i <= m; ++i) {
            dp[i][0] = 1;
            for(int j = 1; j <= n; ++j) {
                dp[i][j] = dp[i-1][j] + (s[i-1] == t[j-1] ? dp[i-1][j-1] : 0);
            }
        }
        return dp[m][n];
    }
};

/*
Solution 4. Scan s as outer loop, use two 1D arrays.
*/

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        vector<int> dp(n+1, 0), newdp(n+1, 0);
        dp[0] = newdp[0] = 1; //entry 0 is always 1  
        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j <= n; ++j) {
                newdp[j] = dp[j] + (s[i-1] == t[j-1] ? dp[j-1] : 0);
            }
            dp.swap(newdp);
        }
        return dp[n];
    }
};


/**************************************************** 
 ***    113,Medium,Path Sum II 
 ****************************************************/

/*
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
For example:
Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1

return

[
   [5,4,11,2],
   [5,8,4,5]
]
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// DFS backtracking. Recursive solution.
// Caveats: when reaching leaf, compare sum with x, not with zero!

class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int> > result;
        if(!root) return result;
        vector<int> path;
        dfs(root, sum, path, result);
        return result;
    }
    void dfs(TreeNode* root, int sum, vector<int>& path, vector<vector<int> >& result) {
        int x = root->val;
        path.push_back(x);
        //reaching leaf
        if(!root->left && !root->right && sum == x) result.push_back(path);
        if(root->left) dfs(root->left, sum-x, path, result);
        if(root->right) dfs(root->right, sum-x, path, result);
        path.pop_back();
    }
};

/**************************************************** 
 ***    112,Easy,Path Sum 
 ****************************************************/

/*
Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.
For example:
Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1

return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Caveats: 
// 1. empty root should return false.
// 2. leaf node mean node with NO children
// Several cases:
// 1. If reaching an leaf node, check if it's value is equal to sum
// 2. If an internal node, then check left or right subtree
// 3. if root is empty return false

class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;
        if(!root->left && !root->right) return (sum == root->val);
        sum -= root->val;
        return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);
    }
};

//Solution 2.
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;
        return dfs(root, sum);
    }
    bool dfs(TreeNode* root, int sum) {
        int x = root->val;
        //reaching leaf
        if(!root->left && !root->right && sum == x) return true;
        if(root->left && dfs(root->left, sum-x)) return true;
        if(root->right && dfs(root->right, sum-x)) return true;
        return false;
    }
};


/**************************************************** 
 ***    111,Easy,Minimum Depth of Binary Tree 
 ****************************************************/

/*
Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Caveat: This is different from the maxDepth problem!. There are several cases:
// 1. single node (no left or right children): minD = 1;
// 2. only left child: minD = 1 + minD of left
// 3. only right child: minD = 1 + minD of right
// 4. both childs: mindepth = 1 + min(minD of left, minD of right)
// The reason for the difference is that if a node has one empty subtree, and the other is not empty, the empty subtree does not count as the mininum depth path.

class Solution {
public:
    int minDepth(TreeNode* root) {
        if(!root) return 0;
        int minD = 0;
        if(!root->left)  minD = minDepth(root->right);
        else if(!root->right) minD = minDepth(root->left);
        else minD = min(minDepth(root->left), minDepth(root->right));
        return minD+1;
    }
};

// An alternative solution
class Solution {
public:
    int minDepth(TreeNode* root) {
        if(!root) return 0;
        if((root->left == NULL) ^ (root->right == NULL))  //only one subtree is not null
            return root->left ? minDepth(root->left)+1 : minDepth(root->right)+1;
        else //either both are null, or none are null
            return minD = min(minDepth(root->left), minDepth(root->right)) + 1;
    }
};

// The following solution is WRONG!
class Solution {
public:
    int minDepth(TreeNode* root) { //wrong solution. fails when left is NULL, and right is not
        if(!root) return 0;
        int d = 1;
        if(root->left) d = minDepth(root->left) + 1;
        if(root->right) d = min(d, minDepth(root->right)+1);
        return d;
    }
};



/**************************************************** 
 ***    110,Easy,Balanced Binary Tree 
 ****************************************************/

/*
Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1. 
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution. A tree is balanced iff:
// 1. left and right subtree are both balanced
// 2. depth of left and right subtree differ by at most 1

// Use a recursive function to return whether the tree is balanced, and at the same time set the height of the tree to a reference variable

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        int h = 0;
        return isBalanced(root, h);
    }

    bool isBalanced(TreeNode* root, int& h) {
        if(!root) { h = 0; return true; }
        int hl = 0, hr = 0;
        if(!isBalanced(root->left, hl) || !isBalanced(root->right, hr) || abs(hl-hr) > 1) return false;
        h = max(hl, hr) + 1;
        return true;
    }
};

// Solution 2. One recursive function calculating tree depth and balanced information at the same time! No reference passing needed!
// Use a trick, the height returned has two meanings:
// If 0, means tree is not balanced
// If > 0, means the height of tree + 1. So empty node will return 1.

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return depth(root);
    }
    int depth(TreeNode* root) {
        if(!root) return 1;
        int hl = depth(root->left);
        int hr = depth(root->right);
        if(hl == 0 || hr == 0 || abs(hl - hr) > 1) return 0;
        return max(hl, hr)+1;
    }
};



/**************************************************** 
 ***    107,Easy,Binary Tree Level Order Traversal II 
 ****************************************************/

/*
Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree {3,9,20,#,#,15,7},

    3
   / \
  9  20
    /  \
   15   7

return its bottom-up level order traversal as:

[
  [15,7],
  [9,20],
  [3]
]
*/

// Classical solution using BFS. Reverse result vector in the end.
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    struct Element {
        TreeNode *node;
        int level;
        Element(TreeNode *n, int l) : node(n), level(l) {}
    };
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int> > ret;
        if(!root) return ret;
        deque<Element> q; //queue
        q.push_back(Element(root, 0));
        while(!q.empty()) {
            TreeNode *node = q.front().node;
            int level = q.front().level;
            q.pop_front();
            if(level == ret.size()) ret.push_back(vector<int>());
            ret[level].push_back(node->val);
            if(node->left) q.push_back(Element(node->left, level+1));
            if(node->right) q.push_back(Element(node->right, level+1));
        }
        reverse(ret.begin(), ret.end()); //reverse result
        return ret;
    }
};


/**************************************************** 
 ***    104,Easy,Maximum Depth of Binary Tree 
 ****************************************************/

/*
Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution. Easy.

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};

/**************************************************** 
 ***    103,Medium,Binary Tree Zigzag Level Order Traversal 
 ****************************************************/

/*
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree {3,9,20,#,#,15,7},

    3
   / \
  9  20
    /  \
   15   7

return its level order traversal as:

[
  [3],
  [9,20],
  [15,7]
]
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Be careful when using bit operator!! if(level & 1 == 0) is wrong!, 1 == 0 has higher priority, should use if (!(level&1)).

/// Using two stacks. Swap the two when exhausting one level. Use a level tag to track polarity, which determines whether left or right subtree gets pushed to stack first
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int> > ret;
        if(!root) return ret;
        deque<TreeNode*> current, next;
        int level = 0;
        current.push_back(root);
        ret.push_back(vector<int>());
        while(!current.empty() || !next.empty()) { //break when both current and next are empty
            if(current.empty()) { // when exhausing current level ...
                current.swap(next); //swap current and next
                ret.push_back(vector<int>());
                level ++;
            }
            TreeNode *node = current.back();  current.pop_back();
            if(level % 2 == 0) {
                if(node->left) next.push_back(node->left);
                if(node->right) next.push_back(node->right);
            } else {
                if(node->right) next.push_back(node->right);
                if(node->left) next.push_back(node->left);
            }
            ret[level].push_back(node->val);
        }
        return ret;
    }
};

// Solution with 2 stacks, and two loops
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int> > result;
        if(!root) return result;
        //stack for two levels
        vector<TreeNode*> current, next;
        int level = 0; //level and parity
        current.push_back(root);
        while(!current.empty()) {
            result.push_back(vector<int>()); //new level
            //user current as stack
            for(vector<TreeNode*>::reverse_iterator it = current.rbegin(); it != current.rend(); ++it) {
                TreeNode *node = *it;
                if(level % 2 == 0) { //l=>r
                    if(node->left) next.push_back(node->left);
                    if(node->right) next.push_back(node->right);
                } else {
                    if(node->right) next.push_back(node->right);
                    if(node->left) next.push_back(node->left);
                }
                //insert to result
                result[level].push_back(node->val);
            }
            current.swap(next);
            next.clear();
            level++;
        }
        return result;
    }
};

// An old solution using struct instead of pair
/// Using a queue, after constructed, reverse odd level elements's order

class Solution {
public:
    struct Element {
        TreeNode *node;
        int level;
        Element(TreeNode *n, int l) : node(n), level(l) {}
    };
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int> > ret;
        if(!root) return ret;
        deque<Element> q; //queue
        q.push_back(Element(root, 0));
        while(!q.empty()) {
            TreeNode *node = q.front().node;
            int level = q.front().level;
            q.pop_front();
            if(level == ret.size()) ret.push_back(vector<int>());
            ret[level].push_back(node->val);
            if(node->left) q.push_back(Element(node->left, level+1));
            if(node->right) q.push_back(Element(node->right, level+1));
        }
        for(size_t i = 1; i < ret.size(); i += 2) {
            reverse(ret[i].begin(), ret[i].end());
        }
        return ret;
    }
};

/**************************************************** 
 ***    102,Easy,Binary Tree Level Order Traversal 
 ****************************************************/

/*
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree {3,9,20,#,#,15,7},

    3
   / \
  9  20
    /  \
   15   7

return its level order traversal as:

[
  [3],
  [9,20],
  [15,7]
]
*/

/// Classical solution using a queue

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Solution using one queue and a customized struct Element

class Solution {
public:
    struct Element {
        TreeNode *node;
        int level;
        Element(TreeNode *n, int l) : node(n), level(l) {}
    };
    
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > ret;
        if(!root) return ret;
        deque<Element> q; //queue
        q.push_back(Element(root, 0));
        while(!q.empty()) {
            TreeNode *node = q.front().node;
            int level = q.front().level;
            q.pop_front();
            if(level == ret.size()) ret.push_back(vector<int>());
            ret[level].push_back(node->val);
            if(node->left) q.push_back(Element(node->left, level+1));
            if(node->right) q.push_back(Element(node->right, level+1));
        }
        return ret;
    }
};

// Solution using one queue and std::pair (4ms)
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > result;
        if(!root) return result;
        deque<pair<TreeNode*, int> > q; //include level
        q.push_back(make_pair(root, 0));
        int currLevel = -1;
        while(!q.empty()) {
            TreeNode *node = q.front().first;
            int level = q.front().second;
            q.pop_front();
            if(level > currLevel) { 
                result.push_back(vector<int>());  //start a new level
                currLevel = level;
            }
            if(node->left) q.push_back(make_pair(node->left, level+1));
            if(node->right) q.push_back(make_pair(node->right, level+1));
            result[currLevel].push_back(node->val);
        }
        return result;
    }
};

// Solution using 2 vectors (queues), one for current level and one for next level (8ms)
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > result;
        if(!root) return result;
        vector<TreeNode*> current, next;
        current.push_back(root);
        while(!current.empty()) {
            result.push_back(vector<int>()); //start a new level (for current)
            for(auto node : current) {
                if(node->left) next.push_back(node->left);
                if(node->right) next.push_back(node->right);
                result.back().push_back(node->val); //push value to result
            }
            current.swap(next);
            next.clear();
        }
        return result;
    }
};

// Recursive solution:
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > result;
        if(!root) return result;
        vector<TreeNode*> current;
        current.push_back(root);
        int level = 0;
        levelOrder(current, result, level);
        return result;
    }
    void levelOrder(vector<TreeNode*>& current, vector<vector<int> >& result, int level) {
        if(current.empty()) return;
        result.push_back(vector<int>());
        vector<TreeNode*> next;
        for(auto it : current) {
            if(it->left) next.push_back(it->left);
            if(it->right) next.push_back(it->right);
            result[level].push_back(it->val);
        }
        levelOrder(next, result, level+1);
    }
};


/**************************************************** 
 ***    101,Easy,Symmetric Tree 
 ****************************************************/

/*
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3

But the following is not:

    1
   / \
  2   2
   \   \
   3    3
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution. check if the left and right subtrees are symmetric or not
// Two non-empty trees are symmetric iff:
// 1. root1->val = root2->val &&
// 2. 1's left is symmetric to 2's right &&
// 3. 2's left is symmetric to 1's right

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(root == NULL) return true;
        return isSymmetric(root->left, root->right);
    }
    
    bool isSymmetric(TreeNode* left, TreeNode *right) {
        if(left == NULL) return right == NULL;
        if(right == NULL) return false;
        return p->val == q->val && isSymmetric(p->left, q->right) && isSymmetric(p->right, q->left);
    }
};


/**************************************************** 
 ***    100,Easy,Same Tree 
 ****************************************************/

/*
Given two binary trees, write a function to check if they are equal or not.

Two binary trees are considered equal if they are structurally identical and the nodes have the same value. 
*/

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Do it recursively.
// Caveats: remember to compare the values of the two nodes!

class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if((p == NULL) ^ (q == NULL)) return false; //one null, the other not
        if(p == NULL) return true; //both are null
        //both are not null 
        return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

//alternative solution
class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if(p == NULL) return q == NULL;
        if(q == NULL) return false;
        //both are not null 
        return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};


/**************************************************** 
 ***    099,Hard,Recover Binary Search Tree 
 ****************************************************/

/*
Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.
Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution? 

*/
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/*
Solution 1. Using morris traversal. Morris traversal (alternative while loop where visit only appears once)

When finding swapped elements, can optimize and use :

if(!n1) n1 = prev;
n2 = node;

 1   3   2   4   5
      3>2: n1 = 3, n2 = 2;
 1   4   3   2   5
      4>3 3>2: n1 = 4, n2 = 2;
swap values of two nodes, not nodes themselves

*/

class Solution {
public:
   void recoverTree(TreeNode* root) {
        if(!root) return;
        TreeNode *node = root, *prev = NULL;
        TreeNode *n1(NULL), *n2(NULL); //node to be swapped
        //now starts morris traversal
        while(node) {
            if(node->left) {  // has left subtree
                TreeNode *child = node->left;
                while(child->right != NULL && child->right != node) child = child->right;
                //reached right most child of left subtree
                if(child->right == NULL) { //first time
                    child->right = node;
                    node = node->left;
                    continue;
                } else { //second time
                   child->right = NULL; //second time
                }
            }
            //visit node, then move to right
            if(prev && prev->val > node->val) {
                if(!n1) n1 = prev;
                n2 = node;
            }
            prev = node;
            node = node->right;
        }
        if(n1 && n2) {
            int t = n1->val;
            n1->val = n2->val;
            n2->val = t;
        }
   }
};

/*
Another solution using inorder traversal without vector<>. Just store prev at last step and compare with node->val at current step.
O(lg n) space for the stack space of recursive calls.
*/

class Solution {
public:
    void recoverTree(TreeNode* root) {
        if(!root) return;
        inorder(root);
        int t = n1->val;
        n1->val = n2->val;
        n2->val = t;
    }
    void inorder(TreeNode *node) {
        if(!node) return;
        inorder(node->left);
        //visit node
        if(prev && prev->val > node->val) {
           if(!n1) n1 = prev;
           n2 = node;
        }
        prev = node;
        inorder(node->right);
    }
    TreeNode *n1 = NULL, *n2 = NULL, *prev = NULL;
};

/*
The worst solution is to use a 1D array to store the inorder results. O(n) space.
*/

class Solution {
public:
   void recoverTree(TreeNode* root) {
        if(!root) return;
        vector<TreeNode*> nodes;
        inorder(root, nodes);
        TreeNode *n1(NULL), *n2(NULL);
        for (size_t i = 0; i < nodes.size()-1; ++i) {
            if(nodes[i]->val > nodes[i+1]->val) {
                if(!n1) n1 = nodes[i];
                n2 = nodes[i+1];
            }
        }
        if(n1 && n2) {
            int tmp = n1->val;
            n1->val = n2->val;
            n2->val = tmp;
        }
    }
    void inorder(TreeNode *root, vector<TreeNode*>& nodes) {
       if(!root) return;
       inorder(root->left, nodes);
       nodes.push_back(root);
       inorder(root->right, nodes);
    }
};



/**************************************************** 
 ***    098,Medium,Validate Binary Search Tree 
 ****************************************************/

/*
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

    The left subtree of a node contains only nodes with keys less than the node's key.
    The right subtree of a node contains only nodes with keys greater than the node's key.
    Both the left and right subtrees must also be binary search trees.

confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution.
// store lower and upper bounds of each subtree, initially it is (-inf, inf)
// One corner case is when INT_MIN and INT_MAX is part of the value, so use LONG_MIN and LONG_MAX instead.

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return validate(root, LONG_MIN, LONG_MAX);
    }
    //make sure all tree values between (lo, hi)
    bool validate(TreeNode* root, long lo, long hi) {
        if(!root) return true;
        int x = root->val;
        if(x <= lo || x >= hi) return false;
        return validate(root->left, lo, x) && validate(root->right, x, hi);
    }
};

/**************************************************** 
 ***    097,Hard,Interleaving String 
 ****************************************************/

/*
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false. 
*/

/*
Dynamic programming.
Use a 2D array recording whether s1[0, i) and s2[0, j) interleaves to form s3[0, i+j).

If dp[i][j] is true, it can be either of the two cases:
dp[i-1][j] is true and s1[i-1] == s3[i+j-1]
1)
adb | e
a b
  d   | e 

2).
a d e |b
  a  | b
 d e

Boundary cse: i = 0 or j = 0.
we further define dp[0][0] = 0.

We can put boundary condition in various places (either outside main loop, or inside)
*/

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
        if(n1+n2 != n3) return false;
        //table[i][j]: s3[0 .. i+j-1] is interleaved by s1[0..i-1] and s2[0 .. j-1]
        vector<vector<bool> > table(n1+1, vector<bool>(n2+1, false));
        table[0][0] = true;
        for (int i = 0; i < n1 && s1[i] == s3[i]; ++i) {
            table[i+1][0] = true; //only uses s1
        }
        for (int j = 0; j < n2 && s2[j] == s3[j]; ++j) {
            table[0][j+1] = true; //only uses s2
        }
        for (int i = 0; i < n1; ++i) { //check s1[i]
            for (int j = 0; j < n2; ++j) { //check s2[j]
                table[i+1][j+1] = (s3[i+j+1] == s2[j] && table[i+1][j]) ||
                                  (s3[i+j+1] == s1[i] && table[i][j+1]);
            }
        }
        return table[n1][n2];
    }
};

/* Slightly optimized solution still using 2D array. Use length as outer loop. Avoid unecessary checks. 4ms. */

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.empty()) return s2 == s3;
        if(s2.empty()) return s1 == s3;
        int m = s1.size(), n = s2.size(), p = s3.size();
        if(m + n != p) return false;
        vector<vector<bool> > dp(m+1, vector<bool>(n+1, false)); //dp[i][j], whether s1[0 .. i) and s2[0 .. j) interleaves to form s3[0 .. i+j).
        dp[0][0] = true;
        for(int len = 1; len <= p; ++len) { //determine s3[0, len), check s3[0, len-1) and s3[len-1]
            bool found = false;
            for(int i = 0; i <= min(len-1, m); ++i) { //checking s1[0, i) and s1[i]
                int j = len - i-1; //checking s2[0, j) and s2[j]
                if(dp[i][j]) {
                    if(s1[i] == s3[len-1]) found = dp[i+1][j] = true; 
                    if(s2[j] == s3[len-1]) found = dp[i][j+1] = true;
                }
            }
            if(!found) return false;
        }
        return dp[m][n];
    }
};

/*
Space optimized version: only a 1D array (8ms).
*/

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.empty()) return s2 == s3;
        if(s2.empty()) return s1 == s3;
        int m = s1.size(), n = s2.size(), p = s3.size();
        if(m + n != p) return false;
        vector<bool> dp(n+1, false); //dp[i][j], whether s1[0 .. i) and s2[0 .. j) interleaves to form s3[0 .. i+j).
        dp[0] = true;
        for(int j = 1; j <= n; ++j) {
            dp[j] = dp[j-1] && (s2[j-1] == s3[j-1]);
        }
        
        for(int i = 1; i <= m; ++i) { //checking s1[0, i)
            dp[0] = dp[0] && (s1[i-1] == s3[i-1]);
            for(int j = 1; j <= n; ++j) { //checking s2[0, j)
                dp[j] = (dp[j] && (s1[i-1] == s3[i+j-1])) ||
                            (dp[j-1] && (s2[j-1] == s3[i+j-1]));
            }
        }
        return dp[n];
    }
};


/**************************************************** 
 ***    096,Medium,Unique Binary Search Trees 
 ****************************************************/

/*
Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

*/

// Dynamic programming. The ways of forming tree of size n can be found by choosing each of the n elements as root, which divides the others as left and right subtrees.

class Solution {
public:
    int numTrees(int n) {
        if(n < 0) return 0;
        if(n == 0 || n == 1) return 1;
        vector<int> count(n+1, 0); //store counts from i=0 to n
        count[0] = count[1] = 1;
        //calculate number of unique trees of size i
        for(int i = 2; i <= n; ++i) {
            //pick k-th number as root, then k elements as left-tree, i-k-1 elements as right-tree
            for(int k = 0; k < i; ++k) {
                count[i] += count[k]*count[i-k-1];
            }
        }
        return count[n];
    }
};


/**************************************************** 
 ***    095,Medium,Unique Binary Search Trees II 
 ****************************************************/

/*
Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Dynamic programming using a 2D array. The trick is to generate the right subtree by using a createNew function with a delta value.

class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if(n < 0) return vector<TreeNode*>();
        if(n == 0) return vector<TreeNode*>();
        vector<vector<TreeNode*> > dp(n+1); //dp[i]: solutions for tree of size i
        dp[0].push_back(NULL);
        for(int i = 1; i <= n; ++i) { //check tree of size i
            for(int k = 1; k <= i; ++k) { //make k as root
                for(auto l : dp[k-1]) { //construct left subtree
                    for(auto r : dp[i-k]) { //construct right subtree
                        TreeNode *root = new TreeNode(k);
                        root->left = l;
                        root->right = createNew(r, k);
                        dp[i].push_back(root);
                    }
                }
            }
        }
        return dp[n];
    }
    TreeNode* createNew(TreeNode* root, int delta) {
        if(!root) return NULL;
        TreeNode* nr = new TreeNode(root->val+delta); //new root
        nr->left = createNew(root->left, delta);
        nr->right = createNew(root->right, delta);
        return nr;
    }
};


/**************************************************** 
 ***    094,Medium,Binary Tree Inorder Traversal 
 ****************************************************/

/*
Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution (easy).

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        if(!root) return ret;
        inorder(root, ret);
        return ret;
    }
    void inorder(TreeNode* root, vector<int>& ret) {
        if(!root) return;
        if(root->left) inorder(root->left, ret);
        ret.push_back(root->val);
        if(root->right) inorder(root->right, ret);
    }
};

// Iterative solution using a stack (and a tag indicating the number of times an element appears in stack).
// Slightly different version with modified control flow with tag.

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        deque<pair<TreeNode*, int> > st; //stack
        st.push_back(make_pair(root, 0));
        while(!st.empty()) {
            TreeNode *node = st.back().first;
            int tag = ++st.back().second;
            if(tag == 1) {
                if(node->left) st.push_back(make_pair(node->left, 0));
            } else {
                result.push_back(node->val);
                st.pop_back();
                if(node->right) st.push_back(make_pair(node->right, 0));
            }
        }
        return result;
    }
};

// Another iterative solution by pushing left spline in the stack
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        deque<TreeNode*> st; //stack
        while(root) {
            st.push_back(root);
            root = root->left;
        }
        while(!st.empty()) {
            TreeNode* node = st.back(); st.pop_back();
            result.push_back(node->val);
            node = node->right;
            while(node) {
                st.push_back(node);
                node = node->left;
            }
        }
        return result;
    }
};

// Morris traversal O(n) without using a stack or recursive calls.
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        TreeNode *node = root;
        while(node) {
            if(!node->left) {
                result.push_back(node->val);
                node = node->right;
            } else {
                TreeNode *child = node->left;
                while(child->right != NULL && child->right != node) child = child->right;
                if(child->right == NULL) {
                    child->right = node; // first time, modify right pointer
                    node = node->left; //move to left child
                } else {
                    child->right = NULL; //second time, reset right pointer to NULL
                    result.push_back(node->val);
                    node = node->right;
                }
            }
        }
        return result;
    }
};

// Morris traversal with a slightly different while loop (visit node in the end of loop body)
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        TreeNode *node = root;
        while(node) {
            if(node->left) {  // has left subtree
                TreeNode *child = node->left;
                while(child->right != NULL && child->right != node) child = child->right;
                //reached right most child of left subtree
                if(child->right == NULL) { //first time
                    child->right = node;
                    node = node->left;
                    continue;
                } else { //second time
                   child->right = NULL; //second time
                }
            }
            //visit node
            result.push_back(node->val);
            node = node->right;
        }
        return result;
    }
};



/**************************************************** 
 ***    093,Medium,Restore IP Addresses 
 ****************************************************/

/*
Given a string containing only digits, restore it by returning all possible valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter) 
*/

// Recursive solution #1.
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> result;
        if(s.empty()) return result;
        string tmp;
        dfs(s, 0, 0, tmp, result);
        return result;
    }
    void dfs(const string& s, int i, int count, string tmp, vector<string>& result) {
        int n = s.size();
        if(i == n && count == 4) {
            result.push_back(tmp);
            return;
        }
        if(i == n || count == 4) return;
        if(i != 0) tmp += '.';
        if(s[i] == '0') {
            dfs(s, i+1, count+1, tmp+'0', result);
            return;
        }
        for(int k = i, val = 0; k < n; k++) {
            val = val*10 + (s[k] - '0');
            if(val >= 256) break;
            tmp += s[k];
            dfs(s, k+1, count+1, tmp, result);
        }
   }
};

// Recursive solution #2. 
// Need to add 4 periods, last one has to be after last character.
// store positions of periods (index of character right before newly added period), and reconstruct the string when valid solutions are found
// Caveat: string::insert function argument is the index which the new character is inserted before.
// Another caveat: ip address segments cannot have leading zeros, except .0. case, others like .03. or .00. are illegal. Need to filter them out

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> ret;
        vector<int> dotPos(4, -1); //dot positions in the s
        restore(s, 0, 0, dotPos, ret);
        return ret;
    }
    //checking substring starting at s[i] for dot number k (0-3), add values to dotPos
    void restore(const string& s, int i, int k, vector<int>& dotPos, vector<string>& ret) {
       if (k == 4) { //already placing 4 dots (one at the end)
          //onlyd add when i reaches the end
          if (i == s.size()) ret.push_back(construct(s, dotPos));
          return;
       }
       if (i == s.size()) return;
       int v = 0;
       for (int j = i; j < s.size(); ++j) {
          v = 10*v + s[j] - '0';
          if(v >= 256) break;
          dotPos[k] = j; //dot is after j's position
          restore(s, j+1, k+1, dotPos, ret);
          if(s[i] == '0') break; //if leading character is '0', do not continue loop ('.00.' is illegal IP segment)
       }
    }
    string construct(const string& s, const vector<int>& dotPos) {
        string ret = s;
        ret.insert(dotPos[2]+1, 1, '.');
        ret.insert(dotPos[1]+1, 1, '.');
        ret.insert(dotPos[0]+1, 1, '.');
        return ret;
    }

};


/**************************************************** 
 ***    090,Medium,Subsets II 
 ****************************************************/

/*
Given a collection of integers that might contain duplicates, nums, return all possible subsets.

Note:

    Elements in a subset must be in non-descending order.
    The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,2], a solution is:

[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
*/

// Solution 1. Similar to #78, DFS backtracking with fan-out = 2.
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int> > result;
        sort(nums.begin(), nums.end());
        vector<int> tmp;
        dfs(nums, 0, tmp, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result) {
        if(i == nums.size()) {
            result.push_back(tmp);
            return;
        }
        int j = i;
        while(j < nums.size() && nums[j] == nums[i]) j++;
        //j is index of first element != nums[i], or end
        //not adding nums[i] to set
        dfs(nums, j, tmp, result);
        //adding 1 to j-i nums[i] to set
        for(int k = 0; k < j-i; ++k) {
            tmp.push_back(nums[i]);
            dfs(nums, j, tmp, result);
        }
        //revert back
        for(int k = 0; k < j-i; ++k) {
            tmp.pop_back();
        }
    }
};

// Solution 2. Similar to #78, DFS backtracking with fan-out = number of unused elements
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int> > result;
        vector<int> tmp;
        sort(nums.begin(), nums.end());
        dfs(nums, 0, tmp, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result) {
        result.push_back(tmp);
        for(int j = i; j < nums.size(); ++j) {
            if(j == i || nums[j] != nums[j-1]) { //ignore duplicates
                tmp.push_back(nums[j]);
                dfs(nums, j+1, tmp, result);
                tmp.pop_back();
            }
        }
    }
};

// Solution 3. Similar to #78, dynamic programming.
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int> > result;
        sort(nums.begin(), nums.end());
        result.push_back(vector<int>()); //empty set
        int i = 0;
        int n = nums.size();
        while(i < n) {
            int j = i;
            while(j < n && nums[j] == nums[i]) j++;
            int ndup = j-i; //number of duplicates
            //add 1 - ndup nums[i] to existing solution
            int size = result.size();
            for(int k = 0; k < ndup; ++k) {
                for(int l = k*size; l < (k+1)*size; ++l) {
                    result.push_back(result[l]);
                    result.back().push_back(nums[i]);
                }
            }
            i = j;
        }
        return result;
    }
};


/**************************************************** 
 ***    088,Easy,Merge Sorted Array 
 ****************************************************/

/*
Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2. The number of elements initialized in nums1 and nums2 are m and n respectively.
*/

// Best solution: start backwards, utilize the extra space after nums1, only O(1) extra space needed.
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m-1, j = n-1, k = m+n-1;
        while(i >= 0 || j >= 0) {
            if(j < 0) break;
            else if(i < 0) nums1[k--] = nums2[j--];
            else nums1[k--] = nums1[i] <= nums2[j] ? nums2[j--] : nums1[i--];
       }
    }
};

// A slightly more concise solution
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m-1, j = n-1, k = m+n-1;
        while(j >= 0) {
            nums1[k--] = (i < 0 || nums1[i] <= nums2[j]) ? nums2[j--] : nums1[i--];
       }
    }
};

// An old solution: merge procedure in merge sort. No sentinel. Need extra array of length O(m+n).

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int tot = m+n;
        vector<int> aux(tot, 0);
        for (int i = 0, j = 0, k = 0; i < m || j < n; ) {
            int v1 = (i < m) ? nums1[i] : INT_MAX;
            int v2 = (j < n) ? nums2[j] : INT_MAX;
            if (v1 < v2) { aux[k++] = v1; i++; }
            else { aux[k++] = v2; j++; }
        }
        for (int i = 0; i < tot; ++i) nums1[i] = aux[i];
    }
};

/**************************************************** 
 ***    087,Hard,Scramble String 
 ****************************************************/

/*
Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.
Below is one possible representation of s1 = "great":

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t

To scramble the string, we may choose any non-leaf node and swap its two children.
For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t

We say that "rgeat" is a scrambled string of "great".
Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a

We say that "rgtae" is a scrambled string of "great".
Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1. 
*/

/*
Solution 1. Recursive dfs with branching by anagram checking, 8ms. 

If no branching, time complexity is around 5^n (exponential algorithm!)
f(n) = 2*(f(1)+f(n-1)) + 2*(f(2)+f(n-2)+ ... + 2(f(n-1)+f(1)).
f(n+1) = ...
f(n+1) = 5f(n) => f(n) = 5^n.

Try all ways of cutting the string into two parts, and recursively check if the two parts are scramble strings. Check every possibilities of partition:
e.g.  a0-a4 v.s. b0-b4
check  a0 | a1-a4 v.s. b0 | b1-b4; 
       a0a1 | a2-a4 v.s. b0b1 | b2-b4 ... 
and
       a0 | a1-a4 v.s. b0-b3 | b4; 
       a0a1 | a2-a4 v.s. b0-b2 | b3b4 ...

Anagram checking: indexed map from 0 to 256. If we assume only a-z characters and use 26 entries, we can reduce the time to 4ms.

search s1, increment character counts,
search s2, decrement character counts. If found a negative value, then we know that they are not anagram.
*/

class Solution {
public:
    bool isScramble(string s1, string s2) {
        if(s1.size() != s2.size()) return false;
        if(s1.empty()) return true; //empty string
        return isScramble(s1, 0, s2, 0, s1.size());
    }

    bool isScramble(const string& s1, int lo1, const string& s2, int lo2, int len) {
        if(len == 0) return true;
        if(len == 1) return s1[lo1] == s2[lo2];
        if(!isAnagram(s1, lo1, s2, lo2, len)) return false;
        //cut s1 and s2 into two parts
        for(int i = 1; i < len; ++i) {
            if(isScramble(s1, lo1, s2, lo2, i) && isScramble(s1, lo1+i, s2, lo2+i, len-i)) return true;
            if(isScramble(s1, lo1, s2, lo2+len-i, i) && isScramble(s1, lo1+i, s2, lo2, len-i)) return true;
        }
        return false;
    }

    bool isAnagram(const string& s1, int lo1, const string& s2, int lo2, int len) {
        vector<int> dict(256, 0);
        for(int i = lo1; i < lo1+len; ++i) {
            dict[s1[i]]++;
        }
        for(int i = lo2; i < lo2+len; ++i) {
            if(--dict[s2[i]] < 0) return false;
        }
        return true;
    }
};

/*
2. 3D DP solution (bottom-up), 284 ms even with adding isAnagram checking for branching.  3 indices, len, i, j
//dp[i][j][len]: whether s1[i, i+len) and s2[j, j+len) is scramble, len can be 0 to n, i, j can be 0 to n-1
len as outer loop. Special treatment when len = 1.
*/

class Solution {
public:
    bool isScramble(string s1, string s2) {
        if(s1.size() != s2.size()) return false;
        if(s1.empty()) return true; //empty string
        int n = s1.size();
        //dp[i][j][len]: whether s1[i, i+len) and s2[j, j+len) is scramble, len can be 0 to n, i, j can be 0 to n-1
        dp.resize(n+1, vector<vector<bool> >(n, vector<bool>(n, false)));
        for(int len = 1; len <= n; ++len) {
            for(int i = 0; i+len <= n; ++i) {
                for(int j = 0; j+len <= n; ++j) {
                    if(len == 1) {
                       dp[len][i][j] = (s1[i] == s2[j]);
                       continue;
                    }
                    if(!isAnagram(s1, i, s2, j, len)) { dp[len][i][j] = 0; continue; }
                    for(int l = 1; l < len; ++l) {
                        dp[len][i][j] = ((dp[l][i][j] && dp[len-l][i+l][j+l]) || (dp[l][i][j+len-l] && dp[len-l][i+l][j]));
                        if(dp[len][i][j]) break;
                    }
                }
            }
        }
        return dp[n][0][0];
    }
    
    bool isAnagram(const string& s1, int lo1, const string& s2, int lo2, int len) {
        vector<int> dict(256, 0);
        for(int i = lo1; i < lo1+len; ++i) {
            dict[s1[i]]++;
        }
        for(int i = lo2; i < lo2+len; ++i) {
            if(--dict[s2[i]] < 0) return false;
        }
        return true;
    }

    vector<vector<vector<bool> > > dp;
};

/*
3. 3D DP solution with memoization (20ms). now the 3D vector can have three values, -1, 0, 1. -1 means uninitialized, 0 means not scramble, 1 means scramble. Need to ensure each call to scramble returns either 0 and 1 and properly sets dp[len][i][j] at the first time.
*/

class Solution {
public:
    bool isScramble(string s1, string s2) {
        if(s1.size() != s2.size()) return false;
        if(s1.empty()) return true; //empty string
        int n = s1.size();
        //dp[i][j][len]: whether s1[i, i+len) and s2[j, j+len) is anagram, len can be 0 to s1.size, i, j can be 0 to n-1
        dp.resize(n+1, vector<vector<int> >(n, vector<int>(n, -1)));
        return isScramble(s1, 0, s2, 0, s1.size());
    }
    //memoization, always return 0 or 1
    int isScramble(const string& s1, int i, const string& s2, int j, int len) {
        int tag = dp[len][i][j];
        if(tag >= 0) return tag;

        if(len == 0) dp[len][i][j] = 1;
        else if(len == 1) dp[len][i][j] = (s1[i] == s2[j]);
        else if(!isAnagram(s1, i, s2, j, len)) dp[len][i][j] = 0;
        else {
             dp[len][i][j] = 0; //should first set to zero (for not found case)
             //cut s1 and s2 into two parts
             for(int l = 1; l < len; ++l) {
                 if( (isScramble(s1, i, s2, j, l) && isScramble(s1, i+l, s2, j+l, len-l) ) ||
                     (isScramble(s1, i, s2, j+len-l, l) && isScramble(s1, i+l, s2, j, len-l) ) ) {
                     dp[len][i][j] = 1;
                     break;
                 }
             }
        }
        return dp[len][i][j];
    }

    bool isAnagram(const string& s1, int lo1, const string& s2, int lo2, int len) {
        vector<int> dict(256, 0);
        for(int i = lo1; i < lo1+len; ++i) {
            dict[s1[i]]++;
        }
        for(int i = lo2; i < lo2+len; ++i) {
            if(--dict[s2[i]] < 0) return false;
        }
        return true;
    }

    vector<vector<vector<int> > > dp;
};



/**************************************************** 
 ***    085,Hard,Maximal Rectangle 
 ****************************************************/

/*
Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing all ones and return its area. 
*/

// Solution 1. Use the routine of finding the largest rectangle in the histogram.
// Scan from top to bottom, find largest rectangle at current level. 

class Solution {
public:
    int maximalRectangle(vector<vector<char> >& matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> height(n, 0);
        int max_area = 0;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                height[j] = (matrix[i][j] == '1') ? height[j]+1 : 0;
            }
            max_area = max(max_area, largestRectangleArea(height));
        }
        return max_area;
    }

    int largestRectangleArea(vector<int>& height) {
        if(height.empty()) return 0;
        height.push_back(0);
        deque<int> s; //stack for positions
        int n = height.size();
        int max_area = 0;
        for(int i = 0; i < n; ++i) {
             while(!s.empty() && height[s.back()] > height[i]) {
                int h = height[s.back()];
                s.pop_back();
                int j = s.empty() ? 0 : s.back()+1;
                max_area = max(max_area, h*(i-j));
            }
            s.push_back(i);
        }
        return max_area;
    }
};

/*
Solution 2 using dynamic programming. For each row, use three arrays, left/right/height to store the left and right boundary and height of maximum rectangle enclosing matrix[i][j] for the rows seen so far (just like the bars in the histogram problem). Use the values at step i to calculate the values at step i+1.

             +
         +   +
         +   + +
         + + + +
index: 0 1 2 3 4
left: -1 1 1 3 3
right: 5 1 4 3 4
height:0 3 1 4 2

Now check the new row, we track the first left seen so far.

           +
       +   +
       +   + +
       + + + +
     0 1 2 3 4 
     + + +  : cur_left = 0
the new left is simply the maximum of old left and cur_left
the new right is simply the minimum of old right and cur_right
We assign cur_left values in an eager way: whenever we see a '0', we asisgn cur_left to j+1.

Caveat: 
1. for '0' entries, left[i] can be -1, but right[i] should be n, due to the min operation used to update its value.
2. Remember to properly initialize cur_left and cur_right when scanning each row.
*/

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> left(n, -1), right(n, n), height(n, 0);
        int cur_left = 0, cur_right = 0;
        int max_area = 0;
        for(int i = 0; i < m; ++i) {
            cur_left = 0; cur_right = n-1; //initialize
            for(int j = 0; j < n; ++j) { //scan left to right
                height[j] = (matrix[i][j] == '0') ? 0 : height[j]+1;
                if(matrix[i][j] == '0') {
                    left[j] = -1;
                    cur_left = j+1; //pre-assign cur_left to next 
                } else {
                    left[j] = max(left[j], cur_left);
                }
            }
            for(int j = n-1; j >= 0; --j) { //scan right to left
                if(matrix[i][j] == '0') {
                    right[j] = n; //cannot be -1 due to the min operation!
                    cur_right = j-1; //pre-assign cur_right to next
                } else {
                    right[j] = min(right[j], cur_right);
                }
            }
            //now we have left[j], right[j], and height[j] in place
            for(int j = 0; j < n; ++j) {
                max_area = max(max_area, height[j]*(right[j] - left[j] + 1));
            }
        }
        return max_area;
    }
};

/**************************************************** 
 ***    084,Hard,Largest Rectangle in Histogram 
 ****************************************************/

/*
Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

The largest rectangle is shown in the shaded area, which has area = 10 unit.

For example,
Given height = [2,1,5,6,2,3],
return 10. 
*/

/*
The rectangle is limited by the histrogram bar of the lowest height.
Scan the histogram one-by-one. Say we already scanned i bars, and the next is i+1. There are three cases:
1. i+1 is higher than i. In this case, we can't say anything about the possible rectangles formed by i, so we just push i+1 to stack.

     ++++
     +  +
  ++++  +
  +  +  +
  +  +  +
+++++++++++++++++++++++++++++++++++++++
   i  i+1

2. i+1 is lower than i. In this case, we can say for sure that the largest rectangle that bar i can form will terminate at i+1. So we calculate that area, and pop-out i (since we don't need i anymore)

  ++++
  +  +
  +  ++++
  +  +  +
  +  +  +
+++++++++++++++++++++++++++++++++++++++
   i  i+1

The tricky part is, when we pop-out i, i+1 can be extended to the left, since it is lower, and the largest rectangle formed by i+1 can extend to the left, so we have to store not only the height but also the current left boundary position of the rectangle formed by i. After removing i effectively we will have, which waits to be checked in the next step.


  +++++++
  +     +
  +     +
+++++++++++++++++++++++++++++++++++++++
   i  i+1

3. i+1 is same height as i. We can still use 2, because i+1 will inherit the position of i.

*/

/// Solution 1 using a stack of both position and height. No need to handle degenerate cases separately. O(n) time amorized, because each bar is pushed and popped at most once. O(n) space for sstack.
/// We use a variable j to store the position of recently popped bars, and make the new bar inherit this position when inserted to stack.
/// Another trick is to append a sentinel of height 0 in the end of height vector, so that all the bars in the stack will eventually be popped out to be examined.

class Solution {
public:
    int largestRectangleArea(vector<int>& height) {
        if(height.empty()) return 0;
        int max_area = 0;
        stack<pair<int, int> > st; //store position and height 
        height.push_back(0); //sentinel at the end
        int n = height.size();
        for(int i = 0; i < n; ++i) {
            int j = i, h = 0;
            while(!st.empty() && st.top().second > height[i]) {
                j = st.top().first;
                h = st.top().second;
                max_area = max(max_area, (i-j)*h);
                st.pop();
            }
            st.push(make_pair(j, height[i])); //inherits position j from popped elements
        }
        return max_area;
    }
};

/// Solution 2 using a stack only tracking the index of bar in the height. We don't need to store the inherited position, because we observe that the inherited position is always one plus the position of the bar at top of stack after the bar currently under examination is popped out.
/// Again O(n) amortized time and O(n) space.

class Solution {
public:
    int largestRectangleArea(vector<int>& height) {
        if(height.empty()) return 0;
        int max_area = 0;
        stack<int> st; //store position in height
        height.push_back(0); //sentinel at the end
        int n = height.size();
        for(int i = 0; i < n; ++i) {
            while(!st.empty() && height[st.top()] > height[i]) {
                int h = height[st.top()];
                st.pop();
                int j = st.empty() ? 0 : st.top() + 1;
                max_area = max(max_area, (i-j)*h);
            }
            st.push(i);
        }
        return max_area;
    }
};

/*
Solution 3, O(n) amortized time, and O(n) space. The idea is to find the left and right boundaries of the rectangle for each bar. This means that for each bar i, we find left[i] and right[i] such that bars within them have height no less than bar[i], and the spacing between the two is as wide as possible. We can achieve this in O(n) amortized time.
Scan from left to right to find left[i]:
1. If bar i+1 is higher than i, then left[i+1] = i+1.
2. If bar i+1 is lower than i, we start scanning from left[i]-1 towards left, and find the first bar j whose height is smaller than i+1, then left[i+1] = j+1
3. If bar i+1 is same height as i, then left[i+1] = left[i]
Similarly for right.
We can proove that we never scan each element more than twice, so amortized O(n).

We can further optimize step 2 in that if we find a bar j having the same height as i+1, then immediately we have left[i+1] = left[j], and break the loop.
*/

class Solution {
public:
    int largestRectangleArea(vector<int>& height) {
        if(height.empty()) return 0;
        int max_area = 0;
        int n = height.size();
        vector<int> left(n, 0), right(n, n-1);
        for(int i = 1; i < n; ++i) { //get left
            if(height[i] > height[i-1]) left[i] = i;
            else if(height[i] == height[i-1]) left[i] = left[i-1];
            else { //start scanning from left[i-1]-1 backwards
                int j = left[i-1]-1;
                while(j >= 0 && height[j] >= height[i]) j--;
                left[i] = j+1;
            }
        }
        for(int i = n-2; i >= 0; --i)  {  //get right
            if(height[i] > height[i+1]) right[i] = i;
            else if(height[i] == height[i+1]) right[i] = right[i+1];
            else { //start scanning from right[i+1]+1 forwards
                int j = right[i+1]+1;
                while(j < n && height[j] >= height[i]) j++;
                right[i] = j-1;
            }
        }
        for(int i = 0; i < n; ++i)
            max_area = max(max_area, height[i]*(right[i] - left[i] + 1));

        return max_area;
    }
};

/// Solution 4, O(n2) worst case time, and O(1) space. Do not use stack, rather modify the heights in height
class Solution {
public:
    int largestRectangleArea(vector<int>& height) {
        if(height.empty()) return 0;
        int max_area = 0;
        height.push_back(0);
        int n = height.size();
        for(int i = 1; i < n; ++i) {
            if(height[i] >= height[i-1]) continue;
            int j = i-1;
            while(j >= 0 && height[j] > height[i]) {
                max_area = max(max_area, (i-j)*height[j]);
                height[j] = height[i];
                j--;
            }
        }
        return max_area;
    }
};



/**************************************************** 
 ***    083,Easy,Remove Duplicates from Sorted List 
 ****************************************************/

/*
Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Since head will never be removed, do not need a dummy head pointer

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* p = head, *q = head->next;
        while(q) {
            if(p->val == q->val) { //delete q
                p->next = q->next;
                delete q;
                q = p->next;
            } else { //move forward
                p = q;
                q = q->next;
            }
        }
        return head;
    }
};

/**************************************************** 
 ***    082,Medium,Remove Duplicates from Sorted List II 
 ****************************************************/

/*
Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// use two pointers. Also dummy head, because head might be deleted.

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;

        ListNode *p = dummy, *q = p->next;
        //p is tail of processed list, q is its next, r is one node past the last duplicated entry.
        while(q) {
            ListNode* r = q->next;
            while(r && r->val == q->val) r = r->next;
            //r is either null or first entry not equal to q
            if(r == q->next) { //no duplicated entry
                p = q;
                q = r; //just move forward
                continue;
            }
            //then delete everything from q to r's ancestor
            while(q != r) {
                ListNode * t = q;
                delete t;
                q = q->next;
            }
            //after loop q == r
            p->next = q;
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};

/**************************************************** 
 ***    081,Medium,Search in Rotated Sorted Array II 
 ****************************************************/

/*
Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?

Write a function to determine if a given target is in the array.
*/

/*
Binary search. The array can be broken into two part, first part is 4-7, second part is 0-2. If array is unrotated, then only first part exists (corner case). 
There are three anchor points, lo, hi, and mid.
First determine whether mid is in first half or second half. Due to duplicated items, we now has three cases:
1. Mid is in first half iff nums[mid] > nums[lo] 
2. Mid is in second half iff nums[mid] < nums[lo]
3. if nums[mid] == nums[lo], we can't say for sure which part mid belongs to, but we know that nums[lo] is not target, so we simply increment lo. 
Examples for 3. 
 2 2 2 2 3 2 2
lo    mid   hi  (mid is in first half)
 2 2 3 2 2 2 2
lo    mid   hi  (mid is in second half)

1. If mid is in first half, we know that nums[mid] >= nums[lo] (could be equal because mid can be lo, when hi = lo+1), if target falls between the two, then the index has to be between lo and mid. Otherwise, it is between mid and hi.
2. If mid is in second half, we know that nums[mid] <= nums[hi] (could be equal because mid can be hi, when hi = lo), if target falls between the two, then the index has to be between mid and hi. Otherwise, it is between lo and mid.
*/

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        int lo(0), hi(n-1);
        while(lo <= hi) {
            int mid = lo + (hi-lo) / 2;
            if(target == nums[mid]) return true;
            if (nums[mid] > nums[lo]) {
                if(target >= nums[lo] && target < nums[mid]) hi = mid -1;
                else lo = mid + 1;
            } else if (nums[mid] < nums[lo]) {
                if(target <= nums[hi] && target > nums[mid]) lo = mid + 1;
                else hi = mid - 1;
            } else {
                lo++;
            }
        }
        return false;
    }
};

/**************************************************** 
 ***    080,Medium,Remove Duplicates from Sorted Array II 
 ****************************************************/

/*
Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new length. 
*/

// Solution: two pointers. 
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return n;
        int len = 0;
        int i = 0, j = 0;
        while(i < n) {
            j = i+1;
            while(j < n && nums[j] == nums[i]) j++;
            if(j >= i+1) nums[len++] = nums[i];
            if(j > i+1) nums[len++] = nums[i];
            i = j;
        }
        return len;
    }
};

// A old solution
class Solution {
public:
    int removeDuplicates(int A[], int n) {
        if(n == 0) return 0;
   		int i(0), j(1), prev = INT_MAX, count = 0;
		for(j = 0; j < n; ++j) {
		    if(A[j] == prev) count++;
		    else count = 1;
		    prev = A[j];
		    if(count <= 2) A[i++] = A[j]; 
		}
		return i;   
    }
};

/**************************************************** 
 ***    079,Medium,Word Search 
 ****************************************************/

/*
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]

word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
*/

/* 
Recursive solution using DFS
Several optimizations:
1. Do not use another array to store the visited status of the board. Instead, set the visited board character as '*', and set it back to original at retrace stage.
2. For checking validity of new positions, leave it to the recursive function (if not legal simply return false). If do something like this, will lead to TLE.

        if(i > 0 && board[i-1][j] != '*' && existHelper(board, i-1, j, word, k+1)) return true;
        if(i < m-1 && board[i+1][j] != '*' && existHelper(board, i+1, j, word, k+1)) return true;
        if(j > 0 && board[i][j-1] != '*' && existHelper(board, i, j-1, word, k+1)) return true;
        if(j < n-1 && board[i][j+1] != '*' && existHelper(board, i, j+1, word, k+1)) return true;

*/

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if(board.empty() || board[0].empty()) return false;
        if(word.empty()) return true;
        int m = board.size(), n = board[0].size();
        if(m*n < word.size()) return false;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(existHelper(board, i, j, word, 0)) return true;
            }
        }
        return false;
    }
    bool existHelper(vector<vector<char> >& board, int i, int j, const string& word, int k) {
        if(k == word.size()) return true; //found
        int m = board.size(), n = board[0].size();
        if(i < 0 || i >= m || j < 0 || j >= n) return false; //not legal position
        if(board[i][j] == '*') return false; //already visited
        if(board[i][j] != word[k]) return false; //not match
        char c = board[i][j];
        board[i][j] = '*';
        //matches, move to next one
        if(existHelper(board, i-1, j, word, k+1)) return true;
        if(existHelper(board, i+1, j, word, k+1)) return true;
        if(existHelper(board, i, j-1, word, k+1)) return true;
        if(existHelper(board, i, j+1, word, k+1)) return true;
        
        board[i][j] = c; //retrace
        return false;
    }
};

// An old iterative solution
class Solution {
public:
	//move from current position (row,col) to next position
	void move(int &row, int &col, int dir) {
		if(dir == 1) col += 1; //right
		else if(dir == 2) row -= 1; //up
		else if(dir == 3) col -= 1; //left
		else if(dir == 4) row += 1; //down
		else row = col = -1; //not move
	}
	//check if position (row, col) exceeds boundary
	bool isValid(int row, int col, int m, int n) {
		return(row >= 0 && row < m && col >= 0 && col < n);
	}
	bool exist(vector<vector<char> > &board, string word) {
		int m = board.size();
		int n = board[0].size();
		int tot = m*n;
		int len = word.size();
		int k = 0; //k-th character in word
		vector<int> dir(len, 1);  //directions at step k
		vector<int> row(len, -1); //row number at step k
		vector<int> col(len, -1); //column number at step k
		vector<vector<bool> > visited(m, vector<bool>(n, false));//site visited? 
		
		for(int l = 0; l < tot; ++l) { //loop thru all elements in the board
			//invariant: k characters matched (now matching word[k] with position[k] determined from position[k-1] and dir[k-1])
			k = 0; //reset k everytime!
			while(1) {
			    if(k == len) return true; //already found!
			    if(k > 0 && dir[k-1] > 4) { //tried all directions, retrace
			    	dir[k-1] = 1; //reset to first direction
			    	visited[row[k-1]][col[k-1]] = false; //reset
				    row[k-1] = col[k-1] = -1;
				    k--;
				    if(k == 0) break; //breaking condition
				    dir[k-1] ++; //last one should increment
				    continue;
				}
			    //find next position
			    int nextRow = row[k-1], nextCol = col[k-1];
			    if(k == 0) { nextRow = l/n; nextCol = l%n; }
			    else move(nextRow, nextCol, dir[k-1]);
			    
			    //check match?
			    if(k == 0) { //first character special case
				    if(board[nextRow][nextCol] != word[k]) break; 
				    else { //matched first character
				        row[k] = nextRow; col[k] = nextCol;
				        visited[row[k]][col[k]] = true;
				        k++; //try next one
				    }
				} else if(!isValid(nextRow, nextCol, m, n) || board[nextRow][nextCol] != word[k] || visited[nextRow][nextCol]) { //no match
    				dir[k-1] ++;
				} else { //found match
		    	    row[k] = nextRow; col[k] = nextCol;
			        visited[row[k]][col[k]] = true; //update visited
			        k++;
				}
			}
		}
		return false;
	}
};



/**************************************************** 
 ***    078,Medium,Subsets 
 ****************************************************/

/*
Given a set of distinct integers, nums, return all possible subsets.

Note:

    Elements in a subset must be in non-descending order.
    The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
*/

// Solution 1. Recursive backtracking using DFS. Fan-out is 2 (for each number, add or not add).

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int> > result;
        sort(nums.begin(), nums.end());
        vector<int> tmp;
        dfs(nums, 0, tmp, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result) {
        if(i == nums.size()) {
            result.push_back(tmp);
            return;
        }
        // not taking nums[i]
        dfs(nums, i+1, tmp, result);
        // taking nums[i]
        tmp.push_back(nums[i]);
        dfs(nums, i+1, tmp, result);
        tmp.pop_back(); //revert
    }
};

// Solution 2. Recursive backtracking using DFS. Fan-out is number of unused elements, less tree depth and thus better efficiency than 1.

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int> > result;
        vector<int> tmp;
        sort(nums.begin(), nums.end());
        dfs(nums, 0, tmp, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result) {
        result.push_back(tmp);
        for(int j = i; j < nums.size(); ++j) { //choose one from unused numbers
            tmp.push_back(nums[j]);
            dfs(nums, j+1, tmp, result);
            tmp.pop_back();
        }
    }
};

// Solution 3. Dynamic programming. For each number, add to previous solution.
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int> > result;
        sort(nums.begin(), nums.end());
        result.push_back(vector<int>()); //empty set
        for(int i = 0; i < nums.size(); ++i) {
            //add nums[i] to all previous solutions
            int size = result.size();
            for(int j = 0; j < size; ++j) {
                result.push_back(result[j]);
                result.back().push_back(nums[i]);
            }
        }
        return result;
    }
};

// Solution 4. Use bit operation. There are pow(2, n) results, we can label them in a consistent order similar to Solution 3.
// for example [1,2,3]:
// subset:       [], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]
// id(base 10):  0    1    2      3     4     5       6         7
// id(base 2):  000  001  010    011   100   101     110       111
// As we can see, number 1 (the 0-th number) only appears when last digit is set. number 2 (the 1st number) only appears when second from last digit is set, and so on. Thus, for each id, we can check which digit are set, and add the corresponding number to the subset.
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        int size = 1 << n;
        sort(nums.begin(), nums.end());
        vector<vector<int> > result(size, vector<int>());
        for(int i = 0; i < result.size(); ++i) {
            for(int j = 0; j < n; ++j) {
                if(i & (1 << j)) result[i].push_back(nums[j]);
            }
        }
        return result;
    }
};


/**************************************************** 
 ***    077,Medium,Combinations 
 ****************************************************/

/*
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
*/

// Solution 1. Recursive solution. Start with k trials, every time decrement trials. Stop recursion when there is no trials left (k == 0). (12ms)
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int> > result;
        if(k > n || n <= 0) return result;
        vector<int> tmp(k, 0);
        dfs(1, n, k, tmp, result);
        return result;
    }
    //k trials left, start from number i, maximum is n
    void dfs(int i, int n, int k, vector<int>& tmp, vector<vector<int> >& result) {
        if(k == 0) {
            result.push_back(tmp);
            return;
        }
        if(i > n) return; //no numbers available
        int size = tmp.size();
        for(int j = i; j <= n; ++j) { //choose number between i and n
            tmp[size-k] = j; //choose number j
            dfs(j+1, n, k-1, tmp, result); //dfs starting with j+1
        }
    }
};

// Solution 2. Optimized recursive solution. Stop recursion after making the decision for the last trial (k == 1), also avoid uncessary trial when i > n.
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int> > result;
        if(k > n || n <= 0) return result;
        vector<int> tmp(k, 0);
        dfs(1, n, k, tmp, result);
        return result;
    }
    //k trials left, start from number i, maximum is n
    void dfs(int i, int n, int k, vector<int>& tmp, vector<vector<int> >& result) {
        int size = tmp.size();
        for(int j = i; j <= n; ++j) { //choose number between i and n
            tmp[size-k] = j; //choose number j
            if(k == 1) result.push_back(tmp); //reaching the end
            else if(j < n) dfs(j+1, n, k-1, tmp, result); //dfs starting with j+1
        }
    }
};	

// Solution 3. Iterative. Save results at i == k. (16ms)
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int> > result;
        if(k > n || n <= 0) return result;
        vector<int> tmp(k, 0);
        int i = 0; 
        while(i >= 0) { //the i-th choice ( 0 <= i < k)
            if(i == k) { 
                result.push_back(tmp); 
                i--; //backtrace!
                continue; 
            }
            tmp[i]++; //choose the next number
            if(tmp[i] > n) { i--; continue; } //back trace
            i++; //go to next step
            if(i < k) tmp[i] = tmp[i-1]; //choose right starting point for the next tmp[i]++
        }
        return result;
    }
};

// Solution 3. Iterative, optmized and simpler. Save results at i == k-1. (8ms)
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int> > result;
        if(k > n || n <= 0) return result;
        vector<int> tmp(k, 0);
        int i = 0; 
        while(i >= 0) { //the i-th choice ( 0 <= i < k)
            tmp[i]++; //choose the next number
            if(tmp[i] > n) i--; //back trace
            else if (i == k-1) result.push_back(tmp);
            else {
                i++; //go to next step
                tmp[i] = tmp[i-1]; //choose right starting point for the next tmp[i]++
            }
        }
        return result;
    }
};


/**************************************************** 
 ***    076,Hard,Minimum Window Substring 
 ****************************************************/

/*
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"

Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S. 
*/

/*
The string T can have duplicated characters, so need to maintain a count for each unique character. We also need to keep track of which characters have been seen during the scan. We could use two maps, but a more elegant way is to use one map intialized as the count in T, and as we scan S and see a character in T, we decrement the individual count. As we scan the S, we also maintain the left side of the window as "istart", and increment it as needed. There are several things to consider:
1. how to distinguish between characters appearing in T and not? (e.g. "D" v.s. "A")
2. how to know whether we have all the characters we need to construct T?

For Q1, we can use an index vector (dict[256]) to store the occurrences of each alphabet in T, and for other alphabets, initialized as -s.len(). When scanning, if we see the individual count of a char to be smaller or equal than -s.len(), we know that it does not appear in T.
For Q2, we maintain another variable "count", initialized as T.len(), and decremented only when we have seen a "useful" character. "useful" means character appearing in T and also not redundant. How to know if it is redundant or not? We can check the individual count is negative or not. When count == 0, we know that s[istart, i] covers T.
The next step is to check if we could move istart to the right and remove some redundant characters. This can be checked by individual count ++dict[s[istart]] <= 0. After this step, s[istart, i] is the minimum window seen so far containing T, by definition, s[istart] for sure is needed for T.
Next is to continue scanning forward. This gives 16ms solution.

An optimization (16ms=>12ms): we remove s[istart], update the counts (dict and count), and move on. Once count == 0 again, we go back to previous step again. Because we know for sure that we don't need s[istart] in layer searches, so we can remove it and update count. This can avoid many uncessary executiong of if(count == 0) part.

The code can be further shortened: in the while loop:
while(++dict[s[istart] <= 0) istart++;
and then only do: istart++;
*/

class Solution {
public:
    string minWindow(string s, string t) {
        int slen = s.size();
        vector<int> dict(256, -slen);
        int nc = t.size();
        for(int i = 0; i < nc; ++i) {
            if(dict[t[i]] < 0) dict[t[i]] = 1;
            else dict[t[i]]++;
        }
        int istart = 0, count = nc;
        int min_len = INT_MAX, min_start = -1;
        for(size_t i = 0; i < s.size(); ++i) {
            if(--dict[s[i]] >= 0) count--;
            if(count == 0) {
                while(dict[s[istart]] < 0) {
                    dict[s[istart++]]++;
                }
                int len = i-istart+1;
                if(len < min_len) { min_len = len; min_start = istart; }
                dict[s[istart++]]++; count = 1;
            }
        }
        return min_start == -1 ? "" : s.substr(min_start, min_len);        
    }
};

/*
Another solution is to use a queue to store (position in S of) T's characters seen so far, see below:
*/
/// An old solution using queue
/// Use a window to slide from left to right
/// Use counts to store the occurrences of characters needed to complete (when we see a character that is in t, we decrement the corresponding
/// count in counts. The values can become negative, indicating that the character is in excess.
/// Use a queue to store the current window, the queue is maintained in the following way:
/// 1. when we see a character that is in t, add it to end of queue
/// 2. If the new character in (1) is the same as the front of queue, and a is in excess we pop front (e.g. S = abea.. T = ab, but not: 
/// S = abea.. T = aab, where second a in S is required).
/// 3. when count is zero, we calculate the length, update minL if needed
/// 4. when we pop and push, we incre/decre counts[c], and depending on its sign, update cnt acoordingly.

class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> counts(256, 0);
        int cnt = 0; // number of characters required to completely include t.
        for (int i = 0; i < t.size(); i++) { 
            counts[t[i]]++; 
            cnt++;
        }
        int minl = INT_MAX, mini = 0;
        deque<int> q;
        
        for(int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (t.find(c) == string::npos) continue;
            
            counts[c]--;
            if(counts[c] >= 0) cnt--;
            else if (s[q.front()] == c) {
                counts[c]++;
                q.pop_front();
            }
            q.push_back(i);
            
            if (cnt == 0) {
                while (counts[s[q.front()]] < 0) {
                    counts[s[q.front()]]++;
                    q.pop_front();
                }
                int len = q.back()-q.front()+1;
                if (len < minl) { minl = len; mini = q.front(); }
            }
        }
        if (minl == INT_MAX) return string();
        else return s.substr(mini, minl);
    }
};

/**************************************************** 
 ***    072,Hard,Edit Distance 
 ****************************************************/

/*
Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character
*/

/*
https://leetcode.com/discuss/43398/20ms-detailed-explained-c-solutions-o-n-space
*/

/*
Classic dynamic programing, classical solution using a 2-D matrix.
Consider boundary cases.
The matrix dp[i][j] means the edit distance for s[0, i) and t[0, j), excluding the last character. Here i and j means the length, not the index for the ending string.
so to calculate dp[i][j] we need information for s[i-1] and t[j-1].
For boundary cases:
dp[i][0] = i because changing length-i string to empty string requires i operations. Here we see the convenience of using length as dp's index variable.

We can first write two separate routines for boundary cases i = 0 and j = 0, and then write a nested loop for i >=1 and j >= 1. We can also put them in one loop and take care of boundary cases in if statements.
*/

//Solution 1. Use a 2D array storing the min edit distance between the prefixes of word1 and word2

class Solution {
public:
    int minDistance(string word1, string word2) {
        if(word1.empty()) return word2.size();
        if(word2.empty()) return word1.size();
        int m = word1.size(), n = word2.size();
        vector<vector<int> > dp(m+1, vector<int>(n+1, INT_MAX)); //dp[i][j]: min-distance between word1[0, i) and word2[0, j)
        for(int i = 0; i <= m; ++i) dp[i][0] = i;
        for(int j = 0; j <= n; ++j) dp[0][j] = j;
        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j <= n; ++j) {
                dp[i][j] = min(dp[i-1][j]+1, dp[i][j-1]+1);
                dp[i][j] = min(dp[i][j], dp[i-1][j-1] + (word1[i-1] != word2[j-1]));
            }
        }
        return dp[m][n];
    }
};

/*
Space optimized solution. Because we only need dp[i-1][j], dp[i][j-1] and dp[i-1][j-1] to calcualte dp[i][j], we can use two 1D arrays. cur and next. After each row we swap cur and next.

A even better optimized solution is to use one array curr, and use a temporary variable to store dp[i-1][j-1]. Before updating cur[i], its old value corresponds to dp[i-1][j], and the already updated value in cur[i-1] corresponds to dp[i][j-1]. The key is to find dp[i-1][j-1]. If every step before overwriting cur[i], we store it in a variable pre, so next step (j = j+1) the pre value is exactly dp[i-1][j-1]!. The additional work is to update pre at the current step, we do this by first storing the old cur[j] value in a variable tmp, and in the end assign it to pre.

A final optimization is that, when we see two characters are equal, e.g.
abe cde, we immediately get minD(abe, cde) = minD(ab, cd), instead of doing the minimum among
minD(abe, cd)+1, minD(ab, cde)+1, and minD(ab,cd).
The reason is that we know ajacent entries in the table can only differ by one. i.e. fabs(dp[i+1][j] - dp[i][j]) <= 1. so minD(ab, cd) <= minD(ab,cde)+1, and minD(ab, cd) is guaranteed to be the minimum among the three
For example:
dp(acb, ab) = dp(ac, ab) = 1
dp(acb, ad) = dp(ac, ad) + 1
*/

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<int> dp(n+1, INT_MAX);
        int pre = 0;
        //i = 0 case
        for(int j = 0; j <= n; ++j) dp[j] = j;

        for(int i = 1; i <= m; ++i) {
            pre = dp[0];
            dp[0] = i;
            for(int j = 1; j <= n; ++j) {
                if (word1[i-1] == word2[j-1]) {  //equal case
                    int tmp = dp[j];
                    dp[j] = pre;
                    pre = tmp;
                } else  {
                    int tmp = dp[j];
                    dp[j] = min(min(dp[j]+1, dp[j-1]+1), pre+1);
                    pre = tmp;
                }
            }
        }
        return dp[n];
    }
};

/**************************************************** 
 ***    070,Easy,Climbing Stairs 
 ****************************************************/

/*
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top? 
*/

/// Fibonacci series, dynamic programming (bottom-up)
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        vector<int> sol(n+1, 0);
        sol[1] = 1; sol[2] = 2;
        for (int i = 3; i <= n; ++i)
            sol[i] = sol[i-1] + sol[i-2];
        return sol[n];    
    }
};

// Space optimized version. Only need value for the last 2 steps.
class Solution {
public:
    int climbStairs(int n) {
        if(n <= 2) return n;
        int curr = 0, last = 2, last_last = 1;
        for(int i = 2; i < n; ++i) {
            curr = last + last_last;
            last_last = last;
            last = curr;
        }
        return curr;
    }
};


/**************************************************** 
 ***    068,Hard,Text Justification 
 ****************************************************/

/*
Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly L characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:

[
   "This    is    an",
   "example  of text",
   "justification.  "
]

Note: Each word is guaranteed not to exceed L in length.

click to show corner cases.
Corner Cases:

    A line other than the last line might contain only one word. What should you do in this case?
    In this case, that line should be left-justified.
*/

/*
Two pointers, [i, j) to find the words to be put on each row.
j starts from i, and scans forward until total character count > maxWIdth or j reaches the end.
several cases:

1. If count <= maxWidth that means j reaches the end. We just do left justification, append each word followed by one space.
2. If count > maxWidth, then we retrace one step back. Now [i, j) contains all the words to put on current line. We need to decide on distribution of spaces.
  2.1) if there is only one word, then same as left justification
  2.2) If there is more than one word, then we have ngaps = nword-1 gaps to be filled. We first calculate the remaining number of spots to be filled by spaces, and more-or-less evenly distribute them among ngaps. First r gaps receive one more space than the rest, where r is remaining % ngaps.

Caveat:
1. Do not forget the case where there is only one word! In this case, number of gaps is 0, and division by gaps will result in error!
2. Don't forget the initial space assigned to each gap, so q = remaining/ngaps +1 !.
3. don't forget to append padding spaces for left justification case.
4. Properly initialize/reest the variable storing line contents at the beginning of each loop iteration.
5. the condition after while(count <= maxWidth && j < n) should be (count <= maxWidth), but not (j == n). Because we could have count < maxWidth and j == n at the same time, and this is not reach last row, because j will retrace and leave the last word to the next line, which is the last line.
*/

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        string line;
        if(words.empty()) return result;
        int n = words.size();
        int i = 0, j = 0;  //each row put words[i, j) to the line
        while(i < n) {
           int count = 0; //character count one the current line
           j = i;
           line = words[i]; //should contain at least one word
           count += words[j++].size();
           while(count <= maxWidth && j < n) {
               count += 1+words[j++].size(); //including one leading space
           }
           if(count <= maxWidth) { //reach the last row, then just append words
               for(int k = i+1; k < j; ++k) { //left justified
                   line += " " + words[k];
               }
               line += string(maxWidth-count, ' '); //append padding spaces!
           } else {  //not reach last row, retrace one step back
               count -= 1+words[--j].size();
               int nwords = j-i; //number of words on the line
               int ngaps = nwords-1; //number of gaps on the line
               if(ngaps == 0) { // only one word on the line
                   line += string(maxWidth-count, ' '); //append padding spaces
               } else {
                    int remaining = maxWidth-count; //left over amount to be filled by space
                    //should spread residue to nwords-1 slots more-or-less evenly
                    //first r gaps get q+1, the rest get q (don't forget initial one space)
                    int q = remaining / ngaps + 1, r = remaining % ngaps;
                    for(int k = i+1; k < j; ++k) {
                        if(k-i <= r) line += string(q+1, ' ') + words[k];
                        else line += string(q, ' ') + words[k];
                    }
               }
           }
           result.push_back(line);
           i = j;
        }
        return result;
    }
};


/**************************************************** 
 ***    067,Easy,Add Binary 
 ****************************************************/

/*
Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100". 
*/

// General solution that works works for binary and hex and oct systems, except need to change R to 8 or 16 
class Solution {
public:
    string addBinary(string a, string b) {
        const int R = 2; //radix for binary system (R = 8/16 for oct/hex)
        int m = a.size(), n = b.size();
        int l = max(m, n);
        string c(l, '0');
        int carry(0), sum(0); 
        for (int i = 0; i < l; ++i) {
            int v1 = (i < m) ? char2int(a[m-1-i]) : 0;
            int v2 = (i < n) ? char2int(b[n-1-i]) : 0;
            sum = carry + v1 + v2;
            carry = sum / R;
            sum = sum % R;
            c[l-1-i] = int2char(sum);
        }
        if (carry > 0) c = "1" + c;
        return c;
    }
    
    int char2int(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        return 0;
    }
    
    char int2char(int n) {
        if (n >= 0  && n <= 9)  return n + '0';
        if (n >= 10 && n <= 15) return n - 10 + 'A';
        return '0';
    }
};

/* Another solution using bit operator to calculate sum and carry
            sum = v1 ^ v2 ^ carry;
            carry = (v1 & v2) | (v1 & carry) | (v2 & carry);

// An alternative is use:
            sum = v1 + v2 + carry;
            carry = sum / 2;
            sum %= 2;
*/

class Solution {
public:
    string addBinary(string a, string b) {
        int l1 = a.size(), l2 = b.size();
        int l = max(l1, l2);
        string result(l, '0');
        int sum = 0, carry = 0;
        //i counts from right to left
        for(int i = 0; i < l; ++i) {
            int v1 = (i >= l1) ? 0 : a[l1-i-1] - '0';
            int v2 = (i >= l2) ? 0 : b[l2-i-1] - '0';
            sum = v1 ^ v2 ^ carry;
            carry = (v1 & v2) | (v1 & carry) | (v2 & carry);
            result[l-i-1] = sum + '0';
        }
        if(carry > 0) result = '1' + result;
        return result;
    }
};

/**************************************************** 
 ***    066,Easy,Plus One 
 ****************************************************/

/*
Given a non-negative number represented as an array of digits, plus one to the number.

The digits are stored such that the most significant digit is at the head of the list.
*/

// Optimization: copy digits to result, and then stop when carry == 0

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> result;
        if(digits.empty()) return result;
        int n = digits.size();
        result = digits;
        int carry = 1, sum = 0;
        for(int i = n-1; i >= 0 && carry > 0; i--) {
            sum = digits[i] + carry;
            carry = sum / 10;
            sum %= 10;
            result[i] = sum; //update result
        }
        if(carry > 0) result.insert(result.begin(), 1); //add a leading 1
        return result;
    }
};

/**************************************************** 
 ***    065,Hard,Valid Number 
 ****************************************************/

/*
Validate if a given string is numeric.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true

Note: It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one. 
*/

/*
 * A valid number consists of several fields:
 *    -28.82e-20 
 * 00012222233334444  

 * Fields 0 and 4 are spaces and can appear >=0 times, thus: \s*
 * Field 1 is either plus or minus sign, and can appear zero or one times, thus:  [\+\-]?
 * Field 2 is the coefficient part, can be one of the following:
 * - integers (a sequence of digits) 20348
 * - integers plus a dot: 20345.
 * - floating points: 2.304
 * - dot followed by digits: .234
 * It should not accept a single dot (.). 
 * Depending on whether a dot is the first character we can break it into two cases:
 * - first character is a digit, so the dot and fractional points can be absent, thus: \d+(\.\d*)?
 * - second character is a dot, it has to be followed by at least one digit, thus: \.\d+
 * thus field 2 is: \d+ (\.\d*)? | \.\d+ 
 * Field 3 is the exponential part. It consists of several parts: 
 * - the e/EXPO character: [eE]
 * - the sign (either + or - or missing): [\+\-]?
 * - the exponent as a sequence of numbers (at least one): \d+.
 * field 3 can be absent or appear only one time, thus: ([eE][\+\-]?\d+)?
 * Thus the regular expression for the valid number is:
 *  \s* [\+\-]? (\d+(\.\d*)?|\.\d+) ([eE][\+\-]?\d+)? \s*  (spaces in between are added for clarity and should be removed)
 * 0..0 1  .. 1 2      ..         2 3     ..        3 4..4
 */

// Use finite automaton. Read charater one by one, depending on the current state and character read, jump to the next state
// 9 states,  and 6 types of charaters defined in CharType
// state 0: has only seen spaces so far, expects another space, a digit, a dot, or a sign
// state 1: has read a sign (+/-), expects a digit, or a dot
// state 2: has read a digit in coeffient part, expects another digit, a dot, a e/E, or space
// state 3: has read a dot (.) before reading any digit, only expects a digit as fractional part only
// state 4: has read a dot (.) after reading at least one digit, expects a digit, or e/E, or space
// state 5: has read a e/E in exponent field, expects a sign, or a digit
// state 6: has read a sign in exponent field, expects a digit
// state 7: has read a digit in exponent field, expects another digit, or space
// state 8: has read a trailing space, expects another space      
// Small trick: add a space after string s, so we only need to check if state == 8 in the end. 
// Alternative: not add a space, and instead check if state is one of 2,4,7,8 in the end.

class Solution {
public:
    enum CharType { SPACE=0, DIGIT, DOT, SIGN, EXPO, OTHER };

    bool isNumber(string s) {
        s += ' ';
        initDFA();
        int state = 0;
        for (int i = 0; i < s.size() && state >= 0; ++i)
            state = dfa[state][getType(s[i])];
        
        return state == 8;
    }

    void initDFA() {
        dfa.resize(9, vector<int>(6, -1));
        // state 0: has only seen spaces so far, expects another space, a digit, a dot, or a sign
        dfa[0][SPACE] = 0;
        dfa[0][DIGIT] = 2;
        dfa[0][DOT]   = 3;
        dfa[0][SIGN]  = 1;
        // state 1: has read a sign (+/-), expects a digit, or a dot
        dfa[1][DIGIT] = 2;
        dfa[1][DOT]   = 3;
        // state 2: has read a digit in coeffient part, expects another digit, a dot, a e/E, or space
        dfa[2][SPACE] = 8;
        dfa[2][DIGIT] = 2;
        dfa[2][DOT]   = 4;
        dfa[2][EXPO]  = 5;
        // state 3: has read a dot (.) before reading any digit, only expects a digit as fractional part only
        dfa[3][DIGIT] = 4;
        // state 4: has read a dot (.) after reading at least one digit, expects a digit, or e/E, or space
        dfa[4][SPACE] = 8;
        dfa[4][DIGIT] = 4;
        dfa[4][EXPO]  = 5;
        // state 5: has read a e/E in exponent field, expects a sign, or a digit
        dfa[5][DIGIT] = 7;
        dfa[5][SIGN]  = 6;
        // state 6: has read a sign in exponent field, expects a digit
        dfa[6][DIGIT] = 7;
        // state 7: has read a digit in exponent field, expects another digit, or space
        dfa[7][SPACE] = 8;
        dfa[7][DIGIT] = 7;
        // state 8: has read a trailing space, expects another space
        dfa[8][SPACE] = 8; 
    }

    int getType(char c) {
        if (c == ' ' || c == '\t') return SPACE;
        if (c >= '0' && c <= '9')  return DIGIT;
        if (c == '.')              return DOT;
        if (c == '+' || c == '-')  return SIGN;
        if (c == 'e' || c == 'E')  return EXPO;
        return OTHER;
    }

    vector<vector<int> > dfa;
};


/**************************************************** 
 ***    060,Medium,Permutation Sequence 
 ****************************************************/

/*
The set [1,2,3,…,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):

    "123"
    "132"
    "213"
    "231"
    "312"
    "321"

Given n and k, return the kth permutation sequence.

Note: Given n will be between 1 and 9 inclusive.
*/

/* Solution using modular relation to determine the most significant digit and moving downward. This solution does not print the numbers in lexigraphical order.
 Maintain an array storing whether a particular digit has been used or not (e.g. used[2] denotes char '3'). Use a helper function to find the K-th unused character.
 k-- to make k start from 0
 e.g. n = 4
 1... (3!)  k = 0 - 5 (k / 3! = 0)
 2... (3!)  k = 6 - 11 (k / 3! = 1)
 3... (3!)  k = 12 - 17 (k / 3! = 2)
 4... (3!)  k = 18 - 23 (k / 3! = 3)
Caveats: the next permutation algorithm does not pass here due to TLE: has to move forward one step at a time!
*/

class Solution {
public:
    string getPermutation(int n, int k) {
        int fact = 1;
        for(int i = 1; i <= n; ++i) fact *= i;
        k = (k-1) % fact;
        vector<int> used(n, false);
        string result(n, '0');
        for(int i = 0; i < n; ++i) { //from MSD to LSD
            fact = fact / (n-i);
            int j = k / fact;
            int idx = findUnused(used, j);
            used[idx] = true;
            result[i] = idx + '1';
            k %= fact;
        }
        return result;
    }

    int findUnused(const vector<int>& used, int i) {
        for(int j = 0; j < used.size(); ++j) {
            if(!used[j]) {
                if(i-- == 0) return j;
            }
        }
        return -1;
    }
};

/*
Solution 2 using a bit status number.
Caveat:
 When testring if a digit is unset, use
 !(x & (1 << n)). not ~ , because inverting boolean and inverting bit number are totally different things!
 ! 1 = !(true) = false
 ~ 1 = -2 = true!
*/

class Solution {
public:
    string getPermutation(int n, int k) {
        int fact = 1;
        for(int i = 1; i <= n; ++i) fact *= i;
        k = (k-1) % fact;
        int state = 0; //used state: digit i means whether k+1 has been used
        string result(n, '0');
        for(int i = 0; i < n; ++i) { //from MSD to LSD
            fact = fact / (n-i);
            int j = k / fact;
            int idx = findUnused(state, j);
            state |= (1 << idx);
            result[i] = idx + '1';
            k %= fact;
        }
        return result;
    }

    int findUnused(int state, int i) {
        for(int j = 0; j < 32; ++j) {
            if(!(state & (1 << j))) {
                if(i-- == 0) return j;
            }
        }
        return 32;
    }
};

// Solution 3 using a string storing unused characters, when a character is used, remove the character
// Notice the usage of two STL functions: iota and string::erase

class Solution {
public:
    string getPermutation(int n, int k) {
        string dict(n, '0');
        iota(dict.begin(), dict.end(), '1'); // dict = '1234...n'
        int fact = 1;
        for(int i = 1; i <= n; ++i) fact *= i;
        k = (k-1) % fact;
        string result(n, '0');
        for(int i = 0; i < n; ++i) { //from MSD to LSD
            fact = fact / (n-i);
            int j = k / fact;
            result[i] = dict[j];
            dict.erase(j, 1); //erase j-th character
            k %= fact;
        }
        return result;
    }
};



/**************************************************** 
 ***    058,Easy,Length of Last Word 
 ****************************************************/

/*
Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

For example,
Given s = "Hello World",
return 5. 
*/

// Two pointers, i and j. Scan from right to left
// i is first non-space char, j is first space char after i (right -> left)

class Solution {
public:
    int lengthOfLastWord(string s) {
        int n = s.size();
        //scan from right end to left, find first non-space character
        int i = n-1;
        while (i >= 0 && s[i] == ' ') i--;
        if (i < 0) return 0;
        //scan from i to left, find first space character
        int j = i;
        while(j >= 0 && s[j] != ' ') j--;
        return i-j;
    }
};

/**************************************************** 
 ***    057,Hard,Insert Interval 
 ****************************************************/

/*
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10]. 
*/

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

/// scan intervals from left to right:
// 1. if current interval overlaps with newInterval, then merge the two and update newInterval
// 2. if not overlap, then push-back the one with smaller start time to final array, and make the other one as newInterval.
// Use a tag "inserted" to check if newInterval already inserted. If yes, then no need to perform interval comparison in later step (just copy and paste)

class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        vector<Interval> result;
        if(intervals.empty()) {
            result.push_back(newInterval);
            return result;
        }
        int n = intervals.size();
        bool inserted = false;
        for(int i = 0; i < n; ++i) {
           const Interval& current = intervals[i];
           if(inserted) result.push_back(current);
           else if(newInterval.start <= current.end && current.start <= newInterval.end) { //merge the two
               newInterval.start = min(current.start, newInterval.start);
               newInterval.end = max(current.end, newInterval.end);
           } else { //not overlap
               if(current.start > newInterval.start) {
                   result.push_back(newInterval); //smaller start goes first
                   result.push_back(current);
                   inserted = true; //finshed insertion
               } else {
                   result.push_back(current); //smaller start goes first
               }
           }
        }
        if(!inserted) result.push_back(newInterval);
        return result;
    }

    bool isOverlap(const Interval& a, const Interval& b) {
       return !((a.end < b.start) || (a.start > b.end));
    }
};

/**************************************************** 
 ***    056,Hard,Merge Intervals 
 ****************************************************/

/*
Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18]. 
*/

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

// One pass simple solution after sorting interval array

bool compare_start(const Interval& a, const Interval& b) {
    return a.start < b.start;
}

class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> result;
        if(intervals.empty()) return result;
        int n = intervals.size();
        if(n == 1) return intervals;
        sort(intervals.begin(), intervals.end(), compare_start);
        result.push_back(intervals[0]);
        Interval last = intervals[0];
        for(int i = 1; i < intervals.size(); ++i) {
            const Interval& curr = intervals[i];
            if(curr.start <= last.end) {
                //merge current with last
                last.end = result.back().end = max(curr.end, result.back().end);
            } else {
                result.push_back(curr);
                last = curr;
            }
        }
        return result;
    }
};


// An old solution 
bool compare(const Interval &a, const Interval &b) {
    if(a.start < b.start) return true;
    if(a.start > b.start) return false;
    return a.end < b.end;
}

class Solution {
public:

    vector<Interval> merge(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), compare);
        vector<Interval> s; //stack 
        int n = intervals.size();
        for(int i = 0; i < n; ++i) {
            Interval it = intervals[i];
            while(!s.empty() && isOverlap(s.back(), it)) { //overlap
                it = mergeTwo(s.back(), it);
                s.erase(s.end()-1); //stack pop
            } 
            //now either stack is empty, or there is no overlap
            s.insert(s.end(), it); //stack push
        }
        return s; //return whole stack
    }
    
    bool isOverlap(const Interval& a, const Interval &b) {
        return (a.start <= b.end && b.start <= a.end);
    }
    
    Interval mergeTwo(const Interval &a, const Interval &b) {
        Interval it;
        it.start = min(a.start, b.start);
        it.end = max(a.end, b.end);
        return it;
    }
};

/**************************************************** 
 ***    055,Medium,Jump Game 
 ****************************************************/

/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false. 
*/

/* Solution 1. Maintain a variable (step) for the maximum steps at each position. Scan forward, say the maximum step at position i is step, then we move one step further, the maximum step can be either step-1 (because we moved one step forward), or the maximum step at i+1. Thus
step = max(step-1, nums[i]);
If step = 0, then cannot jump.
*/

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return true;
        if(nums[0] == 0) return false;
        int step = nums[0];
        for(int i = 1; i < n-1; ++i) {
            step = max(step-1, nums[i]);
            if(step <= 0) return false;
        }
        return true;
    }
};

/*
Solution 2. Similar to Solution 1, but Keep a variable (rightEnd) for the maximum reachable index at each position. Scan forward, if the current position is beyond the rightEnd, then cannot jump. If rightEnd exceeds n-1, then can jump.
*/
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return true;
        int rightEnd = 0, i = 0;
        for(int i = 0; i <= rightEnd; i++) {
            rightEnd = max(rightEnd, i + nums[i]);
            if(rightEnd >= n-1) return true;
        }
        return false;
    }
};

/*
Solution 3. Standard BFS, each step, maintain a range [lo, hi] reachable from beginning, then scan all elements in the range, and calculate the newly reachable range as [hi+1, max( nums[i]+i) for all i between lo and hi]. If hi is not increased in the newly range, then cannot jump.
*/
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return true;
        int lo = 0, hi = 0;
        while(hi < n-1) {
           int tmp = hi;
           for(int i = lo; i <= tmp; ++i) {
               hi = max(hi, i+nums[i]);
           }
           if(hi == tmp) return false;
           lo = tmp+1;
        }
        return true;
    }
};

/*
Solution 4. Start from right and scan to left. Find first element reachable to end, and make that element the new end.
e.g. [4 3 4 1 0 2]
search starts from 0, and found 4 reachable to end. Then problem reduces to the [4 3 4] subarray.
*/

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return true;
        int i = n-1, j = 0;
        while(i > 0) {
           j = i-1;
           while(j >= 0 && nums[j] < i-j) { //find first element that can reach to nums[i]
              j--;
           }
           if(j == -1) return false; //not found
           i = j;
        }
        return true;
    }
};

/**************************************************** 
 ***    053,Medium,Maximum Subarray 
 ****************************************************/

/*
Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
the contiguous subarray [4,−1,2,1] has the largest sum = 6.

click to show more practice.
More practice:

If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
*/

// Solution 1. Divide and conquer.
// Find max from left sub array, right sub array, and crossing arrays.
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.empty()) return 0;
        return maxSubArrayAux(nums, 0, nums.size()-1);
    }
    
    int maxSubArrayAux(vector<int>& nums, int lo, int hi) {
        if(lo > hi) return INT_MIN;
        if(lo == hi) return nums[lo]; //only one element
        int mid = lo + (hi - lo) / 2; //break array at mid | mid+1
        int max1 = maxSubArrayAux(nums, lo, mid);
        int max2 = maxSubArrayAux(nums, mid+1, hi);
        int max3 = maxCrossing(nums, lo, hi, mid);
        return max(max(max1, max2), max3);
    }
    
    int maxCrossing(vector<int>& nums, int lo, int hi, int mid) {
        int left_sum = nums[mid], max_left_sum = left_sum;
        int right_sum = nums[mid+1], max_right_sum = right_sum;
        int jleft = mid-1, jright = mid+2;
        while(jleft >= lo) {
            left_sum += nums[jleft];
            max_left_sum = max(max_left_sum, left_sum);
            jleft--;
        }
        while(jright <= hi) {
            right_sum += nums[jright];
            max_right_sum = max(max_right_sum, right_sum);
            jright++;
        }
        return max_left_sum + max_right_sum;
    }
};


/// Solution 2 dynamic programming.
/*
Maximum ending at nums[k] can be obtained from nums[k] and maximum ending at nums[k-1].
1. if max ending at nums[k-1] is positive, then we simply add nums[k] to obtain max ending at nums[k].
2. if max ending at nums[k-1] is negative, then we can discard everything before nums[k], and use nums[k] as max ending at nums[k].
When assigning max_all, using conditional clause (as below) is 4ms faster than using std::max.
*/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.empty()) return 0;
        int max_ending_here = 0, max_all = INT_MIN;
        int n = nums.size();
        for(int i = 0; i < n; ++i) {
            max_ending_here = max_ending_here > 0 ? (max_ending_here + nums[i]) : nums[i];
            if(max_all < max_ending_here) max_all = max_ending_here;
        }
        return max_all;
    }
};

/**************************************************** 
 ***    052,Hard,N-Queens II 
 ****************************************************/

/*
Follow up for N-Queens problem.

Now, instead outputting board configurations, return the total number of distinct solutions.
*/

// Solution 1. Recursive solution.

class Solution {
public:
    int totalNQueens(int n) {
        if(n == 0) return 0;
        int count = 0;
        vector<int> pos(n, -1); //position of queen in row[i], can be between 0 and n-1
        return solveNQueensHelper(0, pos);
    }
    //checking row i
    int solveNQueensHelper(int i, vector<int>& pos) {
        int n = pos.size();
        if(i == n) return 1;
        int count = 0;
        //try position j on row i (no queens will be on the same row)
        for(int j = 0; j < n; ++j) {
           if(canPlace(i, j, pos)) {
              pos[i] = j;
              count += solveNQueensHelper(i+1, pos);
           }
        }
        pos[i] = -1; //reset value
        return count;
    }
    //can place, check if Queen at [i][j] conflicts with queens in previous rows
    bool canPlace(int i, int j, vector<int>& pos) {
        for(int row = 0; row < i; ++row) {
            int col = pos[row];
            if(col == j || fabs(j - col) == i - row) return false;   //same col or diagonal
        }
        return true;
    }
};


// Solution 2. Iterative solution.

class Solution {
public:
    int totalNQueens(int n) {
        if(n == 0) return 0;
        int count = 0;
        vector<int> pos(n, -1); //position of queen in row[i], can be between 0 and n-1
        int i = 0, j = 0;
        while(i >= 0) {
            if(i == n) {
                count++;
                i--; //retrace back
                continue;
            }
            j = pos[i]+1; //move one step to right and try new positions
            while(j < n && !canPlace(i, j, pos)) j++;
            if(j == n) { //tried all possibilities, retrace back
                pos[i] = -1; i--;
                continue;
            }
            //found a possible place, record and move to next row.
            pos[i] = j;  i++;
        }
        return count;
    }

    //can place, check if Queen at [i][j] conflicts with queens in previous rows
    bool canPlace(int i, int j, vector<int>& pos) {
        for(int row = 0; row < i; ++row) {
            int col = pos[row];
            if(col == j || fabs(j - col) == i - row) return false;   //same col or diagonal
        }
        return true;
    }
};

/**************************************************** 
 ***    051,Hard,N-Queens 
 ****************************************************/

/*
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]

*/

/*
Solution 1. Recursive DFS.
use a vector to keep track of the column position of queens in each row.
This way it is guaranteed that no queen are on the same row.
We only need to check if the current queen is on the same column or same diagonal with any previously placed queens.

Use a matrix for string to prestore the solutions, when found solution, update string matrix, push to solution, and reset string matrix back.
*/

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string> > result;
        if(n == 0) return result;
        vector<int> pos(n, -1); //position of queen in row[i], can be between 0 and n-1
        vector<string> solstr(n, string(n, '.'));
        solveNQueensHelper(0, pos, solstr, result);
        return result;
    }
    //checking row i
    void solveNQueensHelper(int i, vector<int>& pos, vector<string>& solstr, vector<vector<string> >& result) {
        int n = pos.size();
        if(i == n) {
            //construct solution
            for(size_t i = 0; i < pos.size(); ++i) {
                solstr[i][pos[i]] = 'Q';
            }
            result.push_back(solstr);
            //reset solstr
            for(size_t i = 0; i < pos.size(); ++i) {
                solstr[i][pos[i]] = '.';
            }
            return;
        }
        //try position j on row i (no queens will be on the same row)
        for(int j = 0; j < n; ++j) {
           if(canPlace(i, j, pos)) {
              pos[i] = j;
              solveNQueensHelper(i+1, pos, solstr, result);
           }
        }
        pos[i] = -1; //reset value
    }
    //can place, check if Queen at [i][j] conflicts with queens in previous rows
    bool canPlace(int i, int j, vector<int>& pos) {
        for(int row = 0; row < i; ++row) {
            int col = pos[row];
            if(col == j || fabs(j - col) == i - row) return false;   //same col or diagonal
        }
        return true;
    }
};

// Solution 2. Iterative solution.

class Solution {
public:
	vector<vector<string> > solveNQueens(int n) {
		vector<vector<string> > ret;
		int irow = 0;
		vector<int> col(n,-1);
		while(irow >= 0) { 
		    if(irow == n) { //found a solution
		        ret.push_back(config2str(col));
		        irow--; //retrace
		    } else {
			    //find next valid column position
			    col[irow] ++;
			    while(col[irow] < n && !isValid(col, irow)) col[irow]++;
			
			    if(col[irow] == n) {  // tried all combinations, retrace
			        col[irow] = -1;
			        irow--; 
    			} else {  //suceeded at k-th step, move to next
    			    irow++;
				}
			}
		}
		return ret;
	}
	
	bool isValid(const vector<int>& col, int irow) { 
		for(int j = 0; j < irow; ++j) {
			if(col[j] == col[irow] || irow - j == std::fabs(col[irow] - col[j])) return false;
		}
		return true; 
	}
	
	vector<string> config2str(const vector<int>& conf) {
		vector<string> ret;
		string str;
		for(int k = 0; k < conf.size(); ++k) { //k-th string
			str.clear();
			for(int j = 0; j < conf.size(); ++j) {
				if(conf[k] == j) str += 'Q';
				else str += '.';
			}
			ret.push_back(str);
		}
		return ret;
	}
};

/**************************************************** 
 ***    049,Medium,Group Anagrams 
 ****************************************************/

// Simplest solution: maintain a map from string (sorted) to a vector of indices who is anagram to the string.
// Process all strings, then check the map and add to result if the vector size is larger than 1

class Solution {
public:
     vector<string> anagrams(vector<string>& strs) {
        vector<string> ret;
        if (strs.empty()) return ret;
        int n = strs.size();
        if (n == 1) return ret;
        map<string, vector<int> > table;
        for (int i = 0; i < n; ++i) {
           string s = strs[i];
           sort(s.begin(), s.end());
           table[s].push_back(i);
        }
        for (map<string, vector<int> >::iterator it = table.begin(); it != table.end(); ++it) {
            if (it->second.size() > 1) {
               for (size_t i = 0; i < it->second.size(); ++i)
                   ret.push_back(strs[it->second[i]]);
            }
        }
        return ret;
    }
};
/*
Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
Return:

[
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
]

Note:

    For the return value, each inner list's elements must follow the lexicographic order.
    All inputs will be in lower-case.
*/

// Solution 1. Using a hash table to store the already found anagrams. Use the sorted string as the key. 68ms.
// For each string in strs, if found in table, then insert to approapriate positions, otherwise, add a new vector to the result, and push the string to that vector.
// Finally, sort each sub-vector

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        if(strs.empty()) return result;
        unordered_map<string, int> dict;

        for(int i = 0; i < strs.size(); ++i) {
            string s = strs[i];
            sort(s.begin(), s.end());
            if(dict.count(s)) { //found anagrams
                result[dict[s]].push_back(strs[i]);
            } else { //new entry
                dict[s] = result.size();
                result.push_back(vector<string>(1, strs[i]));
            }
        }
        for(int i = 0; i < result.size(); ++i) {
            sort(result[i].begin(), result[i].end());
        }
        return result;
    }
};

// Solution 2. 400ms. Not a very efficient solution.
// First sort the strs array by a customized compare function (compare each string's sorted forms). After this step all anagrams are ajacent to each other. Next step scan the array and group anagrams using the isAnagram function. Still need to sort each group in the end.

bool compare(const string& s, const string& t) {
    string ss = s, tt = t;
    sort(ss.begin(), ss.end());
    sort(tt.begin(), tt.end());
    return ss < tt;
}

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        if(strs.empty()) return result;
        sort(strs.begin(), strs.end(), compare);

        for(int i = 0; i < strs.size(); ++i) {
            if(i == 0 || !isAnagram(strs[i], strs[i-1]))
                result.push_back(vector<string>());
            result.back().push_back(strs[i]);
        }
        for(int i = 0; i < result.size(); ++i) {
            sort(result[i].begin(), result[i].end());
        }
        return result;
    }
    bool isAnagram(const string& s, const string& t) {
        if(s.size() != t.size()) return false;
        int n = s.size();
        if(n == 0) return true;
        if(n == 1) return s == t;
        vector<int> dict(26, 0);
        for(auto c : s) dict[c-'a']++;
        for(auto c : t) {
            if(--dict[c-'a'] < 0) return false;
        }
        return true;
    }
};

// Solution 3. TLE. Brute force solution, very inefficient.
// One pass. Construct result as we scan strs, for each string, linearly scan all anagram groups in results. Compare the string with the first entry of the anagram group. If found equal, insert to this group. Otherwise, append a new group to end of results and insert the string to this group.

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        if(strs.empty()) return result;
        for(auto s : strs) {
            bool hasAnagram = false;
            for(int i = 0; i < result.size(); ++i) {
                if(isAnagram(result[i][0], s)) {
                    result[i].push_back(s);
                    hasAnagram = true;
                    break;
                }
            }
            if(!hasAnagram) result.push_back(vector<string>(1, s));
        }
        for(auto s : result) {
            sort(s.begin(), s.end());
        }
        return result;
    }
    bool isAnagram(const string& s, const string& t) {
        if(s.size() != t.size()) return false;
        int n = s.size();
        if(n == 0) return true;
        if(n == 1) return s == t;
        vector<int> dict(26, 0);
        for(auto c : s) dict[c-'a']++;
        for(auto c : t) {
            if(--dict[c-'a'] < 0) return false;
        }
        return true;
    }
};




/**************************************************** 
 ***    047,Medium,Permutations II 
 ****************************************************/

/*
Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[1,1,2], [1,2,1], and [2,1,1]. 
*/

// Solution 1. Use next permutation algorithm to print permutations in lexigraphical order (see 031)
// Copied from 046_permutation.cc

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        sort(nums.begin(), nums.end());
        result.push_back(nums);
        while(nextPermutation(nums)) result.push_back(nums);
        return result;
    }
    bool nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int k = n-2, l = n-1;
        while(k >= 0 && nums[k] >= nums[k+1]) k--;
        //k is the last k such that nums[k] < nums[k+1]
        if(k == -1) return false;
        while(l > k && nums[l] <= nums[k]) l--;
        //l is the last l such that nums[l] > nums[k]
        //swap nums[k] and nums[l]
        swap(nums[k], nums[l]);
        //sort numbers after k
        int i = k+1, j = n-1;
        while(i < j) swap(nums[i++], nums[j--]);
        return true;
    }
};

// Solution 2. Recursive solution with swapping adapted from 046_permutations.cc. 
// To deal with duplicated entries, we can't use something simpler such as checking current to be exchanged ia equal to previously exchanged one, because the subarray maybe unsorted, for example, given aabbccd, and after a while we have bcd|caba, and the second part is unsorted. 
// Unless using a set structure, there is no way of preventing 'c' to be swapped with second 'a', because the previous is a 'b'.

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        dfs(nums, 0, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<vector<int> >& result) {
        int n = nums.size();
        if(i == n) {
            result.push_back(nums);
            return;
        }
        unordered_set<int> used;
        for(int k = i; k < n; ++k) {
            if(used.count(nums[k])) continue; //ignore duplicates that are already used
            used.insert(nums[k]); //insert to used table
            swap(nums[i], nums[k]);
            dfs(nums, i+1, result);
            swap(nums[i], nums[k]);
        }
    }
};

// Solution 3. Recursive solution adapted from Solution 3 in 046_permutations.cc. using a bit number representing status. Adapted to duplicated cases. Use a number "last" to store the last number used. When scanning forwards, skip the numbers equal to last as well.

class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        int state = 0; //bit states for 0 to n-1 
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<int> tmp(n, 0);
        dfs(nums, 0, tmp, result, state);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result, int state) {
        int n = nums.size();
        if(i == n) {
            result.push_back(tmp);
            return;
        }
        int last = INT_MIN; // assume no numbers are INT_MIN
        for(int k = 0; k < n; ++k) { //try all possible numbers
            if((state & (1 << k)) || nums[k] == last) continue; //already used, or duplicate entries
            last = tmp[i] = nums[k]; //use nums[k]
            state |= (1 << k);
            dfs(nums, i+1, tmp, result, state);
            state &= ~(1 << k); //retrace
        }
    }
};

// Solution 4. An iterative solution. Similar to that of 046_permutations. Only difference is that when we scan forward, if we see a used character OR a character that is the same as previous one, then we continue searching.
// A tricky case is when there is no previous character. So need to carefully write the conditiont in while loop.

class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        int n = nums.size(), i(0);
        sort(nums.begin(), nums.end()); //first sort array
        vector<bool> used(n, false); //whether i-th number has been used
        vector<int> pos(n, -1); //position in nums for the number chosen for i-th position in permutation sequence
        while(i >= 0) { //check i-th position
            if(i == n) {
                vector<int> tmp(n, 0);
                for(int k = 0; k < n; ++k) tmp[k] = nums[pos[k]];
                result.push_back(tmp);
                i--; //retrace
                continue;
            }
            //find next unused number for i-th selection
            if(pos[i] >= 0) used[pos[i]] = false; //unset
            int tmp_pos = pos[i];
            pos[i]++;
            while(pos[i] < n && (used[pos[i]] || (tmp_pos >= 0 && nums[pos[i]] == nums[tmp_pos]))) pos[i]++;
            if(pos[i] == n) { //no numbers left
                pos[i] = -1;
                i--; //retrace
                continue;
            }
            used[pos[i]] = true;
            //find next pos[i]
            i++;
        }
        return result;
    }
};


/**************************************************** 
 ***    046,Medium,Permutations 
 ****************************************************/

/*
Given a collection of numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1]. 
*/

// Solution 1. Use next permutation algorithm to print permutations in lexigraphical order (see 031)
// use a tag to indicate the status of permutation. If reaching the last permutation (descending order), return false. 
// Also works for cases when duplicated entries exist
// Caveats: 
// 1. If use a counter to print exactly n! permutations, then does not for cases where duplicated entries exist!
// 2. array should be sorted in the beginning!

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        sort(nums.begin(), nums.end()); //first sort the array!
        result.push_back(nums);
        while(nextPermutation(nums)) result.push_back(nums);
        return result;
    }
    bool nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int k = n-2, l = n-1;
        while(k >= 0 && nums[k] >= nums[k+1]) k--;
        //k is the last k such that nums[k] < nums[k+1]
        if(k == -1) return false;
        while(l > k && nums[l] <= nums[k]) l--;
        //l is the last l such that nums[l] > nums[k]
        //swap nums[k] and nums[l]
        swap(nums[k], nums[l]);
        //sort numbers after k
        int i = k+1, j = n-1;
        while(i < j) swap(nums[i++], nums[j--]);
        return true;
    }
};

// Solution 2. Recursive solution using swapping. Does not work for duplicated cases. Developing a method that deals with duplicated cases are not straightforward, because the array order is destructed during the swapping! One hack is to introduce a table storing used elements, and avoid using them again in the same level of dfs search (see 047)
// Note that this method does not print the permutations in lexigraphical order!

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        dfs(nums, 0, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<vector<int> >& result) { 
        int n = nums.size();
        if(i == n) {
            result.push_back(nums);
            return;
        }
        for(int k = i; k < n; ++k) {
            swap(nums[i], nums[k]);
            dfs(nums, i+1, result);
            swap(nums[i], nums[k]);
        }
    }
};

// Solution 3. Recursive solution, each time take a number, use a bit status number indicating which number has been taken. Can be extended to duplicated cases (see 047).
// Some bit operators:
// checking if k-th number is used: if(state & (1 << k))
// set the tag for the k-th number: state != (1 << k)
// unset the tag for the k-th number: state &= ~(1 << k)

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        int state = 0; //bit states for 0 to n-1 
        int n = nums.size();
        vector<int> tmp(n, 0);
        dfs(nums, 0, tmp, result, state);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result, int state) {
        int n = nums.size();
        if(i == n) {
            result.push_back(tmp);
            return;
        }
        for(int k = 0; k < n; ++k) { //try all possible numbers
            if(state & (1 << k)) continue; //already used
            tmp[i] = nums[k]; //use nums[k]
            state |= (1 << k);
            dfs(nums, i+1, tmp, result, state);
            state &= ~(1 << k); //retrace
        }
    }
};

// Solution 4. An iterative solution using O(n) space to track the status of each number, and another O(n) space to record the positions of each number used.

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        int n = nums.size(), i(0);
        vector<bool> used(n, false); //whether i-th number has been used
        vector<int> pos(n, -1); //position in nums for the number chosen for i-th position in permutation sequence
        while(i >= 0) { //check i-th position
            if(i == n) {
                vector<int> tmp(n, 0);
                for(int k = 0; k < n; ++k) tmp[k] = nums[pos[k]];
                result.push_back(tmp);
                i--; //retrace
                continue;
            }
            //find next unused number for i-th selection
            if(pos[i] >= 0) used[pos[i]] = false; //unset
            pos[i]++;
            while(pos[i] < n && used[pos[i]]) pos[i]++;
            if(pos[i] == n) { //no numbers left
                pos[i] = -1;
                i--; //retrace
                continue;
            }
            used[pos[i]] = true;
            //find next pos[i]
            i++;
        }
        return result;
    }
};



/**************************************************** 
 ***    045,Hard,Jump Game II 
 ****************************************************/

/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)
*/

/*
Solution 1. Standard BFS, each step, maintain a range [lo, hi] reachable from beginning, then scan all elements in the range, and calculate the newly reachable range as [hi+1, max( nums[i]+i) for all i between lo and hi]. If hi is not increased in the newly range, then cannot jump.
*/

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return 0;
        int lo = 0, hi = 0;
        int step = 0;
        while(hi < n-1) {
           int tmp = hi;
           for(int i = lo; i <= tmp; ++i) {
               hi = max(hi, i+nums[i]);
           }
           if(hi == tmp) return -1;
           lo = tmp+1;
           step ++;
        }
        return step;
    }
};


/**************************************************** 
 ***    044,Hard,Wildcard Matching 
 ****************************************************/

/*
Implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false
*/

/*
See 
https://leetcode.com/discuss/52274/three-solutions-iterative-16ms-180ms-modified-recursion-88ms

Solution 1. Standard DP solution with a 2D vector. Slow.
When we see a '*' it can match nothing, hence dp[i][j-1], or it can match at least one character, hence dp[i-1][j].
*/

class Solution {
public:
    bool isMatch(string s, string p) {
        if(p == "") return s == "";
        //s can be "", p cannot
        int m = s.size(), n = p.size();
        vector<vector<bool> > dp(m+1, vector<bool>(n+1, false)); //match[i][j]: s[0..i-1] matches p[0..j-1]
        dp[0][0] = true; // "" matches ""
        //matching p with ""
        for(int j = 1; j <= n && p[j-1] == '*'; ++j)
            dp[0][j] = true;
        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(p[j-1] != '*') dp[i][j] = dp[i-1][j-1] && matchHelper(s[i-1], p[j-1]);
                else dp[i][j] = dp[i-1][j] || dp[i][j-1];
            }
        }
        return dp[m][n];
    }

    bool matchHelper(char t, char p) {
        return p == '?' || p == t;
    }
};

/*
Solution 2. Need further analysis
*/

class Solution {
public:
    bool helper(const string &s, const string &p, int si, int pi, int &recLevel)
    {
        int sSize = s.size(), pSize = p.size(), i, curLevel = recLevel;
        bool first=true;
        while(si<sSize && (p[pi]==s[si] || p[pi]=='?')) {++pi; ++si;} //match as many as possible
        if(pi == pSize) return si == sSize; // if p reaches the end, return
        if(p[pi]=='*')
        { // if a star is met
            while(p[++pi]=='*'); //skip all the following stars
            if(pi>=pSize) return true; // if the rest of p are all star, return true
            recLevel++;
            for(i=si; i<sSize; ++i)
            {   // then do recursion
                if(p[pi]!= '?' && p[pi]!=s[i]) continue;
                if(helper(s, p, i+1, pi+1, recLevel)) return true;
                if(recLevel>curLevel+1) return false; // if the currently processed star is not the last one, return
            }
        }
        return false;
    }

    bool isMatch(string s, string p) {
        int recLevel = 0;
        return helper(s, p, 0, 0, recLevel);
    }
};

/*
Solution 3. An elegant greedy solution from Yu's coding garden. Need further study.
*/



/**************************************************** 
 ***    043,Medium,Multiply Strings 
 ****************************************************/

/*
Given two numbers represented as strings, return multiplication of the numbers as a string.

Note: The numbers can be arbitrarily large and are non-negative.
*/

/// Just minic the elementary school multiplication method
///      1 2 3 4   (num2, outer loop)
///    x   5 6 7   (num1, inner loop)
/// -------------
///      8 6 3 8
///    7 4 0 4
///  6 1 7 0
/// -------------
///  6 9 9 6 7 8
/// If nums1 and num2 have l1 and l2 digits, without carry over, the product will have l1+l2-1 digits. In this way, product of num1[i] and num2[j] should be aligned to num[i+j].
/// Start from the bottom up. Update the result in-place (instead of creating intermediate strings to store the products)
/// each time inner loop is done, the carry should go to result[i-1] or additional carry digit.

class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0") return "0";
        int l1 = num1.size(), l2 = num2.size();
        string result(l1+l2-1, '0'); // result has l1+l2-1 digits
        int sum = 0, carry = 0;
        for(int i = l1-1; i >= 0; --i) {
            carry = 0;
            for(int j = l2-1; j >= 0; --j) {
                sum = (num1[i] - '0')*(num2[j] - '0') + (result[i+j] - '0') + carry;
                carry = sum / 10;
                sum %= 10;
                result[i+j] = sum + '0';
            }
            if(carry > 0) {
                if(i > 0) result[i-1] = carry + '0'; 
                else result = char(carry + '0') + result;
            }
        }
        
        return result;
    }
};

// Another solution, create an intemediate string for products, shift the products to correct positions by appending proper number of zeroes, and add products together. Optimization on the for loops, so that roughly strings of similar lengths are added. But still very slow ...
class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0") return "0";
        int l1 = num1.size(), l2 = num2.size();
        string result = "0";
        for(int k = 0; k < l1+l2-1; ++k) {
            for(int i = max(0, k-l2+1); i <= min(k, l1-1); ++i) {
                int j = k-i;
                char c1 = num1[l1-i-1], c2 = num2[l2-j-1];
                string prod = num2str((c1-'0')*(c2-'0'));
                prod.append(k, '0');
                result = add(result, prod);
            }
        }
        return result;
    }
    
    string num2str(int num) {
        if(num == 0) return "0";
        string result;
        while(num) {
            result = char(num % 10 + '0') + result;
            num /= 10;
        }
        return result;
    }

    string add(const string& num1, const string& num2) {
        int l1 = num1.size(), l2 = num2.size();
        int l = max(l1, l2);
        string result(l, '0');
        int sum = 0, carry = 0;
        for(int i = 0; i < l; ++i) {
            if(i >= l1) sum = (num2[l2-i-1] - '0') + carry;
            else if(i >= l2) sum = (num1[l1-i-1] - '0') + carry;
            else sum = (num1[l1-i-1]-'0') + (num2[l2-i-1]-'0') + carry;
            carry = sum / 10;
            sum %= 10;
            result[l-i-1] = sum + '0';
         }
         if(carry == 1) result = '1' + result;
         return result;
    }
};

// A better solution by multiplying string to each integer number, and adding the result together. The key is function:
// string multiply(const string& num, int d)

class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0") return "0";
        string result = "0";
        if(num1.size() < num2.size()) num1.swap(num2); //longer one first
        int l1 = num1.size(), l2 = num2.size();
        for(int i = 0; i < l2; ++i) {
            string prod = multiply(num1, num2[l2-i-1]-'0');
            prod.append(i, '0');
            result = add(prod, result);
        }
        return result;
    }
    
    string num2str(int num) {
        if(num == 0) return "0";
        string result;
        while(num) {
            result = char(num % 10 + '0') + result;
            num /= 10;
        }
        return result;
    }

    string multiply(const string& num, int d) {
        if(d == 0) return "0";
        else if(d == 1) return num;
        int n = num.size();
        string result(n, '0');
        int sum = 0, carry = 0;
        for(int i = 0; i < n; ++i) {
            sum = (num[n-i-1] - '0')*d + carry;
            carry = sum / 10;
            sum %= 10;
            result[n-i-1] = sum + '0';
        }
        if(carry > 0) result = char(carry + '0') + result;
        return result;
    }

    string add(const string& num1, const string& num2) {
        int l1 = num1.size(), l2 = num2.size();
        int l = max(l1, l2);
        string result(l, '0');
        int sum = 0, carry = 0;
        for(int i = 0; i < l; ++i) {
            if(i >= l1) sum = (num2[l2-i-1] - '0') + carry;
            else if(i >= l2) sum = (num1[l1-i-1] - '0') + carry;
            else sum = (num1[l1-i-1]-'0') + (num2[l2-i-1]-'0') + carry;
            carry = sum / 10;
            sum %= 10;
            result[l-i-1] = sum + '0';
         }
         if(carry == 1) result = '1' + result;
         return result;
    }
};

/**************************************************** 
 ***    042,Hard,Trapping Rain Water 
 ****************************************************/

/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

For example,
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6. 
*/

/*
We notice that the amount of water trapped at position[i] is bounded by the *lower* of the peak position at its left and peak position at its right. This has suggested a two-way search, instead of single-direction scan. We use two pointers, l and r, initially at the two boundaries of array. Then, the water level is limited by the lower of hl = height[l] and hr = height[r]. We move from the lower side towards the other side., here we assume it is the left side. We also keep track of the current water level at each position. Two cases:
1) if we see a higher point than hl. this will raise the water level to the new height. No water can be trapped here.
2) if we see a lower point than hl, then water will be trapped here and the amount is the difference between current water level and current height at this position.

Every time we move one step, we compare height[l] and height[r], and we always move from the lower side until the two meets.

Caveats:
store height[l] and height[r] as temporary hl and hr, so that when l or r moves, we are comparing to the old value of hl and hr. We need to properly update hl and hr before proceeding to next step.

One while loop.
*/

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int i(0), j(n-1);
        int sum(0);

        int l = i, r = j;
        while (i < j-1) {
            int level = min(height[l], height[r]);
            if (height[l] < height[r]) { //left side lower
                i++;
                if (height[i] < level) sum += level - height[i];
                else l = i;
            } else { //right side lower
                j--;
                if (height[j] < level) sum += level - height[j];
                else r = j;
            }
        }
        return sum;
    }
};


/// Another solution using nested while loops.
/// Two pointers on each end (l, r).
/// Maintain the current minimum water level as level
/// Scan from two sides until l and r meet, collect water amounts at each position
/// Given l and r, the minimum water level should be level = min(height[l], height[r])
/// Always scan from the lower side (between l and r) because it determines the current water level
/// When the encountered height is below level, then collect the difference and add to water amount
/// When the encountered height is above level, no water can be stored at this point. But the water level can rise (determined by minimum of this height and height of other end), so simply update level.
/// Use nested while loops

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n <= 2) return 0;
        int l(0), r(n-1);
        int level(0), water(0);
        while(l < r) {
            level = min(height[l], height[r]);
            if(height[l] < height[r]) { //left side lower
                while(++l < r && height[l] <= level) water += (level-height[l]);
            } else {
                while(--r > l && height[r] <= level) water += (level-height[r]);
            }
        }
        return water;
    }
};

/**************************************************** 
 ***    041,Hard,First Missing Positive 
 ****************************************************/

/*
Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space. 
*/

/* Solution with O(1) space and O(n) time. Uses nums itself as the table. When we find a positive integer i, we should put it in the right position nums[i-1], and put original values there in correct positions as well. This requires a while loop with swap functions. For an array of n numbers, it is guaranteed that the missing positive lies between 1 and n+1. When it is between 1 and n, then at least one entry in nums is not filled properly, and we return that values. When it is n+1, then all entries are filled properly, and we simply return n+1.
Think of indices as mapping nums[i] => i+1.
Scan left to right, only perform swapping when value is within [1 .. N], and the destination does not have correct indices (nums[t-1] != t).s
Caveats:
1. when the destination already has the correct numbers, do not swap. This will avoid an infinite while loop. e.g. 1 1
2. return i+1, n+1.
*/

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        //nums[i] should be i+1
        for(int i = 0; i < n; ++i) {
            int t = nums[i];
            while(t > 0 && t <= n && nums[t-1] != t)
               swap(nums[t-1], t);
        }
        for(int i = 0; i < n; ++i) {
           if(nums[i] != i+1) return i+1;
        }
        return n+1;
    }
};


/**************************************************** 
 ***    040,Medium,Combination Sum II 
 ****************************************************/

/*
Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:

    All numbers (including target) will be positive integers.
    Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
    The solution set must not contain duplicate combinations.

For example, given candidate set 10,1,2,7,6,1,5 and target 8,
A solution set is:
[1, 7]
[1, 2, 5]
[2, 6]
[1, 1, 6]
*/

// Notice the difference between this and problem 039? Here it is "collection" while 039 is "set", which means that here C can have duplicates.

// Solution 1. Iterative solution. Similar to 039, except need to avoid choosing duplicates again, also should only choose one number once.
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int> > result;
        int n = candidates.size();
        if(n == 0) return result;
        sort(candidates.begin(), candidates.end());
        vector<int> tmp;
        dfs(candidates, 0, target, tmp, result);
        return result;
    }
    void dfs(vector<int>& candidates, int i, int target, vector<int>& tmp, vector<vector<int> >& result) {
        if(target == 0) {
            result.push_back(tmp);
            return;
        }
        int n = candidates.size();
        if(i == n || target < candidates[i]) return;
        tmp.push_back(0);
        //choose any number from i to n.
        for(int j = i; j < n; ++j) {
            if(j > i && candidates[j] == candidates[j-1]) continue; //avoid duplicates
            tmp.back() = candidates[j];
            dfs(candidates, j+1, target-candidates[j], tmp, result); //j+1: choose the number only once.
        }
        tmp.pop_back();
    }
};


/**************************************************** 
 ***    039,Medium,Combination Sum 
 ****************************************************/

/*
Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

Note:

    All numbers (including target) will be positive integers.
    Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
    The solution set must not contain duplicate combinations.

For example, given candidate set 2,3,6,7 and target 7,
A solution set is:
[7]
[2, 2, 3]
*/

// Solution 1. Recursive solution. Need to sort the number first. Use the fact that all numbers are positive, terminate when target < current number.
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int> > result;
        int n = candidates.size();
        if(n == 0) return result;
        sort(candidates.begin(), candidates.end());
        vector<int> tmp;
        dfs(candidates, 0, target, tmp, result);
        return result;
    }
    void dfs(vector<int>& candidates, int i, int target, vector<int>& tmp, vector<vector<int> >& result) {
        int n = candidates.size();
        if(i == n || target < candidates[i]) return;
        tmp.push_back(0);
        //choose any number from i to n.
        for(int j = i; j < n; ++j) {
            tmp.back() = candidates[j];
            if(target == candidates[j]) result.push_back(tmp);
            else dfs(candidates, j, target-candidates[j], tmp, result);
        }
        tmp.pop_back();
    }
};

// Solution 2. An old iterative solution. (faster)
class Solution {
public:
	vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
		vector<vector<int> > ret;
		if(candidates.empty()) return ret;
		
		vector<int> sorted = sort(candidates);
	
		//maximum possible numbers target/ min(sorted)
		int n = sorted.size();
		int csize = std::ceil(target/sorted[0]); //no zero!
		vector<int> choice(csize, -1); //stores the indices of a solution in sorted array
		int k = 0; // the k-th number
		int sum = 0; // accumulated sum
		while(k >= 0) {
			if(k == csize) { // target > sums
				k--;
				continue;
			}
			if(choice[k] == -1) { //first time for k-th number
				choice[k] = ((k > 0) ? choice[k-1] : 0); //start from same number before
			} else { //not the first time
				int prev = sorted[choice[k]];
				sum -= prev; //remove sum
				choice[k] ++;
			}
		
			if(choice[k] == n) { // searched till the end
			    choice[k] = -1; //reset
				k--;
				continue;
			}
			//found one
			sum += sorted[choice[k]]; //update sum
			
			//sum exceeding or equal to target
			if(sum >= target) {
				if(sum == target) ret.push_back(construct(choice, sorted));
				sum -= sorted[choice[k]];
				choice[k] = -1;
				k--;
			} else { //check next number
				k++;
			}
		}
		return ret;
	}
	
	//construct vector from choices
	vector<int> construct(const vector<int>& choice, const vector<int>& sorted) {
		vector<int> ret;
		for(int j = 0; j < choice.size(); ++j) {
			if(choice[j] != -1) ret.push_back(sorted[choice[j]]);
			else break; //can break if found an invalid -1 entry
		}
	return ret;
	}
	//insertion sort
	vector<int> sort(vector<int>& num) {
		vector<int> sorted = num;
		int n = sorted.size();
		int i, j;
		for(i = 1; i < n; ++i) {
			j = i;
			int key = sorted[j];
			while( j >= 1 && sorted[j-1] > key) {
				sorted[j] = sorted[j-1]; //shift to right by 1
				j--;
			}
			sorted[j] = key;
		}
		return sorted;
	}
};


/**************************************************** 
 ***    038,Easy,Count and Say 
 ****************************************************/

/*
The count-and-say sequence is the sequence of integers beginning as follows:
1, 11, 21, 1211, 111221, ...

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.

Given an integer n, generate the nth sequence.

Note: The sequence of integers will be represented as a string. 
*/

/// Iterative solution, can place the countAndSay(string&) function directly into for loop to reduce unecessary function call cost
// Caveat: in num2str, should be res = c + res, not res += c + res;

class Solution {
public:
    string countAndSay(int n) {
        string res = "1";
        for(int i = 1; i < n; ++i) {
            res = countAndSay(res);
        }
        return res;
    }
    
    string countAndSay(const string& str) {
        int n = str.size();
        int count = 1;
        string res;
        for(int i = 1; i < n; ++i) {
            if(str[i] == str[i-1]) count++;
            else {
                res += num2str(count) + str[i-1];
                count = 1; //new character
            }
        }
        res += num2str(count) + str[n-1];
        return res;
    }

    string num2str(int n) {
        if(n == 0) return "0";
        string res;
        while(n) {
            res = char(n % 10 + '0') + res;
            n /= 10;
        }
        return res;
    }
};

/// An old solution, use the last string, and scan from left to right to find the number of duplicated entries, and append count as string
class Solution {
public:
    string countAndSay(int n) {
        if (n <= 0) return "";
        if (n == 1) return "1";
        string s = countAndSay(n-1);
        string ret;
        int size = s.size();
        int i = 0, j = 0;
        char c = '\0';
        while(i < size) {
            char c = s[i];
            while(j < size && s[j] == c) j++;
            int cnt = j-i;
            ret += num2str(cnt) + c;
            i = j;
        }
        return ret;
    }
    string num2str(int n) {
        string ret;
        while(n) {
            ret = char('0' + (n % 10)) + ret;
            n /= 10;
        }
        return ret;
    }

};

/**************************************************** 
 ***    037,Hard,Sudoku Solver 
 ****************************************************/

/*
Write a program to solve a Sudoku puzzle by filling the empty cells.

Empty cells are indicated by the character '.'.

You may assume that there will be only one unique solution.
*/

/*
DFS backtracking. Using a helper function canPlace (44ms).
Two passes: first pass initializes state, second pass do dfs and fills empty cells.

Have dfs return true or false so that once a solution is find, terminate search immediately.

Caveats:
1. numbers start from 1, not 0.
2. when to terminate? i == 9, not j == 9!. 
*/

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        dfs(board, 0, 0);
    }
    bool dfs(vector<vector<char> >& board, int i, int j) {
        //try all possible choices
        if(i == 9) return true;
        int inext = (j == 8) ? i+1 : i;
        int jnext = (j == 8) ? 0 : j+1;
        //already filled, just jump to next
        if(board[i][j] != '.') return dfs(board, inext, jnext);
        //only try when board[i][j] is '.'
        for(char c = '1'; c <= '9'; c++) {
            if(canPlace(board, i, j, c)) {
                board[i][j] = c;
                if(dfs(board, inext, jnext)) return true;
            }
            board[i][j] = '.'; //reset back to '.'
        }
        return false; //tried all possibilities
    }

    bool canPlace(vector<vector<char> >& board, int i, int j, char c) {
        for(int irow = 0; irow < 9; irow++)
            if(irow != i && board[irow][j] == c) return false;
        
        for(int jcol = 0; jcol < 9; jcol++)    
            if(jcol != j && board[i][jcol] == c) return false;
        
        int iblk = i-i%3, jblk = j-j%3; //block offset
        for(int l = 0; l < 9; l++) { // try all entries within the block
            int irow = iblk + l/3, jcol = jblk + l%3;
            if(irow != i && jcol != j && board[irow][jcol] == c) return false;
        }
        return true;
    }
};

/*
Solution 2. Use three bits vectors indicating states for rows, colums, and blocks (8ms).

bit negation takes 4ms longer time, so use
  if( state & ..) continue;
instead of using 
  if(! (state & ..)) { ... }
results in 4ms reduction of runtime (12ms => 8ms)
*/

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        row.resize(9, 0); col.resize(9, 0); block.resize(9, 0); 
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j) {
                if(board[i][j] != '.') {
                    int state = 1 << (board[i][j] - '1');
                    row[i] |= state;
                    col[j] |= state;
                    block[i/3*3+j/3] |= state;
                }
            }
        }
        dfs(board, 0, 0);
    }
    bool dfs(vector<vector<char> >& board, int i, int j) {
        //try all possible choices
        if(i == 9) return true;
        int inext = (j == 8) ? i+1 : i;
        int jnext = (j == 8) ? 0 : j+1;
        //already filled, just jump to next
        if(board[i][j] != '.') return dfs(board, inext, jnext);
        //only try when board[i][j] is '.'
        int k = i/3*3+j/3;
        int state = 1;
        for(char c = '1'; c <= '9'; c++, state <<= 1) {
            if(state & (row[i] | col[j] | block[k])) continue;
            board[i][j] = c;
            row[i] |= state; col[j] |= state;  block[k] |= state;
            if(dfs(board, inext, jnext)) return true;
            row[i] &= ~state; col[j] &= ~state;  block[k] &= ~state; //reset states
            board[i][j] = '.'; //reset back to '.'
        }
        return false; //tried all possibilities
    }

    vector<int> row, col, block; //bit status array
};

/**************************************************** 
 ***    036,Easy,Valid Sudoku 
 ****************************************************/

/* Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.

A partially filled sudoku which is valid.

Note:
A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated. 

*/

/// Check each row, column and block, record the state of each check.
/// Can use a single integer to record the state, using bit operations
///  1  1  1  1  1  1  1  1  1
/// '9'       ...           '1'
/// caveat: when calculating i/j index based on block index, 3*(ib/3)+jb/3 != (3*ib+jb)/3 
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int state = 0;

        //check rows
        for (int ir = 0; ir < 9; ++ir) {
            state = 0;
            for (int jc = 0; jc < 9; ++jc) {
                char c = board[ir][jc];
                if(c == '.') continue;
                int x = 1 << (c -'0');
                if (state & x) return false;
                state |= x;
            }
        }
        //check columns
        for (int jc = 0; jc < 9; ++jc) {
            state = 0;
            for (int ir = 0; ir < 9; ++ir) {
                char c = board[ir][jc];
                if(c == '.') continue;
                int x = 1 << (c -'0');
                if (state & x) return false;
                state |= x;
            }
        }
        //check blocks
        for (int ib = 0; ib < 9; ++ib) {
            state = 0;
            for (int jb = 0; jb < 9; ++jb) {
                char c = board[3*(ib/3)+jb/3][3*(ib%3)+jb%3];
                if(c == '.') continue;
                int x = 1 << (c -'0');
                if (state & x) return false;
                state |= x;
            }
        }
        return true;
    }
};

//Another solution using 3 bit vectors
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<int> row(9, 0), col(9, 0), block(9, 0); //bit status array
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j) {
                if(board[i][j] != '.') {
                    int k = i/3*3 + j/3;
                    int state = 1 << (board[i][j] - '1');
                    if(state & (row[i] | col[j] | block[k])) return false;
                    row[i] |= state;
                    col[j] |= state;
                    block[k] |= state;
                }
            }
        }
        return true;
    }
};


/**************************************************** 
 ***    035,Medium,Search Insert Position 
 ****************************************************/

/*
Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0
*/

// Binary search. Loop invariant:
// nums[0 .. lo-1] < target, nums[hi+1, n) > target, nums[lo, hi] TBD
// If found, return index. If not found, return position lo, because when out of while loop we have lo=hi+1, and target is between nums[hi] and nums[lo].

class Solution {
    
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        int lo(0), hi(n-1), mid(0);
        while(lo <= hi) {
            mid = lo + (hi-lo)/2;
            if(target == nums[mid]) return mid;
            if(target < nums[mid]) hi = mid-1;
            else lo = mid+1;
        }
        return lo;
    }
}; 

/**************************************************** 
 ***    033,Hard,Search in Rotated Sorted Array 
 ****************************************************/

/*
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.
*/

/*
Binary search. The array can be broken into two parts, 
for example, [4 5 6 7 0 1 2], first part is 4-7, second part is 0-2. If array is unrotated, then only first part exists (corner case). 
There are three anchor points, lo, hi, and mid.
First determine whether mid is in first half or second half. Mid is in first half iff nums[mid] >= nums[lo] (we can't use comparison between mid and hi, i.e. nums[mid] > nums[hi] because a corner case where array is not rotated has nums[mid] < nums[hi], but still mid is in first half.

1. If mid is in first half, we know that nums[mid] >= nums[lo] (could be equal because mid can be lo, when hi = lo+1), if target falls between the two, then the index has to be between lo and mid. Otherwise, it is between mid and hi.
2. If mid is in second half, we know that nums[mid] <= nums[hi] (could be equal because mid can be hi, when hi = lo), if target falls between the two, then the index has to be between mid and hi. Otherwise, it is between lo and mid.

Difference between finding target and finding minimum:
1. for finding minimum, we let lo < hi, terminate at lo == hi, and return nums[lo]
   for finding target, we let lo <= hi, return as soon as values are found. If not found, terminate at lo > hi.
2. both involve one corner case, where array is not rotated. For find min, just return nums[lo], for search target, we need to carefully design while loop so that it also works for corner cases. Thus we compare nums[mid] and nums[lo], rather than nums[hi]. In find min case, we eliminate corner case upfront, so we compare nums[mid] with nums[hi]. Also, since we could end up mid = lo (when hi and lo differ by one), and nums[lo] will = nums[mid] causing problems, so it is safer to compare with nums[hi].
*/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int lo(0), hi(n-1);
        while(lo <= hi) {
            int mid = lo + (hi-lo) / 2;
            if(target == nums[mid]) return mid;
            if (nums[mid] >= nums[lo]) {
                if(target >= nums[lo] && target < nums[mid]) hi = mid - 1;
                else lo = mid + 1;
            } else {
                if(target <= nums[hi] && target > nums[mid]) lo = mid + 1;
                else hi = mid - 1;
            }
        }
        return -1;
    }
};

/**************************************************** 
 ***    032,Hard,Longest Valid Parentheses 
 ****************************************************/

/*
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4. 
*/

/*
 Dynamic programming, use a table to store the length of longest valid parentheses of s's substring of length i (i = 0 .. n) that ends at s[i].
The result will be the maximum length among all such strings.
 We scan all characters, for i-th character, when we see a ')' we start checking the substring s[0..i-1] of length i. We already know the maximum length of s[0..i), so we check the character before that, if it is '(', then we have found a matching bracket, we further add the part before that '(' is there is any. Be attention of case of possible array out of bound.

  s: 0    ..       j   ...    i-1  i
         [ ... ]  '('   [ ... ]   ')'
*/ 

// Caveats:
// In this scheme, when checking s[i], we are calculating mp[i+1], not mp[i].
// Do not confuse mp[i] and s[i]
// Indexing: mp[i-len-1] not mp[i-len]
// should return max_len, not mp[n]

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        if(n <= 1) return 0;
        vector<int> mp(n+1, 0); //mp[n]: the length of lvp substring of s[0..n-1] that ends at s[n-1].
        int max_len = 0;
        for(int i = 0; i < n; ++i) {
            if(s[i] == ')') {
                int len = mp[i]; //check previous substring
                if(mp[len] >= i || s[i-len-1] != '(') mp[i+1] = 0; //no valid substring ending at s[i]
                else mp[i+1] = len + mp[i-len-1] + 2;
                max_len = max(max_len, mp[i+1]);
            }
        }
        return max_len;
    }
};

// Another solution with stack
/* Stack stores the position of last unmatched position so far, when seeing a ')' start checking the top of stack. If it is a ')', we found a match, and calculate the length from the current top, not if matched, insert the current ')' to the stack indicating the new "end" of unmatched position.
 For example, s=())(())
s[0]: '(', stack: 0
s[1]: ')', pop stack 0 and found a match, now stack is empty, len = 1+1 = 2;
s[2]: ')', stack empty, no match, just push ')' position 2 to stack
s[3]: '(', push to stack, now 2, 3
s[4]: '(', push to stack, now 2, 3, 4
s[5]: ')', matched 4 in stack, len = 2, now stack is 2,3
s[6]: ')', matched 3 in stack, len = 4, now stack is 2.
*/
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        if(n <= 1) return 0;
        deque<int> st; //stack storing indices
        int max_len = 0;
        for(int i = 0; i < n; ++i) {
            char c = s[i];
            if(c == '(' || st.empty()) st.push_back(i);
            else { //c is ')' and st not empty
                int j = st.back(); st.pop_back();
                if(s[j] != '(') st.push_back(i); //not matched
                else { //matched, pop out and get one pos left of valid substring
                    int len = st.empty() ? i+1 : i-st.back();
                    max_len = max(max_len, len);
                }
            }
        }
        return max_len;
    }
};

// Another solution with a sentinel element (-1) to avoid st.empty() checks
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        if(n <= 1) return 0;
        deque<int> st; //stack storing indices
        st.push_back(-1); //sentinel element to avoid st.empty() checks
        int max_len = 0;
        for(int i = 0; i < n; ++i) {
            char c = s[i];
            if(c == '(') st.push_back(i);
            else { //c is ')' and st not empty
                int j = st.back(); st.pop_back();
                if(j == -1 || s[j] != '(') st.push_back(i); //not matched (need to check if j == -1!)
                else { //matched, pop out and get one pos left of valid substring
                    int len = i-st.back(); //if sentinel is back, then is i+1
                    max_len = max(max_len, len);
                }
            }
        }
        return max_len;
    }
};

/**************************************************** 
 ***    031,Medium,Next Permutation 
 ****************************************************/

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


/**************************************************** 
 ***    030,Hard,Substring with Concatenation of All Words 
 ****************************************************/

/*
You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).
*/

// words may contain duplicates, so use a map (counts) to count occurrences of each unique word, use occurs to count words seen so far in s
// e.g. words = ["a", "a", "b"], then counts = { "a" => 2, "b" => 1 }
// let the length of each word to be L, then has to do L passes, each time searching starts from s[l], l = 0 .. l-1.
// Each pass, use two pointers to track the sliding window boundaries. grab a subtring of length L once at a time. If reaching the maximum window size (L*nwords), then slide left (i) one L step. When counts == occurs (size equal && individual elements equal), then found a valid index

// Be cautious, j is not the end of the window, but j+L is!, so length of window is actually j-i+1.
// Don't need to maintain a separate total count, since when comparing counts and occurs, first it compares the size

// e.g.
// s = b a r f o o t h e f o o b a r m a n  ,  counts = {bar => 1, foo => 1}
//    [b a r]f o o t h e f o o b a r m a n  ,  i = 0, j = 0, occurs = {bar => 1}
//    [b a r f o o]t h e f o o b a r m a n  ,  i = 0, j = 3, occurs = {bar => 1, foo = 1},  found '0'
//     b a r[f o o t h e]f o o b a r m a n  ,  i = 3, j = 6, break since the is not in words, occurs = {}
//     b a r f o o t h e[f o o]b a r m a n  ,  i = 9, j = 12, occurs = {foo => 1}
//     b a r f o o t h e[f o o b a r]m a n  ,  i = 9, j = 15, occurs = {foo => 1, bar = 1}, found '9'
//     b a r f o o t h e f o o[b a r m a n] ,  i = 12, j = 18, break since the is not in words, occurs = {}

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ret;
        if(words.empty()) return ret;
        map<string, int> counts; //counts of each unique word
        map<string, int> occurs; //occurrences of each word in s
        for(int i = 0; i < words.size(); ++i) {
            counts[words[i]]++;
        }
        int L = words[0].size(); //word length
        for (int l = 0; l < L; ++l) { //do L passes
            int i = l, j = l;
            occurs.clear(); // clear occurences map
            //scan each substring of length L
            while(j+L <= s.size()) {
                string t = s.substr(j, L);
                if(counts.count(t) == 0) { //not found such word
                    i = j = j+L;
                    occurs.clear();
                    continue;
                }
                occurs[t] ++; //found such word
                if(j == i + L*words.size()) { //reached max size of window
                    string t2 = s.substr(i, L);
                    if(counts.count(t2) > 0) occurs[t2] --;
                    i += L; //move left side of window forward by L
                }
                if(occurs == counts) ret.push_back(i);
                j += L;
            }
        }
        return ret;
    }
};

// Can further optimize and only use one map to store the counts, when see the string, reduce the individual counts, when it reaches zero we know that we have exactly the amount we need.
// similar to min window, use only one dict to store the counting information. The key is to restore the information after each run.

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
         vector<int> result;
         int nwords = words.size();
         if(nwords == 0) return result;
         int lword = words[0].size();
         if(s.empty()) return result;
         unordered_map<string, int> dict, count;
         int total_count = 0;
         int n = s.size();
         for(size_t i = 0; i < nwords; ++i)
             dict[words[i]]++;
        
         for(size_t i = 0; i < lword; ++i) {
             total_count = nwords;
             count = dict;
             int jstart = i, j = i;
             while(j + lword <= n) {
                 string str = s.substr(j, lword);
                 if(count.find(str) == count.end()) {
                     total_count = nwords;
                     count.clear();
                     jstart = j + lword;
                 } else {
                     total_count ++;
                     count[str] ++;
                     int c = dict[str];
                     while(count[str] > c) {
                         string tmp = s.substr(jstart, lword);
                         count[tmp] --;
                         total_count --;
                         jstart += lword;
                     }
                 }
                 if(total_count == words.size()) result.push_back(jstart);
                 j += lword;
             }
         }
         return result;
    }
};


/**************************************************** 
 ***    028,Easy,Implement strStr() 
 ****************************************************/

/*
Implement strStr().

Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
*/

/// Classical pattern search problem. 
/// Solution 1. Brute-force solution, O(MN) in the worst case

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        int i(0), j(0);
        for(i = 0; i < n && j < m; ++i) {
            if(haystack[i] == needle[j]) j++;
            else { i-=j; j = 0; }
        }
        if(j == m) return i-j;
        else return -1;
    }
};

// Solution 2. A varient of brute-force solution
class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size(), i(0), j(0);
        while(i < n && j < m) {
            if(haystack[i] == needle[j]) { i++; j++; }
            else {i = i-j+1; j = 0; }
        }
        if(j == m) return i-j;
        else return -1;
    }
};

// Solution 3. KMP algorithm with transfer function.
/*
We define the transfer function f[j] = k as the length of longest prefix of p[0 .. j-1] such that
f[0 .. k-1] == f[j-k .. j-1], 0 <= k < j
we don't allow k to equal j to avoid the trivial case where prefix is the string itself.
Therefore, whenever we see a mismatch between t[i] and p[j], we can directly make j jump to k = f[j], and i stays unchanged, so that t[i] is compared with p[k] (we know for sure that p[0 .. k-1] matches with t[i-k, i-1].
One corner case is that when mismatch happens at first character of pattern, i.e. j = 0. In this case we just increment i and keep j unchanged.

e.g. 01234   5
     abcab | cabd
     abcab | d    mismatch at j = 5, f[5] = 2
     01234   5   
=>   abcab | cabd
        ab | cabd
        01   23   j jumps to f[j] = 2

How to build transfer function for the pattern strign? We use an elegant dynamic programming approach. Say we know f[j-1] = k, now we calculate f[j], where we need to examine p[j-1].
We simply compare p[j-1] with p[k].
If they are equal, then we found that f[j] = k+1.
e.g. abcabc,  f[5] = 2 (ab), then f[6] = 3 because p[3] = [5] = c.
If they are not equal, we need to continue searching f[k] until k is less than zero. e
e.g. acadaca x acadaca d, f[15] = 7 (acadaca), for f[16], since p[7] != p[16], we need to examine f[7]. Since f[7] = 3 (aca), and p[4] = p[16], we know f[16] = 4 (acad)
Boundary case: f[0] = -1 for later convenience, f[1] = 0.

Thus we have come up with the following loop:
    f[0] = -1; f[1] = 0;
    for(int j = 2; j <= m; ++j) { //length j
        char c = needle[j-1];
        int k = f[j-1]; //result for previous
        while(k >= 0 && needle[k] != c) k = f[k];
        f[j] = k+1; //either k = -1, or needle[k] == c
    }

We can further optimize, and let k be the f value for the last calculation. Initially, k = f[1] = 0.
After each calculation, we update k's value by k = k+1, and then assign it to f[j].
Two case:
1. k = -1 after while loop, which indicates no such prefix exists, in this case by definition f[j] = 0, we let f[j] = ++k which is OK.
2. k >= 0 after while loop, which we know that needle[k] == c. This means that the maximum prefix for for pj is p[0..k] including k, and thus f[j] = ++k is also OK.
This has lead to the following loop:
    f[0] = -1; f[1] = 0; k = 0; // k is result for previous
    for(int j = 2; j <= m; ++j) { //length j
        while(k >= 0 && needle[k] != needle[j-1]) k = f[k];
        f[j] = ++k; //after while loop, either k = -1, or needle[k] == needle[j-1]
    }
*/

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        vector<int> f(m+1, -1); //jump position for p[0. i-1) of length i
        f[1] = 0; 
        for(int j = 2; j <= m; ++j) { //length j, f[1] will lead to 0
            char c = needle[j-1];
            int k = f[j-1];
            while(k >= 0 && needle[k] != c) k = f[k];
            f[j] = k+1; //either f[k] = -1, or t[f[k]] = c
        }
        int i(0), j(0);
        while(i < n && j < m) {
            if(haystack[i] == needle[j]) { i++; j++; }
            else if(j == 0) i++;
            else j = f[j];
        }
        return (j == m) ? i-j : -1;
    }
};

//slightly optimized KMP.

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        vector<int> f(m+1, -1); //jump position for p[0. i-1) of length i
        int k = -1; //k is result from previous step
        for(int j = 1; j <= m; ++j) { //length j, f[1] will lead to 0
            while(k >= 0 && needle[k] != needle[j-1]) k = f[k];
            f[j] = ++k; //either f[k] = -1, or t[f[k]] = c
        }
        int i(0), j(0);
        while(i < n && j < m) {
            if(haystack[i] == needle[j]) { i++; j++; }
            else if(j == 0) i++;
            else j = f[j];
        }
        return (j == m) ? i-j : -1;
    }
};


/**************************************************** 
 ***    027,Easy,Remove Element 
 ****************************************************/

/*
Given an array and a value, remove all instances of that value in place and return the new length.

The order of elements can be changed. It doesn't matter what you leave beyond the new length. 
*/

// Solution 1, fastest. Just maintain two pointers. Since we don't care about elements == val, we don't use fancy color sort algorithms.

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if(nums.empty()) return 0;
        int i(0), j(0), n = nums.size();
        for(int j = 0; j < n; ++j) {
            if(nums[j] != val) nums[i++] = nums[j];
        }
        return i;
    }
};

// Solution 2, two color sort.
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        //[0 .. i-1] != val, [i, j-1] == val, [j, n-1] TBD
        if(nums.empty()) return 0;
        int i = 0, j = 0, n = nums.size();
        while(j < n) {
            if(nums[j] == val) j++;
            else swap(nums[j++], nums[i++]);
        }
        return i;
    }
};

// Solution. variation of solution 2.
/// Similar to two-color problem, use two pointers i, and j. Loop invariant:
/// 1. nums[0 .. i-1] != val
/// 2. nums[i .. j] to be determined
/// 3. nums[j .. end) == val
/// when i and j cross, return i

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int i = 0, j = nums.size()-1;
        while (i <= j) {
            if (nums[i] != val) i++;
            else swap(nums[i], nums[j--]);
        }
        return i;
    }
};


/**************************************************** 
 ***    026,Easy,Remove Duplicates from Sorted Array 
 ****************************************************/

/*
Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

For example,
Given input array nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the new length. 
*/

// Two pointers
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return n;
        int len = 0;
        int i = 0, j = 0;
        while(i < n) {
            j = i+1;
            while(j < n && nums[j] == nums[i]) j++;
            nums[len++] = nums[i];
            i = j;
        }
        return len;
    }
};

// A slightly different solution (no len variable)
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return n;
        int i = 0, j = 1;
        while(1) {
            while(j < n && nums[j] == nums[i]) j++;
            if(j == n) break;
            nums[++i] = nums[j++];
        }
        return i+1;
    }
};

/**************************************************** 
 ***    025,Hard,Reverse Nodes in k-Group 
 ****************************************************/

/*
Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/*
Solution 1. Iterative.
Determine the head and tail of each segment, and use a helper function to reverse it, and attach it to original list. The helper funtion
Uses a dummy head.
while loop invariant:
 start:   p1 -> [ p2 -> ... -> p3 ] -> p4 
 end:     p1 -> [ p3 -> ... -> p2 ] -> p4
*/

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(!head || k <= 1) return head;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *p1 = dummy, *p2 = head;
       // p1 -> [ p2 -> ... -> p3 ] -> p4 => p1 -> p3 -> ... -> p2 -> p4
        while(p2) {
            int count = k;
            ListNode *p3 = p2, *p4 = NULL;
            while(count > 1 && p3) {
                count--;
                p3 = p3->next;
            }
            if(!p3) break; //not enough elements to reverse
            p4 = p3->next;
            //now reverse p2 -> ... -> p3
            ListNode *curr = p2, *next = curr->next, *nextnext = NULL;
            while(curr != p3) {
                nextnext = next->next; // save it to tmp
                next->next = curr; //reverse 
                curr = next; //move forward
                next = nextnext; //move forward
            }
            //now connects p1 -> p3 and p2 -> p4
            p1->next = p3; p2->next = p4;
            //back to loop
            p1 = p2; p2 = p4;
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};

/* 
Solution 2. Same as method 1, but use iterative helper function to reverse.
*/

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == NULL || k == 1) return head;
        ListNode dum(0), *p(&dum); //dummy head
        p->next = head;
        ListNode *tail(NULL), *next(NULL), *last(p);
        while (head) {
            tail = head;
            int cnt = 1;
            while (cnt < k && tail) { tail = tail->next; cnt++; }
            if (!tail) break;
            next = tail->next;
            reverse(head, tail);
            last->next = tail; //tail is new head
            head->next = next; //head is new tail
            //update and move to next segment
            last = head;
            head = next;
        }
        return p->next;
    }
    void reverse(ListNode* head, ListNode* tail) {
        ListNode *next(head->next), *nextnext(NULL);
        while (head != tail) {
            nextnext = next->next;
            next->next = head; //reverse
            head = next;
            next = nextnext;
        }
    }
/*  
    //A slightly different reverse version
    void reverse(ListNode* head, ListNode* tail) {
        ListNode *next(head->next);
        while (head != tail) {
            ListNode* tmp = next->next; //tmp stores next->next 
            next->next = head; //reverse
            head = next;
            next = tmp;
        }
    }
*/
};

/**************************************************** 
 ***    024,Medium,Swap Nodes in Pairs 
 ****************************************************/

/*
Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Solution 1. Iterative solution. Use a dummy head and two pointers.

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        //p is tail of processed list part
        ListNode *p = dummy, *q = p->next;
        //swap q and q->next
        while(q && q->next) {
            ListNode *r = q->next;
            q = r->next; //move to next
            r->next = p->next;
            p->next = r;
            p = r->next; //move forward
            p->next = q;
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};

// Solution 2. Recursive solution.
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode *p = head->next, *q = p->next;
        p->next = head;
        head->next = swapPairs(q);
        return p;
    }
};


/**************************************************** 
 ***    023,Hard,Merge k Sorted Lists 
 ****************************************************/

/*
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
// Divide and conquer solution. Use the merge-two-list function.
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int size = lists.size();
        if(size == 0) return NULL;
        int i = 0;
        while(size > 1) {
            for(i = 0; 2*i+1 < size; i++) {
                lists[i] = mergeTwoLists(lists[2*i], lists[2*i+1]);
            }
            if(size % 2 == 1) lists[i] = lists[size-1];
            size = (size+1)/2;
        }
        return lists[0];
    }

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0), *p(&dummy);
        ListNode *tail = p;
        while(l1 && l2) {
            if(l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        if(l1) tail->next = l1;
        else tail->next = l2;
        return p->next;
    }
};

// Priority queue solution O(nlgk) using STL priority queue, and comparator class
class isGreater {
public:
    bool operator() (ListNode *a, ListNode *b) {
        return a->val > b->val;
    }
};

class Solution {

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, isGreater> q;
        for(int i = 0; i < lists.size(); ++i) {
            if(lists[i]) q.push(lists[i]);
        }
        if(q.empty()) return NULL;
        ListNode dummy(0), *p(&dummy);
        ListNode *tail = p;
        while(q.size() > 1) {
            ListNode *node = q.top(); q.pop();
            tail->next = node;           
            tail = tail->next;
            if(node->next) q.push(node->next);
        }
        // only one element left
        tail->next = q.top();
        return p->next;
    }
};

// Priority queue solution O(nlgk) without using STL priority queue
class MinHeap {
public:
	MinHeap(int max_l) : maxL(max_l), size(0) {
		head = new ListNode* [maxL];
		arr = head-1; //pointer such that first element is arr[1]
	}
	~MinHeap() { delete [] head;}
	
    //push back without FixUp
	void PushBack(ListNode* node) {
		head[size++] = node;
	}
    //insert and run FixUp 
    void Insert(ListNode* node) {
        head[size++] = node;
        FixUp(size);
    }
	//build heap
	void BuildHeap() {
		for(int i = size/2; i >= 1; --i) FixDown(i);
	}

	bool Empty() { return size == 0; }

	// Extract minimum element
	ListNode* ExtractMin() {
		Swap(arr[size--], arr[1]);
		FixDown(1);
		return arr[size+1];
	}

	//fix down (check if arr[i] needs to be swapped with children)
	void FixDown(int i) {
		while(i > 0) {
			int smallest = i;
			int l = Left(i), r = Right(i);
			if( l <= size && arr[l]->val < arr[smallest]->val) smallest = l;
			if( r <= size && arr[r]->val < arr[smallest]->val) smallest = r;
			if(smallest != i) {
				Swap(arr[smallest], arr[i]);
				i = smallest;
			} else break;
		}
	}
    //fix up (check if arr[i] needs to be swapped with parent)
	void FixUp(int i) {
		while(i > 1) {
			int p = Parent(i);
			if(arr[p]->val > arr[i]->val) {
				Swap(arr[p], arr[i]);
				i = p;
			} else break;
		}
	}

	int Left(int i) {return 2*i;}
	int Right(int i) {return 2*i+1;}
	int Parent(int i) {return i/2;}
	void Swap(ListNode* &a, ListNode* &b) { ListNode* t = a; a = b; b = t;}

private:
	ListNode** head; //point to the head of array
	ListNode** arr; //one less the beginning of array
	int maxL; //max length
	int size; //size
};

class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        int size = lists.size();
        if(size == 0) return NULL;
        ListNode dum(0), *dummy(&dum), *p(dummy);
        MinHeap hp(size);
        for(int i = 0; i < size; ++i) {
            if(lists[i]) hp.PushBack(lists[i]);
        }
        hp.BuildHeap();
        while(!hp.Empty()) {
            ListNode *min_node = hp.ExtractMin();
            p->next = min_node;
            if(min_node->next) hp.Insert(min_node->next);
            p = p->next;
        }
        p->next = NULL;
        return dummy->next;
    }
};

/**************************************************** 
 ***    022,Medium,Generate Parentheses 
 ****************************************************/

/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

"((()))", "(()())", "(())()", "()(())", "()()()" 
*/

// Recursive solution. backtracking, DFS
// pre-allocate string, pass reference and string index to avoid string copying. Keep track of number of open and close brackets left.

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        if(n < 1) return result;
        string str(2*n, '0');
        dfs(n, n, 0, str, result);
        return result;
    }
    void dfs(int nl, int nr, int i, string& str, vector<string>& result) {
        if(i == str.size()) {
            result.push_back(str);
            return;
        }
        if(nl > 0) {
            str[i] = '(';
            dfs(nl-1, nr, i+1, str, result);
        }
        if(nr > 0 && nl < nr) {
            str[i] = ')';
            dfs(nl, nr-1, i+1, str, result);
        }
    }
};

// Another iterative solution
class Solution {
public:
	vector<string> generateParenthesis(int n) {
		vector<string> ret;
		int k(0); //k is the index of current parenthesis
		int nr(0); //number of left and right parenthesis
		string str(2*n, '('); //initially '('
		while(1) {
			int nl = k+1-nr;
			if(k == 2*n) { //reached end of string, add to solution
				ret.push_back(str);
				k--;
				update(str[k], nr);
			} else if (str[k] == 'X') { //exhaust all trials, abandon and retrace
				update(str[k], nr); //reset to '.'
				k--;
				if(k < 0) break; //breaking condition
				update(str[k], nr); //increment last element
			} else if(nr > n || nl > n || nl < nr){ //unbalanced
				update(str[k], nr);
			} else { //normal
				k++;
			}
		}
		return ret;
	}
	void update(char& c, int& nr) {
		if(c == '(') {
			c = ')';
			nr ++;
		} else if(c == ')') {
			c = 'X';
			nr --;
		}	else if(c == 'X') c = '(';
	}
};

/**************************************************** 
 ***    021,Easy,Merge Two Sorted Lists 
 ****************************************************/

/*
Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Use dummy head, and a tail pointer to track end of sorted list.
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0), *p(&dummy);
        ListNode *tail = p;
        while(l1 && l2) {
            if(l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        if(l1) tail->next = l1;
        else tail->next = l2;
        return p->next;
    }
};

/**************************************************** 
 ***    020,Easy,Valid Parentheses 
 ****************************************************/

/*
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
*/

// Use a stack. When seeing a left parenthesis, push to stack; otherwise check against top of stack
// After reaching the end of string, need to check if stack is empty! (e.g. '[' is not valid)

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if(isLeft(c)) st.push(c);
            else if (st.empty() || !match(st.top(), c)) return false; //is right, no match
            else st.pop(); //match, pop out
        }
        return st.empty();
    }
    
    bool isLeft(char c) {
        return c == '(' || c == '[' || c == '{';
    }
    bool isRight(char c) {
        return c == '(' || c == '[' || c == '{';
    }
    bool match(char c1, char c2) {
        return (c1 == '(' && c2 == ')') ||
                (c1 == '[' && c2 == ']') ||
                (c1 == '{' && c2 == '}');
    }
};

/**************************************************** 
 ***    019,Easy,Remove Nth Node From End of List 
 ****************************************************/

/*
Given a linked list, remove the nth node from the end of list and return its head.

For example,

   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes 1->2->3->5.

Note:
Given n will always be valid.
Try to do this in one pass. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/// Solution 1. Use dummy head node. Two while loops.
/// Two pointers, first and last. Let last move forward by n steps. And then left first and last move together until last reaches the tail.
/// Then the node to be removed is first-next.

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *first(dummy), *last(dummy);
        while(n) {
            last = last->next;
            n--;
        }
        while(last->next) {
            first = first->next; last = last->next;
        }
        //delete first->next;
        ListNode* tmp = first->next;
        first->next = tmp->next;
        delete tmp;
        //return new head
        head = dummy->next;
        delete dummy;
        return head;
    }
};

/// Solution 2. Same idea, but one pass (slightly simplified code).

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *first(dummy), *last(dummy);
        while(last->next) {
            last = last->next;
            if(--n < 0) first = first->next;
        }
        
        //delete first->next;
        ListNode* tmp = first->next;
        first->next = tmp->next;
        delete tmp;
        //return new head
        head = dummy->next;
        delete dummy;
        return head;
    }
};



/**************************************************** 
 ***    018,Medium,4Sum 
 ****************************************************/

/*
Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note:

    Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d)
    The solution set must not contain duplicate quadruplets.

    For example, given array S = {1 0 -1 0 -2 2}, and target = 0.

    A solution set is:
    (-1,  0, 0, 1)
    (-2, -1, 1, 2)
    (-2,  0, 0, 2)
*/

// O(n3) solution, need to take care of duplicated entries.
// Also several optimization lines (break/continue).
// Storing partial sums (e.g. nums[n-2] + nums[n-1]) does not reduce run time.

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int> > result;
        vector<int> tmp(4, 0);
        int n = nums.size();
        if(n <= 3) return result;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n-3; ++i) {
            if(i > 0 && nums[i] == nums[i-1]) continue; //avoid duplicates
            if(nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target) break;
            if(nums[i] + nums[n-3] + nums[n-2] + nums[n-1] < target) continue;
            for(int j = i+1; j < n-2; ++j) {
                if(j > i+1 && nums[j] == nums[j-1]) continue; //avoid duplicates
                if(nums[i] + nums[j] + nums[j+1] + nums[j+2] > target) break;
                if(nums[i] + nums[j] + nums[n-2] + nums[n-1] < target) continue;
                int k = j+1, l = n-1;
                while(k < l) {
                    int sum = nums[i] + nums[j] + nums[k] + nums[l];
                    if(sum < target) k++;
                    else if(sum > target) l--;
                    else { //equal
                        tmp[0] = nums[i]; tmp[1] = nums[j]; tmp[2] = nums[k]; tmp[3] = nums[l];
                        result.push_back(tmp);
                        k++; l--;
                        while(k < l && nums[k] == nums[k-1]) k++;
                        while(k < l && nums[l] == nums[l+1]) l--;
                    }
                }
            }
        }
        return result;
    }
};

/**************************************************** 
 ***    017,Medium,Letter Combinations of a Phone Number 
 ****************************************************/

/*
Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

Note:
Although the above answer is in lexicographical order, your answer could be in any order you want. 
*/

// Solution 1. Recursive dfs solution. Use a dict storing the conversion rule. Terminate at i == n.
// A variant is also given where termination is at i == n-1.

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> dict = {"", "", "abc", "def", "ghi", "jkl", "mno", "prqs", "tuv", "wxyz"};
        vector<string> result;
        if(digits.empty()) return result;
        int n = digits.size();
        string tmp(n, '0');
        dfs(digits, 0, dict, tmp, result);
        return result;
    }
    //starting from i-th digits
    void dfs(const string& digits, int i, vector<string>& dict, string& tmp, vector<string>& result) {
        if(i == digits.size()) {
            result.push_back(tmp);
            return;
        }
        int idx = digits[i] - '0';
        //choose among possible characters in dict[idx]
        for(auto c : dict[idx]) {
            tmp[i] = c;
            dfs(digits, i+1, dict, tmp, result);
        }
    }
/*  // simplified dfs routine terminating at i == n-1
    void dfs(const string& digits, int i, vector<string>& dict, string& tmp, vector<string>& result) {
        int idx = digits[i] - '0';
        int n = digits.size();
        //choose among possible characters in dict[idx]
        for(auto c : dict[idx]) {
            tmp[i] = c;
            if(i == n-1) result.push_back(tmp);
            else dfs(digits, i+1, dict, tmp, result);
        }
    }
*/
};


/**************************************************** 
 ***    016,Medium,3Sum Closest 
 ****************************************************/

/*
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/

/// O(n2) solution

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int result = 0;
        int min_diff = INT_MAX;
        int n = nums.size();
        if(n <= 2) return 0;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n-2; ++i) {
            if(i > 1 && nums[i] == nums[i-1]) continue;
            int j = i+1, k = n-1;
            while(j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                int diff = target - sum;
                if(diff == 0) return target;
                else if(diff < 0) k--;
                else j++;
                if(abs(diff) < min_diff) {
                    min_diff = abs(diff);
                    result = sum;
                }
            }
        }
        return result;
    }
};

/**************************************************** 
 ***    015,Medium,3Sum 
 ****************************************************/

/*
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

    Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
    The solution set must not contain duplicate triplets.

    For example, given array S = {-1 0 1 2 -1 -4},

    A solution set is:
    (-1, 0, 1)
    (-1, -1, 2)
*/

/// O(n2) solution
/// Need to consider duplicated entries.
/// Optimization: break if nums[i] > 0, and also num[n-1] < 0 (52ms => 48ms)

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > ret;
        int n = nums.size();
        if(n <= 2) return ret;
        vector<int> tmp(3, -1);
        sort(nums.begin(), nums.end());
        if(nums[n-1] < 0) return ret; //no need to continue if largest value is < 0
        for(int i = 0; i < n-2; i++) {
            if(nums[i] > 0) break; //no need to continue if found a positive number
            if(i > 0 && nums[i] == nums[i-1]) continue; //avoid duplicates
            if(nums[i] + nums[i+1] + nums[i+2] > 0) break;
            if(nums[i] + nums[n-2] + nums[n-1] < 0) continue;
            int target = -nums[i];
            int j = i+1, k = n-1;
            while(j < k) {
               int sum = nums[j] + nums[k];
               if(sum < target) j++;
               else if(sum > target) k--;
               else {
                   tmp[0] = nums[i]; tmp[1] = nums[j]; tmp[2] = nums[k];
                   ret.push_back(tmp);
                   j++; k--;
                   while(j < k && nums[j] == nums[j-1]) j++; //avoid duplicates
                   while(j < k && nums[k] == nums[k+1]) k--; //avoid duplicates
               }
            }
        }
        return ret;
    }
};

/// O(n2 lgn) solution. Iterate first 2 brute-force, and use binary search to find 3rd element.
/// Need to avoid duplicated entries. (lines 14 and 16).

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > ret;
        
        int n = nums.size();
        if(n <= 2) return ret;
        vector<int> sol(3, 0);
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n; ++i) { //whether nums[i] is one of the triplet?
            if(i > 0 && nums[i] == nums[i-1]) continue; //ignore duplicates
            for(int j = i+1; j < n; ++j) {
                if(j > i+1 && nums[j] == nums[j-1]) continue; //ignore duplicates
                int target = -(nums[i] + nums[j]);
                int r = find(nums, j+1, target);
                if(r != -1) {
                    sol[0] = nums[i], sol[1] = nums[j], sol[2] = nums[r];
                    ret.push_back(sol);
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

/**************************************************** 
 ***    014,Easy,Longest Common Prefix 
 ****************************************************/

/*
Write a function to find the longest common prefix string amongst an array of strings. 
*/

// Compare all strings against first string. Two nested loops. When found a mismatch, simply return the maximum length found so far.
// If no mismatch found, return full first string
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty()) return "";
        int n = strs.size();
        if(n == 1) return strs[0];
        int ns = strs[0].size();
        for(int j = 0; j < ns; ++j) { //j loops over each string
            for(int i = 1; i < n; ++i) { //i loops over vector of strings
                if(j == strs[i].size() || strs[i][j] != strs[0][j])  //found a mismatch!
                    return strs[0].substr(0, j); //return s[0, j)
            }
        }
        return strs[0];
    }
};

// Another solution, need to break out two nested loops.
// Compare all strings against first string

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int n = strs.size();
        if (n == 0) return string();
        if (n == 1) return strs[0];
        string s;
        bool stop = false;
        for (int j = 0; j < strs[0].size(); ++j) {
            stop = false;
            for (int i = 1; i < n; ++i)
                if (j == strs[i].size() || strs[i][j] != strs[0][j]) { stop = true; break; }
            if (stop) break;
            s += strs[0][j];
        }
        return s;
    }
};

/**************************************************** 
 ***    013,Easy,Roman to Integer 
 ****************************************************/

/*
Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.
*/

// Solution 1:
// Scan from left to right. Get the value of next character and compare with current one.
// If current one is larger, add to sum and move forward one step
// If current one is smaller, add (next-curr) and move forward two steps

class Solution {
public:
    int romanToInt(string s) {
        int n = s.size();
        int val = 0;
        for (int i = 0; i < n; ++i) {
            int curr = char2num(s[i]);
            int next = (i < n-1) ? char2num(s[i+1]) : 0;
            if (next > curr) {val += next-curr; i++; }
            else val += curr;
        }
        return val;
    }
    
    int char2num(char c) {
        switch (c) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50; 
            case 'C': return 100;
            case 'D': return 500; 
            case 'M': return 1000; 
            default:  return 0;
        }
    }
};

// Solution 2:
// Scan from right to left. check current value against last value
// If current value is larger or equal than last value, add to sum (e.g. XI, add 10)
// If current value is smaller, substract from sum (e.g. IX, subract 1)
// Underlying assumption is that we won't have invalid string like "IVX"

class Solution {
public:
    int romanToInt(string s) {
        int n = s.size();
        int val = 0;
        int last(0), curr(0);
        for (int i = n-1; i >= 0; --i) {
            curr = char2num(s[i]);
            if (curr >= last) val += curr;
            else val -= curr;
            last = curr;
        }
        return val;
    }
    
    int char2num(char c) {
        switch (c) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50; 
            case 'C': return 100;
            case 'D': return 500; 
            case 'M': return 1000; 
            default:  return 0;
        }
    }
};

/**************************************************** 
 ***    012,Medium,Integer to Roman 
 ****************************************************/

/*
Given an integer, convert it to a roman numeral.

Input is guaranteed to be within the range from 1 to 3999.
*/

// A simple solution using a table

const int values[13] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
const string strs[13] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
        
class Solution {
public:
    string intToRoman(int num) {
        string s;
        for(int i = 0; i < 13; ++i) {
            while(num >= values[i]) {
                num -= values[i];
                s += strs[i];
            }
            if(num == 0) break;
        }
        return s;
    }
};

// An old solution. use an append function. Deal with one, five, ten
class Solution {
public:
    string intToRoman(int num) {
        string s;
        int n = 0;
        if (num >= 1000) { append(s, num/1000, 'M', 'Y', 'Z'); num %= 1000; }
        if (num >= 100)  { append(s, num/100,  'C', 'D', 'M'); num %= 100;  }
        if (num >= 10)   { append(s, num/10,   'X', 'L', 'C'); num %= 10;   }
        if (num >= 1)    { append(s, num/1,    'I', 'V', 'X'); }
        return s;
    }
    //c1 is for one, c2 is for five, c3 is for ten
    void append(string& s, int d, char c1, char c2, char c3) {
        if (d == 0) return;
        else if (d <= 3) s += string(d, c1);
        else if (d == 4) { s += c1; s += c2;  }
        else if (d == 5) s += c2;
        else if (d <= 8) { s += c2; s += string(d-5, c1); }
        else if (d == 9) { s += c1; s += c3; }
    }
};

/**************************************************** 
 ***    011,Medium,Container With Most Water 
 ****************************************************/

/*
Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container. 
*/

/*
Similar idea to "trapping rain water". Maintain two pointers and find the minimum water level deterimed by the two pointers. Move from the side with lower height, stop when two pointers meet.
The height of container is the smaller of the two ends. Proceed by moving the lower point inwards, because we can proove that the interval between lo and hi is the widest one possible for the container of height of height[lo].
Proceeding from higher point is wrong! e.g.
height:   3 9 1 1
position: 0 1 2 3

l = 0, h = 3 => area = 3
if we move from higher point, we missed [0, 1] with area 6.
*/

class Solution {
public:
    int maxArea(vector<int>& height) {
        int area = 0;
        int n = height.size();
        if(n <= 1) return 0;
        int l(0), r(n-1);
        while(l < r) {
            area = max(area, min(height[l], height[r])*(r-l));
            if(height[l] < height[r]) l++;
            else r--;
        }
        return area;
    }
};

/**************************************************** 
 ***    010,Hard,Regular Expression Matching 
 ****************************************************/

/*
Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true
*/

/*
Solution 1. Standard dynamic programming. Use a 2D vector dp, dp[i][j] stores whether s[0 .. i-1] matches p[0 .. j-1]. dp[i][j] can be determined by the following rules:

1. if p[j-1] is not '*', then we simply check dp[i-1][j-1] and whether s[i-1] matches p[j-1]:
           t[i-1]
t:   abc  | d   => match abc with a*bc, and d with d
p:   a*bc | d
           p[j-1]

           t[i-1]
t:   abc  | d   => match abc with a*bc, and d with .
p:   a*bc | .
           p[j-1]
thus dp[i][j] = dp[i-1][j-1] && matchHelper(s[i-1], p[j-1]);

whether matchHelper(t, p) returns true when p == '.' or p == t.

2. if p[j-1] is '*', we have two sub-cases. Let p[j-2] = x (for p to be a valid RE, '*' has to follow another character that is not '*'). Then x* can match nothing or one or more x's.
a) x* matches nothing, then we just check dp[i-1][j-2]
           t[i-1]
t:   ab    | d   => match abd with a*bd, ignore e*
p:   a*bde | *
          p[j-1]

b) x* matches at least one x, iff p[0, j-1] matches with s[0, i-2], and s[i-2] matches with x/
           t[i-1]
t:   abde  | e   => match abde with a*bde, then e with e
p:   a*bde | *
          p[j-1]

           t[i-1]
t:   abde  | e   => match abde with a*bd., then e with .
p:   a*bd. | *
          p[j-1]

thus dp[i][j] = dp[i][j-2] || (dp[i-1][j] && matchHelper(s[i-1], p[j-2])

Boundary case:
1. "" matches with "", so dp[0][0] = true
2. a non-empty p may also match "", e.g. "a*", so dp[0][j] = dp[0][j-2] && p[j-1] == '*'
*/

class Solution {
public:
    bool isMatch(string s, string p) {
        if(p == "") return s == "";
        //s can be "", p cannot
        int m = s.size(), n = p.size();
        vector<vector<bool> > dp(m+1, vector<bool>(n+1, false)); //match[i][j]: s[0..i-1] matches p[0..j-1]
        dp[0][0] = true; // "" matches ""
        //matching p with ""
        for(int j = 1; j <= n; ++j)
            dp[0][j] = p[j-1] == '*' && dp[0][j-2];
        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(p[j-1] != '*') dp[i][j] = dp[i-1][j-1] && matchHelper(s[i-1], p[j-1]);
                else dp[i][j] = dp[i][j-2] || (dp[i-1][j] && matchHelper(s[i-1], p[j-2]));
            }
        }
        return dp[m][n];
    }
    bool matchHelper(char t, char p) {
        return p == '.' || p == t;
    }
};

/*
Solution 2. Recursive solution, which takes 76ms (v.s. 20ms in solution 1).
Two pointers to scan text and pattern. When we see a pattern character, we "peek" the next character in pattern. If it is not '*', then we do normal matching, and move both forward in case of match. If next is a '*', then we either match empty string (move j two steps further, i stay put), or match one or more charaters after i if they match with p[j].
*/

class Solution {
public:
    bool matchHelper(char t, char p) {
        return p == '.' || p == t;
    }

    bool isMatch(string s, string p) {
        return isMatch(s, p, 0, 0);
    }

    bool isMatch(const string& s, const string& p, int i, int j) {
        int n = s.size(), m = p.size(); //n, i for text; m, j for pattern
        if(j == m) return i == n;
        if(j == m-1 || p[j+1] != '*') { //last char, or next is not '*'
           return matchHelper(s[i], p[j]) && isMatch(s, p, i+1, j+1);
        } else { // next character is '*'
            //first match c* with empty string
            if(isMatch(s, p, i, j+2)) return true;
            //match one or more c's
            while(i < n && matchHelper(s[i], p[j])) {
                if(isMatch(s, p, ++i, j+2)) return true;
            }
	/* //a variant of the last while loop, greedy match, but not much improvements.
	    int k = i;
            while(k < n && matchHelper(s[k], p[j])) k++;
            while(k > i) {
                if(isMatch(s, p, k--, j+2)) return true;
            }
	*/
        }
        return false;
    }
};



/**************************************************** 
 ***    009,Easy,Palindrome Number 
 ****************************************************/

/*
Determine whether an integer is a palindrome. Do this without extra space.

Some hints:

Could negative integers be palindromes? (ie, -1)

If you are thinking of converting the integer to string, note the restriction of using extra space.

You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", you know that the reversed integer might overflow. How would you handle such case?

There is a more generic way of solving this problem.
*/

// Most straightforward solution: construct the reverse number from x, and compare with x
// Doesn't handle overflow explicitly because when overflow happens, y != x

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        int y = 0, num = x;
        while (num > 0) {
            y = y * 10 + num % 10;
            num /= 10;
        }
        return y == x;
    }
};

// Another solution without any overflow issue.
// Store a variable mask that is the largest power of 10 smaller or equal to x.
// Then use it as a mask to get the MSD and compare with the LSD. Next time strip off MSD and LSD and repeat, until the two digits meet.

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        //determine minimum power of 10 smaller or equal than x
        int mask = 1;
        int y = x/10;
        while (mask <= y) mask *= 10; 
        while (mask > 1) {
            if (x / mask != x % 10) return false;
            x = (x % mask) / 10; //strip off first and last digit
            mask /= 100; //update mask
        }
        return true;
    }
};

// Another solution by comparing only half digits.

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        if (x == 0) return true;
        int nd = 0; //number of digits of x
        int xx = x;
        while(xx) {
            xx /= 10;
            nd++;
        }
        int y = 0;
        for(int i = 0; i < nd / 2; ++i) {
            y = 10*y + x%10;
            x /= 10;
        }
        if(nd & 1 == 1) x /= 10; //remove additional digit
        return x == y;
    }
};

/**************************************************** 
 ***    008,Easy,String to Integer (atoi) 
 ****************************************************/

/*
Implement atoi to convert a string to an integer.

Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.

Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible to gather all the input requirements up front.

The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.

The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.

If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.

If no valid conversion could be performed, a zero value is returned. If the correct value is out of the range of representable values, INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.
*/

/// Use a dfa (deterministic finite state automaton to process input string).
/// Stop when state goes to -1 and return the value obtained so far (do not return 0)
/// Be aware of overflow!

class Solution {
public:
    enum CharType {SPACE, SIGN, DIGIT, OTHER};
    //states: 
    // 0: only space read
    // 1: sign read
    // 2: digit read
    // -1: error
    int myAtoi(string str) {
        vector<vector<int> > dfa(3, vector<int>(4, -1));
        dfa[0][SPACE] = 0;
        dfa[0][SIGN] = 1;
        dfa[0][DIGIT] = 2;
        dfa[1][DIGIT] = 2;
        dfa[2][DIGIT] = 2;
        int sgn = 1;
        int ret = 0; 
        int state = 0;
        for(size_t i = 0; i < str.size(); ++i) {
            char c = str[i];
            int type = getType(c);
            state = dfa[state][type];
            if(state == 1) sgn = (c == '-' ? -1 : 1);
            else if(state == 2) {
               int num = c - '0';
               if((INT_MAX - num) / 10 < ret) return (sgn == 1) ? INT_MAX : INT_MIN;
               ret = ret*10 + num;
            } else if(state == -1) {
               return sgn*ret; //return current calcualted value
            }
        }
        return sgn*ret;
    }
    CharType getType(char c) {
        if(c >= '0' && c <= '9') return DIGIT;
        else if(c == '+' || c == '-') return SIGN;
        else if(c == ' ') return SPACE;
        else return OTHER;
    }
};

/// Solution without using dfa. First ignore all trailing spaces, then read possible signs, then read digits until a non-digit character appears or reaching the end. Be aware of overflow!

class Solution {
public:
    int myAtoi(string str) {
        int ret = 0;
        int n = str.size();
        int i = 0;
        while(i < n && str[i] == ' ') i++;
        if(i == n) return 0;
        int sgn = 1;
        if(str[i] == '-') { sgn = -1; i++; }
        else if (str[i] == '+') { i++; }
        for(; i < n; i++) {
           char c = str[i];
           if(c >= '0' && c <= '9') {
               int num = c - '0';
               if((INT_MAX - num) / 10 < ret) return sgn == -1 ? INT_MIN : INT_MAX;
               ret = ret*10 + num;
           } else return sgn*ret;
        }
        return sgn*ret;
    }
};

/**************************************************** 
 ***    007,Easy,Reverse Integer 
 ****************************************************/

/*
Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321

For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
*/

// Solution using long to store intermediate results. Need to consider integer overflow.
// If y > INT_MAX, then overflow (y should always be positive since it is long and will not overflow), also don't need to check -y < INT_MIN, as it is redundant. (We won't end up with y = 2147483647, since the input x cannot be as large as 7463847412)

class Solution {
public:
    int reverse(int x) {
        int sgn = (x >= 0) ? 1 : -1;
        if (x == 0) return 0;
        if(x == INT_MIN) return 0;
        x = abs(x); // no overflow
        long y = 0;
        while (x) {
            y = y*10 + x%10;
            if(y > INT_MAX) return 0;
            x = x / 10;
        }
        return sgn > 0 ? y : -y;
    }
};

// Solution without using long. Need to consider integer overflow for both addition and mutiplication and abs. 
// check overflow for addition: two positive number adds up to a negative number (y < 0)
// check overflow for multiplication: a > INT_MAX / b
// check overflow for calculating absolute values: x == INT_MIN

// Can combine multiplication and addition overflow check into one. See the next solution.

class Solution {
public:
    int reverse(int x) {
        int sign = x > 0 ? 1 : -1;
        if(x == 0) return 0;
        if(x == INT_MIN) return 0;
        x = abs(x); //no overflow
        int y = 0;
        while(x) {
            if(y > INT_MAX / 10) return 0; //overflow
            y = y*10 + (x%10);
            if(y < 0) return 0; //overflow
            x /= 10;
        }
        y = sign > 0 ? y : -y; //no overflow
        return y;
    }
};

class Solution {
public:
    int reverse(int x) {
        int sign = x > 0 ? 1 : -1;
        if(x == 0) return 0;
        if(x == INT_MIN) return 0;
        x = abs(x); //no overflow
        int y = 0;
        while(x) {
            int r = x % 10;
            if(y > (INT_MAX - r) / 10) return 0; //overflow
            y = y*10 + r;
            x /= 10;
        }
        y = sign > 0 ? y : -y; //no overflow
        return y;
    }
};

/**************************************************** 
 ***    004,Hard,Median of Two Sorted Arrays 
 ****************************************************/

/*
There are two sorted arrays nums1 and nums2 of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
*/

/*
Solution 1: compare medians of the two array.
We make a general algorithm that returns the k-th order value from two sorted arrays ( 0 <= k < m+n ). Then use it to calculate the median.
First some mathematics:
Generally, for an array nums[lo, hi], with length len = hi-lo+1, mid = (lo+hi)/2 = lo + ceil((hi-lo)/2.0). Let hlen = (hi-lo)/2. Thus, number of elements before mid (exclusive) is ceil((hi-lo)/2.0) = hlen, and number of elements after mid (exclusive) is floor((hi-lo)/2.0) which can be either hlen or hlen+1, depending on the length of array. Here we have used the fact that
for any integer: ceil(x/2.0) + floor(x/2.0) = x

Now we have two arrays nums1[lo1, hi1], nums2[lo2, hi2], we calculate mid1 and mid2 accordingly. We compare nums1[mid1] and nums2[mid2], say we have nums1[mid1] <= nums2[mid2]. If we combine the two in sorted order we will have something like:
      ... nums1[mid1] ... nums2[mid2] ...
From above, we know that:
a. nums1[mid1] has at least hlen1 + hlen2 + 1 (from nums1, nums2, and nums2[mid2] respectively) elements behind it (exlucsively)
b. nums2[mid2] has at least hlen1 + hlen2 + 1 elements ahead of it (exclusively)

Now let's check k's value, the k-th element (k starts from 0) has k elements before it,
1. if k <= hlen1 + hlen2, then the element can have at most hlen1+hlen2 elements ahead of it. Then we know for sure that the answer is before nums2[mid2], so we can discard nums2[mid2] and the elements in nums2 after it can be excluded
2. if k > hlen1 + hlen2, then the element can have at least hlen1+hlen2+1 elements ahead of it. Can we discard nums1[mid1] and the ones in nums1 ahead of it? Yes! Because nums1[mid1] will have 
at most hlen1 + hlen2 elements ahead of it, including nums1[mid1] we have hlen1+hlen2+1, which we can safely exclude mathemetically (in practice we only exclude elements nums1[0 .. mid1]). The calculation is below:
   number of elements before and including nums1[mid1] <= len1 + len2 - (hlen1 + hlen2 + 1)
                                                        = (hi1-lo1+1) + (hi2-lo2+1) - ( floor((hi1-lo1)/2.0) + floor((hi2-lo2)/2.0 + 1)
                                                        = ceil((hi1-lo1)/2.0) + ceil((hi2-lo2)/2.0) + 1
                                                        = hlen1 + hlen2 + 1
Similar for the case where nums1[mid1] > nums2[mid2]
*/

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int k = (m+n)/2;
        if((m + n) % 2 == 0) {
            int v1 = findKth(nums1, 0, m-1, nums2, 0, n-1, k-1);
            int v2 = findKth(nums1, 0, m-1, nums2, 0, n-1, k);
            return double(v1+v2)/2;
        } else {
            return findKth(nums1, 0, m-1, nums2, 0, n-1, k);
        }
    }
    int findKth(vector<int>& nums1, int lo1, int hi1, vector<int>& nums2, int lo2, int hi2, int k) {
        if(lo1 > hi1) return nums2[lo2+k];
        if(lo2 > hi2) return nums1[lo1+k];
        int mid1 = lo1 + (hi1-lo1)/2;
        int mid2 = lo2 + (hi2-lo2)/2;
        int hlen1 = mid1 - lo1, hlen2 = mid2 - lo2; //number of elements before mid
        if(nums1[mid1] <= nums2[mid2]) {
            if(k <= hlen1 + hlen2) return findKth(nums1, lo1, hi1, nums2, lo2, mid2-1, k); //drop elements after mid2 (inclusive)
            else return findKth(nums1, mid1+1, hi1, nums2, lo2, hi2, k-hlen1-1); //drop elements before mid1 (inclusive)
        } else {
            if(k <= hlen1 + hlen2) return findKth(nums1, lo1, mid1-1, nums2, lo2, hi2, k); //drop elements after mid1 (inclusive)
            else return findKth(nums1, lo1, hi1, nums2, mid2+1, hi2, k-hlen2-1); //drop elements before mid2 (inclusive)
        }
    }
};

// The same idea, iterative solution
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int k = (m+n)/2;
        if((m + n) % 2 == 0) {
            int v1 = findKth(nums1, 0, m-1, nums2, 0, n-1, k-1);
            int v2 = findKth(nums1, 0, m-1, nums2, 0, n-1, k);
            return double(v1+v2)/2;
        } else {
            return findKth(nums1, 0, m-1, nums2, 0, n-1, k);
        }
    }
    int findKth(vector<int>& nums1, int lo1, int hi1, vector<int>& nums2, int lo2, int hi2, int k) {
        while(lo1 <= hi1 && lo2 <= hi2) {
            int mid1 = lo1 + (hi1-lo1)/2;
            int mid2 = lo2 + (hi2-lo2)/2;
            int hlen1 = mid1 - lo1, hlen2 = mid2 - lo2; //number of elements before mid
            if(nums1[mid1] <= nums2[mid2]) {
                if(k <= hlen1 + hlen2) hi2 = mid2-1; //drop elements after mid2 (inclusive)
                else { lo1 = mid1+1; k -= hlen1+1; } //drop elements before mid1 (inclusive)
            } else {
                if(k <= hlen1 + hlen2) hi1 = mid1-1;  //drop elements after mid1 (inclusive)
                else { lo2 = mid2+1; k -= hlen2+1; }  //drop elements before mid2 (inclusive)
            }
        }
        if(lo1 > hi1) return nums2[lo2+k];
        else return nums1[lo1+k];
    }
};

// An old solution. Need further analysis
class Solution {
public:
	double findMedianSortedArrays(int A[], int m, int B[], int n) {
		int k = (m+n)/2; 
		if((m+n)%2 == 0) { //even
			int a = Select(A, m, B, n, k);
			int b = Select(A, m, B, n, k+1);
			return double(a+b)/2.0;
		} else return Select(A, m, B, n, k+1); //odd
	}

	//Binary search algorithm to selelect k-th order statistics from two SORTED arrays. Average O(log(m+n)) time.
	int Select(int A[], int m, int B[], int n, int k) {
		int idx = SelectUtil(A, B, n, 0, m-1, k); //search in A
		if(m == 0) return B[k-1];
		else if(n == 0) return A[k-1];
		
		if(idx != -1) return A[idx];
		else {
			idx = SelectUtil(B, A, m, 0, n-1, k); //search in B
			return B[idx];
		}
	}
    
 	//Utility function to find k-th order static in A+B in A[l .. r], B's size is n
	int SelectUtil(int A[], int B[], int n, int l, int r, int k) {
		if(r < l) return -1;
		int m = (l+r)/2;
		int x = A[m];
		//x is <= m+1 elements in A, check if x is <= k-(m+1) elements in B
		int q = k-m-1;
		if(q < 0 || (q < n && x > B[q])) return SelectUtil(A, B, n, l, m-1, k); //search left (A[l .. m-1])
		if(q > n || (q > 0 && x < B[q-1])) return SelectUtil(A, B, n, m+1, r, k); //search right (A[m+1 .. r])
		if((q == 0 || x >= B[q-1]) && (q == n || x <= B[q])) return m;
	}
};


/**************************************************** 
 ***    003,Medium,Longest Substring Without Repeating Characters 
 ****************************************************/

/*
Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
*/

// Solution 1, use a map to store the position of each character (since s is string, can use an indexed array which is faster than map). Scan from left to right, and maintain a map to store characters already seen and its last position, update length each time.
// Use a pointer (i) to store the current front of substring
// When a character is not in the map, insert it to map; 
// When a character is found and its index is within i and j, then move i to one character to the right of it. 

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> pos(256, -1); //map<char, int> pos;
        int max_len(0);
        for(int i = 0, j = 0; j < s.size(); ++j) {
            char c = s[j];
            if(pos[c] >= i)  i = pos[c]+1;
            pos[c] = j;
            max_len = max(max_len, j-i+1);
        }
        return max_len;
    }
};

// Another solution by counting the occurrences of each character, similar to problem 159.
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
         int n = s.size(); //number of records
         int istart = 0, max_len = 0;
         int count = 0;
         vector<int> dict(256);
         for(int i = 0; i < n; ++i) {
            char c = s[i];
            ++dict[c];
            while(dict[c] > 1) {
               --dict[s[istart++]];
            }
            max_len = max(max_len, i-istart+1);
         }
         return max_len;
    }
};

/**************************************************** 
 ***    002,Medium,Add Two Numbers 
 ****************************************************/

/*
You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Use dummy head. Add additional node if final carry = 1.
// Caveats:
// 1. Don't forget to move l1 and l2 forward!
// 2. Last step, scheck if carry > 0, not carry > 1 !

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0), *p(dummy);
        int sum = 0, carry = 0;
        while(l1 || l2) {
            int v1 = l1 ? l1->val : 0;
            int v2 = l2 ? l2->val : 0;
            sum = v1 + v2 + carry;
            carry = sum / 10;
            sum %= 10;
            p->next = new ListNode(sum);
            p = p->next;
            if(l1) l1 = l1->next;
            if(l2) l2 = l2->next;
        }
        if(carry > 0) p->next = new ListNode(carry);
        
        p = dummy->next;
        delete dummy;
        return p;
    }
};



/**************************************************** 
 ***    001,Medium,Two Sum 
 ****************************************************/

/*
Given an array of integers, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2
*/

// This solution uses a map to store the positions of each number in array. Uses two passes, first pass builds the map, second pass do the two-sum check. For each number if the other number is in then found.
// There is a simpler way to do this, see solution 2.

class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        map<int, int> s; //occurrence index
        vector<int> ret(2, 0);
        int n = numbers.size();
        if(n == 0) return ret;
        //build hash table first
        for(int k = 0; k < n; ++k)  s[numbers[k]] = k;
        //another sweep
        for(int k = 0; k < n; ++k) { 
            //find residue in map
            map<int, int>::iterator it = s.find(target-numbers[k]);
            if(it != s.end() && it->second != k) { //found and not the same entry
                ret[0] = k+1;  ret[1] = it->second+1;
                break;
            }
        }
        return ret;
    }
};

// This solution uses a map to store the positions of each number in array. Only one pass is needed.
// For each number in the array, see if the residue (target - number) already exists in the map, if yes then found; if no, then add it to map
// This also properly handles duplicates, because checking residue happens before insertion. 
// Unordered map (hash table) is faster than map (which is balanced tree) in this case.

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
      unordered_map<int, int> table;
      vector<int> ret(2, -1);
      int n = nums.size();
      for(int i = 0; i < nums.size(); i++) {
        int res = target - nums[i];
        if(table.count(res)) {
           ret[0] = table[res]+1; ret[1] = i+1;
           break;
        } else {
           table[nums[i]] = i;
        }
      }
      return ret;
    }
};

// This version uses insertion sort t sort nums, together with its positions as satellite data. Use two pointers to find the 
// target items, and return their positions. (No hash table is involved)
// Insertion sort: O(n2), search for target: O(n).
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> pos(n);
        for(int i = 0; i < n; ++i) pos[i] = i+1;
        //insertion sort nums
        for(int i = 1; i < n; ++i) {
            int tmp = nums[i];
            int tmp2 = pos[i];
            int j = i-1;
            while(j >= 0 && nums[j] > tmp) {
                nums[j+1] = nums[j]; 
                pos[j+1] = pos[j];
                j--;
            }
            nums[j+1] = tmp;
            pos[j+1] = tmp2;
        }
        
        int l = 0, r = nums.size()-1;
        vector<int> ret(2, 0);
        while(1) {
            int sum = nums[l] + nums[r];
            if(target == sum) {
                ret[0] = min(pos[l], pos[r]), ret[1] = max(pos[l], pos[r]);
                return ret;
            } else if (target > sum) l++;
            else r--;
        }
        return ret;
    }
};


