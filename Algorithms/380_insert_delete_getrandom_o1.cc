/*
Implement the RandomizedSet class:

    RandomizedSet() Initializes the RandomizedSet object.
    bool insert(int val) Inserts an item val into the set if not present. Returns true if the item was not present, false otherwise.
    bool remove(int val) Removes an item val from the set if present. Returns true if the item was present, false otherwise.
    int getRandom() Returns a random element from the current set of elements (it's guaranteed that at least one element exists when this method is called). Each element must have the same probability of being returned.

You must implement the functions of the class such that each function works in average O(1) time complexity.

 

Example 1:

Input
["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
[[], [1], [2], [2], [], [1], [2], []]
Output
[null, true, false, true, 2, true, false, 2]

Explanation
RandomizedSet randomizedSet = new RandomizedSet();
randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contains [1,2].
randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly.
randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now contains [2].
randomizedSet.insert(2); // 2 was already in the set, so return false.
randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom() will always return 2.

 

Constraints:

    -231 <= val <= 231 - 1
    At most 2 * 105 calls will be made to insert, remove, and getRandom.
    There will be at least one element in the data structure when getRandom is called.
*/

// Use an array to store the values. When inserting, insert to end of array. When deleting, swap the element with the last element of the array and remove the latter.
// When getting random, generates a random number from 0 to n-1 as the index of the array.
class RandomizedSet {
public:
    RandomizedSet() {
    }
    
    bool insert(int val) {
        if (val2idx.find(val) != val2idx.end()) return false;
        val2idx[val] = array.size();
        array.push_back(val);
        return true;
    }
    
    bool remove(int val) {
        if (val2idx.find(val) == val2idx.end()) return false;
        int index = val2idx[val];
        val2idx.erase(val);
        // Only swap when the element to be removed is not the last element.
        if (index < array.size()-1) {
            // Move the last element into the position of the removed element
            int last_val = array[array.size()-1];
            array[index] = last_val;
            val2idx[last_val] = index;
        }
        array.pop_back();
        return true;
    }
    
    int getRandom() {
        return array[rand() % array.size()];
    }

private:    
    // Uses an unordered map from value to position in array for O(1) insertion and removal
    std::unordered_map<int, int> val2idx;
    // Uses an array to store the values for O(1) get random
    std::vector<int> array;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
                                                                               
