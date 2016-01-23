/*
Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.
Examples:

[2,3,4] , the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

    void addNum(int num) - Add a integer number from the data stream to the data structure.
    double findMedian() - Return the median of all elements so far.

For example:

add(1)
add(2)
findMedian() -> 1.5
add(3) 
findMedian() -> 2

*/

// Solution: use two priority queues, one max-queue and the other min-queue. Store first half of data in max-queue and second half of data in min-queue.
// Need to take care of corner cases (count == 0)

class MedianFinder {
public:
    MedianFinder() : N(0) {}

    // Adds a number into the data structure.
    void addNum(int num) {
        if(N == 0)   max_queue.push(num); //corner case, min_queue is still empty
        else if(N % 2 == 0) { //evenly distributed among min and max queues
            if(num <= min_queue.top()) max_queue.push(num);
            else {
                min_queue.push(num);
                max_queue.push(min_queue.top());
                min_queue.pop();
            }
        } else { //max_queue has one more element
            if(num >= max_queue.top()) min_queue.push(num);
            else {
                max_queue.push(num);
                min_queue.push(max_queue.top());
                max_queue.pop();
            }
        }
        N++;
    }

    // Returns the median of current data stream
    double findMedian() {
        if(N % 2 == 1) return max_queue.top();
        else return (max_queue.top() + min_queue.top()) / 2.0;
    }
private:
    int N;
    priority_queue<int> max_queue; //storing smallest ceil(N/2) elements
    priority_queue<int, vector<int>, greater<int> > min_queue; //storing largest floor(N/2) elements
};


// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();
