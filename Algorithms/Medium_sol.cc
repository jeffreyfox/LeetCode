/**************************************************** 
 ***    001,Medium,Two Sum 
 ****************************************************/

/*
Given an array of integers, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2
*/

// This solution uses a map to store the positions of each number in array. Uses two passes, first pass builds the map, second pass do the two-sum check. For each number if the other number is in then found.
// There is a simpler way to do this, see solution 2.

class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        map<int, int> s; //occurrence index
        vector<int> ret(2, 0);
        int n = numbers.size();
        if(n == 0) return ret;
        //build hash table first
        for(int k = 0; k < n; ++k)  s[numbers[k]] = k;
        //another sweep
        for(int k = 0; k < n; ++k) { 
            //find residue in map
            map<int, int>::iterator it = s.find(target-numbers[k]);
            if(it != s.end() && it->second != k) { //found and not the same entry
                ret[0] = k+1;  ret[1] = it->second+1;
                break;
            }
        }
        return ret;
    }
};

// This solution uses a map to store the positions of each number in array. Only one pass is needed.
// For each number in the array, see if the residue (target - number) already exists in the map, if yes then found; if no, then add it to map
// This also properly handles duplicates, because checking residue happens before insertion. 
// Unordered map (hash table) is faster than map (which is balanced tree) in this case.

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
      unordered_map<int, int> table;
      vector<int> ret(2, -1);
      int n = nums.size();
      for(int i = 0; i < nums.size(); i++) {
        int res = target - nums[i];
        if(table.count(res)) {
           ret[0] = table[res]+1; ret[1] = i+1;
           break;
        } else {
           table[nums[i]] = i;
        }
      }
      return ret;
    }
};

// This version uses insertion sort t sort nums, together with its positions as satellite data. Use two pointers to find the 
// target items, and return their positions. (No hash table is involved)
// Insertion sort: O(n2), search for target: O(n).
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> pos(n);
        for(int i = 0; i < n; ++i) pos[i] = i+1;
        //insertion sort nums
        for(int i = 1; i < n; ++i) {
            int tmp = nums[i];
            int tmp2 = pos[i];
            int j = i-1;
            while(j >= 0 && nums[j] > tmp) {
                nums[j+1] = nums[j]; 
                pos[j+1] = pos[j];
                j--;
            }
            nums[j+1] = tmp;
            pos[j+1] = tmp2;
        }
        
        int l = 0, r = nums.size()-1;
        vector<int> ret(2, 0);
        while(1) {
            int sum = nums[l] + nums[r];
            if(target == sum) {
                ret[0] = min(pos[l], pos[r]), ret[1] = max(pos[l], pos[r]);
                return ret;
            } else if (target > sum) l++;
            else r--;
        }
        return ret;
    }
};


/**************************************************** 
 ***    002,Medium,Add Two Numbers 
 ****************************************************/

/*
You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Use dummy head. Add additional node if final carry = 1.
// Caveats:
// 1. Don't forget to move l1 and l2 forward!
// 2. Last step, scheck if carry > 0, not carry > 1 !

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0), *p(dummy);
        int sum = 0, carry = 0;
        while(l1 || l2) {
            int v1 = l1 ? l1->val : 0;
            int v2 = l2 ? l2->val : 0;
            sum = v1 + v2 + carry;
            carry = sum / 10;
            sum %= 10;
            p->next = new ListNode(sum);
            p = p->next;
            if(l1) l1 = l1->next;
            if(l2) l2 = l2->next;
        }
        if(carry > 0) p->next = new ListNode(carry);
        
        p = dummy->next;
        delete dummy;
        return p;
    }
};



/**************************************************** 
 ***    003,Medium,Longest Substring Without Repeating Characters 
 ****************************************************/

/*
Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
*/

// Solution 1, use a map to store the position of each character (since s is string, can use an indexed array which is faster than map). Scan from left to right, and maintain a map to store characters already seen and its last position, update length each time.
// Use a pointer (i) to store the current front of substring
// When a character is not in the map, insert it to map; 
// When a character is found and its index is within i and j, then move i to one character to the right of it. 

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> pos(256, -1); //map<char, int> pos;
        int max_len(0);
        for(int i = 0, j = 0; j < s.size(); ++j) {
            char c = s[j];
            if(pos[c] >= i)  i = pos[c]+1;
            pos[c] = j;
            max_len = max(max_len, j-i+1);
        }
        return max_len;
    }
};

// Another solution by counting the occurrences of each character, similar to problem 159.
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
         int n = s.size(); //number of records
         int istart = 0, max_len = 0;
         int count = 0;
         vector<int> dict(256);
         for(int i = 0; i < n; ++i) {
            char c = s[i];
            ++dict[c];
            while(dict[c] > 1) {
               --dict[s[istart++]];
            }
            max_len = max(max_len, i-istart+1);
         }
         return max_len;
    }
};

/**************************************************** 
 ***    005,Medium,Longest Palindromic Substring 
 ****************************************************/

/*
Given a string S, find the longest palindromic substring in S. You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.
*/

// Scan from left to right, for each character, check if it is in the middle of a palindrome. 
// Consider even and odd cases.
// Caveat: be careful of index bounds!

class Solution {
public:
    string longestPalindrome(string s) {
        if(s.empty()) return s;
        int n = s.size();
        int istart = 0, max_len = 1;
        for(int i = 0; i < n; ++i) {
            //check odd substrings (j is offset from middle)
            for(int j = 1; j <= i && i+j < n && s[i-j] == s[i+j]; ++j) {
                if(2*j+1 > max_len) { max_len = 2*j+1; istart = i-j; }
            }
            //check even substrings (j is offset from middle)
            for(int j = 1; j <= i+1 && i+j < n && s[i-j+1] == s[i+j]; ++j) {
                if(2*j > max_len) { max_len = 2*j; istart = i-j+1; }
            }
        }
        return s.substr(istart, max_len);
    }
};

/**************************************************** 
 ***    011,Medium,Container With Most Water 
 ****************************************************/

/*
Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container. 
*/

/*
Similar idea to "trapping rain water". Maintain two pointers and find the minimum water level deterimed by the two pointers. Move from the side with lower height, stop when two pointers meet.
The height of container is the smaller of the two ends. Proceed by moving the lower point inwards, because we can proove that the interval between lo and hi is the widest one possible for the container of height of height[lo].
Proceeding from higher point is wrong! e.g.
height:   3 9 1 1
position: 0 1 2 3

l = 0, h = 3 => area = 3
if we move from higher point, we missed [0, 1] with area 6.
*/

class Solution {
public:
    int maxArea(vector<int>& height) {
        int area = 0;
        int n = height.size();
        if(n <= 1) return 0;
        int l(0), r(n-1);
        while(l < r) {
            area = max(area, min(height[l], height[r])*(r-l));
            if(height[l] < height[r]) l++;
            else r--;
        }
        return area;
    }
};

/**************************************************** 
 ***    012,Medium,Integer to Roman 
 ****************************************************/

/*
Given an integer, convert it to a roman numeral.

Input is guaranteed to be within the range from 1 to 3999.
*/

// A simple solution using a table

const int values[13] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
const string strs[13] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
        
class Solution {
public:
    string intToRoman(int num) {
        string s;
        for(int i = 0; i < 13; ++i) {
            while(num >= values[i]) {
                num -= values[i];
                s += strs[i];
            }
            if(num == 0) break;
        }
        return s;
    }
};

// An old solution. use an append function. Deal with one, five, ten
class Solution {
public:
    string intToRoman(int num) {
        string s;
        int n = 0;
        if (num >= 1000) { append(s, num/1000, 'M', 'Y', 'Z'); num %= 1000; }
        if (num >= 100)  { append(s, num/100,  'C', 'D', 'M'); num %= 100;  }
        if (num >= 10)   { append(s, num/10,   'X', 'L', 'C'); num %= 10;   }
        if (num >= 1)    { append(s, num/1,    'I', 'V', 'X'); }
        return s;
    }
    //c1 is for one, c2 is for five, c3 is for ten
    void append(string& s, int d, char c1, char c2, char c3) {
        if (d == 0) return;
        else if (d <= 3) s += string(d, c1);
        else if (d == 4) { s += c1; s += c2;  }
        else if (d == 5) s += c2;
        else if (d <= 8) { s += c2; s += string(d-5, c1); }
        else if (d == 9) { s += c1; s += c3; }
    }
};

/**************************************************** 
 ***    015,Medium,3Sum 
 ****************************************************/

/*
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

    Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
    The solution set must not contain duplicate triplets.

    For example, given array S = {-1 0 1 2 -1 -4},

    A solution set is:
    (-1, 0, 1)
    (-1, -1, 2)
*/

/// O(n2) solution
/// Need to consider duplicated entries.
/// Optimization: break if nums[i] > 0, and also num[n-1] < 0 (52ms => 48ms)

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > ret;
        int n = nums.size();
        if(n <= 2) return ret;
        vector<int> tmp(3, -1);
        sort(nums.begin(), nums.end());
        if(nums[n-1] < 0) return ret; //no need to continue if largest value is < 0
        for(int i = 0; i < n-2; i++) {
            if(nums[i] > 0) break; //no need to continue if found a positive number
            if(i > 0 && nums[i] == nums[i-1]) continue; //avoid duplicates
            if(nums[i] + nums[i+1] + nums[i+2] > 0) break;
            if(nums[i] + nums[n-2] + nums[n-1] < 0) continue;
            int target = -nums[i];
            int j = i+1, k = n-1;
            while(j < k) {
               int sum = nums[j] + nums[k];
               if(sum < target) j++;
               else if(sum > target) k--;
               else {
                   tmp[0] = nums[i]; tmp[1] = nums[j]; tmp[2] = nums[k];
                   ret.push_back(tmp);
                   j++; k--;
                   while(j < k && nums[j] == nums[j-1]) j++; //avoid duplicates
                   while(j < k && nums[k] == nums[k+1]) k--; //avoid duplicates
               }
            }
        }
        return ret;
    }
};

/// O(n2 lgn) solution. Iterate first 2 brute-force, and use binary search to find 3rd element.
/// Need to avoid duplicated entries. (lines 14 and 16).

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > ret;
        
        int n = nums.size();
        if(n <= 2) return ret;
        vector<int> sol(3, 0);
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n; ++i) { //whether nums[i] is one of the triplet?
            if(i > 0 && nums[i] == nums[i-1]) continue; //ignore duplicates
            for(int j = i+1; j < n; ++j) {
                if(j > i+1 && nums[j] == nums[j-1]) continue; //ignore duplicates
                int target = -(nums[i] + nums[j]);
                int r = find(nums, j+1, target);
                if(r != -1) {
                    sol[0] = nums[i], sol[1] = nums[j], sol[2] = nums[r];
                    ret.push_back(sol);
                }
            }
        }
        return ret;
    }
    
    //search target in sorted array nums[k..end)
    int find(vector<int>& nums, int k, int target) {
        int lo = k, hi = nums.size()-1;
        while(lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if(target < nums[mid]) hi = mid-1;
            else if(target > nums[mid]) lo = mid+1;
            else return mid;
        }
        return -1;
    }
};

/**************************************************** 
 ***    016,Medium,3Sum Closest 
 ****************************************************/

/*
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/

/// O(n2) solution

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int result = 0;
        int min_diff = INT_MAX;
        int n = nums.size();
        if(n <= 2) return 0;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n-2; ++i) {
            if(i > 1 && nums[i] == nums[i-1]) continue;
            int j = i+1, k = n-1;
            while(j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                int diff = target - sum;
                if(diff == 0) return target;
                else if(diff < 0) k--;
                else j++;
                if(abs(diff) < min_diff) {
                    min_diff = abs(diff);
                    result = sum;
                }
            }
        }
        return result;
    }
};

/**************************************************** 
 ***    017,Medium,Letter Combinations of a Phone Number 
 ****************************************************/

/*
Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

Note:
Although the above answer is in lexicographical order, your answer could be in any order you want. 
*/

// Solution 1. Recursive dfs solution. Use a dict storing the conversion rule. Terminate at i == n.
// A variant is also given where termination is at i == n-1.

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> dict = {"", "", "abc", "def", "ghi", "jkl", "mno", "prqs", "tuv", "wxyz"};
        vector<string> result;
        if(digits.empty()) return result;
        int n = digits.size();
        string tmp(n, '0');
        dfs(digits, 0, dict, tmp, result);
        return result;
    }
    //starting from i-th digits
    void dfs(const string& digits, int i, vector<string>& dict, string& tmp, vector<string>& result) {
        if(i == digits.size()) {
            result.push_back(tmp);
            return;
        }
        int idx = digits[i] - '0';
        //choose among possible characters in dict[idx]
        for(auto c : dict[idx]) {
            tmp[i] = c;
            dfs(digits, i+1, dict, tmp, result);
        }
    }
/*  // simplified dfs routine terminating at i == n-1
    void dfs(const string& digits, int i, vector<string>& dict, string& tmp, vector<string>& result) {
        int idx = digits[i] - '0';
        int n = digits.size();
        //choose among possible characters in dict[idx]
        for(auto c : dict[idx]) {
            tmp[i] = c;
            if(i == n-1) result.push_back(tmp);
            else dfs(digits, i+1, dict, tmp, result);
        }
    }
*/
};


/**************************************************** 
 ***    018,Medium,4Sum 
 ****************************************************/

/*
Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note:

    Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d)
    The solution set must not contain duplicate quadruplets.

    For example, given array S = {1 0 -1 0 -2 2}, and target = 0.

    A solution set is:
    (-1,  0, 0, 1)
    (-2, -1, 1, 2)
    (-2,  0, 0, 2)
*/

// O(n3) solution, need to take care of duplicated entries.
// Also several optimization lines (break/continue).
// Storing partial sums (e.g. nums[n-2] + nums[n-1]) does not reduce run time.

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int> > result;
        vector<int> tmp(4, 0);
        int n = nums.size();
        if(n <= 3) return result;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n-3; ++i) {
            if(i > 0 && nums[i] == nums[i-1]) continue; //avoid duplicates
            if(nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target) break;
            if(nums[i] + nums[n-3] + nums[n-2] + nums[n-1] < target) continue;
            for(int j = i+1; j < n-2; ++j) {
                if(j > i+1 && nums[j] == nums[j-1]) continue; //avoid duplicates
                if(nums[i] + nums[j] + nums[j+1] + nums[j+2] > target) break;
                if(nums[i] + nums[j] + nums[n-2] + nums[n-1] < target) continue;
                int k = j+1, l = n-1;
                while(k < l) {
                    int sum = nums[i] + nums[j] + nums[k] + nums[l];
                    if(sum < target) k++;
                    else if(sum > target) l--;
                    else { //equal
                        tmp[0] = nums[i]; tmp[1] = nums[j]; tmp[2] = nums[k]; tmp[3] = nums[l];
                        result.push_back(tmp);
                        k++; l--;
                        while(k < l && nums[k] == nums[k-1]) k++;
                        while(k < l && nums[l] == nums[l+1]) l--;
                    }
                }
            }
        }
        return result;
    }
};

/**************************************************** 
 ***    022,Medium,Generate Parentheses 
 ****************************************************/

/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

"((()))", "(()())", "(())()", "()(())", "()()()" 
*/

// Recursive solution. backtracking, DFS
// pre-allocate string, pass reference and string index to avoid string copying. Keep track of number of open and close brackets left.

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        if(n < 1) return result;
        string str(2*n, '0');
        dfs(n, n, 0, str, result);
        return result;
    }
    void dfs(int nl, int nr, int i, string& str, vector<string>& result) {
        if(i == str.size()) {
            result.push_back(str);
            return;
        }
        if(nl > 0) {
            str[i] = '(';
            dfs(nl-1, nr, i+1, str, result);
        }
        if(nr > 0 && nl < nr) {
            str[i] = ')';
            dfs(nl, nr-1, i+1, str, result);
        }
    }
};

// Another iterative solution
class Solution {
public:
	vector<string> generateParenthesis(int n) {
		vector<string> ret;
		int k(0); //k is the index of current parenthesis
		int nr(0); //number of left and right parenthesis
		string str(2*n, '('); //initially '('
		while(1) {
			int nl = k+1-nr;
			if(k == 2*n) { //reached end of string, add to solution
				ret.push_back(str);
				k--;
				update(str[k], nr);
			} else if (str[k] == 'X') { //exhaust all trials, abandon and retrace
				update(str[k], nr); //reset to '.'
				k--;
				if(k < 0) break; //breaking condition
				update(str[k], nr); //increment last element
			} else if(nr > n || nl > n || nl < nr){ //unbalanced
				update(str[k], nr);
			} else { //normal
				k++;
			}
		}
		return ret;
	}
	void update(char& c, int& nr) {
		if(c == '(') {
			c = ')';
			nr ++;
		} else if(c == ')') {
			c = 'X';
			nr --;
		}	else if(c == 'X') c = '(';
	}
};

/**************************************************** 
 ***    024,Medium,Swap Nodes in Pairs 
 ****************************************************/

/*
Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Solution 1. Iterative solution. Use a dummy head and two pointers.

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        //p is tail of processed list part
        ListNode *p = dummy, *q = p->next;
        //swap q and q->next
        while(q && q->next) {
            ListNode *r = q->next;
            q = r->next; //move to next
            r->next = p->next;
            p->next = r;
            p = r->next; //move forward
            p->next = q;
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};

// Solution 2. Recursive solution.
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode *p = head->next, *q = p->next;
        p->next = head;
        head->next = swapPairs(q);
        return p;
    }
};


/**************************************************** 
 ***    029,Medium,Divide Two Integers 
 ****************************************************/

/*
Divide two integers without using multiplication, division and mod operator.

If it is overflow, return MAX_INT. 
*/

// Solution 1. Subtract and bit-wise shift (*2).
// Need to consider overflow cases.
class Solution {
public:
    int divide(int dividend, int divisor) {
        if(divisor == 0) return INT_MAX;
        if(dividend == 0) return 0;
        if(dividend == INT_MIN) {
            if(divisor == -1) return INT_MAX;
            else if(divisor == 1) return INT_MIN;
        }
        long a = dividend, b = divisor;
        bool neg = (a > 0) ^ (b > 0);
        a = abs(a); b = abs(b);
        int result = 0;
        while(a >= b) {
            long x = b, y = 1;
            while(a >= (x << 1)) {
              x <<= 1; y <<= 1;
            }
            a -= x;
            result += y;
        }
        //result <= INT_MAX
        if(neg) result = -result;
        return result;
    }
};

// Solution 2. Similar one.
class Solution {
public:
    int divide(int dividend, int divisor) {
        long a = dividend, b = divisor;
        a = abs(a); b = abs(b);
        bool negative = (dividend < 0) ^ (divisor < 0);
        // a/b
        long x(b), n(1), ret(0);
        while (x <= a) {
            x <<= 1; n <<= 1;
        }
        //x = n*b and > a
        while (a > 0) {
            while(n > 0 && x > a) { x >>=1; n>>=1; }
            // x <= a or n == 1
            if (n == 0)  break;
            else {
                ret += n;
                a -= x;
            }
        }
        if(negative) return (ret <= long(INT_MAX)+1) ? -ret : INT_MAX;
        else return ret <= INT_MAX ? ret : INT_MAX;
    }
};

/**************************************************** 
 ***    031,Medium,Next Permutation 
 ****************************************************/

/*
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
*/

/* Solution implementing an algorithm to generate permutation sequence in lexigraphical order
How is lexigraphical order generated?

For the permutations with the same prefix, the following sub permutations should also be in lexigraphical order, e.g.
13245, 13254, 13425, 13452 ... (same prefix 13, then 2,4,5 are permutaed in lexi-order as well).

For a group of numbers, the first one in the lexi-order is the ascending sequence, the last one is the descending sequence.

We scan right to left, if we see a subsequence that is descending, that part is already the last one of its own lexi-order. For example:

1,2,5,4,3. What is next step? Since we finished the last three positions, we need to proccess 2, basically move to the next larger one, 3.
How to find 3 ? we utilize the descending order of array 5,4,3 we search from right to left and find the first element larger than 2, and it will be the next one. We simply swap it with 2, and the resulting array 5,4,2 will still be descending. We need to reverse it to make it ascending (as the first permutation in the new sub-array 2,4,5). Therefore, here is the whole procedure:

1. Find the largest index k such that a[k] < a[k + 1]. If no such index exists, the permutation is the last permutation.
2. Find the largest index l greater than k such that a[k] < a[l].
3. Swap the value of a[k] with that of a[l].
4. Reverse the sequence from a[k + 1] up to and including the final element a[n].

Since the comparisons are strict, we will not perform unecessary swaps in the case of duplicated ent
ries. So the algorithm works for duplicated entries as well.
*/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int k = n-2, l = n-1;
        while(k >= 0 && nums[k] >= nums[k+1]) k--;
        //k is the last k such that nums[k] < nums[k+1]
        if(k == -1) { //no next, just reverse it to 1st lexi-order
            int i = 0, j = n-1;
            while(i < j) swap(nums[i++], nums[j--]);
            return;
        }
        while(l > k && nums[l] <= nums[k]) l--;
        //l is the last l such that nums[l] > nums[k]
        //swap nums[k] and nums[l]
        swap(nums[k], nums[l]);
        //sort numbers after k
        int i = k+1, j = n-1;
        while(i < j) swap(nums[i++], nums[j--]);
    }
};


/**************************************************** 
 ***    034,Medium,Search for a Range 
 ****************************************************/

/*
Given a sorted array of integers, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4]. 
*/

/// Binary search two passes.
/// First find the left-most index with value >= target as lo
/// Then find the right-most index with value <= target as hi
/// Caveat: If lo <= hi, then found the interval, otherwise, not found, return [-1, -1]

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> ret(2, -1);
        if(nums.empty()) return ret;
        int n = nums.size();
        int lo(0), hi(n-1);
        while(lo <= hi) {
            int mid = lo + (hi-lo)/2;
            if(nums[mid] < target) lo = mid+1;
            else hi = mid-1;
        }
        ret[0] = lo;

        lo = 0, hi = n-1;
        while(lo <= hi) {
            int mid = lo + (hi-lo)/2;
            if(nums[mid] <= target) lo = mid+1;
            else hi = mid-1;
        }
        ret[1] = hi;
        if(ret[0] > ret[1]) ret[0] = ret[1] = -1;
        return ret;
    }
};

/**************************************************** 
 ***    035,Medium,Search Insert Position 
 ****************************************************/

/*
Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0
*/

// Binary search. Loop invariant:
// nums[0 .. lo-1] < target, nums[hi+1, n) > target, nums[lo, hi] TBD
// If found, return index. If not found, return position lo, because when out of while loop we have lo=hi+1, and target is between nums[hi] and nums[lo].

class Solution {
    
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        int lo(0), hi(n-1), mid(0);
        while(lo <= hi) {
            mid = lo + (hi-lo)/2;
            if(target == nums[mid]) return mid;
            if(target < nums[mid]) hi = mid-1;
            else lo = mid+1;
        }
        return lo;
    }
}; 

/**************************************************** 
 ***    039,Medium,Combination Sum 
 ****************************************************/

/*
Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

Note:

    All numbers (including target) will be positive integers.
    Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
    The solution set must not contain duplicate combinations.

For example, given candidate set 2,3,6,7 and target 7,
A solution set is:
[7]
[2, 2, 3]
*/

// Solution 1. Recursive solution. Need to sort the number first. Use the fact that all numbers are positive, terminate when target < current number.
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int> > result;
        int n = candidates.size();
        if(n == 0) return result;
        sort(candidates.begin(), candidates.end());
        vector<int> tmp;
        dfs(candidates, 0, target, tmp, result);
        return result;
    }
    void dfs(vector<int>& candidates, int i, int target, vector<int>& tmp, vector<vector<int> >& result) {
        int n = candidates.size();
        if(i == n || target < candidates[i]) return;
        tmp.push_back(0);
        //choose any number from i to n.
        for(int j = i; j < n; ++j) {
            tmp.back() = candidates[j];
            if(target == candidates[j]) result.push_back(tmp);
            else dfs(candidates, j, target-candidates[j], tmp, result);
        }
        tmp.pop_back();
    }
};

// Solution 2. An old iterative solution. (faster)
class Solution {
public:
	vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
		vector<vector<int> > ret;
		if(candidates.empty()) return ret;
		
		vector<int> sorted = sort(candidates);
	
		//maximum possible numbers target/ min(sorted)
		int n = sorted.size();
		int csize = std::ceil(target/sorted[0]); //no zero!
		vector<int> choice(csize, -1); //stores the indices of a solution in sorted array
		int k = 0; // the k-th number
		int sum = 0; // accumulated sum
		while(k >= 0) {
			if(k == csize) { // target > sums
				k--;
				continue;
			}
			if(choice[k] == -1) { //first time for k-th number
				choice[k] = ((k > 0) ? choice[k-1] : 0); //start from same number before
			} else { //not the first time
				int prev = sorted[choice[k]];
				sum -= prev; //remove sum
				choice[k] ++;
			}
		
			if(choice[k] == n) { // searched till the end
			    choice[k] = -1; //reset
				k--;
				continue;
			}
			//found one
			sum += sorted[choice[k]]; //update sum
			
			//sum exceeding or equal to target
			if(sum >= target) {
				if(sum == target) ret.push_back(construct(choice, sorted));
				sum -= sorted[choice[k]];
				choice[k] = -1;
				k--;
			} else { //check next number
				k++;
			}
		}
		return ret;
	}
	
	//construct vector from choices
	vector<int> construct(const vector<int>& choice, const vector<int>& sorted) {
		vector<int> ret;
		for(int j = 0; j < choice.size(); ++j) {
			if(choice[j] != -1) ret.push_back(sorted[choice[j]]);
			else break; //can break if found an invalid -1 entry
		}
	return ret;
	}
	//insertion sort
	vector<int> sort(vector<int>& num) {
		vector<int> sorted = num;
		int n = sorted.size();
		int i, j;
		for(i = 1; i < n; ++i) {
			j = i;
			int key = sorted[j];
			while( j >= 1 && sorted[j-1] > key) {
				sorted[j] = sorted[j-1]; //shift to right by 1
				j--;
			}
			sorted[j] = key;
		}
		return sorted;
	}
};


/**************************************************** 
 ***    040,Medium,Combination Sum II 
 ****************************************************/

/*
Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:

    All numbers (including target) will be positive integers.
    Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
    The solution set must not contain duplicate combinations.

For example, given candidate set 10,1,2,7,6,1,5 and target 8,
A solution set is:
[1, 7]
[1, 2, 5]
[2, 6]
[1, 1, 6]
*/

// Notice the difference between this and problem 039? Here it is "collection" while 039 is "set", which means that here C can have duplicates.

// Solution 1. Iterative solution. Similar to 039, except need to avoid choosing duplicates again, also should only choose one number once.
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int> > result;
        int n = candidates.size();
        if(n == 0) return result;
        sort(candidates.begin(), candidates.end());
        vector<int> tmp;
        dfs(candidates, 0, target, tmp, result);
        return result;
    }
    void dfs(vector<int>& candidates, int i, int target, vector<int>& tmp, vector<vector<int> >& result) {
        if(target == 0) {
            result.push_back(tmp);
            return;
        }
        int n = candidates.size();
        if(i == n || target < candidates[i]) return;
        tmp.push_back(0);
        //choose any number from i to n.
        for(int j = i; j < n; ++j) {
            if(j > i && candidates[j] == candidates[j-1]) continue; //avoid duplicates
            tmp.back() = candidates[j];
            dfs(candidates, j+1, target-candidates[j], tmp, result); //j+1: choose the number only once.
        }
        tmp.pop_back();
    }
};


/**************************************************** 
 ***    043,Medium,Multiply Strings 
 ****************************************************/

/*
Given two numbers represented as strings, return multiplication of the numbers as a string.

Note: The numbers can be arbitrarily large and are non-negative.
*/

/// Just minic the elementary school multiplication method
///      1 2 3 4   (num2, outer loop)
///    x   5 6 7   (num1, inner loop)
/// -------------
///      8 6 3 8
///    7 4 0 4
///  6 1 7 0
/// -------------
///  6 9 9 6 7 8
/// If nums1 and num2 have l1 and l2 digits, without carry over, the product will have l1+l2-1 digits. In this way, product of num1[i] and num2[j] should be aligned to num[i+j].
/// Start from the bottom up. Update the result in-place (instead of creating intermediate strings to store the products)
/// each time inner loop is done, the carry should go to result[i-1] or additional carry digit.

class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0") return "0";
        int l1 = num1.size(), l2 = num2.size();
        string result(l1+l2-1, '0'); // result has l1+l2-1 digits
        int sum = 0, carry = 0;
        for(int i = l1-1; i >= 0; --i) {
            carry = 0;
            for(int j = l2-1; j >= 0; --j) {
                sum = (num1[i] - '0')*(num2[j] - '0') + (result[i+j] - '0') + carry;
                carry = sum / 10;
                sum %= 10;
                result[i+j] = sum + '0';
            }
            if(carry > 0) {
                if(i > 0) result[i-1] = carry + '0'; 
                else result = char(carry + '0') + result;
            }
        }
        
        return result;
    }
};

// Another solution, create an intemediate string for products, shift the products to correct positions by appending proper number of zeroes, and add products together. Optimization on the for loops, so that roughly strings of similar lengths are added. But still very slow ...
class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0") return "0";
        int l1 = num1.size(), l2 = num2.size();
        string result = "0";
        for(int k = 0; k < l1+l2-1; ++k) {
            for(int i = max(0, k-l2+1); i <= min(k, l1-1); ++i) {
                int j = k-i;
                char c1 = num1[l1-i-1], c2 = num2[l2-j-1];
                string prod = num2str((c1-'0')*(c2-'0'));
                prod.append(k, '0');
                result = add(result, prod);
            }
        }
        return result;
    }
    
    string num2str(int num) {
        if(num == 0) return "0";
        string result;
        while(num) {
            result = char(num % 10 + '0') + result;
            num /= 10;
        }
        return result;
    }

    string add(const string& num1, const string& num2) {
        int l1 = num1.size(), l2 = num2.size();
        int l = max(l1, l2);
        string result(l, '0');
        int sum = 0, carry = 0;
        for(int i = 0; i < l; ++i) {
            if(i >= l1) sum = (num2[l2-i-1] - '0') + carry;
            else if(i >= l2) sum = (num1[l1-i-1] - '0') + carry;
            else sum = (num1[l1-i-1]-'0') + (num2[l2-i-1]-'0') + carry;
            carry = sum / 10;
            sum %= 10;
            result[l-i-1] = sum + '0';
         }
         if(carry == 1) result = '1' + result;
         return result;
    }
};

// A better solution by multiplying string to each integer number, and adding the result together. The key is function:
// string multiply(const string& num, int d)

class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0") return "0";
        string result = "0";
        if(num1.size() < num2.size()) num1.swap(num2); //longer one first
        int l1 = num1.size(), l2 = num2.size();
        for(int i = 0; i < l2; ++i) {
            string prod = multiply(num1, num2[l2-i-1]-'0');
            prod.append(i, '0');
            result = add(prod, result);
        }
        return result;
    }
    
    string num2str(int num) {
        if(num == 0) return "0";
        string result;
        while(num) {
            result = char(num % 10 + '0') + result;
            num /= 10;
        }
        return result;
    }

    string multiply(const string& num, int d) {
        if(d == 0) return "0";
        else if(d == 1) return num;
        int n = num.size();
        string result(n, '0');
        int sum = 0, carry = 0;
        for(int i = 0; i < n; ++i) {
            sum = (num[n-i-1] - '0')*d + carry;
            carry = sum / 10;
            sum %= 10;
            result[n-i-1] = sum + '0';
        }
        if(carry > 0) result = char(carry + '0') + result;
        return result;
    }

    string add(const string& num1, const string& num2) {
        int l1 = num1.size(), l2 = num2.size();
        int l = max(l1, l2);
        string result(l, '0');
        int sum = 0, carry = 0;
        for(int i = 0; i < l; ++i) {
            if(i >= l1) sum = (num2[l2-i-1] - '0') + carry;
            else if(i >= l2) sum = (num1[l1-i-1] - '0') + carry;
            else sum = (num1[l1-i-1]-'0') + (num2[l2-i-1]-'0') + carry;
            carry = sum / 10;
            sum %= 10;
            result[l-i-1] = sum + '0';
         }
         if(carry == 1) result = '1' + result;
         return result;
    }
};

/**************************************************** 
 ***    046,Medium,Permutations 
 ****************************************************/

/*
Given a collection of numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1]. 
*/

// Solution 1. Use next permutation algorithm to print permutations in lexigraphical order (see 031)
// use a tag to indicate the status of permutation. If reaching the last permutation (descending order), return false. 
// Also works for cases when duplicated entries exist
// Caveats: 
// 1. If use a counter to print exactly n! permutations, then does not for cases where duplicated entries exist!
// 2. array should be sorted in the beginning!

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        sort(nums.begin(), nums.end()); //first sort the array!
        result.push_back(nums);
        while(nextPermutation(nums)) result.push_back(nums);
        return result;
    }
    bool nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int k = n-2, l = n-1;
        while(k >= 0 && nums[k] >= nums[k+1]) k--;
        //k is the last k such that nums[k] < nums[k+1]
        if(k == -1) return false;
        while(l > k && nums[l] <= nums[k]) l--;
        //l is the last l such that nums[l] > nums[k]
        //swap nums[k] and nums[l]
        swap(nums[k], nums[l]);
        //sort numbers after k
        int i = k+1, j = n-1;
        while(i < j) swap(nums[i++], nums[j--]);
        return true;
    }
};

