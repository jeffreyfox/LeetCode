/*
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function will only be called once for each test case. 
*/

// Forward declaration of the read4 API.
int read4(char *buf);

// Solution: keep track of current buffer write position, and total number of characters read so far. Also decrement n by the number of characters written.

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int once = 0, total = 0;
        while(n >= 4) {
            once = read4(buf);
            total += once; //increment character counter
            buf += once; //move buffer forward
            if(once < 4) return total; //reached end of file
            n -= 4; //for sure read-in 4 characters
        }
        //now n < 4
        if(n > 0) {
            once = read4(buf); //could read end of file
            total += min(once, n);
            buf += min(once, n);
        }
        return total;
    }
};
