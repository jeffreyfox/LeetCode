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
