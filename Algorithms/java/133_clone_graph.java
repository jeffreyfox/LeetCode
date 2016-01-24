/**
 * Definition for undirected graph.
 * class UndirectedGraphNode {
 *     int label;
 *     List<UndirectedGraphNode> neighbors;
 *     UndirectedGraphNode(int x) { label = x; neighbors = new ArrayList<UndirectedGraphNode>(); }
 * };
 */
 
/// DFS solution. For each node, create a new node. Use a map to store the mapping between old node and new node.
/// When procesing an old node's neighbor list, check if the neighbor node is in the map or not.
/// If neighbor is in the map, it is previously visited, then add the new node reference in the map to new nodes' neighbor list
/// If neighbor is not in the map, create a new neighbor and add it to the new nodes' neighborlist

public class Solution {
    public UndirectedGraphNode cloneGraph(UndirectedGraphNode node) {
        if (node == null) return null;
        HashMap<UndirectedGraphNode, UndirectedGraphNode> visitedMap = new HashMap<UndirectedGraphNode, UndirectedGraphNode>();
        UndirectedGraphNode newnode = new UndirectedGraphNode(node.label);
        dfs(node, newnode, visitedMap); //add neighbor lists
        return newnode;
    }
    private void dfs(UndirectedGraphNode node, UndirectedGraphNode newnode, HashMap<UndirectedGraphNode, UndirectedGraphNode> visitedMap) {
        visitedMap.put(node, newnode);
        for (UndirectedGraphNode nbr : node.neighbors) {
            if (!visitedMap.containsKey(nbr)) { // a new node
                UndirectedGraphNode newnbr = new UndirectedGraphNode(nbr.label);
                newnode.neighbors.add(newnbr); // add to neighbor list
                dfs(nbr, newnbr, visitedMap);
            } else { // a visited node, find in map
                UndirectedGraphNode newnbr = visitedMap.get(nbr);
                newnode.neighbors.add(newnbr); // add to neighbor list
            }
        }    
    }
}
