class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int rows=matrix.size();
        int cols=matrix[0].size();
        int basei=-1;
        int basej=-1;

        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){

                if(basei==-1 && matrix[i][j]==0){
                    basei=i;
                    basej=j;
                }

                else if(matrix[i][j]==0){
                    matrix[basei][j]=0;
                    matrix[i][basej]=0;
                }

            }
        }

        if(basei==-1){return;}


        // choose row and erase
        for(int i=0;i<rows;i++){
            if(i==basei){continue;}

            if(matrix[i][basej]==0){
                for(int j=0; j<cols; j++){
                    matrix[i][j]=0;
                }
            }
        }

        //choose col and erase
        for(int j=0;j<cols;j++){
            if(j==basej){continue;}

            if(matrix[basei][j]==0){
                for(int i=0; i<rows; i++){
                    matrix[i][j]=0;
                }
            }
        }

        for(int j=0; j< cols; j++){
            matrix[basei][j]=0;
        }
        for(int i=0; i< rows; i++){
            matrix[i][basej]=0;
        }


        return;

    }
};
