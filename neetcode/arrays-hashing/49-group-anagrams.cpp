#include<unordered_map>
#include<vector>
#include<algorithm>
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> charsToAnagram;

        // chars of string to anagrams
        for(auto& str: strs){
            string digest = str;
            std::sort(digest.begin(), digest.end());
            charsToAnagram[digest].push_back(str); // add str to vector for its digest
        }

        vector<vector<string>> solution;
        for(auto& groups: charsToAnagram){
            solution.push_back(groups.second);
        }
        return solution;
    }
};
