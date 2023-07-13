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
    int res =0;

    int goodNodes(TreeNode* root) {
        DFS(root, -10000);
        return res;
    }

    void DFS(TreeNode* curr, int max){
        if(!curr){return;}
        if(curr->val >= max){max = curr->val; res++;}

        DFS(curr->left, max);
        DFS(curr->right, max);
        return;
    }
};
