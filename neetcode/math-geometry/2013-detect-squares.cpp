class DetectSquares {
public:
    string point_to_str(vector<int> point){
        return to_string(point[0]) + "," + to_string(point[1]);
    }

    int checkpt(pair<int, int> point){
        string coords = to_string(point.first) + ","+ to_string(point.second);
        if(presence.count(coords)!=0){return presence[coords];}
        else return 0;
    }
    unordered_map<string,int> presence;   // hashtable for checking given points
    unordered_map<int, vector<int> > col;         // check y coords for given x

    DetectSquares() {

    }
    
    void add(vector<int> point) {
        string ptstr = point_to_str(point);
        if(presence.count(ptstr)==0){presence[ptstr]=1;}
        else{presence[ptstr]++;}
        int x=point[0];
        int y=point[1];

        if(col.count(x)==0){
            vector<int> init;
            init.push_back(y);
            col[x] = init;
        }
        else{
            col[x].push_back(y);
        }

    }
    
    int count(vector<int> point) {
        int x1=point[0];
        int y1=point[1];
        int side;
        int res=0;

        if(col.count(x1)!=0){
            for(auto y2: col[x1]){
                side = y2-y1;
                if(side==0){continue;}
                res+=checkpt({x1+side,y1}) * checkpt({x1+side,y2});
                res+=checkpt({x1-side,y1}) * checkpt({x1-side,y2});
            }
        }

        return res;

    }
};

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares* obj = new DetectSquares();
 * obj->add(point);
 * int param_2 = obj->count(point);
 */
