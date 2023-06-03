#include<map>
#include<vector>

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::vector<int> solution;
        std::map<int, int> numToInd;

        for(int i=0; i<nums.size(); i++){
            //complement
            int curr = nums.at(i);
            if(numToInd.count(target-curr) != 0)
            {
                solution.push_back(numToInd[target-curr]);
                solution.push_back(i);
                return solution;
            }
            numToInd[curr] = i;
        }
        return solution;
    }
};
