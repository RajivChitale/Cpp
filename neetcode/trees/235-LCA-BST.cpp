/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* curr=root;
        while(1){
            if(curr->val == p->val || curr->val ==q->val) {return curr;} //equal to p or q
            else if( (curr->val > p->val) != (curr->val > q->val)){
                return curr;
            }
            else if(curr->val > p->val){curr=curr->left;}
            else if(curr->val < p->val){curr=curr->right;}
        }
    }
};
