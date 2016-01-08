/*
Implement the following operations of a queue using stacks.

    push(x) -- Push element x to the back of queue.
    pop() -- Removes the element from in front of queue.
    peek() -- Get the front element.
    empty() -- Return whether the queue is empty.

Notes:

    You must use only standard operations of a stack -- which means only push to top, peek/pop from top, size, and is empty operations are valid.
    Depending on your language, stack may not be supported natively. You may simulate a stack by using a list or deque (double-ended queue), as long as you use only standard operations of a stack.
    You may assume that all operations are valid (for example, no pop or peek operations will be called on an empty queue).

*/

/// Use two stacks
/// Lazy push (into secondary stack), when pop/peek for the first time (primary stack s1 is empty), dump s2's elements into s1 in reverse order, then later pop/peek is O(1).

class Queue {
public:
    // Push element x to the back of queue.
    void push(int x) {
        s2.push(x);
    }

    // Removes the element from in front of queue.
    void pop(void) {
        if(s1.empty()) {
            while(!s2.empty()) {
                s1.push(s2.top()); s2.pop();
            }
        }
        s1.pop();
    }

    // Get the front element.
    int peek(void) {
        if(s1.empty()) {
            while(!s2.empty()) {
                s1.push(s2.top()); s2.pop();
            }
        }
        return s1.top();
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return s1.empty() && s2.empty();
    }
private:
    stack<int> s1, s2;
};

