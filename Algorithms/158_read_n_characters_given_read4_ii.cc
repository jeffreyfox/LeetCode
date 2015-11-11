/*
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function may be called multiple times. 
*/

// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
    
public:
    Solution() { leftover[0] = '\0';}
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
       if (n == 0) return 0;
        int count = 0;
        //copy leftover to buf
        while(count < n && nleft > 0) {
           *buf++ = leftover[ileft];
           ileft = (ileft+1) % 4; //current left-over character to be copied to buf
           nleft--; //number of left-over characters
           count++;
        }
        if(count == n)  return count;  //already read enough

        //nleft = 0, leftover is empty. reset ileft
        ileft = 0;
        while(count < n) {
            int r = read4(leftover);
            nleft = r;
            while(count < n && nleft > 0) {
                *buf++ = leftover[ileft];
                ileft = (ileft+1) % 4;
                nleft--;
                count++;
            }
            if(r < 4) break; //reaching end
        }
        return count;
    }

    char leftover[4];
    int nleft;
    int ileft;
};
