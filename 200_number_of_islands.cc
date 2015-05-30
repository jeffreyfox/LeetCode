/// depth-first search of undirected graph
/// need to search all 4 directions, even though initial direction goes right and down (in the middle, may need to search up and left as well, such as an 'H' shape island)
public class Solution {
    private int count = 0;
    
    public int numIslands(char[][] grid) {
        int m = grid.length;
        if (m == 0) return 0;
        int n = grid[0].length;
        if (n == 0) return 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    dfs(grid, i, j);
                    count++;
                }
            }
        }
        return count;
    }
    private void dfs(char[][] grid, int i, int j) {
        int m = grid.length;
        int n = grid[0].length;
        
        grid[i][j] = '0'; // markd site as visited
        // top
        if (i > 0 && grid[i-1][j] == '1') dfs(grid, i-1, j);
        // bottom
        if (i < m-1 && grid[i+1][j] == '1') dfs(grid, i+1, j);
        // left
        if (j > 0 && grid[i][j-1] == '1') dfs(grid, i, j-1);
        // right
        if (j < n-1 && grid[i][j+1] == '1') dfs(grid, i, j+1);
    }
}