// Solution 2. Recursive solution using swapping. Does not work for duplicated cases. Developing a method that deals with duplicated cases are not straightforward, because the array order is destructed during the swapping! One hack is to introduce a table storing used elements, and avoid using them again in the same level of dfs search (see 047)
// Note that this method does not print the permutations in lexigraphical order!

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        dfs(nums, 0, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<vector<int> >& result) { 
        int n = nums.size();
        if(i == n) {
            result.push_back(nums);
            return;
        }
        for(int k = i; k < n; ++k) {
            swap(nums[i], nums[k]);
            dfs(nums, i+1, result);
            swap(nums[i], nums[k]);
        }
    }
};

// Solution 3. Recursive solution, each time take a number, use a bit status number indicating which number has been taken. Can be extended to duplicated cases (see 047).
// Some bit operators:
// checking if k-th number is used: if(state & (1 << k))
// set the tag for the k-th number: state != (1 << k)
// unset the tag for the k-th number: state &= ~(1 << k)

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        int state = 0; //bit states for 0 to n-1 
        int n = nums.size();
        vector<int> tmp(n, 0);
        dfs(nums, 0, tmp, result, state);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result, int state) {
        int n = nums.size();
        if(i == n) {
            result.push_back(tmp);
            return;
        }
        for(int k = 0; k < n; ++k) { //try all possible numbers
            if(state & (1 << k)) continue; //already used
            tmp[i] = nums[k]; //use nums[k]
            state |= (1 << k);
            dfs(nums, i+1, tmp, result, state);
            state &= ~(1 << k); //retrace
        }
    }
};

// Solution 4. An iterative solution using O(n) space to track the status of each number, and another O(n) space to record the positions of each number used.

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        int n = nums.size(), i(0);
        vector<bool> used(n, false); //whether i-th number has been used
        vector<int> pos(n, -1); //position in nums for the number chosen for i-th position in permutation sequence
        while(i >= 0) { //check i-th position
            if(i == n) {
                vector<int> tmp(n, 0);
                for(int k = 0; k < n; ++k) tmp[k] = nums[pos[k]];
                result.push_back(tmp);
                i--; //retrace
                continue;
            }
            //find next unused number for i-th selection
            if(pos[i] >= 0) used[pos[i]] = false; //unset
            pos[i]++;
            while(pos[i] < n && used[pos[i]]) pos[i]++;
            if(pos[i] == n) { //no numbers left
                pos[i] = -1;
                i--; //retrace
                continue;
            }
            used[pos[i]] = true;
            //find next pos[i]
            i++;
        }
        return result;
    }
};



/**************************************************** 
 ***    047,Medium,Permutations II 
 ****************************************************/

/*
Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[1,1,2], [1,2,1], and [2,1,1]. 
*/

// Solution 1. Use next permutation algorithm to print permutations in lexigraphical order (see 031)
// Copied from 046_permutation.cc

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        sort(nums.begin(), nums.end());
        result.push_back(nums);
        while(nextPermutation(nums)) result.push_back(nums);
        return result;
    }
    bool nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int k = n-2, l = n-1;
        while(k >= 0 && nums[k] >= nums[k+1]) k--;
        //k is the last k such that nums[k] < nums[k+1]
        if(k == -1) return false;
        while(l > k && nums[l] <= nums[k]) l--;
        //l is the last l such that nums[l] > nums[k]
        //swap nums[k] and nums[l]
        swap(nums[k], nums[l]);
        //sort numbers after k
        int i = k+1, j = n-1;
        while(i < j) swap(nums[i++], nums[j--]);
        return true;
    }
};

// Solution 2. Recursive solution with swapping adapted from 046_permutations.cc. 
// To deal with duplicated entries, we can't use something simpler such as checking current to be exchanged ia equal to previously exchanged one, because the subarray maybe unsorted, for example, given aabbccd, and after a while we have bcd|caba, and the second part is unsorted. 
// Unless using a set structure, there is no way of preventing 'c' to be swapped with second 'a', because the previous is a 'b'.

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        dfs(nums, 0, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<vector<int> >& result) {
        int n = nums.size();
        if(i == n) {
            result.push_back(nums);
            return;
        }
        unordered_set<int> used;
        for(int k = i; k < n; ++k) {
            if(used.count(nums[k])) continue; //ignore duplicates that are already used
            used.insert(nums[k]); //insert to used table
            swap(nums[i], nums[k]);
            dfs(nums, i+1, result);
            swap(nums[i], nums[k]);
        }
    }
};

// Solution 3. Recursive solution adapted from Solution 3 in 046_permutations.cc. using a bit number representing status. Adapted to duplicated cases. Use a number "last" to store the last number used. When scanning forwards, skip the numbers equal to last as well.

class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        int state = 0; //bit states for 0 to n-1 
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<int> tmp(n, 0);
        dfs(nums, 0, tmp, result, state);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result, int state) {
        int n = nums.size();
        if(i == n) {
            result.push_back(tmp);
            return;
        }
        int last = INT_MIN; // assume no numbers are INT_MIN
        for(int k = 0; k < n; ++k) { //try all possible numbers
            if((state & (1 << k)) || nums[k] == last) continue; //already used, or duplicate entries
            last = tmp[i] = nums[k]; //use nums[k]
            state |= (1 << k);
            dfs(nums, i+1, tmp, result, state);
            state &= ~(1 << k); //retrace
        }
    }
};

// Solution 4. An iterative solution. Similar to that of 046_permutations. Only difference is that when we scan forward, if we see a used character OR a character that is the same as previous one, then we continue searching.
// A tricky case is when there is no previous character. So need to carefully write the conditiont in while loop.

class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.empty()) return result;
        int n = nums.size(), i(0);
        sort(nums.begin(), nums.end()); //first sort array
        vector<bool> used(n, false); //whether i-th number has been used
        vector<int> pos(n, -1); //position in nums for the number chosen for i-th position in permutation sequence
        while(i >= 0) { //check i-th position
            if(i == n) {
                vector<int> tmp(n, 0);
                for(int k = 0; k < n; ++k) tmp[k] = nums[pos[k]];
                result.push_back(tmp);
                i--; //retrace
                continue;
            }
            //find next unused number for i-th selection
            if(pos[i] >= 0) used[pos[i]] = false; //unset
            int tmp_pos = pos[i];
            pos[i]++;
            while(pos[i] < n && (used[pos[i]] || (tmp_pos >= 0 && nums[pos[i]] == nums[tmp_pos]))) pos[i]++;
            if(pos[i] == n) { //no numbers left
                pos[i] = -1;
                i--; //retrace
                continue;
            }
            used[pos[i]] = true;
            //find next pos[i]
            i++;
        }
        return result;
    }
};


/**************************************************** 
 ***    048,Medium,Rotate Image 
 ****************************************************/

/*
You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Follow up:
Could you do this in-place?
*/

/// Proceed in a circular fashion, and outer to inner.
/// Each element, perform a 4-rotation with 3 counterparts
/// make sure the bounds for i and j are correct
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if(n <= 1) return;
        
        for(int i = 0; i < n/2; ++i) {
            for(int j = i; j < n-1-i; ++j) {
                //4-rotation
                int tmp = matrix[i][j];
                matrix[i][j] = matrix[n-1-j][i];
                matrix[n-1-j][i] = matrix[n-1-i][n-1-j];
                matrix[n-1-i][n-1-j] = matrix[j][n-1-i];
                matrix[j][n-1-i] = tmp;
            }
        }
    }
};

/**************************************************** 
 ***    049,Medium,Group Anagrams 
 ****************************************************/

/*
Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
Return:

[
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
]

Note:

    For the return value, each inner list's elements must follow the lexicographic order.
    All inputs will be in lower-case.
*/

// Solution 1. Using a hash table to store the already found anagrams. Use the sorted string as the key. 68ms.
// For each string in strs, if found in table, then insert to approapriate positions, otherwise, add a new vector to the result, and push the string to that vector.
// Finally, sort each sub-vector

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        if(strs.empty()) return result;
        unordered_map<string, int> dict;

        for(int i = 0; i < strs.size(); ++i) {
            string s = strs[i];
            sort(s.begin(), s.end());
            if(dict.count(s)) { //found anagrams
                result[dict[s]].push_back(strs[i]);
            } else { //new entry
                dict[s] = result.size();
                result.push_back(vector<string>(1, strs[i]));
            }
        }
        for(int i = 0; i < result.size(); ++i) {
            sort(result[i].begin(), result[i].end());
        }
        return result;
    }
};

// Solution 2. 400ms. Not a very efficient solution.
// First sort the strs array by a customized compare function (compare each string's sorted forms). After this step all anagrams are ajacent to each other. Next step scan the array and group anagrams using the isAnagram function. Still need to sort each group in the end.

bool compare(const string& s, const string& t) {
    string ss = s, tt = t;
    sort(ss.begin(), ss.end());
    sort(tt.begin(), tt.end());
    return ss < tt;
}

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        if(strs.empty()) return result;
        sort(strs.begin(), strs.end(), compare);

        for(int i = 0; i < strs.size(); ++i) {
            if(i == 0 || !isAnagram(strs[i], strs[i-1]))
                result.push_back(vector<string>());
            result.back().push_back(strs[i]);
        }
        for(int i = 0; i < result.size(); ++i) {
            sort(result[i].begin(), result[i].end());
        }
        return result;
    }
    bool isAnagram(const string& s, const string& t) {
        if(s.size() != t.size()) return false;
        int n = s.size();
        if(n == 0) return true;
        if(n == 1) return s == t;
        vector<int> dict(26, 0);
        for(auto c : s) dict[c-'a']++;
        for(auto c : t) {
            if(--dict[c-'a'] < 0) return false;
        }
        return true;
    }
};

// Solution 3. TLE. Brute force solution, very inefficient.
// One pass. Construct result as we scan strs, for each string, linearly scan all anagram groups in results. Compare the string with the first entry of the anagram group. If found equal, insert to this group. Otherwise, append a new group to end of results and insert the string to this group.

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        if(strs.empty()) return result;
        for(auto s : strs) {
            bool hasAnagram = false;
            for(int i = 0; i < result.size(); ++i) {
                if(isAnagram(result[i][0], s)) {
                    result[i].push_back(s);
                    hasAnagram = true;
                    break;
                }
            }
            if(!hasAnagram) result.push_back(vector<string>(1, s));
        }
        for(auto s : result) {
            sort(s.begin(), s.end());
        }
        return result;
    }
    bool isAnagram(const string& s, const string& t) {
        if(s.size() != t.size()) return false;
        int n = s.size();
        if(n == 0) return true;
        if(n == 1) return s == t;
        vector<int> dict(26, 0);
        for(auto c : s) dict[c-'a']++;
        for(auto c : t) {
            if(--dict[c-'a'] < 0) return false;
        }
        return true;
    }
};




/**************************************************** 
 ***    050,Medium,"Pow(x, n) "
 ****************************************************/

/*
Implement pow(x, n)
*/

// O(lgn) iterative solution, decode n into binary digits, and calculate x^1, x^2, x^4 procedingly. When the digit is set, add it into the factor.
// e.g:
// n = 13 =   1     1    0     1
//   x^13 = x^8 + x^4 + .. + x^1
// 1. when n is negative, replace n by -n, and x by 1/x
// 2. To avoid overflow, use long instead of int
// 3. shift n towards right one by one.

class Solution {
public:
    double myPow(double x, int n) {
        if(x == 0.0) return 0.0;
        if(n == 0) return 1;
        long m = n;
        if(m < 0) {
            m = -m; x = 1/x;
        }
        //n > 0
        double y = x;
        double res = 1.0;
        while(m) {
            if(m & 1) res *= y;
            m >>= 1;
            y *= y;
        }
        return res;
    }
};

// Solution 2. Similar to above solution, except shift the power of two towards left (avoid overflow!).
class Solution {
public:
    double myPow(double x, int n) {
        if(x == 0.0) return 0.0;
        if(n == 0) return 1;
        bool rev = (n < 0);
        long nn = abs(n);
        double result = 1.0;
        long m = 1;
        double y = x;
        while(m <= nn) {
            if(nn & m) result *= y;
            y *= y; m <<= 1;
        }
        if(rev) result = 1.0/result;
        return result;
    }
};

// Solution 3. Recursive solution. Three cases: n is even, n is positive odd, n is negative odd.
class Solution {
public:
    double myPow(double x, int n) {
        if(n == 0) return 1;
        if(n == 1) return x;
        if(n == -1) return 1/x;
        double y = myPow(x, n/2);
        if(n % 2 == 0) return y*y;
        else if(n > 0) return y*y*x;
        else return y*y/x;
    }
};


/**************************************************** 
 ***    053,Medium,Maximum Subarray 
 ****************************************************/

/*
Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
the contiguous subarray [4,−1,2,1] has the largest sum = 6.

click to show more practice.
More practice:

If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
*/

// Solution 1. Divide and conquer.
// Find max from left sub array, right sub array, and crossing arrays.
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.empty()) return 0;
        return maxSubArrayAux(nums, 0, nums.size()-1);
    }
    
    int maxSubArrayAux(vector<int>& nums, int lo, int hi) {
        if(lo > hi) return INT_MIN;
        if(lo == hi) return nums[lo]; //only one element
        int mid = lo + (hi - lo) / 2; //break array at mid | mid+1
        int max1 = maxSubArrayAux(nums, lo, mid);
        int max2 = maxSubArrayAux(nums, mid+1, hi);
        int max3 = maxCrossing(nums, lo, hi, mid);
        return max(max(max1, max2), max3);
    }
    
    int maxCrossing(vector<int>& nums, int lo, int hi, int mid) {
        int left_sum = nums[mid], max_left_sum = left_sum;
        int right_sum = nums[mid+1], max_right_sum = right_sum;
        int jleft = mid-1, jright = mid+2;
        while(jleft >= lo) {
            left_sum += nums[jleft];
            max_left_sum = max(max_left_sum, left_sum);
            jleft--;
        }
        while(jright <= hi) {
            right_sum += nums[jright];
            max_right_sum = max(max_right_sum, right_sum);
            jright++;
        }
        return max_left_sum + max_right_sum;
    }
};


/// Solution 2 dynamic programming.
/*
Maximum ending at nums[k] can be obtained from nums[k] and maximum ending at nums[k-1].
1. if max ending at nums[k-1] is positive, then we simply add nums[k] to obtain max ending at nums[k].
2. if max ending at nums[k-1] is negative, then we can discard everything before nums[k], and use nums[k] as max ending at nums[k].
When assigning max_all, using conditional clause (as below) is 4ms faster than using std::max.
*/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.empty()) return 0;
        int max_ending_here = 0, max_all = INT_MIN;
        int n = nums.size();
        for(int i = 0; i < n; ++i) {
            max_ending_here = max_ending_here > 0 ? (max_ending_here + nums[i]) : nums[i];
            if(max_all < max_ending_here) max_all = max_ending_here;
        }
        return max_all;
    }
};

/**************************************************** 
 ***    054,Medium,Spiral Matrix 
 ****************************************************/

/*
Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
Given the following matrix:

[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].
*/

// Keep track of the current boundaries of the matrix, and the current state indicating moving direction
// When moving direction changes, update boundary accordingly
// Return when exactly m*n elements have been visited

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        if(matrix.empty() || matrix[0].empty()) return result;
        int m = matrix.size(), n = matrix[0].size(), mn = m*n;
        top = 0; bottom = m-1; left = 0; right = n-1;
        state = 0;
        result.resize(mn);
        int i(0), j(0), k(0);
        while(k < mn) {
            result[k++] = matrix[i][j];
            //update boundary and go to next step
            switch(state) {
                case 0:
                    if(j < right) j++; // move right
                    else { state = 1; i++; top++; } //start to move down
                    break;
                case 1:
                    if(i < bottom) i++; // move down
                    else { state = 2; j--; right--; } //start to move left
                    break;
                case 2:
                    if(j > left) j--; //move left
                    else { state = 3; i--; bottom--; } //start to move up
                    break;
                case 3:
                    if(i > top) i--; //move up
                    else { state = 0; j++; left++; } //start to move right 
                    break;
                default:
                    break;
            }
        }
        return result;
    }
    int top, bottom, left, right, state;
};

/**************************************************** 
 ***    055,Medium,Jump Game 
 ****************************************************/

/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false. 
*/

/* Solution 1. Maintain a variable (step) for the maximum steps at each position. Scan forward, say the maximum step at position i is step, then we move one step further, the maximum step can be either step-1 (because we moved one step forward), or the maximum step at i+1. Thus
step = max(step-1, nums[i]);
If step = 0, then cannot jump.
*/

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return true;
        if(nums[0] == 0) return false;
        int step = nums[0];
        for(int i = 1; i < n-1; ++i) {
            step = max(step-1, nums[i]);
            if(step <= 0) return false;
        }
        return true;
    }
};

/*
Solution 2. Similar to Solution 1, but Keep a variable (rightEnd) for the maximum reachable index at each position. Scan forward, if the current position is beyond the rightEnd, then cannot jump. If rightEnd exceeds n-1, then can jump.
*/
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return true;
        int rightEnd = 0, i = 0;
        for(int i = 0; i <= rightEnd; i++) {
            rightEnd = max(rightEnd, i + nums[i]);
            if(rightEnd >= n-1) return true;
        }
        return false;
    }
};

/*
Solution 3. Standard BFS, each step, maintain a range [lo, hi] reachable from beginning, then scan all elements in the range, and calculate the newly reachable range as [hi+1, max( nums[i]+i) for all i between lo and hi]. If hi is not increased in the newly range, then cannot jump.
*/
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return true;
        int lo = 0, hi = 0;
        while(hi < n-1) {
           int tmp = hi;
           for(int i = lo; i <= tmp; ++i) {
               hi = max(hi, i+nums[i]);
           }
           if(hi == tmp) return false;
           lo = tmp+1;
        }
        return true;
    }
};

/*
Solution 4. Start from right and scan to left. Find first element reachable to end, and make that element the new end.
e.g. [4 3 4 1 0 2]
search starts from 0, and found 4 reachable to end. Then problem reduces to the [4 3 4] subarray.
*/

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return true;
        int i = n-1, j = 0;
        while(i > 0) {
           j = i-1;
           while(j >= 0 && nums[j] < i-j) { //find first element that can reach to nums[i]
              j--;
           }
           if(j == -1) return false; //not found
           i = j;
        }
        return true;
    }
};

/**************************************************** 
 ***    059,Medium,Spiral Matrix II 
 ****************************************************/

/*
Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

For example,
Given n = 3,

You should return the following matrix:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
*/

// same idea as 54. spiral matrix 

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int> > result;
        if(n == 0) return result;
        top = 0; bottom = n-1; left = 0; right = n-1;
        state = 0;
        result.resize(n, vector<int>(n, 0));
        int i(0), j(0), k(1), nn(n*n);
        while(k <= nn) {
            result[i][j] = k++;
            //update boundary and go to next step
            switch(state) {
                case 0:
                    if(j < right) j++; // move right
                    else { state = 1; i++; top++; } //start to move down
                    break;
                case 1:
                    if(i < bottom) i++; // move down
                    else { state = 2; j--; right--; } //start to move left
                    break;
                case 2:
                    if(j > left) j--; //move left
                    else { state = 3; i--; bottom--; } //start to move up
                    break;
                case 3:
                    if(i > top) i--; //move up
                    else { state = 0; j++; left++; } //start to move right 
                    break;
                default:
                    break;
            }
        }
        return result;
    }
    int top, bottom, left, right, state;
};

/**************************************************** 
 ***    060,Medium,Permutation Sequence 
 ****************************************************/

/*
The set [1,2,3,…,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):

    "123"
    "132"
    "213"
    "231"
    "312"
    "321"

Given n and k, return the kth permutation sequence.

Note: Given n will be between 1 and 9 inclusive.
*/

/* Solution using modular relation to determine the most significant digit and moving downward. This solution does not print the numbers in lexigraphical order.
 Maintain an array storing whether a particular digit has been used or not (e.g. used[2] denotes char '3'). Use a helper function to find the K-th unused character.
 k-- to make k start from 0
 e.g. n = 4
 1... (3!)  k = 0 - 5 (k / 3! = 0)
 2... (3!)  k = 6 - 11 (k / 3! = 1)
 3... (3!)  k = 12 - 17 (k / 3! = 2)
 4... (3!)  k = 18 - 23 (k / 3! = 3)
Caveats: the next permutation algorithm does not pass here due to TLE: has to move forward one step at a time!
*/

class Solution {
public:
    string getPermutation(int n, int k) {
        int fact = 1;
        for(int i = 1; i <= n; ++i) fact *= i;
        k = (k-1) % fact;
        vector<int> used(n, false);
        string result(n, '0');
        for(int i = 0; i < n; ++i) { //from MSD to LSD
            fact = fact / (n-i);
            int j = k / fact;
            int idx = findUnused(used, j);
            used[idx] = true;
            result[i] = idx + '1';
            k %= fact;
        }
        return result;
    }

    int findUnused(const vector<int>& used, int i) {
        for(int j = 0; j < used.size(); ++j) {
            if(!used[j]) {
                if(i-- == 0) return j;
            }
        }
        return -1;
    }
};

/*
Solution 2 using a bit status number.
Caveat:
 When testring if a digit is unset, use
 !(x & (1 << n)). not ~ , because inverting boolean and inverting bit number are totally different things!
 ! 1 = !(true) = false
 ~ 1 = -2 = true!
*/

class Solution {
public:
    string getPermutation(int n, int k) {
        int fact = 1;
        for(int i = 1; i <= n; ++i) fact *= i;
        k = (k-1) % fact;
        int state = 0; //used state: digit i means whether k+1 has been used
        string result(n, '0');
        for(int i = 0; i < n; ++i) { //from MSD to LSD
            fact = fact / (n-i);
            int j = k / fact;
            int idx = findUnused(state, j);
            state |= (1 << idx);
            result[i] = idx + '1';
            k %= fact;
        }
        return result;
    }

    int findUnused(int state, int i) {
        for(int j = 0; j < 32; ++j) {
            if(!(state & (1 << j))) {
                if(i-- == 0) return j;
            }
        }
        return 32;
    }
};

// Solution 3 using a string storing unused characters, when a character is used, remove the character
// Notice the usage of two STL functions: iota and string::erase

class Solution {
public:
    string getPermutation(int n, int k) {
        string dict(n, '0');
        iota(dict.begin(), dict.end(), '1'); // dict = '1234...n'
        int fact = 1;
        for(int i = 1; i <= n; ++i) fact *= i;
        k = (k-1) % fact;
        string result(n, '0');
        for(int i = 0; i < n; ++i) { //from MSD to LSD
            fact = fact / (n-i);
            int j = k / fact;
            result[i] = dict[j];
            dict.erase(j, 1); //erase j-th character
            k %= fact;
        }
        return result;
    }
};



/**************************************************** 
 ***    061,Medium,Rotate List 
 ****************************************************/

/*
Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// 1. Find the length of list, and the tail node
// 2. reduce k, if k % l == 0, then do nothing
// 3. find the new tail by calculating the residue
// 4. patch the two sub-lists

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == NULL || head->next == NULL) return head;
        if (k == 0) return head;
        
        ListNode *p = head, *tail(NULL);
        int l = 0; 
        //find length of list and tail
        while (p) {
            if(p->next == NULL) tail = p;
            p = p->next; l++;
        }
        if (k % l == 0) return head; //no rotation required
        //scan and stop at the new tail
        int cnt = l - k % l;
        p = head;
        while (cnt > 1) { // it is not > 0!
            p = p->next; cnt--;
        }
        ListNode *q = p->next; //q is the new head
        p->next = NULL; //p is new tail
        tail->next = head; //glue to segments together
        return q;
    }
};

/**************************************************** 
 ***    062,Medium,Unique Paths 
 ****************************************************/

/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

Above is a 3 x 7 grid. How many possible unique paths are there? 

Note: m and n will be at most 100.
*/

/// Dynamic programming, space O(m*n). Can further optimize space usage to O(n).
/// First initialize all entries to 1 (cells at top, left sides have only 1 path). then start from 1 to end for DP construction.
class Solution {
public:
    int uniquePaths(int m, int n) {
        //table[i][j]: number of paths from board[0][0] to boad[i][j], i < m; j < n;
        vector<vector<int> > table(m, vector<int>(n, 1));
        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j)
                table[i][j] = table[i-1][j] + table[i][j-1];

        return table[m-1][n-1];
    }
};

/// Space optimized solution, O(n) space using only one array
class Solution {
public:
    int uniquePaths(int m, int n) {
        //table[j]: number of paths from board[0][0] to boad[i][j], i < m; j < n;
        vector<int> table(n, 1);
        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j)
                table[j] += table[j-1];

        return table[n-1];
    }
};


/**************************************************** 
 ***    063,Medium,Unique Paths II 
 ****************************************************/

/*
Follow up for "Unique Paths":

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

For example,


There is one obstacle in the middle of a 3x3 grid as illustrated below.
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]


The total number of unique paths is 2.

Note: m and n will be at most 100.
*/

/// Dynamic programming O(m*n) space solution.
/// Only one nested loop. If site has obsticle, then its dp value is immediately set as zero.

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        //table[i][j]: number of paths from board[0][0] to boad[i][j], i < m; j < n;
        vector<vector<int> > table(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(obstacleGrid[i][j] == 1) table[i][j] = 0; //has obstacle, 0 paths
                else if (i == 0 && j == 0) table[i][j] = 1; //top left corner
                else if (i == 0) table[i][j] = table[i][j-1]; // top side boundary
                else if (j == 0) table[i][j] = table[i-1][j]; // left side boundary
                else table[i][j] = table[i-1][j] + table[i][j-1]; //interior cells
            }
        }
        return table[m-1][n-1];
    }
};

/// Space optimized DP solution, O(n) space with only one 1D array
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        //table[j]: number of paths from board[0][0] to boad[i][j], i < m; j < n;
        vector<int> table(n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(obstacleGrid[i][j] == 1) table[j] = 0; //has obstacle, 0 paths
                else if (i == 0 && j == 0) table[j] = 1; //top left corner
                else if (i == 0) table[j] = table[j-1]; // top side boundary
                else if (j == 0) ; //table[j] = table[j]; // left side boundary
                else table[j] += table[j-1]; //interior cells
            }
        }
        return table[n-1];
    }
};

/**************************************************** 
 ***    064,Medium,Minimum Path Sum 
 ****************************************************/

/*
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.
*/

// Solution 1. Dynamic programming.

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        vector<vector<int> > dp(m, vector<int>(n, 0));
        dp[0][0] = grid[0][0];
        for(int i = 1; i < m; ++i) dp[i][0] = dp[i-1][0] + grid[i][0];
        for(int j = 1; j < n; ++j) dp[0][j] = dp[0][j-1] + grid[0][j];
        for(int i = 1; i < m; ++i) {
            for(int j = 1; j < n; ++j) {
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }
        return dp[m-1][n-1];
    }
};

// Solution 2. Dynamic programming, space-optimized version.
// Be aware of initial values of the 1D array!

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> sum(n, INT_MAX);
        sum[0] = 0;
        for (int i = 0; i < m; ++i) {
            sum[0] += grid[i][0];
            for (int j = 1; j < n; ++j)
                sum[j] = min(sum[j-1], sum[j]) + grid[i][j];
        }
        return sum[n-1];
    }
};

/**************************************************** 
 ***    069,Medium,Sqrt(x) 
 ****************************************************/

/*
Implement int sqrt(int x).

Compute and return the square root of x.
*/

/// Binary search. Loop invariant:
/// [1 .. lo-1]: < sqrt(x)
/// [lo .. hi]: to be checked
/// [hi+1, x]: > sqrt(x)
/// Need to take care of possible overflow (mid > INT_MAX / mid)

class Solution {
public:
    int mySqrt(int x) {
        if (x <= 0) return 0;
        int lo = 1, hi = x, mid = 0;
        while(lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (mid > INT_MAX / mid) hi = mid - 1;
            else {
                int v = mid * mid;
                if (v < x) lo = mid + 1;
                else if (v > x) hi = mid - 1;
                else return mid;
            }
        }
        return hi;
    }
};

// Another solution using long to avoid overflow
class Solution {
public:
    int mySqrt(int x) {
       if(x <= 0) return 0;
       if(x == 1) return 1;
       long xx = x;
       int lo = 1, hi = x-1;
       //(lo-1)*(lo-1) <= x, (hi+1)*(hi+1) > x, hi*hi
       while(lo <= hi) {
           long mid = lo + (hi-lo)/2;
           long val = mid*mid;
           if(val == x) return mid;
           else if(val < x) lo = mid+1;
           else hi = mid-1;
       }
       return hi;
    }
};

// Solution 3. Newton's iteration
// For given x, solve f(y) = y*y - x = 0
// Then y_(n+1) = y_n - f(y)'/f(y) = 0.5*(y_n + x/y_n)
// exit when converges (two consecutive y's differ by some amount)

class Solution {
public:
    int mySqrt(int x) {
        if(x <= 0) return 0;
        double y = x, yold = 0;
        while(fabs(y-yold) > 0.1) {
            yold = y;
            y = 0.5*(y + x/y);
        }
        return y;
    }
};

/**************************************************** 
 ***    071,Medium,Simplify Path 
 ****************************************************/

/*
Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"

click to show corner cases.
Corner Cases:

    Did you consider the case where path = "/../"?
    In this case, you should return "/".
    Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
    In this case, you should ignore redundant slashes and return "/home/foo".
*/

// use a double-ended queue, break the string into tokens, 
// when see a '.', do nothing
// when see a "..", pop back element from queue (if not empty)
// when see a normal word, push to back of queue
// Then process queue and construct return string
// if queue is empty, then return "/".

class Solution {
public:
    string simplifyPath(string path) {
        string result;
        if(path == "") return result;
        int n = path.size();
        deque<string> s;
        int i = 0;
        while(i < n) {
            if(path[i] == '/') { i++; continue; }
            //find string
            int j = i+1;
            while(j < n && path[j] != '/') j++;
            //[i, j) is the string
            string tmp = path.substr(i, j-i);
            if(tmp == "..") {
                if(!s.empty()) s.pop_back();
            } else if(tmp == ".") ;
            else s.push_back(tmp);
            i = j+1;
        }
        if(s.empty()) return "/";
        while(!s.empty()) {
            result += "/" + s.front();
            s.pop_front();
        }
        return result;
    }
};


/**************************************************** 
 ***    073,Medium,Set Matrix Zeroes 
 ****************************************************/

/*
Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.

click to show follow up.

Follow up:
Did you use extra space?
A straight forward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?
*/

/// Solution 1. O(MN) time, O(1) space Algorithm
/// scan from top to bottom, and each row from right to left
/// use a boolean to track if current row contains any zeroes, and another to track if previous row contails any zeroes. 
/// (a) If see an zero at (i, j), then set all elements above it to zero (only if the element directly above it is not zero), 
/// also label current row's boolean as true(contains one zero). 
/// (b) If see an element that is non-zero, check if the element above it is zero, if yes, then set this element as zero as well
/// The tricky part is we need to set any rows containing an zero all to zero. If we do this after finishing scanning a row,
/// then when we move to next line, the newly added zeroes will disrupt step (b). To avoid this, we only set entire row after
/// we finish step (b) for the next row. In other words, after we finish scanning row i, we set entire row i-1 to zero if needed
/// thus we need two variables to track the status of current and previous rows.


class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if(m == 0) return;
        int n = matrix[0].size();
        if(n == 0) return;
       
        //whether last row, and current row has zero?
        bool last = false, curr = false;
        
        for(int i = 0; i < m; ++i) { //row
            
            for(int j = 0; j < n; ++j) { //column
                if(matrix[i][j] == 0) {
                    curr = true;
                    if(i > 0 && matrix[i-1][j] != 0) setColAbove(matrix, i, j);
                } else if(i > 0 && matrix[i-1][j] == 0) {
                    matrix[i][j] = 0; //set to zero
                }
            }
            
            //there is zero in the last line, set that row to zero
            if(last) setRow(matrix, i-1);
            
            last = curr;
            curr = false;
        }
        //don't forget the last row!
        if(last) setRow(matrix, m-1);
    }
    //set row i all to zero
    void setRow(vector<vector<int>>& matrix, int i) {
        for(int k = 0; k < matrix[i].size(); ++k) 
            matrix[i][k] = 0;
    }
    //set elements above row i, and at col j to zero
    void setColAbove(vector<vector<int>>& matrix, int i, int j) {
        for(int k = 0; k < i; ++k) 
            matrix[k][j] = 0;
    }
};

/// Solution 2. Similar to solution 1, less optimized. At first row, search below and see if there is a zero there, if yes, mark the 
/// element in the first row as zero.
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return;
        int m = matrix.size(), n = matrix[0].size();
        bool hasZeroCurr(false), hasZeroLast(false);
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(matrix[i][j] == 0) hasZeroCurr = true;
                else if(i == 0) {
                    //search below
                    for(int k = i+1; k < m; k++)
                        if(matrix[k][j] == 0) { matrix[i][j] = 0; break;}
                } else if(matrix[i-1][j] == 0) matrix[i][j] = 0; //set element in this row to 0
            }
            //set last row as zero
            if(hasZeroLast) setRow(matrix, i-1);
            
            hasZeroLast = hasZeroCurr; //update
            hasZeroCurr = false; //reset
        }
        if(hasZeroLast) setRow(matrix, m-1);
    }
    void setRow(vector<vector<int>>& matrix, int ir) {
        int n = matrix[0].size();
        for(int j = 0; j < n; j++)
            matrix[ir][j] = 0;
    }
};

/// Solution 3. 
/// Two pass O(MN) time, O(m+n) space algorithm
/// Use two arrays to track if a given row/column has zero

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(); 
        if(m == 0) return; 
        int n = matrix[0].size(); 
        if(n == 0) return; 
        
        vector<bool> rows(m, false);
        vector<bool> cols(n, false);
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(matrix[i][j] == 0) rows[i] = cols[j] = true;
            }
        }
        
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(rows[i] || cols[j]) matrix[i][j] = 0;
            }
        }
    }
};


