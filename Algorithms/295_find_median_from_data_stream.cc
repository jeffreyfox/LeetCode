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

// Solution: use two priority queues, one max-queue and the other min-queue. Store first half of data in max-queue and second half of data in min-queue. Has to take care of corner cases (count == 0)

class MedianFinder {
public:
    MedianFinder() : count(0) {}

    // Adds a number into the data structure.
    void addNum(int num) {
        if(count == 0) maxHeap.push(num);
        else if(count % 2 == 0) { //even number of elements
            if(num <= maxHeap.top()) maxHeap.push(num);
            else {
                minHeap.push(num);
                maxHeap.push(minHeap.top()); //put smallest in minHeap to maxHeap
                minHeap.pop();
            }
        } else { //odd number of elements, maxHeap has the extra one
            if(num >= maxHeap.top()) minHeap.push(num);
            else {
                maxHeap.push(num);
                minHeap.push(maxHeap.top());
                maxHeap.pop();
            }
        }
        count++;
    }

    // Returns the median of current data stream
    double findMedian() {
        if(count == 0) return 0;
        else if(count % 2 == 1) return maxHeap.top();
        else return (maxHeap.top() + minHeap.top())/2.0;
    }

private:    
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int> > minHeap;
    int count;
};

// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();
