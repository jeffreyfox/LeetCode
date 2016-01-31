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

/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */

/// One pass solution using DFS. Make sure only visit unvisited nodes. First create a copy for current node, and then process its neighors,
/// It neighbor already visited (indicated by the map), then use the copy as the new neighbor, otherwise dfs on the neighbor.
/// Maintain a map from old node to new node, which also serves as the visited marker

class Solution {
public:
    typedef UndirectedGraphNode Node;
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(!node) return NULL;
        return dfs(node);
    }
    Node* dfs(Node* node) {
        Node* newnode = new Node(node->label);
        dict[node] = newnode; //insert to map before processing neighbors (handle self-loops)
        newnode->neighbors = node->neighbors;
        for(int i = 0; i < node->neighbors.size(); i++) {
            if(dict.count(node->neighbors[i])) newnode->neighbors[i] = dict[node->neighbors[i]];
            else newnode->neighbors[i] = dfs(node->neighbors[i]);
        }
        return newnode;
    }
    unordered_map<Node*, Node*> dict;
};

/// Solution 2, slightly different one. In DFS, first check if node is visited or not. If visited, just return the copy.

class Solution {
public:
    typedef UndirectedGraphNode Node;
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(!node) return NULL;
        return dfs(node);
    }
    Node* dfs(Node* node) {
        if(dict.count(node)) return dict[node];
        Node* newnode = new Node(node->label);
        dict[node] = newnode; //insert to map before processing neighbors (handle self-loops)
        newnode->neighbors = node->neighbors;
        for(int i = 0; i < node->neighbors.size(); i++) {
            newnode->neighbors[i] = dfs(node->neighbors[i]);
        }
        return newnode;
    }
    unordered_map<Node*, Node*> dict;
};

