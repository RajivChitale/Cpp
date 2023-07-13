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
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if( isSameTree(root, subRoot) ) {return true;}
        else if(root==nullptr){return false;}

        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }

    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(!p && !q){return true;} // both empty
        if(!p || !q){return false;} // differ in existence
        if(p->val != q->val){return false;} // differ in value
        return (isSameTree(q->left, p->left) && isSameTree(q->right, p->right));    
    }

};
