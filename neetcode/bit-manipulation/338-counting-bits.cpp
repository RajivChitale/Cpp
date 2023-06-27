class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> count(n+1);

        count[0]=0;
        for(int d=1; d<=n; d*=2)
        {
            for(int i=d; i<2*d && i<=n; i++){
                count[i]=count[i-d]+1;
            }
        }
        return count;
    }
};


// class Solution {
// public:
//     vector<int> countBits(int n) {
//         vector<int> count(n+1);

//         for(int i=0; i<=n; i++){
//             int j=i;
//             int sum=0;
//             while(j>0){
//                 if(j%2==1) {sum++;}
//                 j = j/2;
//             }
//             count[i]=sum;
//         }
//         return count;
//     }
// };
