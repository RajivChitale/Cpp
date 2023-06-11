class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l=0;
        int r=nums.size()-1;
        int mid;
        while(r>=l)
        {
            if(r==l && nums[l]!=target){return -1;}

            mid = (l+r)/2;
            if(target < nums[mid]) {r=mid;}
            else if(target > nums[mid]) {l=mid+1;}
            else {return mid;}
        }
        return -1;
    }
};
