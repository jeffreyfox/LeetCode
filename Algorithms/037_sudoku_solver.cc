/*
Write a program to solve a Sudoku puzzle by filling the empty cells.

Empty cells are indicated by the character '.'.

You may assume that there will be only one unique solution.
*/

// DFS backtracking. Use three bits vectors indicating states for rows, colums, and blocks.
// Two passes: first pass initializes state, second pass do dfs and fills empty cells.

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        vector<int> rows(9, 0), cols(9, 0), blks(9, 0);
        initState(board, rows, cols, blks);
        dfs(board, 0, 0, rows, cols, blks);
    }
    
    bool dfs(vector<vector<char> >& board, int ir, int jc, vector<int>& rows, vector<int>& cols, vector<int>& blks) {
        if(ir == 9) return true; // we are done!
        if(board[ir][jc] != '.') { //already filled
            return dfs(board, ir+(jc+1)/9, (jc+1)%9, rows, cols, blks); //move to next
        }
        //not filled
        int ib = (ir/3)*3+jc/3; //block index
        for(char c = '1'; c <= '9'; ++c) { //try 1-9
            int x = (1 << (c-'0'));
            if ( (x & rows[ir]) || (x & cols[jc]) || (x & blks[ib]) ) continue; //can't place
            //can place
            board[ir][jc] = c;
            rows[ir] |= x;  cols[jc] |= x;  blks[ib] |= x;
            //move to next
            if(dfs(board, ir+(jc+1)/9, (jc+1)%9, rows, cols, blks)) return true;
            //backtrack
            board[ir][jc] = '.';
            rows[ir] &= ~x;  cols[jc] &= ~x;  blks[ib] &= ~x;
        }
        return false;
    }

    void initState(vector<vector<char> >& board, vector<int>& rows, vector<int>& cols, vector<int>& blks) {
        //check rows
        for (int ir = 0; ir < 9; ++ir) {
            for (int jc = 0; jc < 9; ++jc) {
                char c = board[ir][jc];
                if(c != '.')  rows[ir] |= (1 << (c -'0'));
            }
        }
        //check columns
        for (int jc = 0; jc < 9; ++jc) {
            for (int ir = 0; ir < 9; ++ir) {
                char c = board[ir][jc];
                if(c != '.')  cols[jc] |= (1 << (c -'0'));
            }
        }
        //check blocks
        for (int ib = 0; ib < 9; ++ib) {
            for (int jb = 0; jb < 9; ++jb) {
                char c = board[3*(ib/3)+jb/3][3*(ib%3)+jb%3];
                if(c != '.')  blks[ib] |= (1 << (c -'0'));
            }
        }
    }
};
