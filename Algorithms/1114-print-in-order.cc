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
