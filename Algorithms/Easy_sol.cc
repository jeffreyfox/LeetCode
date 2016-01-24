/**************************************************** 
 ***    006,Easy,ZigZag Conversion 
 ****************************************************/

/*
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R

And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);

convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR". 
*/

// period is 2*numRows-2
// when numRows = 1, the resulting string is the same as original one.
class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows == 1) return s;
        string result = s;
        int p= 2*numRows-2;
        int k = 0, n = s.size();
        for(int ir = 0; ir < numRows; ++ir) {
            for(int j = ir; j < n; j += p) {
                result[k++] = s[j];
                if(ir > 0 && ir < numRows-1) { //not first or last row
                    int idx = j+p-2*ir;
                    if(idx < n) result[k++] = s[idx]; //need to check if idx < n!
                }
            }
        }
        return result;
    }
};


/**************************************************** 
 ***    007,Easy,Reverse Integer 
 ****************************************************/

/*
Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321

For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
*/

// Solution using long to store intermediate results. Need to consider integer overflow.
// If y > INT_MAX, then overflow (y should always be positive since it is long and will not overflow), also don't need to check -y < INT_MIN, as it is redundant. (We won't end up with y = 2147483647, since the input x cannot be as large as 7463847412)

class Solution {
public:
    int reverse(int x) {
        int sgn = (x >= 0) ? 1 : -1;
        if (x == 0) return 0;
        if(x == INT_MIN) return 0;
        x = abs(x); // no overflow
        long y = 0;
        while (x) {
            y = y*10 + x%10;
            if(y > INT_MAX) return 0;
            x = x / 10;
        }
        return sgn > 0 ? y : -y;
    }
};

// Solution without using long. Need to consider integer overflow for both addition and mutiplication and abs. 
// check overflow for addition: two positive number adds up to a negative number (y < 0)
// check overflow for multiplication: a > INT_MAX / b
// check overflow for calculating absolute values: x == INT_MIN

// Can combine multiplication and addition overflow check into one. See the next solution.

class Solution {
public:
    int reverse(int x) {
        int sign = x > 0 ? 1 : -1;
        if(x == 0) return 0;
        if(x == INT_MIN) return 0;
        x = abs(x); //no overflow
        int y = 0;
        while(x) {
            if(y > INT_MAX / 10) return 0; //overflow
            y = y*10 + (x%10);
            if(y < 0) return 0; //overflow
            x /= 10;
        }
        y = sign > 0 ? y : -y; //no overflow
        return y;
    }
};

class Solution {
public:
    int reverse(int x) {
        int sign = x > 0 ? 1 : -1;
        if(x == 0) return 0;
        if(x == INT_MIN) return 0;
        x = abs(x); //no overflow
        int y = 0;
        while(x) {
            int r = x % 10;
            if(y > (INT_MAX - r) / 10) return 0; //overflow
            y = y*10 + r;
            x /= 10;
        }
        y = sign > 0 ? y : -y; //no overflow
        return y;
    }
};

/**************************************************** 
 ***    008,Easy,String to Integer (atoi) 
 ****************************************************/

/*
Implement atoi to convert a string to an integer.

Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.

Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible to gather all the input requirements up front.

The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.

The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.

If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.

If no valid conversion could be performed, a zero value is returned. If the correct value is out of the range of representable values, INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.
*/

/// Use a dfa (deterministic finite state automaton to process input string).
/// Stop when state goes to -1 and return the value obtained so far (do not return 0)
/// Be aware of overflow!

class Solution {
public:
    enum CharType {SPACE, SIGN, DIGIT, OTHER};
    //states: 
    // 0: only space read
    // 1: sign read
    // 2: digit read
    // -1: error
    int myAtoi(string str) {
        vector<vector<int> > dfa(3, vector<int>(4, -1));
        dfa[0][SPACE] = 0;
        dfa[0][SIGN] = 1;
        dfa[0][DIGIT] = 2;
        dfa[1][DIGIT] = 2;
        dfa[2][DIGIT] = 2;
        int sgn = 1;
        int ret = 0; 
        int state = 0;
        for(size_t i = 0; i < str.size(); ++i) {
            char c = str[i];
            int type = getType(c);
            state = dfa[state][type];
            if(state == 1) sgn = (c == '-' ? -1 : 1);
            else if(state == 2) {
               int num = c - '0';
               if((INT_MAX - num) / 10 < ret) return (sgn == 1) ? INT_MAX : INT_MIN;
               ret = ret*10 + num;
            } else if(state == -1) {
               return sgn*ret; //return current calcualted value
            }
        }
        return sgn*ret;
    }
    CharType getType(char c) {
        if(c >= '0' && c <= '9') return DIGIT;
        else if(c == '+' || c == '-') return SIGN;
        else if(c == ' ') return SPACE;
        else return OTHER;
    }
};

/// Solution without using dfa. First ignore all trailing spaces, then read possible signs, then read digits until a non-digit character appears or reaching the end. Be aware of overflow!

class Solution {
public:
    int myAtoi(string str) {
        int ret = 0;
        int n = str.size();
        int i = 0;
        while(i < n && str[i] == ' ') i++;
        if(i == n) return 0;
        int sgn = 1;
        if(str[i] == '-') { sgn = -1; i++; }
        else if (str[i] == '+') { i++; }
        for(; i < n; i++) {
           char c = str[i];
           if(c >= '0' && c <= '9') {
               int num = c - '0';
               if((INT_MAX - num) / 10 < ret) return sgn == -1 ? INT_MIN : INT_MAX;
               ret = ret*10 + num;
           } else return sgn*ret;
        }
        return sgn*ret;
    }
};

/**************************************************** 
 ***    009,Easy,Palindrome Number 
 ****************************************************/

/*
Determine whether an integer is a palindrome. Do this without extra space.

Some hints:

Could negative integers be palindromes? (ie, -1)

If you are thinking of converting the integer to string, note the restriction of using extra space.

You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", you know that the reversed integer might overflow. How would you handle such case?

There is a more generic way of solving this problem.
*/

// Most straightforward solution: construct the reverse number from x, and compare with x
// Doesn't handle overflow explicitly because when overflow happens, y != x

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        int y = 0, num = x;
        while (num > 0) {
            y = y * 10 + num % 10;
            num /= 10;
        }
        return y == x;
    }
};

// Another solution without any overflow issue.
// Store a variable mask that is the largest power of 10 smaller or equal to x.
// Then use it as a mask to get the MSD and compare with the LSD. Next time strip off MSD and LSD and repeat, until the two digits meet.

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        //determine minimum power of 10 smaller or equal than x
        int mask = 1;
        int y = x/10;
        while (mask <= y) mask *= 10; 
        while (mask > 1) {
            if (x / mask != x % 10) return false;
            x = (x % mask) / 10; //strip off first and last digit
            mask /= 100; //update mask
        }
        return true;
    }
};

// Another solution by comparing only half digits.

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        if (x == 0) return true;
        int nd = 0; //number of digits of x
        int xx = x;
        while(xx) {
            xx /= 10;
            nd++;
        }
        int y = 0;
        for(int i = 0; i < nd / 2; ++i) {
            y = 10*y + x%10;
            x /= 10;
        }
        if(nd & 1 == 1) x /= 10; //remove additional digit
        return x == y;
    }
};

/**************************************************** 
 ***    013,Easy,Roman to Integer 
 ****************************************************/

/*
Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.
*/

// Solution 1:
// Scan from left to right. Get the value of next character and compare with current one.
// If current one is larger, add to sum and move forward one step
// If current one is smaller, add (next-curr) and move forward two steps

class Solution {
public:
    int romanToInt(string s) {
        int n = s.size();
        int val = 0;
        for (int i = 0; i < n; ++i) {
            int curr = char2num(s[i]);
            int next = (i < n-1) ? char2num(s[i+1]) : 0;
            if (next > curr) {val += next-curr; i++; }
            else val += curr;
        }
        return val;
    }
    
    int char2num(char c) {
        switch (c) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50; 
            case 'C': return 100;
            case 'D': return 500; 
            case 'M': return 1000; 
            default:  return 0;
        }
    }
};

// Solution 2:
// Scan from right to left. check current value against last value
// If current value is larger or equal than last value, add to sum (e.g. XI, add 10)
// If current value is smaller, substract from sum (e.g. IX, subract 1)
// Underlying assumption is that we won't have invalid string like "IVX"

class Solution {
public:
    int romanToInt(string s) {
        int n = s.size();
        int val = 0;
        int last(0), curr(0);
        for (int i = n-1; i >= 0; --i) {
            curr = char2num(s[i]);
            if (curr >= last) val += curr;
            else val -= curr;
            last = curr;
        }
        return val;
    }
    
    int char2num(char c) {
        switch (c) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50; 
            case 'C': return 100;
            case 'D': return 500; 
            case 'M': return 1000; 
            default:  return 0;
        }
    }
};

/**************************************************** 
 ***    014,Easy,Longest Common Prefix 
 ****************************************************/

/*
Write a function to find the longest common prefix string amongst an array of strings. 
*/

// Compare all strings against first string. Two nested loops. When found a mismatch, simply return the maximum length found so far.
// If no mismatch found, return full first string
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty()) return "";
        int n = strs.size();
        if(n == 1) return strs[0];
        int ns = strs[0].size();
        for(int j = 0; j < ns; ++j) { //j loops over each string
            for(int i = 1; i < n; ++i) { //i loops over vector of strings
                if(j == strs[i].size() || strs[i][j] != strs[0][j])  //found a mismatch!
                    return strs[0].substr(0, j); //return s[0, j)
            }
        }
        return strs[0];
    }
};

// Another solution, need to break out two nested loops.
// Compare all strings against first string

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int n = strs.size();
        if (n == 0) return string();
        if (n == 1) return strs[0];
        string s;
        bool stop = false;
        for (int j = 0; j < strs[0].size(); ++j) {
            stop = false;
            for (int i = 1; i < n; ++i)
                if (j == strs[i].size() || strs[i][j] != strs[0][j]) { stop = true; break; }
            if (stop) break;
            s += strs[0][j];
        }
        return s;
    }
};

/**************************************************** 
 ***    019,Easy,Remove Nth Node From End of List 
 ****************************************************/

/*
Given a linked list, remove the nth node from the end of list and return its head.

For example,

   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes 1->2->3->5.

Note:
Given n will always be valid.
Try to do this in one pass. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/// Solution 1. Use dummy head node. Two while loops.
/// Two pointers, first and last. Let last move forward by n steps. And then left first and last move together until last reaches the tail.
/// Then the node to be removed is first-next.

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *first(dummy), *last(dummy);
        while(n) {
            last = last->next;
            n--;
        }
        while(last->next) {
            first = first->next; last = last->next;
        }
        //delete first->next;
        ListNode* tmp = first->next;
        first->next = tmp->next;
        delete tmp;
        //return new head
        head = dummy->next;
        delete dummy;
        return head;
    }
};

/// Solution 2. Same idea, but one pass (slightly simplified code).

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *first(dummy), *last(dummy);
        while(last->next) {
            last = last->next;
            if(--n < 0) first = first->next;
        }
        
        //delete first->next;
        ListNode* tmp = first->next;
        first->next = tmp->next;
        delete tmp;
        //return new head
        head = dummy->next;
        delete dummy;
        return head;
    }
};



/**************************************************** 
 ***    020,Easy,Valid Parentheses 
 ****************************************************/

/*
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
*/

