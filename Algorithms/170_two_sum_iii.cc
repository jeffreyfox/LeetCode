/*
Design and implement a TwoSum class. It should support the following operations: add and find.

add - Add the number to an internal data structure.
find - Find if there exists any pair of numbers which sum is equal to the value.

For example,

add(1); add(3); add(5);
find(4) -> true
find(7) -> false
*/

// Solution: use a lookup table to store the counts of each number (can handle duplicates). 
// add is O(1) amortized, just increment count in table
// find needs to traverse all entries in table. Handle two cases: number and residue are the same, and differerent.
// Slight optimization: only check half of cases (i >= j), avoid rechecking the same pair.

class TwoSum {

public:

  // Add the number to an internal data structure.
  void add(int number) {
    dict[number]++;
  }

  // Find if there exists any pair of numbers which sum is equal to the value.
  bool find(int value) {
    for(unordered_map<int, int>::iterator it = dict.begin(); it != dict.end(); ++it) {
      int i = it->first, j = value - i;
      if(j < i) continue;
      if((i == j && it->second > 1) || (i != j && dict.count(j))) return true;
    }
    return false;
  }

private:
  unordered_map<int, int> dict;
};


// Your TwoSum object will be instantiated and called as such:
// TwoSum twoSum;
// twoSum.add(number);
// twoSum.find(value);
