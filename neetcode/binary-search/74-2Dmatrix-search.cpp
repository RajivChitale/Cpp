class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        int l = 0;
        int r = rows*cols-1;
        int mid=0;
        int e;

        while(l<=r)
        {
            mid = (l+r)/2;
            e = matrix[mid/cols][mid%cols];

            if(l==r && e!=target) {return false;}
            if(e<target) {l=mid+1;}
            else if(e>target) {r=mid;}
            else {return true; }

        }


        return false;
    }
};
