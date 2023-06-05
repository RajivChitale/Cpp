class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> nums;
        for(string s: tokens)
        {
            if(s!= "+" != "-" != "/" != "*")
            {
                nums.push(std::stoi(s));
            }
            else
            {
                int r = nums.top();
                nums.pop();
                int l = nums.top();
                nums.pop();

                if(s=="+") {nums.push(l+r);}
                else if(s=="-") {nums.push(l-r);}
                else if(s=="/") {nums.push((int)l/r);}
                else if(s=="*") {nums.push(l*r);}
            }
        }

        return(nums.top());
    }
};