// Use a stack. When seeing a left parenthesis, push to stack; otherwise check against top of stack
// After reaching the end of string, need to check if stack is empty! (e.g. '[' is not valid)

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if(isLeft(c)) st.push(c);
            else if (st.empty() || !match(st.top(), c)) return false; //is right, no match
            else st.pop(); //match, pop out
        }
        return st.empty();
    }
    
    bool isLeft(char c) {
        return c == '(' || c == '[' || c == '{';
    }
    bool isRight(char c) {
        return c == '(' || c == '[' || c == '{';
    }
    bool match(char c1, char c2) {
        return (c1 == '(' && c2 == ')') ||
                (c1 == '[' && c2 == ']') ||
                (c1 == '{' && c2 == '}');
    }
};

/**************************************************** 
 ***    021,Easy,Merge Two Sorted Lists 
 ****************************************************/

/*
Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Use dummy head, and a tail pointer to track end of sorted list.
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0), *p(&dummy);
        ListNode *tail = p;
        while(l1 && l2) {
            if(l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        if(l1) tail->next = l1;
        else tail->next = l2;
        return p->next;
    }
};

/**************************************************** 
 ***    026,Easy,Remove Duplicates from Sorted Array 
 ****************************************************/

/*
Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

For example,
Given input array nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the new length. 
*/

// Solution with one loop, two pointers
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return n;
        int i = 0, j = 1;
        while(j < n) {
            if(nums[j] != nums[i])  nums[++i] = nums[j];
            j++;
        }
        return i+1;
    }
};

// A slightly different solution (nested while loops)
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return n;
        int i = 0, j = 1;
        while(1) {
            while(j < n && nums[j] == nums[i]) j++;
            if(j == n) break;
            nums[++i] = nums[j++];
        }
        return i+1;
    }
};

/**************************************************** 
 ***    027,Easy,Remove Element 
 ****************************************************/

/*
Given an array and a value, remove all instances of that value in place and return the new length.

The order of elements can be changed. It doesn't matter what you leave beyond the new length. 
*/

// Solution 1, fastest. Just maintain two pointers. Since we don't care about elements == val, we don't use fancy color sort algorithms.

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if(nums.empty()) return 0;
        int i(0), j(0), n = nums.size();
        for(int j = 0; j < n; ++j) {
            if(nums[j] != val) nums[i++] = nums[j];
        }
        return i;
    }
};

// Solution 2, two color sort.
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        //[0 .. i-1] != val, [i, j-1] == val, [j, n-1] TBD
        if(nums.empty()) return 0;
        int i = 0, j = 0, n = nums.size();
        while(j < n) {
            if(nums[j] == val) j++;
            else swap(nums[j++], nums[i++]);
        }
        return i;
    }
};

// Solution. variation of solution 2.
/// Similar to two-color problem, use two pointers i, and j. Loop invariant:
/// 1. nums[0 .. i-1] != val
/// 2. nums[i .. j] to be determined
/// 3. nums[j .. end) == val
/// when i and j cross, return i

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int i = 0, j = nums.size()-1;
        while (i <= j) {
            if (nums[i] != val) i++;
            else swap(nums[i], nums[j--]);
        }
        return i;
    }
};


/**************************************************** 
 ***    028,Easy,Implement strStr() 
 ****************************************************/

/*
Implement strStr().

Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
*/

/// Classical pattern search problem. 
/// Solution 1. Brute-force solution, O(MN) in the worst case

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        int i(0), j(0);
        for(i = 0; i < n && j < m; ++i) {
            if(haystack[i] == needle[j]) j++;
            else { i-=j; j = 0; }
        }
        if(j == m) return i-j;
        else return -1;
    }
};

// Solution 2. A varient of brute-force solution
class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size(), i(0), j(0);
        while(i < n && j < m) {
            if(haystack[i] == needle[j]) { i++; j++; }
            else {i = i-j+1; j = 0; }
        }
        if(j == m) return i-j;
        else return -1;
    }
};

// Solution 3. KMP algorithm with transfer function.
/*
We define the transfer function f[j] = k as the length of longest prefix of p[0 .. j-1] such that
f[0 .. k-1] == f[j-k .. j-1], 0 <= k < j
we don't allow k to equal j to avoid the trivial case where prefix is the string itself.
Therefore, whenever we see a mismatch between t[i] and p[j], we can directly make j jump to k = f[j], and i stays unchanged, so that t[i] is compared with p[k] (we know for sure that p[0 .. k-1] matches with t[i-k, i-1].
One corner case is that when mismatch happens at first character of pattern, i.e. j = 0. In this case we just increment i and keep j unchanged.

e.g. 01234   5
     abcab | cabd
     abcab | d    mismatch at j = 5, f[5] = 2
     01234   5   
=>   abcab | cabd
        ab | cabd
        01   23   j jumps to f[j] = 2

How to build transfer function for the pattern strign? We use an elegant dynamic programming approach. Say we know f[j-1] = k, now we calculate f[j], where we need to examine p[j-1].
We simply compare p[j-1] with p[k].
If they are equal, then we found that f[j] = k+1.
e.g. abcabc,  f[5] = 2 (ab), then f[6] = 3 because p[3] = [5] = c.
If they are not equal, we need to continue searching f[k] until k is less than zero. e
e.g. acadaca x acadaca d, f[15] = 7 (acadaca), for f[16], since p[7] != p[16], we need to examine f[7]. Since f[7] = 3 (aca), and p[4] = p[16], we know f[16] = 4 (acad)
Boundary case: f[0] = -1 for later convenience, f[1] = 0.

Thus we have come up with the following loop:
    f[0] = -1; f[1] = 0;
    for(int j = 2; j <= m; ++j) { //length j
        char c = needle[j-1];
        int k = f[j-1]; //result for previous
        while(k >= 0 && needle[k] != c) k = f[k];
        f[j] = k+1; //either k = -1, or needle[k] == c
    }

We can further optimize, and let k be the f value for the last calculation. Initially, k = f[1] = 0.
After each calculation, we update k's value by k = k+1, and then assign it to f[j].
Two case:
1. k = -1 after while loop, which indicates no such prefix exists, in this case by definition f[j] = 0, we let f[j] = ++k which is OK.
2. k >= 0 after while loop, which we know that needle[k] == c. This means that the maximum prefix for for pj is p[0..k] including k, and thus f[j] = ++k is also OK.
This has lead to the following loop:
    f[0] = -1; f[1] = 0; k = 0; // k is result for previous
    for(int j = 2; j <= m; ++j) { //length j
        while(k >= 0 && needle[k] != needle[j-1]) k = f[k];
        f[j] = ++k; //after while loop, either k = -1, or needle[k] == needle[j-1]
    }
*/

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        vector<int> f(m+1, -1); //jump position for p[0. i-1) of length i
        f[1] = 0; 
        for(int j = 2; j <= m; ++j) { //length j, f[1] will lead to 0
            char c = needle[j-1];
            int k = f[j-1];
            while(k >= 0 && needle[k] != c) k = f[k];
            f[j] = k+1; //either f[k] = -1, or t[f[k]] = c
        }
        int i(0), j(0);
        while(i < n && j < m) {
            if(haystack[i] == needle[j]) { i++; j++; }
            else if(j == 0) i++;
            else j = f[j];
        }
        return (j == m) ? i-j : -1;
    }
};

//slightly optimized KMP.

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        vector<int> f(m+1, -1); //jump position for p[0. i-1) of length i
        int k = -1; //k is result from previous step
        for(int j = 1; j <= m; ++j) { //length j, f[1] will lead to 0
            while(k >= 0 && needle[k] != needle[j-1]) k = f[k];
            f[j] = ++k; //either f[k] = -1, or t[f[k]] = c
        }
        int i(0), j(0);
        while(i < n && j < m) {
            if(haystack[i] == needle[j]) { i++; j++; }
            else if(j == 0) i++;
            else j = f[j];
        }
        return (j == m) ? i-j : -1;
    }
};


/**************************************************** 
 ***    036,Easy,Valid Sudoku 
 ****************************************************/

/* Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.

A partially filled sudoku which is valid.

Note:
A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated. 

*/

/// Check each row, column and block, record the state of each check.
/// Can use a single integer to record the state, using bit operations
///  1  1  1  1  1  1  1  1  1
/// '9'       ...           '1'
/// caveat: when calculating i/j index based on block index, 3*(ib/3)+jb/3 != (3*ib+jb)/3 
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int state = 0;

        //check rows
        for (int ir = 0; ir < 9; ++ir) {
            state = 0;
            for (int jc = 0; jc < 9; ++jc) {
                char c = board[ir][jc];
                if(c == '.') continue;
                int x = 1 << (c -'0');
                if (state & x) return false;
                state |= x;
            }
        }
        //check columns
        for (int jc = 0; jc < 9; ++jc) {
            state = 0;
            for (int ir = 0; ir < 9; ++ir) {
                char c = board[ir][jc];
                if(c == '.') continue;
                int x = 1 << (c -'0');
                if (state & x) return false;
                state |= x;
            }
        }
        //check blocks
        for (int ib = 0; ib < 9; ++ib) {
            state = 0;
            for (int jb = 0; jb < 9; ++jb) {
                char c = board[3*(ib/3)+jb/3][3*(ib%3)+jb%3];
                if(c == '.') continue;
                int x = 1 << (c -'0');
                if (state & x) return false;
                state |= x;
            }
        }
        return true;
    }
};

//Another solution using 3 bit vectors
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<int> row(9, 0), col(9, 0), block(9, 0); //bit status array
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j) {
                if(board[i][j] != '.') {
                    int k = i/3*3 + j/3;
                    int state = 1 << (board[i][j] - '1');
                    if(state & (row[i] | col[j] | block[k])) return false;
                    row[i] |= state;
                    col[j] |= state;
                    block[k] |= state;
                }
            }
        }
        return true;
    }
};


/**************************************************** 
 ***    038,Easy,Count and Say 
 ****************************************************/

/*
The count-and-say sequence is the sequence of integers beginning as follows:
1, 11, 21, 1211, 111221, ...

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.

Given an integer n, generate the nth sequence.

Note: The sequence of integers will be represented as a string. 
*/

/// Iterative solution, can place the countAndSay(string&) function directly into for loop to reduce unecessary function call cost
// Caveat: in num2str, should be res = c + res, not res += c + res;

class Solution {
public:
    string countAndSay(int n) {
        string res = "1";
        for(int i = 1; i < n; ++i) {
            res = countAndSay(res);
        }
        return res;
    }
    
    string countAndSay(const string& str) {
        int n = str.size();
        int count = 1;
        string res;
        for(int i = 1; i < n; ++i) {
            if(str[i] == str[i-1]) count++;
            else {
                res += num2str(count) + str[i-1];
                count = 1; //new character
            }
        }
        res += num2str(count) + str[n-1];
        return res;
    }

    string num2str(int n) {
        if(n == 0) return "0";
        string res;
        while(n) {
            res = char(n % 10 + '0') + res;
            n /= 10;
        }
        return res;
    }
};

/// An old solution, use the last string, and scan from left to right to find the number of duplicated entries, and append count as string
class Solution {
public:
    string countAndSay(int n) {
        if (n <= 0) return "";
        if (n == 1) return "1";
        string s = countAndSay(n-1);
        string ret;
        int size = s.size();
        int i = 0, j = 0;
        char c = '\0';
        while(i < size) {
            char c = s[i];
            while(j < size && s[j] == c) j++;
            int cnt = j-i;
            ret += num2str(cnt) + c;
            i = j;
        }
        return ret;
    }
    string num2str(int n) {
        string ret;
        while(n) {
            ret = char('0' + (n % 10)) + ret;
            n /= 10;
        }
        return ret;
    }

};

/**************************************************** 
 ***    058,Easy,Length of Last Word 
 ****************************************************/

/*
Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

For example,
Given s = "Hello World",
return 5. 
*/

// Two pointers, i and j. Scan from right to left
// i is first non-space char, j is first space char after i (right -> left)

