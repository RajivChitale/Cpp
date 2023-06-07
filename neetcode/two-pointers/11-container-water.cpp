/*
ignore smaller lines between l and r  (because less width and less height)
no minima- only maxima allowed. Keep checking if increase in height beats decrease in width
*/

class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0;
        int r = height.size()-1;
        int lh = 0;
        int rh = 0;
        int max = 0;
        int curr = 0;
        
        while(l<r){
            if(height[l] >= lh){lh=height[l];}
            else {l++; continue;}

            if(height[r] >= rh){rh=height[r];}
            else {r--; continue;}

            if(lh<rh){
                curr = (r-l)*lh;
                l++;
            }
            else{
                curr = (r-l)*rh;
                r--;
            }
            if(max<curr){max=curr;}
        }
        return max;
    }
};
