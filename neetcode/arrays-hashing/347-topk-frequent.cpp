#include<map>
#include<algorithm>
#include<unordered_map>

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        //generate freq
        std::unordered_map<int, int> numToFreq;
        for(int& number: nums){
            if(numToFreq.count(number) == 0){
                numToFreq[number] = 1;
            }
            else {
                numToFreq[number]++;
            }
        }

        // reverse map: from freq to nums
        std::multimap<int, int> freqToNum;
        for(auto& pair: numToFreq){
            freqToNum.insert({pair.second, pair.first});
        }

        vector<int> res;
        int cutoff = k; // get k most frequent nums
        for(auto pair = freqToNum.rbegin(); cutoff>0 && pair != freqToNum.rend(); pair++ ){
            res.push_back(pair->second);
            cutoff--;
        }

        return res;
    }
};
