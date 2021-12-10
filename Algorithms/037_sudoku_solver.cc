/*
Write a program to solve a Sudoku puzzle by filling the empty cells.

Empty cells are indicated by the character '.'.

You may assume that there will be only one unique solution.
*/

/*
DFS backtracking. Using a helper function canPlace.

Have dfs return true or false so that once a solution is find, terminate search immediately.

We use an iterative function to find the next unfilled position instead of recursively to reduce stack size.
*/

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        dfs(0, 0, board);                
    }
    
    bool dfs(int row, int col, vector<vector<char>>& board) {
        if (row == 9) return true;
        if (board[row][col] != '.') {
            auto next = FindNext(row, col, board);
            return dfs(next.first, next.second, board);
        }
        for (char c = '1'; c <= '9'; ++c) {
            if (canPlace(row, col, c, board)) {
                board[row][col] = c;
                auto next = FindNext(row, col, board);
                if (dfs(next.first, next.second, board)) return true;
                // backtrack
                board[row][col] = '.';
            }
        }
        return false;
    }
    
    pair<int, int> FindNext(int row, int col, const vector<vector<char>>& board) {
        while (row < 9 && col < 9) {
            if (col < 8) col++;
            else { row++; col = 0;}
            if (row == 9) return {row, col};
            if (board[row][col] == '.') break;
        }
        return make_pair(row, col);
    }
    
    bool canPlace(int row, int col, char c, const vector<vector<char>>& board) {
        // check row
        for (int jcol = 0; jcol < 9; ++jcol) {
            if (board[row][jcol] == c) return false;
        }
        // check col
        for (int irow = 0; irow < 9; ++irow) {
            if (board[irow][col] == c) return false;
        }
        // check block
        int iblk = row/3, jblk = col/3; //block offset
        for(int l = 0; l < 9; l++) { // try all entries within the block
            int irow = iblk*3 + l/3, jcol = jblk*3 + l%3;
            if(board[irow][jcol] == c) return false;
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
