class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
       vector<int> linear;
       int r1=0, r2=matrix.size()-1;
       int c1=0, c2=matrix[0].size()-1;
       int i=0, j=0;
       int dir = 0;

        linear.push_back(matrix[0][0]);
        while(true){
            dir = dir%4;
            if(dir==0){j++;}
            else if(dir==1){i++;}
            else if(dir==2){j--;}
            else if(dir==3){i--;}

            // if(dir%2==0){       //move inside row
            //     j += 1-2*(dir/2); // 1 or -1 step
            // }
            // else{
            //     i += 1-2*(dir/2);
            // }


            if(j==c1-1){j=c1; r2--; dir++;} //left end
            else if(j==c2+1){j=c2; r1++; dir++;} //right end
            else if(i==r1-1){i=r1; c1++; dir++;} //top
            else if(i==r2+1){i=r2; c2--; dir++;} //bottom
            else {
                linear.push_back(matrix[i][j]);        
            }
            if(c1>c2 || r1>r2) {break;} // all space checked


            
        }

        return linear;
    }
};
