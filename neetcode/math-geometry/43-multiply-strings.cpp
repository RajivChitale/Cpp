class Solution {

public:

    string multiply(string num1, string num2) {
        int N1=num1.size();
        int N2=num2.size();
        vector<int> res(N1+N2, 0); 
        int sum;
        for(int i=0; i<N1; i++){
            for(int j=0; j<N2; j++){
                sum = (num1[N1-1-i]-'0') * (num2[N2-1-j]-'0');
                res[i+j] = res[i+j]+sum;
                res[i+j+1] += res[i+j]/10;
                res[i+j] %= 10;

            }          
        }

        // //carry
        // for(int i=0; i<N1+N2-1; i++){
        //     res[i+1] += res[i]/10;
        //     res[i] = res[i] % 10;
        // }

        string outstr = "";
        int loc = N1+N2-1;
        while(res[loc] ==0 && loc>0){loc--;}
        while(loc>=0){
            outstr.push_back(res[loc] + '0');
            loc--;
        }

        return outstr;

    }
};
