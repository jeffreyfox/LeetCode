// Solution using a condition variable.
// Can also put the unique_lock line into the for loop. It increases the overhead of lock creation and destruction.
// At any given time, one thread is waiting and the other thread is executing.

class FooBar {
private:
    int n;
    mutex m;
    int turn = 0;
    condition_variable cv;

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {        
        unique_lock<mutex> ul(m);
        for (int i = 0; i < n; i++) {            
            cv.wait(ul, [this]{return turn == 0;}); 
        	// printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            turn = 1;
            cv.notify_all();
        }
    }

    void bar(function<void()> printBar) {
        unique_lock<mutex> ul(m);
        for (int i = 0; i < n; i++) {            
            cv.wait(ul, [this]{return turn == 1;});
        	// printBar() outputs "bar". Do not change or remove this line.
            printBar();
            turn = 0;
            cv.notify_all();
        }
    }
};
