#include<map>

class Solution {
public:
//order: x, nums[j], nums[i]
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        int size = nums.size();
        sort(nums.begin(), nums.end());

        for(int i=0; i<size-2; i++)
        {
            if(i>0 && nums[i]==nums[i-1]) {continue;} // to avoid repetitions without loss, use leftmost i
            int l = i+1;
            int r = size -1;
            while(l<r)
            {
                if(l!=i+1 && nums[l-1]==nums[l]) {l++; continue;}
                if(r!=size-1 && nums[r+1]==nums[r]) {r--; continue;}

                if(nums[r]+nums[l]> -nums[i]) {r--; continue;}
                else if(nums[r]+nums[l]< -nums[i]) {l++; continue;}
                else 
                {
                    res.push_back({nums[i], nums[l], nums[r]});
                    l++; r--;
                }
            }

        }

        return res;
    }
};