/**************************************************** 
 ***    074,Medium,Search a 2D Matrix 
 ****************************************************/

/*
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

    Integers in each row are sorted from left to right.
    The first integer of each row is greater than the last integer of the previous row.

For example,

Consider the following matrix:

[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]

Given target = 3, return true.
*/

//binary search. Convert 1D index to 2D index

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if (m == 0) return false;
        int n = matrix[0].size();
        if (n == 0) return false;
        int lo = 0, hi = m*n-1, mid = 0;
        // invariant:
        // [0 .. lo-1] < target
        // [lo .. hi] to be checked
        // [hi+1 .. m*n-1] > target
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            int v = matrix[mid/n][mid%n];
            if (v < target) lo = mid + 1;
            else if (v > target) hi = mid - 1;
            else return true;
        }
        return false;
    }
};

/**************************************************** 
 ***    075,Medium,Sort Colors 
 ****************************************************/

/*
Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue. 

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively. 

Note:
 You are not suppose to use the library's sort function for this problem. 

click to show follow up.


Follow up:
 A rather straight forward solution is a two-pass algorithm using counting sort.
 First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?
*/

// Dutch national flag problem

class Solution {
public:
    void sortColors(vector<int>& nums) {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        // [0 .. lo-1] == 0, [lo, mid-1] == 1, [mid, hi] TBD, [hi+1, n-1] == 2 
        int lo = 0, mid = 0, hi = n-1;
        while(mid <= hi) {
            int x = nums[mid];
            if(x == 0) swap(nums[mid++], nums[lo++]);
            else if(x == 1) mid++;
            else swap(nums[mid], nums[hi--]);
        }
    }
};


/**************************************************** 
 ***    077,Medium,Combinations 
 ****************************************************/

/*
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
*/

// Solution 1. Recursive solution. Start with k trials, every time decrement trials. Stop recursion when there is no trials left (k == 0). (12ms)
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int> > result;
        if(k > n || n <= 0) return result;
        vector<int> tmp(k, 0);
        dfs(1, n, k, tmp, result);
        return result;
    }
    //k trials left, start from number i, maximum is n
    void dfs(int i, int n, int k, vector<int>& tmp, vector<vector<int> >& result) {
        if(k == 0) {
            result.push_back(tmp);
            return;
        }
        if(i > n) return; //no numbers available
        int size = tmp.size();
        for(int j = i; j <= n; ++j) { //choose number between i and n
            tmp[size-k] = j; //choose number j
            dfs(j+1, n, k-1, tmp, result); //dfs starting with j+1
        }
    }
};

// Solution 2. Optimized recursive solution. Stop recursion after making the decision for the last trial (k == 1), also avoid uncessary trial when i > n.
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int> > result;
        if(k > n || n <= 0) return result;
        vector<int> tmp(k, 0);
        dfs(1, n, k, tmp, result);
        return result;
    }
    //k trials left, start from number i, maximum is n
    void dfs(int i, int n, int k, vector<int>& tmp, vector<vector<int> >& result) {
        int size = tmp.size();
        for(int j = i; j <= n; ++j) { //choose number between i and n
            tmp[size-k] = j; //choose number j
            if(k == 1) result.push_back(tmp); //reaching the end
            else if(j < n) dfs(j+1, n, k-1, tmp, result); //dfs starting with j+1
        }
    }
};	

// Solution 3. Iterative. Save results at i == k. (16ms)
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int> > result;
        if(k > n || n <= 0) return result;
        vector<int> tmp(k, 0);
        int i = 0; 
        while(i >= 0) { //the i-th choice ( 0 <= i < k)
            if(i == k) { 
                result.push_back(tmp); 
                i--; //backtrace!
                continue; 
            }
            tmp[i]++; //choose the next number
            if(tmp[i] > n) { i--; continue; } //back trace
            i++; //go to next step
            if(i < k) tmp[i] = tmp[i-1]; //choose right starting point for the next tmp[i]++
        }
        return result;
    }
};

// Solution 3. Iterative, optmized and simpler. Save results at i == k-1. (8ms)
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int> > result;
        if(k > n || n <= 0) return result;
        vector<int> tmp(k, 0);
        int i = 0; 
        while(i >= 0) { //the i-th choice ( 0 <= i < k)
            tmp[i]++; //choose the next number
            if(tmp[i] > n) i--; //back trace
            else if (i == k-1) result.push_back(tmp);
            else {
                i++; //go to next step
                tmp[i] = tmp[i-1]; //choose right starting point for the next tmp[i]++
            }
        }
        return result;
    }
};


/**************************************************** 
 ***    078,Medium,Subsets 
 ****************************************************/

/*
Given a set of distinct integers, nums, return all possible subsets.

Note:

    Elements in a subset must be in non-descending order.
    The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
*/

// Solution 1. Recursive backtracking using DFS. Fan-out is 2 (for each number, add or not add).

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int> > result;
        sort(nums.begin(), nums.end());
        vector<int> tmp;
        dfs(nums, 0, tmp, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result) {
        if(i == nums.size()) {
            result.push_back(tmp);
            return;
        }
        // not taking nums[i]
        dfs(nums, i+1, tmp, result);
        // taking nums[i]
        tmp.push_back(nums[i]);
        dfs(nums, i+1, tmp, result);
        tmp.pop_back(); //revert
    }
};

// Solution 2. Recursive backtracking using DFS. Fan-out is number of unused elements, less tree depth and thus better efficiency than 1.

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int> > result;
        vector<int> tmp;
        sort(nums.begin(), nums.end());
        dfs(nums, 0, tmp, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result) {
        result.push_back(tmp);
        for(int j = i; j < nums.size(); ++j) { //choose one from unused numbers
            tmp.push_back(nums[j]);
            dfs(nums, j+1, tmp, result);
            tmp.pop_back();
        }
    }
};

// Solution 3. Dynamic programming. For each number, add to previous solution.
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int> > result;
        sort(nums.begin(), nums.end());
        result.push_back(vector<int>()); //empty set
        for(int i = 0; i < nums.size(); ++i) {
            //add nums[i] to all previous solutions
            int size = result.size();
            for(int j = 0; j < size; ++j) {
                result.push_back(result[j]);
                result.back().push_back(nums[i]);
            }
        }
        return result;
    }
};

// Solution 4. Use bit operation. There are pow(2, n) results, we can label them in a consistent order similar to Solution 3.
// for example [1,2,3]:
// subset:       [], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]
// id(base 10):  0    1    2      3     4     5       6         7
// id(base 2):  000  001  010    011   100   101     110       111
// As we can see, number 1 (the 0-th number) only appears when last digit is set. number 2 (the 1st number) only appears when second from last digit is set, and so on. Thus, for each id, we can check which digit are set, and add the corresponding number to the subset.
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        int size = 1 << n;
        sort(nums.begin(), nums.end());
        vector<vector<int> > result(size, vector<int>());
        for(int i = 0; i < result.size(); ++i) {
            for(int j = 0; j < n; ++j) {
                if(i & (1 << j)) result[i].push_back(nums[j]);
            }
        }
        return result;
    }
};


/**************************************************** 
 ***    079,Medium,Word Search 
 ****************************************************/

/*
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]

word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
*/

/* 
Recursive solution using DFS
Several optimizations:
1. Do not use another array to store the visited status of the board. Instead, set the visited board character as '*', and set it back to original at retrace stage.
2. For checking validity of new positions, leave it to the recursive function (if not legal simply return false). If do something like this, will lead to TLE.

        if(i > 0 && board[i-1][j] != '*' && existHelper(board, i-1, j, word, k+1)) return true;
        if(i < m-1 && board[i+1][j] != '*' && existHelper(board, i+1, j, word, k+1)) return true;
        if(j > 0 && board[i][j-1] != '*' && existHelper(board, i, j-1, word, k+1)) return true;
        if(j < n-1 && board[i][j+1] != '*' && existHelper(board, i, j+1, word, k+1)) return true;

*/

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if(board.empty() || board[0].empty()) return false;
        int m = board.size(), n = board[0].size();
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(dfs(board, i, j, word, 0)) return true;
            }
        }
        return false;
    }
    //check whether board[i][j] matches with word[k] and continue searching
    bool dfs(vector<vector<char> >& board, int i, int j, const string& word, int k) {
        if(k == word.size()) return true;
        int m = board.size(), n = board[0].size();
        if(i < 0 || j < 0 || i >= m || j >= n) return false;
        if(board[i][j] != word[k]) return false;
        char c = board[i][j];
        board[i][j] = '*'; //mark as visited
        if(dfs(board, i-1, j, word, k+1)) return true;
        if(dfs(board, i, j-1, word, k+1)) return true;
        if(dfs(board, i+1, j, word, k+1)) return true;
        if(dfs(board, i, j+1, word, k+1)) return true;
        board[i][j] = c; //retrace
        return false;
    }
};

// An old iterative solution
class Solution {
public:
	//move from current position (row,col) to next position
	void move(int &row, int &col, int dir) {
		if(dir == 1) col += 1; //right
		else if(dir == 2) row -= 1; //up
		else if(dir == 3) col -= 1; //left
		else if(dir == 4) row += 1; //down
		else row = col = -1; //not move
	}
	//check if position (row, col) exceeds boundary
	bool isValid(int row, int col, int m, int n) {
		return(row >= 0 && row < m && col >= 0 && col < n);
	}
	bool exist(vector<vector<char> > &board, string word) {
		int m = board.size();
		int n = board[0].size();
		int tot = m*n;
		int len = word.size();
		int k = 0; //k-th character in word
		vector<int> dir(len, 1);  //directions at step k
		vector<int> row(len, -1); //row number at step k
		vector<int> col(len, -1); //column number at step k
		vector<vector<bool> > visited(m, vector<bool>(n, false));//site visited? 
		
		for(int l = 0; l < tot; ++l) { //loop thru all elements in the board
			//invariant: k characters matched (now matching word[k] with position[k] determined from position[k-1] and dir[k-1])
			k = 0; //reset k everytime!
			while(1) {
			    if(k == len) return true; //already found!
			    if(k > 0 && dir[k-1] > 4) { //tried all directions, retrace
			    	dir[k-1] = 1; //reset to first direction
			    	visited[row[k-1]][col[k-1]] = false; //reset
				    row[k-1] = col[k-1] = -1;
				    k--;
				    if(k == 0) break; //breaking condition
				    dir[k-1] ++; //last one should increment
				    continue;
				}
			    //find next position
			    int nextRow = row[k-1], nextCol = col[k-1];
			    if(k == 0) { nextRow = l/n; nextCol = l%n; }
			    else move(nextRow, nextCol, dir[k-1]);
			    
			    //check match?
			    if(k == 0) { //first character special case
				    if(board[nextRow][nextCol] != word[k]) break; 
				    else { //matched first character
				        row[k] = nextRow; col[k] = nextCol;
				        visited[row[k]][col[k]] = true;
				        k++; //try next one
				    }
				} else if(!isValid(nextRow, nextCol, m, n) || board[nextRow][nextCol] != word[k] || visited[nextRow][nextCol]) { //no match
    				dir[k-1] ++;
				} else { //found match
		    	    row[k] = nextRow; col[k] = nextCol;
			        visited[row[k]][col[k]] = true; //update visited
			        k++;
				}
			}
		}
		return false;
	}
};



/**************************************************** 
 ***    080,Medium,Remove Duplicates from Sorted Array II 
 ****************************************************/

/*
Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new length. 
*/

// Solution: two pointers. 
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return n;
        int len = 0;
        int i = 0, j = 0;
        while(i < n) {
            j = i+1;
            while(j < n && nums[j] == nums[i]) j++;
            if(j >= i+1) nums[len++] = nums[i];
            if(j > i+1) nums[len++] = nums[i];
            i = j;
        }
        return len;
    }
};

// A old solution
class Solution {
public:
    int removeDuplicates(int A[], int n) {
        if(n == 0) return 0;
   		int i(0), j(1), prev = INT_MAX, count = 0;
		for(j = 0; j < n; ++j) {
		    if(A[j] == prev) count++;
		    else count = 1;
		    prev = A[j];
		    if(count <= 2) A[i++] = A[j]; 
		}
		return i;   
    }
};

/**************************************************** 
 ***    081,Medium,Search in Rotated Sorted Array II 
 ****************************************************/

/*
Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?

Write a function to determine if a given target is in the array.
*/

/*
Binary search. The array can be broken into two part, first part is 4-7, second part is 0-2. If array is unrotated,
then only first part exists (corner case). 
There are three anchor points, lo, hi, and mid.
First determine whether mid is in first half or second half. Due to duplicated items, we now has three cases:
1. mid is in first half iff nums[mid] > nums[lo] 
2. mid is in second half iff nums[mid] < nums[lo]
3. if nums[mid] == nums[lo], we can't say for sure which part mid belongs to, but we know that nums[lo] is not target, 
so we simply increment lo. 
Examples for 3. 
 2 2 2 2 3 2 2
lo    mid   hi  (mid is in first half)
 2 2 3 2 2 2 2
lo    mid   hi  (mid is in second half)

1. If mid is in first half, we know that nums[mid] >= nums[lo] (could be equal because mid can be lo, when hi = lo+1), 
if target falls between the two, then the index has to be between lo and mid. Otherwise, it is between mid and hi.
2. If mid is in second half, we know that nums[mid] <= nums[hi] (could be equal because mid can be hi, when hi = lo), 
if target falls between the two, then the index has to be between mid and hi. Otherwise, it is between lo and mid.
*/

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        int lo(0), hi(n-1);
        while(lo <= hi) {
            int mid = lo + (hi-lo) / 2;
            if(target == nums[mid]) return true;
            if (nums[mid] > nums[lo]) {
                if(target >= nums[lo] && target < nums[mid]) hi = mid -1;
                else lo = mid + 1;
            } else if (nums[mid] < nums[lo]) {
                if(target <= nums[hi] && target > nums[mid]) lo = mid + 1;
                else hi = mid - 1;
            } else {
                lo++;
            }
        }
        return false;
    }
};

/**************************************************** 
 ***    082,Medium,Remove Duplicates from Sorted List II 
 ****************************************************/

/*
Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// use two pointers. Also dummy head, because head might be deleted.

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;

        ListNode *p = dummy, *q = p->next;
        //p is tail of processed list, q is its next, r is one node past the last duplicated entry.
        while(q) {
            ListNode* r = q->next;
            while(r && r->val == q->val) r = r->next;
            //r is either null or first entry not equal to q
            if(r == q->next) { //no duplicated entry
                p = q;
                q = r; //just move forward
                continue;
            }
            //then delete everything from q to r's ancestor
            while(q != r) {
                ListNode * t = q;
                delete t;
                q = q->next;
            }
            //after loop q == r
            p->next = q;
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};

/**************************************************** 
 ***    086,Medium,Partition List 
 ****************************************************/

/*
Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// No dummy heads, two sub-lists for < x and >= x
// when finish, patch two lists together, and remember to set list tail's next pointer to NULL!

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if(!head || !head->next) return head;
        //p1 .. q1 < x, p2 .. q2 >= x
        ListNode *p1(NULL), *q1(NULL), *p2(NULL), *q2(NULL);
        ListNode *curr = head;
        while(curr) {
            if(curr->val < x) {
                if(!p1) p1 = q1 = curr; //first one
                else q1 = q1->next = curr; 
            } else {
                if(!p2) p2 = q2 = curr; //first one
                else q2 = q2->next = curr; 
            }
            curr = curr->next;
        }
        if(q1) q1->next = p2; //connect the two
        if(q2) q2->next = NULL; //set tail to NULL!
        return p1 ? p1 : p2;
    }
};

/**************************************************** 
 ***    089,Medium,Gray Code 
 ****************************************************/

/*
The gray code is a binary numeral system where two successive values differ in only one bit.
Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.
For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:
00 - 0
01 - 1
11 - 3
10 - 2
Note:
For a given n, a gray code sequence is not uniquely defined.
For example, [0,2,3,1] is also a valid gray code sequence according to the above definition.
For now, the judge is able to judge based on one instance of gray code sequence. Sorry about that.
*/

// Dynamic programming, start from 1, expand to n:
// 1: (0 1)
// 2: (0 1, 2+1 2+0) = (0 1 3 2)
// 3: (0 1 3 2, 4+2 4+3 4+1 4+0) = (0 1 3 2 6 7 5 4)
// One array is enough (no need to use another array to store temporary results
// Be careful of corner case n = 0 (somehow should return [0])

class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> res;
        if (n == 0) return vector<int>(1, 0);
        res.resize(2, 0);
        res[1] = 1;
        for (int i = 1; i < n; ++i) {
            int size = res.size();
            res.resize(size*2);
            for(int j = 0; j < size; ++j) {
               res[j+size] = (1 << i) + res[size-1-j];
            }
        }
        return res;
    }
};

// Solution 2 using one single loop
class Solution {
public:
   vector<int> grayCode(int n) {
        if(n < 0) return vector<int>();
        vector<int> result(1 << n, 0); //pow(2, n)
        for(int j = 1, size = 1; j < result.size(); ++j) {
            if(j == size)  size <<= 1;
            result[j] = result[size-j-1] + (size >> 1);
        }
        return result;
    }
};

/**************************************************** 
 ***    090,Medium,Subsets II 
 ****************************************************/

/*
Given a collection of integers that might contain duplicates, nums, return all possible subsets.

Note:

    Elements in a subset must be in non-descending order.
    The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,2], a solution is:

[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
*/

// Solution 1. Similar to #78, DFS backtracking with fan-out = 2.
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int> > result;
        sort(nums.begin(), nums.end());
        vector<int> tmp;
        dfs(nums, 0, tmp, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result) {
        if(i == nums.size()) {
            result.push_back(tmp);
            return;
        }
        int j = i;
        while(j < nums.size() && nums[j] == nums[i]) j++;
        //j is index of first element != nums[i], or end
        //not adding nums[i] to set
        dfs(nums, j, tmp, result);
        //adding 1 to j-i nums[i] to set
        for(int k = 0; k < j-i; ++k) {
            tmp.push_back(nums[i]);
            dfs(nums, j, tmp, result);
        }
        //revert back
        for(int k = 0; k < j-i; ++k) {
            tmp.pop_back();
        }
    }
};

// Solution 2. Similar to #78, DFS backtracking with fan-out = number of unused elements
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int> > result;
        vector<int> tmp;
        sort(nums.begin(), nums.end());
        dfs(nums, 0, tmp, result);
        return result;
    }
    void dfs(vector<int>& nums, int i, vector<int>& tmp, vector<vector<int> >& result) {
        result.push_back(tmp);
        for(int j = i; j < nums.size(); ++j) {
            if(j == i || nums[j] != nums[j-1]) { //ignore duplicates
                tmp.push_back(nums[j]);
                dfs(nums, j+1, tmp, result);
                tmp.pop_back();
            }
        }
    }
};

// Solution 3. Similar to #78, dynamic programming.
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int> > result;
        sort(nums.begin(), nums.end());
        result.push_back(vector<int>()); //empty set
        int i = 0;
        int n = nums.size();
        while(i < n) {
            int j = i;
            while(j < n && nums[j] == nums[i]) j++;
            int ndup = j-i; //number of duplicates
            //add 1 - ndup nums[i] to existing solution
            int size = result.size();
            for(int k = 0; k < ndup; ++k) {
                for(int l = k*size; l < (k+1)*size; ++l) {
                    result.push_back(result[l]);
                    result.back().push_back(nums[i]);
                }
            }
            i = j;
        }
        return result;
    }
};


/**************************************************** 
 ***    091,Medium,Decode Ways 
 ****************************************************/

/*
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26

Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2. 
*/

// use two helper functions: 
// num(c): whether c itself is legal (1) or not (0)
// num(c1, c2): whether c1c2 together is legal (1) or not (0). e.g. 15 => 1, 56 => 0
// Dynamic programming, when checking s[i], see if we can form s[0..i-1] + s[i] or s[0..i-2] + s[i-1]s[i]
// Only use two variables storing last and lastlast, instead of a vector

class Solution {
public:
    int numDecodings(string s) {
        int val(0);
        int n = s.size();
        if (n == 0) return 0;
        if (n == 1) return num(s[0]);
        if (n == 2) return num(s[0])*num(s[1]) + num(s[0], s[1]);
        int lastlast = num(s[0]), last = num(s[0])*num(s[1]) + num(s[0], s[1]);
        for (int i = 2; i < n; ++i) {
            val = lastlast*num(s[i-1],s[i]) + last*num(s[i]);
            lastlast = last;
            last = val;
        }
        return val;
    }

    int num(char c) {
       return c == '0' ? 0 : 1;
    }
    int num(char c1, char c2) {
        if (c1 == '0') return 0;
        else if (c2 == '0') return (c1 == '1' || c1 == '2') ? 1 : 0;
        else {
            int v = 10*(c1-'0')+(c2-'0');
            return v <= 26 ? 1 : 0;
        }
    }
};

// Solution 2. Shorter one.
class Solution {
public:
    int numDecodings(string s) {
       if(s.empty()) return 0;
       int n = s.size();
       if(s[0] == '0') return 0;
       if(n == 1) return 1;
       int last_last = 1, last = 1, curr = 0;
       for(int i = 1; i < n; ++i) {
           int v1 = s[i] - '0';
           int v2 = (s[i-1] - '0')*10 + v1;
           curr = 0;
           if(v1 != 0) curr += last;
           if(v2 >= 10 && v2 <= 26) curr += last_last;
           last_last = last;
           last = curr;
       }
       return curr;
    }
};


/**************************************************** 
 ***    092,Medium,Reverse Linked List II 
 ****************************************************/

/* 
Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 ≤ m ≤ n ≤ length of list. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
// Use a counter k, one pass.
// 1. When reached (m-1)-th element, save the curr and next node as pa and pb:
// 2. when k between m and n-1, do reverse
// 3. when k = n, patch two segments together using pa and pb.
// Use a dummy head pointer
//  1 => .. => m-1 => m => ... => n => n+1 => ...
//              pa   pb           curr  next
//       ... => pa => curr => pb => next => ...

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if(head == NULL || head->next == NULL) return head;
        if(m == n) return head;

        ListNode dum(0), *p(&dum);
        p->next = head;
        ListNode *curr(p), *next(NULL);
        ListNode *pa(NULL), *pb(NULL);
        for (int k = 0; curr != NULL && k <= n; k++) {
            if (k < m-1)  curr = curr->next;
            else if (k == m-1)  {
                pa = curr;
                pb = curr->next;
                curr = curr->next;
                next = curr->next; //init next at this point
            }
            else if (k < n) { // do reverse: change curr->next to point to curr
                ListNode *nextnext = next->next;  //store in temp variable
                next->next = curr;
                curr = next;  //update curr
                next = nextnext; //update next
            } else if (k == n) { //connect two list segments
                pa->next = curr;
                pb->next = next;
            }
        }
        return p->next;
    }
};

/**************************************************** 
 ***    093,Medium,Restore IP Addresses 
 ****************************************************/

/*
Given a string containing only digits, restore it by returning all possible valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter) 
*/

// Recursive solution #1.
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> result;
        if(s.empty()) return result;
        string tmp;
        dfs(s, 0, 0, tmp, result);
        return result;
    }
    void dfs(const string& s, int i, int count, string tmp, vector<string>& result) {
        int n = s.size();
        if(i == n && count == 4) {
            result.push_back(tmp);
            return;
        }
        if(i == n || count == 4) return;
        if(i != 0) tmp += '.';
        if(s[i] == '0') {
            dfs(s, i+1, count+1, tmp+'0', result);
            return;
        }
        for(int k = i, val = 0; k < n; k++) {
            val = val*10 + (s[k] - '0');
            if(val >= 256) break;
            tmp += s[k];
            dfs(s, k+1, count+1, tmp, result);
        }
   }
};

// Recursive solution #2. 
// Need to add 4 periods, last one has to be after last character.
// store positions of periods (index of character right before newly added period), and reconstruct the string when valid solutions are found
// Caveat: string::insert function argument is the index which the new character is inserted before.
// Another caveat: ip address segments cannot have leading zeros, except .0. case, others like .03. or .00. are illegal. Need to filter them out

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> ret;
        vector<int> dotPos(4, -1); //dot positions in the s
        restore(s, 0, 0, dotPos, ret);
        return ret;
    }
    //checking substring starting at s[i] for dot number k (0-3), add values to dotPos
    void restore(const string& s, int i, int k, vector<int>& dotPos, vector<string>& ret) {
       if (k == 4) { //already placing 4 dots (one at the end)
          //onlyd add when i reaches the end
          if (i == s.size()) ret.push_back(construct(s, dotPos));
          return;
       }
       if (i == s.size()) return;
       int v = 0;
       for (int j = i; j < s.size(); ++j) {
          v = 10*v + s[j] - '0';
          if(v >= 256) break;
          dotPos[k] = j; //dot is after j's position
          restore(s, j+1, k+1, dotPos, ret);
          if(s[i] == '0') break; //if leading character is '0', do not continue loop ('.00.' is illegal IP segment)
       }
    }
    string construct(const string& s, const vector<int>& dotPos) {
        string ret = s;
        ret.insert(dotPos[2]+1, 1, '.');
        ret.insert(dotPos[1]+1, 1, '.');
        ret.insert(dotPos[0]+1, 1, '.');
        return ret;
    }

};


/**************************************************** 
 ***    094,Medium,Binary Tree Inorder Traversal 
 ****************************************************/

/*
Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution (easy).

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        if(!root) return ret;
        inorder(root, ret);
        return ret;
    }
    void inorder(TreeNode* root, vector<int>& ret) {
        if(!root) return;
        if(root->left) inorder(root->left, ret);
        ret.push_back(root->val);
        if(root->right) inorder(root->right, ret);
    }
};

// Iterative solution using a stack (and a tag indicating the number of times an element appears in stack).
// Slightly different version with modified control flow with tag.

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        deque<pair<TreeNode*, int> > st; //stack
        st.push_back(make_pair(root, 0));
        while(!st.empty()) {
            TreeNode *node = st.back().first;
            int tag = ++st.back().second;
            if(tag == 1) {
                if(node->left) st.push_back(make_pair(node->left, 0));
            } else {
                result.push_back(node->val);
                st.pop_back();
                if(node->right) st.push_back(make_pair(node->right, 0));
            }
        }
        return result;
    }
};

// Another iterative solution by pushing left spline in the stack
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        deque<TreeNode*> st; //stack
        while(root) {
            st.push_back(root);
            root = root->left;
        }
        while(!st.empty()) {
            TreeNode* node = st.back(); st.pop_back();
            result.push_back(node->val);
            node = node->right;
            while(node) {
                st.push_back(node);
                node = node->left;
            }
        }
        return result;
    }
};

// Another iterative solution using a stack and a pointer pointing to current node
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        stack<TreeNode*> s;
        TreeNode *curr = root;
        while(!s.empty() || curr) {
            if(curr) {
                s.push(curr);
                curr = curr->left;
            } else { //need to process curr
                curr = s.top(); s.pop();
                result.push_back(curr->val);
                curr = curr->right;
            }
        }
        return result;
    }
};

// Morris traversal O(n) without using a stack or recursive calls.
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        TreeNode *node = root;
        while(node) {
            if(!node->left) {
                result.push_back(node->val);
                node = node->right;
            } else {
                TreeNode *child = node->left;
                while(child->right != NULL && child->right != node) child = child->right;
                if(child->right == NULL) {
                    child->right = node; // first time, modify right pointer
                    node = node->left; //move to left child
                } else {
                    child->right = NULL; //second time, reset right pointer to NULL
                    result.push_back(node->val);
                    node = node->right;
                }
            }
        }
        return result;
    }
};

// Morris traversal with a slightly different while loop (visit node in the end of loop body)
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        TreeNode *node = root;
        while(node) {
            if(node->left) {  // has left subtree
                TreeNode *child = node->left;
                while(child->right != NULL && child->right != node) child = child->right;
                //reached right most child of left subtree
                if(child->right == NULL) { //first time
                    child->right = node;
                    node = node->left;
                    continue;
                } else { //second time
                   child->right = NULL; //second time
                }
            }
            //visit node
            result.push_back(node->val);
            node = node->right;
        }
        return result;
    }
};



/**************************************************** 
 ***    095,Medium,Unique Binary Search Trees II 
 ****************************************************/

/*
Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Dynamic programming using a 2D array. The trick is to generate the right subtree by using a createNew function with a delta value.

class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if(n < 0) return vector<TreeNode*>();
        if(n == 0) return vector<TreeNode*>();
        vector<vector<TreeNode*> > dp(n+1); //dp[i]: solutions for tree of size i
        dp[0].push_back(NULL);
        for(int i = 1; i <= n; ++i) { //check tree of size i
            for(int k = 1; k <= i; ++k) { //make k as root
                for(auto l : dp[k-1]) { //construct left subtree
                    for(auto r : dp[i-k]) { //construct right subtree
                        TreeNode *root = new TreeNode(k);
                        root->left = l;
                        root->right = createNew(r, k);
                        dp[i].push_back(root);
                    }
                }
            }
        }
        return dp[n];
    }
    TreeNode* createNew(TreeNode* root, int delta) {
        if(!root) return NULL;
        TreeNode* nr = new TreeNode(root->val+delta); //new root
        nr->left = createNew(root->left, delta);
        nr->right = createNew(root->right, delta);
        return nr;
    }
};


/**************************************************** 
 ***    096,Medium,Unique Binary Search Trees 
 ****************************************************/

/*
Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

*/

// Dynamic programming. The ways of forming tree of size n can be found by choosing each of the n elements as root, which divides the others as left and right subtrees.

class Solution {
public:
    int numTrees(int n) {
        if(n < 0) return 0;
        if(n == 0 || n == 1) return 1;
        vector<int> count(n+1, 0); //store counts from i=0 to n
        count[0] = count[1] = 1;
        //calculate number of unique trees of size i
        for(int i = 2; i <= n; ++i) {
            //pick k-th number as root, then k elements as left-tree, i-k-1 elements as right-tree
            for(int k = 0; k < i; ++k) {
                count[i] += count[k]*count[i-k-1];
            }
        }
        return count[n];
    }
};


/**************************************************** 
 ***    098,Medium,Validate Binary Search Tree 
 ****************************************************/

/*
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

    The left subtree of a node contains only nodes with keys less than the node's key.
    The right subtree of a node contains only nodes with keys greater than the node's key.
    Both the left and right subtrees must also be binary search trees.

confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution.
// store lower and upper bounds of each subtree, initially it is (-inf, inf)
// One corner case is when INT_MIN and INT_MAX is part of the value, so use LONG_MIN and LONG_MAX instead.

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return validate(root, LONG_MIN, LONG_MAX);
    }
    //make sure all tree values between (lo, hi)
    bool validate(TreeNode* root, long lo, long hi) {
        if(!root) return true;
        int x = root->val;
        if(x <= lo || x >= hi) return false;
        return validate(root->left, lo, x) && validate(root->right, x, hi);
    }
};

/**************************************************** 
 ***    103,Medium,Binary Tree Zigzag Level Order Traversal 
 ****************************************************/

/*
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree {3,9,20,#,#,15,7},

    3
   / \
  9  20
    /  \
   15   7

return its level order traversal as:

[
  [3],
  [9,20],
  [15,7]
]
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Be careful when using bit operator!! if(level & 1 == 0) is wrong!, 1 == 0 has higher priority, should use if (!(level&1)).

/// Using two stacks. Swap the two when exhausting one level. Use a level tag to track polarity, which determines whether left or right subtree gets pushed to stack first
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int> > ret;
        if(!root) return ret;
        deque<TreeNode*> current, next;
        int level = 0;
        current.push_back(root);
        ret.push_back(vector<int>());
        while(!current.empty() || !next.empty()) { //break when both current and next are empty
            if(current.empty()) { // when exhausing current level ...
                current.swap(next); //swap current and next
                ret.push_back(vector<int>());
                level ++;
            }
            TreeNode *node = current.back();  current.pop_back();
            if(level % 2 == 0) {
                if(node->left) next.push_back(node->left);
                if(node->right) next.push_back(node->right);
            } else {
                if(node->right) next.push_back(node->right);
                if(node->left) next.push_back(node->left);
            }
            ret[level].push_back(node->val);
        }
        return ret;
    }
};

// Solution with 2 stacks, and two loops
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int> > result;
        if(!root) return result;
        //stack for two levels
        vector<TreeNode*> current, next;
        int level = 0; //level and parity
        current.push_back(root);
        while(!current.empty()) {
            result.push_back(vector<int>()); //new level
            //user current as stack
            for(vector<TreeNode*>::reverse_iterator it = current.rbegin(); it != current.rend(); ++it) {
                TreeNode *node = *it;
                if(level % 2 == 0) { //l=>r
                    if(node->left) next.push_back(node->left);
                    if(node->right) next.push_back(node->right);
                } else {
                    if(node->right) next.push_back(node->right);
                    if(node->left) next.push_back(node->left);
                }
                //insert to result
                result[level].push_back(node->val);
            }
            current.swap(next);
            next.clear();
            level++;
        }
        return result;
    }
};

// An old solution using struct instead of pair
/// Using a queue, after constructed, reverse odd level elements's order

class Solution {
public:
    struct Element {
        TreeNode *node;
        int level;
        Element(TreeNode *n, int l) : node(n), level(l) {}
    };
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int> > ret;
        if(!root) return ret;
        deque<Element> q; //queue
        q.push_back(Element(root, 0));
        while(!q.empty()) {
            TreeNode *node = q.front().node;
            int level = q.front().level;
            q.pop_front();
            if(level == ret.size()) ret.push_back(vector<int>());
            ret[level].push_back(node->val);
            if(node->left) q.push_back(Element(node->left, level+1));
            if(node->right) q.push_back(Element(node->right, level+1));
        }
        for(size_t i = 1; i < ret.size(); i += 2) {
            reverse(ret[i].begin(), ret[i].end());
        }
        return ret;
    }
};

/**************************************************** 
 ***    105,Medium,Construct Binary Tree from Preorder and Inorder Traversal 
 ****************************************************/

