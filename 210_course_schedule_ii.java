/// Topological sort and cycle detection

public class Solution {
    
    public int[] findOrder(int numCourses, int[][] prerequisites) {
        
        int[] ret = {};
        
        int ne = prerequisites.length; //number of edges
        
        Digraph g = new Digraph(numCourses);
        for (int i = 0; i < ne; ++i)  //add edges to graph
            g.addEdge(prerequisites[i][1], prerequisites[i][0]);
        
        TopoSort topo = new TopoSort(g);
        if (topo.hasCycle()) return ret; //cyclic, no topological sort
        else {
            ret = new int[g.V()];
            int count = 0;
            for (int v : topo.order()) 
                ret[count++] = v;
        } 
        return ret;
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
    
    //inner class for topological sort
    private class TopoSort {
        
        private char[] color; // white, grey, or black
        private boolean hasCycle;
        private LinkedList<Integer> order; //reverse postorder
        
        public TopoSort(Digraph g) {
            color = new char[g.V()]; //default false
            for (int i = 0; i < g.V(); ++i)
                color[i] = 'w'; //default white
            
            hasCycle = false;
            order = new LinkedList<Integer>();
            
            for (int v = 0; v < g.V(); ++v)
                if (color[v] == 'w')
                    dfs(g, v);
        }
        
        public boolean hasCycle() { return hasCycle; }
        public LinkedList<Integer> order() { return order; }
        
        private void dfs(Digraph g, int v) {
            color[v] = 'g'; //first discovered, color as grey
            for (int w : g.adj(v)) {
                if (hasCycle) return;
                if (color[w] == 'w') dfs(g, w);
                else if (color[w] == 'g') hasCycle = true; //found cycle
            }
            color[v] = 'b'; //finished, color as black
            order.addFirst(v);
        }
    }
}
