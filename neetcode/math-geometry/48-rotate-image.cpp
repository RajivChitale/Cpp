class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix[0].size();
        int temp, temp2;
        int m=0;
        if(n%2==1){m=1;}
    
        for(int i=0; i<n/2; i++){
            for(int j=0; j<n/2+m; j++){
                temp = matrix[i][j];

                for(int t=0; t<4; t++){
                    temp2= n-1-i;
                    i = j;
                    j = temp2;

                    swap(temp, matrix[i][j]);
                }

            }
        }
        return;

    }
};
