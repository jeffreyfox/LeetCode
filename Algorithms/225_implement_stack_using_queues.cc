// Use to queues, when adding an element, put into the empty queue, and
// migrate all elements from the other queue to this queue.

class Stack {
public:
    // Push element x onto stack.
    void push(int x) {
        if(q1.empty()) {
            q1.push_back(x);
            while(!q2.empty()) {
                q1.push_back(q2.front());
                q2.pop_front();
            }
        } else {
            q2.push_back(x);
            while(!q1.empty()) {
                q2.push_back(q1.front());
                q1.pop_front();
            }
        }
    }

    // Removes the element on top of the stack.
    void pop() {
        if (!q1.empty()) q1.pop_front();
        else q2.pop_front();
    }

    // Get the top element.
    int top() {
        if (!q1.empty()) return q1.front();
        else return q2.front();
    }

    // Return whether the stack is empty.
    bool empty() {
        return (q1.empty() && q2.empty());
    }

private:
    deque<int> q1;
    deque<int> q2;
};
