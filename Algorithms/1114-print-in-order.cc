// Solution using conditional variable. We need to call notify_all in all three functions.

class Foo {
public:
    Foo() {
        
    }

    void first(function<void()> printFirst) {
        std::unique_lock<mutex> ul(m);
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        counter = 1;
        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        std::unique_lock<mutex> ul(m);
        cv.wait(ul, [this]{return counter == 1;});
        // printSecond() outputs "second". Do not change or remove this line.        
        printSecond();
        counter = 2;
        cv.notify_all();
    }

    void third(function<void()> printThird) {
        std::unique_lock<mutex> ul(m);
        cv.wait(ul, [this]{return counter == 2;});
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
        cv.notify_all();
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
