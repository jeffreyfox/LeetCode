/*
Design an iterator to flatten a 2D vector. It should support the next and hasNext operations.

Implement the Vector2D class:

Vector2D(int[][] vec) initializes the object with the 2D vector vec.
next() returns the next element from the 2D vector and moves the pointer one step forward. You may assume that all the calls to next are valid.
hasNext() returns true if there are still some elements in the vector, and false otherwise.
 

Example 1:

Input
["Vector2D", "next", "next", "next", "hasNext", "hasNext", "next", "hasNext"]
[[[[1, 2], [3], [4]]], [], [], [], [], [], [], []]
Output
[null, 1, 2, 3, true, true, 4, false]

Explanation
Vector2D vector2D = new Vector2D([[1, 2], [3], [4]]);
vector2D.next();    // return 1
vector2D.next();    // return 2
vector2D.next();    // return 3
vector2D.hasNext(); // return True
vector2D.hasNext(); // return True
vector2D.next();    // return 4
vector2D.hasNext(); // return False
 

Constraints:

0 <= vec.length <= 200
0 <= vec[i].length <= 500
-500 <= vec[i][j] <= 500
At most 105 calls will be made to next and hasNext.
 

Follow up: As an added challenge, try to code it using only iterators in C++ or iterators in Java.
*/
 
// Solution 1 using two pointers: i is the outer pointer and j is the inner pointer. When calling next() and hasNext(), we call the function moveToNext(). This function
// moves the cursors to the next element if needed.
// - If j already points to the next element, then no op.
// - Otherwise, j must be pointing to the end of vec[i], we then move down to the next rows until we find a non-empty row or read the end.
class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec) : v(vec), i(0), j(0) {        
    }
    
    int next() {
        moveToNext();
        return v[i][j++];
    }
    
    bool hasNext() {
        moveToNext();        
        return i < v.size();
    }
    
    // Move the cursor to the next element.
    // If j already points to the next element, then no op.
    // Otherwise, j must be pointing to the end of vec[i], we then move down to
    // the next rows until we find a non-empty row or read the end.
    void moveToNext() {
        while (i < v.size() && j == v[i].size()) {
            i++;
            j = 0;
        }
    }
    
private:
    vector<vector<int>> &v;
    int i, j;
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D* obj = new Vector2D(vec);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */

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
