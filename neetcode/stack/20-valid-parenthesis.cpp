#include<stack>
#include<map>

class Solution {
public:
    bool isValid(string s) {
        std::stack<char> levels;
        std::map<char, char> closing = {
            {'{','}'},
            {'(',')'},
            {'[',']'}
        };
        for(int i=0; i<s.length(); i++)
        {
            if(!levels.empty() && s[i]== closing[levels.top()] )
            {
                levels.pop(); // matched
            }
            else if(s[i]==']' || s[i]==')' || s[i]=='}')
            {
                return false; // unmatched end
            }
            else
            {
                levels.push(s[i]);  // new level
            }
        }
        return levels.empty();
    }
};
