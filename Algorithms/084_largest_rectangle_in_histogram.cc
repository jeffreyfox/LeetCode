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


