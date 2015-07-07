// recursive solution using DFS

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        if (m == 0) return false;
        int n = board[0].size();
        if (n == 0) return false;
        vector<vector<bool>> marked(m, vector<bool>(n, false));
        // run search through all elements in the board
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (exist(board, i, j, word, 0, marked)) return true;
            }
        }
        return false;
    }
    
    //dfs: check if board[i][j] can match word[k]
    bool exist(vector<vector<char>>& board, int i, int j, const string& word, int k, vector<vector<bool>>& marked) {
        if (k == word.size()) return true; //reach end of word
        if (!isValidPos(board, i, j) || marked[i][j]) return false; //not valid or visited before
        if (board[i][j] != word[k]) return false; //not matched
        marked[i][j] = true;
        // try the neighboring 4 positions
        bool res = exist(board, i+1, j, word, k+1, marked) || 
        exist(board, i-1, j, word, k+1, marked) || 
        exist(board, i, j+1, word, k+1, marked) ||
        exist(board, i, j-1, word, k+1, marked);
        marked[i][j] = false;
        return res;
    }
    
    bool isValidPos(vector<vector<char>>& board, int i, int j) {
        int m = board.size();
        int n = board[0].size();
        return (i >= 0 && i < m && j >= 0 && j < n);
    }
};
