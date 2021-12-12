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

// 2021.12. Simple solution that only works for k=2 case.
class ZigzagIterator {
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) : v1(v1), v2(v2) {
        i = 0; j = 0; reverse = false;        
    }

    int next() {
        if (i == v1.size()) return v2[j++];
        if (j == v2.size()) return v1[i++];
        if (reverse) {
            reverse = !reverse;
            return v2[j++];        
        } else {
            reverse = !reverse;
            return v1[i++];
        }
    }

    bool hasNext() {
        if (i == v1.size()) return j < v2.size();
        if (j == v2.size()) return i < v1.size();
        if (reverse) return j < v2.size();
        else return i < v1.size();
    }
private:
    int i, j;
    bool reverse;
    vector<int> &v1, &v2;
};

// Solution 1. Maintain an array of pointers, which always points to the the next valid value. After obtaining the next value, move pointer to next valid value.

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
        if(i == arrayIdx && indices[i] == nums[i].size()) arrayIdx = n; // no available elements, set arrayIdx to n
        else arrayIdx = i; //found next available array index

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

// Solution 2. Maintain a queue of iterator pairs, each pair corresponding to the beginning and end of an array. Each time dequeue a pair,
// and if the array is not exhausted, enqueue again.
class ZigzagIterator {
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        if(!v1.empty()) q.push(make_pair(v1.begin(), v1.end()));
        if(!v2.empty()) q.push(make_pair(v2.begin(), v2.end()));
    }

    int next() {
        auto beg = q.front().first;
        auto end = q.front().second;
        q.pop();
        if(beg+1 < end) q.push(make_pair(beg+1, end));
        return *beg;
    }

    bool hasNext() {
        return !q.empty();
    }
    queue<pair<vector<int>::iterator, vector<int>::iterator> > q;
};