/*
Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree. 
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution. Use start and length of subarray as parameter
/// pre: [  X  [ left ] [ right ] ] : total length = len
///        lo1    mid    len-mid+1
/// in:  [ [ left ]  X  [ right ] ] : total length = len
///        lo2  mid      len-mid+1
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.empty()) return NULL;
        int n = preorder.size();
        return build(preorder, inorder, 0, 0, n);
    }
    //starting positions of arrays and lengths
    TreeNode *build(vector<int>& preorder, vector<int>& inorder, int lo1, int lo2, int len) {
        if(len == 0) return NULL;
        int r = preorder[lo1];
        TreeNode *root = new TreeNode(r);
        int mid = 0; //number of nodes in left subtree
        while(inorder[lo2+mid] != r) mid++;
        root->left = build(preorder, inorder, lo1+1, lo2, mid);
        root->right = build(preorder, inorder, lo1+1+mid, lo2+mid+1, len-mid-1);
        return root;
    }
};

// Solution 2, slightly different version

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.empty()) return NULL;
        int n = preorder.size();
        return buildTree(preorder, 0, n-1, inorder, 0, n-1);
    }
    //build tree from pre[p1 ..p2] and in[i1 .. i2]
    TreeNode* buildTree(vector<int>& preorder, int p1, int p2, vector<int>& inorder, int i1, int i2) {
        int len = p2 - p1 + 1;
        if(len <= 0) return NULL;
        if(len == 1) return new TreeNode(preorder[p1]); //one node only
        int root_val = preorder[p1];
        TreeNode *root = new TreeNode(root_val);
        
        int i = i1;
        for(; i <= i2; i++) {
            if(inorder[i] == root_val) break;
        }
        //i is the root in inorder
        int nl = i-i1; //number of elements in left subtree
        root->left = buildTree(preorder, p1+1, p1+nl, inorder, i1, i-1);
        root->right = buildTree(preorder, p1+nl+1, p2, inorder, i+1, i2);
    }
};

/**************************************************** 
 ***    106,Medium,Construct Binary Tree from Inorder and Postorder Traversal 
 ****************************************************/

/*
Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree. 
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Similar idea as 105

class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(inorder.empty()) return NULL;
        int n = inorder.size();
        return build(inorder, postorder, 0, 0, n);
    }
    //starting positions of arrays and lengths
    TreeNode *build(vector<int>& inorder, vector<int>& postorder, int lo1, int lo2, int len) {
        if(len == 0) return NULL;
        int r = postorder[lo2+len-1];
        TreeNode *root = new TreeNode(r);
        int mid = 0; //number of nodes in left subtree
        while(inorder[lo1+mid] != r) mid++;
        root->left = build(inorder, postorder, lo1, lo2, mid);
        root->right = build(inorder, postorder, lo1+mid+1, lo2+mid, len-mid-1);
        return root;
    }
};

// Solution 2, slightly different.
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(inorder.empty()) return NULL;
        int n = inorder.size();
        return buildTree(inorder, 0, n-1, postorder, 0, n-1);
    }
    //build tree from in[i1 .. i2] and post[p1 .. p2]
    TreeNode* buildTree(vector<int>& inorder, int i1, int i2, vector<int>& postorder, int p1, int p2) {
        int len = p2 - p1 + 1;
        if(len <= 0) return NULL;
        if(len == 1) return new TreeNode(postorder[p1]); //one node only
        int root_val = postorder[p2]; //last one is root
        TreeNode *root = new TreeNode(root_val);
        
        int i = i1;
        for(; i <= i2; i++) {
            if(inorder[i] == root_val) break;
        }
        //i is the root in inorder
        int nl = i-i1; //number of elements in left subtree
        root->left = buildTree(inorder, i1, i-1, postorder, p1, p1+nl-1);
        root->right = buildTree(inorder, i+1, i2, postorder, p1+nl, p2-1);
    }
};


/**************************************************** 
 ***    108,Medium,Convert Sorted Array to Binary Search Tree 
 ****************************************************/

/*
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if(nums.empty()) return NULL;
        int n = nums.size();
        return convert(nums, 0, n-1);
    }
    
    TreeNode* convert(vector<int>& nums, int lo, int hi) {
        if(lo > hi) return NULL;
        int mid = (lo+hi)/2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = convert(nums, lo, mid-1);
        root->right = convert(nums, mid+1, hi);
        return root;
    }
};

// A variant. Range is [beg, end)

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return helper(nums, 0, nums.size());
    }

    TreeNode* helper(vector<int>& nums, int beg, int end) {
        if(beg >= end) return NULL;
        int mid = (beg+end)/2;
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = helper(nums, beg, mid);
        root->right = helper(nums, mid+1, end);
        return root;
    }
};


/**************************************************** 
 ***    109,Medium,Convert Sorted List to Binary Search Tree 
 ****************************************************/

/*
Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution. First find middle element, then use that element as root of tree node, recursively build tree for the list segments before and after middle element, and attach as left and right child of root.

class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        return helper(head, NULL);
    }
    //construct from head (inclusive) to tail (exclusive)
    TreeNode *helper(ListNode* head, ListNode *tail) {
        if(head == tail) return NULL;
        ListNode *slow = head, *fast = head;
        while(fast->next != tail && fast->next->next != tail) { //this approach returns middle of element, or the first among the two middle ones.
            slow = slow->next;
            fast = fast->next->next;
        }
        //make slow the root
        TreeNode *root = new TreeNode(slow->val);
        root->left = helper(head, slow);
        root->right = helper(slow->next, tail);
        return root;
    }
};


/**************************************************** 
 ***    113,Medium,Path Sum II 
 ****************************************************/

/*
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
For example:
Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1

return

[
   [5,4,11,2],
   [5,8,4,5]
]
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// DFS backtracking. Recursive solution.
// Caveats: when reaching leaf, compare sum with x, not with zero!

class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int> > result;
        if(!root) return result;
        vector<int> path;
        dfs(root, sum, path, result);
        return result;
    }
    void dfs(TreeNode* root, int sum, vector<int>& path, vector<vector<int> >& result) {
        int x = root->val;
        path.push_back(x);
        //reaching leaf
        if(!root->left && !root->right && sum == x) result.push_back(path);
        if(root->left) dfs(root->left, sum-x, path, result);
        if(root->right) dfs(root->right, sum-x, path, result);
        path.pop_back();
    }
};

/**************************************************** 
 ***    114,Medium,Flatten Binary Tree to Linked List 
 ****************************************************/

/*
 Given a binary tree, flatten it to a linked list in-place.

For example,
Given

         1
        / \
       2   5
      / \   \
     3   4   6

The flattened tree should look like:

   1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution. First flatten right, then left, then insert left list between root and root->right. Finally, remember to set root->left to NULL!
// Caveat: Set root->left to NULL in the end!

class Solution {
public:
    void flatten(TreeNode* root) {
        if(!root) return;
        flatten(root->left);
        flatten(root->right);
        if(root->left) {
            TreeNode *node = root->left;
            while(node->right) node = node->right;
            node->right = root->right;
            root->right = root->left;
            root->left = NULL;
        }
    }
};


/**************************************************** 
 ***    116,Medium,Populating Next Right Pointers in Each Node 
 ****************************************************/

/*
Given a binary tree

    struct TreeLinkNode {
      TreeLinkNode *left;
      TreeLinkNode *right;
      TreeLinkNode *next;
    }

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

    You may only use constant extra space.
    You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).

For example,
Given the following perfect binary tree,

         1
       /  \
      2    3
     / \  / \
    4  5  6  7

After calling your function, the tree should look like:

         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL
*/

/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */

// General solution that works for all kinds of trees
// Use a dummy head in current layer.
// Use last layer to help progress the current layer

// Solution 1. Use two dummy heads. Progress layer by layer. Use last layer to help traverse current layer. Remember to set the tail's next to NULL when finishing one layer.

class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        //two dummy heads
        TreeLinkNode* phead = new TreeLinkNode(0);
        TreeLinkNode* qhead = new TreeLinkNode(0);
        TreeLinkNode *p = phead, *q = qhead;
        phead->next = root; root->next = NULL;
        while(phead->next) {
            p = p->next;
            while(p && !p->left && !p->right)  p = p->next;
            if(!p) {
                q->next = NULL; //set tail pointer
                phead->next = qhead->next;
                p = phead;
                q = qhead;
                continue;
            }
            if(p->left) {
                q->next = p->left;
                q = q->next;
            }
            if(p->right) {
                q->next = p->right;
                q = q->next;
            }
        }
        delete phead, qhead;
    }
};

// Solution 2. An old solution with the same idea.

class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        TreeLinkNode dum1(0), *head(&dum1); //dummy head
        TreeLinkNode *last(root), *curr(NULL); //head of last row, and curr tail node
        while(last) {
            curr = head;
            while(last) {
                if(!last->left && !last->right) {
                    last = last->next;
                    continue;
                }
                curr->next = (last->left ? last->left : last->right);
                curr = curr->next;
                if(curr == last->left && last->right) {
                    curr->next = last->right;
                    curr = curr->next;
                }
                last = last->next;
            }
            last = head->next; //move to new row
            head->next = NULL; //reset to NULL!
        }
    }
};

/**************************************************** 
 ***    120,Medium,Triangle 
 ****************************************************/

/*
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]

The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle. 
*/

// Solution using standard DP, with 2 vectors representing current and next rows.

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.empty()) return 0;
        int ret = INT_MAX;
        int nr = triangle.size();
        vector<int> currRow(nr, INT_MAX);
        vector<int> nextRow(nr, INT_MAX);
        //row 0:
        currRow[0] = triangle[0][0];
        for (int ir = 1; ir < nr; ++ir) { //ir has ir+1 elements in triangle (0 .. ir)
            nextRow[0] = currRow[0] + triangle[ir][0];
            for (int j = 1; j < ir; ++j)
                nextRow[j] = min(currRow[j-1], currRow[j]) + triangle[ir][j];
            nextRow[ir] = currRow[ir-1] + triangle[ir][ir];
            currRow.swap(nextRow);
        }
        for (size_t i = 0; i < currRow.size(); ++i) {
            ret = min(ret, currRow[i]);
        }
        return ret;
    }
};

/**************************************************** 
 ***    121,Medium,Best Time to Buy and Sell Stock 
 ****************************************************/

/*
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.
*/

/// Greedy one pass O(n) solution:

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        int max_so_far = 0, max_all = 0;
        for(int i = 1; i < n; ++i) {
            int change = prices[i] - prices[i-1];
            if(max_so_far <= 0) max_so_far = change;
            else max_so_far += change;
            max_so_far = max(0, max_so_far);
            max_all = max(max_so_far, max_all);
        }
        return max_all;
    }
};

/**************************************************** 
 ***    122,Medium,Best Time to Buy and Sell Stock II 
 ****************************************************/

/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/

/// Allow infinte transitions. Very simple. Just add up all positive differences!

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int max_profit = 0;
        for (int i = 1; i < prices.size(); ++i) {
            int diff = prices[i] - prices[i-1];
            if (diff > 0) max_profit += diff;
        }
        return max_profit;
    }
};

/**************************************************** 
 ***    127,Medium,Word Ladder 
 ****************************************************/

/*
Given two words (beginWord and endWord), and a dictionary, find the length of shortest transformation sequence from beginWord to endWord, such that:

    Only one letter can be changed at a time
    Each intermediate word must exist in the dictionary

For example,

Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]

As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:

    Return 0 if there is no such transformation sequence.
    All words have the same length.
    All words contain only lowercase alphabetic characters.

*/

/* 
=== Solution 1 ===
One-way BFS from beinWord to endWord. Do not remove elements from the original dictionary! Rather create a new one (unvisited) and remove from it.
Systematically trying the new word by altering one character of the new word. Do not create a new string, rather change the character in-place and revert back to original afterwards.
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
       deque<pair<string, int> > q;
       unordered_set<string> unvisited = wordList;
       int wl = beginWord.size();

       q.push_back(make_pair(beginWord, 1));
       unvisited.erase(beginWord); //remove beginWord to unvisited
       unvisited.insert(endWord); //insert beginWord to unvisited
       while(!q.empty()) {
           string wd = q.front().first;
           int level = q.front().second;
           if(wd == endWord) return level;
           q.pop_front();
           for(int i = 0; i < wl; ++i) {
               char c = wd[i];
               for(char ch = 'a'; ch <= 'z'; ++ch) {
                   if(ch == c) continue;
                   wd[i] = ch;
                   if(unvisited.count(wd))  {
                       q.push_back(make_pair(wd, level+1));
                       unvisited.erase(wd);
                   }
               }
               wd[i] = c; //revert back
           }
       }

       return 0;
    }
};

/*
=== Solution 2 ===
BFS with two sets, one for current level, one for next level, and in the end of each iteration swap the two.
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
       vector<string> current, next;
       int level = 1;
       unordered_set<string> unvisited = wordList;
       int wl = beginWord.size();

       unvisited.erase(beginWord);
       unvisited.insert(endWord);

       current.push_back(beginWord);
       
       while(!current.empty()) {
           for(vector<string>::iterator it = current.begin(); it != current.end(); ++it) {
               string wd = *it;
               for(int i = 0; i < wl; ++i) {
                   char c = wd[i];
                   for(char ch = 'a'; ch <= 'z'; ++ch) {
                       if(ch == c) continue;
                       wd[i] = ch;
                       if(wd == endWord) return level+1;
                       if(unvisited.count(wd))  {
                           next.push_back(wd);
                           unvisited.erase(wd);
                       }
                   }
                   wd[i] = c; //revert back
               }
           }
           current.swap(next);
           next.clear();
           level++;
       }
       return 0;        
    }
};

/*
=== Solution 3 ===
Bi-directional BFS to reduce search space. Start from two ends (begin/end), and only do BFS from the side with smaller search space. 
When we find one string in the search front that belongs to the front of the other side, we have "connected" the two sides.
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
       unordered_set<string> beginSet, nextSet, endSet;
       unordered_set<string> unvisited = wordList;
       int wl = beginWord.size();

       unvisited.erase(beginWord);
       unvisited.erase(endWord);

       beginSet.insert(beginWord);
       endSet.insert(endWord);
       int level = 2;

       while(!beginSet.empty()) {
           //for(unordered_set<string>::iterator it = beginSet.begin(); it != beginSet.end(); ++it) {
           for(auto wd : beginSet) {
               for(int i = 0; i < wl; ++i) {
                   char c = wd[i];
                   for(char ch = 'a'; ch <= 'z'; ++ch) {
                       if(ch == c) continue;
                       wd[i] = ch;
                      if(endSet.count(wd)) return level;
                       if(unvisited.count(wd))  {
                           nextSet.insert(wd);
                           unvisited.erase(wd);
                       }
                   }
                   wd[i] = c; //revert back
               }
           }
           beginSet.swap(nextSet);
           nextSet.clear();
           level++;
           if(beginSet.size() > endSet.size()) beginSet.swap(endSet);
       }
       return 0;
    }
};

/*
=== Solution 4 ===
Bidirectional BFS, recursive solution (64ms!)
*/
class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        unordered_set<string> unvisited = wordList;
        unvisited.erase(beginWord);
        unvisited.erase(endWord);
        unordered_set<string> forwardSet, backwardSet;
        forwardSet.insert(beginWord);
        backwardSet.insert(endWord);
        return ladderLengthUtil(forwardSet, backwardSet, unvisited, 2);
    }
    int ladderLengthUtil(unordered_set<string>& forwardSet, unordered_set<string>& backwardSet, unordered_set<string>& unvisited, int level) {
        if(forwardSet.empty()) return 0;
        if(forwardSet.size() > backwardSet.size()) return ladderLengthUtil(backwardSet, forwardSet, unvisited, level);
        unordered_set<string> next;
        for(auto word : forwardSet) {
            //try all posssibilities
            for(auto it = word.begin(); it != word.end(); ++it) {
                char tmp = *it;
                for(*it = 'a'; *it != 'z'; ++(*it)) {
                    if(*it == tmp) continue;
                    if(backwardSet.count(word)) return level;
                    else if(unvisited.count(word)) { //not visited
                        unvisited.erase(word);
                        next.insert(word);
                    }
                }
                *it = tmp; //revert back
            }
        }
        return ladderLengthUtil(next, backwardSet, unvisited, level+1);
    }
};


/**************************************************** 
 ***    129,Medium,Sum Root to Leaf Numbers 
 ****************************************************/

/*
Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

    1
   / \
  2   3

The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25. 
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Post-order traversal using a stack.
// Keep a running partial sum, and when reaching a leaf, add the partial sum to total sum.
// First time visiting a node, add value to partial sum. When finished processing left and right subtrees, remove the value from partial sum.
// Caveats: avoid adding value to partial sum multiple times! Only do it when tag == 0.

class Solution {
public:
    int sumNumbers(TreeNode* root) {
        if(!root) return 0;
        int partial_sum(0), total_sum(0);
        deque<pair<TreeNode*, int> > s; //stack
        s.push_back(make_pair(root, 0));
        while(!s.empty()) {
            TreeNode *node = s.back().first;
            int tag = s.back().second;
            if(tag == 0) { //first-time, push left subtree to stack
                partial_sum = partial_sum*10 + node->val; //also calculate partial sum
                s.back().second++;
                if(node->left) s.push_back(make_pair(node->left, 0));
            } else if(tag == 1) { //second-time, push right subtree to stack
                s.back().second++;
                if(node->right) s.push_back(make_pair(node->right, 0));
            } else {  //third-time, process node
                if(!node->left && !node->right) total_sum += partial_sum;
                partial_sum /= 10; //revert to previous value without this node
                s.pop_back();
            }
        }
        return total_sum;
    }
};

// Another solution. Similar, but add pathSums when node has been added.
class Solution {
public:
    int sumNumbers(TreeNode* root) {
        if(!root) return 0;
        stack<pair<TreeNode*, int> > st;
        st.push(make_pair(root, 0));
        int sum = 0, pathSum = root->val;
        while(!st.empty()) {
            TreeNode* node = st.top().first;
            int tag = st.top().second;
            if(tag == 0) {
                st.top().second++;
                if(node->left) { 
                    st.push(make_pair(node->left, 0));
                    pathSum = pathSum*10 + node->left->val;
                }
            } else if(tag == 1) {
                st.top().second++;
                if(node->right) {
                    st.push(make_pair(node->right, 0));
                    pathSum = pathSum*10 + node->right->val;
                }
            } else {
                st.pop();
                if(!node->left && !node->right) sum += pathSum; //leaf node, add to sum
                pathSum /= 10;
            }
        }
        return sum;
    }
};


/**************************************************** 
 ***    130,Medium,Surrounded Regions 
 ****************************************************/

/*
Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,

X X X X
X O O X
X X O X
X O X X

After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X
*/

// Use BFS search instead of DFS to avoid stack-overflow
// First label all 'O' connected to borders as 'T' (BFS)
// Then linearly scan all matrix, mark all 'O' as 'X' and 'T' as 'O'

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if(board.empty() || board[0].empty()) return;
        int m = board.size(), n = board[0].size();
        //bfs, starting from boundary 'O's
        vector<pair<int, int> > curr, next;
        for(int i = 0; i < m; i++) {
            testSet(board, i, 0, curr);
            testSet(board, i, n-1, curr);
        }
        for(int j = 1; j < n-1; j++) {
            testSet(board, 0, j, curr);
            testSet(board, m-1, j, curr);
        }
        //now do bfs
        while(!curr.empty()) {
            for(auto pos : curr) {
                int ir = pos.first, jc = pos.second;
                if(ir > 0)    testSet(board, ir-1, jc, next);
                if(ir < m-1)  testSet(board, ir+1, jc, next);
                if(jc > 0)    testSet(board, ir, jc-1, next);
                if(jc < n-1)  testSet(board, ir, jc+1, next);
            }
            curr.swap(next);
            next.clear();
        }
        //now set all 'O' to 'X' and all 'T' back to 'O'
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(board[i][j] == 'O') board[i][j] = 'X';
                else if(board[i][j] == 'T') board[i][j] = 'O';
            }
        }
    }
    //helper function to set value 'O' temporarily as 'T', and push position to queue
    void testSet(vector<vector<char>>& board, int i, int j, vector<pair<int, int> >& q) {
        if(board[i][j] == 'O') {
            board[i][j] = 'T';
            q.push_back(make_pair(i, j));
        }
    }
};

// DFS search version, causes runtime error due to stack overflow (stack runs too deep)
// First label all 'O' connected to borders as 'T' (BFS)
// Then linearly scan all matrix, mark all 'O' as 'X' and 'T' as 'O'

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return;
        int m = board.size(), n = board[0].size();
        //dfs on boundary nodes, temporary mark as 'T'
        for (int i = 0; i < m; ++i) {
            if(board[i][0] == 'O') dfs(board, i, 0);
            if(board[i][n-1] == 'O') dfs(board, i, n-1);
        }
        for (int j = 1; j < n-1; ++j) {
            if(board[0][j] == 'O') dfs(board, 0, j);
            if(board[m-1][j] == 'O') dfs(board, m-1, j);
        }
        //scan all matrix, mark all 'O' as 'X'; mark all 'T' back to 'O'
        for (int i = 0; i < m; ++i)  {
            for (int j = 0; j < n; ++j) {
                if(board[i][j] == 'O') board[i][j] = 'X';
                if(board[i][j] == 'T') board[i][j] = 'O';
            }
        }
    }
    void dfs(vector<vector<char> >& board, int i, int j) {
        int m = board.size(), n = board[0].size();
        board[i][j] = 'T';
        // check four neighbors
        if(j < n-1 && board[i][j+1] == 'O') dfs(board, i, j+1);
        if(j > 0   && board[i][j-1] == 'O') dfs(board, i, j-1);
        if(i < m-1 && board[i+1][j] == 'O') dfs(board, i+1, j);
        if(i > 0   && board[i-1][j] == 'O') dfs(board, i-1, j);
    }
};


/**************************************************** 
 ***    131,Medium,Palindrome Partitioning 
 ****************************************************/

/*
Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

  [
    ["aa","b"],
    ["a","a","b"]
  ]
*/

/// use DFS. Don't need to use dynamic programming, since there is no overlapping subproblems. Only checked ispalindrome(s, i, j) once for each i, j pair.

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<string> tmp;
        vector<vector<string> > ret;
        if(s.empty()) return ret;
        
        dfs(s, 0, tmp, ret);
        return ret;
    }
    
    void dfs(const string& s, int i, vector<string>& tmp, vector<vector<string> >& ret) {
        if(i == s.size()) {
            ret.push_back(tmp);
            return;
        }
        tmp.push_back(""); //add one entry
        for (int j = i; j < s.size(); ++j) {
            if(isPalindrome(s, i, j)) {
                tmp.back() = s.substr(i, j-i+1);
                dfs(s, j+1, tmp, ret);
            }
        }
        tmp.resize(tmp.size()-1); //remove last entry
    }
    bool isPalindrome(const string& s, int i, int j) {
        while(i < j) {
            if(s[i++] != s[j--]) return false;
        }
        return true;
    }
};

/**************************************************** 
 ***    133,Medium,Clone Graph 
 ****************************************************/

/*
Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.

OJ's undirected graph serialization:

Nodes are labeled uniquely.
We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.

As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as separated by #.

    First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
    Second node is labeled as 1. Connect node 1 to node 2.
    Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.

Visually, the graph looks like the following:

       1
      / \
     /   \
    0 --- 2
         / \
         \_/
*/

/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */

/// One pass solution using DFS. Make sure only visit unvisited nodes. First create a copy for current node, and then process its neighors,
/// It neighbor already visited (indicated by the map), then use the copy as the new neighbor, otherwise dfs on the neighbor.
/// Maintain a map from old node to new node, which also serves as the visited marker

class Solution {
public:
    typedef UndirectedGraphNode Node;
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(!node) return NULL;
        return dfs(node);
    }
    Node* dfs(Node* node) {
        Node* newnode = new Node(node->label);
        dict[node] = newnode; //insert to map before processing neighbors (handle self-loops)
        newnode->neighbors = node->neighbors;
        for(int i = 0; i < node->neighbors.size(); i++) {
            if(dict.count(node->neighbors[i])) newnode->neighbors[i] = dict[node->neighbors[i]];
            else newnode->neighbors[i] = dfs(node->neighbors[i]);
        }
        return newnode;
    }
    unordered_map<Node*, Node*> dict;
};

/// Solution 2, slightly different one. In DFS, first check if node is visited or not. If visited, just return the copy.

class Solution {
public:
    typedef UndirectedGraphNode Node;
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(!node) return NULL;
        return dfs(node);
    }
    Node* dfs(Node* node) {
        if(dict.count(node)) return dict[node];
        Node* newnode = new Node(node->label);
        dict[node] = newnode; //insert to map before processing neighbors (handle self-loops)
        newnode->neighbors = node->neighbors;
        for(int i = 0; i < node->neighbors.size(); i++) {
            newnode->neighbors[i] = dfs(node->neighbors[i]);
        }
        return newnode;
    }
    unordered_map<Node*, Node*> dict;
};


/**************************************************** 
 ***    134,Medium,Gas Station 
 ****************************************************/

/*
There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

Note:
The solution is guaranteed to be unique. 
*/

/*
Two pass DP solution using an auxiliary array to store minimum required gas from 0 to other sites. O(n) space.
To be able to complete circuit at a site i, we need to traverse i to 0, and then from 0 to i. The idea is to first figure out
the minimum amount of gas needed when traveling from site 0 to site i (required[i]). 
The second pass, we calculate the remaining gases traveling from site i to 0 (starting with an empty tank). We do it in reverse order.
If at a given site i the remaining gases are larger than the pre-calculated minimum aount of gas needed at that site, then we know for sure that we can complete the circuit at site i.
the net consumption of gas from site i-1 to i is: amount of gas available at site i-1 (gas[i-1]) - gas cost between i-1 and i (cost[i-1]) + leftovers in tank at site i-1 (leftover).
If the net consumption is positive, then the minimum required gas at site i-1 is enough. If it is negative, then we need additional gas to cover the cost from i-1 to i, thus: required[i] = required[i-1] + (net < 0 ? -net : 0);
Similarly, if the net consumption is positive, we have more leftovers, otherwise we have 0. thus: leftover = (net > 0 ? net : 0);
*/

class Solution {
    
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size(); //assume n >= 2
        vector<int> required(n, 0); //minimum required gas from 0 to i
        int leftover(0);  //leftover gas from 0 to i
        for(int i = 1; i < n; ++i) {
            int net = gas[i-1]-cost[i-1]+leftover;
            required[i] = required[i-1] + (net < 0 ? -net : 0);
            leftover = (net > 0 ? net : 0);
        }
        int remaining(0); //leftover from i to 0
        for(int i = n-1; i >= 0; --i) {
           remaining += (gas[i] - cost[i]);
           if(remaining >= required[i]) return i;
        }
        return -1;
    }
};

/*
O(1) space greedy solution. 2 passes.
Start from 0, move forward and record the lowest level in the tank (could be negative), and the associated site position. Say i, this means that, tank will reach lowest level after visiting site i, when reaching site i+1. 
If the lowest level is non-negative, then we can complete circuit at site 0. Just return 0.
Second pass starts form site i+1, and traverse to 0. Calculate the residue amount of gas after reaching 0. If the residue amount is larger than the deficit from 0 to i, then we can complete circle from site i+1.

Caveat:
min_pos+1 need to apply modulo N or not? Looks like not, since that corresponds to site 0, but we already identified site 0 with condition min_left >= 0.
*/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int leftover = 0, min_left = 0, min_pos = -1;
        for(int i = 0; i < gas.size(); ++i) {
            leftover += gas[i] - cost[i];
            if(leftover < min_left) {  min_left = leftover, min_pos = i; }
        }
        if(min_left >= 0) return 0;
        int residue = 0;
        for(int j = min_pos+1; j < gas.size(); ++j) {
            residue += gas[j] - cost[j];
        }
        if(residue + min_left >= 0) return min_pos+1;
        else return -1;
    }
};

/*
O(1) space greedy solution. Only 1 pass.
We can improve from the last solution by noting that we can calculate residue and leftover in the same loop. When we see a smaller tank level, we reset residue to zero. The calculation for residue is effectively the same as previous solution.
*/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int leftover = 0, min_left = 0, min_pos = -1, residue = 0;
        for(int i = 0; i < gas.size(); ++i) {
            int net = gas[i] - cost[i];
            leftover += net;
            residue += net;
            if(leftover < min_left) { 
                min_left = leftover;
                min_pos = i; 
                residue = 0;
            } 
        }
        if(residue + min_left >= 0) return (min_pos+1)%gas.size();
        else return -1;
    }
};


/**************************************************** 
 ***    136,Medium,Single Number 
 ****************************************************/

/*
Given an array of integers, every element appears twice except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory? 
*/

/// Use exclusive OR

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int v = 0;
        for (int i = 0; i < nums.size(); ++i)
            v ^= nums[i];
        return v;
    }
};

/**************************************************** 
 ***    137,Medium,Single Number II 
 ****************************************************/

/*
Given an array of integers, every element appears three times except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory? 
*/

/// Use bit operations. Can extend to general cases (N times)
/// Use three variables to store the occurrences of each bit: 
/// ones stores whether the bit has been set for AT LEAST 1 times
/// twos stores whether the bit has been set for AT LEAST 2 times
/// threes stores whether the bit has been set for 3 times
/// when each bit position has reached maximum number of times (3), we reset the corresponding bit positions in ones and twos to zero

/// The "AT LEAST" implies that the ones, twos are not mutually exclusive (e.g. ones & twos != 0)

// 1. A given bit position has appeared 3 times iff already appeared 2 times AND the corresponding bit of nums[i] is set, hence: threes = twos & nums[i]
// 2. For twos, if it is already set (appeared at least 2 times), we don’t touch it, otherwise, it can be set to 1 iff it has appeared at least one time and nums[i] has the bit set, hence twos = twos | (ones & nums[i]). 
// 3. For ones, if it is already set (appeared at least 1 times), we don’t touch it, otherwise, it can be set to 1 iff nums[i] has the bit set, hence ones = ones | nums[i]. 
// 4. For both twos and ones, we need to reset bits when reaching 3 times. Thus: ones = ones & ~threes; twos = twos & ~threes;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ones(0), twos(0), threes(0);
        for(int i = 0; i < nums.size(); ++i) {
            threes = twos & nums[i];
            twos = (twos | (ones & nums[i])) & ~threes;
            ones = (ones | nums[i]) & ~threes; // it is |, not ^
        }
        return ones;
    }
};

// Extension to general cases (N times)
/// Use an array to store the occurrences of each bit: 
/// count[1] stores whether the bit has been set for AT LEAST 1 times
/// count[2] stores whether the bit has been set for AT LEAST 2 times
/// count[N] stores whether the bit has been set for N times
/// when each bit position has reached maximum number of times (N), we reset the corresponding bit positions in count to zero

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        const int N = 3; //number of times, can be generalized to > 3
        vector<int> count(N+1, 0); //count[i]: occured AT LEAST i times? (count[0] unused)
        for(int i = 0; i < nums.size(); ++i) {
            count[N] = count[N-1] & nums[i];
            for(int n = N-1; n > 1; --n)
                count[n] = (count[n] | (count[n-1] & nums[i])) & ~count[N];
            count[1] = (count[1] | nums[i]) & ~count[N];
        }
        return count[1];
    }
};

/**************************************************** 
 ***    139,Medium,Word Break 
 ****************************************************/

/*
 Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code". 
*/

/// Dynamic programming, store whether s's length-i substring can be broken into an array. 
/// When found, just break;
/// Optimization: for j goes opposite direction to i, so that we encountered lastly found breakable item first.
/// 4ms.

class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        //if(s.empty()) return true;
        int n = s.size();
        vector<bool> breakable(n+1, false); //whether s[i, n) is breakable
        breakable[n] = true; //s[n, n) is defined to be true
        for(int i = n-1; i >= 0; --i) { //check s[i, n)
            for(int j = i+1; j <= n; ++j) { //check s[i, j) and s[j, n), j direction optimized so that we encountered lastly set breakable[j] first
                if(breakable[j] && wordDict.count(s.substr(i, j-i))) { 
                    breakable[i] = true; 
                    break; 
                }
            }
        }
        return breakable[0];        
    }
};

// Solution 2. Same solution as 1 except starting from beginning
class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n+1,false);
        dp[0]=true;
        for(int i=1; i<=n; i++)  {
            for(int j = i-1; j >= 0; j--) {
                if(dp[j] && wordDict.count(s.substr(j,i-j))) {
                    dp[i]=true;
                    break; //next i
                }
            }
        }
        return dp[n];
    }
};

// Solution 3. DP with memoization (16ms)
class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        if(breakable.count(s)) return breakable[s];
        if(wordDict.count(s)) {
            breakable[s] = true; //memoization
            return true;
        }
        int n = s.size();
        for(int i = 1; i < n; ++i) {
            if(wordDict.count(s.substr(0, i)) && wordBreak(s.substr(i), wordDict)) {
                breakable[s] = true;
                return true;
            }
        }
        breakable[s] = false;
        return false;
    }
    unordered_map<string, bool> breakable;
};


/**************************************************** 
 ***    141,Medium,Linked List Cycle 
 ****************************************************/

/*
Given a linked list, determine if it has a cycle in it.

Follow up:
Can you solve it without using extra space?
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Floyd's algorithm. Maintain a slow and a fast pointer
// see http://keithschwarz.com/interesting/code/?dir=find-duplicate

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == NULL) return false;
        ListNode *slow(head), *fast(head);
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast) return true;
        }
        return false;
    }
};

/**************************************************** 
 ***    142,Medium,Linked List Cycle II 
 ****************************************************/