class Solution {
public:
    int lengthOfLastWord(string s) {
        int n = s.size();
        //scan from right end to left, find first non-space character
        int i = n-1;
        while (i >= 0 && s[i] == ' ') i--;
        if (i < 0) return 0;
        //scan from i to left, find first space character
        int j = i;
        while(j >= 0 && s[j] != ' ') j--;
        return i-j;
    }
};

/**************************************************** 
 ***    066,Easy,Plus One 
 ****************************************************/

/*
Given a non-negative number represented as an array of digits, plus one to the number.

The digits are stored such that the most significant digit is at the head of the list.
*/

// Optimization: copy digits to result, and then stop when carry == 0

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> result;
        if(digits.empty()) return result;
        int n = digits.size();
        result = digits;
        int carry = 1, sum = 0;
        for(int i = n-1; i >= 0 && carry > 0; i--) {
            sum = digits[i] + carry;
            carry = sum / 10;
            sum %= 10;
            result[i] = sum; //update result
        }
        if(carry > 0) result.insert(result.begin(), 1); //add a leading 1
        return result;
    }
};

/**************************************************** 
 ***    067,Easy,Add Binary 
 ****************************************************/

/*
Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100". 
*/

// General solution that works works for binary and hex and oct systems, except need to change R to 8 or 16 
class Solution {
public:
    string addBinary(string a, string b) {
        const int R = 2; //radix for binary system (R = 8/16 for oct/hex)
        int m = a.size(), n = b.size();
        int l = max(m, n);
        string c(l, '0');
        int carry(0), sum(0); 
        for (int i = 0; i < l; ++i) {
            int v1 = (i < m) ? char2int(a[m-1-i]) : 0;
            int v2 = (i < n) ? char2int(b[n-1-i]) : 0;
            sum = carry + v1 + v2;
            carry = sum / R;
            sum = sum % R;
            c[l-1-i] = int2char(sum);
        }
        if (carry > 0) c = "1" + c;
        return c;
    }
    
    int char2int(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        return 0;
    }
    
    char int2char(int n) {
        if (n >= 0  && n <= 9)  return n + '0';
        if (n >= 10 && n <= 15) return n - 10 + 'A';
        return '0';
    }
};

/* Another solution using bit operator to calculate sum and carry
            sum = v1 ^ v2 ^ carry;
            carry = (v1 & v2) | (v1 & carry) | (v2 & carry);

// An alternative is use:
            sum = v1 + v2 + carry;
            carry = sum / 2;
            sum %= 2;
*/

class Solution {
public:
    string addBinary(string a, string b) {
        int l1 = a.size(), l2 = b.size();
        int l = max(l1, l2);
        string result(l, '0');
        int sum = 0, carry = 0;
        //i counts from right to left
        for(int i = 0; i < l; ++i) {
            int v1 = (i >= l1) ? 0 : a[l1-i-1] - '0';
            int v2 = (i >= l2) ? 0 : b[l2-i-1] - '0';
            sum = v1 ^ v2 ^ carry;
            carry = (v1 & v2) | (v1 & carry) | (v2 & carry);
            result[l-i-1] = sum + '0';
        }
        if(carry > 0) result = '1' + result;
        return result;
    }
};

/**************************************************** 
 ***    070,Easy,Climbing Stairs 
 ****************************************************/

/*
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top? 
*/

/// Fibonacci series, dynamic programming (bottom-up)
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        vector<int> sol(n+1, 0);
        sol[1] = 1; sol[2] = 2;
        for (int i = 3; i <= n; ++i)
            sol[i] = sol[i-1] + sol[i-2];
        return sol[n];    
    }
};

// Space optimized version. Only need value for the last 2 steps.
class Solution {
public:
    int climbStairs(int n) {
        if(n <= 2) return n;
        int curr = 0, last = 2, last_last = 1;
        for(int i = 2; i < n; ++i) {
            curr = last + last_last;
            last_last = last;
            last = curr;
        }
        return curr;
    }
};


/**************************************************** 
 ***    083,Easy,Remove Duplicates from Sorted List 
 ****************************************************/

/*
Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Since head will never be removed, do not need a dummy head pointer

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* p = head, *q = head->next;
        while(q) {
            if(p->val == q->val) { //delete q
                p->next = q->next;
                delete q;
                q = p->next;
            } else { //move forward
                p = q;
                q = q->next;
            }
        }
        return head;
    }
};

/**************************************************** 
 ***    088,Easy,Merge Sorted Array 
 ****************************************************/

/*
Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2. The number of elements initialized in nums1 and nums2 are m and n respectively.
*/

// Best solution: start backwards, utilize the extra space after nums1, only O(1) extra space needed.
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m-1, j = n-1, k = m+n-1;
        while(i >= 0 || j >= 0) {
            if(j < 0) break;
            else if(i < 0) nums1[k--] = nums2[j--];
            else nums1[k--] = nums1[i] <= nums2[j] ? nums2[j--] : nums1[i--];
       }
    }
};

// A slightly more concise solution
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m-1, j = n-1, k = m+n-1;
        while(j >= 0) {
            nums1[k--] = (i < 0 || nums1[i] <= nums2[j]) ? nums2[j--] : nums1[i--];
       }
    }
};

// An old solution: merge procedure in merge sort. No sentinel. Need extra array of length O(m+n).

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int tot = m+n;
        vector<int> aux(tot, 0);
        for (int i = 0, j = 0, k = 0; i < m || j < n; ) {
            int v1 = (i < m) ? nums1[i] : INT_MAX;
            int v2 = (j < n) ? nums2[j] : INT_MAX;
            if (v1 < v2) { aux[k++] = v1; i++; }
            else { aux[k++] = v2; j++; }
        }
        for (int i = 0; i < tot; ++i) nums1[i] = aux[i];
    }
};

/**************************************************** 
 ***    100,Easy,Same Tree 
 ****************************************************/

/*
Given two binary trees, write a function to check if they are equal or not.

Two binary trees are considered equal if they are structurally identical and the nodes have the same value. 
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

// Do it recursively.
// Caveats: remember to compare the values of the two nodes!

class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if((p == NULL) ^ (q == NULL)) return false; //one null, the other not
        if(p == NULL) return true; //both are null
        //both are not null 
        return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

//alternative solution
class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if(p == NULL) return q == NULL;
        if(q == NULL) return false;
        //both are not null 
        return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};


/**************************************************** 
 ***    101,Easy,Symmetric Tree 
 ****************************************************/

/*
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3

But the following is not:

    1
   / \
  2   2
   \   \
   3    3
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

// Recursive solution. check if the left and right subtrees are symmetric or not
// Two non-empty trees are symmetric iff:
// 1. root1->val = root2->val &&
// 2. 1's left is symmetric to 2's right &&
// 3. 2's left is symmetric to 1's right

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(root == NULL) return true;
        return isSymmetric(root->left, root->right);
    }
    
    bool isSymmetric(TreeNode* left, TreeNode *right) {
        if(left == NULL) return right == NULL;
        if(right == NULL) return false;
        return p->val == q->val && isSymmetric(p->left, q->right) && isSymmetric(p->right, q->left);
    }
};


/**************************************************** 
 ***    102,Easy,Binary Tree Level Order Traversal 
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

/// Classical solution using a queue

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Solution using one queue and a customized struct Element

class Solution {
public:
    struct Element {
        TreeNode *node;
        int level;
        Element(TreeNode *n, int l) : node(n), level(l) {}
    };
    
    vector<vector<int>> levelOrder(TreeNode* root) {
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
        return ret;
    }
};

// Solution using one queue and std::pair (4ms)
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > result;
        if(!root) return result;
        deque<pair<TreeNode*, int> > q; //include level
        q.push_back(make_pair(root, 0));
        int currLevel = -1;
        while(!q.empty()) {
            TreeNode *node = q.front().first;
            int level = q.front().second;
            q.pop_front();
            if(level > currLevel) { 
                result.push_back(vector<int>());  //start a new level
                currLevel = level;
            }
            if(node->left) q.push_back(make_pair(node->left, level+1));
            if(node->right) q.push_back(make_pair(node->right, level+1));
            result[currLevel].push_back(node->val);
        }
        return result;
    }
};

// Solution using 2 vectors (queues), one for current level and one for next level (8ms)
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > result;
        if(!root) return result;
        vector<TreeNode*> current, next;
        current.push_back(root);
        while(!current.empty()) {
            result.push_back(vector<int>()); //start a new level (for current)
            for(auto node : current) {
                if(node->left) next.push_back(node->left);
                if(node->right) next.push_back(node->right);
                result.back().push_back(node->val); //push value to result
            }
            current.swap(next);
            next.clear();
        }
        return result;
    }
};

// Recursive solution:
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > result;
        if(!root) return result;
        vector<TreeNode*> current;
        current.push_back(root);
        int level = 0;
        levelOrder(current, result, level);
        return result;
    }
    void levelOrder(vector<TreeNode*>& current, vector<vector<int> >& result, int level) {
        if(current.empty()) return;
        result.push_back(vector<int>());
        vector<TreeNode*> next;
        for(auto it : current) {
            if(it->left) next.push_back(it->left);
            if(it->right) next.push_back(it->right);
            result[level].push_back(it->val);
        }
        levelOrder(next, result, level+1);
    }
};


/**************************************************** 
 ***    104,Easy,Maximum Depth of Binary Tree 
 ****************************************************/

/*
Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
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

// Recursive solution. Easy.

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};

/**************************************************** 
 ***    107,Easy,Binary Tree Level Order Traversal II 
 ****************************************************/

/*
Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree {3,9,20,#,#,15,7},

    3
   / \
  9  20
    /  \
   15   7

return its bottom-up level order traversal as:

[
  [15,7],
  [9,20],
  [3]
]
*/

// Classical solution using BFS. Reverse result vector in the end.
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
    struct Element {
        TreeNode *node;
        int level;
        Element(TreeNode *n, int l) : node(n), level(l) {}
    };
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
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
        reverse(ret.begin(), ret.end()); //reverse result
        return ret;
    }
};


/**************************************************** 
 ***    110,Easy,Balanced Binary Tree 
 ****************************************************/

/*
Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1. 
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

// Recursive solution. A tree is balanced iff:
// 1. left and right subtree are both balanced
// 2. depth of left and right subtree differ by at most 1

// Use a recursive function to return whether the tree is balanced, and at the same time set the height of the tree to a reference variable

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        int h = 0;
        return isBalanced(root, h);
    }

    bool isBalanced(TreeNode* root, int& h) {
        if(!root) { h = 0; return true; }
        int hl = 0, hr = 0;
        if(!isBalanced(root->left, hl) || !isBalanced(root->right, hr) || abs(hl-hr) > 1) return false;
        h = max(hl, hr) + 1;
        return true;
    }
};

// Solution 2. One recursive function calculating tree depth and balanced information at the same time! No reference passing needed!
// Use a trick, the height returned has two meanings:
// If 0, means tree is not balanced
// If > 0, means the height of tree + 1. So empty node will return 1.

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return depth(root);
    }
    int depth(TreeNode* root) {
        if(!root) return 1;
        int hl = depth(root->left);
        int hr = depth(root->right);
        if(hl == 0 || hr == 0 || abs(hl - hr) > 1) return 0;
        return max(hl, hr)+1;
    }
};



/**************************************************** 
 ***    111,Easy,Minimum Depth of Binary Tree 
 ****************************************************/

