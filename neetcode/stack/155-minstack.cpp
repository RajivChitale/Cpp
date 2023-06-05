#include<stack>
class MinStack {
public:

    MinStack() {;
    }
    stack<int> vals, min;
    
    void push(int val) {
        vals.push(val);
        if(min.empty() || min.top()>val) {min.push(val);}
        else {min.push(min.top());}
    }
    
    void pop() {
        vals.pop();
        min.pop();
    }
    
    int top() {
        return vals.top();
    }
    
    int getMin() {
        return min.top();
    }
};

