/// Cycle detection of directed graph
/// need to check if an edge is back edge, so need to color vertices as white (undiscovered), grey (discovered but not
/// finished, and black (finished)

public class Solution {
    
    public boolean canFinish(int numCourses, int[][] prerequisites) {
        int ne = prerequisites.length; //number of edges
        
        Digraph g = new Digraph(numCourses);
        for (int i = 0; i < ne; ++i)  //add edges to graph
            g.addEdge(prerequisites[i][1], prerequisites[i][0]);
        
        Cycle cycleFinder = new Cycle(g);
        return !cycleFinder.hasCycle();
    }
    
    //inner class for directed graph representation
    private class Digraph {
        private int V;
        private ArrayList<Integer>[] adj;
        public Digraph(int V) { 
            this.V = V; 
            adj = (ArrayList<Integer>[]) new ArrayList[V];
            for (int i = 0; i < V; ++i) 
                adj[i] = new ArrayList<Integer>();
        }
        public int V() { return V; }
        public void addEdge(int v, int w) { adj[v].add(w); }
        public ArrayList<Integer> adj(int v) { return adj[v]; }
    }
    
    //inner class for cycle detection
    private class Cycle {
        private char[] color; // white, grey, or black
        private boolean hasCycle;
        
        public Cycle(Digraph g) {
            color = new char[g.V()]; //default false
            for (int i = 0; i < g.V(); ++i)
                color[i] = 'w'; //default white
            
            hasCycle = false;
        
            for (int v = 0; v < g.V(); ++v)
                if (color[v] == 'w')
                    dfs(g, v);
        }
        
        private void dfs(Digraph g, int v) {
           color[v] = 'g'; //first discovered, color as grey
            for (int w : g.adj(v)) {
                if (hasCycle) return;
                if (color[w] == 'w') dfs(g, w);
                else if (color[w] == 'g') hasCycle = true; //found cycle
            }
            color[v] = 'b'; //finished, color as black
        }
        public boolean hasCycle() { return hasCycle; }
    }
}
