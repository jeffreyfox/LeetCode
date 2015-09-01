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
        s.push_back(x);
        if(ms.empty() || x <= ms.back()) ms.push_back(x);
    }

    void pop() {
        if(s.back() == ms.back()) ms.pop_back();
        s.pop_back();
    }

    int top() {
        return s.back();
    }

    int getMin() {
        return ms.back();
    }
private:
    deque<int> s; //normal stack
    deque<int> ms; //stack for minimum elements at the time
};