/*
Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
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

// Caveat: This is different from the maxDepth problem!. There are several cases:
// 1. single node (no left or right children): minD = 1;
// 2. only left child: minD = 1 + minD of left
// 3. only right child: minD = 1 + minD of right
// 4. both childs: mindepth = 1 + min(minD of left, minD of right)
// The reason for the difference is that if a node has one empty subtree, and the other is not empty, the empty subtree does not count as the mininum depth path.

class Solution {
public:
    int minDepth(TreeNode* root) {
        if(!root) return 0;
        int minD = 0;
        if(!root->left)  minD = minDepth(root->right);
        else if(!root->right) minD = minDepth(root->left);
        else minD = min(minDepth(root->left), minDepth(root->right));
        return minD+1;
    }
};

// An alternative solution
class Solution {
public:
    int minDepth(TreeNode* root) {
        if(!root) return 0;
        if((root->left == NULL) ^ (root->right == NULL))  //only one subtree is not null
            return root->left ? minDepth(root->left)+1 : minDepth(root->right)+1;
        else //either both are null, or none are null
            return minD = min(minDepth(root->left), minDepth(root->right)) + 1;
    }
};

// The following solution is WRONG!
class Solution {
public:
    int minDepth(TreeNode* root) { //wrong solution. fails when left is NULL, and right is not
        if(!root) return 0;
        int d = 1;
        if(root->left) d = minDepth(root->left) + 1;
        if(root->right) d = min(d, minDepth(root->right)+1);
        return d;
    }
};



/**************************************************** 
 ***    112,Easy,Path Sum 
 ****************************************************/

/*
Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.
For example:
Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1

return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
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

// Caveats: 
// 1. empty root should return false.
// 2. leaf node mean node with NO children
// Several cases:
// 1. If reaching an leaf node, check if it's value is equal to sum
// 2. If an internal node, then check left or right subtree
// 3. if root is empty return false

class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;
        if(!root->left && !root->right) return (sum == root->val);
        sum -= root->val;
        return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);
    }
};

//Solution 2.
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;
        return dfs(root, sum);
    }
    bool dfs(TreeNode* root, int sum) {
        int x = root->val;
        //reaching leaf
        if(!root->left && !root->right && sum == x) return true;
        if(root->left && dfs(root->left, sum-x)) return true;
        if(root->right && dfs(root->right, sum-x)) return true;
        return false;
    }
};


/**************************************************** 
 ***    118,Easy,Pascal's Triangle 
 ****************************************************/

/*
Given numRows, generate the first numRows of Pascal's triangle.

For example, given numRows = 5,
Return

[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
*/

// Straightforward solution. Commented unecessary checks for better efficiency. 0ms.

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int> > result;
        result.resize(numRows);
        for(int r = 0; r < numRows; ++r) {
            int n = r+1; //number of elements in this row
            result[r].resize(n, 1); //initialize as 1
            for(int i = 1; i < n-1; ++i)  result[r][i] = result[r-1][i-1] + result[r-1][i];
        }
        return result;
    }
};

// Solution 2, with unecessary checks. 4ms.
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int> > result;
        if(numRows == 0) return result;
        result.resize(numRows);
        result[0] = vector<int>(1, 1);
        for(int r = 1; r < numRows; ++r) {
            int n = r+1; //number of elements in this row
            result[r].resize(n, 1); //initialize as 1
            for(int i = 1; i < n-1; ++i)  result[r][i] = result[r-1][i-1] + result[r-1][i];
        }
        return result;
    }
};


/**************************************************** 
 ***    119,Easy,Pascal's Triangle II 
 ****************************************************/

/*
Given an index k, return the kth row of the Pascal's triangle.

For example, given k = 3,
Return [1,3,3,1].

Note:
Could you optimize your algorithm to use only O(k) extra space? 
*/

// DP solution using only one vector. And avoided uncessary checks. Use an "old" variable to store the old value of current index, to be used for getting sum for the next element.

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> result(rowIndex+1, 1); //initialize as 1        
        for(int r = 2; r <= rowIndex; ++r) {
            int tmp = 0, old = 1;
            for(int i = 1; i < r; ++i) {
                tmp = result[i]; //store old value in temporary
                result[i] += old;
                old = tmp; //update old value
            }
        }
        return result;
    }
};

// Same as above. With additional unecessary checks.
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        if(rowIndex == 0) return vector<int>(1, 1);
        if(rowIndex == 1) return vector<int>(2, 1);
        vector<int> result(rowIndex+1, 0); //initialize as 0
        result[0] = result[1] = 1; 

        for(int r = 2; r <= rowIndex; ++r) {
            int n = r + 1;
            int tmp = 0, old = 1;
            for(int i = 1; i < n-1; ++i) {
                tmp = result[i]; //store old value in temporary
                result[i] += old;
                old = tmp; //update old value
            }
            result[n-1] = 1;
        }
        return result;
    }
};

// DP solution using two vectors. swapping.

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> currRow(rowIndex+1, 1);
        vector<int> nextRow(rowIndex+1, 1);
        currRow[0] = 1;
        for(int ir = 1; ir <= rowIndex; ++ir) { //ir has ir+1 elments [0 .. ir]
            nextRow[0] = nextRow[ir] = 1;
            for (int j = 1; j < ir; ++j)
                nextRow[j] = currRow[j-1] + currRow[j];
            currRow.swap(nextRow);
        }
        return currRow;
    }
};

/**************************************************** 
 ***    125,Easy,Valid Palindrome 
 ****************************************************/

/*
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Note:
Have you consider that the string might be empty? This is a good question to ask during an interview.

For the purpose of this problem, we define empty string as valid palindrome. 
*/

// Solution 1. Two pointers, O(n).
// ignore cases, so use toLower to convert to lower case
// isAlphaNumeric checks whether character is alpha-numeric

class Solution {
public:
    bool isPalindrome(string s) {
        if(s.empty()) return true;
        int n = s.size();
        int i(0), j(n-1);
        while (i < j) {
            if (!isAlphaNumeric(s[i])) i++;
            else if (!isAlphaNumeric(s[j])) j--;
            else if(toLower(s[i]) != toLower(s[j])) return false;
            else {i++; j--; } //equal, move on
        }
        return true;
    }
    bool isAlphaNumeric(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
    }
    char toLower(char c) {
        if(c >= 'A' && c <= 'Z') return c-'A'+'a';
        else return c;
    }
};

// Solution 2. Use another while loop inside, similar to quick-sort implementation.
// Note the ++i in isAphaNumeric, not i++
// If put two sentinels at front and end (s = 'a' + s + 'a';), then can save the boundary checks in the two inner while loop.

class Solution {
public:
    bool isPalindrome(string s) {
        if(s.empty()) return true;
        int n = s.size();
        int i(-1), j(n);
        while (i < j) {
            while (!isAlphaNumeric(s[++i])) if (i == j) return true;
            while (!isAlphaNumeric(s[--j])) if (j == i) return true;
            
            // i and j point to first meaningful characeter
            if (!isSame(s[i], s[j])) return false;
        }
        return true;
    }
    bool isAlphaNumeric(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
    }
    bool isSame(char c1, char c2) {
        if (c1 == c2) return true;
        if (c1 >= 'A' && c1 <= 'Z') return c2 == c1 + 32;
        if (c1 >= 'a' && c1 <= 'z') return c2 == c1 - 32;
    }
};


/**************************************************** 
 ***    155,Easy,Min Stack 
 ****************************************************/

/*
 Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

    push(x) -- Push element x onto stack.
    pop() -- Removes the element on top of the stack.
    top() -- Get the top element.
    getMin() -- Retrieve the minimum element in the stack.
*/

// Use two stacks, one is normal, the other tracks the minimum element at the time of insertion

class MinStack {
public:
    void push(int x) {
        s.push(x);
        if(ms.empty() || x <= ms.top()) ms.push(x);
    }

    void pop() {
        int x = s.top(); s.pop();
        if(x <= ms.top()) ms.pop();
    }

    int top() {
        return s.top();
    }

    int getMin() {
        return ms.top();
    }
private:
    stack<int> s, ms;
};


/**************************************************** 
 ***    157,Easy,Read N Characters Given Read4 
 ****************************************************/

/*
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function will only be called once for each test case. 
*/

// Forward declaration of the read4 API.
int read4(char *buf);

// Solution: keep track of current buffer write position, and total number of characters read so far. Also decrement n by the number of characters written.

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int once = 0, total = 0;
        while(n >= 4) {
            once = read4(buf);
            total += once; //increment character counter
            buf += once; //move buffer forward
            if(once < 4) return total; //reached end of file
            n -= 4; //for sure read-in 4 characters
        }
        //now n < 4
        if(n > 0) {
            once = read4(buf); //could read end of file
            total += min(once, n);
            buf += min(once, n);
        }
        return total;
    }
};

/**************************************************** 
 ***    165,Easy,Compare Version Numbers 
 ****************************************************/

/*
Compare two version numbers version1 and version2.
If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.

You may assume that the version strings are non-empty and contain only digits and the . character.
The . character does not represent a decimal point and is used to separate number sequences.
For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.

Here is an example of version numbers ordering:

0.1 < 1.1 < 1.2 < 13.37
*/

// C++ version without using any system libraries (iterative solution).
// Use two pointers to scan two version numbers. Calculate integer value on the fly until encountering a '.' or end of string
// Caveats:
// 1.1 > 1 (longer one is larger), but 1.0 = 1. Need to extract the next number for empty strings, which is set as zero.

class Solution {
public:
    int compareVersion(string version1, string version2) {
        int m = version1.size();
        int n = version2.size();
        int i = 0, j = 0;
        while (i < m || j < n) {
            int num1 = 0, num2 = 0;
            while (i < m && version1[i] != '.') {
                num1 = num1*10 + (version1[i]-'0');
                i++;
            }
            while (j < n && version2[j] != '.') {
                num2 = num2*10 + (version2[j]-'0');
                j++;
            }
            if      (num1 > num2) return  1;
            else if (num1 < num2) return -1;
            i++; j++; //remember to increment i and j!
        }
        return 0; //equal
    }
};

// Another solution. Recursive.
class Solution {
public:
    int compareVersion(string version1, string version2) {
        return compareVersion(version1, version2, 0, 0);
    }
    int compareVersion(const string& version1, const string& version2, int i, int j) {
        if(i >= version1.size() && j >= version2.size()) return 0; //termination
        //now neither has reached end
        int v1 = 0, v2 = 0;
        while(i < version1.size() && version1[i] != '.') {
            v1 = v1*10 + (version1[i++] - '0');
        }
        while(j < version2.size() && version2[j] != '.') {
            v2 = v2*10 + (version2[j++] - '0');
        }
        if(v1 > v2) return 1;
        else if(v1 < v2) return -1;
        return compareVersion(version1, version2, i+1, j+1); //equal, compare next
    }
};


/**************************************************** 
 ***    168,Easy,Excel Sheet Column Title 
 ****************************************************/

/*
Given a positive integer, return its corresponding column title as appear in an Excel sheet.

For example:

    1 -> A
    2 -> B
    3 -> C
    ...
    26 -> Z
    27 -> AA
    28 -> AB
*/

/*
Iterative solution. Radix-26 notation, can think of 0 as 0, and Z as A0.
remember to subtract 1.
 ABCD = 1*26^3 + 2*26^2 + 3*26 + 26, 
 ZZZZ = 26*26^3 + 26*26^2 + 26*26 + 26, 
The ZZZZ case, we can not just do / 26, because Z is just 26. But we can do -1, so to extract the last Z, we subtract one from the number, then the last number becomes 25, so when we do % 26, we end up wiht 25. Similarly, when we strip off the last Z, we can't just do / 26, since the last Z will give a 1, we can subtract one, and we are left with 26*26^2 + 26*26 + 26, which is just ZZZ.
*/

class Solution {
public:
    string convertToTitle(int n) {
        string ret;
        while(n) {
            int r = (n - 1) % 26; //r from 0 to 25
            ret = char('A'+r) + ret;
            n = (n - 1) / 26;
        }
        return ret;
    }
};

/**************************************************** 
 ***    170,Easy,Two Sum III - Data structure design 
 ****************************************************/

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

/**************************************************** 
 ***    171,Easy,Excel Sheet Column Number 
 ****************************************************/

