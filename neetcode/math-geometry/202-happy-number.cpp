class Solution {
public:
    int sqrsum(int a){
        int sum=0;
        int t;
        while(a>0){
            t = a%10;
            sum += t*t;
            a=a/10;
        }
        return sum;
    }

    bool isHappy(int n) {
        unordered_set<int> seen;
        while(true){
            seen.insert(n);
            n = sqrsum(n);
            if(n==1){return true;}
            if(seen.count(n)>0){return false;}
        }
        return false;
    }
};
