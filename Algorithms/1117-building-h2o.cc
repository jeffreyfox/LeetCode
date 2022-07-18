// Solution using two condition variables.
// Why can't we use cvn.notify_one() in oxygen()?
// For "HHHHOO", at the time when the first O thread enters the critical section, there are 4 H threads waiting on cvH.
// If we only wake up one H thread, it could lead to deadlock:
// * First H thread wakes up, leftH becomes 1, and cvH.notify_one() is called. Then this thread finishes and releases the mutex.
// * Second H thread wakes up, leftH becomes 0, and cvH.notify_one() is NOT called.
// Thus there are two more H threads waiting on cvH but is not woken up by any thread. ==> deadlock
// If we use notify_all(), then all 4 H thread will wake up. The first two H threads that get woken up will decrement leftH and do the paring.
// The 3rd H thread will exit the wait with condition pairing = false and h>=2 and o >=1 (the second O threads has incremented o to 1).
// Thus there is no deadlock.

class H2O {
private:
    // The unpaired counts
    int h, o;
    // The counts of atoms to be paired
    int h_to_pair, o_to_pair;
    // whether pairing is in progress
    bool is_pairing;
    
    mutex m;    
    condition_variable cvh, cvo;
    
    void reset() {
        h_to_pair = 2;
        o_to_pair = 1;
        is_pairing = false;
    }

public:
    H2O() {
        h = o = 0;
        reset();
    }

    void hydrogen(function<void()> releaseHydrogen) {
        unique_lock<mutex> ul(m);
        h++;
        cvh.wait(ul, [this]{
            return (!is_pairing && h >= 2 && o >= 1) || (is_pairing && h_to_pair > 0);
        });
        
        is_pairing = true;        
        h--;
        h_to_pair--;
        if (h_to_pair > 0) cvh.notify_one();
        if (o_to_pair > 0) cvo.notify_one();
        if (h_to_pair == 0 && o_to_pair == 0) reset();
        
        // releaseHydrogen() outputs "H". Do not change or remove this line.        
        releaseHydrogen();
    }

    void oxygen(function<void()> releaseOxygen) {        
        unique_lock<mutex> ul(m);
        o++;        
        cvo.wait(ul, [this]{
            return (!is_pairing && h >= 2 && o >= 1) || (is_pairing && o_to_pair > 0);
        });
        
        is_pairing = true;
        o--;
        o_to_pair--;        
        if (h_to_pair > 0) cvh.notify_all();        
        if (h_to_pair == 0 && o_to_pair == 0) reset();
        
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();        
    }
};
