/*
An image is represented by a binary matrix with 0 as a white pixel and 1 as a black pixel. The black pixels are connected, i.e., there is only one black region. Pixels are connected horizontally and vertically. Given the location (x, y) of one of the black pixels, return the area of the smallest (axis-aligned) rectangle that encloses all black pixels.

For example, given the following image:

[
  "0010",
  "0110",
  "0100"
]

and x = 0, y = 2,

Return 6. 
*/

// Standard BFS solution.
class Solution {
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        if(image.empty() || image[0].empty()) return 0;
        xmin = x, xmax = x, ymin = y, ymax = y;
        pixels.push_back(make_pair(x, y));
        image[x][y] = '.'; //sign for visited
        int m = image.size(), n = image[0].size();
        while(!pixels.empty()) {
            x = pixels.front().first;
            y = pixels.front().second;
            pixels.pop_front();
            if(x > 0 && image[x-1][y] == '1') {
                pixels.push_back(make_pair(x-1, y));
                image[x-1][y] = '.';
                xmin = min(xmin, x-1);
            }
            if(x < m-1 && image[x+1][y] == '1') {
                pixels.push_back(make_pair(x+1, y));
                image[x+1][y] = '.';
                xmax = max(xmax, x+1);
            }
            if(y > 0 && image[x][y-1] == '1') {
                pixels.push_back(make_pair(x, y-1));
                image[x][y-1] = '.';
                ymin = min(ymin, y-1);
            }
            if(y < n-1 && image[x][y+1] == '1') {
                pixels.push_back(make_pair(x, y+1));
                image[x][y+1] = '.';
                ymax = max(ymax, y+1);
            }
        }
      /*  for(int i = xmin; i <= xmax; ++i) {
            for(int j = ymin; j <= ymax; ++j) {
                if(image[i][j] == '.') image[i][j] = '1';
            }
        } */
        return (xmax-xmin+1)*(ymax-ymin+1);
    }

    int xmin, xmax, ymin, ymax;
    deque<pair<int, int> > pixels;
};

/*
Binary search solution. There is only one connected region, and we are given a position inside it. If we project the region to 1D (x, or y), we end up with: 00000111110000, where we have a one when there is at least one '1' in the same colum or row.
The starting position is guaranteed to be one of the '1's. So we do two binary searches, once left and once right, to find the boundary between 0 and 1's. We carry out the same algorithm for both row and column, and we get the maximum area.

Use a function to perform the same task for row and colume, and a helper function foundOne.
*/

class Solution {
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        if(image.empty() || image[0].empty()) return 0;
        int xmin(0), xmax(0), ymin(0), ymax(0);
        //'r' means row, 'c' means col
        getBoundaries(image, y, xmin, xmax, 'r');
        getBoundaries(image, x, ymin, ymax, 'c');
        return (xmax-xmin+1)*(ymax-ymin+1);
    }

    void getBoundaries(vector<vector<char> >& image, int pos, int& lb, int& hb, char rc) {
        //binary search, first left then right
        int lo(0), hi(0), mid(0);

        lo = 0, hi = pos-1;
        // [0 .. lo): 0, [lo .. hi] TBD, (hi, pos) 1
        while(lo <= hi) {
            mid = lo + (hi-lo)/2;
            if(foundOne(image, mid, rc)) hi = mid-1;
            else lo = mid+1;
        }
        lb = lo;

        lo = pos+1, hi = (rc == 'r') ? image[0].size()-1 : image.size()-1;
        // [0 .. lo): 1, [lo .. hi] TBD, (hi, pos) 0
        while(lo <= hi) {
            mid = lo + (hi-lo)/2;
            if(foundOne(image, mid, rc)) lo = mid+1;
            else hi = mid-1;
        }
        hb = hi;
    }
    bool foundOne(vector<vector<char> >& image, int pos, char rc) {
        int m = image.size(), n = image[0].size();
        if(rc == 'r') { //we need to search along column
            for(int k = 0; k < m; ++k)
               if(image[k][pos] == '1') return true;
            return false;
         } else { //we need to search along row
            for(int k = 0; k < n; ++k)
               if(image[pos][k] == '1') return true;
            return false;
         }
    }
};

*/

