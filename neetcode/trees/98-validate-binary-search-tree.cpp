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
    int past;
    bool bound = false;

    bool isValidBST(TreeNode* root) {
        return DFS(root);
    }

    bool DFS(TreeNode* curr){
        if(!curr){return true;}
        bool res = DFS(curr->left);

        if(bound && curr->val <= past){
            return false;
        }
        
        bound = true;
        past = curr->val;

        return res && DFS(curr->right);
    }

};