/*
Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

Note: Do not modify the linked list.

Follow up:
Can you solve it without using extra space?
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Floyd's algorithm. Maintain a slow and a fast pointer
// see http://keithschwarz.com/interesting/code/?dir=find-duplicate

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if(head == NULL) return NULL;
        ListNode *slow = head, *fast = head;
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast) break;
        }
        if(!fast || !fast->next) return NULL; //no cycle detected
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};

/**************************************************** 
 ***    143,Medium,Reorder List 
 ****************************************************/

/*
Given a singly linked list L: L0->L1->...->Ln-1->Ln,
reorder it to: L0->Ln->L1->Ln-1->L2->Ln-2->...

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// 1. Traverse list using a slow and a fast pointer, find the middle element
// 2. Reverse the second half of list and return its head
// 3. start from head of first half, insert elements of second half one-by-one to first half.
// 4. set the next pointer of combined graph's tail as NULL

class Solution {
public:
    void reorderList(ListNode* head) {
        if(!head || !head->next || !head->next->next) return;
        ListNode* slow = head, *fast = head;
        while(fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *p = head;
        ListNode *q = reverse(slow->next);
        slow->next = NULL;
        merge(p, q);
    }

    ListNode* reverse(ListNode *head) {
        if(!head || !head->next) return head;
        ListNode *p = head, *q = p->next;
        //p is head of new list
        while(q) {
            ListNode *tmp = q->next;
            q->next = p;
            p = q; q = tmp; //move forward
        }
        head->next = NULL;
        return p;
    }

    void merge(ListNode* p, ListNode *q) {
        ListNode *r = p;
        while(q) {
            ListNode *tmp = q->next;
            q->next = r->next;
            r->next = q;
            r = q->next; q = tmp; //move forward
        }
    }
};


/**************************************************** 
 ***    144,Medium,Binary Tree Preorder Traversal 
 ****************************************************/

/*
Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [1,2,3].

Note: Recursive solution is trivial, could you do it iteratively?
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution (easy).

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        if(!root) return ret;
        preorder(root, ret);
        return ret;
    }
    void preorder(TreeNode *root, vector<int>& ret) {
        if(!root) return;
        ret.push_back(root->val);
        preorder(root->left, ret);
        preorder(root->right, ret);
    }
};

// Iterative solution using a stack

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        if(!root) return ret;
        deque<TreeNode*> s; //stack
        s.push_back(root);
        while(!s.empty()) {
            TreeNode *node = s.back(); s.pop_back();
            ret.push_back(node->val);
            if(node->right) s.push_back(node->right);
            if(node->left) s.push_back(node->left);
        }
        return ret;
    }
};

/**************************************************** 
 ***    147,Medium,Insertion Sort List 
 ****************************************************/

/*
Sort a linked list using insertion sort.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/// Start from head, track the tail of already sorted list
/// If the element to be added is larger than the tail of sorted list, simply append it to the tail and move on (makes the code more efficient, 92ms => 28ms reduction!)
/// Otherwise scan from head of list and find the position to insert
/// Remember to set the next pointer of list's tail to NULL in the beginning.

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode *tail = head, *q = head->next;
        tail->next = NULL; //set tail's next to NULL
        while(q) {
            ListNode *next = q->next;
            //insert q to list from dummy to tail
            if(q->val >= tail->val) {
                tail = tail->next = q;  //update tail!
		q->next = NULL;
            } else { //search insert position from beginning
                ListNode *curr = dummy->next, *prev = dummy;
                while(curr && curr->val <= q->val) {
                    prev = curr; curr = curr->next;
                }
                prev->next = q; q->next = curr; //insert to list
            }
            q = next; //move forward
        }

        head = dummy->next;
        delete dummy;
        return head;
    }
};

/**************************************************** 
 ***    148,Medium,Sort List 
 ****************************************************/

/*
Sort a linked list in O(n log n) time using constant space complexity.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Solution 1. Top-down merge sort (not really constant space, because of stack space)
// when finding the middle element, fast is initialized as head->next, not head, to avoid infinite loop in corner cases (only two nodes).

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* p = head, *q = head;
        while(q->next && q->next->next) {
            p = p->next;
            q = q->next->next;
        }
        //merge head and p->next
        q = p->next;
        p->next = NULL;
        head = sortList(head);
        q = sortList(q);
        return merge(head, q);
    }

    ListNode *merge(ListNode* left, ListNode *right) {
        ListNode* dummy = new ListNode(0);
        ListNode *p = left, *q = right, *tail = dummy;
        while(p && q) {
            if(p->val <= q->val) {
                tail->next = p; p = p->next;
            } else {
                tail->next = q; q = q->next;
            }
            tail = tail->next;
        }
        tail->next = p ? p : q;

        p = dummy->next;
        delete dummy;
        return p;
    }
};

// Solution 2. Bottom-up merge sort with O(1) space, by using an elegant split function.
// Maintain the length of sub lists to be sorted, starting form 1, and then 2, 4 ...
// Split(head, len), cuts break the list at position len, and returns the head of the second part, e.g.
// head = 1 -> 2 -> 3 -> 4, len = 2, then after second = split(head, 2), we have head = 1->2,  second = 3->4.
// Merge merges to linked lists and attach them to the head, and then returns the tail of the merged list.

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        int count = 0;
        ListNode *p = dummy->next;
        while(p) {
            count++;
            p = p->next;
        }
        for(int len = 1; len < count; len *= 2) { //len: merge length
            ListNode *tail = dummy, *left = dummy->next;
            while(left) {
                ListNode *right = split(left, len);
                ListNode *next = split(right, len);
                tail = merge(left, right, tail);
                left = next;
            }
        }
        head = dummy->next;
        delete dummy;
        return head;
    }

    ListNode* split(ListNode *head, int len) {
        while(head && len > 1) {
           head = head->next; len--;
        }
        if(!head) return NULL;
        ListNode *second = head->next;
        head->next = NULL;
        return second;
    }
    //merge two lists and attach to head (head serves similar to the dummy head), and return the tail of the merged list
    ListNode *merge(ListNode* left, ListNode *right, ListNode *head) {
        ListNode *p = left, *q = right, *tail = head;
        while(p && q) {
            if(p->val < q->val) {
                tail->next = p; p = p->next;
            } else {
                tail->next = q; q = q->next;
            }
            tail = tail->next;
        }
        tail->next = p ? p : q;
        while(tail->next) tail = tail->next;
        return tail;
    }
};

// Solution 3. 3-way quick-sort, with the first element as the pivot. Maintain three sub lists, one < x, one == x, one > x. Then attach them ogether in the end. Not really O(1) space, due to recursive calls.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;
        return sortList(head, NULL);
    }
    //sort list and connect it to next, return new head
    ListNode* sortList(ListNode *head, ListNode *next) {
        ListNode* dummy = new ListNode(0);
        //use head as pivot. p : <x, q : >x, r : =x
        ListNode *phead = NULL, *qhead = NULL, *rhead = NULL;
        ListNode *p = NULL, *q = NULL, *r = head;
        ListNode *curr = head->next;
        while(curr) {
            if(curr->val < head->val) {
                if(!p) p = phead = curr;
                else p = p->next = curr;
            } else if(curr->val > head->val) {
                if(!q) q = qhead = curr;
                else q = q->next = curr;
            } else {
                r = r->next = curr;
            }
            curr = curr->next;
        }
        //work on first part (<x)
        if(phead) {
            p->next = NULL; //p is tail
            dummy->next = sortList(phead, head);
        } else dummy->next = head;
        //work on second part (>x)
        if(qhead) {
            q->next = NULL; //q is tail
            r->next = sortList(qhead, next);
        } else r->next = next;
        head = dummy->next;
        delete dummy;
        return head;
    }
};

// Solution 4. Bottom-up merge sort, using a queue. O(n) space!
// Sort is unstable if number of nodes are not power of 2!

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;
        deque<ListNode*> q;
        ListNode *p = head;
        //push nodes into queue, also set next to NULL (break into many single-node lists)
        while(p) {
            q.push_back(p);
            ListNode *next = p->next;
            p->next = NULL;
            p = next;
        }
        ListNode dum(0);
        p = &dum; //dummy node
        while(!q.empty()) {
            ListNode* n1 = q.front(); q.pop_front();
            if(q.empty()) return n1;
            ListNode *n2 = q.front(); q.pop_front();
            q.push_back(merge(n1, n2));
        }
        return NULL; //something wrong
    }
    //merge two sorted, non-empty lists
    ListNode* merge(ListNode *head1, ListNode *head2) {
        ListNode dum(0), *p(&dum), *tail(p);
        while(head1 && head2) {
            if(head1->val <= head2->val) {
                tail->next = head1;
                head1 = head1->next;
            } else {
                tail->next = head2;
                head2 = head2->next;
            }
            tail = tail->next;
        }
        tail->next = head1 ? head1 : head2;
        return p->next;
    }
};


/**************************************************** 
 ***    150,Medium,Evaluate Reverse Polish Notation 
 ****************************************************/

/*
Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Some examples:

  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
*/

/// Use a stack. Pushing numbers to stack. When seeing an operator, pop two numbers, operate, and put value back to stack.
/// caveat: when evaluating integer numbers, take care of possible positive/negative signs!

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        deque<int> st; //stack
        for(size_t i = 0; i < tokens.size(); ++i) {
            const string& str = tokens[i];
            if(str == "+" || str == "-" || str == "*" || str == "/") {
                 int num2 = st.back(); st.pop_back();
                 int num1 = st.back(); st.pop_back();
                 if(str == "+") st.push_back(num1+num2);
                 else if(str == "-") st.push_back(num1-num2);
                 else if(str == "*") st.push_back(num1*num2);
                 else if(str == "/") st.push_back(num1/num2);
            } else {
                 st.push_back(eval(str));
            }
        }
        return st.back();
    }
    int eval(const string& str) {
        int v = 0;
        int sign = 1;
        for(size_t i = 0; i < str.size(); ++i) {
            if(i == 0 && (str[i] == '-' || str[i] == '+')) sign = (str[i] == '+') ? 1 : -1;
            else v = v*10 + (str[i] - '0');
        }
        return sign*v;
    }
};

/**************************************************** 
 ***    151,Medium,Reverse Words in a String 
 ****************************************************/

/*
Given an input string, reverse the string word by word.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Update (2015-02-12):
For C programmers: Try to solve it in-place in O(1) space.

click to show clarification.
Clarification:

    What constitutes a word?
    A sequence of non-space characters constitutes a word.
    Could the input string contain leading or trailing spaces?
    Yes. However, your reversed string should not contain leading or trailing spaces.
    How about multiple spaces between two words?
    Reduce them to a single space in the reversed string.
*/

// Solution 1: kinda in-place. Procedure:
// 1. remove extra spaces and store the shorted string to s[0, end)
// 2. reverse substring s[0, end)
// 3. reverse individual string in s[0, end)
// Two pointers

class Solution {
public:
    void reverseWords(string &s) {
        if(s.empty()) return;
        int n = s.size();
        //1. remove extra spaces
        //end: end of shorted string, scan j
        int i = 0, j = 0;
        int beg = 0, end = 0;
        while(beg < n && s[beg] == ' ') beg++; 
        //beg points to first non-space char or end
        end = 0; //copy string to start
        for(j = beg; j < n; j++) {
            if(s[j] == ' ') continue;
            else { //non-space character, copy
                if(j > beg && s[j-1] == ' ') s[end++] = ' '; //add space
                s[end++] = s[j];
            }
        }
        //2. reverse substr string s[0, end)
        reverse(s, 0, end);
        
        //3. reverse individual words for s[0, end)
        for(i = 0; i < end; i++) {
            if(s[i] == ' ') continue;
            j = i+1;
            while(j < end && s[j] != ' ') j++;
            reverse(s, i, j); //j points to space or s.end()
            i = j;
        }
        s = s.substr(0, end); //copy result to s (can handle end = 0 case)
    }

    //reverse s[lo, hi)
    void reverse(string &s, int lo, int hi) {
        hi--;
        while(lo < hi) {
            char c = s[lo];
            s[lo] = s[hi];
            s[hi] = c;
            lo++; hi--;
        }
    }
};

// Solution 2: Use an auxiliary string vector
// Caveat: size_t i = str.size()-1 is wrong! because it will fail when str is empty(), use int i instead.

class Solution {
public:
    void reverseWords(string &s) {
        vector<string> strs;
        split(s, strs);
        s.clear();
        for (int i = strs.size()-1; i >= 0; i--) {
            s += strs[i];
            if(i > 0) s += " ";
        }
    }
    void split(string& s, vector<string>& strs) {
        s += " ";
        string word;
        for(size_t i = 0; i < s.size(); ++i) {
            char c = s[i];
            if(c != ' ') word += c;
            else if(word != "") {
                strs.push_back(word);
                word = "";
            }
        }
    }
};

/**************************************************** 
 ***    152,Medium,Maximum Product Subarray 
 ****************************************************/

/*
Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6. 
*/

// DP solution.
// Keep track of maximum (in terms of absolute value) positive and negative values (initially set as 0)
// Update the values based on the polarity of newly seen element. If max_pos_prod and max_neg_prod are 0, then they are considered uninitialized.
// Caveat: When updating max_pos and max_neg, need to use temporary variables
// Optimization: since we call nums[i] multiply times, save it into a variable x to avoid excessive array indexing cost.

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        int max_pos_prod = 0, max_neg_prod = 0, max_prod = INT_MIN;
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            if(x == 0) {
                max_prod = max(max_prod, 0);
                max_pos_prod = max_neg_prod = 0;
            } else if(x > 0) {
                max_pos_prod = (max_pos_prod > 0) ? max_pos_prod*x : x;
                max_neg_prod = (max_neg_prod < 0) ? max_neg_prod*x : 0;
            } else { //nums[i] < 0
                int tmp_pos = max_pos_prod, tmp_neg = max_neg_prod;
                max_pos_prod = (tmp_neg < 0) ? tmp_neg*x : 0;
                max_neg_prod = (tmp_pos > 0) ? tmp_pos*x : x;
            }
            if(max_pos_prod > 0 && max_prod < max_pos_prod) max_prod = max_pos_prod;
            if(max_neg_prod < 0 && max_prod < max_neg_prod) max_prod = max_neg_prod; //needed for n=1 case with one negative number (max_pos undefined)
        }
        return max_prod;
    }
};

// A slightly different solution, considering n=1 corner case explicitly (so that max_pos will always be valid)
// Corner case: when there is only one negative number, should return itself, not 0.

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0]; //corner case
        int max_pos(0), max_neg(0), max_prod(0);
        int tmp_pos(0), tmp_neg(0);
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            if(x == 0) tmp_pos = tmp_neg = 0;
            else if (x > 0) {
                tmp_pos = (max_pos > 0) ? max_pos*x : x;
                tmp_neg = (max_neg < 0) ? max_neg*x : 0;
            } else {  //x < 0
                tmp_pos = (max_neg < 0) ? max_neg*x : 0;
                tmp_neg = (max_pos > 0) ? max_pos*x : x;
            }
            max_pos = tmp_pos; max_neg = tmp_neg;
            max_prod = max(max_prod, max_pos);
        }
        return max_prod;
    }
};

/**************************************************** 
 ***    153,Medium,Find Minimum in Rotated Sorted Array 
 ****************************************************/

/*
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

You may assume no duplicate exists in the array.
*/

/*
General solution that also works for duplicated cases.
Binary search. The array can be broken into two parts, 
for example, [4 5 6 7 0 1 2], first part is 4-7, second part is 0-2. If array is unrotated, then only first part exists (corner case). 

There are three anchor points, lo, hi, and mid. Compare nums[mid] with nums[hi].
1. If nums[mid] < nums[hi], then we know for sure that minimum lies on or before mid, so hi = mid (we excluding nums[mid+1, hi]).
2. If nums[mid] > nums[hi], then we know for sure that mid is in first part of array, and array is rotated. This means that minimum lies between mid and hi, so lo = mid+1. Since nums[mid] > nums[hi], nums[mid] cannot be the minimum, so we can exlude it. 
3. If nums[mid] = nums[hi], we can't say where mid lies. It could be left or right. But we can safely exclude nums[hi], since it is a duplicated entry apart from nums[mid]. Thus we simply decrement hi. 
*/

class Solution {
public:
    int findMin(vector<int>& nums) {
        int lo = 0, hi = nums.size()-1;
        int mid = 0;
        //invariant: [lo, hi] contains minimum
        while(lo < hi) {
            mid = lo + (hi-lo)/2;
            if(nums[mid] < nums[hi]) hi = mid;
            else if(nums[mid] > nums[hi]) lo = mid+1;
            else hi--;
        }
        return nums[lo];
    }
};

/**************************************************** 
 ***    156,Medium,Binary Tree Upside Down 
 ****************************************************/

/*
Given a binary tree where all the right nodes are either leaf nodes with a sibling (a left node that shares the same parent node) or empty, flip it upside down and turn it into a tree where the original right nodes turned into left leaf nodes. Return the new root.

For example:
Given a binary tree {1,2,3,4,5},
    1
   / \
  2   3
 / \
4   5
return the root of the binary tree [4,5,2,#,#,3,1].
   4
  / \
 5   2
    / \
   3   1  
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution. Rememeber to set root's child pointers to NULL!

class Solution {
public:
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        if(!root) return NULL;
        if(!root->left) return root;
        TreeNode * newRoot = upsideDownBinaryTree(root->left);
        root->left->left = root->right;
        root->left->right = root;
        root->left = root->right = NULL;
        return newRoot;
    }
};

/**************************************************** 
 ***    161,Medium,One Edit Distance 
 ****************************************************/

/*
Given two strings S and T, determine if they are both one edit distance apart.
*/

/*
one pass solution. Two pointers scanning two arrays.
For s[i] and t[j], If found equal, move forward,
if not equal, then the rest should be the same, three cases:
a) remove s[i] and the rest matches, so we just check isSame for s[i+1, m) and t[j, n). e.g.
   abc[de]   ab[de]
     i          j
b) insert t[j] and the rest matches, so we just check isSame for s[i, m) and t[j+1, n) e.g
   ab[efg]   abd[efg]
      i        j
c) replace s[i] with t[j] and the rest matches, so we just check isSame for s[i+1, m) and t[j+1, n) e.g.
   abe[fg]   abc[fg]
     i         j

Finally, if we break out of loop, which means everything seen so far is matched. We simply check if we still have one and only one unchecked character in either one of the two arrays.

*/

class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int m = s.size(), n = t.size();
        if(m - n < -1 || m -n > 1) return false;
        int i = 0, j = 0;
        while(i < m && j < n) {
            if(s[i] == t[j]) { i++; j++; }
            else return isSame(s, i+1, t, j) || isSame(s, i, t, j+1) || isSame(s, i+1, t, j+1);
        }
        return j == n-1 || i == m-1;
    }
    bool isSame(const string& s, int i, const string& t, int j) {
        int m = s.size(), n = t.size();
        while(i < m && j < n) {
            if(s[i] != t[j]) return false;
            i++; j++;
        }
        return i == m && j == n;
    }
};


/**************************************************** 
 ***    162,Medium,Find Peak Element 
 ****************************************************/

/*
A peak element is an element that is greater than its neighbors.

Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.

You may imagine that num[-1] = num[n] = -∞.

For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.

click to show spoilers.
Note:

Your solution should be in logarithmic complexity.
*/

// Solution 1. Simple binary search. compare mid with mid+1. break when lo == hi.

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        int lo = 0, hi = n-1;
        while(lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if(nums[mid] < nums[mid+1]) lo = mid+1;
            else hi = mid;
        }
        return lo;
    }
};

// Solution 2. Variant of solution 1. Slightly more complicated. Need to compare mid with mid-1 and mid+1.

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        if(nums.empty()) return -1;
        int n = nums.size();
        if(n == 1) return 0;
        if(nums[0] > nums[1]) return 0;
        if(nums[n-1] > nums[n-2]) return n-1;
        int lo = 1, hi = n-2;
        while(lo < hi) {
            int mid = lo + (hi-lo)/2;
            if(nums[mid] > nums[mid-1] && nums[mid] > nums[mid+1]) return mid;
            else if(nums[mid] < nums[mid-1]) hi = mid-1;
            else lo = mid+1;
        }
        return lo;
    }
};


/**************************************************** 
 ***    163,Medium,Missing Ranges 
 ****************************************************/

/*
Given a sorted integer array where the range of elements are [lower, upper] inclusive, return its missing ranges.

For example, given [0, 1, 3, 50, 75], lower = 0 and upper = 99, return ["2", "4->49", "51->74", "76->99"]. 
*/

// First locate the lower and upper in the array, using binary search.
// Then linearly scan the portion of array that falls into [lower, upper], and check missing ranges.

class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<string> ret;
        int i(0), j(0);
        int n = nums.size();
        int lo(0), hi(n-1), mid(0);
        //i is first element >= lower
        while(lo <= hi) {
           mid = lo + (hi-lo)/2;
           if(nums[mid] < lower) lo++;
           else hi--;
        }
        i = lo;
        lo = 0, hi = n-1;
        //j is last element <= upper
        while(lo <= hi) {
           mid = lo + (hi-lo)/2;
           if(nums[mid] > upper) hi--;
           else lo++;
        }
        j = hi;

        if(i > j) { //array is outside of [lower, upper]
            appendRange(ret, lower, upper);
            return ret;
        }
        //insert
        appendRange(ret, lower, nums[i]-1);
        for(int k = i; k < j; ++k) {
            appendRange(ret, nums[k]+1, nums[k+1]-1);
        }
        appendRange(ret, nums[j]+1, upper);
        return ret;
    }
    void appendRange(vector<string>& ret, int lo, int hi) {
        if(lo == hi) ret.push_back(num2str(lo));
        else if(lo < hi) ret.push_back(num2str(lo) + "->" + num2str(hi));
    }
    string num2str(int num) {
        if(num == 0) return "0";
        string s;
        int sign = num >= 0 ? 1 : -1;
        num = abs(num);
        while(num) {
            s = char(num%10 + '0') + s;
            num /= 10;
        }
        if(sign < 0) s = "-" + s;
        return s;
    }
};


/**************************************************** 
 ***    166,Medium,Fraction to Recurring Decimal 
 ****************************************************/

/*
Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

For example,

    Given numerator = 1, denominator = 2, return "0.5".
    Given numerator = 2, denominator = 1, return "2".
    Given numerator = 2, denominator = 3, return "0.(6)".
*/

// Use a table to track the first occuring position of residue, add corresponding quotient to decimal string, also take care of sign
// caveat: use long for all integer variables to avoid integer overflow!

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        long a = numerator, b = denominator; //use long to avoid overflow!
        bool negative = (a < 0 && b > 0) || (a > 0 && b < 0);
        a = abs(a), b = abs(b); //get absolute value
        long q = a / b, r = a % b;
        string integer = int2str(q);
        if(negative) integer = '-' + integer;
        if(r == 0) return integer;
        
        string decimal;
        int i = 0; //position of decimal
        unordered_map<long, int> table; // the place in decimal that a given r value has appeared the first time
        do {
            q = (r*10) / b;
            if(!table.count(r)) { // not found
                table[r] = i;
                decimal += char(q + '0');
            } else { //found!
                int j = table[r];
                decimal.insert(j, "(");
                decimal += ")";
                break;
            }
            r = (r*10) % b; //update r
            i++; //update i
        } while(r);
        return integer + "." + decimal;
    }

    string int2str(long val) {
        string s;
        do {
            s = char(val % 10 + '0') + s;
            val /= 10;
        } while(val);
        return s;
    }
};

/**************************************************** 
 ***    167,Medium,Two Sum II - Input array is sorted 
 ****************************************************/

/*
Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2 
*/

// Solution: two pointers, linear search. Time O(n), space O(1).

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
      vector<int> ret(2, -1);
      int n = numbers.size();
      int i = 0, j = n-1;
      while(i < j) {
        int sum = numbers[i] + numbers[j];
        if(sum > target) j--;
        else if(sum < target) i++;
        else {
          ret[0] = i+1; ret[1] = j+1;
          return ret;
        }
      }
      return ret;
    }
};

/**************************************************** 
 ***    173,Medium,Binary Search Tree Iterator 
 ****************************************************/

/*
Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree. 
*/

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */

// Push all left spline to a stack.
// When popping, it a node has right subtree, push all left spline of the right child.

class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        pushLeft(root, s);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !s.empty();
    }

    /** @return the next smallest number */
    int next() {
        TreeNode *node = s.back();
        int val = node->val;
        s.pop_back();
        if(node->right) pushLeft(node->right, s);
        return val;
    }
private:
    void pushLeft(TreeNode *root, deque<TreeNode*>& s) {
        while(root) {
            s.push_back(root);
            root = root->left;
        }
    }
    deque<TreeNode*> s; //stack
};


/**************************************************** 
 ***    179,Medium,Largest Number 
 ****************************************************/

/*
Given a list of non negative integers, arrange them such that they form the largest number.

For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.

Note: The result may be very large, so you need to return a string instead of an integer.
*/

// Write a customized comparator function to compare two integer string, compare a+b v.s. b+a;
// An improved version from comparing integers, where we need to do int=>string conversions many times.
// Use a comparator class. can also define a bool compare function outside the class.

// Caveats:
// Corner case where nums are filled with "0"s, so we need to check if first character of result is zero.

class Solution {
public:
    struct myClass {
        bool operator() (const string& a, const string& b) {
            return a + b < b + a;
        }
    } compare;

    string largestNumber(vector<int>& nums) {
        string res;
        //assemble res from reverse iteration
        int n = nums.size();
        vector<string> strs(n);
        for(int i = 0; i < n; ++i)  strs[i] = num2str(nums[i]);

        sort(strs.begin(), strs.end(), compare);
        
        for(int i = n-1; i >= 0; --i) {
            res += strs[i];
        }
        if(res[0] == '0') return "0";
        else return res;
    }
    
    string num2str(int num) {
        if(num == 0) return "0";
        string res;
        while(num) {
            int d = num % 10;
            res = char(d + '0') + res;
            num /= 10;
        }
        return res;
    }
};

/**************************************************** 
 ***    186,Medium,Reverse Words in a String II 
 ****************************************************/

/*
Given an input string, reverse the string word by word. A word is defined as a sequence of non-space characters.

The input string does not contain leading or trailing spaces and the words are always separated by a single space.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Could you do it in-place without allocating extra space?

Related problem: Rotate Array
*/

// Solution: first reverse the whole string, then scan left to right to reverse each individual words.
// Two pointers.

class Solution {
public:
    void reverseWords(string &s) {
        int n = s.size();
        if(n <= 1) return;
        reverse(s, 0, n);
        int i = 0, j = 0;
        for(int i = 0; i < n;) {
            j = i+1;
            while(j < n && s[j] != ' ') j++;
            reverse(s, i, j); //j points to space
            i = j+1;
        }
    }
    //reverse s[lo, hi)
    void reverse(string &s, int lo, int hi) {
        hi--;
        while(lo < hi) {
            char c = s[lo];
            s[lo] = s[hi];
            s[hi] = c;
            lo++; hi--;
        }
    }
};

/**************************************************** 
 ***    187,Medium,Repeated DNA Sequences 
 ****************************************************/

/*
All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

For example,

Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",

Return:
["AAAAACCCCC", "CCCCCAAAAA"].
*/

/// Use a hash code for the length-10 substring. 3 digit code for each character, so that a total of 30 digits, 
/// which can be represented by an integer (32 bits). 
/// Only 4 characters occuring, 'A', 'C', 'G', 'T' has different last three digits, thus use last three digits (c & 0b111)
/// First calculate the hash code for the first 9 digit, when we add a new digit, we multiply by 8 (radix-8 hash code), or
/// equivalently, << 3. How to strip off the highest character when moving to next? Notice that we only have 30 bits, and 
/// we simply turn off the highest 2 bits, so that we mask with Ox3FFFFFFF.

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> ret;
        int n = s.size();
        if(n < 10) return ret;
        map<int, int> count;
        int hash = 0;
        for(int i = 0; i < 9; ++i) {
            hash = (hash << 3) | (s[i] & 7);
        }
        for(int i = 9; i < n; ++i) {
            hash = ((hash << 3) & 0x3FFFFFFF) | (s[i] & 7);
            count[hash]++;
            if(count[hash] == 2) ret.push_back(s.substr(i-9, 10));
        }
        return ret;
    }
};

/// Similar approach to solution 1, except we use 2-digit code for each character, thus resulting in 20-bit hash code for 
/// the substring, represented by an integer (32 bits). 
/// Use a function to return the hash code for the 4 characters, we only requires 2 bits. We can use a trick to return the hash value:
/// hash = (s[i] - 'A' + 1) % 5. This way, ACGT returns 1 3 2 0 respectively.

/// First calculate the hash code for the first 9 digit, when we add a new digit, we multiply by 4 (radix-4 hash code), or
/// equivalently, << 2. How to strip off the highest character when moving to next? Notice that we only have 20 bits, and 
/// we simply turn off the highest 12 bits, so we mask with Ox000FFFFF.

// Another optimization is to use an array to store the hash table (can use char if counts are less than 256 to save space). Note that using vector<int> increases runtime from 20 ms to 100 ms. But using vector<char> is only 12 ms.

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> result;
        char dict[1048576] = {0}; //hash => counts (assume counts < 256).
        int n = s.size();
        const int LEN = 10;
        if(n <= LEN) return result;
        int hashval = 0;
        for(int i = 0; i < LEN-1; ++i) {
            hashval = (hashval << 2) | (s[i] - 'A' + 1) % 5;
        }
        for(int i = LEN-1; i < n; ++i) {
            //remove two leading bits, and shift to right by two and add next hash value
            hashval = ((hashval << 2) & 0x000FFFFF) | (s[i] - 'A' + 1) % 5;
            if(dict[hashval]++ == 1) result.push_back(s.substr(i-LEN+1, LEN));
        }
        return result;
    }
};


/**************************************************** 
 ***    199,Medium,Binary Tree Right Side View 
 ****************************************************/

/*
Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

For example:
Given the following binary tree,
   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
You should return [1, 3, 4].
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
 /// Solution 1. Level order traversal using two vectors (curr, next). When getting the last element of curr, insert it to result.

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        vector<TreeNode*> curr, next;
        curr.push_back(root);
        while(!curr.empty()) {
            int n = curr.size();
            for(int i = 0; i < n; i++) {
                TreeNode* node = curr[i];
                if(node->left)  next.push_back(node->left);
                if(node->right) next.push_back(node->right);
                if(i == n-1) result.push_back(node->val);
            }
            curr.swap(next);
            next.clear();
        }
        return result;
    }
};

 /// Solution 2. Level order traversal. We encounter the rightmost element at each level in two cases:
 /// (a) there's no element in the queue (queue empty)
 /// (b) the next element in the queue has higher level
 
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        queue<int> lq;
        queue<TreeNode*> nq;
        vector<int> ret;
        if(root == NULL) return ret;
        nq.push(root); lq.push(0);
        while(!nq.empty()) {
            TreeNode *node = nq.front(); nq.pop();
            int level = lq.front(); lq.pop();
            if(node->left) {
                nq.push(node->left);
                lq.push(level+1);
            }
            if(node->right) {
                nq.push(node->right);
                lq.push(level+1);
            }
            if(lq.empty() || lq.front() > level) ret.push_back(node->val);
        }
        return ret;
    }
};

/**************************************************** 
 ***    200,Medium,Number of Islands 
 ****************************************************/

/*
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:

11110
11010
11000
00000

Answer: 1

Example 2:

11000
11000
00100
00011

Answer: 3
*/

//Solution 1: Standard DFS
// Note that we have to check 4 neighbors! Only checking right and bottom is not enough! See the case below:

// 1 1 1
// 0 1 0
// 1 1 1
// Starting from left top corner, if only checking 2 neighbors, we missed the bottom left one, and we end up count = 2.

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        int count = 0;
        for(int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(grid[i][j] == '1') {
                    dfs(grid, i, j);
                    count++;
                }
            }
        }
        return count;
    }
    void dfs(vector<vector<char> >& grid, int i, int j) {
        grid[i][j] = '0';
        //check 4 neighbors
        if(i > 0 && grid[i-1][j] == '1') dfs(grid, i-1, j); //top
        if(j > 0 && grid[i][j-1] == '1') dfs(grid, i, j-1); //left
        if(i < grid.size()-1    && grid[i+1][j] == '1') dfs(grid, i+1, j); //bottom
        if(j < grid[i].size()-1 && grid[i][j+1] == '1') dfs(grid, i, j+1); //right
    }
};

// Solution 2: BFS using a queue
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        int count = 0;
        for(int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(grid[i][j] == '1') {
                    bfs(grid, i, j);
                    count++;
                }
            }
        }
        return count;
    }
    void bfs(vector<vector<char> >& grid, int i, int j) {
        deque<pair<int, int> > q;
        q.push_back(make_pair(i, j)); 
        grid[i][j] = '0';
        while (!q.empty()) {
            int ni = q.front().first;
            int nj = q.front().second;
            q.pop_front();
            //check 4 neighbors
            if(ni > 0 && grid[ni-1][nj] == '1') { grid[ni-1][nj] = '0'; q.push_back(make_pair(ni-1, nj)); } //top
            if(nj > 0 && grid[ni][nj-1] == '1') { grid[ni][nj-1] = '0'; q.push_back(make_pair(ni, nj-1)); } //left
            if(ni < grid.size()-1    && grid[ni+1][nj] == '1') { grid[ni+1][nj] = '0'; q.push_back(make_pair(ni+1, nj)); } //bottom
            if(nj < grid[ni].size()-1 && grid[ni][nj+1] == '1') { grid[ni][nj+1] = '0'; q.push_back(make_pair(ni, nj+1)); } //right
        }
    }
};

