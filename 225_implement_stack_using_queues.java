// Use two queues, always use q1 as main queue, and q2 as buffer
class MyStack {
    // Push element x onto stack.
    public void push(int x) {
        q2.add(x);
        while(!q1.isEmpty()) {
            q2.add(q1.element());
            q1.remove();
        }
        LinkedList<Integer> t = q1;
        q1 = q2;
        q2 = t;
    }

    // Removes the element on top of the stack.
    public void pop() {
        q1.remove();
    }

    // Get the top element.
    public int top() {
        return q1.element();
    }

    // Return whether the stack is empty.
    public boolean empty() {
        return q1.isEmpty();
    }
    
    private LinkedList<Integer> q1 = new LinkedList<Integer>();
    private LinkedList<Integer> q2 = new LinkedList<Integer>();
}
