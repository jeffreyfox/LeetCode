/*
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]

word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
*/

/* 
Recursive solution using DFS
Several optimizations:
1. Do not use another array to store the visited status of the board. Instead, set the visited board character as '*', and set it back to original at retrace stage.
2. For checking validity of new positions, leave it to the recursive function (if not legal simply return false). If do something like this, will lead to TLE.

        if(i > 0 && board[i-1][j] != '*' && existHelper(board, i-1, j, word, k+1)) return true;
        if(i < m-1 && board[i+1][j] != '*' && existHelper(board, i+1, j, word, k+1)) return true;
        if(j > 0 && board[i][j-1] != '*' && existHelper(board, i, j-1, word, k+1)) return true;
        if(j < n-1 && board[i][j+1] != '*' && existHelper(board, i, j+1, word, k+1)) return true;

*/

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if(board.empty() || board[0].empty()) return false;
        if(word.empty()) return true;
        int m = board.size(), n = board[0].size();
        if(m*n < word.size()) return false;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(existHelper(board, i, j, word, 0)) return true;
            }
        }
        return false;
    }
    bool existHelper(vector<vector<char> >& board, int i, int j, const string& word, int k) {
        if(k == word.size()) return true; //found
        int m = board.size(), n = board[0].size();
        if(i < 0 || i >= m || j < 0 || j >= n) return false; //not legal position
        if(board[i][j] == '*') return false; //already visited
        if(board[i][j] != word[k]) return false; //not match
        char c = board[i][j];
        board[i][j] = '*';
        //matches, move to next one
        if(existHelper(board, i-1, j, word, k+1)) return true;
        if(existHelper(board, i+1, j, word, k+1)) return true;
        if(existHelper(board, i, j-1, word, k+1)) return true;
        if(existHelper(board, i, j+1, word, k+1)) return true;
        
        board[i][j] = c; //retrace
        return false;
    }
};

// An old iterative solution
class Solution {
public:
	//move from current position (row,col) to next position
	void move(int &row, int &col, int dir) {
		if(dir == 1) col += 1; //right
		else if(dir == 2) row -= 1; //up
		else if(dir == 3) col -= 1; //left
		else if(dir == 4) row += 1; //down
		else row = col = -1; //not move
	}
	//check if position (row, col) exceeds boundary
	bool isValid(int row, int col, int m, int n) {
		return(row >= 0 && row < m && col >= 0 && col < n);
	}
	bool exist(vector<vector<char> > &board, string word) {
		int m = board.size();
		int n = board[0].size();
		int tot = m*n;
		int len = word.size();
		int k = 0; //k-th character in word
		vector<int> dir(len, 1);  //directions at step k
		vector<int> row(len, -1); //row number at step k
		vector<int> col(len, -1); //column number at step k
		vector<vector<bool> > visited(m, vector<bool>(n, false));//site visited? 
		
		for(int l = 0; l < tot; ++l) { //loop thru all elements in the board
			//invariant: k characters matched (now matching word[k] with position[k] determined from position[k-1] and dir[k-1])
			k = 0; //reset k everytime!
			while(1) {
			    if(k == len) return true; //already found!
			    if(k > 0 && dir[k-1] > 4) { //tried all directions, retrace
			    	dir[k-1] = 1; //reset to first direction
			    	visited[row[k-1]][col[k-1]] = false; //reset
				    row[k-1] = col[k-1] = -1;
				    k--;
				    if(k == 0) break; //breaking condition
				    dir[k-1] ++; //last one should increment
				    continue;
				}
			    //find next position
			    int nextRow = row[k-1], nextCol = col[k-1];
			    if(k == 0) { nextRow = l/n; nextCol = l%n; }
			    else move(nextRow, nextCol, dir[k-1]);
			    
			    //check match?
			    if(k == 0) { //first character special case
				    if(board[nextRow][nextCol] != word[k]) break; 
				    else { //matched first character
				        row[k] = nextRow; col[k] = nextCol;
				        visited[row[k]][col[k]] = true;
				        k++; //try next one
				    }
				} else if(!isValid(nextRow, nextCol, m, n) || board[nextRow][nextCol] != word[k] || visited[nextRow][nextCol]) { //no match
    				dir[k-1] ++;
				} else { //found match
		    	    row[k] = nextRow; col[k] = nextCol;
			        visited[row[k]][col[k]] = true; //update visited
			        k++;
				}
			}
		}
		return false;
	}
};