// Solution 3: Union find.
// Record the total number of disjoint sets. m*n elements, initially all inactive. Scan the grid, when finding a '1', mark the element as active, and set its id and size attributes in UnionFind class. Maintain a conversion formula from 2D positions to 1D index (i*n+j).
// Use weighted union find with path compression, close to O(n) time complexity.
// Caveats:
// 1. 1D index is i*n+j, not i*m+j!
// 2. we need to check left and top neighbors, can skip bottom and right neighbors. Since we are scanning strictly top-down, left-right. 

class UnionFind {
public:
    UnionFind(int N) : n(0) {
        id.resize(N, -1);
        size.resize(N, 0);
    }
    //add element i as a new set
    void add(int i) {
        id[i] = i;
        size[i] = 1;
        n++;
    }
    //unite two elements
    void unite(int i, int j) {
        while(id[i] != i) { id[i] = id[id[i]]; i = id[i]; }
        while(id[j] != j) { id[j] = id[id[j]]; j = id[j]; }
        if(i != j) {
            if(size[i] < size[j]) { id[i] = j; size[j] += size[i]; }
            else { id[j] = i; size[i] += size[j]; }
            n--;
        }
    }

    int count() const { return n; }

private:
    vector<int> id; //set id
    vector<int> size; //size of each set
    int n; //total number of sets
};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        UnionFind uf(m*n);
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(grid[i][j] == '0') continue;
                int idx = i*n+j;
                uf.add(idx); //add to sets
                if(i > 0 && grid[i-1][j] == '1')  //top neighbor
                    uf.unite(idx, idx-n);
                if(j > 0 && grid[i][j-1] == '1') //left neighbor
                    uf.unite(idx, idx-1);
            }
        }
        return uf.count();        
    }
};


/**************************************************** 
 ***    201,Medium,Bitwise AND of Numbers Range 
 ****************************************************/

/*
Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.

For example, given the range [5, 7], you should return 4.
*/


/* If we search from highest bits to lowest bits, the result should have the same bit if m and n have the same bit, 
and once we encountered the first different bit, then all the bits in result on and after this bit should be zero. 
The reason is as follows. Suppose the first different bit is at i, then m[i] should be 0 and n[i] should be 1 (m <=n), 
then the numbers ..011111 and ..100000 should be between m and n, and it will give all zeros after AND operations. 
Thus, the key is to find the highest set bit of m^n, and use ~(m^n-1) as the mask.
Also works for m == n case, where m_and = m, and m_xor = 0, the return value is thus m & ~0 = m & 1111111 = m
*/
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int m_and = m & n;
        int m_xor = m ^ n;
        //mask is the number from highest bit of mask2 minus 1 (i.e. 0011111..)
        int mask;
        while(m_xor) { //each loop removes a rightmost set bit of m_xor
            mask = m_xor-1;
            m_xor = m_xor & mask;
        }
        //after loop, m_xor is 0, and mask is of form 00111..
        return m_and & (~mask);
    }
};

// Solution 2. Shift m and n until they are equal. Record the number of shifts, and shift m back.

class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int i = 0;
        while(m != n) {
            i ++;
            m >>= 1;
            n >>= 1;
        }
        return m << i;
    }
};

// Solution 3.
// Alternative solution by shifting bits. For explanations refer to the first solution.

class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        if(m == n || n == 0) return n;
        int ret = 0;
        unsigned int i = 0x80000000; //1000...
        while(i) {
            if ((m ^ n) & i) break; //m and n's bits differ at that bit
            else ret = ret | (m & i); //bit the same, copy m's bit to result
            i >>= 1; //move one bit lower
        }
        return ret;
    }
};

/**************************************************** 
 ***    207,Medium,Course Schedule 
 ****************************************************/

/*
There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

For example:

2, [[1,0]]

There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.

2, [[1,0],[0,1]]

There are a total of 2 courses to take. To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.

click to show more hints.
Hints:

    This problem is equivalent to finding if a cycle exists in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
    Topological Sort via DFS - A great video tutorial (21 minutes) on Coursera explaining the basic concepts of Topological Sort.
    Topological sort could also be done via BFS.
*/

// Solution using graph cycle-detection using dfs

class Graph {
public:
    Graph(int NN) : N(NN) {
        adj.resize(N);
    }
    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }
    int NV() const { return N; }
    const vector<int>& neighbors(int v) const { return adj[v]; }
private:
    int N; //number of vertices
    vector<vector<int> > adj; //adjacency lists
};

class CycleDetector {
public:
    CycleDetector(const Graph& gg): g(gg), hasCycle(false) {
        status.resize(g.NV(), 0);
    }
    //detect cycle using dfs, immediately return if found cycle
    bool detectCycle() { 
        for(int v = 0; v < g.NV() && !hasCycle; v++) {
            if(status[v] == 0) dfs(v);
        }
        return hasCycle;
    }
private:
    void dfs(int v) {
        status[v] = 1; //on stack
        for(auto w : g.neighbors(v)) {
            if(hasCycle) return; //found cycle, just return
            if(status[w] == 1) { hasCycle = true; return; } //found cycle!
            else if(status[w] == 0) dfs(w); //unvisited, visit
        }
        status[v] = 2; //finished
    }
    const Graph& g;
    bool hasCycle; //has cycle
    vector<int> status; //vertex status during dfs (0: unvisited, 1: onstack, 2: finished)
};

class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        //construct directed graph
        Graph g(numCourses);
        for(auto c : prerequisites) 
            g.addEdge(c.second, c.first);
        //detect cycle using dfs
        CycleDetector det(g);
        return !det.detectCycle();
    }
};


/**************************************************** 
 ***    208,Medium,Implement Trie (Prefix Tree) 
 ****************************************************/

/*
Implement a trie with insert, search, and startsWith methods.

Note:
You may assume that all inputs are consist of lowercase letters a-z. 
*/

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");

/// Solution 1. Follows the Java implementation from the Sedgewick book.
/// The character we are currently at does not correpsond to the node itself, but one of its links!

/// When we do search(x, str, d), we are actually looking for x->next[str[d]] !, 
/// e.g. ab , when d == 0, we search character 'a' in the first link of root.
/// Then we search b in the second link of node 'a'. When we arrive b, we have d == 2, pointing to str.end(). then we check if b is a key.
/// When d reaches one past the end of str, return the node we are currently at.
/// If we encountered a NULL node before that, we simply return null.

/// When we do insert(x, str, d), we are actually inserting str[d] to the associated next link of the node x.
/// e.g. inserting ab to empty trie. first insert(root, "ab", 0), which directly goes to root->next[0], and we have 
/// insert(root->next[0], "ab", 1), we first need to create the node corresponding to 'a' (this node is pointed by the first link of root)
/// in the last step, so it is interpreted as 'a'. Then we should check its second link for 'b'. We then call
/// insert(a_node->next[1], "ab", 2), we again need to create one, then as d reaches the end, we set isKey to true, and then return the node (not its links)
/// When not reaching the end, we need to recursively call the insert of its links, and return the new link address. We finally return the node x.

class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() {
        isKey = false;
        for(int i = 0; i < 26; i++) next[i] = NULL;
    }
    bool isKey;
    TrieNode* next[26];
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
        root = insert(root, word, 0);
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode * node = search(root, word, 0);
        return node != NULL && node->isKey;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode* node = search(root, prefix, 0);
        return node != NULL;
    }

private:
    TrieNode* insert(TrieNode* x, const string& word, int d) {
        if(x == NULL) x = new TrieNode;
        if(d == word.size()) { x->isKey = true; return x; }
        int idx = word[d] - 'a';
        x->next[idx] = insert(x->next[idx], word, d+1);
        return x;
    }
    TrieNode* search(TrieNode* x, const string& word, int d) {
        if(x == NULL) return NULL;
        if(d == word.size()) return x;
        int idx = word[d] - 'a';
        return search(x->next[idx], word, d+1);
    }
    TrieNode* root;
};

/// Solution 2. Slightly simpler, make sure search and insert will never encounter null nodes, can remove the check of x == NULL.
/// this also reduces stack depth by one (no need to descend in to a null node), and easier to comprehend.

class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() {
        isKey = false;
        for(int i = 0; i < 26; i++) next[i] = NULL;
    }
    bool isKey;
    TrieNode* next[26];
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
        insert(root, word, 0);
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode * node = search(root, word, 0);
        return node != NULL && node->isKey;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode* node = search(root, prefix, 0);
        return node != NULL;
    }

private:
    void insert(TrieNode* x, const string& word, int d) {
        if(d == word.size()) { x->isKey = true; return; }
        //if link not exist, create it before descending
        int idx = word[d] - 'a';
        if(x->next[idx] == NULL) x->next[idx] = new TrieNode;
        insert(x->next[idx], word, d+1);
    }
    TrieNode* search(TrieNode* x, const string& word, int d) {
        if(d == word.size()) return x;
        int idx = word[d] - 'a';
        //if link is null, return null;
        if(x->next[idx] == NULL) return NULL;
        return search(x->next[idx], word, d+1);
    }
    TrieNode* root;
};

/// Solution 3, with delete function (which slows down runtime by 40 ms!)

class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() {
        isKey = false;
        links.resize(26, NULL);
    }

    bool isKey;
    vector<TrieNode*> links;
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        eraseUtil(root);
    }
    // Inserts a word into the trie.
    void insert(string word) {
        insertUtil(root, word, 0);
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode* node = searchUtil(root, word, 0);
        return node != NULL && node->isKey;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode* node = searchUtil(root, prefix, 0);
        return node != NULL;
    }

private:
    //root can never be NULL
    void insertUtil(TrieNode* root, const string& word, int i) {
        if(i == word.size()) { root->isKey = true; return; }
        int c = word[i] - 'a';
        if(!root->links[c]) root->links[c] = new TrieNode();
        insertUtil(root->links[c], word, i+1);
    }
    TrieNode* searchUtil(TrieNode* root, const string& word, int i) {
        if(root == NULL) return NULL;
        if(i == word.size()) return root;
        int c = word[i] - 'a';
        return searchUtil(root->links[c], word, i+1);
    }
    void eraseUtil(TrieNode* root) {
        if(!root) return;
        for(int c = 0; c < 26; ++c) eraseUtil(root->links[c]);
        delete root;
    }
    TrieNode* root;
};


/**************************************************** 
 ***    209,Medium,Minimum Size Subarray Sum 
 ****************************************************/

/*
Given an array of n positive integers and a positive integer s, find the minimal length of a subarray of which the sum ≥ s. If there isn't one, return 0 instead.

For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.

click to show more practice.
More practice:

If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n).
*/

/// Solution 1: sliding window. Move one step further to optimize. O(n)

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        int sum = 0, minL = INT_MAX;
        for(int i = 0, istart = 0; i < n; ++i) {
            sum += nums[i];
            if(sum < s) continue;
            while(sum - nums[istart] >= s) {
                sum -= nums[istart++];
            }
            minL = min(minL, i-istart+1);
            sum -= nums[istart++]; //move one step further
        }
        return minL != INT_MAX ? minL : 0;
    }
};

/// Solution 2: binary search on the accumulative sums. O(nlogn)
// First create the partial sum array, then scan the sum, if the paritial_sum >= s, then we search for the array before the element and find the largest element <= (partial_sum - s). Use binary search
// Since all numbers are positive, if we see partial_sum == s, we can skip the binary search and use i+1 as the length (can't be shorter than nums[0..i].

/// So far, divide and conquer seems not possible...

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if(nums.empty()) return 0;
        //get partial sums
        int n = nums.size();
        vector<int> partial(n, 0);
        partial[0] = nums[0];
        int minL = INT_MAX;
        for(int i = 1; i < n; ++i) {
            partial[i] = partial[i-1] + nums[i];
        }
        for(int i = 0; i < n; ++i) {
            if(partial[i] >= s) {
                //binary search for largest number <= residue in sums[0, i-1];
                int residue = partial[i] - s;
                int lo = 0, hi = i-1, mid = 0;
                while(lo <= hi) {
                    mid = lo + (hi - lo) / 2;
                    if(partial[mid] <= residue) lo = mid+1;
                    else hi = mid-1;
                }
                minL = min(minL, i-hi);
            }
        }
        return minL == INT_MAX ? 0 : minL;
    }
};


/**************************************************** 
 ***    210,Medium,Course Schedule II 
 ****************************************************/

/*
There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.

For example:

2, [[1,0]]

There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1]

4, [[1,0],[2,0],[3,1],[3,2]]

There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. Another correct ordering is[0,2,1,3].

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.

click to show more hints.
Hints:

    This problem is equivalent to finding the topological order in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
    Topological Sort via DFS - A great video tutorial (21 minutes) on Coursera explaining the basic concepts of Topological Sort.
    Topological sort could also be done via BFS.
*/

// Solution using topological sort with dfs

class Graph {
public:
    Graph(int NN) : N(NN) {
        adj.resize(N);
    }
    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }
    int NV() const { return N; }
    const vector<int>& neighbors(int v) const { return adj[v]; }
private:
    int N; //number of vertices
    vector<vector<int> > adj; //adjacency lists
};

class TopoSort {
public:
    TopoSort(const Graph& gg): g(gg), hasCycle(false) {
        status.resize(g.NV(), 0);
    }
    //detect cycle using dfs, immediately return if found cycle
    void sort() { 
        for(int v = 0; v < g.NV() && !hasCycle; v++) {
            if(status[v] == 0) dfs(v);
        }
    }
    vector<int> getOrder() {
        vector<int> result;
        if(hasCycle) return result;
        result = order;
        reverse(result.begin(), result.end());
        return result;
    }
private:
    void dfs(int v) {
        status[v] = 1; //on stack
        for(auto w : g.neighbors(v)) {
            if(hasCycle) return; //found cycle, just return
            if(status[w] == 1) { hasCycle = true; return; } //found cycle!
            else if(status[w] == 0) dfs(w); //unvisited, visit
        }
        status[v] = 2; //finished
        order.push_back(v); //push after finished
    }
    const Graph& g;
    bool hasCycle; //has cycle
    vector<int> status; //vertex status during dfs (0: unvisited, 1: onstack, 2: finished)
    vector<int> order; //topological order
};

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        //construct directed graph
        Graph g(numCourses);
        for(auto c : prerequisites) 
            g.addEdge(c.second, c.first);
        //detect cycle using dfs
        TopoSort ts(g);
        ts.sort();
        return ts.getOrder();
    }
};


/**************************************************** 
 ***    211,Medium,Add and Search Word - Data structure design 
 ****************************************************/

/*
Design a data structure that supports the following two operations:

void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.

For example:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
Note:
You may assume that all words are consist of lowercase letters a-z.
*/

// Your WordDictionary object will be instantiated and called as such:
// WordDictionary wordDictionary;
// wordDictionary.addWord("word");
// wordDictionary.search("pattern");

/// Use a trie as underlying data-structure, search function now returns boolean, and supports checking wildcard '.'
/// if new character is normal a-z, do normal search, otherwise it is a '.', then check all non-null next links

class TrieNode {
public:
    TrieNode() : isKey(false) {
        for(int i = 0; i < 26; i++) next[i] = NULL;
    }
    bool isKey;
    TrieNode* next[26];
};

class Trie {
public:
    Trie() { root = new TrieNode; }
    
    void insert(const string& word) {
        insert(root, word, 0);
    }
    bool search(const string& word) {
        return search(root, word, 0);
    }
    
private:
    void insert(TrieNode *x, const string& word, int d) {
        if(d == word.size()) { x->isKey = true; return; }
        int idx = word[d] - 'a';
        if(x->next[idx] == NULL) x->next[idx] = new TrieNode;
        insert(x->next[idx], word, d+1);
    }
    //x will never be null
    bool search(TrieNode *x, const string& word, int d) {
        if(d == word.size()) return x->isKey;
        if(word[d] != '.') {
            int idx = word[d] - 'a';
            return (x->next[idx] && search(x->next[idx], word, d+1));
        } else {
            for(int idx = 0; idx < 26; idx++) {
                if(x->next[idx] && search(x->next[idx], word, d+1)) return true;
            }
            return false;
        }
    }
    TrieNode* root;
};

class WordDictionary {
public:
    WordDictionary() : t() {}
    // Adds a word into the data structure.
    void addWord(string word) {
        t.insert(word);
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        return t.search(word);
    }
    Trie t;
};

/**************************************************** 
 ***    213,Medium,House Robber II 
 ****************************************************/

/*
Note: This is an extension of House Robber.

After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
*/

// One pass DP solution. Use two variables, one meaning maximum including first house, second meaning maximum excluding first house.
// Special treatment for the last house.

class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);
        //dp1: maximum including first house, dp2: maximum excluding first house
        vector<int> dp1(n, 0), dp2(n, 0);
        dp1[0] = nums[0]; dp1[1] = nums[0];
        dp2[0] = 0; dp2[1] = nums[1];
        for (int i = 2; i < n-1; ++i) {
            dp1[i] = max(dp1[i-2] + nums[i], dp1[i-1]); 
            dp2[i] = max(dp2[i-2] + nums[i], dp2[i-1]); 
        }
        //last one
        dp1[n-1] = dp1[n-2];
        dp2[n-1] = max(dp2[n-3] + nums[n-1], dp2[n-2]); 
        return max(dp1[n-1], dp2[n-1]);
    }
};

/// Two pass DP solution. Each pass calls original rob, once excluding nums[0] and once excluding nums[n-1]. Compare the two and return the maximum
/// robLin is the original rob function on a linear street.

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);
        return max(robLin(nums.begin(), nums.end()-1), robLin(nums.begin()+1, nums.end()));
    }
    int robLin(vector<int>::const_iterator beg, vector<int>::const_iterator end) {
        int n = end - beg;
        if(n == 0) return 0;
        if(n == 1) return *beg;
        if(n == 2) return max(*beg, *(beg+1));
        int last = max(*beg, *(beg+1));
        int lastlast = *beg;
        int curr = 0;
        for(vector<int>::const_iterator it = beg+2; it != end; it++) {
            curr = max(lastlast + *it, last);
            lastlast = last;
            last = curr;
        }
        return curr;
    }
};


/**************************************************** 
 ***    215,Medium,Kth Largest Element in an Array 
 ****************************************************/

/*
Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.

Note: 
You may assume k is always valid, 1 ≤ k ≤ array's length.
*/

// Solution 1. Use a min-queue of k elements. 
// First build the heap from first k elements of array, then insert another and remove the mininum.
// Finally we end up with the k largest numbers of the array. Simple extract the minimum we get the k-th largest element.
// We use the linear O(n) method to build the heap : initialize the heap array and the element count N, and then run fixDown backwards
// Capacity of the heap should be k+2. 1 is for the unused nums[0], the other is for the additional element added before calling deleteMin.

class PQ {
public:
    PQ(int cap) : N(0) {
        nums.resize(cap, 0);
    }
    void buildHeap(const vector<int>& arr, int i, int j) {
        for(int k = i; k <= j; ++k) {
            nums[k-i+1] = arr[k];
        }
        N = j-i+1;
        for(int k = N/2; k > 0; --k)
            fixDown(k);
    }
    void insert(int k) {
        nums[++N] = k;
        fixUp(N);
    }
    int deleteMin() {
        swap(nums[1], nums[N--]);
        fixDown(1);
        return nums[N+1];
    }
    
private:
    void fixUp(int i) {
        while(i > 1 && nums[i/2] > nums[i]) {
            swap(nums[i/2], nums[i]);
            i /= 2;
        }
    }
    void fixDown(int i) {
        while(2*i <= N) {
            int j = 2*i;
            if(j < N && nums[j+1] < nums[j]) j++;
            if(nums[j] < nums[i]) {
                swap(nums[j], nums[i]);
                i = j;
            } else break;
        }
    }
    int N; //number of elements
    vector<int> nums;
};

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        // min-queue of k numbers
        PQ pq(k+2);//maximum capacity k+2
        //build heap from first k numbers
        pq.buildHeap(nums, 0, k-1);
        
        //add one and remove min
        for(int i = k; i < n; i++) {
            pq.insert(nums[i]);
            pq.deleteMin();
        }
        return pq.deleteMin();
    }
};

// Solution 2. Same idea but using STL priority_queue class

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        // min-queue of k numbers
        std::priority_queue<int, std::vector<int>, std::greater<int> > pq;
        //build the heap from first k numbers
        for(int i = 0; i < k; i++) pq.push(nums[i]);
        //add one and remove min
        for(int i = k; i < n; i++) {
            pq.push(nums[i]);
            pq.pop();
        }
        return pq.top();
    }
};

// Solution 3. Use quick selection. Iterative or recursive findKthHelper. Since looking for k-th largest, need to revert implementatino of traditional partition function.
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        return findKthHelper(nums, 0, n-1, k);
    }
    int findKthHelper(vector<int>& nums, int l, int r, int k) {
        while(l < r) {
            //if(l == r) return nums[l];
            int i = partition(nums, l, r);
            int cnt = i-l+1; //number of elements between [l, i]
            if(k == cnt) return nums[i];
            else if(k < cnt) r = i-1; 
            else { l = i+1; k -= cnt; }
        }
        return nums[l];
    }
    /* 
    //recursive findKthHelper
    int findKthHelper(vector<int>& nums, int l, int r, int k) {
        if(l == r) return nums[l];
        int i = partition(nums, l, r);
        int cnt = i-l+1; //number of elements between [l, i]
        if(k == cnt) return nums[i];
        else if(k < cnt) return findKthHelper(nums, l, i-1, k);
        else return findKthHelper(nums, i+1, r, k-cnt);
    }
    */
    //no need to check l, r bounds because calling function guards against it. 
    //opposite to traditional paritition (larger ones to the left, smaller ones to the right)
    int partition(vector<int>& nums, int l, int r) {
        int x = nums[r]; //pivot is last one
        int i = l-1, j = r;
        while(1) {
            while(nums[++i] > x) ;
            while(nums[--j] < x) if(j == l) break;
            if(i < j) swap(nums[i], nums[j]);
            else break;
        }
        swap(nums[i], nums[r]);
        return i;
    }
};

/**************************************************** 
 ***    216,Medium,Combination Sum III 
 ****************************************************/

/*
Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.

Ensure that numbers within the set are sorted in ascending order.

Example 1:

Input: k = 3, n = 7

Output:

[[1,2,4]]


Example 2:

Input: k = 3, n = 9

Output:

[[1,2,6], [1,3,5], [2,3,4]]
*/

/// Solution 1. Recursive solution. Choose number in ascending order, track how many trials we are left, and the next available number to choose.
// Terminate at three conditions:
// 1. Searched beyond number 9.
// 2. Used up all k trials.
// 3. target sum is smaller than the next number i

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int> > result;
        if(k == 0 || n <= 0) return result;
        vector<int> tmp;
        dfs(1, k, n, tmp, result);
    }
    //search starting from i, k numbers left
    void dfs(int i, int k, int target, vector<int>& tmp, vector<vector<int> >& result) {
        if(target == 0 && k == 0) { //target is 0 and we used exactly k numbers
            result.push_back(tmp);
            return;
        }
        if(i == 10 || k < 0 || target < i) return; //used up all numbers or all trials, or target < i.

        tmp.push_back(0);
        for(int j = i; j < 10; ++j) {
            tmp.back() = j;
            dfs(j+1, k-1, target-j, tmp, result);
        }
        tmp.pop_back();
    }
};

// Solution 2. Iterative. Keep a running sum and trial number. The tricky part is how to calculate the partial sums properly. 
// Caveats:
// sum += tmp[i] should be placed after tmp[i] == 10 checks!
// after retracing, need to first subtract the tmp[i] value from sum, so that when tmp[i] is incremented, sum += tmp[i] will give the correct new usm.

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int> > result;
        if(k == 0 || n <= 0) return result;
        vector<int> tmp(k, 0);
        int i = 0; //i-th trial
        int sum = 0;
        while(i >= 0) {
            if(i == k) {
                if(sum == n) result.push_back(tmp); 
                i--; 
                if(i >= 0) sum -= tmp[i]; 
                continue; //retrace
            }
            tmp[i]++;
            if(tmp[i] == 10) { //retrace
                i--; 
                if(i >= 0) sum -= tmp[i]; 
                continue;
            } 
            sum += tmp[i]; //add to sum
            i++;
            if(i < k) tmp[i] = tmp[i-1]; //initialize starting point for next number (for tmp[i]++).
        }
        return result;
    }
};



/**************************************************** 
 ***    220,Medium,Contains Duplicate III 
 ****************************************************/

/*
Given an array of integers, find out whether there are two distinct indices i and j in the array such that the difference between nums[i] and nums[j] is at most t and the difference between i and j is at most k.
*/

// Maintain a window, when searching, utilize the ordered feature of set, and find the element >= a given value in O(lgn) time. 

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        int n = nums.size();
        for(int i = 0; i < n; i++) { //try element i
            if(i > k) dict.erase(nums[i-k-1]); //remove older elements
            long x = nums[i];
            auto it = dict.lower_bound(x - t); //find first element >= x-t in the window
            if(it != dict.end() && *it <= x + t) return true; //found and value <= x+t
            dict.insert(x); //insert to window
        }
        return false;
    }
    set<long> dict; //ordered-set for fast search
};

/**************************************************** 
 ***    221,Medium,Maximal Square 
 ****************************************************/

/*
Given a 2D binary matrix filled with 0's and 1's, find the largest square containing all 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

Return 4. 
*/

// Same idea as maximal rectangle, use routine in finding largest rectangle. Except when calculating area, use min(height, length)^2. See solutions in 085 maximal rectangle

class Solution {
public:
    int maximalSquare(vector<vector<char> > &matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> height(n, 0);
        int max_area = 0;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                height[j] = (matrix[i][j] == '1') ? height[j]+1 : 0;
            }
            max_area = max(max_area, largestSquareArea(height));
        }
        return max_area;
    }

    int largestSquareArea(vector<int>& height) {
        if(height.empty()) return 0;
        height.push_back(0);
        deque<int> s; //stack for positions
        int n = height.size();
        int max_area = 0;
        for(int i = 0; i < n; ++i) {
             while(!s.empty() && height[s.back()] > height[i]) {
                int h = height[s.back()];
                s.pop_back();
                int j = s.empty() ? 0 : s.back()+1;
                int side = min(h, i-j);
                max_area = max(max_area, side*side);
            }
            s.push_back(i);
        }
        return max_area;
    }
};

/**************************************************** 
 ***    222,Medium,Count Complete Tree Nodes 
 ****************************************************/

/*
Given a complete binary tree, count the number of nodes.

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
// solution using a function to get the height of left spine of tree. time complexity is:
// lgn + ... + 1 = lgn lgn

class Solution {
public:
    int countNodes(TreeNode* root) {
        if(!root) return 0;
        int h = leftSpineHeight(root);
        int count = (1 << h) - 1; // total possible nodes for tree at root: 2^h-1
        while(root) { //subtree under root may not be full
            h--;
            int hr = leftSpineHeight(root->right);
            if(hr < h) {
                count -= (1 << hr); // exclude missing nodes: 2^hr
                root = root->left;
            } else {
                root = root->right;
            }
        }
        return count;
    }

    int leftSpineHeight(TreeNode* root) {
        int h = 0;
        while(root) {
            root = root->left;
            h++;
        }
        return h;
    }
};

/**************************************************** 
 ***    224,Medium,Basic Calculator 
 ****************************************************/

/*
Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .

You may assume that the given expression is always valid.

Some examples:

"1 + 1" = 2
" 2-1 + 2 " = 3
"(1+(4+5+2)-3)+(6+8)" = 23

Note: Do not use the eval built-in library function. 
*/

// Solution 1. Basic calculator, with "+-" and parentheses, no "*/"
// Two stacks, one for number and one for operators (can use one, where operator can be stored by an integer sign)
// 1. when seeing a digit, update number
// 2. when seeing a + or -, update result
// 3. when seeing a '(', push result and operator to stack, reset num, res, and op
// 4. when seeing a ')', first update res, and then pop num, res from stack, update res again (e.g. calculate 2 + (...)).
// Finally after loop, update res if no '+' or '-' is seen in the string (e.g. (3))

class Solution {
public:
    int calculate(string s) {
        stack<int> nums;
        stack<char> ops;
        int res = 0;
        int num = 0;
        char op = '+';
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] >= '0' && s[i] <= '9') {
                num = num*10 + (s[i] - '0');
            } else if (s[i] == '+' || s[i] == '-') {
                res = (op == '+') ? res + num : res - num;
                num = 0;
                op = s[i];
            } else if (s[i] == '(') {
                nums.push(res); ops.push(op); //push number and sign to stack
                num = 0; res = 0; op = '+';
            } else if (s[i] == ')') {
                res = (op == '+') ? res + num : res - num;
                op = ops.top(); ops.pop();
                num = nums.top(); nums.pop();
                res = (op == '+') ? num + res : num - res;
                num = 0;
            }
        }
        if (num != 0)
            res = (op == '+') ? res + num : res - num;
        return res;
    }

};

// Solution 2. Use only one stack, push sign (1/-1) and value to the same stack, when pop, pop twice

class Solution {
public:
    int calculate(string s) {
        stack<int> st;
        int res = 0, num = 0, sgn = 1;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] >= '0' && s[i] <= '9') num = num*10 + (s[i] - '0');
            else if (s[i] == '+' || s[i] == '-') {
                res += sgn*num;
                sgn = (s[i] == '+') ? 1 : -1;
                num = 0; //reset num
            } else if (s[i] == '(') {
                st.push(res); st.push(sgn);
                num = 0; res = 0; sgn = 1; //reset
            } else if (s[i] == ')') {
                res += sgn*num; //add last number first
                res *= st.top(); st.pop(); //pop out sign
                res += st.top(); st.pop(); //pop out number
                num = 0; //reset num
            }
        }
        if (num != 0) res += sgn*num;
        return res;
    }
};


/**************************************************** 
 ***    227,Medium,Basic Calculator II 
 ****************************************************/

/*
Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, +, -, *, / operators and empty spaces . The integer division should truncate toward zero.

You may assume that the given expression is always valid.

Some examples:

"3+2*2" = 7
" 3/2 " = 1
" 3+5 / 2 " = 5

Note: Do not use the eval built-in library function. 
*/

// Basic calculator II, with "+-*/" but no parentheses
// No stack solution:
// 1. when seeing an integer, run all the way to the end of integer and get the value. If it is after a '*' or '/', immediately calculate the 
//    result and update num. Otherwise, initialize num to the value.
// 2. when seeing a '+' or '-', add the preceding number (value stored in num and sign stored in sign) to res
// 3. when seeing a '*' or '/', update last operator
// Remember to reset num after processing "+-*/"

// Also, after loop, need to add final num to res, and return
// Another tiny variation is to add a '+' in the end of string, and then can return res 
class Solution {
public:
    int calculate(string s) {
        int res = 0;
        int num = 0;
        char op = '+';
        int sign = 1;
        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            if (isDigit(c)) {
                int val = c - '0';
                int j = i+1;
                while (j < s.size() && isDigit(s[j])) {
                    val = val*10 + s[j] - '0';
                    j++;
                }
                if (op == '*') num = num * val;
                else if (op == '/') num = num / val;
                else num = val;
                i = j-1;
            } else if (c == '+' || c == '-') {
                res += num*sign;
                sign = (c == '+') ? 1 : -1;
                num = 0;
                op = c;
            } else if (c == '*' || c == '/') {
                op = c;
            } 
        }

        return res + num*sign;
    }

    bool isDigit(char c) { return c >= '0' && c <= '9'; }
};


/**************************************************** 
 ***    229,Medium,Majority Element II 
 ****************************************************/

/*
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times. The algorithm should run in linear time and in O(1) space.

Hint:

How many majority elements could it possibly have?
*/

// Solution extended from Moore's Voting algortihm
// Caveat: need to count again in the end after we find maj1 and maj2, e.g. [3,2,3]. maj2 will be 2, but 2 is not a majority element.

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        if(nums.empty()) return vector<int>();
        int n = nums.size();
        int maj1 = 0, maj2 = 0, count1 = 0, count2 = 0;
        int nmaj = 0;
        for(auto x : nums) {
            if(nmaj == 0) { nmaj = 1; maj1 = x; count1 = 1; }
            else if(nmaj == 1) { //always maj1 will have the value
                if(x == maj1) count1++;
                else { //x != maj1
                    nmaj = 2;
                    maj2 = x; count2 = 1;
                }
            } else { //already have 2 majs
                if(x == maj1) count1++;
                else if(x == maj2) count2++;
                else {
                    count1--;
                    count2--;
                    if(count1 == 0) nmaj--;
                    if(count2 == 0) nmaj--;
                    if(count1 == 0 && count2 != 0) {
                        count1 = count2;
                        maj1 = maj2;
                    }
                }
            }
        }
        vector<int> result;
        //count again
        count1 = 0; count2 = 0;
        for(auto x : nums) {
            if(x == maj1) count1++;
            else if(x == maj2) count2++;
        }
        if(count1 > n/3) result.push_back(maj1);
        if(count2 > n/3) result.push_back(maj2);
        return result;
    }
};

/**************************************************** 
 ***    230,Medium,Kth Smallest Element in a BST 
 ****************************************************/

/*
Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note:
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?

Hint:

    Try to utilize the property of a BST.
    What if you could modify the BST node's structure?
    The optimal runtime complexity is O(height of BST).
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

//First find minimum, and store the search path. Then do inorder traversal k times.
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        if(!root) return 0;
        stack<TreeNode*> path;
        while(root) {
            path.push(root);
            root = root->left;
        }
        TreeNode* node(NULL);
        int i = 1;
        while(1) {
            if(path.empty()) return 0;
            node = path.top(); path.pop();
            if(i == k) return node->val;
            i++;
            node = node->right;
            while(node) {
                path.push(node); node = node->left;
            }
        }
        return 0;
    }
};


/**************************************************** 
 ***    233,Medium,Number of Digit One 
 ****************************************************/

