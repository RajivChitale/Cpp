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
    int counter;
    int res; 

    int kthSmallest(TreeNode* root, int k) {
        counter = 0;
        DFS(root, k);
        return res;
    }

    bool DFS(TreeNode* curr, int k){
        if(!curr){return false;}
        if(DFS(curr->left, k)){return true;}
        counter++;
        if(counter==k){res = curr->val; return true;}
        return DFS(curr->right, k);   
    }
};
