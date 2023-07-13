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
    vector<vector<int>> order;

    vector<vector<int>> levelOrder(TreeNode* root) {
        DFS(root,0);
        return order;
    }

    void DFS(TreeNode* n, int depth){
        if(!n){return;}

        if(order.size()<depth+1){
            vector<int> temp(1, n->val);
            order.push_back(temp);
        }
        else {
            order[depth].push_back(n->val);
        }

        DFS(n->left, depth+1);
        DFS(n->right, depth+1);
    }
        
};
