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

// Solution 2. Similar to 281. Use a stack to store the pair of iterators
class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d) {
        for(auto vit = vec2d.rbegin(); vit != vec2d.rend(); vit++) {
            if(!vit->empty()) s.push(make_pair(vit->begin(), vit->end()));
        }
    }

    int next() {
        auto beg = s.top().first;
        auto end = s.top().second;
        s.pop();
        if(beg+1 < end) s.push(make_pair(beg+1, end));
        return *beg;
    }

    bool hasNext() {
        return !s.empty();
    }
    stack<pair<vector<int>::iterator, vector<int>::iterator> > s;
};
