// Solution using condition variable. Has to call notify_all instead of notify_one.
// If calling notify_one, the one thread notified might still be blocked.

class FizzBuzz {
private:
    int n;
    int i = 1;
    mutex m;
    condition_variable cv;

public:
    FizzBuzz(int n) {
        this->n = n;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while (i <= n) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this]{return i > n || (i % 3 == 0 && i % 5 != 0);});
            if (i > n) break;
            printFizz();
            i++;
            cv.notify_all();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while (i <= n) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this]{return i > n || (i % 3 != 0 && i % 5 == 0);});
            if (i > n) break;
            printBuzz();
            i++;
            cv.notify_all();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        while (i <= n) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this]{return i > n || (i % 3 == 0 && i % 5 == 0);});
            if (i > n) break;
            printFizzBuzz();
            i++;
            cv.notify_all();
        }        
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while (i <= n) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this]{return i > n || (i % 3 != 0 && i % 5 != 0);});
            if (i > n) break;
            printNumber(i);
            i++;
            cv.notify_all();
        }
    }
};
