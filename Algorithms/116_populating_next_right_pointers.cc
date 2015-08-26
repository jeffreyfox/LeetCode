/*
Given a binary tree

    struct TreeLinkNode {
      TreeLinkNode *left;
      TreeLinkNode *right;
      TreeLinkNode *next;
    }

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

    You may only use constant extra space.
    You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).

For example,
Given the following perfect binary tree,

         1
       /  \
      2    3
     / \  / \
    4  5  6  7

After calling your function, the tree should look like:

         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL
*/

// General solution that works for all kinds of trees
// Use a dummy head in current layer.
// Use last layer to help progress the current layer

/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */

class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        TreeLinkNode dum1(0), *head(&dum1); //dummy head
        TreeLinkNode *last(root), *curr(NULL); //head of last row, and curr tail node
        while(last) {
            curr = head;
            while(last) {
                if(!last->left && !last->right) {
                    last = last->next;
                    continue;
                }
                curr->next = (last->left ? last->left : last->right);
                curr = curr->next;
                if(curr == last->left && last->right) {
                    curr->next = last->right;
                    curr = curr->next;
                }
                last = last->next;
            }
            last = head->next; //move to new row
            head->next = NULL; //reset to NULL!
        }
    }
};
