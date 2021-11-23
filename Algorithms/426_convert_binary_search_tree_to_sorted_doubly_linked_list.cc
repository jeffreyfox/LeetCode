/*
Convert a Binary Search Tree to a sorted Circular Doubly-Linked List in place.

You can think of the left and right pointers as synonymous to the predecessor and successor pointers in a doubly-linked list. For a circular doubly linked list, the predecessor of the first element is the last element, and the successor of the last element is the first element.

We want to do the transformation in place. After the transformation, the left pointer of the tree node should point to its predecessor, and the right pointer should point to its successor. You should return the pointer to the smallest element of the linked list.

 

Example 1:



Input: root = [4,2,5,1,3]


Output: [1,2,3,4,5]

Explanation: The figure below shows the transformed BST. The solid line indicates the successor relationship, while the dashed line means the predecessor relationship.

Example 2:

Input: root = [2,1,3]
Output: [1,2,3]
Example 3:

Input: root = []
Output: []
Explanation: Input is an empty tree. Output is also an empty Linked List.
Example 4:

Input: root = [1]
Output: [1]
 

Constraints:

The number of nodes in the tree is in the range [0, 2000].
-1000 <= Node.val <= 1000
All the values of the tree are unique.
*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/

// Recursive. We need to merge the root with the already done left subtree and right subtree.
// Write a merge function to merge linked lists.

class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if (!root) return nullptr;
        Node *left_head = treeToDoublyList(root->left);
        Node *right_head = treeToDoublyList(root->right);
        // Merge root to the two doubly lists left_head and right_head
        // Make root a doubly linked list of its own
        root->left = root; root->right = root;
        return merge(merge(left_head, root), right_head);
    }
    
    Node* merge(Node* head1, Node* head2) {
        if (!head1) return head2;
        if (!head2) return head1;
        Node *tail1 = head1->left;
        Node *tail2 = head2->left;
        tail1->right = head2;
        head2->left = tail1;
        tail2->right = head1;
        head1->left = tail2;
        return head1;
    }
};
