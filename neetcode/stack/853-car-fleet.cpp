#include<algorithm>
#include<vector>
#include<stack>

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int count = position.size();

        vector<pair<int,int>> cars(count);
        for(int i=0; i<count; i++)
        {
            cars[i] = {position[i], speed[i]};
        }
        sort(cars.begin(), cars.end()); //sort by position

        stack<pair<int,int>> fleets;
        for(int i=count-1; i>=0; i--)
        {
            if(fleets.empty()) {fleets.push(cars[i]); continue;}

            double nextFleetArrival = (double)(target-fleets.top().first)/fleets.top().second;
            double carArrival = (double)(target-cars[i].first)/cars[i].second;
            if(nextFleetArrival < carArrival)   //fleet arrives first
            {
                fleets.push(cars[i]);
            }
            //else it joins fleet
        }

        return fleets.size();
    }
};