/*
Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.

For example:
Given n = 13,
Return 6, because digit 1 occurred in the following numbers: 1, 10, 11, 12, 13.

Hint:

Beware of overflow.
*/

// Count the occurrences of 1 on each digit seperately, and sum them up.
// First observe that for any number starting with a one on digit i, there are 10^i of them, e.g. i = 2, 100-199 (count = 100)
// For an arbitrary number, let's determine how many times the number of 1s appear at digit i, 
// let the number formed to the left of d as l, and to the right of d as r. For example: 264d32, where d can be 0 to 9.
// and l = 27, r = 32.
// (1) if d = 0, then n = 27032. The numbers contributing are from 001xx to 261xx, a total of 27*100,
//     or in general, l*10^i.
// (2) if d = 1, then n = 27132, The numbers contributing are from 001xx to 261xx, plus 27100 to 27132, a total of 27*100 + 33,
//     or in genera, l*10^i + r+1
// (3) if d > 1, e.g. n = 27232. The numbers contributing are from 001xx to 271xx, a total of (27+1)*100,
//     or in genera, (l+1)*10^i
// Algorithm starts from least significant digit, and store and update the 10^i value.

class Solution {
public:
    int countDigitOne(int n) {
        if (n <= 0) return 0;
        int ndigit = 0;
        int x = n;
        while (x) {
            x /= 10; ndigit ++;
        }
        int count = 0;
        int power = 1;
        for (int i = 0; i < ndigit; ++i) { //starting from least digit to most
            int d = n / power % 10; // digit
            int l = n / power / 10; //number to the left of d
            int r = n % power; //number to the right of d
            if (d == 0) count += l*power;
            else if (d == 1) count += l*power + r+1;
            else count += (l+1)*power;
            power *= 10;
        }
        return count;
    }
};

/**************************************************** 
 ***    236,Medium,Lowest Common Ancestor of a Binary Tree 
 ****************************************************/

/*
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

        _______3______
       /              \
    ___5__          ___1__
   /      \        /      \
   6      _2       0       8
         /  \
         7   4

For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// The tree is not BST, so we can't use value comparison. Instead, we need to examine both subtrees recursively O(n).

// Solution 1. Use two auxiliary vectors storing the search paths from root to the node. 
// Compare the two paths and find the last element both in two paths.

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || !p || !q) return NULL;
        if( !search(root, p, path1) || !search(root, q, path2)) return NULL;
        TreeNode* node = NULL;
        while(!path1.empty() && !path2.empty()) {
            TreeNode* n1 = path1.front(); path1.pop_front();
            TreeNode* n2 = path2.front(); path2.pop_front();
            if(n1 == n2) node = n1;
            else break;
        }
        return node;
    }
    //search p under subtree root
    bool search(TreeNode* root, TreeNode* p, deque<TreeNode*>& path) {
        if(!root) return false;

        path.push_back(root);
        if(root == p) return true;
        //search left and right subtree
        if(search(root->left, p, path) || search(root->right, p, path)) return true;
        path.pop_back(); //retrace
        return false;
    }
    deque<TreeNode*> path1, path2;
};

// Solution 2 without the auxiliary path vector.
// Assumes p and q are not NULL.
// Similar to Solution 1 in that when root is equal to either node, return the root.
// Then call the function for left and right subtrees. If both returns a non NULL value, that means one node is in left sub-tree, and the other is in the right sub-tree. In this case root is the LCA, and we return root.
// In other cases, simply return the value returned by the recursive calls.

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return NULL;
        if(root == p || root == q) return root;
        TreeNode* lca_l = lowestCommonAncestor(root->left, p, q);
        TreeNode* lca_r = lowestCommonAncestor(root->right, p, q);
        if(lca_l && lca_r) return root;
        else return (lca_l ? lca_l : lca_r);
    }
};


/**************************************************** 
 ***    238,Medium,Product of Array Except Self 
 ****************************************************/

/*
Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].

Solve it without division and in O(n).

For example, given [1,2,3,4], return [24,12,8,6].

Follow up:
Could you solve it with constant space complexity? (Note: The output array does not count as extra space for the purpose of space complexity analysis.)
*/

/// O(n) time, O(1) space solution.
/// Two passes, one from left and one from right
/// Product without self = product of all elements to the left, times product of all elements to the right
/// First pass, calculate products of all elements to the left and save it to ret array
/// Second pass, calculate products of all elements to the right, and multiple to the ret array values
/// when done, return the ret array

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ret(n, 1);
        int t = 1;
        for (int i = 1; i < n; ++i)
            ret[i] = ret[i-1]*nums[i-1];
        for (int i = n-2; i >= 0; --i) {
            t *= nums[i+1];
            ret[i] *= t;
        }
        return ret;
    }
};

/**************************************************** 
 ***    240,Medium,Search a 2D Matrix II 
 ****************************************************/

/*
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

    Integers in each row are sorted in ascending from left to right.
    Integers in each column are sorted in ascending from top to bottom.

For example,

Consider the following matrix:

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]

Given target = 5, return true.

Given target = 20, return false.
*/

//O(m+n) solution. Two pointers, one at left top corner, other at bottom right corner. Compare value at top right corner with target.
// If smaller than target, then the top row can be excluded (left top corner can be moved down by one step).
// If larger than target, then the rightmost row can be excluded (right bottom corner can be moved left by one step).

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty() || matrix[0].empty()) return false;
        int m = matrix.size(), n = matrix[0].size();
        int xlo = 0, ylo = 0, xhi = m-1, yhi = n-1;
        while(xlo <= xhi && ylo <= yhi) {
            int val = matrix[xlo][yhi];
            if(target == val) return true;
            else if(target > val) xlo++; 
            else yhi--;
        }
        return false;
    }
};

// Solution 2. Divide and conquer. Longer than Solution 1.

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;
        int m = matrix.size(), n = matrix[0].size();
        return search(matrix, 0, 0, m-1, n-1, target);
    }
    bool search(vector<vector<int> >& matrix, int xl, int yl, int xh, int yh, int target) {
        if (xl > xh || yl > yh) return false;
        int xm = xl + (xh - xl) / 2;
        int ym = yl + (yh - yl) / 2;
        int v = matrix[xm][ym];
        if (target < v) return search(matrix, xl, yl, xh, ym-1, target) || search(matrix, xl, ym, xm-1, yh, target);
        else if (target > v) return search(matrix, xl, ym+1, xh, yh, target) || search(matrix, xm+1, yl, xh, ym, target);
        else return true;
    }
};


/**************************************************** 
 ***    241,Medium,Different Ways to Add Parentheses 
 ****************************************************/

/*
Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *.

Example 1

Input: "2-1-1".

((2-1)-1) = 0
(2-(1-1)) = 2

Output: [0, 2]

Example 2

Input: "2*3-4*5"

(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10

Output: [-34, -14, -10, -10, 10]
*/

// Dynamic programming solution.
// First parse string and save numbers and operators separately.
// Then start from bottom up, for large string break into small pieces and check all options.

class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        if(input.empty()) return vector<int>();
        vector<int> nums; 
        vector<char> ops;
        parse(input, nums, ops);
        int n = nums.size(); //number of numbers
        //mp[i][j]: outcomes from i (i = [0..n]) numbers starting at j (j = [0 .. n-1]). 
        vector<vector<vector<int> > > mp(n+1, vector<vector<int> >(n, vector<int>()));
        //len = 1 case
        for(int i = 0; i < n; ++i) {
           mp[1][i].push_back(nums[i]);
        }
        for(int len = 2; len <= n; ++len) {
            for (int i = 0; i + len <= n; ++i) {
                int j = i + len - 1; //i start, j end, inclusive
                //try to break it from i+1 .. to j-1
                for(int k = i; k < j; ++k) { // break like this: num[k] | op[k] | num[k+1]
                    for(auto it1 : mp[k-i+1][i]) {
                        for(auto it2 : mp[j-k][k+1]) {
                            mp[len][i].push_back(eval(it1, it2, ops[k]));
                        }
                    }
                }
            }
        }
        return mp[n][0];
    }
    
    int eval(int v1, int v2, char op) {
       if(op == '+') return v1+v2;
       if(op == '-') return v1-v2;
       if(op == '*') return v1*v2;
       return 0;
    }

    void parse(string& input, vector<int>& nums, vector<char>& ops) {
        int val = 0;
        for(int i = 0; i < input.size(); ++i) {
            char c = input[i];
            if(isdigit(c)) {
               val = 10*val + (c - '0');
            } else {
               ops.push_back(c);
               nums.push_back(val);
               val = 0;
            }
        }
        nums.push_back(val); //don't forget last one!
    }
};

// Recursive solution using divide and conquer. Final vector is the cartesian product of two sub-vectors

class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> numbers;
        vector<char> operators;
        int num = 0;
        for(int i = 0; i < input.size(); i++) {
            char c = input[i];
            if(c >= '0' && c <= '9') num = num*10 + (c-'0');
            else {
                numbers.push_back(num);
                operators.push_back(c);
                num = 0;
            }
        }
        numbers.push_back(num);
        
        int n = numbers.size();
        vector<int> ret;
        eval(numbers, operators, 0, n-1, ret);
        return ret;
    }
    
    void eval(vector<int>& numbers, vector<char>& operators, int lo, int hi, vector<int>& vals) {
        vals.clear();
        if(lo == hi) {
            vals.push_back(numbers[lo]); //only one
            return;
        }
        vector<int> v1, v2;
        for(int mid = lo; mid < hi; ++mid) {
            eval(numbers, operators, lo, mid, v1);
            eval(numbers, operators, mid+1, hi, v2);
            for (int j1 = 0; j1 < v1.size(); ++j1) {
                for(int j2 = 0; j2 < v2.size(); ++j2) {
                    vals.push_back(eval(v1[j1], v2[j2], operators[mid]));
                }
            }
        }
    }
    
    int eval(int n1, int n2, char op) {
        switch (op) {
            case '+': return n1 + n2;
            case '-': return n1 - n2;
            case '*': return n1 * n2;
            default : return 0;
        }
    }
};

/**************************************************** 
 ***    244,Medium,Shortest Word Distance II 
 ****************************************************/

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

/**************************************************** 
 ***    245,Medium,Shortest Word Distance III 
 ****************************************************/

/*
This is a follow up of Shortest Word Distance. The only difference is now word1 could be the same as word2.

Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.

word1 and word2 may be the same and they represent two individual words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “makes”, word2 = “coding”, return 1.
Given word1 = "makes", word2 = "makes", return 3.

Note:
You may assume word1 and word2 are both in the list.
*/

// Solution 1. Similar to 243 with additional lines to take care of case where word1 == word2.
class Solution {
public:
    int shortestWordDistance(vector<string>& words, string word1, string word2) {
        int index(-1), mind = INT_MAX, n = words.size();
        for(int i = 0; i < n; i++) {
            const string& w = words[i];
            if(w == word1 || w == word2) {
                if(word1 == word2) {
                    if(index != -1) mind = min(mind, i-index);
                } else {
                    if(index != -1 && words[index] != w) mind = min(mind, i-index);
                }
                index = i;
            }
        }
        return mind;
    }
};

// Solution 2. Simplified control logic

class Solution {
public:
    int shortestWordDistance(vector<string>& words, string word1, string word2) {
        int index(-1), mind = INT_MAX, n = words.size();
        for(int i = 0; i < n; i++) {
            const string& w = words[i];
            if(w == word1 || w == word2) {
                if(index != -1 && (word1 == word2 || words[index] != w)) mind = min(mind, i-index);
                index = i;
            }
        }
        return mind;
    }
};

/**************************************************** 
 ***    247,Medium,Strobogrammatic Number II 
 ****************************************************/

/*
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Find all strobogrammatic numbers that are of length = n.

For example,
Given n = 2, return ["11","69","88","96"]. 
*/

// Solution 1. Recursive. First add solutions with leading zeros and put them in the end of vector. then erase them altogether.

class Solution {
public:
    vector<string> findStrobogrammatic(int n) {
        vector<string> result;
        if(n == 1) {
            result = {"0", "1", "8"};
            return result;
        }
        stroboHelper(n, result);
        //remove ones starting with zero
        int i = 0;
        for(i = 0; i < result.size(); ++i) {
            if(result[i][0] == '0') break;
        }
        result.resize(i);
        return result;
    }
    void stroboHelper(int n, vector<string>& result) {
        if(n == 1) result = {"1", "8", "0"}; 
        else if(n == 2) result = {"11", "69", "88", "96", "00"};
        else {
            vector<string> tmp;
            stroboHelper(n-2, tmp);
            for(auto it : tmp) {
                result.push_back('1'+it+'1');
                result.push_back('6'+it+'9');
                result.push_back('8'+it+'8');
                result.push_back('9'+it+'6');
            }
            for(auto it : tmp) result.push_back('0'+it+'0');
        }
    }
};

// Solution 2. Iterative. Avoid the annoying leading 0 issue by checking whether reaching last step.

class Solution {
public:
    vector<string> findStrobogrammatic(int n) {
        if(n <= 0) return vector<string>();
        if(n == 1) return {"0", "1", "8"};
        if(n == 2) return {"11", "69", "88", "96"};
        vector<string> result;
        if(n % 2 == 1) result = {"0", "1", "8"};
        else result = {"00", "11", "69", "88", "96"};
        vector<string> newresult;
        while(n > 2) {
            n -= 2;
            for(auto it : result) {
                if(n > 2) newresult.push_back('0'+it+'0');
                newresult.push_back('1'+it+'1');
                newresult.push_back('6'+it+'9');
                newresult.push_back('8'+it+'8');
                newresult.push_back('9'+it+'6');
            }
                
            result.swap(newresult);
            newresult.clear();
        }

        return result;
    }
};


/**************************************************** 
 ***    250,Medium,Count Univalue Subtrees 
 ****************************************************/

/*
Given a binary tree, count the number of uni-value subtrees.

A Uni-value subtree means all nodes of the subtree have the same value.

For example:
Given binary tree,

              5
             / \
            1   5
           / \   \
          5   5   5

return 4. 
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Recursive solution. Use a helper function to count the univalue subtrees and also return whether the tree itself is univalue.
// An empty tree is defined to be univalue.
// A tree is univalue iff:
// 1. left and right tree are both univalue
// 2. if left/right child is not empty, the node value of left/right child should be equal to root value.

class Solution {
public:
    int countUnivalSubtrees(TreeNode* root) {
        int count = 0;
        helper(root, count);
        return count;
    }
    bool helper(TreeNode* root, int& count) {
        if(!root) { count = 0; return true; }
        int cl(0), cr(0);
        TreeNode *l = root->left, *r = root->right;
        bool uniVal_l = helper(l, cl);
        bool uniVal_r = helper(r, cr);
        count = cl + cr;
        if((uniVal_l && (!l || l->val == root->val)) && (uniVal_r && (!r || r->val == root->val))) {
            count += 1;
            return true; //root is univalue tree
        } else return false; //root is not univalue tree
    }
};


/**************************************************** 
 ***    251,Medium,Flatten 2D Vector 
 ****************************************************/

/*
Implement an iterator to flatten a 2d vector.

For example,
Given 2d vector =

[
  [1,2],
  [3],
  [4,5,6]
]

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,2,3,4,5,6].

Hint:

    How many variables do you need to keep track?
    Two variables is all you need. Try with x and y.
    Beware of empty rows. It could be the first few rows.
    To write correct code, think about the invariant to maintain. What is it?
    The invariant is x and y must always point to a valid point in the 2d vector. Should you maintain your invariant ahead of time or right when you need it?
    Not sure? Think about how you would implement hasNext(). Which is more complex?
    Common logic in two different places should be refactored into a common method.

Follow up:
As an added challenge, try to code it using only iterators in C++ or iterators in Java. 
*/

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D i(vec2d);
 * while (i.hasNext()) cout << i.next();
 */

class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d) {
        nums = vec2d;
        n = nums.size();
        index = 0;
        arrayIdx = 0;
        while(arrayIdx < n && nums[arrayIdx].empty()) arrayIdx++;
    }

    int next() {
        if(arrayIdx == n) return -1;
        int val = nums[arrayIdx][index];
        index++;
        if(index == nums[arrayIdx].size()) {
            index = 0;
            arrayIdx ++;
            while(arrayIdx < n && nums[arrayIdx].empty()) arrayIdx ++;
        }
        return val;
    }

    bool hasNext() {
        return arrayIdx < n;
    }

private:
    vector<vector<int> > nums;
    int arrayIdx; //current array index
    int index; //index within current array
    int n; //number of arrays
};

// Solution 2. Similar to 281. Use a stack to store the pair of iterators
class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d) {
        for(auto vit = vec2d.rbegin(); vit != vec2d.rend(); vit++) {
            if(!vit->empty()) s.push(make_pair(vit->begin(), vit->end()));
        }
    }

    int next() {
        auto beg = s.top().first;
        auto end = s.top().second;
        s.pop();
        if(beg+1 < end) s.push(make_pair(beg+1, end));
        return *beg;
    }

    bool hasNext() {
        return !s.empty();
    }
    stack<pair<vector<int>::iterator, vector<int>::iterator> > s;
};

/**************************************************** 
 ***    253,Medium,Meeting Rooms II 
 ****************************************************/

/*
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return 2. 
*/

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

//Solution 1: sort the ending point according to its coordinate and type (start/end). If ties on coordinate, end goes before start
//Then do sweeping line and count. When see a start point, increment count, otherwise decrement count.

struct EndPoint {
    int val;
    int type; //0 for starting, 1 for ending
    EndPoint(): val(0), type(0) {}
    EndPoint(int v, int t) : val(v), type(t) {}
};

bool compare(const EndPoint& a, const EndPoint& b) {
    if(a.val == b.val) return a.type < b.type;
    else return a.val < b.val;
}


class Solution {
public:

    int minMeetingRooms(vector<Interval>& intervals) {
        int n = intervals.size();
        if(n <= 1) return n;
        vector<EndPoint> points(2*n);
        for(int i = 0; i < n; ++i) {
            points[2*i] = EndPoint(intervals[i].start, 2);
            points[2*i+1] = EndPoint(intervals[i].end, 1);
        }
        sort(points.begin(), points.end(), compare);
        int count = 0, result = 0;
        for(int i = 0; i < 2*n; ++i) {
            if(points[i].type == 2) { //is start point
               count++;
               result = max(result, count);
            } else count--;
        }
        return result;
    }
};


//A simpler solution: use a map to keep order, and count individual points, then iterate orderly through map
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        map<int, int> dict;
        int n = intervals.size();
        if(n <= 1) return n;
        for(int i = 0; i < n; ++i) {
            dict[intervals[i].start]++;
            dict[intervals[i].end]--;
        }
        int count = 0, max_count = 0;
        for(auto it : dict) { //ordered iterator
            count += it.second;
            max_count = max(count, max_count);
        }
        return max_count;
    }
};


/**************************************************** 
 ***    254,Medium,Factor Combinations 
 ****************************************************/

/*
Numbers can be regarded as product of its factors. For example,

8 = 2 x 2 x 2;
  = 2 x 4.

Write a function that takes an integer n and return all possible combinations of its factors.

Note:

    Each combination's factors must be sorted ascending, for example: The factors of 2 and 6 is [2, 6], not [6, 2].
    You may assume that n is always positive.
    Factors should be greater than 1 and less than n.

Examples:
input: 1
output:

[]

input: 37
output:

[]

input: 12
output:

[
  [2, 6],
  [2, 2, 3],
  [3, 4]
]

input: 32
output:

[
  [2, 16],
  [2, 2, 8],
  [2, 2, 2, 4],
  [2, 2, 2, 2, 2],
  [2, 4, 4],
  [4, 8]
]
*/

// Recursive DFS solution. Avoid adding [n] to solution (checking tmp.empty()).
// Also avoid pushing duplicated entries, e.g. [2, 2, 3], [2, 3, 2]. This is done by the j*j <= n condition in the loop.
class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int> > result;
        if(n <= 2) return result; //empty
        vector<int> tmp;
        dfs(n, 2, tmp, result); // start searching factors from 2 to sqrt(n)
        return result;
    }
    void dfs(int n, int i, vector<int>& tmp, vector<vector<int> >& result) {
        tmp.push_back(0);
        if(!tmp.empty()) { //push n itself
            tmp.back() = n;
            result.push_back(tmp);
        }
        //now check factors
        for(int j = i; j*j <= n; ++j) {
            if(n % j != 0) continue; //not a factor
            tmp.back() = j;
            dfs(n/j, j, tmp, result); //now start searching from j
        }
        tmp.pop_back();
    }
};


/**************************************************** 
 ***    255,Medium,Verify Preorder Sequence in Binary Search Tree 
 ****************************************************/

/*
Given an array of numbers, verify whether it is the correct preorder traversal sequence of a binary search tree.

You may assume each number in the sequence is unique.

Follow up:
Could you do it using only constant space complexity?
*/

// Solution 1. Using a stack, O(n) space. https://leetcode.com/discuss/51543/java-o-n-and-o-1-extra-space
// when seeing a number smaller than the top of stack, push to stack, otherwise pop all values in the stack smaller than current value.
// Also maintain a lower bound value (lo) that all new values are subject to.

class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        if(preorder.empty()) return true;
        stack<int> s;
        int lo = INT_MIN;
        for(int x : preorder) {
            if(x < lo) return false;
            while(!s.empty() && x > s.top()) {
                lo = s.top(); //update lower bound
                s.pop();
            }
            s.push(x);
        }
        return true;
    }
};

// Solution 2, manipulate original vector as stack, O(1) space. Modifies original vector. i is the top of the stack, when inserting a 
// new value, set the ++i position to the new value.

class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        if(preorder.empty()) return true;
        int i = -1;
        int lo = INT_MIN;
        for(int x : preorder) {
            if(x < lo) return false;
            while(i != -1 && x > preorder[i]) {
                lo = preorder[i]; //update lower bound
                i--;
            }
            preorder[++i] = x;
        }
        return true;
    }
};

// Solution 3, recursive solution, very slow. Idea is to first locate root (first element), then locate left and right subtree.
// Start of right subtree starts at the first element larger than root value. Then recursively check left and right subtree.
// The proper lower and higher bounds need to be maintained.
class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        if(preorder.empty()) return true;
     //   long lo = long(INT_MIN)-1, hi = long(INT_MAX)+1;
        int lo = INT_MIN, hi = INT_MAX;
        return verify(preorder, 0, preorder.size()-1, lo, hi);
    }
    //check whether pre[i .. j] is between [lo .. hi]
    bool verify(vector<int>& preorder, int i, int j, int lo, int hi) {
        if(i > j) return true; //empty
        int root_val = preorder[i];
        if(root_val < lo || root_val > hi) return false;
        int k = i+1;
        while(k <= j && preorder[k] < root_val) k++;
        //k points to start of right subtree or end of preorder
        return verify(preorder, i+1, k-1, lo, root_val) && verify(preorder, k, j, root_val, hi);
    }
};


/**************************************************** 
 ***    256,Medium,Paint House 
 ****************************************************/

/*
There are a row of n houses, each house can be painted with one of the three colors: red, blue or green. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x 3 cost matrix. For example, costs[0][0] is the cost of painting house 0 with color red; costs[1][2] is the cost of painting house 1 with color green, and so on... Find the minimum cost to paint all houses.

Note:
All costs are positive integers.
*/

// Solution: Dynamic programming
// Keep the cost for painting the first k houses with last house colored as R/G/B.
// The k+1 house can choose among R/G/B, with cost as
// cost_so_far[R]:  cost[k+1][R] + min(cost_so_far[G], cost_so_far[B])
// and similar for other two cases.

class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        if(costs.empty() || costs[0].empty()) return 0;
        int n = costs.size();
        vector<int> cost_so_far(3, 0);
        for(int i = 0; i < n; ++i) {
            int t0 = min(cost_so_far[1], cost_so_far[2]) + costs[i][0];
            int t1 = min(cost_so_far[0], cost_so_far[2]) + costs[i][1];
            int t2 = min(cost_so_far[0], cost_so_far[1]) + costs[i][2];
            cost_so_far[0] = t0;
            cost_so_far[1] = t1;
            cost_so_far[2] = t2;
        }
        return min(min(cost_so_far[0], cost_so_far[1]), cost_so_far[2]);
    }
};

/**************************************************** 
 ***    259,Medium,3Sum Smaller 
 ****************************************************/

/*
Given an array of n integers nums and a target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.

For example, given nums = [-2, 0, 1, 3], and target = 2.

Return 2. Because there are two triplets which sums are less than 2:

[-2, 0, 1]
[-2, 0, 3]

Follow up:
Could you solve it in O(n2) runtime? 
*/

// Two pointers, similar to 3sum.
// Optimization: break if sum is too large.

class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int count = 0;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for(int i = 0; i < n-2; i++) {
            int res = target - nums[i];
            if(nums[i+1] + nums[i+2] >= res) break;
            int j = i+1, k = n-1;
            while(j < k) {
               if(nums[j] + nums[k] < res) { count += k-j; j++; }
               else k--;
            }
        }
        return count;
    }
};

/**************************************************** 
 ***    260,Medium,Single Number III 
 ****************************************************/

/*
Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.

For example:

Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].

Note:

    The order of the result is not important. So in the above example, [5, 3] is also correct.
    Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?
*/

// Solution using bit operations. Since the two numbers are different, they should differ by at least one bit position. Say the position is i, then one number should have 0, the other have 1 at this position. We use exlcusive or to find the bits that they differ. Then extract one bit out. And then group the numbers by whether the bit is set or not. We effectively break the problem into two easier problems where each group has only one single number. We calculate the single number for each group separately.

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        vector<int> result(2, 0);
        int val = 0, n = nums.size();
        for(int i = 0; i < n; ++i) {
            val ^= nums[i];
        }
        //val should be non-zero. Extract one none zero digit.
        val = val & (val ^ (val-1)); //now val has only one digit set
        for(int i = 0; i < n; ++i) {
            if(nums[i] & val) result[0] ^= nums[i];
            else result[1] ^= nums[i];
        }
        return result;
    }
};




/**************************************************** 
 ***    261,Medium,Graph Valid Tree 
 ****************************************************/

/*
Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.

For example:

Given n = 5 and edges = [[0, 1], [0, 2], [0, 3], [1, 4]], return true.

Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]], return false.

Hint:

    Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], what should your return? Is this case a valid tree?
    According to the definition of tree on Wikipedia: “a tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.”

Note: you can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges. 
*/

// Solution 1. Union find with weighted quick-union and path compression by halving. For a graph to be a tree, it has to make sure:
// no cycles
// no disconnected components
class UnionFind {
public:
    UnionFind(int N) : n(N) {
        id.resize(N, 0);
        for(int i = 0; i < N; ++i) id[i] = i;
        size.resize(N, 1);
    }
    bool unite(int i, int j) {
        while(id[i] != i) { id[i] = id[id[i]]; i = id[i]; }
        while(id[j] != j) { id[j] = id[id[j]]; j = id[j]; }
        if(i != j) {
            if(size[i] < size[j]) { id[i] = j; size[j] += size[i]; }
            else { id[j] = i; size[i] += size[j]; }
            n--;
            return true;
        } else return false; //already connected
    }
    int count() const { return n; }

private:
    vector<int> id;
    vector<int> size;
    int n;
};

class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
         UnionFind uf(n);
         for(auto it : edges)
             if(!uf.unite(it.first, it.second)) return false;
         return uf.count() == 1;
    }
};

// Solution 2 using DFS cycle detection
class Graph {
public:
    Graph(int n) : N(n) {
       adj.resize(n);
    }
    int NV() const { return N; }
    void addEdge(int i, int j) {
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    int N;
    vector<vector<int> > adj; //adjacency list
};

class GraphValidTree {
public:
    GraphValidTree(const Graph& graph) : g(graph) {
        int nv = g.NV();
        state.resize(nv, 0);
    }
    bool isValidTree() {
        if(!dfs(0, -1)) return false;
        // check if there are still unvisited nodes (g is a forest)
        for(int i = 0; i < g.NV(); ++i) {
            if(state[i] == 0) return false;
        }
        return true;
    }
    bool dfs(int v, int p) {
        state[v] = 1;
        for(int w : g.adj[v]) {
            if(w == p) continue; //its parent
            if(state[w] != 0 || !dfs(w, v)) return false;
        }
        return true;
    }
    const Graph& g;
    vector<int> state;
};

class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
         if(n == 0) return true;
         Graph g(n);
         for(auto it : edges)
             g.addEdge(it.first, it.second);

         GraphValidTree gvt(g);
         return gvt.isValidTree();
    }
};


/**************************************************** 
 ***    264,Medium,Ugly Number II 
 ****************************************************/

/*
Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.

Note that 1 is typically treated as an ugly number.

Hint:

    The naive approach is to call isUgly for every number until you reach the nth one. Most numbers are not ugly. Try to focus your effort on generating only the ugly ones.
    An ugly number must be multiplied by either 2, 3, or 5 from a smaller ugly number.
    The key is how to maintain the order of the ugly numbers. Try a similar approach of merging from three sorted lists: L1, L2, and L3.
    Assume you have Uk, the kth ugly number. Then Uk+1 must be Min(L1 * 2, L2 * 3, L3 * 5).
*/

// Solution: http://www.geeksforgeeks.org/ugly-numbers/
// All ugly numbers are built from the following three lists:
// (1) 1x2 2x2 3x2 4x2 5x2 6x2 8x2
// (2) 1x3 2x3 3x3 4x3 5x3 6x3 8x3
// (3) 1x5 2x5 3x5 4x5 5x5 6x5 8x5
// Where (1) is built from the exact ugly number sequence multiple by 2, and similar for (2) and (3). So we could use dynamic programming to generate the next ugly number from previous ones. The key is to maintain the order.
// To solve this, we keep track of which is the last ugly number used in each list, for example, 4 in (1), 3 in (2), and 2 in (5), then the next ugly number will be the minimum of 4x2, 3x3, and 2x5. We found the minimum is 4x2 from (1), then we advance pointer in (1) to 5. We store all the previous ugly numbers in an array so that we can use three pointers to point to the approapriate entry in the array and easily find the next ugly number for each list by advancing the pointers. 
// There might be duplicates in the lists, so we need to test each list.

// A simple solution with many array addressing (a bit slower)
class Solution {
public:
    int nthUglyNumber(int n) {
        if(n == 1) return 1;
        int mult2 = 1, mult3 = 1, mult5 = 1;
        vector<int> ugly(n, 1);
        int i2 = 0, i3 = 0, i5 = 0; //index in ugly array
        for(int i = 1; i < n; ++i) {
            ugly[i] = min(min(ugly[i2]*2, ugly[i3]*3), ugly[i5]*5);
            if(ugly[i] == ugly[i2]*2) i2++;
            if(ugly[i] == ugly[i3]*3) i3++;
            if(ugly[i] == ugly[i5]*5) i5++;
        }
        return ugly[n-1];
    }
};

// A faster version avoiding array addressing by using intermediate variable mult and next
class Solution {
public:
    int nthUglyNumber(int n) {
        if(n == 1) return 1;
        int mult2 = 1, mult3 = 1, mult5 = 1;
        vector<int> ugly(n, 1);
        int i2 = 0, i3 = 0, i5 = 0; //index in ugly array
        for(int i = 1; i < n; ++i) {
            int next = min(min(mult2*2, mult3*3), mult5*5);
            ugly[i] = next;
            if(next == mult2*2) mult2 = ugly[++i2];
            if(next == mult3*3) mult3 = ugly[++i3];
            if(next == mult5*5) mult5 = ugly[++i5];
        }
        return ugly[n-1];
    }
};

// Solution 2. avoid multiplications, but have additional variables. Can be extended to super ugly case. Also loop starts at 0.
class Solution {
public:
    int nthUglyNumber(int n) {
        if(n == 1) return 1;
        vector<int> ugly(n, 0);
        vector<int> idx(3, 0); //indices in ugly for numbers being multiplied by 2, 3, 5
        vector<int> val(3, 1); //next values for 2, 3, 5
        int next = 1;
        for(int i = 0; i < n; ++i) {
            ugly[i] = next; 
            if(val[0] == ugly[i]) val[0] = ugly[idx[0]++] * 2;
            if(val[1] == ugly[i]) val[1] = ugly[idx[1]++] * 3;
            if(val[2] == ugly[i]) val[2] = ugly[idx[2]++] * 5;
            next = min(min(val[0], val[1]), val[2]);
        }
        return ugly[n-1];
    }
};

// A solution using priority queue
struct Element {
    int val;
    int prime;
    int index;
    Element() : val(0), prime(0), index(0) {}
    Element(int v, int p, int i) : val(v), prime(p), index(i) {}
};

class isGreater
{
public:
    bool operator() (const Element& e1, const Element &e2) {
        return e1.val > e2.val;    
    }
};


class Solution {
public:
    int nthUglyNumber(int n) {
        if(n == 1) return 1;
        vector<int> ugly(n, 1);
        priority_queue<Element, vector<Element>, isGreater> min_queue;
        min_queue.push(Element(2, 2, 0));
        min_queue.push(Element(3, 3, 0));
        min_queue.push(Element(5, 5, 0));
        for(int i = 1; i < n; ++i) {
            int val = min_queue.top().val;
            while(min_queue.top().val == val) { //remove all duplicates
                Element next = min_queue.top();
                min_queue.pop();
                ugly[i] = next.val;
                next.val = ugly[++next.index]*next.prime;
                min_queue.push(next);
            }
        }
        return ugly[n-1];
    }
};

/**************************************************** 
 ***    267,Medium,Palindrome Permutation II 
 ****************************************************/

