/// iterative solution

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
