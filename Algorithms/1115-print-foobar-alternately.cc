// Solution using a condition variable.

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
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> ul(m);
            cv.wait(ul, [this]{return turn == 0;}); 
        	// printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            turn = 1;
            cv.notify_all();
        }
    }

    void bar(function<void()> printBar) {        
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> ul(m);
            cv.wait(ul, [this]{return turn == 1;});
        	// printBar() outputs "bar". Do not change or remove this line.
            printBar();
            turn = 0;
            cv.notify_all();
        }
    }
};
