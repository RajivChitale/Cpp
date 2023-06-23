// hours < h then decrease k and increase hours

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int r=0;
        for(int a:piles){
            if(a>r){r=a;}    //init r to max of piles
        }

        int l=1;
        int mid, hours;

        while(r>=l){
            if(l==r){return l;}
            mid = (l+r)/2;
            hours = 0;
            // calc required hours  
            for(int i=0;i<piles.size();i++){
                hours+=ceil((double)piles[i]/mid);
                    //cout << ceil((double)piles[i]/mid) << " ";
            }   
            //cout << " set:" <<l << " "<< mid<< " "<<  r<< " "<<  endl;

            if(hours<=h) {r = mid;}
            else if(hours>h) {l = mid+1; }

        }

        return -1;
    }
};
