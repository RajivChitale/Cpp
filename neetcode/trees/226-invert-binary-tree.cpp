/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* invertTree(TreeNode* n) {
        if(n==nullptr){return nullptr;}
        if(n->left!=nullptr){invertSubtree(n->left);}
        if(n->right!=nullptr){invertSubtree(n->right);}
        swap(n->left, n->right);
        return n;
    }

    void invertSubtree(TreeNode* n){
        if(n==nullptr){return;}
        if(n->left!=nullptr){invertSubtree(n->left);}
        if(n->right!=nullptr){invertSubtree(n->right);}
        swap(n->left, n->right);
        return;
    }
};