/*
Related to question Excel Sheet Column Title

Given a column title as appear in an Excel sheet, return its corresponding column number.

For example:

    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28 
*/

// Iterative solution. Just 26-base counting.
// A-Z  : 1 - 26
//   AAA 
//   111 in 26-base counting

class Solution {
public:
    int titleToNumber(string s) {
        int v = 0;
        for(int i = 0; i < s.size(); ++i) {
            v = v*26+(s[i]-'A'+1);
        }
        return v;
    }
};

/**************************************************** 
 ***    172,Easy,Factorial Trailing Zeroes 
 ****************************************************/

/*
Given an integer n, return the number of trailing zeroes in n!.

Note: Your solution should be in logarithmic time complexity.
*/

// Check how many factors (2 or 5) are contained from 1 to n.
// e.g. n = 100, f = 5
// 5 appears 20 times as 1x5, 2x5 ... 20x5. 
// Then another 4 times from 1 to 20 (when we divide n by 5): 1x5, 2x5, 3x5, 4x5
// Then zero times from 1 to 4(when we divide n by 5).

// Number of trailing zeroes is the minimum of counts of 2s and 5s.
class Solution {
public:
    int trailingZeroes(int n) {
        if(n <= 1) return 0;
        return min(numFact(n, 2), numFact(n, 5));
    }
    //how many factors k do numbers 1 .. n have in total?
    int numFact(int n, int k) {
        int count = 0;
        while(n) {
            n /= k;
            count += n;
        }
        return count;
    }
};

/**************************************************** 
 ***    189,Easy,Rotate Array 
 ****************************************************/

/*
Rotate an array of n elements to the right by k steps.

For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].

Note:
Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.

[show hint]
Hint:
Could you do it in-place with O(1) extra space?

Related problem: Reverse Words in a String II
*/

// Solution 1. Three reverse passes.

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.empty()) return;
        int n = nums.size();
        k = k % n;
        if(k == 0) return;
        reverse(nums, 0, n);
        reverse(nums, 0, k);
        reverse(nums, k, n);
    }
    //reverse nums[beg, end). excluding end.
    void reverse(vector<int>& nums, int beg, int end) {
        int i = beg, j = end-1;
        while(i < j)  swap(nums[i++], nums[j--]);
    }
};

// Solution 2. Juggling method (do-while loop). Need to get gcd of two numbers

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.empty()) return;
        int n = nums.size();
        k = k % n;
        if(k == 0) return;
        int tmp = 0;
        for(int i = 0; i < gcd(k, n); ++i) {
            int j = i;
            tmp = nums[j];
            do {
                //copy nums[i] to nums[j]
                j = (j+k) % n;
                swap(tmp, nums[j]);
            } while(j != i);
        }
    }
    int gcd(int a, int b) {
        if(a == 0) return b;
        if(b == 0) return a;
        if(a > b) return gcd(b, a);
        return gcd(b-a, a);
    }
};

// Solution 3. Improved version of solution 2. Use shift insteaad of swapping, only swap once (similar idea to insertion sort).
// Also a simpler gcd algorithm (Euclid).
// If b == 0, return a,
// If b != 0, then return gcd(b, a%b). Two cases:
// if (b > a), then it goes to gcd(b, a), effectively swapping the two
// if (b == a), then it goes to gcd(b, 0), and it immediately returns b
// if (b < a), then it goes to gcd(b, a%b), and we effectively reduces the first argument from a to b.
// So the algorithm always decreases the first argument for each gcd run.

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.empty()) return;
        int n = nums.size();
        k = k % n;
        if(k == 0) return;
        for(int i = 0; i < gcd(k, n); ++i) {
            int j = i;
            int tmp = nums[j];
            while(1) {
                //copy nums[i] to nums[j]
                int l = (j-k+n) % n;
                if(l == i) break;
                nums[j] = nums[l];
                j = l;
            } 
            nums[j] = tmp;
        }
    }
    int gcd(int a, int b) {
        if(b == 0) return a;
        return gcd(b, a%b);
    }
/*  //iterative gcd, same idea as recursive one
    int gcd(int a, int b) {
        while(b) {
            int tmp = b;
            b = a % b;
            a = tmp;
        }
        return a;
    }        
*/
};

// Solution 4. Use a temp vector. O(n) space.

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.empty()) return;
        int n = nums.size();
        k = k % n;
        if(k == 0) return;
        vector<int> tmp(n, 0);
        for(int i = 0; i < n; ++i) 
            tmp[(i+k)%n] = nums[i];
        nums = tmp;
    }
};

// Solution 5. Shift one by one, will cause TLE. O(nk) time.
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.empty()) return;
        int n = nums.size();
        k = k % n;
        if(k == 0) return;
        for (int i = 0; i < k; ++i) {
            rotateByOne(nums);
        }
    }
    //reverse nums[beg, end)
    void rotateByOne(vector<int>& nums) {
        int reg = nums.back();
        for (int i = 0; i < nums.size(); ++i) {
            int tmp = nums[i];
            nums[i] = reg;
            reg = tmp;
        }
    }
};


/**************************************************** 
 ***    190,Easy,Reverse Bits 
 ****************************************************/

/*
Reverse bits of a given 32 bits unsigned integer.

For example, given input 43261596 (represented in binary as 00000010100101000001111010011100), return 964176192 (represented in binary as 00111001011110000010100101000000).

Follow up:
If this function is called many times, how would you optimize it?

Related problem: Reverse Integer
*/

// Solution 1. Similar to reverse integer. Get last digit and shift the original number to right, and new number left:
// 123, 0 => 3, 12 => 32, 1 => 321, 0
// Optimization: when the original number is zero, stop the for loop and shift the number by the proper amount.

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        if(n == 0) return 0;
        uint32_t m = 0;
        for(int i = 0; i < 32; ++i) {
            m = (m << 1) | (n & 1);
            n >>= 1;
            if(n == 0) return m << (31-i);
        }
        return m;
    }
};

// Solution 2 using exclusive or.

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t lo = 0x00000001, hi = 0x80000000, XOR = 0;
        uint32_t d = 31;//distance between two bits to be swapped
        while(lo < hi) { //swap two bits
            //XOR has value only at the two bits, other bits are 0
            XOR = (((n & lo ) << d) ^ (n & hi)) | (((n & hi ) >> d) ^ (n & lo));
            n = n ^ XOR; //only two bits are affected, as A ^ 0 = A
            lo = lo << 1;
            hi = hi >> 1;
            d -= 2;
        }
        return n;
    }
};

// Solution 3. Swap in groups.
// For 8 bit number, need 3 passes. For 32 bit, 5 passes.
// [1 2 3 4]-[5 6 7 8] => 5 6 7 8 1 2 3 4
// [5 6]-[7 8] [1 2]-[3 4] => 7 8 5 6 3 4 1 2
// [7]-[8] [5]-[6] [3]-[4] [1]-[2] => 8 7 6 5 4 3 2 1

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        n = ((n & 0xFFFF0000) >> 16) | ((n & 0x0000FFFF) << 16);
        n = ((n & 0xFF00FF00) >>  8) | ((n & 0x00FF00FF) <<  8);
        n = ((n & 0xF0F0F0F0) >>  4) | ((n & 0x0F0F0F0F) <<  4);
        n = ((n & 0xCCCCCCCC) >>  2) | ((n & 0x33333333) <<  2);
        n = ((n & 0xAAAAAAAA) >>  1) | ((n & 0x55555555) <<  1);
        return n;
    }
};


/**************************************************** 
 ***    191,Easy,Number of 1 Bits 
 ****************************************************/

/*
Write a function that takes an unsigned integer and returns the number of ’1' bits it has (also known as the Hamming weight).

For example, the 32-bit integer ’11' has binary representation 00000000000000000000000000001011, so the function should return 3.
*/

// Bit operation.
//    n    = 1010101000
//    n-1  = 1010100111
// n&(n-1) = 1010100000 (removed last 1 digit!)

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        while(n) {
            n = n & (n-1);
            count++;
        }
        return count;
    }
};

/**************************************************** 
 ***    198,Easy,House Robber 
 ****************************************************/

/*
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
*/

// DP solution, use one vector max_all, whose i-th entry means the maximum amount for robbing houses 0 to i.
// Recursive formula:
// max_all[i] = max of the following two cases:
// including i-th house, then i-1 should be excluded, thus: max_all[i-2] + nums[i]
// excluding i-th house, then no requirements on i-1, thus: max_all[i-1]

class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return nums[0];
        vector<int> max_all(n, 0); //maximum value from nums[0..i]
        max_all[0] = nums[0];
        max_all[1] = max(nums[0], nums[1]);
        for (int i = 2; i < n; ++i) {
            max_all[i] = max(max_all[i-2] + nums[i], max_all[i-1]);
        }
        return max_all[n-1];
    }
};

// Optimized solution, since we only need the last two values for max_all, we can save the space by using two variables
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);
        int lastlast = nums[0];
        int last = max(nums[0], nums[1]);
        int curr = 0;
        for (int i = 2; i < n; ++i) {
            curr = max(lastlast + nums[i], last);
            lastlast = last; last = curr;
        }
        return curr;
    }
};

// Old DP solution. Use two variables to track max_include and max_all

class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return nums[0];
        vector<int> max_inc(n, 0); //maximum value from nums[0..i] including nums[i]
        vector<int> max_all(n, 0); //maximum value from nums[0..i] whether or not including nums[i]
        max_inc[0] = max_all[0] = nums[0];
        max_inc[1] = nums[1]; max_all[1] = max(nums[0], nums[1]);
        for (int i = 2; i < n; ++i) {
            max_inc[i] = nums[i] + max_all[i-2];
            max_all[i] = max(max_inc[i], max_all[i-1]);
        }
        return max_all[n-1];
    }
};

/**************************************************** 
 ***    202,Easy,Happy Number 
 ****************************************************/

/*
Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

Example: 19 is a happy number

    12 + 92 = 82
    82 + 22 = 68
    62 + 82 = 100
    12 + 02 + 02 = 1
*/

/// Use a hash map (set) to record all numbers and check if we encounter a previous one (loop).
/// If found a "1" then is a happy number, otherwise not.
class Solution {
public:
    bool isHappy(int n) {
        if(n == 0) return false;
        if(n == 1) return true;
        unordered_set<int> dict;
        dict.insert(1);
        while(dict.count(n) == 0) {
            dict.insert(n);
            n = calc(n);
        }
        return n == 1;
    }
    
    int calc(int n) {
        int result = 0;
        while(n) {
            int r = n % 10;
            result += r*r;
            n /= 10;
        }
        return result;
    }
};

/**************************************************** 
 ***    203,Easy,Remove Linked List Elements 
 ****************************************************/

/*
Remove all elements from a linked list of integers that have value val.

Example
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Solution using a dummy head

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if(!head) return NULL;
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode *p = dummy, *q = dummy->next;
        //q is one step ahead of p
        while(q) {
            if(q->val == val) { //delete q
                p->next = q->next;
                delete q;
                q = p->next;
            } else { //just move forward
                p = p->next;
                q = q->next;
            }
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};


/**************************************************** 
 ***    204,Easy,Count Primes 
 ****************************************************/

/*
Description:

Count the number of prime numbers less than a non-negative number, n.
*/

// Sieve of Eratosthenes

// Solution 1. Not optimized solution.
class Solution {
public:
    int countPrimes(int n) {
        if(n < 2) return 0;
        vector<bool> prime(n, true); //is prime: [0, n-1]
        for(int i = 2; i*i < n; ++i) {
            for(int j = i; i*j < n; ++j) {
                prime[i*j] = false;
            }
        }
        int count = 0;
        for(int i = 2; i < n; ++i)  count += prime[i];
        return count;
    }
};

