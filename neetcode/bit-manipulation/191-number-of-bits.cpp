class Solution {
public:
    int hammingWeight(uint32_t n) {
        int sum=0;
        while(n!=0){				//        for(int i=0; i<32; i++){
            if(n & 1) {sum++;}
            n = n >> 1;
        }
        return sum;
    }
};


