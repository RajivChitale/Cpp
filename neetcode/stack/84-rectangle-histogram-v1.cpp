// nlogn by divide and conquer
class Solution {
public:
    // solve in range [p, q]
    int recSolver(int p, int q, vector<int>& heights)
    {
        if(p==q) {return heights[p];} //single bar

        int mid = (p+q)/2; //split in half
        int l_area = recSolver(p, mid, heights);
        int r_area = recSolver(mid+1, q, heights);

        int i=mid+1; int j= mid; // left and right markers for rectangle passing through mid
                // initially cover zero area (no thickness)
        int height = -1; // -1 to denote infinite
        int m_area = 0; 
        while(i!=p || j!=q)
        {
            int l_next = i!=p ? heights[i-1] : -1; // height of bar to left (ends at boundary)
            int r_next = j!=q ? heights[j+1] : -1;
            // expand left/right towards greater height. Reduces net height as little as possible
            if(l_next > r_next)
            {
                i--;
                if(height==-1 || height>heights[i]) {height = heights[i];}
            }
            else
            {
                j++;
                if(height==-1 || height>heights[j]) {height = heights[j];}
            }
            int width = j-i+1;

            if(width*height>m_area) {m_area = width*height;}

        } 
         return std::max({l_area, r_area, m_area});
    }

    int largestRectangleArea(vector<int>& heights) {
        return recSolver(0, heights.size()-1, heights);
    }
};




/* Brute force n^2
    int largestRectangleArea(vector<int>& heights) {
        int count = heights.size();
        // max{ minInRange(i,j)*(j-i) }
        int maxArea = 0;
        for(int i=0; i<count; i++)
        {
            int minHeight = -1; // uninitialized. min from i to j
            for(int j=i; j<count; j++)
            {
                if(minHeight==-1 || minHeight> heights[j]) {minHeight=heights[j];}
                int area = minHeight*(j-i+1);
                if(area > maxArea) {maxArea = area;}
            }
        }
        return maxArea;
    }
*/
