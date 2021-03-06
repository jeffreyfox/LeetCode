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
    void solve(vector<vector<char>>& board) {
        if(board.empty() || board[0].empty()) return;
        int m = board.size(), n = board[0].size();
        //bfs, starting from boundary 'O's
        vector<pair<int, int> > curr, next;
        for(int i = 0; i < m; i++) {
            testSet(board, i, 0, curr);
            testSet(board, i, n-1, curr);
        }
        for(int j = 1; j < n-1; j++) {
            testSet(board, 0, j, curr);
            testSet(board, m-1, j, curr);
        }
        //now do bfs
        while(!curr.empty()) {
            for(auto pos : curr) {
                int ir = pos.first, jc = pos.second;
                if(ir > 0)    testSet(board, ir-1, jc, next);
                if(ir < m-1)  testSet(board, ir+1, jc, next);
                if(jc > 0)    testSet(board, ir, jc-1, next);
                if(jc < n-1)  testSet(board, ir, jc+1, next);
            }
            curr.swap(next);
            next.clear();
        }
        //now set all 'O' to 'X' and all 'T' back to 'O'
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(board[i][j] == 'O') board[i][j] = 'X';
                else if(board[i][j] == 'T') board[i][j] = 'O';
            }
        }
    }
    //helper function to set value 'O' temporarily as 'T', and push position to queue
    void testSet(vector<vector<char>>& board, int i, int j, vector<pair<int, int> >& q) {
        if(board[i][j] == 'O') {
            board[i][j] = 'T';
            q.push_back(make_pair(i, j));
        }
    }
};

// DFS search version, causes runtime error due to stack overflow (stack runs too deep)
// First label all 'O' connected to borders as 'T' (BFS)
// Then linearly scan all matrix, mark all 'O' as 'X' and 'T' as 'O'

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return;
        int m = board.size(), n = board[0].size();
        //dfs on boundary nodes, temporary mark as 'T'
        for (int i = 0; i < m; ++i) {
            if(board[i][0] == 'O') dfs(board, i, 0);
            if(board[i][n-1] == 'O') dfs(board, i, n-1);
        }
        for (int j = 1; j < n-1; ++j) {
            if(board[0][j] == 'O') dfs(board, 0, j);
            if(board[m-1][j] == 'O') dfs(board, m-1, j);
        }
        //scan all matrix, mark all 'O' as 'X'; mark all 'T' back to 'O'
        for (int i = 0; i < m; ++i)  {
            for (int j = 0; j < n; ++j) {
                if(board[i][j] == 'O') board[i][j] = 'X';
                if(board[i][j] == 'T') board[i][j] = 'O';
            }
        }
    }
    void dfs(vector<vector<char> >& board, int i, int j) {
        int m = board.size(), n = board[0].size();
        board[i][j] = 'T';
        // check four neighbors
        if(j < n-1 && board[i][j+1] == 'O') dfs(board, i, j+1);
        if(j > 0   && board[i][j-1] == 'O') dfs(board, i, j-1);
        if(i < m-1 && board[i+1][j] == 'O') dfs(board, i+1, j);
        if(i > 0   && board[i-1][j] == 'O') dfs(board, i-1, j);
    }
};

