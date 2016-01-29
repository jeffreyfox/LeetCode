/*
According to the Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."

Given a board with m by n cells, each cell has an initial state live (1) or dead (0). Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):

Any live cell with fewer than two live neighbors dies, as if caused by under-population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by over-population..
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
Write a function to compute the next state (after one update) of the board given its current state.

Follow up: 
Could you solve it in-place? Remember that the board needs to be updated at the same time: You cannot update some cells first and then use their updated values to update other cells.
In this question, we represent the board using a 2D array. In principle, the board is infinite, which would cause problems when the active area encroaches the border of the array. How would you address these problems?
*/

// Solution using bit manipulation to do it in-place.
// Caveat: should store the old value in lower digit! otherwise the nb function cannot properly retrieve the old state from the top left (already processed) and bottom right (not yet processed)

class Solution {
public:
    //bit operation. Use lower digit to represent old state.
    void gameOfLife(vector<vector<int>>& board) {
        if(board.empty() || board[0].empty()) return;
        int m = board.size(), n = board[0].size();
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                int nbcount = nb(board, i, j);
                if(board[i][j] == 1) board[i][j] = (nbcount == 2 || nbcount == 3)*2 + 1;
                else board[i][j] = (nbcount == 3)*2;
            }
        }
        //remove the value from higher digit
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                board[i][j] >>= 1; //remove old value in lower digit
            }
        }
    }
    int nb(vector<vector<int> >& board, int i, int j) {
        int count = 0;
        int m = board.size(), n = board[0].size();
        for(int ii = max(0, i-1); ii <= min(m-1, i+1); ii++) {
            for(int jj = max(0, j-1); jj <= min(n-1, j+1); jj++) {
                count += (board[ii][jj] & 1); //get old value from lower digit
            }
        }
        count -= board[i][j]; //ignore itself
        return count;
    }
};
