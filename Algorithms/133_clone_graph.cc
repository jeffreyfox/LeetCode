/*
 Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.

OJ's undirected graph serialization:

Nodes are labeled uniquely.
We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.

As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as separated by #.

    First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
    Second node is labeled as 1. Connect node 1 to node 2.
    Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.

Visually, the graph looks like the following:

       1
      / \
     /   \
    0 --- 2
         / \
         \_/

*/


/// Two pass solution. First use DFS to build new nodes, and maintain map from old node to new node
/// Second step simply traverse the map and build neighbor lists.

/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    typedef UndirectedGraphNode Node;

    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(!node) return NULL;
        map<Node*, Node*> lookup;
        //build nodes
        dfs(node, lookup);
        //build neighbor lists
        for(map<Node*, Node*>::const_iterator it = lookup.begin(); it != lookup.end(); ++it) {
            Node *oldnode = it->first, *newnode = it->second;
            newnode->neighbors = oldnode->neighbors; //copy neighbor list
            for (size_t i = 0; i < oldnode->neighbors.size(); ++i) {
                newnode->neighbors[i] = lookup[oldnode->neighbors[i]];
            }
        }
        return lookup[node];
    }
    //build new nodes and look-up table from old to new
    void dfs(Node *node, map<Node*, Node*>& lookup) {
        if(lookup.count(node) == 0) {
            lookup[node] = new Node(node->label);
            for (size_t i = 0; i < node->neighbors.size(); ++i) {
                dfs(node->neighbors[i], lookup);
            }
        }
    }
};
