// Solution using a condition variable.
// Use a state variable to track the current state:
// 0: print 0, next odd
// 1: print odd
// 2: print 0, next even
// 3: print even

class ZeroEvenOdd {
private:
    int n;
    int state = 0;
    int val = 1;
    condition_variable cv;
    mutex m;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        while (val <= n) {
            unique_lock<mutex> l(m);
            // Also waits on val > n.
            cv.wait(l, [this]{ return state == 0 || state == 2 || val > n;});
            if (val > n) break;  // breaks when val > n
            printNumber(0);                
            state ++;
          //  l.unlock();  // probably don't need this
            cv.notify_all();        
        }
    }

    void even(function<void(int)> printNumber) {
        while (val <= n) {
            unique_lock<mutex> l(m);
            cv.wait(l, [this]{ return state == 3 || val > n;});
            if (val > n) break;
            printNumber(val++);
            state = 0;
         //   l.unlock();
            cv.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
        while (val <= n) {
            unique_lock<mutex> l(m);
            cv.wait(l, [this]{ return state == 1 || val > n;});
            if (val > n) break;
            printNumber(val++);
            state = 2;
        //    l.unlock();
            cv.notify_all();
        }
    }
};
