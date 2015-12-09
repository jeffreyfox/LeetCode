/*
Write a program to solve a Sudoku puzzle by filling the empty cells.

Empty cells are indicated by the character '.'.

You may assume that there will be only one unique solution.
*/

/*
DFS backtracking. Using a helper function canPlace (44ms).
Two passes: first pass initializes state, second pass do dfs and fills empty cells.

Have dfs return true or false so that once a solution is find, terminate search immediately.

Caveats:
1. numbers start from 1, not 0.
2. when to terminate? i == 9, not j == 9!. 
*/

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
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
        for(char c = '1'; c <= '9'; c++) {
            if(canPlace(board, i, j, c)) {
                board[i][j] = c;
                if(dfs(board, inext, jnext)) return true;
            }
            board[i][j] = '.'; //reset back to '.'
        }
        return false; //tried all possibilities
    }

    bool canPlace(vector<vector<char> >& board, int i, int j, char c) {
        for(int irow = 0; irow < 9; irow++)
            if(irow != i && board[irow][j] == c) return false;
        
        for(int jcol = 0; jcol < 9; jcol++)    
            if(jcol != j && board[i][jcol] == c) return false;
        
        int iblk = i-i%3, jblk = j-j%3; //block offset
        for(int l = 0; l < 9; l++) { // try all entries within the block
            int irow = iblk + l/3, jcol = jblk + l%3;
            if(irow != i && jcol != j && board[irow][jcol] == c) return false;
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
