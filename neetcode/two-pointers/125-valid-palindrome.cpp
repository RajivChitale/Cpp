class Solution {
public:
    bool isPalindrome(string s) {
        int i=0;
        int n = s.length()-1;
        int j= n;

        while(i<j && i<n && j>=0)
        {
            if(!isalnum(s[i])){i++; continue;}
            if(!isalnum(s[j])){j--; continue;}

            if(tolower(s[i])!=tolower(s[j])){return false;}
            else {i++; j--;}
        } 
        return true;
    }
};
