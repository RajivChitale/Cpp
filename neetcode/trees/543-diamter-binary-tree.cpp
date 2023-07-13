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
    int ans=0;
    int diameterOfBinaryTree(TreeNode* root) {
        scan(root);
        return ans;
    }

    int scan(TreeNode* n){
        if(n==0){return 0;}
        int l = scan(n->left);
        int r = scan(n->right);
        if(l+r > ans){ans=l+r;}
        return max(l,r)+1;
    }
};