/*
Given a string s, return all the palindromic permutations (without duplicates) of it. Return an empty list if no palindromic permutation could be form.

For example:

Given s = "aabb", return ["abba", "baab"].

Given s = "abc", return [].

Hint:

    If a palindromic permutation exists, we just need to generate the first half of the string.
    To generate all distinct permutations of a (half of) string, use a similar approach from: Permutations II or Next Permutation.

*/

// Scan whole word, count occurrences of each character. Only one character is allowed to have odd count. Otherwise return empty set.
// construct half string as half the count of each character. No need to sort the string because we construct it from c = 0 to c = 255.
// Store the middle character as a string (either single character, or empty string). And call nextPermutation to find the next one. Need a reverse function.
// Caveats:
// Need to handle corner cases where the half string is empty! It will result in infinite loops in nextPermutation if there is no checking.
// Alternatively can check this at the beginning (by checking whether the length of s is 1).

class Solution {
public:
    vector<string> generatePalindromes(string s) {
        vector<string> result;
        if(s.empty()) return result;
        if(s.size() == 1) {
            result.push_back(s); return result;
        }
        vector<int> counts(256, 0);
        for(auto c : s) counts[c] ++;
        int nodds = 0;
        string odd = "";
        s = "";
        for(int c = 0; c < 256; ++c) {
            if(counts[c] & 1) {
                odd += c;
                if(++nodds > 1) return result; //no solution
            } 
            if (counts[c] > 0)
                s += string(counts[c]/2, c);
        }
        result.push_back(s+odd+reverse(s));
        while(nextPermutation(s)) result.push_back(s+odd+reverse(s));
        return result;
    }
    
    string reverse(const string& s) {
        string t = s;
        int i(0), j(s.size()-1);
        while(i < j) {
            swap(t[i++], t[j--]);
        }
        return t;
    }
    bool nextPermutation(string& s) {
        if(s.empty()) return false;
        int n = s.size();
        int k = n-2, l = n-1;
        while(k >= 0 && s[k] >= s[k+1]) k--;
        //k is the last k such that nums[k] < nums[k+1]
        if(k == -1) { //no next, just return false
            return false;
        }
        while(l > k && s[l] <= s[k]) l--;
        //l is the last l such that nums[l] > nums[k]
        //swap nums[k] and nums[l]
        swap(s[k], s[l]);
        //sort numbers after k
        int i = k+1, j = n-1;
        while(i < j) swap(s[i++], s[j--]);
        return true;
    }
};

/**************************************************** 
 ***    268,Medium,Missing Number 
 ****************************************************/

/*
 Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.

For example,
Given nums = [0, 1, 3] return 2.

Note:
Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity? 
*/

// solution by swapping. Since numbers are distinct, don't need to worry about infinite while loops due to duplicate entries.

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0; i < n; ++i) {
            while(nums[i] != i && nums[i] != n) {
                swap(nums[i], nums[nums[i]]);
            }
        }
        for(int i = 0; i < n; ++i)
            if(nums[i] != i) return i;
        return n;
    }
};


/**************************************************** 
 ***    271,Medium,Encode and Decode Strings 
 ****************************************************/

/*
Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.

Machine 1 (sender) has the function:

string encode(vector<string> strs) {
  // ... your code
  return encoded_string;
}
Machine 2 (receiver) has the function:
vector<string> decode(string s) {
  //... your code
  return strs;
}
So Machine 1 does:

string encoded_string = encode(strs);
and Machine 2 does:

vector<string> strs2 = decode(encoded_string);
strs2 in Machine 2 should be the same as strs in Machine 1.

Implement the encode and decode methods.

Note:
The string may contain any possible characters out of 256 valid ascii characters. Your algorithm should be generalized enough to work on any possible characters.
Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.
Do not rely on any library method such as eval or serialize methods. You should implement your own encode/decode algorithm.
*/

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));

// Solution using delimiter and escape character
// use ',' as delimiter, if ',' appears in string, use '\' to escape it, also use '\' to escape itself, so
// ',' is delimiter
// when see a '\', get the next character as the real character
// e.g., for "i love new,york" we will get: ",i,love,new\,york,"

class Codec {
public:
    const char ESCAP = 92;
    const char DELIM = ',';
    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        string s;
        for(int i = 0; i < strs.size(); ++i) {
           s += DELIM; //add delimiter
           for(auto c : strs[i]) {
               if(c == DELIM || c == ESCAP) s += ESCAP; //escape character '\'
               s += c;
           }
           s += DELIM; //add delimiter
        }
        return s;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> strs;
        if(s.empty()) return strs;
        int n = s.size();
        int i = 0;
        while(i < n) { //i points to first ','
            int j = i+1;
            string tmp;
            while(s[j] != DELIM) {
                if(s[j] == ESCAP) tmp += s[++j]; //read next char
                else tmp += s[j];
                j++;
            }
            strs.push_back(tmp);
            i = j+1;
        }
        return strs;
    }
};

// solution 2 without delimiter, but serialize the length of each string into a 4 character string (len fits in 32bits)
// Caveats:
// use unsigned int to avoid any sign issues (char is signed)
// when converting char to unsigned, use (c & 255), do not just do unsigned(c).
// when c = -127, unsigned(c) will do sign extension and get INT_MAX, only c & 255 will lead to 255

class Codec {
public:

    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        string result;
        for(auto s : strs) {
            result += int2str(s.size()) + s;
        }
        return result;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> result;
        int i = 0, n = s.size();
        while(i < n) {
            //get first 4 bytes
            unsigned len = str2int(s.substr(i, 4));
            i += 4;
            result.push_back(s.substr(i, len));
            i += len;
        }
        return result;
    }
    //convert an integer to string, 4 bytes => 4 characters
    string int2str(unsigned x) {
        string s(4, 0);
        for(int i = 0; i < 4; i++) {
            s[3-i] = x & 255; //get last 8 bytes
            x >>= 8; //shift to left by 8 bytes
        }
        return s;
    }
   
    //convert a length-4 string to integer, 4 characters => 4 bytes
    unsigned str2int(string s) {
        unsigned x = 0;
        for(int i = 0; i < 4; i++) {
            x = (x << 8) + (s[i] & 255); //don't use unsigned(s[i]), will get unexpected results!
        }
        return x;
    }
};


/**************************************************** 
 ***    273,Medium,Integer to English Words 
 ****************************************************/

/*
Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 231 - 1.

For example,

123 -> "One Hundred Twenty Three"
12345 -> "Twelve Thousand Three Hundred Forty Five"
1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

Hint:

    Did you see a pattern in dividing the number into chunk of words? For example, 123 and 123000.
    Group the number by thousands (3 digits). You can write a helper function that takes a number less than 1000 and convert just that chunk to words.
    There are many edge cases. What are some good test cases? Does your code work with input such as 0? Or 1000010? (middle chunk is zero and should not be printed out)
*/

// Break into 1000 chunks, consider many edge cases.

const vector<string> ones = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
const vector<string> tens = {"Zero", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
const vector<string> bases = {"", "Thousand", "Million", "Billion"};

class Solution {
public:
    string numberToWords(int num) {
        if(num == 0) return "Zero";
        string str;
        int base = 1000000000;
        int k = 3;
        while(base) {
            if(num >= base) {
                int v = num / base;
                if(!str.empty()) str += " ";
                if(k > 0) str += numberBelow1000(v) + " " + bases[k];
                else str += numberBelow1000(v);
                num %= base;
            }
            base /= 1000;
            k--;
        }
        return str;
    }
    
    string numberBelow1000(int num) {
        string str;
        
        int d1 = num / 100; 
        num %= 100;
        if(d1 != 0) str += ones[d1] + " Hundred";
        if(num == 0) ;
        else if(num < 20) str += (str.empty() ? ones[num] : " " + ones[num]);
        else { // num >= 20
            int d2 = num / 10, d3 = num % 10;
            if(d2 != 0) str += (str.empty() ? tens[d2] : " " + tens[d2]);
            if(d3 != 0) str += (str.empty() ? ones[d3] : " " + ones[d3]);
        }
        return str;
    }
};


/**************************************************** 
 ***    274,Medium,H-Index 
 ****************************************************/

/*
Given an array of citations (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, and the other N − h papers have no more than h citations each."

For example, given citations = [3, 0, 6, 1, 5], which means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively. Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, his h-index is 3.

Note: If there are several possible values for h, the maximum one is taken as the h-index.

Hint:

An easy approach is to sort the array first.
What are the possible values of h-index?
A faster approach is to use extra space.
*/

// Solution using binary search. First sort array in descending order. Then find the largest index i such that nums[i] >= i+1.

class Solution {
public:
    int hIndex(vector<int>& citations) {
        if(citations.empty()) return 0;
        sort(citations.begin(), citations.end(), std::greater<int>());
        int n = citations.size();
        int lo = 0, hi = n-1;
        //[0 .. lo-1]: num[i] >= i+1; [hi+1, n): num[i] < i+1, return hi
        while(lo <= hi) {
            int mid = lo + (hi-lo)/2;
            if(citations[mid] >= mid+1) lo = mid+1;
            else hi = mid-1;
        }
        return hi+1;
    }
};

// Solution 2. Use another table to store the counts, O(n) space, but O(n) time.
// dict[i] stores the number of papers that have citation of i, since hindex can only be 0 to n, where n is the size of input array,
// we only need to keep track of the counts for i = 0 .. n, hence the size of dict is n+1.

class Solution {
public:
    int hIndex(vector<int>& citations) {
        if(citations.empty()) return 0;
        int n = citations.size();
        vector<int> dict(n+1, 0); //dict[i]: count for citations equal to i
        for(auto c: citations)  dict[min(c, n)]++;
        for(int i = n, tot = 0; i >= 0; i--) {
            tot += dict[i];
            if(tot >= i) return i;
        }
        return 0;
    }
};

/**************************************************** 
 ***    275,Medium,H-Index II 
 ****************************************************/

/*
Follow up for H-Index: What if the citations array is sorted in ascending order? Could you optimize your algorithm?

Hint:

Expected runtime complexity is in O(log n) and the input is sorted.
*/

// binary search, similar to 274 except that here the array is sorted in ascending order.

class Solution {
public:
    int hIndex(vector<int>& citations) {
        if(citations.empty()) return 0;
        int n = citations.size();
        int lo(0), hi(n-1);
        //[0 .. lo-1] have n-i > citations[i], [hi+1, end) have n-i <= citations[i], return n-lo
        while(lo <= hi) {
            int mid = lo + (hi-lo)/2;
            if(n-mid > citations[mid]) lo = mid+1;
            else hi = mid-1;
        }
        return n-lo;
    }
};

/**************************************************** 
 ***    277,Medium,Find the Celebrity 
 ****************************************************/

/*
Suppose you are at a party with n people (labeled from 0 to n - 1) and among them, there may exist one celebrity. The definition of a celebrity is that all the other n - 1 people know him/her but he/she does not know any of them.

Now you want to find out who the celebrity is or verify that there is not one. The only thing you are allowed to do is to ask questions like: "Hi, A. Do you know B?" to get information of whether A knows B. You need to find out the celebrity (or verify there is not one) by asking as few questions as possible (in the asymptotic sense).

You are given a helper function bool knows(a, b) which tells you whether A knows B. Implement a function int findCelebrity(n), your function should minimize the number of calls to knows.

Note: There will be exactly one celebrity if he/she is in the party. Return the celebrity's label if there is a celebrity in the party. If there is no celebrity, return -1.
*/

// Forward declaration of the knows API.
bool knows(int a, int b);


/* Solution 1. Linear time solution O(n).
For two person i and j, check knows(i, j). Two outcomes:
1. if i knows j, then for sure i is not celebrity
2. if i does not know j, then for sure j is not celebrity.
Thus for each comparison, we can rule out one person.

We can do a linear run, each time compare the next person with the current celebrity candidate. In the end, we will have one candidate x. Then we simply check if everyone knows x, and x does not know anyone.

One optimization is that in the first pass, we already checked that x does not know every one after x. So the second loop only checks people before x.
*/

class Solution {
public:
    int findCelebrity(int n) {
        int x = 0;
        for(int i = 0; i < n; ++i)
            if(knows(x, i))  x = i;
        for(int i = 0; i < x; ++i)
            if(knows(x, i)) return -1;
        for(int i = 0; i < n; ++i)
            if(!knows(i, x)) return -1;
// the last two loops can be combined into one
//         for(int i = 0; i < n; ++i)
//            if((i < x && knows(x, i)) || !knows(i, x) ) return -1;
        return x;
    }
};

// Solution 2. Divide and conquer solution O(nlgn) time. O(lgn) space for the recursive calls.

class Solution {
public:
    int findCelebrity(int n) {
        int x = helper(0, n-1);
        if(x == -1) return -1;
        for(int i = 0; i < n; ++i)  {
            if(x == i) continue;
            if(knows(x, i) || !knows(i, x) ) return -1;
        }
        return x;
    }
    //check possible celebrity among [i .. j]
    int helper(int i, int j) {
        if(j == i) return i;
        int mid = (i+j)/2;
        int x1 = helper(i, mid);
        int x2 = helper(mid+1, j);
        if(x1 == -1) return x2;
        if(x2 == -1) return x1;
        if(knows(x1, x2)) return x2;
        else return x1;
    }
};

// Solution 3. similar to divide and conquer, but use auxiliary vector, O(n) space.

class Solution {
public:
    int findCelebrity(int n) {
        vector<int> curr(n, 0), next;
        for(int i = 0; i < n; ++i) curr[i] = i;
        while(curr.size() > 1) {
            for(int i = 0; i+1 < curr.size(); i += 2) {
                bool fwd = knows(curr[i], curr[i+1]);
                bool bwd = knows(curr[i+1], curr[i]);
                if(fwd ^ bwd) {
                    if(fwd) next.push_back(curr[i+1]);
                    else next.push_back(curr[i]);
                }
            }
            if(curr.size() & 1) next.push_back(curr.back());
            curr.swap(next);
            next.clear();
        }
        //finally check the only possible candidate
        if(curr.empty()) return -1;
        int j = curr[0];
        for(int k = 0; k < n; ++k) {
            if(k == j) continue;
            if(!knows(k, j) || knows(j, k)) return -1;
        }
        return j;
    }
};


/**************************************************** 
 ***    279,Medium,Perfect Squares 
 ****************************************************/

/*
Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9. 
*/

// Top down dynamic programming with memoization. Use an auxiliary array to store the answers. Using an unordered_map takes much longer time!
// For each number, start with 2*2, subtract as many squares as possible (e.g. 13, subtract 3 times and get 1). Then try 3*3, 4*4 ...
// Record already solved solutions in the array for later fast retrieval.

class Solution {
public:
    int numSquares(int n) {
        if(n == 0) return 1;
        if(n <= 3) return n;
        dict.resize(n+1, -1);
        dict[1] = 1;
        dict[2] = 2;
        dict[3] = 3;
        return helper(n);
    }
    int helper(int n) {
        if(dict[n] >= 0) return dict[n];
        int count = n;
        for(int i = 2; i <= n/i; ++i) {
             count = min(count, helper(n%(i*i)) + n/(i*i));
        }
        dict[n] = count;
        return count;
    }

    vector<int> dict;
};


/**************************************************** 
 ***    280,Medium,Wiggle Sort 
 ****************************************************/

/*
Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

For example, given nums = [3, 5, 2, 1, 6, 4], one possible answer is [1, 6, 2, 5, 3, 4]. 
*/

// Linear solution:
/* Scan left to right, two passes
 First pass arranges i and i+1 for even i such that nums[i] >= nums[i+1].
 Second pass arranges i and i+1 for odd i such that nums[i] <= nums[i+1].
 In second pass, we could have (i is odd), then we simply swap i and i+1.
               *                   *
           *                 * \  /
        *           =>      /   *
   *                       *
   (i-1 i) (i+1 
*/

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return;
        for(int i = 0; i+1 < n; i += 2) {
            if(nums[i] > nums[i+1])  swap(nums[i], nums[i+1]);
        }
        for(int i = 1; i+1 < n; i += 2) {
            if(nums[i] < nums[i+1])  swap(nums[i], nums[i+1]);
        }
    }
};

// One pass linear solution. We can combine the two passes into one pass.
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return;
        for(int i = 0; i+1 < n; i++) {
            if(!(i & 1) && nums[i] > nums[i+1]) swap(nums[i], nums[i+1]);
            if((i & 1) && nums[i] < nums[i+1]) swap(nums[i], nums[i+1]);
        }
    }
};

// Another O(nlgn) solution using sort. First sort, then swap ajacent pairs.
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return;
        sort(nums.begin(), nums.end());
        for(int i = 1; i+1 < n; i+=2) {
            swap(nums[i] nums[i+1]);
        }
    }
};

/**************************************************** 
 ***    281,Medium,Zigzag Iterator 
 ****************************************************/

/*
Given two 1d vectors, implement an iterator to return their elements alternately.

For example, given two 1d vectors:

v1 = [1, 2]
v2 = [3, 4, 5, 6]

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1, 3, 2, 4, 5, 6].

Follow up: What if you are given k 1d vectors? How well can your code be extended to such cases?

Clarification for the follow up question - Update (2015-09-18):
The "Zigzag" order is not clearly defined and is ambiguous for k > 2 cases. If "Zigzag" does not look right to you, replace "Zigzag" with "Cyclic". For example, given the following input:

[1,2,3]
[4,5,6,7]
[8,9]

It should return [1,4,8,2,5,9,3,6,7]. 
*/

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */

// Solution 1. Maintain an array of pointers, which always points to the the next valid value. After obtaining the next value, move pointer to next valid value.

class ZigzagIterator {
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        nums.push_back(v1); 
        nums.push_back(v2);
        n = 2;
        indices.resize(n, 0);        
        arrayIdx = 0;
        while(arrayIdx < n && nums[arrayIdx].empty()) arrayIdx++;
    }

    int next() {
        if(arrayIdx == n) return -1;

        int idx = indices[arrayIdx];
        int val = nums[arrayIdx][idx];

        indices[arrayIdx]++;
        int i = (arrayIdx+1) % n;
        while(i != arrayIdx && indices[i] == nums[i].size()) i = (i+1) % n;
        if(i == arrayIdx && indices[i] == nums[i].size()) arrayIdx = n; // no available elements, set arrayIdx to n
        else arrayIdx = i; //found next available array index

        return val;
    }

    bool hasNext() {
        return arrayIdx < n;
    }
private:
    vector<vector<int> > nums;
    vector<int> indices; //current position in each array
    int arrayIdx; //current array index
    int n; //number of arrays
};

// Solution 2. Maintain a queue of iterator pairs, each pair corresponding to the beginning and end of an array. Each time dequeue a pair,
// and if the array is not exhausted, enqueue again.
class ZigzagIterator {
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        if(!v1.empty()) q.push(make_pair(v1.begin(), v1.end()));
        if(!v2.empty()) q.push(make_pair(v2.begin(), v2.end()));
    }

    int next() {
        auto beg = q.front().first;
        auto end = q.front().second;
        q.pop();
        if(beg+1 < end) q.push(make_pair(beg+1, end));
        return *beg;
    }

    bool hasNext() {
        return !q.empty();
    }
    queue<pair<vector<int>::iterator, vector<int>::iterator> > q;
};

/**************************************************** 
 ***    284,Medium,Peeking Iterator 
 ****************************************************/

/*
Given an Iterator class interface with methods: next() and hasNext(), design and implement a PeekingIterator that support the peek() operation -- it essentially peek() at the element that will be returned by the next call to next().

Here is an example. Assume that the iterator is initialized to the beginning of the list: [1, 2, 3].

Call next() gets you 1, the first element in the list.

Now you call peek() and it returns 2, the next element. Calling next() after that still return 2.

You call next() the final time and it returns 3, the last element. Calling hasNext() after that should return false.

Hint:

    Think of "looking ahead". You want to cache the next element.
    Is one variable sufficient? Why or why not?
    Test your design with call order of peek() before next() vs next() before peek().
    For a clean implementation, check out Google's guava library source code. 

Follow up: How would you extend your design to be generic and work with all types, not just integer?
*/

// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
    struct Data;
	Data* data;
public:
	Iterator(const vector<int>& nums);
	Iterator(const Iterator& iter);
	virtual ~Iterator();
	// Returns the next element in the iteration.
	int next();
	// Returns true if the iteration has more elements.
	bool hasNext() const;
};

// Store a cache in peekingIterator. Remember to set and unset the boolean tag.

class PeekingIterator : public Iterator {
public:
        PeekingIterator(const vector<int>& nums) : Iterator(nums) {
            // Initialize any member here.
            // **DO NOT** save a copy of nums and manipulate it directly.
            // You should only use the Iterator interface methods.
            hasPeek = false; 
            peekVal = -1;
        }

    // Returns the next element in the iteration without advancing the iterator.
        int peek() {
            if(!hasPeek) {
                peekVal = Iterator::next();
                hasPeek = true;
            }
            return peekVal;
        }

        // hasNext() and next() should behave the same as in the Iterator interface.
        // Override them if needed.
        int next() {
            if(hasPeek) {
                hasPeek = false;
                return peekVal;
            } else return Iterator::next();
        }

        bool hasNext() const {
            return hasPeek || Iterator::hasNext();
        }
private:
    bool hasPeek;
    int peekVal;
};


/**************************************************** 
 ***    285,Medium,Inorder Successor in BST 
 ****************************************************/

/*
Given a binary search tree and a node in it, find the in-order successor of that node in the BST.

Note: If the given node has no in-order successor in the tree, return null. 
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/*
Several cases:
1. If p has right subtree, then just return the minimum in right subtree.
2. Otherwise, need to go to its ancestors. First build a search path from root to p, then search backwards, if found a path going toward left, then the higher one is the successor.
3. If not found such path, that means p is lying at bottom right of tree, and there is no successor. Return NULL.
Caveats:
tree is BST! So don't use backtracking to seach for path, use O(logn) iterative approach utilizing BST properly!

*/

class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if(!root || !p) return NULL;
        if(p->right) return findMin(p->right);
        //need to find path from root to p
        vector<TreeNode*> path;
        bool found = findPath(root, p, path);
        if(!found) return NULL;
        int n = path.size(), i = 0;
        for(i = n-1; i > 0; i--) {
            //is left subtree
            if(path[i-1]->left == path[i]) return path[i-1];
        }
        return NULL;
    }
    bool findPath(TreeNode* root, TreeNode* p, vector<TreeNode*>& path) {
        while(root) {
            path.push_back(root);
            if(root == p) return true;
            else if(p->val < root->val) root = root->left;
            else root = root->right;
        }
        return false;
    }
    TreeNode* findMin(TreeNode* root) {
        while(root->left) root = root->left;
        return root;
    }
};

//Alternative solution using a stack
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if(!root || !p) return NULL;
        if(p->right) return findMin(p->right);
        //need to find path from root to p
        stack<TreeNode*> path;
        bool found = findPath(root, p, path);
        if(!found) return NULL;
        while(!path.empty()) {
            TreeNode *ancestor = path.top(); 
            path.pop(); 
            //is left subtree
            if(!path.empty() && path.top()->left == ancestor) return path.top();
        }
        return NULL;
    }
    bool findPath(TreeNode* root, TreeNode* p, stack<TreeNode*>& path) {
        while(root) {
            path.push(root);
            if(root == p) return true;
            else if(p->val < root->val) root = root->left;
            else root = root->right;
        }
        return false;
    }
    TreeNode* findMin(TreeNode* root) {
        while(root->left) root = root->left;
        return root;
    }
};



/**************************************************** 
 ***    286,Medium,Walls and Gates 
 ****************************************************/

/*
You are given a m x n 2D grid initialized with these three possible values.

-1 - A wall or an obstacle.
0 - A gate.
INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

For example, given the 2D grid:
INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
  0  -1 INF INF
After running your function, the 2D grid should be:
  3  -1   0   1
  2   2   1  -1
  1  -1   2  -1
  0  -1   3   4
*/
  
// Standard multi-source BFS. First identify all sources, then BFS using two vectors.

class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        if(rooms.empty() || rooms[0].empty()) return;
        int m = rooms.size(), n = rooms[0].size();
        vector<pair<int, int> > curr, next;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(rooms[i][j] == 0) curr.push_back(make_pair(i, j));
            }
        }
        int d = 0; //distance from gate
        while(!curr.empty()) {
            d++; //increase distance
            for(auto pos : curr) {
                int i = pos.first, j = pos.second;
                //try 4 neighbors
                if(i > 0 && rooms[i-1][j] == INT_MAX) { rooms[i-1][j] = d;  next.push_back(make_pair(i-1, j)); }
                if(j > 0 && rooms[i][j-1] == INT_MAX) { rooms[i][j-1] = d;  next.push_back(make_pair(i, j-1)); }
                if(i < m-1 && rooms[i+1][j] == INT_MAX) { rooms[i+1][j] = d;  next.push_back(make_pair(i+1, j)); }
                if(j < n-1 && rooms[i][j+1] == INT_MAX) { rooms[i][j+1] = d;  next.push_back(make_pair(i, j+1)); }
            }
            curr.swap(next);
            next.clear();
        }
    }
};

/**************************************************** 
 ***    289,Medium,Game of Life 
 ****************************************************/

/*
According to the Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."

Given a board with m by n cells, each cell has an initial state live (1) or dead (0). Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):

Any live cell with fewer than two live neighbors dies, as if caused by under-population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by over-population..
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
Write a function to compute the next state (after one update) of the board given its current state.

Follow up: 
Could you solve it in-place? Remember that the board needs to be updated at the same time: You cannot update some cells first and then use their updated values to update other cells.
In this question, we represent the board using a 2D array. In principle, the board is infinite, which would cause problems when the active area encroaches the border of the array. How would you address these problems?
*/

// Solution using bit manipulation to do it in-place.
// Caveat: should store the old value in lower digit! otherwise the nb function cannot properly retrieve the old state from the top left (already processed) and bottom right (not yet processed)

class Solution {
public:
    //bit operation. Use lower digit to represent old state.
    void gameOfLife(vector<vector<int>>& board) {
        if(board.empty() || board[0].empty()) return;
        int m = board.size(), n = board[0].size();
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                int nbcount = nb(board, i, j);
                if(board[i][j] == 1) board[i][j] = (nbcount == 2 || nbcount == 3)*2 + 1;
                else board[i][j] = (nbcount == 3)*2;
            }
        }
        //remove the value from higher digit
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                board[i][j] >>= 1; //remove old value in lower digit
            }
        }
    }
    int nb(vector<vector<int> >& board, int i, int j) {
        int count = 0;
        int m = board.size(), n = board[0].size();
        for(int ii = max(0, i-1); ii <= min(m-1, i+1); ii++) {
            for(int jj = max(0, j-1); jj <= min(n-1, j+1); jj++) {
                count += (board[ii][jj] & 1); //get old value from lower digit
            }
        }
        count -= board[i][j]; //ignore itself
        return count;
    }
};

/**************************************************** 
 ***    294,Medium,Flip Game II 
 ****************************************************/

/*
You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -, you and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a move and therefore the other person will be the winner.

Write a function to determine if the starting player can guarantee a win.

For example, given s = "++++", return true. The starting player can guarantee a win by flipping the middle "++" to become "+--+".

Follow up:
Derive your algorithm's runtime complexity.
*/

// Solution 1. Backtracking. Remember to retrace.

class Solution {
public:
    bool canWin(string s) {
        if(s.empty()) return false;
        if(s.size() == 1) return false;
        return canWinUtil(s);
    }
    bool canWinUtil(string& s) {
        int n = s.size();
        for(int i = 0; i < n-1; i++) { //try all possibilities
            if(s[i] == '+' && s[i+1] == '+') {
                s[i] = s[i+1] = '-';
                bool wins = !canWinUtil(s);
                s[i] = s[i+1] = '+'; //retrace
                if(wins) return true;
            }
        }
        return false;
    }
};

// Solution 2. Dynamic programming. Store previous solutions in an unordered_map

class Solution {
public:
    bool canWin(string s) {
        if(s.empty()) return false;
        if(s.size() == 1) return false;
        return canWinUtil(s);
    }
    bool canWinUtil(string& s) {
        if(dp.count(s)) return dp[s];
        bool wins = false;
        int n = s.size();
        for(int i = 0; i < n-1; i++) { //try all possibilities
            if(s[i] == '+' && s[i+1] == '+') {
                s[i] = s[i+1] = '-';
                wins = !canWinUtil(s);
                s[i] = s[i+1] = '+'; //retrace
                if(wins) break;
            }
        }
        dp[s] = wins;
        return wins;
    }
    unordered_map<string, bool> dp;
};


/**************************************************** 
 ***    297,Medium,Serialize and Deserialize Binary Tree 
 ****************************************************/

/*
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

For example, you may serialize the following tree

    1
   / \
  2   3
     / \
    4   5

as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless. 
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

// Solution 1. Use leetcode format, null represented by "#". Do level-order traversal. For the last layer, ignore all "#"s (using hasNode variable)

class Codec {
public:
    //format: length 1 2 # ...
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root) return "";
        string str;
        string tmp;
        bool hasNodes = false;
        vector<TreeNode*> curr, next; //BFS, two levels
        curr.push_back(root);
        while(!curr.empty()) {
            tmp = "";
            hasNodes = false;
            for(auto node : curr) {
                if(node) {
                    hasNodes = true;
                    next.push_back(node->left);
                    next.push_back(node->right);
                }
                if(tmp != "") tmp += " ";
                tmp += node ? to_string(node->val) : "#";
            }
            if(hasNodes) str += (str == "") ? tmp : " " + tmp;
            swap(curr, next);
            next.clear();
        }
        return str;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data == "") return NULL;
        vector<TreeNode*> curr, next; //BFS, two levels
        int i = 0, n = data.size();
        string num = getNum(data, i);
        TreeNode *root = new TreeNode(atoi(num.c_str()));
        curr.push_back(root);
        while(i < n) {
            for(auto node : curr) {
                string l = getNum(data, i);
                string r = getNum(data, i);
                if(l != "#") {
                    node->left = new TreeNode(atoi(l.c_str()));
                    next.push_back(node->left);
                }
                if(r != "#") {
                    node->right = new TreeNode(atoi(r.c_str()));
                    next.push_back(node->right);
                }
            }
            swap(curr, next);
            next.clear();
        }
        return root;
    }

    string getNum(const string& s, int& i) {
        int n = s.size();
        int j = i;
        while(i < n && s[i] != ' ') i++;
        int len = i-j;
        i++; //move one step further
        return s.substr(j, len);
    }
};

// Solution 2. Recursive solution. Use brackets [root, left-subtree, right-subtree], so above tree will look like:
// [1 [ 2 [] [] ] [ 3 [4[][]] [5[][]] ] ]
// when deserializing, need to find the matching ']' to the first '['

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root) return "[]";
        else return "[" + to_string(root->val) + serialize(root->left) + serialize(root->right) + "]";
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        return deserializeUtil(data, 0, data.size()-1);
    }
    TreeNode* deserializeUtil(const string& data, int lo, int hi) {
        int len = hi-lo+1;
        if(len <= 2) return NULL;
        lo++; hi--; //remove the bounding "[]"
        int i = lo;
        while(i <= hi && data[i] != '[') i++; //i->'['
        int val = atoi(data.substr(lo, i-lo).c_str());
        TreeNode* root = new TreeNode(val);
        //find the matching ']'
        int j = i+1;
        int diff = 1; //# left - # right
        while(j <= hi) {
            if(data[j] == '[') diff++;
            else if(data[j] == ']') {
                diff--;
                if(diff == 0) break; //found matching ']'
            }
            j++;
        }
        root->left = deserializeUtil(data, i, j); //i->'[', j -> ']'
        root->right = deserializeUtil(data, j+1, hi);
        return root;
    }
};


/**************************************************** 
 ***    298,Medium,Binary Tree Longest Consecutive Sequence 
 ****************************************************/

/*
Given a binary tree, find the length of the longest consecutive sequence path.

The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The longest consecutive path need to be from parent to child (cannot be the reverse).

For example,
   1
    \
     3
    / \
   2   4
        \
         5
Longest consecutive sequence path is 3-4-5, so return 3.
   2
    \
     3
    / 
   2    
  / 
 1
Longest consecutive sequence path is 2-3,not3-2-1, so return 2.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
 // solution using a global variable
 
class Solution {
public:
    int longestConsecutive(TreeNode* root) {
        if(!root) return 0;
        max_len = 1; //at least one
        helper(root);
        return max_len;
    }
    //longest consecutive starting from root
    int helper(TreeNode* root) {
        if(!root) return 0;
        int hl = helper(root->left);
        int hr = helper(root->right);
        int h = 1;
        if(root->left && root->left->val == root->val + 1) h = max(h, hl+1);
        if(root->right && root->right->val == root->val + 1) h = max(h, hr+1);
        max_len = max(max_len, max(h, max(hl, hr)));
        return h;
    }
    int max_len;
};

/**************************************************** 
 ***    300,Medium,Longest Increasing Subsequence 
 ****************************************************/

/*
Given an unsorted array of integers, find the length of longest increasing subsequence. 

For example,
 Given [10, 9, 2, 5, 3, 7, 101, 18],
 The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length. 

Your algorithm should run in O(n2) complexity. 

Follow up: Could you improve it to O(n log n) time complexity? 
*/

/// Dynamic programming. O(n2) time. There is a solution using only O(nlgn) time.
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return 1;
        vector<int> dp(n, 1);
        int result = 0;
        for(int i = 1; i < n; ++i) {
            for(int j = 0; j < i; ++j) {
                if(nums[j] < nums[i]) dp[i] = max(dp[i], dp[j]+1);
            }
        }
        //pick maximum amount all dps
        for(int i = 0; i < n; ++i) result = max(result, dp[i]);
        return result;
    }
};

