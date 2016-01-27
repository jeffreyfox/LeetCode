/*
This is a follow up of Shortest Word Distance. The only difference is now you are given the list of words and your method will be called repeatedly many times with different parameters. How would you optimize it?

Design a class which receives a list of words in the constructor, and implements a method that takes two words word1 and word2 and return the shortest distance between these two words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “coding”, word2 = “practice”, return 3.
Given word1 = "makes", word2 = "coding", return 1.

Note:
You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.
*/

// Your WordDistance object will be instantiated and called as such:
// WordDistance wordDistance(words);
// wordDistance.shortest("word1", "word2");
// wordDistance.shortest("anotherWord1", "anotherWord2");

// Solution 1. use a map to store string => sorted list of positions. Then find the minimum difference between elements of two sorted arrays

class WordDistance {
public:
    WordDistance(vector<string>& words) {
        int n = words.size();
        for(int i = 0; i < n; i++) {
            dict[words[i]].push_back(i);
        }
    }

    int shortest(string word1, string word2) {
        return shortest(dict[word1], dict[word2]);
    }
    
    int shortest(const vector<int>& vec1, const vector<int>& vec2) {
        int n1 = vec1.size(), n2 = vec2.size();
        int i(0), j(0), mind = INT_MAX;
        while(i < n1 && j < n2) {
            mind = min(mind, abs(vec2[j] - vec1[i]));
            if(vec2[j] > vec1[i]) i++;
            else j++;
        }
        return mind;
    }
    
    unordered_map<string, vector<int> > dict; //string and positions
};

// Solution 2. Use a hash function to convert string to int

class WordDistance {
public:
    WordDistance(vector<string>& words) {
        int n = words.size();
        for(int i = 0; i < n; i++) {
            dict[hash(words[i])].push_back(i);
        }
    }

    int shortest(string word1, string word2) {
        return shortest(dict[hash(word1)], dict[hash(word2)]);
    }
    
    int shortest(const vector<int>& vec1, const vector<int>& vec2) {
        int n1 = vec1.size(), n2 = vec2.size();
        int i(0), j(0), mind = INT_MAX;
        while(i < n1 && j < n2) {
            mind = min(mind, abs(vec2[j] - vec1[i]));
            if(vec2[j] > vec1[i]) i++;
            else j++;
        }
        return mind;
    }
    
    int hash(const string& s) {
        const int A = 54059; /* a prime */
        const int B = 76963; /* a prime */
        const int C = 86969; /* a prime */
        unsigned int h = 31 /* also prime */;
        for(auto c : s) 
            h = (h * A) ^ (c * B);
        return h; // or return h % C;
    }
    unordered_map<int, vector<int> > dict; //string and positions
};
