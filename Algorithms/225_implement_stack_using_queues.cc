/*
Implement the following operations of a stack using queues.

    push(x) -- Push element x onto stack.
    pop() -- Removes the element on top of the stack.
    top() -- Get the top element.
    empty() -- Return whether the stack is empty.

Notes:

    You must use only standard operations of a queue -- which means only push to back, peek/pop from front, size, and is empty operations are valid.
    Depending on your language, queue may not be supported natively. You may simulate a queue by using a list or deque (double-ended queue), as long as you use only standard operations of a queue.
    You may assume that all operations are valid (for example, no pop or top operations will be called on an empty stack).
*/

// Solution 1. Use only one queue! Push O(n), others O(1). For push, the idea is to add the new element to end of queue, and then move front of queue to back of the new elemenet one by one.
class Stack {
public:
    // Push element x onto stack.
    void push(int x) {
        int n = q.size();
        q.push(x);
        for(int i = 0; i < n; ++i) {
            q.push(q.front());
            q.pop();
        }
    }

    // Removes the element on top of the stack.
    void pop() {
        q.pop();
    }

    // Get the top element.
    int top() {
        return q.front();
    }

    // Return whether the stack is empty.
    bool empty() {
        return q.empty();
    }
    queue<int> q;
};

// Solution 2. Use two queues. Push O(n), others O(1). The primary queue is ordered like a stack. The second queue serves like a loading area. When adding an element, first push to secondary queue, and then move elements from primary to secondary, and then swap primary and secondary.
// primary: 3 2 1, secondary add 4
// Migration: primary : empty, secondary 4 3 2 1
// swap the two: primary: 4 3 2 1, secondary empty.

class Stack {
public:
    // Push element x onto stack.
    void push(int x) {
        q2.push(x);
        while(!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1, q2);
    }

    // Removes the element on top of the stack.
    void pop() {
        q1.pop();
    }

    // Get the top element.
    int top() {
        return q1.front();
    }

    // Return whether the stack is empty.
    bool empty() {
        return q1.empty();
    }
private:
    queue<int> q1, q2;
};

// Solution 3. Push O(1), pop and top O(n).
class Stack {
public:
    // Push element x onto stack.
    void push(int x) {
        q1.push(x);
    }

    // Removes the element on top of the stack.
    void pop() {
        while(!q1.empty()) {
            int x = q1.front(); q1.pop();
            if(!q1.empty()) q2.push(x);
        }
        swap(q1, q2);
    }

    // Get the top element.
    int top() {
        int x = 0;
        while(!q1.empty()) {
            x = q1.front(); q1.pop();
            q2.push(x);
        }
        swap(q1, q2);
        return x;
    }

    // Return whether the stack is empty.
    bool empty() {
        return q1.empty();
    }
private:
    queue<int> q1, q2;
};


