// Uses a deque. Scan from left to right.
// During scanning, the deque is used as a stack to track the right moving stones.
// In the end, the deque is used as a queue to dump all right moving stones to the result.
// Needs to handle corner cases where a left and a right stone with the same mass annilates each other.

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> result;
        deque<int> rightwards;
        for (const int v : asteroids) {
            if (v > 0) rightwards.push_back(v);
            else {
                bool exploded = false; // whether v has exploded
                while (!rightwards.empty() && !exploded) {
                    int right = rightwards.back();
                    exploded = (right >= -v);
                    if (right <= -v) rightwards.pop_back();
                }
                if (!exploded) result.push_back(v);
            }
        }
        // push all elements in rightwards to result
        while (!rightwards.empty()) {
            result.push_back(rightwards.front());
            rightwards.pop_front();
        }
        return result;
    }
};
