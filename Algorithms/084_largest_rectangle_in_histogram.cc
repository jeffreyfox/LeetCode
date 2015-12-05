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

/// Solution 1 using a stack of both position and height. No need to handle degenerate cases separately.
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
