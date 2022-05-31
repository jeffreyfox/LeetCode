/*
Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.

A partially filled sudoku which is valid.

Note:
A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated. 
*/

// Vanilla solution using a state vector.
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<bool> states(9, false);
        
        // check rows
        for (int ir = 0; ir < 9; ++ir) {
            std::fill(states.begin(), states.end(), false);
            for (int jc = 0; jc < 9; ++jc) {
                char c = board[ir][jc];
                if (c == '.') continue;
                if (states[c-'1']) return false;
                states[c-'1'] = true;
            }
        }

        // check columns
        for (int jc = 0; jc < 9; ++jc) {
            std::fill(states.begin(), states.end(), false);
            for (int ir = 0; ir < 9; ++ir) {
                char c = board[ir][jc];
                if (c == '.') continue;
                if (states[c-'1']) return false;
                states[c-'1'] = true;
            }
        }

        // check blocks
        for (int ib = 0; ib < 9; ++ib) {
            std::fill(states.begin(), states.end(), false);
            for (int jb = 0; jb < 9; ++jb) {
                char c = board[3*(ib/3)+jb/3][3*(ib%3)+jb%3];
                if (c == '.') continue;
                if (states[c-'1']) return false;
                states[c-'1'] = true;
            }
        }
        return true;
    }
};

/// Check each row, column and block, record the state of each check.
/// Can use a single integer to record the state, using bit operations
///  1  1  1  1  1  1  1  1  1
/// '9'       ...           '1'
/// caveat: when calculating i/j index based on block index, 3*(ib/3)+jb/3 != (3*ib+jb)/3 
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int state = 0;

        //check rows
        for (int ir = 0; ir < 9; ++ir) {
            state = 0;
            for (int jc = 0; jc < 9; ++jc) {
                char c = board[ir][jc];
                if(c == '.') continue;
                int x = 1 << (c -'0');
                if (state & x) return false;
                state |= x;
            }
        }
        //check columns
        for (int jc = 0; jc < 9; ++jc) {
            state = 0;
            for (int ir = 0; ir < 9; ++ir) {
                char c = board[ir][jc];
                if(c == '.') continue;
                int x = 1 << (c -'0');
                if (state & x) return false;
                state |= x;
            }
        }
        //check blocks
        for (int ib = 0; ib < 9; ++ib) {
            state = 0;
            for (int jb = 0; jb < 9; ++jb) {
                char c = board[3*(ib/3)+jb/3][3*(ib%3)+jb%3];
                if(c == '.') continue;
                int x = 1 << (c -'0');
                if (state & x) return false;
                state |= x;
            }
        }
        return true;
    }
};

//Another solution using 3 bit vectors
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<int> row(9, 0), col(9, 0), block(9, 0); //bit status array
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j) {
                if(board[i][j] != '.') {
                    int k = i/3*3 + j/3;
                    int state = 1 << (board[i][j] - '1');
                    if(state & (row[i] | col[j] | block[k])) return false;
                    row[i] |= state;
                    col[j] |= state;
                    block[k] |= state;
                }
            }
        }
        return true;
    }
};

