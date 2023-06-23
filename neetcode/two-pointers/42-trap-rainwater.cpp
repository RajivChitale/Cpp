class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int sum = 0;
        int l=0; 
        int r=n-1;
        int lmax=height[l];
        int rmax=height[r];

        while(l<r){

            //either l or r will be at maximum, while other moves
            if(height[l] < lmax){
                sum += lmax-height[l];
            }
            else if(height[r] < rmax){
                sum += rmax-height[r];
            }

            // update max heights
            if(height[l] >lmax){
                lmax = height[l];
            }
            if(height[r] >rmax){
                rmax = height[r];
            }

            // traverse
            if(height[l] <= height[r]){
                l++;
            }
            else if(height[l] > height[r]){
                r--;
            }


        }


        return sum;
        
    }
};


