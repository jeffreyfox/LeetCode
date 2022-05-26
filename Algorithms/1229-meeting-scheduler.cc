/*
Given the availability time slots arrays slots1 and slots2 of two people and a meeting duration duration, return the earliest time slot that works for both of them and is of duration duration.

If there is no common time slot that satisfies the requirements, return an empty array.

The format of a time slot is an array of two elements [start, end] representing an inclusive time range from start to end.

It is guaranteed that no two availability slots of the same person intersect with each other. That is, for any two time slots [start1, end1] and [start2, end2] of the same person, either start1 > end2 or start2 > end1.

 

Example 1:

Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 8
Output: [60,68]
Example 2:

Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 12
Output: []
 

Constraints:

1 <= slots1.length, slots2.length <= 104
slots1[i].length, slots2[i].length == 2
slots1[i][0] < slots1[i][1]
slots2[i][0] < slots2[i][1]
0 <= slots1[i][j], slots2[i][j] <= 109
1 <= duration <= 106
*/

bool compare(const vector<int> &a, const vector<int> &b) {
    if (a[0] == b[0]) return a[1] < b[1];
    return a[0] < b[0];
}

bool isOverlap(const vector<int> &a, const vector<int> &b) {
    return a[0] <= b[1] && b[0] <= a[1];
}

vector<int> getIntersection(const vector<int> &a, const vector<int> &b) {
    return {max(a[0], b[0]), min(a[1], b[1])};    
}

class Solution {
public:
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        sort(slots1.begin(), slots1.end(), compare);
        sort(slots2.begin(), slots2.end(), compare);
        vector<int> result;
        for(int i = 0, j = 0; i < slots1.size() && j < slots2.size();) {
            if (isOverlap(slots1[i], slots2[j])) {
                vector<int> intersection = getIntersection(slots1[i], slots2[j]);
                if (intersection[1] - intersection[0] >= duration) {
                    return {intersection[0], intersection[0] + duration};
                }
            }
            // Moves the pointer of the interval that ends earlier
            if (slots1[i][1] < slots2[j][1]) i++;
            else j++;
        }
        return {};
    }
};