// Solution 2. Optimize solution.
class Solution {
public:
    int countPrimes(int n) {
        if(n < 2) return 0;
        vector<bool> prime(n, true); //is prime: [0, n-1]
        for(int i = 2; i*i < n; ++i) {
            if(!prime[i]) continue; //don't need to visit non-prime numbers again!
            for(int j = i*i; j < n; j += i) { // use j as index rather than i*j
                prime[j] = false;
            }
        }
        int count = 0;
        for(int i = 2; i < n; ++i)
            if(prime[i]) count ++;
        return count;
    }
};



/**************************************************** 
 ***    205,Easy,Isomorphic Strings 
 ****************************************************/

/*
Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.

For example,
Given "egg", "add", return true.

Given "foo", "bar", return false.

Given "paper", "title", return true.

Note:
You may assume both s and t have the same length.
*/

//Use two maps, one mapping s to t and the other backwards. Use indices array to mimic map for fast access. 

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if(s.size() != t.size()) return false;
        if(s.empty()) return true;
        int n = s.size();
        vector<int> s2t(256, -1), t2s(256, -1);
        for(int i = 0; i < n; ++i) {
            int a = s[i], b = t[i];
            if(s2t[a] == -1 && t2s[b] == -1) { //new entry, insert to both maps
                s2t[a] = b; t2s[b] = a;
            } else if(s2t[a] == b && t2s[b] == a) continue; //matches, continue
            else return false; //other cases, simply return false.
        }
        return true;
    }
};


/**************************************************** 
 ***    206,Easy,Reverse Linked List 
 ****************************************************/

/*
Reverse a singly linked list.

click to show more hints.
Hint:

A linked list can be reversed either iteratively or recursively. Could you implement both?
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Solution 1. Iterative solution. Use two pointers p and q. Temporary store q's next element.
// remember to set head->next to NULL at last step!

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head) return NULL;
        ListNode* p = head, *q = head->next; //q goes beyond p
        while(q) {
            ListNode *next = q->next;
            q->next = p;
            p = q;
            q = next;
        }
        head->next = NULL;
        return p;
    }
};

// Solution 2. Recursive solution. Set head's next pointer to NULL after calling reverse recursively for it's next. It's next will be assigned after traceback, when processing it's ancestor node.

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head) return NULL;
        if(!head->next) return head;
        ListNode *newhead = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;
        return newhead;
    }
};


/**************************************************** 
 ***    217,Easy,Contains Duplicate 
 ****************************************************/

/*
Given an array of integers, find if the array contains any duplicates. Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct. 
*/

// Solution 1. Use a set to store elements seen so far. O(n) space. O(n) time amortized.

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> dict;
        int n = nums.size();
        for(int i = 0; i < n; ++i) {
            if(dict.count(nums[i])) return true;
            dict.insert(nums[i]);
        }
        return false;
    }
};


// Solution 2. Presort the array, then do a linear search. O(1) space, O(nlgn) time. 

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for(int i = 0; i < n-1; ++i) {
            if(nums[i] == nums[i+1]) return true;
        }
        return false;
    }
};

/**************************************************** 
 ***    219,Easy,Contains Duplicate II 
 ****************************************************/

/*
Given an array of integers and an integer k, find out whether there are two distinct indices i and j in the array such that nums[i] = nums[j] and the difference between i and j is at most k. 
*/

// Solution 1. use a set to store the already seen elements. Maintain a sliding window of side k+1, when seeing a new element, remove the one that falls out of the window from the set. O(k) space. 28ms.
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> dict;
        int n = nums.size();
        for(int i = 0; i < n; ++i) {
            if(i > k) dict.erase(nums[i-k-1]);
            if(dict.count(nums[i])) return true;
            dict.insert(nums[i]);
        }
        return false;
    }
};

// Solution 2. Use a map to store the elements and its position. O(n) space. 32ms.

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> dict;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            int v = nums[i];
            unordered_map<int, int>::iterator it = dict.find(v);
            if (it == dict.end()) dict[v] = i; //init last position
            else if (i - it->second <= k) return true; //found!
            else it->second = i; //update last position
        }
        return false;
    }
};


/**************************************************** 
 ***    223,Easy,Rectangle Area 
 ****************************************************/

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

/**************************************************** 
 ***    225,Easy,Implement Stack using Queues 
 ****************************************************/

/*
Implement the following operations of a stack using queues.

    push(x) -- Push element x onto stack.
    pop() -- Removes the element on top of the stack.
    top() -- Get the top element.
    empty() -- Return whether the stack is empty.

Notes:

    You must use only standard operations of a queue -- which means only push to back, peek/pop from front, size, and is empty operations are valid.
    Depending on your language, queue may not be supported natively. You may simulate a queue by using a list or deque (double-ended queue), as long as you use only standard operations of a queue.
    You may assume that all operations are valid (for example, no pop or top operations will be called on an empty stack).
*/

// Solution 1. Use only one queue! Push O(n), others O(1). For push, the idea is to add the new element to end of queue, and then move front of queue to back of the new elemenet one by one.
class Stack {
public:
    // Push element x onto stack.
    void push(int x) {
        int n = q.size();
        q.push(x);
        for(int i = 0; i < n; ++i) {
            q.push(q.front());
            q.pop();
        }
    }

    // Removes the element on top of the stack.
    void pop() {
        q.pop();
    }

    // Get the top element.
    int top() {
        return q.front();
    }

    // Return whether the stack is empty.
    bool empty() {
        return q.empty();
    }
    queue<int> q;
};

// Solution 2. Use two queues. Push O(n), others O(1). The primary queue is ordered like a stack. The second queue serves like a loading area. When adding an element, first push to secondary queue, and then move elements from primary to secondary, and then swap primary and secondary.
// primary: 3 2 1, secondary add 4
// Migration: primary : empty, secondary 4 3 2 1
// swap the two: primary: 4 3 2 1, secondary empty.

class Stack {
public:
    // Push element x onto stack.
    void push(int x) {
        q2.push(x);
        while(!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1, q2);
    }

    // Removes the element on top of the stack.
    void pop() {
        q1.pop();
    }

    // Get the top element.
    int top() {
        return q1.front();
    }

    // Return whether the stack is empty.
    bool empty() {
        return q1.empty();
    }
private:
    queue<int> q1, q2;
};

// Solution 3. Push O(1), pop and top O(n).
class Stack {
public:
    // Push element x onto stack.
    void push(int x) {
        q1.push(x);
    }

    // Removes the element on top of the stack.
    void pop() {
        while(!q1.empty()) {
            int x = q1.front(); q1.pop();
            if(!q1.empty()) q2.push(x);
        }
        swap(q1, q2);
    }

    // Get the top element.
    int top() {
        int x = 0;
        while(!q1.empty()) {
            x = q1.front(); q1.pop();
            q2.push(x);
        }
        swap(q1, q2);
        return x;
    }

    // Return whether the stack is empty.
    bool empty() {
        return q1.empty();
    }
private:
    queue<int> q1, q2;
};



/**************************************************** 
 ***    226,Easy,Invert Binary Tree 
 ****************************************************/

/*
Invert a binary tree.

     4
   /   \
  2     7
 / \   / \
1   3 6   9

to

     4
   /   \
  7     2
 / \   / \
9   6 3   1

Trivia:
This problem was inspired by this original tweet by Max Howell:

    Google: 90% of our engineers use the software you wrote (Homebrew), but you can’t invert a binary tree on a whiteboard so fuck off.
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

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == NULL) return NULL;
        //swap left and right children
        swap(root->left, root->right);
        //recursively run invert on subtrees
        invertTree(root->left); //don't have to return the root
        invertTree(root->right);
        return root; //don't forget to return
    }
};


/**************************************************** 
 ***    228,Easy,Summary Ranges 
 ****************************************************/

/*
Given a sorted integer array without duplicates, return the summary of its ranges.

For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"]. 
*/

// two pointers
// be careful of overflow when converting from number to string (use unsigned int to store absolute value of an int is ok)

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> ret;
        int n = nums.size();
        int i(0), j(0);
        
        while (i < n && j < n) {
            j = i+1;
            while (j < n && nums[j] == nums[j-1]+1) j++;
            //j stops at one past end
            if (j-1 == i) ret.push_back(num2str(nums[i]));
            else ret.push_back(num2str(nums[i]) + "->" + num2str(nums[j-1]));
            i = j;
        }
        return ret;
    }
    string num2str(int n) {
        if (n == 0) return "0";
        int sign = (n > 0) ? 1 : -1;
        unsigned u = abs(n);
        string s;
        while (u) {
            char c = u % 10 + '0';
            s = c + s;
            u = u / 10;
        }
        if (sign < 0) s = '-' + s;
        return s;
    }
};

//Another solution using one while loop.
class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> result;
        if(nums.empty()) return result;
        int l = nums[0];
        int i = 0, n = nums.size();
        while(i < n) {
            if(i+1 == n || nums[i+1] > nums[i]+1)  { // nums[i] is the boundary
                result.push_back(getRange(l, nums[i]));
                if(i+1 < n) l = nums[i+1];
            }
            i++;
        }
        return result;
    }

    string getRange(int l, int r) {
        if(l == r) return num2str(l);
        else return num2str(l) + "->" + num2str(r);
    }
    string num2str(long n) {
        if(n == 0) return "0";
        bool neg = (n < 0);
        n = abs(n);
        string s;
        while(n) {
            s = char(n % 10 + '0') + s;
            n /= 10;
        }
        if(neg) s = "-" + s;
        return s;
    }
};


/**************************************************** 
 ***    231,Easy,Power of Two 
 ****************************************************/

/*
Given an integer, write a function to determine if it is a power of two.
*/

// use bit operations.
// Caveat: need to check if larger than 0!

class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n>0 && !(n&(n-1));
	// return !n && !(n & 0x80000000) && !(n&(n-1))
    }
};

/**************************************************** 
 ***    232,Easy,Implement Queue using Stacks 
 ****************************************************/

/*
Implement the following operations of a queue using stacks.

    push(x) -- Push element x to the back of queue.
    pop() -- Removes the element from in front of queue.
    peek() -- Get the front element.
    empty() -- Return whether the queue is empty.

Notes:

    You must use only standard operations of a stack -- which means only push to top, peek/pop from top, size, and is empty operations are valid.
    Depending on your language, stack may not be supported natively. You may simulate a stack by using a list or deque (double-ended queue), as long as you use only standard operations of a stack.
    You may assume that all operations are valid (for example, no pop or peek operations will be called on an empty queue).

*/

/// Use two stacks
/// Lazy push (into secondary stack), when pop/peek for the first time (primary stack s1 is empty), dump s2's elements into s1 in reverse order, then later pop/peek is O(1).

class Queue {
public:
    // Push element x to the back of queue.
    void push(int x) {
        s2.push(x);
    }

    // Removes the element from in front of queue.
    void pop(void) {
        if(s1.empty()) {
            while(!s2.empty()) {
                s1.push(s2.top()); s2.pop();
            }
        }
        s1.pop();
    }

    // Get the front element.
    int peek(void) {
        if(s1.empty()) {
            while(!s2.empty()) {
                s1.push(s2.top()); s2.pop();
            }
        }
        return s1.top();
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return s1.empty() && s2.empty();
    }
private:
    stack<int> s1, s2;
};


/**************************************************** 
 ***    234,Easy,Palindrome Linked List 
 ****************************************************/

