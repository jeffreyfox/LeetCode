/// Use two stacks
/// Lazy push, when pop/peek for the first time, dump p1's elements into p2 (in reverse order), then later pop/peek is O(1).

class Queue {
public:
    // Push element x to the back of queue.
    void push(int x) {
        q1.push(x);
    }

    // Removes the element from in front of queue.
    void pop(void) {
        if (q2.empty()) {
           while(!q1.empty()) {
               int x = q1.top();  q1.pop();
               q2.push(x);
           }
        }
        q2.pop();
    }

    // Get the front element.
    int peek(void) {
        if (q2.empty()) {
           while(!q1.empty()) {
               int x = q1.top();  q1.pop();
               q2.push(x);
           }
        }
        return q2.top();
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return q1.empty() && q2.empty();
    }
    stack<int> q1, q2;

};
