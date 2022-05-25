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

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

/// Solution 1 using DFS. Make sure only visit unvisited nodes. First create a copy for current node, and then recursively process its neighors,
/// Maintain a map from old node to new node, which also serves as the visited marker
/// Remember to insert the old-new node mapping after new node creation!

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) return nullptr;
        if (dict.count(node)) return dict[node];
        Node* new_node = new Node(node->val);
        dict[node] = new_node;
        for (auto* v : node->neighbors) {
            Node* new_v = cloneGraph(v);
            new_node->neighbors.push_back(new_v);
        }
        return new_node;
    }
    
private:
    unordered_map<Node*, Node*> dict;
};

/// Solution 2 using BFS. BFS on the old graph, and create new nodes before appending to the queue. Add edges from parent to child when processing the
/// neighbor list.
/// Remember to insert the old-new node mapping after new node creation!

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) return nullptr;
        bfs(node);
        return dict[node];
    }
    
    void bfs(Node* node) {
        dict[node] = new Node(node->val);        
        q.push_back(node);
        while (!q.empty()) {
            Node* old_node = q.front(); q.pop_front();
            Node* new_node = dict[old_node];
            for (Node* nb : old_node->neighbors) {
                if (!dict.count(nb)) {
                    dict[nb] = new Node(nb->val);
                    q.push_back(nb);
                }
                new_node->neighbors.push_back(dict[nb]);                
            }
        }
    }
private:
    unordered_map<Node*, Node*> dict;
    deque<Node*> q;
};
