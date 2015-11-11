/*
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function will only be called once for each test case. 
*/

// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int count = 0; //count how many characters are read at reach read4
        char *beg = buf; //pointer to start of buffer
        if(n == 0) return 0; //can be omitted
        while(count < n) {
            int r = read4(buf); //read next 4
            count += r; //count how many characters are read
            buf += r; //advance buf pointer
            if (r < 4) break; //reach end
        } 
        //after loop count >=n or r == 4
        int len = min(count, n);
        beg[len] = 0; // necessary!
        return len;
    }
};
