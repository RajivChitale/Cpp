class Solution {

public:
    vector<string> res;
    string substr;

    void rec_builder(int level, int i, int n)
    {
        if(2*n-i < level){return;} //too many open brackets
        else if(i==2*n) // end scan
        {
            res.push_back(substr);
            return;
        }

        substr.push_back('('); // proceed with '('
        rec_builder(level+1, i+1, n);
        substr.pop_back();

        if(level>0)
        {
            substr.push_back(')');  // proceed with ')'
            rec_builder(level-1, i+1, n);
            substr.pop_back();
        }
        return;
    }

    vector<string> generateParenthesis(int n) {
        rec_builder(0, 0, n);
        return res;
    }
};
