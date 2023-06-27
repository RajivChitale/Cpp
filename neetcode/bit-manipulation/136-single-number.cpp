class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int xored = 0;
        for(int e: nums){
            xored = xored^e;
        }
        return xored;
    }
};
