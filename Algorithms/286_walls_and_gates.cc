/*
You are given a m x n 2D grid initialized with these three possible values.

-1 - A wall or an obstacle.
0 - A gate.
INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

For example, given the 2D grid:
INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
  0  -1 INF INF
After running your function, the 2D grid should be:
  3  -1   0   1
  2   2   1  -1
  1  -1   2  -1
  0  -1   3   4
*/

// 2021.
// Standard multi-source BFS using a queue.
class Solution {
public:    
    const int kInf = 2147483647;
    using coord = pair<int, int>;
    void wallsAndGates(vector<vector<int>>& rooms) {
        deque<coord> q;
        int m = rooms.size(), n = rooms[0].size();
        // First run push gates to queue
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int val = rooms[i][j];                
                if (val == 0) q.push_back(make_pair(i, j));
            }
        }
        
        // Next do BFS starting the gates
        while (!q.empty()) {
            const auto v = q.front(); q.pop_front();
            const int i = v.first, j = v.second;
            const int distance = rooms[i][j] + 1;
            if (ShouldVisit(rooms, m, n, i+1, j)) {
                rooms[i+1][j] = distance; q.push_back(make_pair(i+1, j));
            }
            if (ShouldVisit(rooms, m, n, i-1, j)) {
                rooms[i-1][j] = distance; q.push_back(make_pair(i-1, j));
            }
            if (ShouldVisit(rooms, m, n, i, j+1)) {
                rooms[i][j+1] = distance; q.push_back(make_pair(i, j+1));
            }
            if (ShouldVisit(rooms, m, n, i, j-1)) {
                rooms[i][j-1] = distance; q.push_back(make_pair(i, j-1));
            }
        }
    }
    
    // Returns true if we should visit this room i, j
    bool ShouldVisit(vector<vector<int>>& rooms, int m, int n, int i, int j) {
        if (i < 0 || i >= m || j < 0 || j >= n) return false;
        return (rooms[i][j] == kInf);
    }
};

// 2015.
// Standard multi-source BFS. First identify all sources, then BFS using two vectors.

class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        if(rooms.empty() || rooms[0].empty()) return;
        int m = rooms.size(), n = rooms[0].size();
        vector<pair<int, int> > curr, next;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(rooms[i][j] == 0) curr.push_back(make_pair(i, j));
            }
        }
        int d = 0; //distance from gate
        while(!curr.empty()) {
            d++; //increase distance
            for(auto pos : curr) {
                int i = pos.first, j = pos.second;
                //try 4 neighbors
                if(i > 0 && rooms[i-1][j] == INT_MAX) { rooms[i-1][j] = d;  next.push_back(make_pair(i-1, j)); }
                if(j > 0 && rooms[i][j-1] == INT_MAX) { rooms[i][j-1] = d;  next.push_back(make_pair(i, j-1)); }
                if(i < m-1 && rooms[i+1][j] == INT_MAX) { rooms[i+1][j] = d;  next.push_back(make_pair(i+1, j)); }
                if(j < n-1 && rooms[i][j+1] == INT_MAX) { rooms[i][j+1] = d;  next.push_back(make_pair(i, j+1)); }
            }
            curr.swap(next);
            next.clear();
        }
    }
};