/*
Given a singly linked list, determine if it is a palindrome.

Follow up:
Could you do it in O(n) time and O(1) space?
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/// 4 steps:
// 1. Find middle element
// 2. reverse second half of array
// 3. compare second half with first half
// 4. recover the original linked list (reverse second part again and connect to first part)

/// O(n) time, O(1) space

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(!head || !head->next) return true;
        ListNode *slow = head, *fast = head;
        while(fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *second = reverse(slow->next);
        ListNode *p = head, *q = second;
        bool result = true;
        while(q) {
            if(p->val != q->val) { result = false; break; }
            p = p->next; q = q->next;
        }
        slow->next = reverse(second);
        return result;
    }
    ListNode* reverse(ListNode *head) {
        if(!head || !head->next) return head;
        ListNode *p = head, *q = head->next;
        p->next = NULL;
        while(q) {
            ListNode *tmp = q->next;
            q->next = p;
            p = q; q = tmp;
        }
        return p;
    }
};


/**************************************************** 
 ***    235,Easy,Lowest Common Ancestor of a Binary Search Tree 
 ****************************************************/

/*
Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

        _______6______
       /              \
    ___2__          ___8__
   /      \        /      \
   0      _4       7       9
         /  \
         3   5

For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6. Another example is LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.
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

// Take advantage of the property of BST. Do it recursively.
// If root is same as either nodes, then root is LCA.
// If the two nodes are one different sides of root, then root is LCA.
// Otherwise recursively go to root's left or right subtree depending on which side of the root the nodes are at.
// Time complexity is O(h), where h is the height of tree.

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || !p || !q) return NULL;
        return LCA(root, p, q);
    }
    TreeNode* LCA(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return NULL;
        if(p == root || q == root) return root; //one is equal to root
        if((p->val < root->val) ^ (q->val < root->val)) return root; //lying on two sides of root
        if(p->val < root->val) return LCA(root->left, p, q);
        else return LCA(root->right, p, q);
    }
};



/**************************************************** 
 ***    237,Easy,Delete Node in a Linked List 
 ****************************************************/

/*
Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.

Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3, the linked list should become 1 -> 2 -> 4 after calling your function. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/// O(1) solution, just link current node's pointer to the next next node, delete the next node.
/// For safety, do the sanity check to ensure node is not null, or last node in the list.

class Solution {
public:
    void deleteNode(ListNode* node) {
        //first do some sanity check
        if(node == NULL || node->next == NULL) return;
        node->val = node->next->val;
        ListNode* t = node->next;
        node->next = t->next;
        delete t;
    }
};

/**************************************************** 
 ***    242,Easy,Valid Anagram 
 ****************************************************/

/*
Given two strings s and t, write a function to determine if t is an anagram of s.

For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false.

Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution to such case?
*/

/// Linear time solution by using a hash table (array indexing)
/// For unicode, we might use an unordered map (real hash table) to save memory space.

class Solution {
public:
    bool isAnagram(string s, string t) {
        int n = s.size();
        if (t.size() != n) return false;
        vector<int> cnt(256, 0);
        for (int i = 0; i < n; ++i) cnt[s[i]]++;
        for (int i = 0; i < n; ++i) {
            cnt[t[i]]--;
            if(cnt[t[i]] < 0) return false;
        }
        return true;
    }
};

// Solution 2. O(nlgn) solution using sorting.

class Solution {
public:
    bool isAnagram(string s, string t) {
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
};

/**************************************************** 
 ***    246,Easy,Strobogrammatic Number 
 ****************************************************/

/*
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to determine if a number is strobogrammatic. The number is represented as a string.

For example, the numbers "69", "88", and "818" are all strobogrammatic.
*/

// Checking front and end. Do not forget the middle character if length is odd.

class Solution {
public:
    bool isStrobogrammatic(string num) {
        int n = num.size();
        for(int i = 0; i < n/2; ++i) {
            char c1 = num[i];
            char c2 = num[n-i-1];
            if( (c1 == '0' && c2 == '0') ||
                (c1 == '1' && c2 == '1') ||
                (c1 == '6' && c2 == '9') ||
                (c1 == '8' && c2 == '8') ||
                (c1 == '9' && c2 == '6') ) continue;
            return false;
        }
        if(n % 2 == 1) {
            char c = num[n/2];
            if(c != '0' && c != '1' && c != '8') return false;
        }
        return true;
    }
};


/**************************************************** 
 ***    249,Easy,Group Shifted Strings 
 ****************************************************/

/*
Given a string, we can "shift" each of its letter to its successive letter, for example: "abc" -> "bcd". We can keep "shifting" which forms the sequence:

"abc" -> "bcd" -> ... -> "xyz"

Given a list of strings which contains only lowercase alphabets, group all strings that belong to the same shifting sequence.

For example, given: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"],
Return:

[
  ["abc","bcd","xyz"],
  ["az","ba"],
  ["acef"],
  ["a","z"]
]

Note: For the return value, each inner list's elements must follow the lexicographic order.
*/

// Convert each string to its "canonical form", which is shifted form such that first letter is 'a'. Use a dictionary to store the canonical form and associated entries in result vector. When seeing a new word, search in the map. If found, simply insert to the correct places, otherwise, insert to map, and append the new entry to the result vector.
// Caveats: when doing shifts, better shift towards 'a', not 'z', because 'z' is lying close to the end 127, and addition 'z' + 'z' can cause overflow (if char is implmemented as signed int in the machine). On the other hand 'a' is far from the left end 0 or -127, so it is safe.

class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        vector<vector<string> > result;
        unordered_map<string, int> dict;
        for(auto c : strings) {
            string s = convert(c);
            if(!dict.count(s)) { //not found
                dict[s] = result.size();
                result.push_back(vector<string>(1, c));
            } else { //found
                result[dict[s]].push_back(c);
            }
        }
        for(int i = 0; i < result.size(); ++i)
            sort(result[i].begin(), result[i].end());
        return result;
    }
    string convert(const string& s) {
        if(s.empty() || s[0] == 'a') return s;
        string t = s;
        int os = s[0] - 'a'; //offset
        for(int i = 0; i < t.size(); ++i) {
            t[i] -= os;
            if(t[i] < 'a') t[i] += 26;
        }
        return t;
    }
};



/**************************************************** 
 ***    252,Easy,Meeting Rooms 
 ****************************************************/

/*
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), determine if a person could attend all meetings.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return false. 
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

// First sort the interval according to starting times, then check whether each ajacent pair overlaps
// Criteria for not overlap:
// a.start <= b.end OR b.start <= a.end
// Then criteria for overlap is (applying boolean logic)
// a.start > b.end AND b.tart > a.end

bool compare_start(const Interval& a, const Interval& b) {
    return a.start < b.start;    
}

class Solution {
public:
    bool canAttendMeetings(vector<Interval>& intervals) {
        if(intervals.empty()) return true;
        int n = intervals.size();
        if(n == 1) return true;
        sort(intervals.begin(), intervals.end(), compare_start);
        for(int i = 1; i < n; ++i) {
            if(intervals[i].start < intervals[i-1].end && intervals[i-1].start < intervals[i].end) return false;
        }
        return true;
    }
};

/**************************************************** 
 ***    257,Easy,Binary Tree Paths 
 ****************************************************/

/*
 Given a binary tree, return all root-to-leaf paths.

For example, given the following binary tree:

   1
 /   \
2     3
 \
  5

All root-to-leaf paths are:

["1->2->5", "1->3"]
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

// Standard dfs solution (recursive). The numbers can be negative.
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        string tmp;
        if(!root) return result;
        dfs(root, tmp, result);
        return result;
    }
    void dfs(TreeNode *root, string tmp, vector<string>& result) {
        tmp += num2str(root->val);
        if(!root->left && !root->right) {
            result.push_back(tmp);
            return;
        }
        if(root->left) dfs(root->left, tmp+"->", result);
        if(root->right) dfs(root->right, tmp+"->", result);
    }

    string num2str(int n) {
        if(n == 0) return "0";
        int sign = n > 0 ? 1 : -1;
        n = abs(n);
        string s;
        while(n) {
            char c = n % 10 + '0';
            s = c + s;
            n /= 10;
        }
        if(sign == -1) s = "-" + s;
        return s;
    }
};

/**************************************************** 
 ***    258,Easy,Add Digits 
 ****************************************************/

/*
Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.

For example:

Given num = 38, the process is like: 3 + 8 = 11, 1 + 1 = 2. Since 2 has only one digit, return it.

Follow up:
Could you do it without any loop/recursion in O(1) runtime? 
*/

// Simple elementary school mathematics.
// Caveats: result is not simply num % 9, because it never gives the value 9.
// Only 0 return 0, positive integers always return 1 - 9.

class Solution {
public:
    int addDigits(int num) {
        if(num == 0) return 0;
        return (num-1) % 9 + 1;
    }
};


/**************************************************** 
 ***    263,Easy,Ugly Number 
 ****************************************************/

/*
Write a program to check whether a given number is an ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 6, 8 are ugly while 14 is not ugly since it includes another prime factor 7.

Note that 1 is typically treated as an ugly number. 
*/

// Solution using only one while loop (faster)
class Solution {
public:
    bool isUgly(int num) {
        if(num == 0) return false;
        while(num != 1) {
            if(num % 2 == 0) num /= 2;
            else if(num % 3 == 0) num /= 3;
            else if(num % 5 == 0) num /= 5;
            else return false;
        }
        return true;
    }
};

// Solution using three while loops (slower)
class Solution {
public:
    bool isUgly(int num) {
        if(num == 0) return false;
        while(num % 2 == 0) num /= 2;
        while(num % 3 == 0) num /= 3;
        while(num % 5 == 0) num /= 5;
        return num == 1;
    }
};

/**************************************************** 
 ***    266,Easy,Palindrome Permutation 
 ****************************************************/

/*
Given a string, determine if a permutation of the string could form a palindrome.

For example,
"code" -> False, "aab" -> True, "carerac" -> True.

Hint:

    Consider the palindromes of odd vs even length. What difference do you notice?
    Count the frequency of each character.
    If each character occurs even number of times, then it must be a palindrome. How about character which occurs odd number of times?
*/

// count occurences of each word. check wheather even or odd.

class Solution {
public:
    bool canPermutePalindrome(string s) {
        int n = s.size(); 
        if(n <= 1) return true;
        vector<bool> odd(256,false);
        for(int i = 0; i < n; ++i) {
            char c = s[i];
            odd[c] = ! odd[c];
        }
        int nodds = 0;
        for(int i = 0; i < 256; ++i) {
            if(odd[i]) nodds ++;
            if(nodds > 1) return false;
        }
        return true;
    }
};

/**************************************************** 
 ***    270,Easy,Closest Binary Search Tree Value 
 ****************************************************/

/*
Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.

Note:

    Given target value is a floating point.
    You are guaranteed to have only one unique value in the BST that is closest to the target.
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

// Iterative solution. Search down the tree.
// Caveat: Do not initialize mind as MAX_INT.
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        double mind = fabs(target - root->val);
        int result = root->val;
        while(root) {
            double diff = fabs(target - root->val);
            if(diff == 0.0) return target;
            if(diff < mind) {
                result = root->val;
                mind = diff;
            }
            if(target > root->val) root = root->right;
            else root = root->left;
        }
        return result;
    }
};


/**************************************************** 
 ***    276,Easy,Paint Fence 
 ****************************************************/

/*
There is a fence with n posts, each post can be painted with one of the k colors.

You have to paint all the posts such that no more than two adjacent fence posts have the same color.

Return the total number of ways you can paint the fence.

Note:
n and k are non-negative integers. 
*/

//Solution: dynamic programming, keep counts for two cases: last two colors are same, and different.

class Solution {
public:
    int numWays(int n, int k) {
        if(n == 0 || k == 0) return 0;
        if(n == 1) return k;
        if(n == 2) return k*k;
        int last_two_same = k, last_two_diff = k*(k-1);
        for(int i = 3; i <= n; ++i) {
            int tmp = last_two_diff;
            last_two_diff = (last_two_same+last_two_diff)*(k-1);
            last_two_same = tmp;
        }
        return last_two_same + last_two_diff;
    }
};

/**************************************************** 
 ***    278,Easy,First Bad Version 
 ****************************************************/

