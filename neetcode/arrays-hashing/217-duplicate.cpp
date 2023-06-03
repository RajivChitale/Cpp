#include<iostream>
#include<map>

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        std::map<int, int> hashtable;
        for(auto& e: nums)
        {
            if(hashtable.count(e)==0){hashtable[e] = 1;}
            else {return true;}
        }

        return false;
    }
};
