class Solution {
public:
    int getSum(int a, int b) {
        int p = 1;
        int sum = (a^b) & p;
        int car = (a & p & b);


        for(int i=0; i< 31; i++)
        {
            p = p << 1;
            sum = sum | (a & p) ^ (b & p) ^ (car*p);

            if(car==1 &&  !(a & p) && !(b & p)  ){
                car = 0;
            }

            else if(car==0 &&  (a & p) && (b & p)  ){
                car = 1;
            }
        }
        return sum;
    }
};
