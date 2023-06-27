class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int res=0;
        for(int i=0; i<nums.size(); i++)
        {
            res = res ^ (i+1) ^ nums[i];
        }
        return res;
    }
};
