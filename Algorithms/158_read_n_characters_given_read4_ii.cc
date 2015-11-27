/*
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function may be called multiple times. 
*/

// Forward declaration of the read4 API.
int read4(char *buf);

// Since read can be called multiple times, we need to store the characters read but not copied to buf in one read call. There are two changes to simple read function:
// 1. in the end any leftover characters are pushed to the queue
// 2. in the beginning check if queue has leftovers, if yes copy to buffer. Has to handle cases where n is small than the number of leftovers.

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int once = 0, total = 0;
        //if there is anything left in residue, pop out.
        while(!q.empty() && n > 0) {
            *(buf++) = q.front(); q.pop_front();
            total ++;
            n--;
        }
        if(n == 0) return total; //finished
        
        while(n >= 4) {
            once = read4(buf);
            total += once;
            buf += once;
            if(once < 4) return total; //reached end of file
            n -= once;
        }
        if(n > 0) {
            once = read4(buf);
            buf += min(once, n); //move buffer position
            total += min(once, n);
            int leftover = once - n;
            for(int i = 0; i < leftover; ++i) { //has residue, push to queue
                q.push_back(*(buf+i));
            }
        }
        return total;
    }
    
private:
    deque<char> q;
};