/*
You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.

Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.

You are given an API bool isBadVersion(version) which will return whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API. 
*/

// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

/// Binary search

class Solution {
public:
    int firstBadVersion(int n) {
        if(n == 0) return -1;
        int lo = 1, hi = n;
        //(1 .. lo) good, [lo, hi] TBD, (hi, n) bad
        while(lo <= hi) {
            int mid = lo + (hi - lo)/2;
            if(isBadVersion(mid)) hi = mid - 1;
            else lo = mid + 1;
        }
        return lo;
    }
};

/**************************************************** 
 ***    283,Easy,Move Zeroes 
 ****************************************************/

/*
Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].

Note:

    You must do this in-place without making a copy of the array.
    Minimize the total number of operations.
*/

// Solution 1. One loop. Avoid redundant assignments.

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        if(nums.empty()) return;
        int i(0), j(0), n = nums.size();
        for(int i = 0; i < n; ++i) {
            if(nums[i] != 0) {
                if(i != j) {
                    nums[j] = nums[i];
                    nums[i] = 0;
                }
                j++;
            }
        }
    }
};

// Solution 2. Two loops
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        if(nums.empty()) return;
        int i = 0;
        for(int j = i; j < n; ++j) {
           if(nums[j]) nums[i++] = nums[j];
        }
        while(i < n) {
           nums[i++] = 0;
        }
    }
};


/**************************************************** 
 ***    288,Easy,Unique Word Abbreviation 
 ****************************************************/

/*
An abbreviation of a word follows the form <first letter><number><last letter>. Below are some examples of word abbreviations:

a) it                      --> it    (no abbreviation)

     1
b) d|o|g                   --> d1g

              1    1  1
     1---5----0----5--8
c) i|nternationalizatio|n  --> i18n

              1
     1---5----0
d) l|ocalizatio|n          --> l10n

Assume you have a dictionary and given a word, find whether its abbreviation is unique in the dictionary. A word's abbreviation is unique if no other word from the dictionary has the same abbreviation.

Example:

Given dictionary = [ "deer", "door", "cake", "card" ]

isUnique("dear") -> false
isUnique("cart") -> true
isUnique("cane") -> false
isUnique("make") -> true
*/

// Your ValidWordAbbr object will be instantiated and called as such:
// ValidWordAbbr vwa(dictionary);
// vwa.isUnique("hello");
// vwa.isUnique("anotherWord");

// Solution 1. Use a map from abbreviated string to the set of original strings (260ms).
// e.g. dictionary = [ "deer", "door", "cake", "card" ]
// dict = 
//  d2r => (deer, door)
//  c2e => (cake)
//  c2d => (card)
// To check the new word, return unique if either of the two cases:
// 1. the abbreviated form does not exist in the map (e.g. candy).
// 2. the abbreviated form exists, but its set contains only the original word (e.g. cake).
	
class ValidWordAbbr {
public:
    ValidWordAbbr(vector<string> &dictionary) {
        for(auto s : dictionary) {
            dict[getAbbr(s)].insert(s);
        }
    }

    bool isUnique(string word) {
        auto it = dict.find(getAbbr(word));
        return it == dict.end() || (it->second.size() == 1 && it->second.count(word));
    }
    string getAbbr(string s) {
        int n = s.size();
        if(n <= 2) return s;
        else return s[0] + num2str(n-2) + s[n-1];
    }
    //n is positive integer
    string num2str(unsigned n) {
        if(n == 0) return "0";
        string s;
        while(n) {
            char c = n % 10 + '0';
            s = c + s;
            n /= 10;
        }
        return s;
    }
    unordered_map<string, unordered_set<string> > dict;
};

// Solution 2. Optimized, do not store the string as the key, but the hashed value (200ms).
class ValidWordAbbr {
public:
    ValidWordAbbr(vector<string> &dictionary) {
        for(auto s : dictionary) {
            dict[hash(s)].insert(s);
        }
    }

    bool isUnique(string word) {
        auto it = dict.find(hash(word));
        return it == dict.end() || (it->second.size() == 1 && it->second.count(word));
    }
    int hash(string s) {
        int n = s.size();
        if(n == 0) return -1;
        if(n == 1) return s[0]-'a';
        return s[0]+s[n-1]*26+n*676;
    }

    unordered_map<int, unordered_set<string> > dict;
};

// Solution 3. Further optimized, do not store the set of strings matching the hash value. Just store a single string. If a hash is associated with two different strings, then for sure there is no unique abbr. for this entry. Use empty string to represent this case.
class ValidWordAbbr {
public:
    ValidWordAbbr(vector<string> &dictionary) {
        for(auto s : dictionary) {
            int t = hash(s);
            if(!dict.count(t)) dict[t] = s;
            else if(dict[t] != s) dict[t] = "";
        }
    }

    bool isUnique(string word) {
        if(word == "") return true;
        auto it = dict.find(hash(word));
        return it == dict.end() || (it->second == word);
    }
    int hash(string s) {
        return s.front()+s.back()*26+s.size()*676;
    }

    unordered_map<int, string> dict;
};


/**************************************************** 
 ***    290,Easy,Word Pattern 
 ****************************************************/

/*
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

Examples:

    pattern = "abba", str = "dog cat cat dog" should return true.
    pattern = "abba", str = "dog cat cat fish" should return false.
    pattern = "aaaa", str = "dog cat cat dog" should return false.
    pattern = "abba", str = "dog dog dog dog" should return false.

Notes:
You may assume pattern contains only lowercase letters, and str contains lowercase letters separated by a single space. 
*/

// Use two dictionaries to record the bijection relation between pattern (char) and words (string). Standard DFS.
// Caveats: be careful of the index bounds for exiting dfs. Should be i >= m, not i == m.
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        return dfs(pattern, str, 0, 0);
    }
    bool dfs(const string& pattern, const string& str, int i, int j) {
        int m = pattern.size(), n = str.size();
        if(i >= m && j >= n) return true; //both reaches end at the same time
        if(i >= m || j >= n) return false; //only one reaches end
        char c = pattern[i];
        int k = j;
        while(k < n && str[k] != ' ') k++;
        string s = str.substr(j, k-j);
        unordered_map<char, string>::iterator it1 = pat2word.find(c);
        unordered_map<string, char>::iterator it2 = word2pat.find(s);
        if(it1 == pat2word.end() && it2 == word2pat.end()) { //not found
            pat2word[c] = s; word2pat[s] = c; //insert
            return dfs(pattern, str, i+1, k+1);
        } else if(it1 == pat2word.end() || it2 == word2pat.end()) { //not bijection
            return false;
        } else if(it1->second == s && it2->second == c) {
            return dfs(pattern, str, i+1, k+1);
        } else return false;
    }
    unordered_map<char, string> pat2word;
    unordered_map<string, char> word2pat;
};


/**************************************************** 
 ***    292,Easy,Nim Game 
 ****************************************************/

/*
You are playing the following Nim Game with your friend: There is a heap of stones on the table, each time one of you take turns to remove 1 to 3 stones. The one who removes the last stone will be the winner. You will take the first turn to remove the stones.

Both of you are very clever and have optimal strategies for the game. Write a function to determine whether you can win the game given the number of stones in the heap.

For example, if there are 4 stones in the heap, then you will never win the game: no matter 1, 2, or 3 stones you remove, the last stone will always be removed by your friend.

Hint:

    If there are 5 stones in the heap, could you figure out a way to remove the stones such that you will always be the winner?

*/

// Easy.
class Solution {
public:
    bool canWinNim(int n) {
        return n % 4;
    }
};

/**************************************************** 
 ***    293,Easy,Flip Game 
 ****************************************************/

/*
You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -, you and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a move and therefore the other person will be the winner.

Write a function to compute all possible states of the string after one valid move.

For example, given s = "++++", after one move, it may become one of the following states:

[
  "--++",
  "+--+",
  "++--"
]

If there is no valid move, return an empty list [].
*/

// Search for two consecutive '+'s, and modify them to '-'.

class Solution {
public:
    vector<string> generatePossibleNextMoves(string s) {
        vector<string> ret;
        int n = s.size();
        for(int i = 0; i < n-1; i++) {
            if(s[i] == '+' && s[i+1] == '+') {
               ret.push_back(s);
               ret.back()[i] = ret.back()[i+1] = '-';
            }
        }
        return ret;
    }
};


/**************************************************** 
 ***    299,Easy,Bulls and Cows 
 ****************************************************/

/*
You are playing the following Bulls and Cows game with your friend: You write down a number and ask your friend to guess what the number is. Each time your friend makes a guess, you provide a hint that indicates how many digits in said guess match your secret number exactly in both digit and position (called "bulls") and how many digits match the secret number but locate in the wrong position (called "cows"). Your friend will use successive guesses and hints to eventually derive the secret number.

For example:

Secret number:  "1807"
Friend's guess: "7810"

Hint: 1 bull and 3 cows. (The bull is 8, the cows are 0, 1 and 7.)

Write a function to return a hint according to the secret number and friend's guess, use A to indicate the bulls and B to indicate the cows. In the above example, your function should return "1A3B".

Please note that both secret number and friend's guess may contain duplicate digits, for example:

Secret number:  "1123"
Friend's guess: "0111"

In this case, the 1st 1 in friend's guess is a bull, the 2nd or 3rd 1 is a cow, and your function should return "1A1B".

You may assume that the secret number and your friend's guess only contain digits, and their lengths are always equal.
*/

// Solution using several counters.

class Solution {
public:
    string getHint(string secret, string guess) {
        int n = secret.size();
        vector<int> count_secret(10, 0), count_guess(10, 0), count_bull(10, 0);
        for(int i = 0; i < n; ++i) {
            int d1 = secret[i]-'0', d2 = guess[i]-'0';
            if(d1 == d2) count_bull[d1]++;
            count_secret[d1]++;
            count_guess[d2]++;
        }
        int bull(0), cow(0);
        for(int d = 0; d < 10; ++d) {
            bull += count_bull[d];
            cow += min(count_secret[d], count_guess[d]) - count_bull[d];
        }
        return num2str(bull) + "A" + num2str(cow) + "B";
    }
    string num2str(int n) {
        if(n == 0) return "0";
        string s;
        while(n) {
           s = char(n%10+'0') + s;
           n /= 10;
        }
        return s;
    }
};


/**************************************************** 
 ***    303,Easy,Range Sum Query - Immutable 
 ****************************************************/

/*
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

Example:

Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3

Note:

    You may assume that the array does not change.
    There are many calls to sumRange function.
*/

// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.sumRange(1, 2);

// Since array is immutable, use standard DP. Use an array storing the partial sums. Array has an additional entry in the front storing "0".

class NumArray {
public:
    NumArray(vector<int> &nums) {
        n = nums.size();
        sum.resize(n+1, 0);
        for(int i = 0; i < n; ++i)
            sum[i+1] = sum[i] + nums[i];
    }

    int sumRange(int i, int j) {
        if(i < 0 || i >= n || j < 0 || j > n || i > j) return 0;
        return sum[j+1] - sum[i];
    }
    vector<int> sum; //partial sums
    int n;
};

// Another solution also storing the nums array itself, and optimized for i == j case.

class NumArray {
public:
    NumArray(vector<int> &nums) {
        n = nums.size();
        sum.resize(n+1, 0);
        val.resize(n+1, 0);
        for(int i = 0; i < n; ++i) {
            sum[i+1] = sum[i] + nums[i];
            val[i+1] = nums[i];
        }
    }

    int sumRange(int i, int j) {
        if(i < 0 || i >= n || j < 0 || j > n || i > j) return 0;
        if(i == j) return val[i+1];
        else return sum[j+1] - sum[i];
    }
    vector<int> sum; //partial sums
    vector<int> val; //values
    int n;
};


