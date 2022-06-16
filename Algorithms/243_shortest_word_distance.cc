// One pass solution. Update the indices of the two words and compute the new distance.
// Use a variable to track the minimum distance seen so far.
class Solution {
public:
    int shortestDistance(vector<string>& wordsDict, string word1, string word2) {
        int idx1 = -1, idx2 = -1;
        int min_dist = INT_MAX;
        for (int i = 0; i < wordsDict.size(); ++i) {
            if (wordsDict[i] == word1) {
                idx1 = i;
                if (idx2 >= 0) min_dist = min(min_dist, idx1 - idx2);
            }
            else if (wordsDict[i] == word2) {
                idx2 = i;
                if (idx1 >= 0) min_dist = min(min_dist, idx2 - idx1);
            }
        }
        return min_dist;
    }
};
