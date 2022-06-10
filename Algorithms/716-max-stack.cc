// A simple solution using a regular stack and a max stack to track the maximum.
// push(), pop(), top() and peekMax(): O(1)
// popMax(): O(n). Needs to pop the elements out until finding the maximum and put them back.
class MaxStack {
public:
    MaxStack() {
        
    }
    
    void push(int x) {
        st.push(x);
        if (max_st.empty()) max_st.push(x);
        else max_st.push(max(max_st.top(), x));
    }
    
    int pop() {
        int val = st.top();
        st.pop();
        max_st.pop();
        return val;
    }
    
    int top() {
        return st.top();
    }
    
    int peekMax() {
        return max_st.top();
    }
    
    int popMax() {
        int max = max_st.top();
        stack<int> tmp;
        while (st.top() != max) {
            tmp.push(st.top());
            st.pop(); max_st.pop();
        }
        st.pop(); max_st.pop();
        while (!tmp.empty()) {
            push(tmp.top());
            tmp.pop();
        }
        return max;
    }

private:
    stack<int> st;
    stack<int> max_st;
};

/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack* obj = new MaxStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->peekMax();
 * int param_5 = obj->popMax();
 */
// Solution using doubly linked list and an ordered map of value to list of nodes to facilitate max operations.
// push() inserts a node to the end of the list and inserts an entry to the ordered map.
// pop() removes a node from the end of the list.
// the node list inside the ordered map uses std::list structure to facilitate O(1) removal from end (can also use vector as adding and removing from end
// is O(1) amortized.
// Use a dummy head (no need to track tail)
// top: O(1). all others: O(lgn)
class MaxStack {
public:
    struct DllNode {
        DllNode *prev, *next;
        int val;
        DllNode(int v) : val(v), prev(nullptr), next(nullptr) {}
    };
    MaxStack() {
        head = new DllNode(-1);
        head->next = head;
        head->prev = head;
    }
    
    void push(int x) {
        DllNode* node = new DllNode(x);
        auto *tail = head->prev;
        node->prev = tail;
        tail->next = node;
        node->next = head;
        head->prev = node;
        dict[x].push_back(node);
    }
    
    int pop() {
        // head of list
        int val = head->prev->val;
        remove(head->prev);
        dict[val].pop_back();
        if (dict[val].empty()) dict.erase(val);
        return val;
    }
    
    int top() {
        return head->prev->val;
    }
    
    int peekMax() {
        return dict.rbegin()->first;
    }
    
    int popMax() {
        int val = dict.rbegin()->first;
        auto &nodes = dict.rbegin()->second;
        auto *node = nodes.back();
        remove(node);
        nodes.pop_back();
        if (nodes.empty()) dict.erase(val);
        return val;
    }
    
    void remove(DllNode* node) {
        node->next->prev = node->prev;
        node->prev->next = node->next;
        delete node;
    }
private:
    DllNode *head;
    map<int, list<DllNode*>> dict;
};

/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack* obj = new MaxStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->peekMax();
 * int param_5 = obj->popMax();
 */
