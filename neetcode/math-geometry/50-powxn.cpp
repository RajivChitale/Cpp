class Solution {
public:
    double myPow(double x, int n) {
        double prod = 1;

        if(n<0){
            x = 1/x;
            n = -(n+1);
            prod = x;
        }   

        double p = x;

        while(n!=0){
            if(n%2) {prod*=p;} //include bit in n
            p = p*p;
            n/=2;
        }
        return prod;
    }
};
