#include<queue>

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {

        if(nums.size()==0){return 0;}
        std::priority_queue<int> pq(nums.begin(),nums.end());

        int prev=pq.top();
        pq.pop();
        int max=1;
        int curr=1;

        while(!pq.empty())
        {
            if(pq.top()==prev-1){curr++;}
            else if(pq.top() != prev){curr=1;}
            prev=pq.top();
            pq.pop();
            if(curr>max){max = curr;}
        }
        return max;

    }
};
