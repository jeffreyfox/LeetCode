/*
 Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

    push(x) -- Push element x onto stack.
    pop() -- Removes the element on top of the stack.
    top() -- Get the top element.
    getMin() -- Retrieve the minimum element in the stack.
*/

// Use two stacks, one is normal, the other tracks the minimum element at the time of insertion

class MinStack {
public:
    void push(int x) {
        s.push(x);
        if(ms.empty() || x <= ms.top()) ms.push(x);
    }

    void pop() {
        int x = s.top(); s.pop();
        if(x <= ms.top()) ms.pop();
    }

    int top() {
        return s.top();
    }

    int getMin() {
        return ms.top();
    }
private:
    stack<int> s, ms;
};

