#include<vector>

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int size = nums.size();
        vector<int> res(size);

        int suffixProd = 1;
        for(int i = size-2; i>=0; i--)
        {
            suffixProd = suffixProd*nums[i+1];
            res[i]= suffixProd;
        }       
        res[size-1] = 1;


        int prefixProd = 1;
        for(int i =1; i<size; i++)
        {
            prefixProd *= nums[i-1];
            res[i] *= prefixProd;
        }

        return res;
    }
};
