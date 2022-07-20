// Solution using conditional variable.

// In first(), we cannot use notify_one otherwise it could lead to deadlock under this scenario
// 1. third() executes first, since counter is 0, it waits on cv and releases the mutex.
// 2. second() executes next, similarly, it waits on cv and releases the mutex.
// 3. first executes next, it increments counter and calls notify_one().
// 4. Thread that executes third() wakes up. It acquires m only to find counter is 1 (condition still not satisfied). It releases the lock
//    and goes to sleep again without notifying waiting threads
// 5. Thread that executes second() is still blocked on cv. Since it is not being notified, it will be stuck in wait. ==> deadlock.
// To prevent this, we should call notify_all() in first() so both second() and third() are waken up. In this case, in step #5, second() will unblock and
// execute the code that sets counter to 2. and then third() can unblock.

class Foo {
public:
    Foo() {
        
    }

    void first(function<void()> printFirst) {
        std::unique_lock<mutex> ul(m);
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        counter = 1;
        // Cannot use notify_one(). See comments above.
        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        std::unique_lock<mutex> ul(m);
        cv.wait(ul, [this]{return counter == 1;});
        // printSecond() outputs "second". Do not change or remove this line.        
        printSecond();
        counter = 2;
        // Can use notify_one() because only one thread (third) is waiting.
        cv.notify_all();
    }

    void third(function<void()> printThird) {
        std::unique_lock<mutex> ul(m);
        cv.wait(ul, [this]{return counter == 2;});
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
        // We don't need to call notify because third() is the one that runs last so there will be no threads waiting on cv.
        // cv.notify_all();
    }
private:
    int counter = 0;
    std::mutex m;    
    condition_variable cv;
};

// Solution using C semaphore. One semaphore for each dependency

#include <semaphore.h>

class Foo {
private:
    sem_t firstDone, secondDone;
    
public:
    Foo() {
        sem_init(&firstDone, 0, 0);
        sem_init(&secondDone, 0, 0);
    }

    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        sem_post(&firstDone);
    }

    void second(function<void()> printSecond) {
        sem_wait(&firstDone);
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        sem_post(&secondDone);
    }

    void third(function<void()> printThird) {
        sem_wait(&secondDone);
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};

// Another solution using a counter and a mutex
class Foo {
public:
    Foo() {
        
    }

    void first(function<void()> printFirst) {
          mtx.lock();
          ++counter;
          printFirst();
          mtx.unlock();                
    }

    void second(function<void()> printSecond) {
        while(true) {
            if (mtx.try_lock()) {
                if (counter != 1) {
                    mtx.unlock();
                } else {
                    ++counter;
                    printSecond();
                    mtx.unlock();
                    break;
                }
            }
        }
    }     

    void third(function<void()> printThird) {
        while(true) {
            if (mtx.try_lock()) {
                if (counter != 2) {
                    mtx.unlock();
                } else {
                    ++counter;
                    printThird();
                    mtx.unlock();
                    break;
                }
            }
        }
    }
private:
    int counter = 0;
    std::mutex mtx;
};
