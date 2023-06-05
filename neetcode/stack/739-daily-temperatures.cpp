class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> unpatched_days; // unpatched days (with temps decreasing)
        vector<int> answer(temperatures.size(), 0);

        for(int i=0; i< temperatures.size(); i++)
        {
            // patch values to left (which have lower temp)
            while(!unpatched_days.empty() && 
                temperatures[i]> temperatures[unpatched_days.top()] )
            {
                int start = unpatched_days.top(); 
                answer[start] = i-start;
                unpatched_days.pop();
            }
            unpatched_days.push(i);     
            // now this is lowest unpatched
        }

        return answer;
    }
};
