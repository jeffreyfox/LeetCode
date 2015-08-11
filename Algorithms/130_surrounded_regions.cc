/*
 Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,

X X X X
X O O X
X X O X
X O X X

After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X

*/

// Use BFS search instead of DFS to avoid stack-overflow
// First label all 'O' connected to borders as 'T' (BFS)
// Then linearly scan all matrix, mark all 'O' as 'X' and 'T' as 'O'

class Solution {
public:
    struct Position {
        int i, j;
        Position(int ii, int jj) : i(ii), j(jj) {}
        Position(): i(-1), j(-1) {}
    };

    void solve(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return;
        int m = board.size(), n = board[0].size();
        queue<Position> q;
        //mark boundary nodes
        for (int i = 0; i < m; ++i) {
            if(board[i][0] == 'O') set(board, i, 0, q);
            if(board[i][n-1] == 'O') set(board, i, n-1, q);
        }
        for (int j = 1; j < n-1; ++j) {
            if(board[0][j] == 'O') set(board, 0, j, q);
            if(board[m-1][j] == 'O') set(board, m-1, j, q);
        }
        //bfs on boundary nodes, temporary mark as 'T'
        while (!q.empty()) {
            Position pos = q.front(); q.pop();
            int i = pos.i, j = pos.j;
            if(j < n-1 && board[i][j+1] == 'O') set(board, i, j+1, q);
            if(j > 0   && board[i][j-1] == 'O') set(board, i, j-1, q);
            if(i < m-1 && board[i+1][j] == 'O') set(board, i+1, j, q);
            if(i > 0   && board[i-1][j] == 'O') set(board, i-1, j, q);
        }
        //scan all matrix, mark all 'O' as 'X'; mark all 'T' back to 'O'
        for (int i = 0; i < m; ++i)  {
            for (int j = 0; j < n; ++j) {
                if(board[i][j] == 'O') board[i][j] = 'X';
                if(board[i][j] == 'T') board[i][j] = 'O';
            }
        }
    }
    //helper function to set value temporarily as 'T', and push position to queue
    void set(vector<vector<char> >& board, int i, int j, queue<Position>& q) {
        board[i][j] = 'T';
        q.push(Position(i, j));
    }
};
