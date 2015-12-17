/*
Find the total area covered by two rectilinear rectangles in a 2D plane.

Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.
Rectangle Area

Assume that the total area is never beyond the maximum possible value of int.
*/

// Key is how to detect two line segments overlap, and how to find the overlap length
// Caveat: should return the *total* area, not the overlapped area!

class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int area1 = (C-A)*(D-B);
        int area2 = (G-E)*(H-F);
        int m = 0, n = 0;
        if(C > E && A < G) m = min(C, G) - max(A, E);
        if(D > F && B < H) n = min(D, H) - max(B, F);
        
        return area1 + area2 - m*n;
    }
};
