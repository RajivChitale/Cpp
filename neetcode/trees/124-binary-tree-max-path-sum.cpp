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
    int maxval=0;
    int maxPathSum(TreeNode* root) {
        if(root!=nullptr){maxval = root->val;}
        scan(root);
        return maxval;
    }

    int scan(TreeNode* n){
        if(!n){return 0;}
        int l = scan(n->left);
        int r = scan(n->right);
        if(l+r+n->val > maxval) { maxval= l+r+n->val;}
        return max(0, max(l,r) + n->val); //propogate if value is positive
    }
};
