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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        DFS(res, root, 0);
        return res;
    }

    void DFS(vector<int> &res, TreeNode* curr, int depth){
        if(curr==NULL){
            return;
        }
        if(depth+1 > res.size()) {
            res.push_back(curr->val);
        }
        DFS(res, curr->right, depth+1);
        DFS(res, curr->left, depth+1);
        return;
    }

};
