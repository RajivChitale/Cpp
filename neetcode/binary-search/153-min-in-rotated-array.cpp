class Solution {
public:
    int findMin(vector<int>& nums) {
        int l=0;
        int r=nums.size()-1;
        int mid;

        if(r==0){return nums[0];}

        while(r>=l)
        {
            if(r-l==1 && nums[l]>nums[r]) {return nums[r];}

            mid = (l+r)/2;
            if(nums[mid]>nums[r]){l = mid;} // jump is on right side
            else if(nums[l] > nums[mid]) {r = mid;} // jump is on left side
            else {return nums[l];} 
        }
        return -1;
    }
};
