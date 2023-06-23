class Solution {
public:
    int findMinLoc(vector<int>& nums)
    {
        int l = 0;
        int r = nums.size()-1;
        int mid;

        if(r==0){return 0;}
        while(r>l)
        {
            if(r-l==1 && nums[l]>nums[r]){return r;}

            mid = (l+r)/2;
            if(nums[l]>nums[mid]){r = mid;}
            else if(nums[mid]>nums[r]){l = mid;}
            else {return l;}
        }
        return -1;
    }

    int search(vector<int>& nums, int target) {
        int base = findMinLoc(nums);
        int l=0;
        int mid;
        int sz=nums.size();
        int r=sz-1;

        while(1)
        {
            mid = (r+l)/2;
            if(target < nums[(base+mid)%sz] ) {r = mid;}
            else if (target > nums[(base+mid)%sz] ) {l = (mid+1)%sz;}
            else {return (mid+base)%sz;}

            if(r==l){
                if(target == nums[(l+base)%sz]) {return (l+base)%sz;}
                else {return -1;}
            }
        }

        return -1;

    }
};
