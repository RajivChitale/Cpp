class Solution {
public:
    

    int reverse(int x) {
        int num = 0;
        int sign = 1;
        if(x < 0){
            sign = -1;
            if(x==INT_MIN){return 0;}
            x = -x;
        }


        for(int i=0; i<9; i++){
            if(x==0){break;}
            num *= 10;
            num += x%10;
            x= x/10;
        }

        if(x==0){return sign*num;} //fewer than 10 digits

        if(num>INT_MAX/10){return 0;} //big

        if(sign==1 && num== INT_MAX/10 && (x%10) > (INT_MAX%10) ){return 0;}        //borderline
        if(sign==-1 && num== INT_MAX/10 && (x%10) > ((INT_MAX)%10+1) ){return 0;}

        num *= sign*10;
        num += sign*(x);
        return num;
    }
};


