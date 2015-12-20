/**************************************************** 
 ***    004,Hard,Median of Two Sorted Arrays 
 ****************************************************/

/*
There are two sorted arrays nums1 and nums2 of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
*/

/*
Solution 1: compare medians of the two array.
We make a general algorithm that returns the k-th order value from two sorted arrays ( 0 <= k < m+n ). Then use it to calculate the median.
First some mathematics:
Generally, for an array nums[lo, hi], with length len = hi-lo+1, mid = (lo+hi)/2 = lo + ceil((hi-lo)/2.0). Let hlen = (hi-lo)/2. Thus, number of elements before mid (exclusive) is ceil((hi-lo)/2.0) = hlen, and number of elements after mid (exclusive) is floor((hi-lo)/2.0) which can be either hlen or hlen+1, depending on the length of array. Here we have used the fact that
for any integer: ceil(x/2.0) + floor(x/2.0) = x

Now we have two arrays nums1[lo1, hi1], nums2[lo2, hi2], we calculate mid1 and mid2 accordingly. We compare nums1[mid1] and nums2[mid2], say we have nums1[mid1] <= nums2[mid2]. If we combine the two in sorted order we will have something like:
      ... nums1[mid1] ... nums2[mid2] ...
From above, we know that:
a. nums1[mid1] has at least hlen1 + hlen2 + 1 (from nums1, nums2, and nums2[mid2] respectively) elements behind it (exlucsively)
b. nums2[mid2] has at least hlen1 + hlen2 + 1 elements ahead of it (exclusively)

Now let's check k's value, the k-th element (k starts from 0) has k elements before it,
1. if k <= hlen1 + hlen2, then the element can have at most hlen1+hlen2 elements ahead of it. Then we know for sure that the answer is before nums2[mid2], so we can discard nums2[mid2] and the elements in nums2 after it can be excluded
2. if k > hlen1 + hlen2, then the element can have at least hlen1+hlen2+1 elements ahead of it. Can we discard nums1[mid1] and the ones in nums1 ahead of it? Yes! Because nums1[mid1] will have 
at most hlen1 + hlen2 elements ahead of it, including nums1[mid1] we have hlen1+hlen2+1, which we can safely exclude mathemetically (in practice we only exclude elements nums1[0 .. mid1]). The calculation is below:
   number of elements before and including nums1[mid1] <= len1 + len2 - (hlen1 + hlen2 + 1)
                                                        = (hi1-lo1+1) + (hi2-lo2+1) - ( floor((hi1-lo1)/2.0) + floor((hi2-lo2)/2.0 + 1)
                                                        = ceil((hi1-lo1)/2.0) + ceil((hi2-lo2)/2.0) + 1
                                                        = hlen1 + hlen2 + 1
Similar for the case where nums1[mid1] > nums2[mid2]
*/

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int k = (m+n)/2;
        if((m + n) % 2 == 0) {
            int v1 = findKth(nums1, 0, m-1, nums2, 0, n-1, k-1);
            int v2 = findKth(nums1, 0, m-1, nums2, 0, n-1, k);
            return double(v1+v2)/2;
        } else {
            return findKth(nums1, 0, m-1, nums2, 0, n-1, k);
        }
    }
    int findKth(vector<int>& nums1, int lo1, int hi1, vector<int>& nums2, int lo2, int hi2, int k) {
        if(lo1 > hi1) return nums2[lo2+k];
        if(lo2 > hi2) return nums1[lo1+k];
        int mid1 = lo1 + (hi1-lo1)/2;
        int mid2 = lo2 + (hi2-lo2)/2;
        int hlen1 = mid1 - lo1, hlen2 = mid2 - lo2; //number of elements before mid
        if(nums1[mid1] <= nums2[mid2]) {
            if(k <= hlen1 + hlen2) return findKth(nums1, lo1, hi1, nums2, lo2, mid2-1, k); //drop elements after mid2 (inclusive)
            else return findKth(nums1, mid1+1, hi1, nums2, lo2, hi2, k-hlen1-1); //drop elements before mid1 (inclusive)
        } else {
            if(k <= hlen1 + hlen2) return findKth(nums1, lo1, mid1-1, nums2, lo2, hi2, k); //drop elements after mid1 (inclusive)
            else return findKth(nums1, lo1, hi1, nums2, mid2+1, hi2, k-hlen2-1); //drop elements before mid2 (inclusive)
        }
    }
};

// The same idea, iterative solution
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int k = (m+n)/2;
        if((m + n) % 2 == 0) {
            int v1 = findKth(nums1, 0, m-1, nums2, 0, n-1, k-1);
            int v2 = findKth(nums1, 0, m-1, nums2, 0, n-1, k);
            return double(v1+v2)/2;
        } else {
            return findKth(nums1, 0, m-1, nums2, 0, n-1, k);
        }
    }
    int findKth(vector<int>& nums1, int lo1, int hi1, vector<int>& nums2, int lo2, int hi2, int k) {
        while(lo1 <= hi1 && lo2 <= hi2) {
            int mid1 = lo1 + (hi1-lo1)/2;
            int mid2 = lo2 + (hi2-lo2)/2;
            int hlen1 = mid1 - lo1, hlen2 = mid2 - lo2; //number of elements before mid
            if(nums1[mid1] <= nums2[mid2]) {
                if(k <= hlen1 + hlen2) hi2 = mid2-1; //drop elements after mid2 (inclusive)
                else { lo1 = mid1+1; k -= hlen1+1; } //drop elements before mid1 (inclusive)
            } else {
                if(k <= hlen1 + hlen2) hi1 = mid1-1;  //drop elements after mid1 (inclusive)
                else { lo2 = mid2+1; k -= hlen2+1; }  //drop elements before mid2 (inclusive)
            }
        }
        if(lo1 > hi1) return nums2[lo2+k];
        else return nums1[lo1+k];
    }
};

// An old solution. Need further analysis
class Solution {
public:
	double findMedianSortedArrays(int A[], int m, int B[], int n) {
		int k = (m+n)/2; 
		if((m+n)%2 == 0) { //even
			int a = Select(A, m, B, n, k);
			int b = Select(A, m, B, n, k+1);
			return double(a+b)/2.0;
		} else return Select(A, m, B, n, k+1); //odd
	}

	//Binary search algorithm to selelect k-th order statistics from two SORTED arrays. Average O(log(m+n)) time.
	int Select(int A[], int m, int B[], int n, int k) {
		int idx = SelectUtil(A, B, n, 0, m-1, k); //search in A
		if(m == 0) return B[k-1];
		else if(n == 0) return A[k-1];
		
		if(idx != -1) return A[idx];
		else {
			idx = SelectUtil(B, A, m, 0, n-1, k); //search in B
			return B[idx];
		}
	}
    
 	//Utility function to find k-th order static in A+B in A[l .. r], B's size is n
	int SelectUtil(int A[], int B[], int n, int l, int r, int k) {
		if(r < l) return -1;
		int m = (l+r)/2;
		int x = A[m];
		//x is <= m+1 elements in A, check if x is <= k-(m+1) elements in B
		int q = k-m-1;
		if(q < 0 || (q < n && x > B[q])) return SelectUtil(A, B, n, l, m-1, k); //search left (A[l .. m-1])
		if(q > n || (q > 0 && x < B[q-1])) return SelectUtil(A, B, n, m+1, r, k); //search right (A[m+1 .. r])
		if((q == 0 || x >= B[q-1]) && (q == n || x <= B[q])) return m;
	}
};


/**************************************************** 
 ***    010,Hard,Regular Expression Matching 
 ****************************************************/

/*
Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true
*/

/*
Solution 1. Standard dynamic programming. Use a 2D vector dp, dp[i][j] stores whether s[0 .. i-1] matches p[0 .. j-1]. dp[i][j] can be determined by the following rules:

1. if p[j-1] is not '*', then we simply check dp[i-1][j-1] and whether s[i-1] matches p[j-1]:
           t[i-1]
t:   abc  | d   => match abc with a*bc, and d with d
p:   a*bc | d
           p[j-1]

           t[i-1]
t:   abc  | d   => match abc with a*bc, and d with .
p:   a*bc | .
           p[j-1]
thus dp[i][j] = dp[i-1][j-1] && matchHelper(s[i-1], p[j-1]);

whether matchHelper(t, p) returns true when p == '.' or p == t.

2. if p[j-1] is '*', we have two sub-cases. Let p[j-2] = x (for p to be a valid RE, '*' has to follow another character that is not '*'). Then x* can match nothing or one or more x's.
a) x* matches nothing, then we just check dp[i-1][j-2]
           t[i-1]
t:   ab    | d   => match abd with a*bd, ignore e*
p:   a*bde | *
          p[j-1]

b) x* matches at least one x, iff p[0, j-1] matches with s[0, i-2], and s[i-2] matches with x/
           t[i-1]
t:   abde  | e   => match abde with a*bde, then e with e
p:   a*bde | *
          p[j-1]

           t[i-1]
t:   abde  | e   => match abde with a*bd., then e with .
p:   a*bd. | *
          p[j-1]

thus dp[i][j] = dp[i][j-2] || (dp[i-1][j] && matchHelper(s[i-1], p[j-2])

Boundary case:
1. "" matches with "", so dp[0][0] = true
2. a non-empty p may also match "", e.g. "a*", so dp[0][j] = dp[0][j-2] && p[j-1] == '*'
*/

class Solution {
public:
    bool isMatch(string s, string p) {
        if(p == "") return s == "";
        //s can be "", p cannot
        int m = s.size(), n = p.size();
        vector<vector<bool> > dp(m+1, vector<bool>(n+1, false)); //match[i][j]: s[0..i-1] matches p[0..j-1]
        dp[0][0] = true; // "" matches ""
        //matching p with ""
        for(int j = 1; j <= n; ++j)
            dp[0][j] = p[j-1] == '*' && dp[0][j-2];
        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(p[j-1] != '*') dp[i][j] = dp[i-1][j-1] && matchHelper(s[i-1], p[j-1]);
                else dp[i][j] = dp[i][j-2] || (dp[i-1][j] && matchHelper(s[i-1], p[j-2]));
            }
        }
        return dp[m][n];
    }
    bool matchHelper(char t, char p) {
        return p == '.' || p == t;
    }
};

/*
Solution 2. Recursive solution, which takes 76ms (v.s. 20ms in solution 1).
Two pointers to scan text and pattern. When we see a pattern character, we "peek" the next character in pattern. If it is not '*', then we do normal matching, and move both forward in case of match. If next is a '*', then we either match empty string (move j two steps further, i stay put), or match one or more charaters after i if they match with p[j].
*/

class Solution {
public:
    bool matchHelper(char t, char p) {
        return p == '.' || p == t;
    }

    bool isMatch(string s, string p) {
        return isMatch(s, p, 0, 0);
    }

    bool isMatch(const string& s, const string& p, int i, int j) {
        int n = s.size(), m = p.size(); //n, i for text; m, j for pattern
        if(j == m) return i == n;
        if(j == m-1 || p[j+1] != '*') { //last char, or next is not '*'
           return matchHelper(s[i], p[j]) && isMatch(s, p, i+1, j+1);
        } else { // next character is '*'
            //first match c* with empty string
            if(isMatch(s, p, i, j+2)) return true;
            //match one or more c's
            while(i < n && matchHelper(s[i], p[j])) {
                if(isMatch(s, p, ++i, j+2)) return true;
            }
	/* //a variant of the last while loop, greedy match, but not much improvements.
	    int k = i;
            while(k < n && matchHelper(s[k], p[j])) k++;
            while(k > i) {
                if(isMatch(s, p, k--, j+2)) return true;
            }
	*/
        }
        return false;
    }
};



/**************************************************** 
 ***    023,Hard,Merge k Sorted Lists 
 ****************************************************/

/*
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
// Divide and conquer solution. Use the merge-two-list function.
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int size = lists.size();
        if(size == 0) return NULL;
        int i = 0;
        while(size > 1) {
            for(i = 0; 2*i+1 < size; i++) {
                lists[i] = mergeTwoLists(lists[2*i], lists[2*i+1]);
            }
            if(size % 2 == 1) lists[i] = lists[size-1];
            size = (size+1)/2;
        }
        return lists[0];
    }

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

// Priority queue solution O(nlgk) using STL priority queue, and comparator class
class isGreater {
public:
    bool operator() (ListNode *a, ListNode *b) {
        return a->val > b->val;
    }
};

class Solution {

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, isGreater> q;
        for(int i = 0; i < lists.size(); ++i) {
            if(lists[i]) q.push(lists[i]);
        }
        if(q.empty()) return NULL;
        ListNode dummy(0), *p(&dummy);
        ListNode *tail = p;
        while(q.size() > 1) {
            ListNode *node = q.top(); q.pop();
            tail->next = node;           
            tail = tail->next;
            if(node->next) q.push(node->next);
        }
        // only one element left
        tail->next = q.top();
        return p->next;
    }
};

// Priority queue solution O(nlgk) without using STL priority queue
class MinHeap {
public:
	MinHeap(int max_l) : maxL(max_l), size(0) {
		head = new ListNode* [maxL];
		arr = head-1; //pointer such that first element is arr[1]
	}
	~MinHeap() { delete [] head;}
	
    //push back without FixUp
	void PushBack(ListNode* node) {
		head[size++] = node;
	}
    //insert and run FixUp 
    void Insert(ListNode* node) {
        head[size++] = node;
        FixUp(size);
    }
	//build heap
	void BuildHeap() {
		for(int i = size/2; i >= 1; --i) FixDown(i);
	}

	bool Empty() { return size == 0; }

	// Extract minimum element
	ListNode* ExtractMin() {
		Swap(arr[size--], arr[1]);
		FixDown(1);
		return arr[size+1];
	}

	//fix down (check if arr[i] needs to be swapped with children)
	void FixDown(int i) {
		while(i > 0) {
			int smallest = i;
			int l = Left(i), r = Right(i);
			if( l <= size && arr[l]->val < arr[smallest]->val) smallest = l;
			if( r <= size && arr[r]->val < arr[smallest]->val) smallest = r;
			if(smallest != i) {
				Swap(arr[smallest], arr[i]);
				i = smallest;
			} else break;
		}
	}
    //fix up (check if arr[i] needs to be swapped with parent)
	void FixUp(int i) {
		while(i > 1) {
			int p = Parent(i);
			if(arr[p]->val > arr[i]->val) {
				Swap(arr[p], arr[i]);
				i = p;
			} else break;
		}
	}

	int Left(int i) {return 2*i;}
	int Right(int i) {return 2*i+1;}
	int Parent(int i) {return i/2;}
	void Swap(ListNode* &a, ListNode* &b) { ListNode* t = a; a = b; b = t;}

private:
	ListNode** head; //point to the head of array
	ListNode** arr; //one less the beginning of array
	int maxL; //max length
	int size; //size
};

class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        int size = lists.size();
        if(size == 0) return NULL;
        ListNode dum(0), *dummy(&dum), *p(dummy);
        MinHeap hp(size);
        for(int i = 0; i < size; ++i) {
            if(lists[i]) hp.PushBack(lists[i]);
        }
        hp.BuildHeap();
        while(!hp.Empty()) {
            ListNode *min_node = hp.ExtractMin();
            p->next = min_node;
            if(min_node->next) hp.Insert(min_node->next);
            p = p->next;
        }
        p->next = NULL;
        return dummy->next;
    }
};

/**************************************************** 
 ***    025,Hard,Reverse Nodes in k-Group 
 ****************************************************/

/*
Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/*
Solution 1. Iterative.
Determine the head and tail of each segment, and use a helper function to reverse it, and attach it to original list. The helper funtion
Uses a dummy head.
while loop invariant:
 start:   p1 -> [ p2 -> ... -> p3 ] -> p4 
 end:     p1 -> [ p3 -> ... -> p2 ] -> p4
*/

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(!head || k <= 1) return head;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *p1 = dummy, *p2 = head;
       // p1 -> [ p2 -> ... -> p3 ] -> p4 => p1 -> p3 -> ... -> p2 -> p4
        while(p2) {
            int count = k;
            ListNode *p3 = p2, *p4 = NULL;
            while(count > 1 && p3) {
                count--;
                p3 = p3->next;
            }
            if(!p3) break; //not enough elements to reverse
            p4 = p3->next;
            //now reverse p2 -> ... -> p3
            ListNode *curr = p2, *next = curr->next, *nextnext = NULL;
            while(curr != p3) {
                nextnext = next->next; // save it to tmp
                next->next = curr; //reverse 
                curr = next; //move forward
                next = nextnext; //move forward
            }
            //now connects p1 -> p3 and p2 -> p4
            p1->next = p3; p2->next = p4;
            //back to loop
            p1 = p2; p2 = p4;
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};

/* 
Solution 2. Same as method 1, but use iterative helper function to reverse.
*/

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == NULL || k == 1) return head;
        ListNode dum(0), *p(&dum); //dummy head
        p->next = head;
        ListNode *tail(NULL), *next(NULL), *last(p);
        while (head) {
            tail = head;
            int cnt = 1;
            while (cnt < k && tail) { tail = tail->next; cnt++; }
            if (!tail) break;
            next = tail->next;
            reverse(head, tail);
            last->next = tail; //tail is new head
            head->next = next; //head is new tail
            //update and move to next segment
            last = head;
            head = next;
        }
        return p->next;
    }
    void reverse(ListNode* head, ListNode* tail) {
        ListNode *next(head->next), *nextnext(NULL);
        while (head != tail) {
            nextnext = next->next;
            next->next = head; //reverse
            head = next;
            next = nextnext;
        }
    }
/*  
    //A slightly different reverse version
    void reverse(ListNode* head, ListNode* tail) {
        ListNode *next(head->next);
        while (head != tail) {
            ListNode* tmp = next->next; //tmp stores next->next 
            next->next = head; //reverse
            head = next;
            next = tmp;
        }
    }
*/
};

/**************************************************** 
 ***    030,Hard,Substring with Concatenation of All Words 
 ****************************************************/

/*
You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).
*/

// words may contain duplicates, so use a map (counts) to count occurrences of each unique word, use occurs to count words seen so far in s
// e.g. words = ["a", "a", "b"], then counts = { "a" => 2, "b" => 1 }
// let the length of each word to be L, then has to do L passes, each time searching starts from s[l], l = 0 .. l-1.
// Each pass, use two pointers to track the sliding window boundaries. grab a subtring of length L once at a time. If reaching the maximum window size (L*nwords), then slide left (i) one L step. When counts == occurs (size equal && individual elements equal), then found a valid index

// Be cautious, j is not the end of the window, but j+L is!, so length of window is actually j-i+1.
// Don't need to maintain a separate total count, since when comparing counts and occurs, first it compares the size

// e.g.
// s = b a r f o o t h e f o o b a r m a n  ,  counts = {bar => 1, foo => 1}
//    [b a r]f o o t h e f o o b a r m a n  ,  i = 0, j = 0, occurs = {bar => 1}
//    [b a r f o o]t h e f o o b a r m a n  ,  i = 0, j = 3, occurs = {bar => 1, foo = 1},  found '0'
//     b a r[f o o t h e]f o o b a r m a n  ,  i = 3, j = 6, break since the is not in words, occurs = {}
//     b a r f o o t h e[f o o]b a r m a n  ,  i = 9, j = 12, occurs = {foo => 1}
//     b a r f o o t h e[f o o b a r]m a n  ,  i = 9, j = 15, occurs = {foo => 1, bar = 1}, found '9'
//     b a r f o o t h e f o o[b a r m a n] ,  i = 12, j = 18, break since the is not in words, occurs = {}

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ret;
        if(words.empty()) return ret;
        map<string, int> counts; //counts of each unique word
        map<string, int> occurs; //occurrences of each word in s
        for(int i = 0; i < words.size(); ++i) {
            counts[words[i]]++;
        }
        int L = words[0].size(); //word length
        for (int l = 0; l < L; ++l) { //do L passes
            int i = l, j = l;
            occurs.clear(); // clear occurences map
            //scan each substring of length L
            while(j+L <= s.size()) {
                string t = s.substr(j, L);
                if(counts.count(t) == 0) { //not found such word
                    i = j = j+L;
                    occurs.clear();
                    continue;
                }
                occurs[t] ++; //found such word
                if(j == i + L*words.size()) { //reached max size of window
                    string t2 = s.substr(i, L);
                    if(counts.count(t2) > 0) occurs[t2] --;
                    i += L; //move left side of window forward by L
                }
                if(occurs == counts) ret.push_back(i);
                j += L;
            }
        }
        return ret;
    }
};

// Can further optimize and only use one map to store the counts, when see the string, reduce the individual counts, when it reaches zero we know that we have exactly the amount we need.
// similar to min window, use only one dict to store the counting information. The key is to restore the information after each run.

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
         vector<int> result;
         int nwords = words.size();
         if(nwords == 0) return result;
         int lword = words[0].size();
         if(s.empty()) return result;
         unordered_map<string, int> dict, count;
         int total_count = 0;
         int n = s.size();
         for(size_t i = 0; i < nwords; ++i)
             dict[words[i]]++;
        
         for(size_t i = 0; i < lword; ++i) {
             total_count = nwords;
             count = dict;
             int jstart = i, j = i;
             while(j + lword <= n) {
                 string str = s.substr(j, lword);
                 if(count.find(str) == count.end()) {
                     total_count = nwords;
                     count.clear();
                     jstart = j + lword;
                 } else {
                     total_count ++;
                     count[str] ++;
                     int c = dict[str];
                     while(count[str] > c) {
                         string tmp = s.substr(jstart, lword);
                         count[tmp] --;
                         total_count --;
                         jstart += lword;
                     }
                 }
                 if(total_count == words.size()) result.push_back(jstart);
                 j += lword;
             }
         }
         return result;
    }
};


/**************************************************** 
 ***    032,Hard,Longest Valid Parentheses 
 ****************************************************/

/*
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4. 
*/

/*
 Dynamic programming, use a table to store the length of longest valid parentheses of s's substring of length i (i = 0 .. n) that ends at s[i].
The result will be the maximum length among all such strings.
 We scan all characters, for i-th character, when we see a ')' we start checking the substring s[0..i-1] of length i. We already know the maximum length of s[0..i), so we check the character before that, if it is '(', then we have found a matching bracket, we further add the part before that '(' is there is any. Be attention of case of possible array out of bound.

  s: 0    ..       j   ...    i-1  i
         [ ... ]  '('   [ ... ]   ')'
*/ 

// Caveats:
// In this scheme, when checking s[i], we are calculating mp[i+1], not mp[i].
// Do not confuse mp[i] and s[i]
// Indexing: mp[i-len-1] not mp[i-len]
// should return max_len, not mp[n]

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        if(n <= 1) return 0;
        vector<int> mp(n+1, 0); //mp[n]: the length of lvp substring of s[0..n-1] that ends at s[n-1].
        int max_len = 0;
        for(int i = 0; i < n; ++i) {
            if(s[i] == ')') {
                int len = mp[i]; //check previous substring
                if(mp[len] >= i || s[i-len-1] != '(') mp[i+1] = 0; //no valid substring ending at s[i]
                else mp[i+1] = len + mp[i-len-1] + 2;
                max_len = max(max_len, mp[i+1]);
            }
        }
        return max_len;
    }
};

// Another solution with stack
/* Stack stores the position of last unmatched position so far, when seeing a ')' start checking the top of stack. If it is a ')', we found a match, and calculate the length from the current top, not if matched, insert the current ')' to the stack indicating the new "end" of unmatched position.
 For example, s=())(())
s[0]: '(', stack: 0
s[1]: ')', pop stack 0 and found a match, now stack is empty, len = 1+1 = 2;
s[2]: ')', stack empty, no match, just push ')' position 2 to stack
s[3]: '(', push to stack, now 2, 3
s[4]: '(', push to stack, now 2, 3, 4
s[5]: ')', matched 4 in stack, len = 2, now stack is 2,3
s[6]: ')', matched 3 in stack, len = 4, now stack is 2.
*/
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        if(n <= 1) return 0;
        deque<int> st; //stack storing indices
        int max_len = 0;
        for(int i = 0; i < n; ++i) {
            char c = s[i];
            if(c == '(' || st.empty()) st.push_back(i);
            else { //c is ')' and st not empty
                int j = st.back(); st.pop_back();
                if(s[j] != '(') st.push_back(i); //not matched
                else { //matched, pop out and get one pos left of valid substring
                    int len = st.empty() ? i+1 : i-st.back();
                    max_len = max(max_len, len);
                }
            }
        }
        return max_len;
    }
};

// Another solution with a sentinel element (-1) to avoid st.empty() checks
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        if(n <= 1) return 0;
        deque<int> st; //stack storing indices
        st.push_back(-1); //sentinel element to avoid st.empty() checks
        int max_len = 0;
        for(int i = 0; i < n; ++i) {
            char c = s[i];
            if(c == '(') st.push_back(i);
            else { //c is ')' and st not empty
                int j = st.back(); st.pop_back();
                if(j == -1 || s[j] != '(') st.push_back(i); //not matched (need to check if j == -1!)
                else { //matched, pop out and get one pos left of valid substring
                    int len = i-st.back(); //if sentinel is back, then is i+1
                    max_len = max(max_len, len);
                }
            }
        }
        return max_len;
    }
};

/**************************************************** 
 ***    033,Hard,Search in Rotated Sorted Array 
 ****************************************************/

/*
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.
*/

/*
Binary search. The array can be broken into two parts, 
for example, [4 5 6 7 0 1 2], first part is 4-7, second part is 0-2. If array is unrotated, then only first part exists (corner case). 
There are three anchor points, lo, hi, and mid.
First determine whether mid is in first half or second half. Mid is in first half iff nums[mid] >= nums[lo] (we can't use comparison between mid and hi, i.e. nums[mid] > nums[hi] because a corner case where array is not rotated has nums[mid] < nums[hi], but still mid is in first half.

1. If mid is in first half, we know that nums[mid] >= nums[lo] (could be equal because mid can be lo, when hi = lo+1), if target falls between the two, then the index has to be between lo and mid. Otherwise, it is between mid and hi.
2. If mid is in second half, we know that nums[mid] <= nums[hi] (could be equal because mid can be hi, when hi = lo), if target falls between the two, then the index has to be between mid and hi. Otherwise, it is between lo and mid.

Difference between finding target and finding minimum:
1. for finding minimum, we let lo < hi, terminate at lo == hi, and return nums[lo]
   for finding target, we let lo <= hi, return as soon as values are found. If not found, terminate at lo > hi.
2. both involve one corner case, where array is not rotated. For find min, just return nums[lo], for search target, we need to carefully design while loop so that it also works for corner cases. Thus we compare nums[mid] and nums[lo], rather than nums[hi]. In find min case, we eliminate corner case upfront, so we compare nums[mid] with nums[hi]. Also, since we could end up mid = lo (when hi and lo differ by one), and nums[lo] will = nums[mid] causing problems, so it is safer to compare with nums[hi].
*/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int lo(0), hi(n-1);
        while(lo <= hi) {
            int mid = lo + (hi-lo) / 2;
            if(target == nums[mid]) return mid;
            if (nums[mid] >= nums[lo]) {
                if(target >= nums[lo] && target < nums[mid]) hi = mid - 1;
                else lo = mid + 1;
            } else {
                if(target <= nums[hi] && target > nums[mid]) lo = mid + 1;
                else hi = mid - 1;
            }
        }
        return -1;
    }
};

/**************************************************** 
 ***    037,Hard,Sudoku Solver 
 ****************************************************/

/*
Write a program to solve a Sudoku puzzle by filling the empty cells.

Empty cells are indicated by the character '.'.

You may assume that there will be only one unique solution.
*/

/*
DFS backtracking. Using a helper function canPlace (44ms).
Two passes: first pass initializes state, second pass do dfs and fills empty cells.

Have dfs return true or false so that once a solution is find, terminate search immediately.

Caveats:
1. numbers start from 1, not 0.
2. when to terminate? i == 9, not j == 9!. 
*/

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        dfs(board, 0, 0);
    }
    bool dfs(vector<vector<char> >& board, int i, int j) {
        //try all possible choices
        if(i == 9) return true;
        int inext = (j == 8) ? i+1 : i;
        int jnext = (j == 8) ? 0 : j+1;
        //already filled, just jump to next
        if(board[i][j] != '.') return dfs(board, inext, jnext);
        //only try when board[i][j] is '.'
        for(char c = '1'; c <= '9'; c++) {
            if(canPlace(board, i, j, c)) {
                board[i][j] = c;
                if(dfs(board, inext, jnext)) return true;
            }
            board[i][j] = '.'; //reset back to '.'
        }
        return false; //tried all possibilities
    }

    bool canPlace(vector<vector<char> >& board, int i, int j, char c) {
        for(int irow = 0; irow < 9; irow++)
            if(irow != i && board[irow][j] == c) return false;
        
        for(int jcol = 0; jcol < 9; jcol++)    
            if(jcol != j && board[i][jcol] == c) return false;
        
        int iblk = i-i%3, jblk = j-j%3; //block offset
        for(int l = 0; l < 9; l++) { // try all entries within the block
            int irow = iblk + l/3, jcol = jblk + l%3;
            if(irow != i && jcol != j && board[irow][jcol] == c) return false;
        }
        return true;
    }
};

/*
Solution 2. Use three bits vectors indicating states for rows, colums, and blocks (8ms).

bit negation takes 4ms longer time, so use
  if( state & ..) continue;
instead of using 
  if(! (state & ..)) { ... }
results in 4ms reduction of runtime (12ms => 8ms)
*/

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        row.resize(9, 0); col.resize(9, 0); block.resize(9, 0); 
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j) {
                if(board[i][j] != '.') {
                    int state = 1 << (board[i][j] - '1');
                    row[i] |= state;
                    col[j] |= state;
                    block[i/3*3+j/3] |= state;
                }
            }
        }
        dfs(board, 0, 0);
    }
    bool dfs(vector<vector<char> >& board, int i, int j) {
        //try all possible choices
        if(i == 9) return true;
        int inext = (j == 8) ? i+1 : i;
        int jnext = (j == 8) ? 0 : j+1;
        //already filled, just jump to next
        if(board[i][j] != '.') return dfs(board, inext, jnext);
        //only try when board[i][j] is '.'
        int k = i/3*3+j/3;
        int state = 1;
        for(char c = '1'; c <= '9'; c++, state <<= 1) {
            if(state & (row[i] | col[j] | block[k])) continue;
            board[i][j] = c;
            row[i] |= state; col[j] |= state;  block[k] |= state;
            if(dfs(board, inext, jnext)) return true;
            row[i] &= ~state; col[j] &= ~state;  block[k] &= ~state; //reset states
            board[i][j] = '.'; //reset back to '.'
        }
        return false; //tried all possibilities
    }

    vector<int> row, col, block; //bit status array
};

/**************************************************** 
 ***    041,Hard,First Missing Positive 
 ****************************************************/

/*
Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space. 
*/

/* Solution with O(1) space and O(n) time. Uses nums itself as the table. When we find a positive integer i, we should put it in the right position nums[i-1], and put original values there in correct positions as well. This requires a while loop with swap functions. For an array of n numbers, it is guaranteed that the missing positive lies between 1 and n+1. When it is between 1 and n, then at least one entry in nums is not filled properly, and we return that values. When it is n+1, then all entries are filled properly, and we simply return n+1.
Think of indices as mapping nums[i] => i+1.
Scan left to right, only perform swapping when value is within [1 .. N], and the destination does not have correct indices (nums[t-1] != t).s
Caveats:
1. when the destination already has the correct numbers, do not swap. This will avoid an infinite while loop. e.g. 1 1
2. return i+1, n+1.
*/

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        //nums[i] should be i+1
        for(int i = 0; i < n; ++i) {
            int t = nums[i];
            while(t > 0 && t <= n && nums[t-1] != t)
               swap(nums[t-1], t);
        }
        for(int i = 0; i < n; ++i) {
           if(nums[i] != i+1) return i+1;
        }
        return n+1;
    }
};


/**************************************************** 
 ***    042,Hard,Trapping Rain Water 
 ****************************************************/

/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

For example,
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6. 
*/

/*
We notice that the amount of water trapped at position[i] is bounded by the *lower* of the peak position at its left and peak position at its right. This has suggested a two-way search, instead of single-direction scan. We use two pointers, l and r, initially at the two boundaries of array. Then, the water level is limited by the lower of hl = height[l] and hr = height[r]. We move from the lower side towards the other side., here we assume it is the left side. We also keep track of the current water level at each position. Two cases:
1) if we see a higher point than hl. this will raise the water level to the new height. No water can be trapped here.
2) if we see a lower point than hl, then water will be trapped here and the amount is the difference between current water level and current height at this position.

Every time we move one step, we compare height[l] and height[r], and we always move from the lower side until the two meets.

Caveats:
store height[l] and height[r] as temporary hl and hr, so that when l or r moves, we are comparing to the old value of hl and hr. We need to properly update hl and hr before proceeding to next step.

One while loop.
*/

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int i(0), j(n-1);
        int sum(0);

        int l = i, r = j;
        while (i < j-1) {
            int level = min(height[l], height[r]);
            if (height[l] < height[r]) { //left side lower
                i++;
                if (height[i] < level) sum += level - height[i];
                else l = i;
            } else { //right side lower
                j--;
                if (height[j] < level) sum += level - height[j];
                else r = j;
            }
        }
        return sum;
    }
};


/// Another solution using nested while loops.
/// Two pointers on each end (l, r).
/// Maintain the current minimum water level as level
/// Scan from two sides until l and r meet, collect water amounts at each position
/// Given l and r, the minimum water level should be level = min(height[l], height[r])
/// Always scan from the lower side (between l and r) because it determines the current water level
/// When the encountered height is below level, then collect the difference and add to water amount
/// When the encountered height is above level, no water can be stored at this point. But the water level can rise (determined by minimum of this height and height of other end), so simply update level.
/// Use nested while loops

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n <= 2) return 0;
        int l(0), r(n-1);
        int level(0), water(0);
        while(l < r) {
            level = min(height[l], height[r]);
            if(height[l] < height[r]) { //left side lower
                while(++l < r && height[l] <= level) water += (level-height[l]);
            } else {
                while(--r > l && height[r] <= level) water += (level-height[r]);
            }
        }
        return water;
    }
};

/**************************************************** 
 ***    044,Hard,Wildcard Matching 
 ****************************************************/

/*
Implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false
*/

/*
See 
https://leetcode.com/discuss/52274/three-solutions-iterative-16ms-180ms-modified-recursion-88ms

Solution 1. Standard DP solution with a 2D vector. Slow.
When we see a '*' it can match nothing, hence dp[i][j-1], or it can match at least one character, hence dp[i-1][j].
*/

class Solution {
public:
    bool isMatch(string s, string p) {
        if(p == "") return s == "";
        //s can be "", p cannot
        int m = s.size(), n = p.size();
        vector<vector<bool> > dp(m+1, vector<bool>(n+1, false)); //match[i][j]: s[0..i-1] matches p[0..j-1]
        dp[0][0] = true; // "" matches ""
        //matching p with ""
        for(int j = 1; j <= n && p[j-1] == '*'; ++j)
            dp[0][j] = true;
        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(p[j-1] != '*') dp[i][j] = dp[i-1][j-1] && matchHelper(s[i-1], p[j-1]);
                else dp[i][j] = dp[i-1][j] || dp[i][j-1];
            }
        }
        return dp[m][n];
    }

    bool matchHelper(char t, char p) {
        return p == '?' || p == t;
    }
};

/*
Solution 2. Need further analysis
*/

class Solution {
public:
    bool helper(const string &s, const string &p, int si, int pi, int &recLevel)
    {
        int sSize = s.size(), pSize = p.size(), i, curLevel = recLevel;
        bool first=true;
        while(si<sSize && (p[pi]==s[si] || p[pi]=='?')) {++pi; ++si;} //match as many as possible
        if(pi == pSize) return si == sSize; // if p reaches the end, return
        if(p[pi]=='*')
        { // if a star is met
            while(p[++pi]=='*'); //skip all the following stars
            if(pi>=pSize) return true; // if the rest of p are all star, return true
            recLevel++;
            for(i=si; i<sSize; ++i)
            {   // then do recursion
                if(p[pi]!= '?' && p[pi]!=s[i]) continue;
                if(helper(s, p, i+1, pi+1, recLevel)) return true;
                if(recLevel>curLevel+1) return false; // if the currently processed star is not the last one, return
            }
        }
        return false;
    }

    bool isMatch(string s, string p) {
        int recLevel = 0;
        return helper(s, p, 0, 0, recLevel);
    }
};

/*
Solution 3. An elegant greedy solution from Yu's coding garden. Need further study.
*/



/**************************************************** 
 ***    045,Hard,Jump Game II 
 ****************************************************/

/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)
*/

/*
Solution 1. Standard BFS, each step, maintain a range [lo, hi] reachable from beginning, then scan all elements in the range, and calculate the newly reachable range as [hi+1, max( nums[i]+i) for all i between lo and hi]. If hi is not increased in the newly range, then cannot jump.
*/

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return 0;
        int lo = 0, hi = 0;
        int step = 0;
        while(hi < n-1) {
           int tmp = hi;
           for(int i = lo; i <= tmp; ++i) {
               hi = max(hi, i+nums[i]);
           }
           if(hi == tmp) return -1;
           lo = tmp+1;
           step ++;
        }
        return step;
    }
};


/**************************************************** 
 ***    051,Hard,N-Queens 
 ****************************************************/

/*
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]

*/

/*
Solution 1. Recursive DFS.
use a vector to keep track of the column position of queens in each row.
This way it is guaranteed that no queen are on the same row.
We only need to check if the current queen is on the same column or same diagonal with any previously placed queens.

Use a matrix for string to prestore the solutions, when found solution, update string matrix, push to solution, and reset string matrix back.
*/

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string> > result;
        if(n == 0) return result;
        vector<int> pos(n, -1); //position of queen in row[i], can be between 0 and n-1
        vector<string> solstr(n, string(n, '.'));
        solveNQueensHelper(0, pos, solstr, result);
        return result;
    }
    //checking row i
    void solveNQueensHelper(int i, vector<int>& pos, vector<string>& solstr, vector<vector<string> >& result) {
        int n = pos.size();
        if(i == n) {
            //construct solution
            for(size_t i = 0; i < pos.size(); ++i) {
                solstr[i][pos[i]] = 'Q';
            }
            result.push_back(solstr);
            //reset solstr
            for(size_t i = 0; i < pos.size(); ++i) {
                solstr[i][pos[i]] = '.';
            }
            return;
        }
        //try position j on row i (no queens will be on the same row)
        for(int j = 0; j < n; ++j) {
           if(canPlace(i, j, pos)) {
              pos[i] = j;
              solveNQueensHelper(i+1, pos, solstr, result);
           }
        }
        pos[i] = -1; //reset value
    }
    //can place, check if Queen at [i][j] conflicts with queens in previous rows
    bool canPlace(int i, int j, vector<int>& pos) {
        for(int row = 0; row < i; ++row) {
            int col = pos[row];
            if(col == j || fabs(j - col) == i - row) return false;   //same col or diagonal
        }
        return true;
    }
};

// Solution 2. Iterative solution.

class Solution {
public:
	vector<vector<string> > solveNQueens(int n) {
		vector<vector<string> > ret;
		int irow = 0;
		vector<int> col(n,-1);
		while(irow >= 0) { 
		    if(irow == n) { //found a solution
		        ret.push_back(config2str(col));
		        irow--; //retrace
		    } else {
			    //find next valid column position
			    col[irow] ++;
			    while(col[irow] < n && !isValid(col, irow)) col[irow]++;
			
			    if(col[irow] == n) {  // tried all combinations, retrace
			        col[irow] = -1;
			        irow--; 
    			} else {  //suceeded at k-th step, move to next
    			    irow++;
				}
			}
		}
		return ret;
	}
	
	bool isValid(const vector<int>& col, int irow) { 
		for(int j = 0; j < irow; ++j) {
			if(col[j] == col[irow] || irow - j == std::fabs(col[irow] - col[j])) return false;
		}
		return true; 
	}
	
	vector<string> config2str(const vector<int>& conf) {
		vector<string> ret;
		string str;
		for(int k = 0; k < conf.size(); ++k) { //k-th string
			str.clear();
			for(int j = 0; j < conf.size(); ++j) {
				if(conf[k] == j) str += 'Q';
				else str += '.';
			}
			ret.push_back(str);
		}
		return ret;
	}
};

/**************************************************** 
 ***    052,Hard,N-Queens II 
 ****************************************************/

/*
Follow up for N-Queens problem.

Now, instead outputting board configurations, return the total number of distinct solutions.
*/

// Solution 1. Recursive solution.

class Solution {
public:
    int totalNQueens(int n) {
        if(n == 0) return 0;
        int count = 0;
        vector<int> pos(n, -1); //position of queen in row[i], can be between 0 and n-1
        return solveNQueensHelper(0, pos);
    }
    //checking row i
    int solveNQueensHelper(int i, vector<int>& pos) {
        int n = pos.size();
        if(i == n) return 1;
        int count = 0;
        //try position j on row i (no queens will be on the same row)
        for(int j = 0; j < n; ++j) {
           if(canPlace(i, j, pos)) {
              pos[i] = j;
              count += solveNQueensHelper(i+1, pos);
           }
        }
        pos[i] = -1; //reset value
        return count;
    }
    //can place, check if Queen at [i][j] conflicts with queens in previous rows
    bool canPlace(int i, int j, vector<int>& pos) {
        for(int row = 0; row < i; ++row) {
            int col = pos[row];
            if(col == j || fabs(j - col) == i - row) return false;   //same col or diagonal
        }
        return true;
    }
};


// Solution 2. Iterative solution.

class Solution {
public:
    int totalNQueens(int n) {
        if(n == 0) return 0;
        int count = 0;
        vector<int> pos(n, -1); //position of queen in row[i], can be between 0 and n-1
        int i = 0, j = 0;
        while(i >= 0) {
            if(i == n) {
                count++;
                i--; //retrace back
                continue;
            }
            j = pos[i]+1; //move one step to right and try new positions
            while(j < n && !canPlace(i, j, pos)) j++;
            if(j == n) { //tried all possibilities, retrace back
                pos[i] = -1; i--;
                continue;
            }
            //found a possible place, record and move to next row.
            pos[i] = j;  i++;
        }
        return count;
    }

    //can place, check if Queen at [i][j] conflicts with queens in previous rows
    bool canPlace(int i, int j, vector<int>& pos) {
        for(int row = 0; row < i; ++row) {
            int col = pos[row];
            if(col == j || fabs(j - col) == i - row) return false;   //same col or diagonal
        }
        return true;
    }
};

/**************************************************** 
 ***    056,Hard,Merge Intervals 
 ****************************************************/

/*
Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18]. 
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

// One pass simple solution after sorting interval array

bool compare_start(const Interval& a, const Interval& b) {
    return a.start < b.start;
}

class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> result;
        if(intervals.empty()) return result;
        int n = intervals.size();
        if(n == 1) return intervals;
        sort(intervals.begin(), intervals.end(), compare_start);
        result.push_back(intervals[0]);
        Interval last = intervals[0];
        for(int i = 1; i < intervals.size(); ++i) {
            const Interval& curr = intervals[i];
            if(curr.start <= last.end) {
                //merge current with last
                last.end = result.back().end = max(curr.end, result.back().end);
            } else {
                result.push_back(curr);
                last = curr;
            }
        }
        return result;
    }
};


// An old solution 
bool compare(const Interval &a, const Interval &b) {
    if(a.start < b.start) return true;
    if(a.start > b.start) return false;
    return a.end < b.end;
}

class Solution {
public:

    vector<Interval> merge(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), compare);
        vector<Interval> s; //stack 
        int n = intervals.size();
        for(int i = 0; i < n; ++i) {
            Interval it = intervals[i];
            while(!s.empty() && isOverlap(s.back(), it)) { //overlap
                it = mergeTwo(s.back(), it);
                s.erase(s.end()-1); //stack pop
            } 
            //now either stack is empty, or there is no overlap
            s.insert(s.end(), it); //stack push
        }
        return s; //return whole stack
    }
    
    bool isOverlap(const Interval& a, const Interval &b) {
        return (a.start <= b.end && b.start <= a.end);
    }
    
    Interval mergeTwo(const Interval &a, const Interval &b) {
        Interval it;
        it.start = min(a.start, b.start);
        it.end = max(a.end, b.end);
        return it;
    }
};

/**************************************************** 
 ***    057,Hard,Insert Interval 
 ****************************************************/

/*
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10]. 
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

/// scan intervals from left to right:
// 1. if current interval overlaps with newInterval, then merge the two and update newInterval
// 2. if not overlap, then push-back the one with smaller start time to final array, and make the other one as newInterval.
// Use a tag "inserted" to check if newInterval already inserted. If yes, then no need to perform interval comparison in later step (just copy and paste)

class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        vector<Interval> result;
        if(intervals.empty()) {
            result.push_back(newInterval);
            return result;
        }
        int n = intervals.size();
        bool inserted = false;
        for(int i = 0; i < n; ++i) {
           const Interval& current = intervals[i];
           if(inserted) result.push_back(current);
           else if(newInterval.start <= current.end && current.start <= newInterval.end) { //merge the two
               newInterval.start = min(current.start, newInterval.start);
               newInterval.end = max(current.end, newInterval.end);
           } else { //not overlap
               if(current.start > newInterval.start) {
                   result.push_back(newInterval); //smaller start goes first
                   result.push_back(current);
                   inserted = true; //finshed insertion
               } else {
                   result.push_back(current); //smaller start goes first
               }
           }
        }
        if(!inserted) result.push_back(newInterval);
        return result;
    }

    bool isOverlap(const Interval& a, const Interval& b) {
       return !((a.end < b.start) || (a.start > b.end));
    }
};

/**************************************************** 
 ***    065,Hard,Valid Number 
 ****************************************************/

/*
Validate if a given string is numeric.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true

Note: It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one. 
*/

/*
 * A valid number consists of several fields:
 *    -28.82e-20 
 * 00012222233334444  

 * Fields 0 and 4 are spaces and can appear >=0 times, thus: \s*
 * Field 1 is either plus or minus sign, and can appear zero or one times, thus:  [\+\-]?
 * Field 2 is the coefficient part, can be one of the following:
 * - integers (a sequence of digits) 20348
 * - integers plus a dot: 20345.
 * - floating points: 2.304
 * - dot followed by digits: .234
 * It should not accept a single dot (.). 
 * Depending on whether a dot is the first character we can break it into two cases:
 * - first character is a digit, so the dot and fractional points can be absent, thus: \d+(\.\d*)?
 * - second character is a dot, it has to be followed by at least one digit, thus: \.\d+
 * thus field 2 is: \d+ (\.\d*)? | \.\d+ 
 * Field 3 is the exponential part. It consists of several parts: 
 * - the e/EXPO character: [eE]
 * - the sign (either + or - or missing): [\+\-]?
 * - the exponent as a sequence of numbers (at least one): \d+.
 * field 3 can be absent or appear only one time, thus: ([eE][\+\-]?\d+)?
 * Thus the regular expression for the valid number is:
 *  \s* [\+\-]? (\d+(\.\d*)?|\.\d+) ([eE][\+\-]?\d+)? \s*  (spaces in between are added for clarity and should be removed)
 * 0..0 1  .. 1 2      ..         2 3     ..        3 4..4
 */

// Use finite automaton. Read charater one by one, depending on the current state and character read, jump to the next state
// 9 states,  and 6 types of charaters defined in CharType
// state 0: has only seen spaces so far, expects another space, a digit, a dot, or a sign
// state 1: has read a sign (+/-), expects a digit, or a dot
// state 2: has read a digit in coeffient part, expects another digit, a dot, a e/E, or space
// state 3: has read a dot (.) before reading any digit, only expects a digit as fractional part only
// state 4: has read a dot (.) after reading at least one digit, expects a digit, or e/E, or space
// state 5: has read a e/E in exponent field, expects a sign, or a digit
// state 6: has read a sign in exponent field, expects a digit
// state 7: has read a digit in exponent field, expects another digit, or space
// state 8: has read a trailing space, expects another space      
// Small trick: add a space after string s, so we only need to check if state == 8 in the end. 
// Alternative: not add a space, and instead check if state is one of 2,4,7,8 in the end.

class Solution {
public:
    enum CharType { SPACE=0, DIGIT, DOT, SIGN, EXPO, OTHER };

    bool isNumber(string s) {
        s += ' ';
        initDFA();
        int state = 0;
        for (int i = 0; i < s.size() && state >= 0; ++i)
            state = dfa[state][getType(s[i])];
        
        return state == 8;
    }

    void initDFA() {
        dfa.resize(9, vector<int>(6, -1));
        // state 0: has only seen spaces so far, expects another space, a digit, a dot, or a sign
        dfa[0][SPACE] = 0;
        dfa[0][DIGIT] = 2;
        dfa[0][DOT]   = 3;
        dfa[0][SIGN]  = 1;
        // state 1: has read a sign (+/-), expects a digit, or a dot
        dfa[1][DIGIT] = 2;
        dfa[1][DOT]   = 3;
        // state 2: has read a digit in coeffient part, expects another digit, a dot, a e/E, or space
        dfa[2][SPACE] = 8;
        dfa[2][DIGIT] = 2;
        dfa[2][DOT]   = 4;
        dfa[2][EXPO]  = 5;
        // state 3: has read a dot (.) before reading any digit, only expects a digit as fractional part only
        dfa[3][DIGIT] = 4;
        // state 4: has read a dot (.) after reading at least one digit, expects a digit, or e/E, or space
        dfa[4][SPACE] = 8;
        dfa[4][DIGIT] = 4;
        dfa[4][EXPO]  = 5;
        // state 5: has read a e/E in exponent field, expects a sign, or a digit
        dfa[5][DIGIT] = 7;
        dfa[5][SIGN]  = 6;
        // state 6: has read a sign in exponent field, expects a digit
        dfa[6][DIGIT] = 7;
        // state 7: has read a digit in exponent field, expects another digit, or space
        dfa[7][SPACE] = 8;
        dfa[7][DIGIT] = 7;
        // state 8: has read a trailing space, expects another space
        dfa[8][SPACE] = 8; 
    }

    int getType(char c) {
        if (c == ' ' || c == '\t') return SPACE;
        if (c >= '0' && c <= '9')  return DIGIT;
        if (c == '.')              return DOT;
        if (c == '+' || c == '-')  return SIGN;
        if (c == 'e' || c == 'E')  return EXPO;
        return OTHER;
    }

    vector<vector<int> > dfa;
};


/**************************************************** 
 ***    068,Hard,Text Justification 
 ****************************************************/

/*
Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly L characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:

[
   "This    is    an",
   "example  of text",
   "justification.  "
]

Note: Each word is guaranteed not to exceed L in length.

click to show corner cases.
Corner Cases:

    A line other than the last line might contain only one word. What should you do in this case?
    In this case, that line should be left-justified.
*/

/*
Two pointers, [i, j) to find the words to be put on each row.
j starts from i, and scans forward until total character count > maxWIdth or j reaches the end.
several cases:

1. If count <= maxWidth that means j reaches the end. We just do left justification, append each word followed by one space.
2. If count > maxWidth, then we retrace one step back. Now [i, j) contains all the words to put on current line. We need to decide on distribution of spaces.
  2.1) if there is only one word, then same as left justification
  2.2) If there is more than one word, then we have ngaps = nword-1 gaps to be filled. We first calculate the remaining number of spots to be filled by spaces, and more-or-less evenly distribute them among ngaps. First r gaps receive one more space than the rest, where r is remaining % ngaps.

Caveat:
1. Do not forget the case where there is only one word! In this case, number of gaps is 0, and division by gaps will result in error!
2. Don't forget the initial space assigned to each gap, so q = remaining/ngaps +1 !.
3. don't forget to append padding spaces for left justification case.
4. Properly initialize/reest the variable storing line contents at the beginning of each loop iteration.
5. the condition after while(count <= maxWidth && j < n) should be (count <= maxWidth), but not (j == n). Because we could have count < maxWidth and j == n at the same time, and this is not reach last row, because j will retrace and leave the last word to the next line, which is the last line.
*/

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        string line;
        if(words.empty()) return result;
        int n = words.size();
        int i = 0, j = 0;  //each row put words[i, j) to the line
        while(i < n) {
           int count = 0; //character count one the current line
           j = i;
           line = words[i]; //should contain at least one word
           count += words[j++].size();
           while(count <= maxWidth && j < n) {
               count += 1+words[j++].size(); //including one leading space
           }
           if(count <= maxWidth) { //reach the last row, then just append words
               for(int k = i+1; k < j; ++k) { //left justified
                   line += " " + words[k];
               }
               line += string(maxWidth-count, ' '); //append padding spaces!
           } else {  //not reach last row, retrace one step back
               count -= 1+words[--j].size();
               int nwords = j-i; //number of words on the line
               int ngaps = nwords-1; //number of gaps on the line
               if(ngaps == 0) { // only one word on the line
                   line += string(maxWidth-count, ' '); //append padding spaces
               } else {
                    int remaining = maxWidth-count; //left over amount to be filled by space
                    //should spread residue to nwords-1 slots more-or-less evenly
                    //first r gaps get q+1, the rest get q (don't forget initial one space)
                    int q = remaining / ngaps + 1, r = remaining % ngaps;
                    for(int k = i+1; k < j; ++k) {
                        if(k-i <= r) line += string(q+1, ' ') + words[k];
                        else line += string(q, ' ') + words[k];
                    }
               }
           }
           result.push_back(line);
           i = j;
        }
        return result;
    }
};


/**************************************************** 
 ***    072,Hard,Edit Distance 
 ****************************************************/

/*
Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character
*/

/*
https://leetcode.com/discuss/43398/20ms-detailed-explained-c-solutions-o-n-space
*/

/*
Classic dynamic programing, classical solution using a 2-D matrix.
Consider boundary cases.
The matrix dp[i][j] means the edit distance for s[0, i) and t[0, j), excluding the last character. Here i and j means the length, not the index for the ending string.
so to calculate dp[i][j] we need information for s[i-1] and t[j-1].
For boundary cases:
dp[i][0] = i because changing length-i string to empty string requires i operations. Here we see the convenience of using length as dp's index variable.

We can first write two separate routines for boundary cases i = 0 and j = 0, and then write a nested loop for i >=1 and j >= 1. We can also put them in one loop and take care of boundary cases in if statements.
*/

//Solution 1. Use a 2D array storing the min edit distance between the prefixes of word1 and word2

class Solution {
public:
    int minDistance(string word1, string word2) {
        if(word1.empty()) return word2.size();
        if(word2.empty()) return word1.size();
        int m = word1.size(), n = word2.size();
        vector<vector<int> > dp(m+1, vector<int>(n+1, INT_MAX)); //dp[i][j]: min-distance between word1[0, i) and word2[0, j)
        for(int i = 0; i <= m; ++i) dp[i][0] = i;
        for(int j = 0; j <= n; ++j) dp[0][j] = j;
        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j <= n; ++j) {
                dp[i][j] = min(dp[i-1][j]+1, dp[i][j-1]+1);
                dp[i][j] = min(dp[i][j], dp[i-1][j-1] + (word1[i-1] != word2[j-1]));
            }
        }
        return dp[m][n];
    }
};

/*
Space optimized solution. Because we only need dp[i-1][j], dp[i][j-1] and dp[i-1][j-1] to calcualte dp[i][j], we can use two 1D arrays. cur and next. After each row we swap cur and next.

A even better optimized solution is to use one array curr, and use a temporary variable to store dp[i-1][j-1]. Before updating cur[i], its old value corresponds to dp[i-1][j], and the already updated value in cur[i-1] corresponds to dp[i][j-1]. The key is to find dp[i-1][j-1]. If every step before overwriting cur[i], we store it in a variable pre, so next step (j = j+1) the pre value is exactly dp[i-1][j-1]!. The additional work is to update pre at the current step, we do this by first storing the old cur[j] value in a variable tmp, and in the end assign it to pre.

A final optimization is that, when we see two characters are equal, e.g.
abe cde, we immediately get minD(abe, cde) = minD(ab, cd), instead of doing the minimum among
minD(abe, cd)+1, minD(ab, cde)+1, and minD(ab,cd).
The reason is that we know ajacent entries in the table can only differ by one. i.e. fabs(dp[i+1][j] - dp[i][j]) <= 1. so minD(ab, cd) <= minD(ab,cde)+1, and minD(ab, cd) is guaranteed to be the minimum among the three
For example:
dp(acb, ab) = dp(ac, ab) = 1
dp(acb, ad) = dp(ac, ad) + 1
*/

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<int> dp(n+1, INT_MAX);
        int pre = 0;
        //i = 0 case
        for(int j = 0; j <= n; ++j) dp[j] = j;

        for(int i = 1; i <= m; ++i) {
            pre = dp[0];
            dp[0] = i;
            for(int j = 1; j <= n; ++j) {
                if (word1[i-1] == word2[j-1]) {  //equal case
                    int tmp = dp[j];
                    dp[j] = pre;
                    pre = tmp;
                } else  {
                    int tmp = dp[j];
                    dp[j] = min(min(dp[j]+1, dp[j-1]+1), pre+1);
                    pre = tmp;
                }
            }
        }
        return dp[n];
    }
};

/**************************************************** 
 ***    076,Hard,Minimum Window Substring 
 ****************************************************/

/*
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"

Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S. 
*/

/*
The string T can have duplicated characters, so need to maintain a count for each unique character. We also need to keep track of which characters have been seen during the scan. We could use two maps, but a more elegant way is to use one map intialized as the count in T, and as we scan S and see a character in T, we decrement the individual count. As we scan the S, we also maintain the left side of the window as "istart", and increment it as needed. There are several things to consider:
1. how to distinguish between characters appearing in T and not? (e.g. "D" v.s. "A")
2. how to know whether we have all the characters we need to construct T?

For Q1, we can use an index vector (dict[256]) to store the occurrences of each alphabet in T, and for other alphabets, initialized as -s.len(). When scanning, if we see the individual count of a char to be smaller or equal than -s.len(), we know that it does not appear in T.
For Q2, we maintain another variable "count", initialized as T.len(), and decremented only when we have seen a "useful" character. "useful" means character appearing in T and also not redundant. How to know if it is redundant or not? We can check the individual count is negative or not. When count == 0, we know that s[istart, i] covers T.
The next step is to check if we could move istart to the right and remove some redundant characters. This can be checked by individual count ++dict[s[istart]] <= 0. After this step, s[istart, i] is the minimum window seen so far containing T, by definition, s[istart] for sure is needed for T.
Next is to continue scanning forward. This gives 16ms solution.

An optimization (16ms=>12ms): we remove s[istart], update the counts (dict and count), and move on. Once count == 0 again, we go back to previous step again. Because we know for sure that we don't need s[istart] in layer searches, so we can remove it and update count. This can avoid many uncessary executiong of if(count == 0) part.

The code can be further shortened: in the while loop:
while(++dict[s[istart] <= 0) istart++;
and then only do: istart++;
*/

class Solution {
public:
    string minWindow(string s, string t) {
        int slen = s.size();
        vector<int> dict(256, -slen);
        int nc = t.size();
        for(int i = 0; i < nc; ++i) {
            if(dict[t[i]] < 0) dict[t[i]] = 1;
            else dict[t[i]]++;
        }
        int istart = 0, count = nc;
        int min_len = INT_MAX, min_start = -1;
        for(size_t i = 0; i < s.size(); ++i) {
            if(--dict[s[i]] >= 0) count--;
            if(count == 0) {
                while(dict[s[istart]] < 0) {
                    dict[s[istart++]]++;
                }
                int len = i-istart+1;
                if(len < min_len) { min_len = len; min_start = istart; }
                dict[s[istart++]]++; count = 1;
            }
        }
        return min_start == -1 ? "" : s.substr(min_start, min_len);        
    }
};

/*
Another solution is to use a queue to store (position in S of) T's characters seen so far, see below:
*/
/// An old solution using queue
/// Use a window to slide from left to right
/// Use counts to store the occurrences of characters needed to complete (when we see a character that is in t, we decrement the corresponding
/// count in counts. The values can become negative, indicating that the character is in excess.
/// Use a queue to store the current window, the queue is maintained in the following way:
/// 1. when we see a character that is in t, add it to end of queue
/// 2. If the new character in (1) is the same as the front of queue, and a is in excess we pop front (e.g. S = abea.. T = ab, but not: 
/// S = abea.. T = aab, where second a in S is required).
/// 3. when count is zero, we calculate the length, update minL if needed
/// 4. when we pop and push, we incre/decre counts[c], and depending on its sign, update cnt acoordingly.

class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> counts(256, 0);
        int cnt = 0; // number of characters required to completely include t.
        for (int i = 0; i < t.size(); i++) { 
            counts[t[i]]++; 
            cnt++;
        }
        int minl = INT_MAX, mini = 0;
        deque<int> q;
        
        for(int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (t.find(c) == string::npos) continue;
            
            counts[c]--;
            if(counts[c] >= 0) cnt--;
            else if (s[q.front()] == c) {
                counts[c]++;
                q.pop_front();
            }
            q.push_back(i);
            
            if (cnt == 0) {
                while (counts[s[q.front()]] < 0) {
                    counts[s[q.front()]]++;
                    q.pop_front();
                }
                int len = q.back()-q.front()+1;
                if (len < minl) { minl = len; mini = q.front(); }
            }
        }
        if (minl == INT_MAX) return string();
        else return s.substr(mini, minl);
    }
};

/**************************************************** 
 ***    084,Hard,Largest Rectangle in Histogram 
 ****************************************************/

/*
Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

The largest rectangle is shown in the shaded area, which has area = 10 unit.

For example,
Given height = [2,1,5,6,2,3],
return 10. 
*/

/*
The rectangle is limited by the histrogram bar of the lowest height.
Scan the histogram one-by-one. Say we already scanned i bars, and the next is i+1. There are three cases:
1. i+1 is higher than i. In this case, we can't say anything about the possible rectangles formed by i, so we just push i+1 to stack.

     ++++
     +  +
  ++++  +
  +  +  +
  +  +  +
+++++++++++++++++++++++++++++++++++++++
   i  i+1

2. i+1 is lower than i. In this case, we can say for sure that the largest rectangle that bar i can form will terminate at i+1. So we calculate that area, and pop-out i (since we don't need i anymore)

  ++++
  +  +
  +  ++++
  +  +  +
  +  +  +
+++++++++++++++++++++++++++++++++++++++
   i  i+1

The tricky part is, when we pop-out i, i+1 can be extended to the left, since it is lower, and the largest rectangle formed by i+1 can extend to the left, so we have to store not only the height but also the current left boundary position of the rectangle formed by i. After removing i effectively we will have, which waits to be checked in the next step.


  +++++++
  +     +
  +     +
+++++++++++++++++++++++++++++++++++++++
   i  i+1

3. i+1 is same height as i. We can still use 2, because i+1 will inherit the position of i.

*/

/// Solution 1 using a stack of both position and height. No need to handle degenerate cases separately. O(n) time amorized, because each bar is pushed and popped at most once. O(n) space for sstack.
/// We use a variable j to store the position of recently popped bars, and make the new bar inherit this position when inserted to stack.
/// Another trick is to append a sentinel of height 0 in the end of height vector, so that all the bars in the stack will eventually be popped out to be examined.

class Solution {
public:
    int largestRectangleArea(vector<int>& height) {
        if(height.empty()) return 0;
        int max_area = 0;
        stack<pair<int, int> > st; //store position and height 
        height.push_back(0); //sentinel at the end
        int n = height.size();
        for(int i = 0; i < n; ++i) {
            int j = i, h = 0;
            while(!st.empty() && st.top().second > height[i]) {
                j = st.top().first;
                h = st.top().second;
                max_area = max(max_area, (i-j)*h);
                st.pop();
            }
            st.push(make_pair(j, height[i])); //inherits position j from popped elements
        }
        return max_area;
    }
};

/// Solution 2 using a stack only tracking the index of bar in the height. We don't need to store the inherited position, because we observe that the inherited position is always one plus the position of the bar at top of stack after the bar currently under examination is popped out.
/// Again O(n) amortized time and O(n) space.

class Solution {
public:
    int largestRectangleArea(vector<int>& height) {
        if(height.empty()) return 0;
        int max_area = 0;
        stack<int> st; //store position in height
        height.push_back(0); //sentinel at the end
        int n = height.size();
        for(int i = 0; i < n; ++i) {
            while(!st.empty() && height[st.top()] > height[i]) {
                int h = height[st.top()];
                st.pop();
                int j = st.empty() ? 0 : st.top() + 1;
                max_area = max(max_area, (i-j)*h);
            }
            st.push(i);
        }
        return max_area;
    }
};

/*
Solution 3, O(n) amortized time, and O(n) space. The idea is to find the left and right boundaries of the rectangle for each bar. This means that for each bar i, we find left[i] and right[i] such that bars within them have height no less than bar[i], and the spacing between the two is as wide as possible. We can achieve this in O(n) amortized time.
Scan from left to right to find left[i]:
1. If bar i+1 is higher than i, then left[i+1] = i+1.
2. If bar i+1 is lower than i, we start scanning from left[i]-1 towards left, and find the first bar j whose height is smaller than i+1, then left[i+1] = j+1
3. If bar i+1 is same height as i, then left[i+1] = left[i]
Similarly for right.
We can proove that we never scan each element more than twice, so amortized O(n).

We can further optimize step 2 in that if we find a bar j having the same height as i+1, then immediately we have left[i+1] = left[j], and break the loop.
*/

class Solution {
public:
    int largestRectangleArea(vector<int>& height) {
        if(height.empty()) return 0;
        int max_area = 0;
        int n = height.size();
        vector<int> left(n, 0), right(n, n-1);
        for(int i = 1; i < n; ++i) { //get left
            if(height[i] > height[i-1]) left[i] = i;
            else if(height[i] == height[i-1]) left[i] = left[i-1];
            else { //start scanning from left[i-1]-1 backwards
                int j = left[i-1]-1;
                while(j >= 0 && height[j] >= height[i]) j--;
                left[i] = j+1;
            }
        }
        for(int i = n-2; i >= 0; --i)  {  //get right
            if(height[i] > height[i+1]) right[i] = i;
            else if(height[i] == height[i+1]) right[i] = right[i+1];
            else { //start scanning from right[i+1]+1 forwards
                int j = right[i+1]+1;
                while(j < n && height[j] >= height[i]) j++;
                right[i] = j-1;
            }
        }
        for(int i = 0; i < n; ++i)
            max_area = max(max_area, height[i]*(right[i] - left[i] + 1));

        return max_area;
    }
};

/// Solution 4, O(n2) worst case time, and O(1) space. Do not use stack, rather modify the heights in height
class Solution {
public:
    int largestRectangleArea(vector<int>& height) {
        if(height.empty()) return 0;
        int max_area = 0;
        height.push_back(0);
        int n = height.size();
        for(int i = 1; i < n; ++i) {
            if(height[i] >= height[i-1]) continue;
            int j = i-1;
            while(j >= 0 && height[j] > height[i]) {
                max_area = max(max_area, (i-j)*height[j]);
                height[j] = height[i];
                j--;
            }
        }
        return max_area;
    }
};



/**************************************************** 
 ***    085,Hard,Maximal Rectangle 
 ****************************************************/

/*
Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing all ones and return its area. 
*/

// Solution 1. Use the routine of finding the largest rectangle in the histogram.
// Scan from top to bottom, find largest rectangle at current level. 

class Solution {
public:
    int maximalRectangle(vector<vector<char> >& matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> height(n, 0);
        int max_area = 0;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                height[j] = (matrix[i][j] == '1') ? height[j]+1 : 0;
            }
            max_area = max(max_area, largestRectangleArea(height));
        }
        return max_area;
    }

    int largestRectangleArea(vector<int>& height) {
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
                max_area = max(max_area, h*(i-j));
            }
            s.push_back(i);
        }
        return max_area;
    }
};

/*
Solution 2 using dynamic programming. For each row, use three arrays, left/right/height to store the left and right boundary and height of maximum rectangle enclosing matrix[i][j] for the rows seen so far (just like the bars in the histogram problem). Use the values at step i to calculate the values at step i+1.

             +
         +   +
         +   + +
         + + + +
index: 0 1 2 3 4
left: -1 1 1 3 3
right: 5 1 4 3 4
height:0 3 1 4 2

Now check the new row, we track the first left seen so far.

           +
       +   +
       +   + +
       + + + +
     0 1 2 3 4 
     + + +  : cur_left = 0
the new left is simply the maximum of old left and cur_left
the new right is simply the minimum of old right and cur_right
We assign cur_left values in an eager way: whenever we see a '0', we asisgn cur_left to j+1.

Caveat: 
1. for '0' entries, left[i] can be -1, but right[i] should be n, due to the min operation used to update its value.
2. Remember to properly initialize cur_left and cur_right when scanning each row.
*/

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> left(n, -1), right(n, n), height(n, 0);
        int cur_left = 0, cur_right = 0;
        int max_area = 0;
        for(int i = 0; i < m; ++i) {
            cur_left = 0; cur_right = n-1; //initialize
            for(int j = 0; j < n; ++j) { //scan left to right
                height[j] = (matrix[i][j] == '0') ? 0 : height[j]+1;
                if(matrix[i][j] == '0') {
                    left[j] = -1;
                    cur_left = j+1; //pre-assign cur_left to next 
                } else {
                    left[j] = max(left[j], cur_left);
                }
            }
            for(int j = n-1; j >= 0; --j) { //scan right to left
                if(matrix[i][j] == '0') {
                    right[j] = n; //cannot be -1 due to the min operation!
                    cur_right = j-1; //pre-assign cur_right to next
                } else {
                    right[j] = min(right[j], cur_right);
                }
            }
            //now we have left[j], right[j], and height[j] in place
            for(int j = 0; j < n; ++j) {
                max_area = max(max_area, height[j]*(right[j] - left[j] + 1));
            }
        }
        return max_area;
    }
};

/**************************************************** 
 ***    087,Hard,Scramble String 
 ****************************************************/

/*
Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.
Below is one possible representation of s1 = "great":

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t

To scramble the string, we may choose any non-leaf node and swap its two children.
For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t

We say that "rgeat" is a scrambled string of "great".
Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a

We say that "rgtae" is a scrambled string of "great".
Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1. 
*/

/*
Solution 1. Recursive dfs with branching by anagram checking, 8ms. 

If no branching, time complexity is around 5^n (exponential algorithm!)
f(n) = 2*(f(1)+f(n-1)) + 2*(f(2)+f(n-2)+ ... + 2(f(n-1)+f(1)).
f(n+1) = ...
f(n+1) = 5f(n) => f(n) = 5^n.

Try all ways of cutting the string into two parts, and recursively check if the two parts are scramble strings. Check every possibilities of partition:
e.g.  a0-a4 v.s. b0-b4
check  a0 | a1-a4 v.s. b0 | b1-b4; 
       a0a1 | a2-a4 v.s. b0b1 | b2-b4 ... 
and
       a0 | a1-a4 v.s. b0-b3 | b4; 
       a0a1 | a2-a4 v.s. b0-b2 | b3b4 ...

Anagram checking: indexed map from 0 to 256. If we assume only a-z characters and use 26 entries, we can reduce the time to 4ms.

search s1, increment character counts,
search s2, decrement character counts. If found a negative value, then we know that they are not anagram.
*/

class Solution {
public:
    bool isScramble(string s1, string s2) {
        if(s1.size() != s2.size()) return false;
        if(s1.empty()) return true; //empty string
        return isScramble(s1, 0, s2, 0, s1.size());
    }

    bool isScramble(const string& s1, int lo1, const string& s2, int lo2, int len) {
        if(len == 0) return true;
        if(len == 1) return s1[lo1] == s2[lo2];
        if(!isAnagram(s1, lo1, s2, lo2, len)) return false;
        //cut s1 and s2 into two parts
        for(int i = 1; i < len; ++i) {
            if(isScramble(s1, lo1, s2, lo2, i) && isScramble(s1, lo1+i, s2, lo2+i, len-i)) return true;
            if(isScramble(s1, lo1, s2, lo2+len-i, i) && isScramble(s1, lo1+i, s2, lo2, len-i)) return true;
        }
        return false;
    }

    bool isAnagram(const string& s1, int lo1, const string& s2, int lo2, int len) {
        vector<int> dict(256, 0);
        for(int i = lo1; i < lo1+len; ++i) {
            dict[s1[i]]++;
        }
        for(int i = lo2; i < lo2+len; ++i) {
            if(--dict[s2[i]] < 0) return false;
        }
        return true;
    }
};

/*
2. 3D DP solution (bottom-up), 284 ms even with adding isAnagram checking for branching.  3 indices, len, i, j
//dp[i][j][len]: whether s1[i, i+len) and s2[j, j+len) is scramble, len can be 0 to n, i, j can be 0 to n-1
len as outer loop. Special treatment when len = 1.
*/

class Solution {
public:
    bool isScramble(string s1, string s2) {
        if(s1.size() != s2.size()) return false;
        if(s1.empty()) return true; //empty string
        int n = s1.size();
        //dp[i][j][len]: whether s1[i, i+len) and s2[j, j+len) is scramble, len can be 0 to n, i, j can be 0 to n-1
        dp.resize(n+1, vector<vector<bool> >(n, vector<bool>(n, false)));
        for(int len = 1; len <= n; ++len) {
            for(int i = 0; i+len <= n; ++i) {
                for(int j = 0; j+len <= n; ++j) {
                    if(len == 1) {
                       dp[len][i][j] = (s1[i] == s2[j]);
                       continue;
                    }
                    if(!isAnagram(s1, i, s2, j, len)) { dp[len][i][j] = 0; continue; }
                    for(int l = 1; l < len; ++l) {
                        dp[len][i][j] = ((dp[l][i][j] && dp[len-l][i+l][j+l]) || (dp[l][i][j+len-l] && dp[len-l][i+l][j]));
                        if(dp[len][i][j]) break;
                    }
                }
            }
        }
        return dp[n][0][0];
    }
    
    bool isAnagram(const string& s1, int lo1, const string& s2, int lo2, int len) {
        vector<int> dict(256, 0);
        for(int i = lo1; i < lo1+len; ++i) {
            dict[s1[i]]++;
        }
        for(int i = lo2; i < lo2+len; ++i) {
            if(--dict[s2[i]] < 0) return false;
        }
        return true;
    }

    vector<vector<vector<bool> > > dp;
};

/*
3. 3D DP solution with memoization (20ms). now the 3D vector can have three values, -1, 0, 1. -1 means uninitialized, 0 means not scramble, 1 means scramble. Need to ensure each call to scramble returns either 0 and 1 and properly sets dp[len][i][j] at the first time.
*/

class Solution {
public:
    bool isScramble(string s1, string s2) {
        if(s1.size() != s2.size()) return false;
        if(s1.empty()) return true; //empty string
        int n = s1.size();
        //dp[i][j][len]: whether s1[i, i+len) and s2[j, j+len) is anagram, len can be 0 to s1.size, i, j can be 0 to n-1
        dp.resize(n+1, vector<vector<int> >(n, vector<int>(n, -1)));
        return isScramble(s1, 0, s2, 0, s1.size());
    }
    //memoization, always return 0 or 1
    int isScramble(const string& s1, int i, const string& s2, int j, int len) {
        int tag = dp[len][i][j];
        if(tag >= 0) return tag;

        if(len == 0) dp[len][i][j] = 1;
        else if(len == 1) dp[len][i][j] = (s1[i] == s2[j]);
        else if(!isAnagram(s1, i, s2, j, len)) dp[len][i][j] = 0;
        else {
             dp[len][i][j] = 0; //should first set to zero (for not found case)
             //cut s1 and s2 into two parts
             for(int l = 1; l < len; ++l) {
                 if( (isScramble(s1, i, s2, j, l) && isScramble(s1, i+l, s2, j+l, len-l) ) ||
                     (isScramble(s1, i, s2, j+len-l, l) && isScramble(s1, i+l, s2, j, len-l) ) ) {
                     dp[len][i][j] = 1;
                     break;
                 }
             }
        }
        return dp[len][i][j];
    }

    bool isAnagram(const string& s1, int lo1, const string& s2, int lo2, int len) {
        vector<int> dict(256, 0);
        for(int i = lo1; i < lo1+len; ++i) {
            dict[s1[i]]++;
        }
        for(int i = lo2; i < lo2+len; ++i) {
            if(--dict[s2[i]] < 0) return false;
        }
        return true;
    }

    vector<vector<vector<int> > > dp;
};



/**************************************************** 
 ***    097,Hard,Interleaving String 
 ****************************************************/

/*
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false. 
*/

/*
Dynamic programming.
Use a 2D array recording whether s1[0, i) and s2[0, j) interleaves to form s3[0, i+j).

If dp[i][j] is true, it can be either of the two cases:
dp[i-1][j] is true and s1[i-1] == s3[i+j-1]
1)
adb | e
a b
  d   | e 

2).
a d e |b
  a  | b
 d e

Boundary cse: i = 0 or j = 0.
we further define dp[0][0] = 0.

We can put boundary condition in various places (either outside main loop, or inside)
*/

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
        if(n1+n2 != n3) return false;
        //table[i][j]: s3[0 .. i+j-1] is interleaved by s1[0..i-1] and s2[0 .. j-1]
        vector<vector<bool> > table(n1+1, vector<bool>(n2+1, false));
        table[0][0] = true;
        for (int i = 0; i < n1 && s1[i] == s3[i]; ++i) {
            table[i+1][0] = true; //only uses s1
        }
        for (int j = 0; j < n2 && s2[j] == s3[j]; ++j) {
            table[0][j+1] = true; //only uses s2
        }
        for (int i = 0; i < n1; ++i) { //check s1[i]
            for (int j = 0; j < n2; ++j) { //check s2[j]
                table[i+1][j+1] = (s3[i+j+1] == s2[j] && table[i+1][j]) ||
                                  (s3[i+j+1] == s1[i] && table[i][j+1]);
            }
        }
        return table[n1][n2];
    }
};

/* Slightly optimized solution still using 2D array. Use length as outer loop. Avoid unecessary checks. 4ms. */

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.empty()) return s2 == s3;
        if(s2.empty()) return s1 == s3;
        int m = s1.size(), n = s2.size(), p = s3.size();
        if(m + n != p) return false;
        vector<vector<bool> > dp(m+1, vector<bool>(n+1, false)); //dp[i][j], whether s1[0 .. i) and s2[0 .. j) interleaves to form s3[0 .. i+j).
        dp[0][0] = true;
        for(int len = 1; len <= p; ++len) { //determine s3[0, len), check s3[0, len-1) and s3[len-1]
            bool found = false;
            for(int i = 0; i <= min(len-1, m); ++i) { //checking s1[0, i) and s1[i]
                int j = len - i-1; //checking s2[0, j) and s2[j]
                if(dp[i][j]) {
                    if(s1[i] == s3[len-1]) found = dp[i+1][j] = true; 
                    if(s2[j] == s3[len-1]) found = dp[i][j+1] = true;
                }
            }
            if(!found) return false;
        }
        return dp[m][n];
    }
};

/*
Space optimized version: only a 1D array (8ms).
*/

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.empty()) return s2 == s3;
        if(s2.empty()) return s1 == s3;
        int m = s1.size(), n = s2.size(), p = s3.size();
        if(m + n != p) return false;
        vector<bool> dp(n+1, false); //dp[i][j], whether s1[0 .. i) and s2[0 .. j) interleaves to form s3[0 .. i+j).
        dp[0] = true;
        for(int j = 1; j <= n; ++j) {
            dp[j] = dp[j-1] && (s2[j-1] == s3[j-1]);
        }
        
        for(int i = 1; i <= m; ++i) { //checking s1[0, i)
            dp[0] = dp[0] && (s1[i-1] == s3[i-1]);
            for(int j = 1; j <= n; ++j) { //checking s2[0, j)
                dp[j] = (dp[j] && (s1[i-1] == s3[i+j-1])) ||
                            (dp[j-1] && (s2[j-1] == s3[i+j-1]));
            }
        }
        return dp[n];
    }
};


/**************************************************** 
 ***    099,Hard,Recover Binary Search Tree 
 ****************************************************/

/*
Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.
Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution? 

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

/*
Solution 1. Using morris traversal. Morris traversal (alternative while loop where visit only appears once)

When finding swapped elements, can optimize and use :

if(!n1) n1 = prev;
n2 = node;

 1   3   2   4   5
      3>2: n1 = 3, n2 = 2;
 1   4   3   2   5
      4>3 3>2: n1 = 4, n2 = 2;
swap values of two nodes, not nodes themselves

*/

class Solution {
public:
   void recoverTree(TreeNode* root) {
        if(!root) return;
        TreeNode *node = root, *prev = NULL;
        TreeNode *n1(NULL), *n2(NULL); //node to be swapped
        //now starts morris traversal
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
            //visit node, then move to right
            if(prev && prev->val > node->val) {
                if(!n1) n1 = prev;
                n2 = node;
            }
            prev = node;
            node = node->right;
        }
        if(n1 && n2) {
            int t = n1->val;
            n1->val = n2->val;
            n2->val = t;
        }
   }
};

/*
Another solution using inorder traversal without vector<>. Just store prev at last step and compare with node->val at current step.
O(lg n) space for the stack space of recursive calls.
*/

class Solution {
public:
    void recoverTree(TreeNode* root) {
        if(!root) return;
        inorder(root);
        int t = n1->val;
        n1->val = n2->val;
        n2->val = t;
    }
    void inorder(TreeNode *node) {
        if(!node) return;
        inorder(node->left);
        //visit node
        if(prev && prev->val > node->val) {
           if(!n1) n1 = prev;
           n2 = node;
        }
        prev = node;
        inorder(node->right);
    }
    TreeNode *n1 = NULL, *n2 = NULL, *prev = NULL;
};

/*
The worst solution is to use a 1D array to store the inorder results. O(n) space.
*/

class Solution {
public:
   void recoverTree(TreeNode* root) {
        if(!root) return;
        vector<TreeNode*> nodes;
        inorder(root, nodes);
        TreeNode *n1(NULL), *n2(NULL);
        for (size_t i = 0; i < nodes.size()-1; ++i) {
            if(nodes[i]->val > nodes[i+1]->val) {
                if(!n1) n1 = nodes[i];
                n2 = nodes[i+1];
            }
        }
        if(n1 && n2) {
            int tmp = n1->val;
            n1->val = n2->val;
            n2->val = tmp;
        }
    }
    void inorder(TreeNode *root, vector<TreeNode*>& nodes) {
       if(!root) return;
       inorder(root->left, nodes);
       nodes.push_back(root);
       inorder(root->right, nodes);
    }
};



/**************************************************** 
 ***    115,Hard,Distinct Subsequences 
 ****************************************************/

/*
Given a string S and a string T, count the number of distinct subsequences of T in S.

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3. 
*/

/*
dynamic programming with various possible optimizations

Let dp[i][j] denote number of distinct subsequencies for s[0, i), and t[0, j). Then the distinct subsequency can be constructed from two cases:
a) s[0, j-1) and t[0, j), or, removing s[i-1]
b) s[0, i-1) and t[0, j-1) and if s[i-1] == t[j-1].
Boundary case:
s[i][0] = 1 for all i >= 0, e.g. "" and "", or "ab" and "".
s[0][j] = 0 for all j > 0, e.g. "" and "abc"

1. Scan t as outer loop, use a 2D array. This is less efficient.
2. Scan t as outer loop, use a 1D array and a prev variable. need to properly update prev.

3. Scan s as outer loop, use a 2D array.
4. Scan s as outer loop, use two 1D arrays.
*/

/*
Solution 1. Scan t as outer loop, use a 2D array. This is less efficient.
*/

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = t.size(), n = s.size();
        //outer loop: t, inner loop s
        //dp[i][j]: num-distinct for s[0..j) and t[0..i)
        vector<vector<int> > dp(m+1, vector<int>(n+1, 0));
        for(int j = 0; j <= n; ++j) dp[0][j] = 1;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
               dp[i+1][j+1] = dp[i+1][j] + (t[i] == s[j] ? dp[i][j] : 0);
            }
        }
        return dp[m][n];
    }
};

/*
Solution 2. Scan t as outer loop, use a 1D array and a prev variable. need to properly update prev.
*/

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = t.size(), n = s.size();
        //dp[j] at step i: num-distinct for s[0..j) and t[0..i)
        vector<int> dp(n+1, 1);  //initially 1
        int prev = 0;
        for(int i = 0; i < m; ++i) {
            prev = dp[0];
            dp[0] = 0; //dp[0] means number for t and "", only when t == "", dp[0] = 1, otherwise dp[0] = 0
            for(int j = 0; j < n; ++j) {
               int tmp = dp[j+1];
               dp[j+1] = dp[j] + (t[i] == s[j] ? prev : 0);
               prev = tmp;
            }
        }
        return dp[n];
    }
};

/*
Solution 3. Scan s as outer loop, use a 2D array. can further optimized second loop as j <= min(i, n), but runtime does not get shorter.
*/

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        vector<vector<int> > dp(m+1, vector<int>(n+1, 0));
        dp[0][0] = 1;
        for(int i = 1; i <= m; ++i) {
            dp[i][0] = 1;
            for(int j = 1; j <= n; ++j) {
                dp[i][j] = dp[i-1][j] + (s[i-1] == t[j-1] ? dp[i-1][j-1] : 0);
            }
        }
        return dp[m][n];
    }
};

/*
Solution 4. Scan s as outer loop, use two 1D arrays.
*/

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        vector<int> dp(n+1, 0), newdp(n+1, 0);
        dp[0] = newdp[0] = 1; //entry 0 is always 1  
        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j <= n; ++j) {
                newdp[j] = dp[j] + (s[i-1] == t[j-1] ? dp[j-1] : 0);
            }
            dp.swap(newdp);
        }
        return dp[n];
    }
};


/**************************************************** 
 ***    117,Hard,Populating Next Right Pointers in Each Node II 
 ****************************************************/

/*
Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

Note:

    You may only use constant extra space.

For example,
Given the following binary tree,

         1
       /  \
      2    3
     / \    \
    4   5    7

After calling your function, the tree should look like:

         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \    \
    4-> 5 -> 7 -> NULL
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
 ***    123,Hard,Best Time to Buy and Sell Stock III 
 ****************************************************/

/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/

/// Dynamic programmming solution that extends to general k cases.
class Solution {
public:
    int maxProfit(vector<int> &prices) {
		int n = prices.size();
		if(n <= 1) return 0;
		int numTrans = 2; //number of transactions
		//mp[k][j] is maximum prof at the end of day j after performing at most k transactions
		vector<vector<int> > mp(numTrans+1, vector<int>(n, 0)); 
		int maxAll = 0; //maximum of all posibilities
		//maxProf[k][j] is the maximum of two cases:
		// a. no selling at day j, so upto k transactions (including 1,2,...k) at end of day j-1: mp[k][j-1]
		// b. selling at day j: for some jj < j, perform upto k-1 transactions at jj, and buy at jj and sell at day j,
		// the profit is the maximum of mp[k-1][jj] + prices[j] - prices[jj] among all 0 <= jj < j. Thus:
		// mp[k][j] = max( mp[k][j-1], prices[j] + max(mp[k-1][jj]-prices[jj], for all jj < j) )
		// when we increase j, we keep a variable tmpMax storing the last term and update properly.
		// The clever part is to take prices[j] out of the maximum expression of jj.
		for(int k = 1; k <= numTrans; ++k) {
			int tmpMax = mp[k-1][0] - prices[0]; //k = 1, tmpMax = mp[k-1][0] - prices[0];
			for(int j = 1; j < n; ++j) {
				mp[k][j] = max(mp[k][j-1], tmpMax+prices[j]);
				tmpMax = max(tmpMax, mp[k-1][j]-prices[j]);
				maxAll = max(maxAll, mp[k][j]);
			}
		}
		return maxAll;
    }
};

/// Space optimized DP solution. Use only one array, and a temporary variable old to store value from last k

class Solution {
public:
    int maxProfit(vector<int> &prices) {
		int n = prices.size();
		if(n <= 1) return 0;
		int numTrans = 2; //number of transactions
		//mp[j] is maximum prof at the end of day j after performing at most k transactions
		vector<int> mp(n, 0); 
		int maxAll = 0; //maximum of all posibilities
		//maxProf[k][j] is the maximum of two cases:
		// a. no selling at day j, so upto k transactions (including 1,2,...k) at end of day j-1: mp[k][j-1]
		// b. selling at day j: for some jj < j, perform upto k-1 transactions at jj, and buy at jj and sell at day j,
		// the profit is the maximum of mp[k-1][jj] + prices[j] - prices[jj] among all 0 <= jj < j. Thus:
		// mp[k][j] = max( mp[k][j-1], prices[j] + max(mp[k-1][jj]-prices[jj], for all jj < j) )
		// when we increase j, we keep a variable tmpMax storing the last term and update properly.
		// The clever part is to take prices[j] out of the maximum expression of jj.
		
		for(int k = 1; k <= numTrans; ++k) {
			int tmpMax = mp[0] - prices[0]; //k = 1, tmpMax = mp[k-1][0] - prices[0];
			for(int j = 1; j < n; ++j) {
			    int old = mp[j]; //mp[k-1][j]
				mp[j] = max(mp[j-1], tmpMax+prices[j]);
				tmpMax = max(tmpMax, old-prices[j]);
				maxAll = max(maxAll, mp[j]);
			}
		}
		return maxAll;
    }
};


/**************************************************** 
 ***    124,Hard,Binary Tree Maximum Path Sum 
 ****************************************************/

/*
Given a binary tree, find the maximum path sum.

The path may start and end at any node in the tree.

For example:
Given the below binary tree,

       1
      / \
     2   3

Return 6. 
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
Recursive solution. 
Maximum path sum of tree rooted at x is the maximum of three cases:
 1. maximum path sum of x's left subtree (not passing x), if x's left subtree exists
 2. maximum path sum of x's right subtree (not passing x), if x's right subtree exists
 3. maximum path crossing x (x->val + maximum path from x's left child to anywhere in x's left subtree + maximum path from x's right child to anywhere in x's right subtree)
Note that the node values can be negative, so in case 3, so, some sub-paths can be length 0 (e.g. in case 3)

Therefore, we store a maximum path sum for a path originating from the root, and ending at any nodes (including the root itself), as mfr (maximum from root). The function returns the maximum path sum of the tree and also sets the mfr value by the reference.
maxPathSum(root) =  maximum of :
1) maxPathSum(root->left) if left exists
2) maxPathSum(root->right) if right exits
3) root->val (has to include root) + max(0, mfr(root->left)) + max(0, mfr(root->right)). Because the mfr can be negative for a subtree, we should compare it with 0 before addition.
Finally, we need to update the mfr of the root, which is simply:
root->val + maximum of 0, mfr(root->left), andmfr(root->right).

We initialize all values as INT_MIN.
*/

class Solution {
public:

    int maxPathSum(TreeNode* root) {
        if(!root) return 0;
        int mfr = INT_MIN; //max from root
        return maxPathHelper(root, mfr);
    }
    int maxPathHelper(TreeNode* root, int& mfr) {
        int mfr_left = INT_MIN, mfr_right = INT_MIN;
        int mp_left = INT_MIN, mp_right = INT_MIN;
        if(root->left) mp_left = maxPathHelper(root->left, mfr_left);
        if(root->right) mp_right = maxPathHelper(root->right, mfr_right);
        mfr = root->val + max(max(mfr_left, mfr_right), 0);

        int maximum = root->val + max(0, mfr_left) + max(0, mfr_right);
        maximum = max(maximum, mp_left);
        maximum = max(maximum, mp_right);
        return maximum;
    }
};

/*
A simplified version. For each subtree only calculate the maximum path originating from root, but keep a global maxSum variable that calculates the maximum path sum for each subtree. Update the maxSum for each subtree.
*/

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        if(!root) return 0;
        int maxSum = INT_MIN;
        maxFromRoot(root, maxSum);
        return maxSum;
    }
    int maxFromRoot(TreeNode* root, int& maxSum) {
        if(!root) return INT_MIN;
        int left = max(maxFromRoot(root->left, maxSum), 0);
        int right = max(maxFromRoot(root->right, maxSum), 0);
        maxSum = max(maxSum, root->val + left + right); //update maxSum
        return root->val + max(left, right);
    }
};

/*
Can further simplify, and put maxSum as a class member.
*/

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        if(!root) return 0;
        maxFromRoot(root);
        return maxSum;
    }
    int maxFromRoot(TreeNode* root) {
        if(!root) return INT_MIN;
        int left = max(maxFromRoot(root->left), 0);
        int right = max(maxFromRoot(root->right), 0);
        maxSum = max(maxSum, root->val + left + right); //update maxSum
        return root->val + max(left, right);
    }
    int maxSum = INT_MIN;
};



/**************************************************** 
 ***    126,Hard,Word Ladder II 
 ****************************************************/

/*
Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:

    Only one letter can be changed at a time
    Each intermediate word must exist in the word list

For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Return

  [
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
  ]

Note:

    All words have the same length.
    All words contain only lowercase alphabetic characters.
*/

/*
https://leetcode.com/discuss/41689/88ms-accepted-solution-with-68ms-word-ladder-88ms-word-ladder

=== Solution 1 ===
Usual BFS, do not change wordList, rather create a new set (unvisited) and operate on it.
Create a predecessor subgraph of the BFS search (each node can have multiple parents, so use a vector for the parent field). The tree structure is stored in the map<string, vector<string> structure called predecessors.
After the map is built, traverse the map from end to begin and reconstruct the ladders. 
*/
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
        vector<vector<string> > result;
        int lword = beginWord.size();
        unordered_set<string> unvisited = wordList;
        unvisited.erase(beginWord);
        unvisited.insert(endWord);
        unordered_set<string> current, next;
        unordered_map<string, vector<string> > predecessors; //predecessor map
        current.insert(beginWord);
        while(!current.empty()) {
            for(auto wd : current) {
                if(wd == endWord) break; //finishes
                unvisited.erase(wd);
                for(int i = 0; i < lword; ++i) {
                    char tmp = wd[i];
                    for(char c = 'a'; c <= 'z'; ++c) {
                        if(c == tmp) continue;
                        wd[i] = c;
                        if(unvisited.count(wd) && current.count(wd) == 0) { //belongs to wordList, and unvisited
                            next.insert(wd);
                            string owd = wd;
                            owd[i] = tmp;
                            predecessors[wd].push_back(owd);
                        }
                    }
                    wd[i] = tmp;
                }
            }

            current.swap(next);
            next.clear();
        }

        //now we have predecessor map, we can build the result using dfs
        vector<string> path;
        dfs(endWord, beginWord, predecessors, path, result);
        return result;
    }
    
    void dfs(const string& word, const string& beginWord, unordered_map<string, vector<string> >& predecessors, vector<string>& path, vector<vector<string> >& result) {
        path.insert(path.begin(), word);
        if(word == beginWord) {
            result.push_back(path);
            path.erase(path.begin());
            return;
        }
        for(auto it : predecessors[word]) {
            dfs(it, beginWord, predecessors, path, result);
        }
        path.erase(path.begin());
    }
};

/*
=== Solution 2 ===
Two way BFS. Instead of storing predecessor, store children map (we can in principle store two predecessor maps for the two direction, but one is much simpler). Since we are going to have multiple predecessor or children, storing children map does not increase the memory usage. Also, children graph makes it easy to construct the ladder path (array push back instead of inserting to front).

Use a tag "found" to check if found. Only construct the ladder when found is set as true.

Use a tag "forward" to keep track of search direction (forwards or backwards)
*/

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
        vector<vector<string> > result;
        
        unordered_set<string> current, opposite, next;
        unordered_map<string, vector<string> > children; //children map
        unordered_set<string> unvisited = wordList;

        unvisited.erase(beginWord);
        unvisited.erase(endWord);

        current.insert(beginWord);
        opposite.insert(endWord);
        bool forward = true;
        bool found = false;

        while(!current.empty()) {
            for(auto word : current) unvisited.erase(word);
            for(auto word : current) {
                //unvisited.erase(word);
                string newWord = word;
                for(auto it = newWord.begin(); it != newWord.end(); ++it) {
                    char tmp = *it;
                    for(*it = 'a'; (*it) <= 'z'; ++(*it)) {
                        if(*it == tmp) continue;
                        if(opposite.count(newWord)) { //found word in opposite search front
                            found = true;
                            if(forward) children[word].push_back(newWord);
                            else children[newWord].push_back(word);
                        } else if(unvisited.count(newWord)/* && !current.count(newWord)*/) { //belongs to wordList, and unvisited
                            next.insert(newWord);
                            if(forward) children[word].push_back(newWord);
                            else children[newWord].push_back(word);
                        }
                    }
                    *it = tmp; //revert
                }
            }
            if(found) break;
            
            current.swap(next);
            next.clear();
            if(current.size() > opposite.size()) { 
                current.swap(opposite);
                forward = !forward;
            }
        }
        //only proceed when found
        if(found) {
            vector<string> path;
            dfs(beginWord, endWord, children, path, result);
        }
        return result;
    }

    void dfs(const string& beginWord, const string& endWord, unordered_map<string, vector<string> >& children, vector<string>& path, vector<vector<string> >& result) {
        path.push_back(beginWord);
        if(beginWord == endWord) {
           result.push_back(path);
           path.pop_back();
           return;
        }
        for(auto it : children[beginWord]) {
            dfs(it, endWord, children, path, result);
        }
        path.pop_back();
    }
};

/*
=== Solution 3 ===
Bi-directional BFS, use recursive to build children graph, rather than interative. 
*/

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
        vector<vector<string> > result;
        
        unordered_set<string> current, opposite;
        unordered_map<string, vector<string> > children; //children map
        unordered_set<string> unvisited = wordList;

        unvisited.erase(beginWord);
        unvisited.erase(endWord);

        current.insert(beginWord);
        opposite.insert(endWord);
        bool found = findLadders(current, opposite, unvisited, children, true);
        
        if(found) {
            vector<string> path;
            dfs(beginWord, endWord, children, path, result);
        }
        return result;
    }

    bool findLadders(unordered_set<string>& current, unordered_set<string>& opposite, unordered_set<string>& unvisited, unordered_map<string, vector<string> >& children, bool forward) {
        if(current.empty()) return false; 
        if(current.size() > opposite.size()) return findLadders(opposite, current, unvisited, children, !forward); //reverse direction
        unordered_set<string> next;
        bool found = false;
        for(auto word : current) unvisited.erase(word); //first erase all words in current from unvisited (avoid double searching)
        for(auto word : current) {
            string newWord = word;
            for(auto it = newWord.begin(); it != newWord.end(); ++it) {
                char tmp = *it;
                for(*it = 'a'; (*it) <= 'z'; ++(*it)) {
                    if(*it == tmp) continue;
                    if(opposite.count(newWord)) { //found word in opposite search front
                        found = true;
                        if(forward) children[word].push_back(newWord);
                        else children[newWord].push_back(word);
                    } else if(unvisited.count(newWord)) { //belongs to wordList, and unvisited
                        next.insert(newWord);
                        if(forward) children[word].push_back(newWord);
                        else children[newWord].push_back(word);
                    }
                }
                *it = tmp; //revert
            }
        }
        
        if(found) return true; //stop here
        else return findLadders(next, opposite, unvisited, children, forward);
    }

    void dfs(const string& beginWord, const string& endWord, unordered_map<string, vector<string> >& children, vector<string>& path, vector<vector<string> >& result) {
        path.push_back(beginWord);
        if(beginWord == endWord) {
           result.push_back(path);
           path.pop_back();
           return;
        }
        for(auto it : children[beginWord]) {
            dfs(it, endWord, children, path, result);
        }
        path.pop_back();
    }
};

/**************************************************** 
 ***    128,Hard,Longest Consecutive Sequence 
 ****************************************************/

/*
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity. 
*/

/*
Solution 1. More elegant. Use a hash table for O(1) look-up of each number.
Then scan the array again. First check if element is in set, if not just continue (no need to search a previously erased element). For each entry, scan numbers to left and right to see if they are in the map, count total number of adjacent numbers. At the same time remove them to avoid future redundant search.
e.g. 0 1  3 4 5 6  8 9,
when 4 is found, scan and find 3 and 6, with count = 4, remove all elements from 3 to 6. so next time we see a 5, we won't count again.
*/

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> table;
        int n = nums.size();
        for(int i = 0; i < n; i++) {
            table.insert(nums[i]);
        }
        int max_count = 0;
        for (int i = 0; i < n; ++i) {
            int x = nums[i];
            if(table.count(x) == 0) continue;
            table.erase(x); //remove it
            int cnt = 1;
            while(table.count(--x)) { cnt++; table.erase(x); }
            x = nums[i];
            while(table.count(++x)) { cnt++; table.erase(x); }
            max_count = max(max_count, cnt);
        }
        return max_count;
    }
};

/*
Solution 2. use a map, storing the starting and ending position of each point.[ 2, 3, 4] : 2=>4, 4=>2, 3 does not matter.

For this to work under duplicated entries, we should not visit the same node again. Once it is in the map, do nothing. Otherwise it might mess up the result.

When inserting a new number, check its neighbors to see if there is any neighoring intervals. If there is an interval on the left, update the extreme points. Do the same for the right interval.
*/

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return n;
        int max_len = 0;
        unordered_map<int, int> dict;
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            int left = x, right = x;
            if(dict.count(x)) continue; //avoid revisiting
            dict[x] = x;
            if(dict.count(x-1)) {
               left = dict[x-1];
               dict[left] = x;
               dict[x] = left;
            }
            if(dict.count(x+1)) {
               right = dict[x+1];
               dict[left] = right;
               dict[right] = left;
            }
            max_len = max(right-left+1, max_len);
        }
        return max_len;
    }
};


/**************************************************** 
 ***    132,Hard,Palindrome Partitioning II 
 ****************************************************/

/*
Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut. 
*/

// Dynamic programming. Store 1-d array indicating the min-cut for s[0, i) prefix. 
// Update the minCuts for substrings as we check the strings.
// j = 0 is needed in this case.

class Solution {
public:
    int minCut(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        vector<int> minCuts(n+1, INT_MAX); //min-cuts for s[0, i)
        minCuts[0] = -1; // define minCut for empty string as -1 for later convenience
        for (int i = 0; i < n; ++i) { //check if s[i] is part of a palindrome substring
            //could s[i] be in the middle of odd-length palindrome?
            for (int j = 0; i >= j && i+j < n && s[i-j] == s[i+j]; ++j) //j = 0 is needed to init minCuts[i+1]
                minCuts[i+j+1] = min(minCuts[i+j+1], minCuts[i-j]+1);
            //could s[i] be in the middle of even-length palindrome?
            for (int j = 0; i >= j && i+j+1 < n && s[i-j] == s[i+j+1]; ++j)
                minCuts[i+j+2] = min(minCuts[i+j+2], minCuts[i-j]+1);
        }
        return minCuts[n];
    }
};


/**************************************************** 
 ***    135,Hard,Candy 
 ****************************************************/

/*
There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

    Each child must have at least one candy.
    Children with a higher rating get more candies than their neighbors.

What is the minimum candies you must give? 
*/

/*
Solution 1. Two passes, once from left to right, once reverse. Keep an array storing current candies assigned to each kid. If see a higher rating than previous, assign 1 more candy compared to previous, otherwise assign 1.
*/

class Solution {
public:
    int candy(vector<int>& ratings) {
        if(ratings.empty()) return 0;
        int n = ratings.size();
        if(n == 1) return 1;
        vector<int> candies(n, 1);
        int tot = 0;
        for(int i = 1; i < n; ++i) {
            if(ratings[i] > ratings[i-1])  candies[i] = candies[i-1] + 1;
        }
        tot += candies[n-1];
        for(int i = n-2; i >= 0; --i) {
            if(ratings[i] > ratings[i+1])  candies[i] = max(candies[i], candies[i+1] + 1);
            tot += candies[i];
        }
        return tot;
    }
};

/*
Solution 2. O(n) one pass and O(1) space. Keep a variable curr for candies assigned to current kid. Three cases:
1. If new kid has higher rating, increment curr, and add it to total.
2. If equal rating, give only one candy and add it to total.
3. If smaller, then use another pointer j to scan forward and find the streak of descending ratings. Then start assigning candies 1, 2, ... starting from end of streak to i. Position i is special in that we might need to increment its current assigned value to satisfy the right side.
rating:    2 5 8 6 4 2 1 2
candy:    1 2 3 4 3 2 1 2  = > 1 2 5 4 3 2 1.
                     i          j-1  j
rating:    2 5 8 6 7 8
candy:    1 2 3 2 1 2   = > unchanged.
                     i    j-1  j
Two ways to sum up the candies in the descending streak, one is decrement curr and add it to total until curr == 0. The other is to use formula for sums : 1+2+...+n , the first one turns out to be faster in the test examples.
*/

class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if(n <= 1) return n;
        int curr = 1, total = 1; //one candy to first kid
        int i = 1, j = 0;
        while(i < n) {
            if(ratings[i] == ratings[i-1]) {
                curr = 1; total += curr; i++;
            } else if(ratings[i] > ratings[i-1]) {
                curr += 1; total += curr; i++;
            } else { //a[i] < a[i-1]
                j = i+1;
                while(j < n && ratings[j] < ratings[j-1]) j++;
                //descending streak from i-1 to j-1 (candies 1, 2, ..., j-i, max(j-i+1, a[i-1]))
                //i should be maximum of j-i and a[i]
                total += max(j-i+1 - curr, 0); //give extra candies to a[i-1] if necessary
                curr = j-i;
                while(curr > 0) total += curr--;
                //total += (j-i+1)*(j-i)/2;
                curr = 1;
                i = j;
            }
        }
        return total;
    }
};

/*
Solution 3. An old solution similar to Solution 2 but unecessarily uses a stack

The idea is as follows: assign as few candies as possible. First assign 1 candy to the first kid, 
then go through the kid one by one. If we encounter kids in increasing rating value, we simply 
increment the candy number for each kid and we are done. But if we encounter kids in decreasing 
rating value, we need to fix previous candy values to avoid zero or negative candies to the current kid. 
Thus I use a stack to keep track of the kids with decreasing ratings, so that we can give more candies 
to them when the 2nd requirement is violated. I use a subroutine clearStack to count the actual number 
of candies required for these kids. For each kid, there are three cases:

1. current kid has higher rating than previous kid: in this case, we assign one more candy to this kid. 
Also pop all previous kids out (and count candies for them), and push current kid's candy number
2. current kid has equal rating to previous kid: we just assign 1 candy to this kid. Use the same stack operation as 1.
3. current kid has less rating to previous kid: we also assign only 1 candy to this kid temporarily, 
and push it to stack (to be fixed later)
I also use a sentinel in the end of ratings to trigger clearStack at the last element.

Time O(n), space O(n)
*/

class Solution {
public:
    int candy(vector<int>& ratings) {
        ratings.insert(ratings.end(), INT_MAX); //sentinel
        int n = ratings.size();
        if(n <= 1) return n;
        int sum(0), curr(0);
        stack<int> s;
        s.push(1); //candy for first kid
        for(int k = 1; k < n; ++k) {
            if(ratings[k] >= ratings[k-1]) { //larger than previous
                if(ratings[k] == ratings[k-1]) curr = 1;
                else curr = s.top()+1;
                sum += clearStack(s); //count all previous
                s.push(curr); //push current candy number in stack (not count yet)
            } else { //smaller than previous
                s.push(1); //just give one candy to this kid, not count yet
            }
        }

        return sum;
    }
    
    int clearStack(stack<int>& s) {
        int sum = 0;
        int curr(0), last(0);
        while(!s.empty()) {
            int curr = s.top(); s.pop();
            if(curr <= last) curr = last+1;
            sum += curr;
            last = curr;
        }
        return sum;
    }
};


/**************************************************** 
 ***    138,Hard,Copy List with Random Pointer 
 ****************************************************/

/*
A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list. 
*/

/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */

/// Solution 1: use a hash table storing mapping from old to new nodes. Two passes.
/// First copy the array label/next fields and use a look-up table to store the mapping between old node and new node
/// Then deal with random array. Go through the old array and use the mapped new node link as the random field of new array.

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(head == NULL) return head;
        RandomListNode *newhead = new RandomListNode(head->label);
        RandomListNode *p = head, *q = newhead;
        map<RandomListNode*, RandomListNode*> lookup;
        lookup[p] = q;
        while (p->next) {
            q->next = new RandomListNode(p->next->label);
            lookup[p->next] = q->next;
            p = p->next;
            q = q->next;
        }
        
        //now deal with the random pointer
        p = head;
        q = newhead;
        while(p) {
            q->random = lookup[p->random];
            p = p->next;
            q = q->next;
        }
        return newhead;
    }
};

/// Solution 2. still uses hash table, but one pass, deal with next and random pointers at the same time.

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(!head) return NULL;
        unordered_map<RandomListNode*, RandomListNode*> dict;
        RandomListNode* dummy = new RandomListNode(0);
        RandomListNode *p = head, *q = dummy;
        while(p) {
            if(dict.count(p) == 0) {
                q->next = dict[p] = new RandomListNode(p->label);
            } else q->next = dict[p];
            q = q->next;
            if(!p->random) q->random = NULL;
            else {
                if(dict.count(p->random) == 0) {
                    q->random = dict[p->random] = new RandomListNode(p->random->label);
                } else q->random = dict[p->random];
            }
            p = p->next; //move p to next
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};

/// Solution 3. Very elegant. 3 passes with O(1) space (no hash table). The trick is to insert new nodes right after old node. Set random pointer, and then extract new array from the combined list.

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(!head) return NULL;
        RandomListNode *p = head, *q = NULL;
        //First pass, for each old node insert a new node after p
        while(p) {
            RandomListNode* tmp = p->next;
            p->next = new RandomListNode(p->label);
            p->next->next = tmp;
            p = tmp;
        }
        //Second pass, set random pointer
        p = head;
        while(p) {
            if(!p->random) p->next->random = NULL;
            else p->next->random = p->random->next;
            p = p->next->next;
        }
        //Third pass, extract new list from the combined list
        p = head; q = p->next;
        head = q; //new head to be returned
        while(p) {
            p->next = q->next;
            if(q->next) q->next = q->next->next;
            p = p->next;
            q = q->next;
        }
        return head;
    }
};


/**************************************************** 
 ***    140,Hard,Word Break II 
 ****************************************************/

/*
Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"]. 
*/

//DP solution: use an array to store whether substring s[i .. end) is breakable.
//Then do a DFS, when checking the conditions, first check if breakable (guaranteed O(1)), and then whether the substring s[i, i+len) is in dictionary (amortize O(1)). 

// Avoid TLE, if string is not breakable at all, return.
// Trick: in if condition, first check breakable, then check wordDict.count() will cause program to run slightly faster, because array look-up is faster than hash table lookup.

class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        vector<string> result;
        if(s.empty() || wordDict.empty()) return result;
        int n = s.size();
        vector<bool> breakable(n+1, false); //whether s[i, n) is breakable?
        breakable[n] = true; //empty string breakable
        for(int i = n-1; i >= 0; --i) {
            for(int len = 1; len <= n-i; ++len) {
                if(breakable[i+len] && wordDict.count(s.substr(i, len))) {
                    breakable[i] = true;
                    break;
                }
            }
        }
	//if string s not breakable, just return (avoid TLE)
        if(!breakable[0]) return result;
        
        string tmp;
        dfs(s, 0, breakable, wordDict, tmp, result);
        return result;
    }
    //check s[k .. end)
    void dfs(string& s, int k, vector<bool>& breakable, unordered_set<string>& wordDict, string tmp, vector<string>& result) {
        int n = s.size();
        if(k == n) {
            result.push_back(tmp);
            return;
        }
        //s's length i substring starting at k
        for(int i = 1; k+i <= n; ++i) {
            string sub = s.substr(k, i);
            if(breakable[k+i] && wordDict.count(sub)) {
                if(tmp == "") dfs(s, k+i, breakable, wordDict, sub, result);
                else dfs(s, k+i, breakable, wordDict, tmp + " " + sub, result);
            }
        }
    }
/*
    // An alternative dfs function passing reference of partial solution tmp. Remember its end position, append new strings, and erase them 
    // using C++'s erase() function.
    void dfs(string& s, int k, vector<bool>& breakable, unordered_set<string>& wordDict, string& tmp, vector<string>& result) {
        int n = s.size();
        if(k == n) {
            result.push_back(tmp);
            return;
        }
        //s's length i substring starting at k
        int j = tmp.size(); //remember tmp's end position
        for(int i = 1; k+i <= n; ++i) {
            string sub = s.substr(k, i);
            if(breakable[k+i] && wordDict.count(sub)) {
                if(tmp == "") tmp = sub;
                else tmp += " " + sub;
                dfs(s, k+i, breakable, wordDict, tmp, result);
                tmp.erase(j); //revert back to original
            }
        }
    }
*/
};
	
// Solution 2. Dynamic programming, but store all the possible breaking points of each substring s[i, n). Checking each substring is breakable simply reduces to checking whether the array for possible breaking points is empty. For string s[i, n), check if s[i, j) is in dictionary and s[j, n) is breakable by dynamic programming.

class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        vector<string> result;
        if(s.empty() || wordDict.empty()) return result;
        int n = s.size();
        vector<vector<int> > breakpos(n+1); //breaking position of s[i, n)
        for(int i = n-1; i >= 0; --i) {
            for(int len = 1; len <= n-i; ++len) {
                if((len == n-i || !breakpos[i+len].empty()) && wordDict.count(s.substr(i, len))) {
                    breakpos[i].push_back(i+len);
                }
            }
        }
        if(breakpos[0].empty()) return result;
        
        string tmp;
        dfs(s, 0, breakpos, tmp, result);
        return result;
    }
    //check s[k .. end)
    void dfs(string& s, int k, vector<vector<int>>& breakpos, string tmp, vector<string>& result) {
        int n = s.size();
        if(k == n) {
            result.push_back(tmp);
            return;
        }
        //s's length i substring starting at k
        for(int j = 0; j < breakpos[k].size(); ++j) {
            int pos = breakpos[k][j];
            if(tmp == "") dfs(s, pos, breakpos, s.substr(k, pos-k), result);
            else dfs(s, pos, breakpos, tmp + " " + s.substr(k, pos-k), result);
        }
    }
};

// Solution 3. Recursive solution with top-down memoization DP. Fastest (4ms) solution.
// Store the possible break solutions for a string in a map (memoization). First search result in map, if not there, do real business.
// To avoid TLE, first check if the word s is breakable or not by examining all its substrings starting at i (ends at s.end()) and see if any belongs to dictionary. If none is in dictionary, then there's no solution.
// If there is solution, then we systematically break the string into 2 parts,with the first part length varying from 1 to n-1. Each time if first part is in dictionary, recursively call wordBreak for second part, and construct the solution for s from the solution of second part.
// Finally, before return, do not forget to write the result to dp table.

class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        //first search in memoization table
        if(dp.count(s)) return dp[s];
        
        vector<string> result;
        int i = 0, n = s.size();
        for(i = 0; i < n; ++i) { //check if s[i, n) is in dict
            if(wordDict.count(s.substr(i))) break;
        }
        if(i == n) return result; //no solution
        
        //now search substrings
        if(wordDict.count(s)) result.push_back(s); //whole string is solution
        for(int len = 1; len < n; ++len) {
            string str = s.substr(0, len);
            if(wordDict.count(str)) {
                vector<string> tmp = wordBreak(s.substr(len), wordDict);
                for(auto it : tmp) {
                    result.push_back(str + " " + it);
                }
            }
        }
        dp[s] = result;
        return result;
    }
    unordered_map<string, vector<string> > dp; //memoization
};


/**************************************************** 
 ***    145,Hard,Binary Tree Postorder Traversal 
 ****************************************************/

/*
Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [3,2,1].

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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        postorder(root, ret);
        return ret;
    }
    void postorder(TreeNode *root, vector<int>& ret) {
        if(!root) return;
        postorder(root->left, ret);
        postorder(root->right, ret);
        ret.push_back(root->val);
    }
};

// Iterative solution using a stack (and a tag for each node tracking how many times it has been pushed_to stack.
// Use pair instead of struct for simplicity.
// Slightly improved version. Avoid frequent pop and push operations, instead just update(increment) top's tag value.
// Typically each node will be checked three times, each time the value associated with it will be incremented.
// 1. The 1st time it is checked, push left child to stack if any
// 2. The 2nd time it is checked, push right child to stack if any
// 3. The 3rd time it is checked, we are done with the sub-trees so we can save the node to output and pop it out.

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        deque<pair<TreeNode*, int> > st; //stack
        st.push_back(make_pair(root, 0));
        TreeNode* node;
        while(!st.empty()) {
            int tag = ++st.back().second;
            node = st.back().first;
            if(tag == 1) {
                if(node->left) st.push_back(make_pair(node->left, 0));
            } else if(tag == 2) {
                if(node->right) st.push_back(make_pair(node->right, 0));
            } else {
                result.push_back(node->val);
                st.pop_back();
            }
        }
        return result;
    }
};

// Iterative solution without tag in each node, instead use a pre pointer pointing to the previous node visited, by checking (1) whether previous node is the nodes left or right child, and (2) whether left or right child exist, we determine what we do next.
// There are three cases typically:
// 1. 1st time a node is checked, pre does not equal either children (if any).
// 2. 2nd time a node is checked, we just visited left sub-tree, so pre == node->left
// 3. 3rd time a node is checked, we just visited right sub-tree, so pre == node->rights
// There are also cases where left and/or right child is empty.
// If left child exists and pre is not equal to either children, then we push
// For correct comparison, pre should be initialized as not a NULL value, so we can initialize it as root.

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        deque<TreeNode*> st;
        st.push_back(root);
        TreeNode *pre = root, *node = NULL;
        while(!st.empty()) {
            node = st.back();
            if(node->left && node->left != pre && node->right != pre) {
                st.push_back(node->left);
            } else if(node->right && node->right != pre) {
                st.push_back(node->right);
            } else {
                result.push_back(node->val);
                pre = node;
                st.pop_back();
            }
        }
        return result;
    }
};



/**************************************************** 
 ***    146,Hard,LRU Cache 
 ****************************************************/

/*
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item. 
*/

/*
 Use a double-linked list, and use a dummy head and tail.
 Maintain a count of elements and capiticy.
 When an element has been touched, move to end of list
 When inserting a new element, first check if reaching maximum capacity. If yes, first delete head element. Then append new element to tail.
 Also included proper delete functions when nodes are removed and in the destructor.
 Caveat:
  1. When using dummy head and tail, should create a new node, not doing this in the constructor:
   ListNode dum1(0), *head = &dum1
  It will cause failure in the set routine when head is referenced. This is because dum1 is a local variable in constructor, and outside this function it will be out-of-scope and later referencing will give segmentation fault error. The correct way is to use new to allocate space on the heap: ListNode *head = new ListNode(-1, 0);
  2. The ListNode should have two data entries, key and value. Value is obvious, key is also needed to find the entry in the map when the entry needs to be erased.
 
*/

class LRUCache{

public:
    struct ListNode {
        ListNode *prev, *next;
        int key, val;
        ListNode(int k, int v) : key(k), val(v), prev(NULL), next(NULL) {}
    };

    LRUCache(int capacity) {
        this->capacity = capacity;
        this->N = 0;
        //dummy head and tail
        head = new ListNode(-1, 0);
        tail = new ListNode(-1, 0);
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCache() {
        ListNode *node = head;
        while(node) {
            ListNode* tmp = node;
            node = node->next;
            delete tmp;
        }
    }

    int get(int key) {
        if(dict.count(key)) {
            ListNode* node = dict[key];
            removeFromList(node);
            appendToList(node);
            return node->val;
        } else return -1;       
    }
    
    void set(int key, int value) {
        if(dict.count(key)) { //found, just update
            ListNode* node = dict[key];
            node->val = value;
            removeFromList(node);
            appendToList(node);
        } else { //not found, insert
            ListNode *node = new ListNode(key, value);
            dict[key] = node;
            appendToList(node);
            N++;
            if(N > capacity) {
               node = head->next;
               removeFromList(node);
               dict.erase(node->key); //erase entry from map
               delete node;
               N--;
            }
        }
    }

private:
    void removeFromList(ListNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    void appendToList(ListNode* node) {
        node->prev = tail->prev;
        node->next = tail;
        tail->prev->next = node;
        tail->prev = node;
    }
    int capacity;
    int N;
    unordered_map<int, ListNode*> dict;
    ListNode *head, *tail;
};
    void appendToTail(ListNode* node) {
        node->prev = tail->prev;
        node->next = tail;
        node->prev->next = node;
        node->next->prev = node;
    }
    void deleteHead() {
        ListNode *tmp = head->next;
        st.erase(tmp->key);
        head->next = tmp->next;
        tmp->next->prev = head;
        delete tmp;
    }
};

/**************************************************** 
 ***    149,Hard,Max Points on a Line 
 ****************************************************/

/*
Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
*/

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */

/// O(n2) solution with hash table.
/// Iterate all points. For each point i, check all points after it (excluding itself). There are three cases:
/// 1. duplicate point as i, track count as n_dup.
/// 2. lying along same vertical line as point i, track count as n_ver
/// 3. lying on a line of a finite slope. maintain a map of slope and count. Track the maximum of counts of all slopes as max_line.
/// After scanning all other points, we have num_dup, num_ver, and max_line. Then the maximum number of points lying across i is: 1 + num_dup + max(max_line, num_ver), where 1 counts point i itself.
/// repeat for all points and update
/// Caveat: when calculating the slope from integer coordinates, convert the numerator to double!

class Solution {
public:
    int maxPoints(vector<Point>& points) {
        int n = points.size();
        if(n <= 2) return n;
        int result = 0;
        unordered_map<double, int> dict;
        for(int i = 0; i < n-1; ++i) { //no need to scan last point
            int num_dup = 0, num_ver = 0, max_line = 0; //# duplicates, # points on same vertical line, max # points on any line
            dict.clear();
            //check all the points from i+1 to n
            for(int j = i+1; j < n; ++j) {
                if(points[j].x == points[i].x) {
                    if(points[j].y == points[i].y) num_dup++; //same point
                    else num_ver++; //on same vertical line
                } else { //calculate slope
                    double slope = double(points[j].y - points[i].y) / (points[j].x - points[i].x);
                    max_line = max(max_line, ++dict[slope]);
                }
            }
            result = max(result, 1 + num_dup + max(max_line, num_ver));
        }
        return result;
    }
};


/// O(n3) solution
/// Check each pair (pi, pj) and count all points lying on the line determined by pi, pj (using colinear function).
// If encountered duplicates, count them as well

class Solution {
public:
    int maxPoints(vector<Point>& points) {
        int n = points.size();
        if(n <= 2) return n;
        int result = 0;
        for(int i = 0; i < n-1; ++i) {
            int num_dup = 1, num_col = 0;
            for(int j = i+1; j < n; ++j) {
                if(points[i].x == points[j].x && points[i].y == points[j].y) {
                    num_dup++;
                    continue;
                }
                num_col = 1; //count point[j]
                for(int k = j+1; k < n; ++k) {
                    if(colinear(points[i], points[j], points[k])) num_col ++;
                }
                result = max(result, num_dup + num_col);
            }
            result = max(result, num_dup); //deal with case where only exist duplicates, no colinear execution
        }
        return result;
    }
    
    bool colinear(Point& p, Point& q, Point& r){
        return (q.y - p.y)*(r.x - q.x) - (r.y - q.y)*(q.x - p.x) == 0;
    }
};


/**************************************************** 
 ***    154,Hard,Find Minimum in Rotated Sorted Array II 
 ****************************************************/

/*
    Follow up for "Find Minimum in Rotated Sorted Array":
    What if duplicates are allowed?

    Would this affect the run-time complexity? How and why?

Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

The array may contain duplicates.
*/

// General solution that also works for duplicated cases (see comments in problem 153)
// Compare mid with hi, when equals, hi-- (not lo++!)

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
 ***    158,Hard,Read N Characters Given Read4 II - Call multiple times 
 ****************************************************/

/*
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function may be called multiple times. 
*/

// Forward declaration of the read4 API.
int read4(char *buf);

// Since read can be called multiple times, we need to store the characters read but not copied to buf in one read call. There are two changes to simple read function:
// 1. in the end any leftover characters are pushed to the queue
// 2. in the beginning check if queue has leftovers, if yes copy to buffer. Has to handle cases where n is small than the number of leftovers.

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int once = 0, total = 0;
        //if there is anything left in residue, pop out.
        while(!q.empty() && n > 0) {
            *(buf++) = q.front(); q.pop_front();
            total ++;
            n--;
        }
        if(n == 0) return total; //finished
        
        while(n >= 4) {
            once = read4(buf);
            total += once;
            buf += once;
            if(once < 4) return total; //reached end of file
            n -= once;
        }
        if(n > 0) {
            once = read4(buf);
            buf += min(once, n); //move buffer position
            total += min(once, n);
            int leftover = once - n;
            for(int i = 0; i < leftover; ++i) { //has residue, push to queue
                q.push_back(*(buf+i));
            }
        }
        return total;
    }
    
private:
    deque<char> q;
};

/**************************************************** 
 ***    159,Hard,Longest Substring with At Most Two Distinct Characters 
 ****************************************************/

/*
Given a string, find the length of the longest substring T that contains at most 2 distinct characters.

For example, Given s = “eceba”,

T is "ece" which its length is 3. 
*/

// Solution: use a hash table to store the counts of each character, and record the starting index of substring. Do a one-time linear search.
// Also store the count of disctinct characters and update i properly (by checking individual count of each character)
// For each character, increment the individual counts. If newly added, increment count.
// When count > 2, remove leading characters in substring (increment istart), and decrement individual counts in table. If no such character
// occurs, decrement count.
// Since the input is a string, using index table instead of unordered_map leads to better performance.

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        vector<int> dict(256, 0);
        int n = s.size();
        int count = 0; //count of disctinct characters
        int istart = 0; //start of substring
        int max_len = 0; //max length of substring
        for(int i = 0; i < n; ++i) {
            dict[s[i]]++;
            if(dict[s[i]] == 1) count++; //new entry added
            while(count > 2) { //more than 2 disctinct characters, remove some characters in the front
                dict[s[istart]]--;
                if(dict[s[istart]] == 0) count--;
                istart++;
            }
            max_len = max(max_len, i-istart+1);
        }
        return max_len;
    }
};

// A faster version with shorter lines (but less readability)
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        vector<int> dict(256, 0);
        int n = s.size();
        int count = 0; //count of disctinct characters
        int istart = 0; //start of substring
        int max_len = 0; //max length of substring
        for(int i = 0; i < n; ++i) {
            if(++dict[s[i]] == 1) count++; //new entry added
            while(count > 2) { //more than 2 disctinct characters, remove some characters in the front
                if(--dict[s[istart++]] == 0) count--;
            }
            max_len = max(max_len, i-istart+1);
        }
        return max_len;
    }
};


/**************************************************** 
 ***    164,Hard,Maximum Gap 
 ****************************************************/

/*
Given an unsorted array, find the maximum difference between the successive elements in its sorted form.

Try to solve it in linear time/space.

Return 0 if the array contains less than 2 elements.

You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.
*/

// Solution using bucket sort.
/*
1. first find the maximum and minimum of the array
2. partition the numbers into n-1 buckets, based on the position in the [min, max] interval. Also put min, max to the buckets
3. According to pigeon-hole, at least one bucket will be empty. And the maximum difference will be straddling across these empty regions (because the legnth is larger than bucket interval, and the difference within a bucket is smaller than bucket interval).
4. Scan all buckets, calculate the difference straddling across all empty buckets, and return the maximum among all of them.

The trick to put max and min to buckets is to avoid array index bound checks (i < 0, i > nb-1). This ensures that the first and last bucket is always filled.

Caveats:
a. max should be the last bucket, should avoid the integer out-of-bounds error.
b. number of buckets should be 1 less of total number of points, so if min/max are included, it should be n-1 !
c. there can be multiple empty buckets, and they can be continuous! So need to keep track of left-most boundary of the continuous empty bucket set.
d. integer/double conversion when doing integer division to find bucket lengths!
e. span / n-1 is wrong, should be span /(n-1)
*/

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if(n < 2) return 0;
        if(n == 2) return abs(nums[0] - nums[1]);
        int minimum = INT_MAX, maximum = INT_MIN;
        for(int i = 0; i < n; ++i) {
            if(nums[i] > maximum) maximum = nums[i];
            if(nums[i] < minimum) minimum = nums[i];
        }
        int span = maximum - minimum;
        if(span == 0) return 0;
        //put the left n numbers into n+1 buckets, tracking the minimum and maximum in each bucket
        int nb = n+1; 
        double bucket_len = double(span) / nb;
        vector<pair<int, int> > buckets(nb, make_pair(-1, -1));
        for(int i = 0; i < n; ++i) {
            int ib = (nums[i] - minimum) / bucket_len;
            //put maximum in last bucket
            if(ib == nb) ib = nb-1;
            if(buckets[ib].first == -1) buckets[ib].first = buckets[ib].second = nums[i];
            else {
                if(nums[i] < buckets[ib].first) buckets[ib].first = nums[i];
                if(nums[i] > buckets[ib].second) buckets[ib].second = nums[i];
            }
        }
        //now scan all buckets and find all empty ones
        int max_diff = INT_MIN, diff = 0;
        int left = -1, right = -1; //left and right boundary of empty space
        for(int ib = 0; ib < nb; ++ib) {
            if(buckets[ib].first == -1) { //can't be first or last bucket
                if(left == -1) left = buckets[ib-1].second;
                right = buckets[ib+1].first;
            } else { //calculate previous
                max_diff = max(max_diff, right - left);
                left = right = -1;
            }
        }
        return max_diff;
    }
};

/**************************************************** 
 ***    174,Hard,Dungeon Game 
 ****************************************************/

/*
The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).

In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.

Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.

For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.
-2 (K) 	-3 	3
-5 	-10 	1
10 	30 	-5 (P)

Notes:

    The knight's health has no upper bound.
    Any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.
*/

/*
Standard dynamic programming. Start from end and scan backwards, calculate the minimum points required at each position.DP solution. Retrace back to top left.
As starting point, set the right and bottom neighbor of P's cell to 1.

  dp[i][j]  | dp[i][j+1]
  _ _ _ _ _ | _ _ _ _ _ _ 
            |
 dp[i+1][j] |  

dp[i][j] stores the minimum points required at position [i][j] in order to reach the princess. We can reach pos[i][j] in two ways, from position [i-1][j] and position [i][j-1], and we can go from the place requiring minimum points. The points required at dp[i-1][j] is simply dp[i][j] - dungeon[i][j], and at least 1, so we have:
dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1])-dungeon[i][j]).
At the boundary, i = m-1 or j = n-1, we replace min by only one of the two neighbors.
At the princess point, we have dp[m-1][n-1] = 1-dungeon[m-1][n-1].
We can use sentinel nodes at the boundary, where all the sentinel values are INT_MAX, but for dp[m-1][n-1] to fit in the formula, we can set dp[m][n-1] and dp[m-1][n] as 1.	

Another solution is to start scanning from top left, but we need to store to variables for each position: the maximum points required at start in order to reach here, and the remaining points at this position.
*/

class Solution {
public:
    int calculateMinimumHP(vector<vector<int> >& dungeon) {
        int m = dungeon.size(), n = dungeon[0].size();
        vector<vector<int> > minHP(m+1, vector<int>(n+1, INT_MAX));
        minHP[m-1][n] = minHP[m][n-1] = 1; //this is the trick!
        for (int i = m-1; i >= 0; i--) {
            for (int j = n-1; j >= 0; j--) {
                minHP[i][j] = max(1, min(minHP[i+1][j], minHP[i][j+1])-dungeon[i][j]);
            }
        }
        return minHP[0][0];
    }
};

/* Same idea as Solution 1 but space optimized */

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size(), n = dungeon[0].size();
        vector<int> dp(n, INT_MAX);
        dp[n-1] = max(1, 1-dungeon[m-1][n-1]);
        //for last row (i == m-1)
        for(int j = n-2; j >= 0; j--)
            dp[j] = max(1, dp[j+1]-dungeon[m-1][j]);

        for (int i = m-2; i >= 0; i--) {
            dp[n-1] = max(1, dp[n-1]-dungeon[i][n-1]);
            for (int j = n-2; j >= 0; j--) {
                dp[j] = max(1, min(dp[j], dp[j+1])-dungeon[i][j]);
            }
        }
        return dp[0];
    }
};



/**************************************************** 
 ***    188,Hard,Best Time to Buy and Sell Stock IV 
 ****************************************************/

/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/

/*
What is a transaction? Buy followed by sell. K transactions means a sequence of buy - sell - buy - sell - ... - buy - sell, where no two transations occur on the same date. If a sell and a buy fall on the same date, we can just merge them into one transaction.
So the key is to find non-overlapping intervals each of which has start and end corresponding to buy and sell dates.
Why non-overlapping? Because the problem requires sell before buy a new stock.
Profit is incurred only after selling a pre-purchased stock (e.g. at the end of opening interval)

Here is how to solve it with dynamic programming:
Let the max profit after day j, when performing up to kk transactions be maxProf[j][k]. It can be the maximum of the two scenarios:
1. No selling at day j, so we inherit the max profit after day j-1, maxProf[j-1][k]:
2. max profit after day jj when performing up to k-1 transactions, then buy stock at day jj, and sell at day j. The prior transactions can end at day jj, because in that case we can merge the sell/buy at jj, and instead sell at j, which in total is up to k-1 transactions, and thus also falls into the up to k transactions category. You can also make jj equal to j, and that is simply maxProf[j-1][k] (no transaction on day j). In this case, the max profit will be:
   max( maxProf[jj][k-1] + price[j] - price[jj] ) for all 0 <= jj <= j
 = price[j] + max (maxProf[jj][k-1] - price[jj]) for all 0 <= jj <= j

To avoid calculating the max for all jj's, we can keep a storage called tmpMax for the quantity max(maxProf[jj][k-1] - price[jj]) as j is incremented. So the DP relation can be expressed as:

maxProf[j][k] = max(maxProf[j-1][k], price[j] + tmpMax[j][k-1]),    j > 0 and k > 0
              = 0,   j = 0 or k = 0

tmpMax[j][k] = max(tmpMax[j-1][k], maxProf[j][k-1]-price[j]),  j > 0 and k > 0
             = max(tmpMax[j-1][k], -price[j]),    j > 0 and k = 0   // maxPro[0][-1] = 0
             = -price[0],   j = 0   // maxProf[0][k] = 0

We noticed that maxProf[0][k] and maxProf[j][0] are always zero, and tmpMax[0][k] = -price[0] for all k, so we can initialize the array and later do not iterate over j = 0 and k = 0.
*/

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        int result = 0;
        if(k >= n/2) {
            for(int i = 1; i < n; ++i) {
                result += max(0, prices[i] - prices[i-1]);
            }
            return result;
        }
        vector<vector<int> > maxProf(n, vector<int>(k+1, 0)); //maxProfit performing upto k transactions
        vector<vector<int> > tmpMax(n, vector<int>(k+1, 0)); //max of (maxProf[jj][k] - price[jj]) for all 0 <= jj <= j.

        for(int kk = 0; kk < k; ++kk) tmpMax[0][kk] = -prices[0];

        for(int j = 1; j < n; ++j) {
            tmpMax[j][0] = max(tmpMax[j-1][0], -prices[j]); //handle kk = 0 case
            for(int kk = 1; kk <= k; ++kk) {
                maxProf[j][kk] = max(maxProf[j-1][kk], prices[j] + tmpMax[j][kk-1]);
                tmpMax[j][kk] = max(tmpMax[j-1][kk], maxProf[j][kk]-prices[j]);
            }
        }
        return maxProf[n-1][k];
    }
};

/*
Space optimized solution: we noticed that maxProf[j][k] only requires values at j-1 and k-1, so we can replace the 2D array with 1D, by reducing the dimension for the day. We use the same array to track the maxProfit for kk transactions for the current day, and update it for the next day.
*/

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        int result = 0;
        if(k >= n/2) {
            for(int i = 1; i < n; ++i) {
                result += max(0, prices[i] - prices[i-1]);
            }
            return result;
        }
        vector<int> maxProf(k+1, 0); //maxProfit performing upto k transactions
        vector<int> tmpMax(k+1, -prices[0]); //max of (maxProf[jj][k] - price[jj]) for all 0 <= jj <= j.

        for(int j = 1; j < n; ++j) {
            tmpMax[0] = max(tmpMax[0], -prices[j]); //handle kk = 0 case
            for(int kk = 1; kk <= k; ++kk) {
                maxProf[kk] = max(maxProf[kk], prices[j] + tmpMax[kk-1]);
                tmpMax[kk] = max(tmpMax[kk], maxProf[kk]-prices[j]);
            }
        }
        return maxProf[k];
    }
}

/**************************************************** 
 ***    212,Hard,Word Search II 
 ****************************************************/

/*
Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

For example,
Given words = ["oath","pea","eat","rain"] and board =

[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]

Return ["eat","oath"].

Note:
You may assume that all inputs are consist of lowercase letters a-z.

click to show hint.

You would need to optimize your backtracking to pass the larger test. Could you stop backtracking earlier?

If the current candidate does not exist in all words' prefix, you could stop backtracking immediately. What kind of data structure could answer such query efficiently? Does a hash table work? Why or why not? How about a Trie? If you would like to learn how to implement a basic trie, please work on this problem: Implement Trie (Prefix Tree) first.
*/

/*
Use a Trie data-structure. 
 Perform dfs on the board, construct the string formed by the path, see if it is contained as prefix in the Trie, if not, then stop searching. This is the essense of using Trie to speed up search.
 Caveats:
1. in trie element removal, do not remove root.
2. need to avoid duplicated entries in the return array, solution 1 erases the found entries in the Trie, solution 2 implements a found() function to check if the solution is in the array or not.
3. When found a match, need to continue searching! Do not simply return!
*/

// Solution 1.
class Trie {
public:
    struct Node {
        bool isEnd;
        vector<Node*> link;
        Node() : isEnd(false) {
            link.resize(26, NULL);
        }
    };

    Trie() {
        head = new Node();
    }

    ~Trie() {
        eraseNode(head);
    }
    void insert(const string& s) {
        insertUtil(head, s, 0);
    }

    bool exist(const string& s) {
        Node *node = find(head, s, 0);
        return node != NULL && node->isEnd;
    }
    bool existPrefix(const string& s) {
        Node *node = find(head, s, 0);
        return node != NULL;
    }
    void erase(const string& s) {
        eraseUtil(head, s, 0);
    }
private:
    void insertUtil(Node* node, const string& s, int k) {
        if(k == s.size()) { node->isEnd = true; return; }
        int i = s[k] - 'a';
        if(node->link[i] == NULL) node->link[i] = new Node();
        insertUtil(node->link[i], s, k+1);
    }

    Node* eraseUtil(Node* node, const string& s, int k) {
        if(node == NULL) return NULL;
        if(k == s.size()) {
            node->isEnd = false;
        } else {
            int c = s[k] - 'a';
            node->link[c] = eraseUtil(node->link[c], s, k+1);
        }
        if(node != head && !hasLinks(node) && !node->isEnd) {
            delete node; //no nodes below it
            node = NULL;
        }
        return node;
    }
    bool hasLinks(Node* node) {
        if(node == NULL) return false;
        for(int i = 0; i < 26; ++i) 
            if(node->link[i]) return true;
        return false;
    }
    Node* find(Node* node, const string& s, int k) {
        if(node == NULL || k == s.size()) return node;
        int i = s[k] - 'a';
        return find(node->link[i], s, k+1);
    }
    void eraseNode(Node* node) {
        if(!node) return;
        for(int i = 0; i < 26; ++i) eraseNode(node->link[i]);
        delete node;
    }
    Node* head;
};


class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> result;
        if(board.empty() || board[0].empty()) return result;
        int m = board.size(), n = board[0].size();
        string tmp;
        for(auto it : words) t.insert(it);
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                dfs(board, i, j, tmp, result);
            }
        }
        return result;
    }

    void dfs(vector<vector<char>>& board, int i, int j, string& tmp, vector<string>& result) {
        int m = board.size(), n = board[0].size();
        if(i < 0 || i >= m || j < 0 || j >= n) return; //illegal position
        if(board[i][j] == '*') return; //visited
        char c = board[i][j];
        tmp = tmp + c;
        if(t.exist(tmp)) {
            result.push_back(tmp);
            t.erase(tmp);
        }
        board[i][j] = '*';
        if(t.existPrefix(tmp)) {
            dfs(board, i, j+1, tmp, result);
            dfs(board, i, j-1, tmp, result);
            dfs(board, i+1, j, tmp, result);
            dfs(board, i-1, j, tmp, result);
        }
        board[i][j] = c;
        tmp.pop_back();
    }
    Trie t;
};

// Solution 2.
class Trie {
public:
    struct Node {
        bool isKey;
        vector<Node*> links;
        Node() : isKey(false) {
            links.resize(26, NULL);
        }
    };

    Trie() {
        root = new Node();
    }

    ~Trie() {
        eraseNode(root);
    }
    void insert(const string& s) {
        insertUtil(root, s, 0);
    }

    bool exist(const string& s) {
        Node *node = find(root, s, 0);
        return node != NULL && node->isKey;
    }
    bool existPrefix(const string& s) {
        Node *node = find(root, s, 0);
        return node != NULL;
    }
    void erase(const string& s) {
        eraseUtil(root, s, 0);
    }
private:
    void insertUtil(Node* node, const string& s, int k) {
        if(k == s.size()) { node->isKey = true; return; }
        int i = s[k] - 'a';
        if(node->links[i] == NULL) node->links[i] = new Node();
        insertUtil(node->links[i], s, k+1);
    }

    Node* eraseUtil(Node* node, const string& s, int k) {
        if(node == NULL) return NULL;
        if(k == s.size()) {
            node->isKey = false;
        } else {
            int c = s[k] - 'a';
            node->links[c] = eraseUtil(node->links[c], s, k+1);
        }
        if(node != root && !hasLinks(node) && !node->isKey) {
            delete node; //no nodes below it
            node = NULL;
        }
        return node;
    }
    bool hasLinks(Node* node) {
        if(node == NULL) return false;
        for(int i = 0; i < 26; ++i) 
            if(node->links[i]) return true;
        return false;
    }
    Node* find(Node* node, const string& s, int k) {
        if(node == NULL || k == s.size()) return node;
        int i = s[k] - 'a';
        return find(node->links[i], s, k+1);
    }
    void eraseNode(Node* node) {
        if(!node) return;
        for(int i = 0; i < 26; ++i) eraseNode(node->links[i]);
        delete node;
    }
    Node* root;
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> result;
        if(board.empty() || board[0].empty()) return result;
        int m = board.size(), n = board[0].size();
        string tmp;
        for(auto it : words) t.insert(it);
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                dfs(board, i, j, tmp, result);
            }
        }
        return result;
    }

    void dfs(vector<vector<char>>& board, int i, int j, string& tmp, vector<string>& result) {
        int m = board.size(), n = board[0].size();
        if(i < 0 || i >= m || j < 0 || j >= n) return; //illegal position
        if(board[i][j] == '*') return; //visited
        char c = board[i][j];
        tmp = tmp + c;
        if(t.exist(tmp) && !found(result, tmp)) {
            result.push_back(tmp);
        }
        board[i][j] = '*';
        if(t.existPrefix(tmp)) {
            dfs(board, i, j+1, tmp, result);
            dfs(board, i, j-1, tmp, result);
            dfs(board, i+1, j, tmp, result);
            dfs(board, i-1, j, tmp, result);
        }
        board[i][j] = c;
        tmp.pop_back();
    }
    
    bool found(vector<string>& result, string& tmp) {
        for(auto it : result) {
            if(tmp == it) return true;
        }
        return false;
    }
    Trie t;
};



/**************************************************** 
 ***    214,Hard,Shortest Palindrome 
 ****************************************************/

/*
Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

For example:

Given "aacecaaa", return "aaacecaaa".

Given "abcd", return "dcbabcd".
*/

//Solution 1. O(n2) solution results in TLE.
class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        if(n <= 1) return s;
        int i = 0, j = 0;
        int max_len = 1; //max length palindrome substring s[0.. max_len-1]
        for(i = (n-1)/2; i >= 0; --i) { //search first half only
            //check even case: [i-j .. i i+1 .. i+j+1]
            for(j = 0; i-j >= 0 && s[i-j] == s[i+j+1]; ++j) ;
            if(j == i+1) { max_len = 2*j; break; }
            
            //check odd case: [i-j .. i .. i+j]
            for(j = 0; i - j >= 0 && s[i-j] == s[i+j]; ++j) ;
            if(j == i+1) { max_len = 2*j-1; break; }
        }
        string result;
        for(int k = n-1; k >= max_len; --k) {
            result.push_back(s[k]);
        }
        result += s;
        return result;
    }
};

/*
Solution 2. KMP algorithm. Text is reverse of s, pattern is s, search s in t, and find the last j position before exit. j is the length of the longest palindrome substring.
e.g.
s = aacecaaa
text    = aaacecaa
pattern = aacecaaa
after KMP, we end up with
    01234567
    aaacecaa
     aacecaaa
            j = 7, => lps = "aacecaa"
*/  

class Solution {
public:
    string shortestPalindrome(string s) {
       int n = s.size();
        if(n <= 1) return s;
        string t = s; //text to search, reverse of s
        reverse(t.begin(), t.end());
        //s is pattern
        vector<int> f(n+1, -1); //transfer function
        int k = -1;
        for(int j = 1; j <= n; ++j) {
            while(k >= 0 && s[k] != s[j-1]) k = f[k];
            f[j] = ++k;
        }
        //now start matching
        int i(0), j(0);
        while(i < n && j < n) {
            if(t[i] == s[j]) { i++; j++; } 
            else if(j == 0) i++;
            else j = f[j];
        }
        //previous j characters matched
        if(j == n) return s;
        else return t.substr(0, n-j) + s;
    }
};


/**************************************************** 
 ***    218,Hard,The Skyline Problem 
 ****************************************************/

/*
A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo (Figure A), write a program to output the skyline formed by these buildings collectively (Figure B).
Buildings Skyline Contour

The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi], where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively, and Hi is its height. It is guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX, and Ri - Li > 0. You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

For instance, the dimensions of all buildings in Figure A are recorded as: [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .

The output is a list of "key points" (red dots in Figure B) in the format of [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline. A key point is the left endpoint of a horizontal line segment. Note that the last key point, where the rightmost building ends, is merely used to mark the termination of the skyline, and always has zero height. Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.

For instance, the skyline in Figure B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].

Notes:

    The number of buildings in any input list is guaranteed to be in the range [0, 10000].
    The input list is already sorted in ascending order by the left x position Li.
    The output list must be sorted by the x position.
    There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]
*/

// divide and conquer, similar to merge sort.
// The crux is in the merge routine. For a new point, we compare it with the last height of the other array. The merge is designed so no duplicates of x coords will appear. But duplicates for the heights will appear, so need to remove them in the end.

class Solution {
public:
    typedef pair<int, int> Point;

    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        vector<Point> skyline;
        int n = buildings.size();
        getSkyline(buildings, 0, n-1, skyline);
        return skyline;
    }
    void getSkyline(const vector<vector<int>>& buildings, int lo, int hi, vector<Point>& skyline) {
        if(lo > hi) return;
        if(lo == hi) {
            skyline.push_back(make_pair(buildings[lo][0], buildings[lo][2])); //left, height
            skyline.push_back(make_pair(buildings[lo][1], 0)); //right, 0
            return;
        }
        //now divide and conquer
        int mid = lo + (hi-lo)/2;
        vector<Point> left, right;
        getSkyline(buildings, lo, mid, left);
        getSkyline(buildings, mid+1, hi, right);
        merge(left, right, skyline);
    }
    void merge(vector<Point>& v1, vector<Point>& v2, vector<Point>& v) {
        int i = 0, j = 0, m = v1.size(), n = v2.size();
        int last_y1 = 0, last_y2 = 0;
        while(i < m || j < n) {
            int x1 = (i < m) ? v1[i].first : INT_MAX;
            int y1 = (i < m) ? v1[i].second : 0;
            int x2 = (j < n) ? v2[j].first : INT_MAX;
            int y2 = (j < n) ? v2[j].second : 0;
            if(x1 == x2) {
                v.push_back(make_pair(x1, max(y1, y2)));
                last_y1 = y1; last_y2 = y2;
                i++; j++;
            } else if(x1 < x2) {
                v.push_back(make_pair(x1, max(y1, last_y2)));
                last_y1 = y1;
                i++;
            } else {
                v.push_back(make_pair(x2, max(y2, last_y1)));
                last_y2 = y2;
                j++;
            }
        }
        //remove duplicates
        int l = 0;
        for(int k = 0; k < v.size(); ++k) {
            if(k == 0 || v[k].second != v[k-1].second) {
                v[l++] = v[k];
            }
        }
        v.resize(l);
    }
};


// An old solution

// divide and conquer, similar to merge sort.
// two caveats:
// 1. avoid duplicated heights ([1,4], [2, 4] is not allowed)
// 2. avoid duplicated coordinates, e.g. two buildings both span [1, 3] but with different heights, need to check if the current strip has same coordinate as previous
class Solution {
public:
    typedef pair<int, int> Strip;

    vector<pair<int, int> > getSkyline(vector<vector<int> >& buildings) {
        return getSkylineUtil(buildings, 0, buildings.size()-1);
    }

    //get strips for buildings[lo .. hi]
    vector<Strip> getSkylineUtil(const vector<vector<int> >& buildings, int lo, int hi) {
        vector<Strip> ret;
        if (lo > hi) return ret;
        if (lo == hi) {  //only one building
            ret.resize(2);
            ret[0] = make_pair(buildings[lo][0], buildings[lo][2]);
            ret[1] = make_pair(buildings[lo][1], 0);
            return ret;
        }
        int mid = (lo + hi) / 2;
        const vector<Strip>& left  = getSkylineUtil(buildings, lo,   mid);
        const vector<Strip>& right = getSkylineUtil(buildings, mid+1, hi);
        return merge(left, right);
    }
    
    //merge two strips
    vector<Strip> merge(const vector<Strip>& a, const vector<Strip>& b) {
        vector<Strip> ret;
        size_t m = a.size(), n = b.size();
        int side(0);
        int ha(0), hb(0), h(-1), x(INT_MIN), newh(0), newx(0);
        for(size_t i = 0, j = 0; i < m || j < n; ) {
            if(i == m) side = 1; //right
            else if(j == n) side = 0; //left
            else side = (a[i].first < b[j].first) ? 0 : 1;

            if (side == 0) { //picked a strip from a
                newx = a[i].first; 
                ha = a[i].second;  //update ha
                i++;
            } else {
                newx = b[j].first; 
                hb = b[j].second; //update hb
                j++;
            }
            newh = max(ha, hb);
            if (h != newh) { // avoid duplicated height
                if(newx == x) ret.back() = make_pair(newx, newh); //update last entry, avoid duplicated x
                else ret.push_back(make_pair(newx, newh)); //append new entry
                h = newh; //update h
                x = newx; //update x
            }
        }
        return ret;
    }
};

/**************************************************** 
 ***    239,Hard,Sliding Window Maximum 
 ****************************************************/

/*
Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

Therefore, return the max sliding window as [3,3,5,5,6,7].

Note:
You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for non-empty array.
*/

// A O(k*n) solution.
// For each new number, look further and predict the maximum for the next k steps

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
       int n = nums.size();
       vector<int> ret;
       if(k == 0 || n < k) return ret;
       int m = n-k+1;
       ret.resize(m, INT_MIN);
       //predict the possible maximums according to nums[i]
       for(int i = 0; i < n; ++i) {
          for(int j = max(0, i-k+1); j <= min(i, m-1); ++j) {
             ret[j] = max(ret[j], nums[i]);
          }
       }
       return ret;
    }
};
/*
Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

Therefore, return the max sliding window as [3,3,5,5,6,7].

Note:
You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for non-empty array.
*/

// Linear time (one pass) solution
// Maintain a doubly-ended queue. add newly seen numbers to end of queue. Several operations:
// 1. when we see a new number, pop all the smaller numbers from the back of queue, and then insert the new value. (the new number makes these smaller numbers values stale)
// 2. also check if front of queque is out of the sliding window, if yes then remove front.
// 3. the maximum is simply the front element of queue.

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        int n = nums.size();
        if(n == 0 || k == 0 || n < k) return result;
        result.resize(n-k+1);
        deque<int> q; //position
        for(int i = 0; i < n; ++i) {
            int val = nums[i];
            if(!q.empty() && i-q.front() == k) q.pop_front();
            while(!q.empty() && nums[q.back()] <= val) {
                q.pop_back();
            }
            q.push_back(i);
            if(i >= k-1) result[i-k+1] = nums[q.front()];
        }
        return result;
    }
};

/**************************************************** 
 ***    248,Hard,Strobogrammatic Number III 
 ****************************************************/

/*
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high.

For example,
Given low = "50", high = "100", return 3. Because 69, 88, and 96 are three strobogrammatic numbers.

Note:
Because the range might be a large number, the low and high numbers are represented as string. 
*/

/*
Idea is to find the number of strobogrammatic strings between [0, num] for a given number num. Then the count between range [low, high] is basically the difference between two runs, one for [0, high] and one for [0, low]. One corner case here is that if low is strobogrammatic, we need to exclude it from the count.

maintain a mapping from a number to its strobogrammatic counterparts, e.g. 0 => 0, 1 => 1, 6 => 9, 8 => 8, 9 => 6.

helper functions:
1. isStrobogrammatic(string num): check whether a string is strobogramatic or not. 
2. stroboLengthN(int n): return number of all strobogrammatic numbers of given length n (including leading zeros). 
3. stroboBelow(int v, int d): for a given 1 or 2 digit number v, return number of strobogrammatic numbers <= v that also has 1 or 2 digits, including numbers with leading zeros (e.g. "0", or "00").
4. sameLengthBelow(string str, bool countZero): a recursive function to find the number of strobogrammatic numbers <= str and has the same length as str. If countZero is set as true, we include numbers with leading zeros, e.g. 0880 is counted for sameLengthBelow(1981, true).

For a number of length n represented by num, the strobogrammatic numbers between [0, num] are:
1. Strings with length less than n (obtained by a loop calling stroboLenghtN).
2. Strings with length n, and most significant digit (MSD) < num[0], and digits 1 to n-2 can be any strobogrammatic strings of length n-2. This part can be calculated by multiplying results from stroboBelow(int v, int d) and stroboLengthN(n-2).
3. If num[0] is 0, 1, 6, 8, 9. Then we can also have strings with length n, and MSD = num[0]. The number of such strings can be calculated by recursively calling stroboBelow(str) for the substring num[1 .. n-1].
3'. In 3 we might be overcounting one number, e.g. when num = 98485, then we overcounted 98486, we need to decrement count. This only happens when num[n-1] is smaller than the counterpart of num[0], and num[1 .. n-1] is strobogrammatic number. 

corner cases:

1. low is equal to hi, return whether high is a strobogrammatic string.
2. low is large than hi, then return 0. Use a function to test if low is larger than hi.
*/

class Solution {
public:
    Solution() {
        mapping = {0, 1, -1, -1, -1, -1, 9, -1, 8, 6};
    }
    int strobogrammaticInRange(string low, string high) {
        if(low == high) return isStrobogrammatic(high);
        if(isLarger(low, high)) return 0;
        int count1 = countBelow(low);
        int count2 = countBelow(high);
        if(isStrobogrammatic(low)) count1--;
        return count2 - count1;
    }
    bool isLarger(const string& a, const string& b) {
        int m = a.size(), n = b.size();
        if(m != n) return m > n;
        for(int i = 0; i < m; ++i) {
            if(a[i] > b[i]) return true;
            if(a[i] < b[i]) return false;
        }
        return false; //equal, false
    }

    //count strobo numbers from 0 to num including num
    int countBelow(string num) {
        int count = 1; //"0"
        for(int n = 1; n < num.size(); ++n) {
            int tmp = stroboLengthN(n);
            if(n == 1) count += tmp-1; //not include zero 
            else count += tmp-tmp/5; //not include zero
        }
        count += sameLengthStroboBelow(num, false);
        return count;
    }
    //count strobogrammatic numbers <= str, with the same length as str (starting with "0" or "1" depending on countZero)
    int sameLengthStroboBelow(string str, bool countZero) {
	    int n = str.size();
        int count = 0;
        if(n == 1) {
            int v = str[0]-'0';
            count = stroboBelow(v, 1);
            if(!countZero) count --;
        } else if (n == 2) {
            int v = (str[0]-'0')*10 + (str[1]-'0');
            count = stroboBelow(v, 2);
            if(!countZero) count --;
        } else {
            int v1 = (str[0]-'0'), v2 = (str[n-1]-'0');
            //count strobo with first digit being 1 .. v1-1.
            if(v1 > 0) {
                int tmp = stroboBelow(v1*10-1, 2);
                if(!countZero) tmp--;
                count += tmp*stroboLengthN(n-2); 
            }
            string sub = str.substr(1, n-2);
            if(mapping[v1] >= 0) count += sameLengthStroboBelow(sub, true);
            if(v2 < mapping[v1] && isStrobogrammatic(sub)) count--; //avoid overcounting
        }
        return count;
    }

    // number of strobos <= v with d digits (including "0" or "00").
    // v is a number between 0-9 (when d = 1) or 0-99 (when d = 2).
    // 1d strobos: "0", "1", "8"
    // 2d strobos: "00", "11", "69", "88", "96"
    int stroboBelow(int v, int d) {
       int count = 0;
       if(d == 1) {
           if(v < 1) count = 1;
           else if(v < 8) count = 2;
           else count = 3;
       } else if(d == 2) {
           if(v < 11) count = 1;
           else if(v < 69) count = 2; //11
           else if(v < 88) count = 3;
           else if(v < 96) count = 4;
           else count = 5;     
       }
       return count;
    }

    //count strobo for digit n (can have leading zeros)
    int stroboLengthN(int n) {
        if(n == 0) return 0;
        int count = (n % 2 == 1) ? 3 : 5;
        while(n > 2) {
            n -= 2;
            count *= 5;  
        }
        return count;
    }

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
    vector<int> mapping;
};

/**************************************************** 
 ***    265,Hard,Paint House II 
 ****************************************************/

/*
There are a row of n houses, each house can be painted with one of the k colors. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x k cost matrix. For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost of painting house 1 with color 2, and so on... Find the minimum cost to paint all houses.

Note:
All costs are positive integers.

Follow up:
Could you solve it in O(nk) runtime?
*/

/* Dynamic programming. Similar to 256 paint house where k=3. To make it O(nk), we need to find the minimum among k-1 colors out of k colors. To do this in O(k) time, notice that the minimum among k-1 colors has n cases, n-1 of them end up with the minimum elements of the k colors, and the other one end up with the second minimum element. So we just keep track of the minimum and second minimum element of the k colors.
*/

class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        if(costs.empty() || costs[0].empty()) return 0;
        int n = costs.size();
        int ncolor = costs[0].size();
        vector<int> cost_so_far(ncolor, 0);
        vector<int> tmp(ncolor, 0);
        int min_cost = INT_MAX, second_min_cost = INT_MAX;
        int min_cost_color = 0, second_min_cost_color = 0;
        for(int i = 0; i < n; ++i) {
            for(int k = 0; k < ncolor; ++k) {
                if(min_cost_color == k) tmp[k] = cost_so_far[second_min_cost_color] + costs[i][k];
                else tmp[k] = cost_so_far[min_cost_color] + costs[i][k];
            }
            //update min and second_min
            min_cost = INT_MAX, second_min_cost = INT_MAX;
            min_cost_color = 0, second_min_cost_color = 0;
            for(int k = 0; k < ncolor; ++k) {
                if(tmp[k] < min_cost) { 
                    second_min_cost = min_cost; second_min_cost_color = min_cost_color;
                    min_cost = tmp[k]; min_cost_color = k; 
                } else if(tmp[k] < second_min_cost) { 
                    second_min_cost = tmp[k]; second_min_cost_color = k;
                }
            }
            cost_so_far.swap(tmp);
        }
        return min_cost;        
    }
};

/**************************************************** 
 ***    269,Hard,Alien Dictionary 
 ****************************************************/

/*
There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you. You receive a list of words from the dictionary, where words are sorted lexicographically by the rules of this new language. Derive the order of letters in this language.

For example,
Given the following words in dictionary,

[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]

The correct order is: "wertf".

Note:

    You may assume all letters are in lowercase.
    If the order is invalid, return an empty string.
    There may be multiple valid order of letters, return any one of them is fine.
*/

// Build a graph containing vertices corresponding letters 'a' to 'z'. Scan the dictionary twice. First time add vertices for seen characters. Second time compare two adjacent strings and add an edge for the pair of characters. 
// Then do a topological sort, and return the result as string. During the topo-sort, also detect whether there is a cycle. If detected, immediately return to calling function which in turn returns "" to main function.
// Use the 3-color scheme in CLRS (white, grey, black) to do topo-sort and cycle detection in one pass.

class Graph {
public:
    Graph()  {
        vertices.resize(26, false);
        adj.resize(26);
        color.resize(26, 0); //0: unvisited, 1: on stack, 2: finished
	hasCycle = false;
    }
    void addVertex(char c) {
        vertices[c-'a'] = true; 
    }
    void addEdge(char c1, char c2) {
        adj[c1-'a'].push_back(c2-'a');
    }

    string topoSort() {
        string s;
        for(int v = 0; v < 26; ++v) {
            if(vertices[v] && color[v] == 0) {
                dfs(v, s);
                if(hasCycle) return "";
            }
        }
        reverse(s.begin(), s.end());
        return s;
    }

    void dfs(int v, string& s) {
        if(hasCycle) return;
        color[v] = 1;
        for(auto w : adj[v]) {
            if(color[w] == 0) dfs(w, s);
            else if(color[w] == 1) { hasCycle = true; return; }
        }
        color[v] = 2;
        //after we are done with v, push back to s.
        s.push_back(v+'a');
    }

private:
    vector<bool> vertices; //vertices (26)
    vector<vector<int> > adj; //adjacency lists 
    vector<int> color; // whether vertices are on stack
    bool hasCycle;
};

class Solution {
public:
    string alienOrder(vector<string>& words) {
        if(words.empty()) return "";
        int n = words.size();
        Graph g;
        for(int i = 0; i < n; ++i)
            for(char c : words[i])
                 g.addVertex(c);

        for(int i = 1; i < n; ++i) {
           int jmax = min(words[i].size(), words[i-1].size());
           for(int j = 0; j < jmax; ++j) {
               if(words[i-1][j] != words[i][j]) { g.addEdge(words[i-1][j], words[i][j]); break;}
           }
        }
        return g.topoSort();
    }
};


/**************************************************** 
 ***    272,Hard,Closest Binary Search Tree Value II 
 ****************************************************/

/*
Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.

Note:

    Given target value is a floating point.
    You may assume k is always valid, that is: k ≤ total nodes.
    You are guaranteed to have only one unique set of k values in the BST that are closest to the target.

Follow up:
Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?

Hint:

    Consider implement these two helper functions:
        getPredecessor(N), which returns the next smaller node to N.
        getSuccessor(N), which returns the next larger node to N.
    Try to assume that each node has a parent pointer, it makes the problem much easier.
    Without parent pointer we just need to keep track of the path from the root to the current node using a stack.
    You would need two stacks to track the path in finding predecessor and successor node separately.
*/

// First build the stack storing search path for predecessor and successor of target. For predecessor, only insert into stack nodes smaller than target during search, and likewise for successor. nodes equal to the target will be inserted to predecessor (to break tie and avoid duplicated results returned). Then implement the nextSucc and nextPred function to return the next larger/smaller value to target, by poppping/pushing elements from/to stack. Do a merging routine similar to the merge sort to establish the order of k values.

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
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        vector<int> result(k, 0);
        if(!root) return result;
        //build stack for predecessor path
        TreeNode *node = root;
        while(node) {
            if(target < node->val) node = node->left;
            else {
                pred.push(node);
                node = node->right;
            } 
        }
        //build stack for successor path
        node = root;
        while(node) {
            if(target >= node->val) node = node->right;
            else {
                succ.push(node);
                node = node->left;
            }
        }

        TreeNode *p = nextPred(), *s = nextSucc();
        for(int i = 0; i < k; ++i) {
           if(!p) { result[i] =  s->val; s = nextSucc(); } 
           else if(!s) { result[i] =  p->val; p = nextPred(); }
           else if(target - p->val > s->val - target) { result[i] =  s->val; s = nextSucc(); } 
           else { result[i] =  p->val; p = nextPred(); }
        }
        return result;
    }

    TreeNode* nextPred() {
        if(pred.empty()) return NULL;
        TreeNode* node = pred.top(); pred.pop();
        TreeNode *tmp = node->left;
        while(tmp) {
            pred.push(tmp); 
            tmp = tmp->right;
        }
        return node;
    }

    TreeNode* nextSucc() {
        if(succ.empty()) return NULL;
        TreeNode* node = succ.top(); succ.pop();
        TreeNode *tmp = node->right;
        while(tmp) {
            succ.push(tmp); 
            tmp = tmp->left;
        }
        return node;
    }

    stack<TreeNode*> pred, succ; //stack for predecessor and successor paths
};


/**************************************************** 
 ***    282,Hard,Expression Add Operators 
 ****************************************************/

/*
Given a string that contains only digits 0-9 and a target value, return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.

Examples:

"123", 6 -> ["1+2+3", "1*2*3"] 
"232", 8 -> ["2*3+2", "2+3*2"]
"105", 5 -> ["1*0+5","10-5"]
"00", 0 -> ["0+0", "0-0", "0*0"]
"3456237490", 9191 -> []
*/

/*
Standard DFS solution, several caveats:

1. avoid multiple digits starting from 0, e.g. 03
2. consider precedence of * than + or -.
2+3 ? 4
 will depend on what ? is:
if ? is +/-, then => 5 ? 4
if ? is *, then => 2 + 12

So, at each start of string, we store the previous two numbers and operator. Say 12333, we decided 1 + 2 and is exploring 333.
Then we scan the rest of numbers, and extract one number out (e.g.  we try +/-/* of 3, 33, 333 etc)
when the next operator to try is +/-, then we can safely calculate the previous result, in this case: 3 +/-  3, 33, 333
when the next operator is *, then we need to evaluate * first, in this case we have
1 + 6,  1 + 66, 1 + 666 ...

so we write our dfs in the following format
dfs(num, long i, long a, long b, char op, string partial, vector<string>& result)

Also need to consider how to start, we use "0+0" as starting point. if i == 0, we only try + with the rest of string.
*/

class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> result;
        string partial; //partial solution
        dfs(num, 0, 0, 0, '+', target, partial, result);
        return result;
    }
    long eval(long a, long b, char op) {
        if(op == '+') return a+b;
        else if(op == '-') return a-b;
        else if(op == '*') return a*b;
        else return 0;
    }
    // a op b ?? num[i, n)
    void dfs(const string& num, int i, long a, long b, char op, long target, string& partial, vector<string>& result) {
        int n = num.size();
        if(i == n && eval(a, b, op) == target) {
            result.push_back(partial); return;
        } 
        long number = 0;
        int size = partial.size();
        if(i != 0) partial += '+'; //append an operator
        int jmax = (num[i] == '0') ? i+1 : n;
        for(int j = i; j < jmax; ++j) {
            number = number*10 + (num[j] - '0'); //number from num[i, j]
            partial += num[j];
            if(i == 0) {
                dfs(num, j+1, 0, number, '+', target, partial, result); //starting point, only try '+'
            } else {  
                 long tmpval = eval(a, b, op);
                 partial[size] = '+';
                 dfs(num, j+1, tmpval, number, '+', target, partial, result);
                 partial[size] = '-';
                 dfs(num, j+1, tmpval, number, '-', target, partial, result);
                 partial[size] = '*';
                 dfs(num, j+1, a, b*number, op, target, partial, result); //op can only be '+' or '-', has lower precedence than *
            }
        }
        partial.resize(size); //reset tmp value
    }
};

/*
We further notice that op can never be '*'.Another solution as in the forum uses this fact, and changes sign of b when '-' is chosen. However, this results in slower code for some reason.
*/

class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> result;
        string partial; //partial solution
        dfs(num, 0, 0, 0, target, partial, result);
        return result;
    }

    // a op b ?? num[i, n)
    void dfs(const string& num, int i, long a, long b, long target, string& partial, vector<string>& result) {
        int n = num.size();
        if(i == n && a+b == target) {
            result.push_back(partial); return;
        } 
        long number = 0;
        int size = partial.size();
        if(i != 0) partial += '+'; //append an operator
        int jmax = (num[i] == '0') ? i+1 : n;
        for(int j = i; j < jmax; ++j) {
            number = number*10 + (num[j] - '0'); //number from num[i, j]
            partial += num[j];
            if(i == 0) {
                dfs(num, j+1, 0, number, target, partial, result);
            } else {  
                 partial[size] = '+';
                 dfs(num, j+1, a+b, number, target, partial, result);
                 partial[size] = '-';
                 dfs(num, j+1, a+b, -number, target, partial, result);
                 partial[size] = '*';
                 dfs(num, j+1, a, b*number, target, partial, result); //op can only be '+' or '-', has lower precedence than *
            }
        }
        partial.resize(size); //reset tmp value
    }
};


/**************************************************** 
 ***    287,Hard,Find the Duplicate Number 
 ****************************************************/

/*
Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.

Note:

    You must not modify the array (assume the array is read only).
    You must use only constant, O(1) extra space.
    Your runtime complexity should be less than O(n2).
    There is only one duplicate number in the array, but it could be repeated more than once.
*/

/*
Recursive solution.  O(nlgn) time.
Use a helper function to find duplicates in nums array in interval [lo, hi], given that the num array has more than hi-lo+1 elements lying in [lo, hi] (pigeon hole principle).
For given lo and hi, we let mid = (lo+hi)/2. We count the # elements <= mid (denoted as smaller), and # elements > mid (denoted as larger). Two cases:
1. [lo, hi] contains even number of integers. If no duplicates, we should find # integers <= mid equal to # integers > mid.
e.g. [2, 7], mid = 4, thus smaller = #[2,3,4] = 3, larger = #[5,6,7] = 3.
If duplicate <= mid, thus we have smaller > larger, otherwise smaller < larger
2. [lo, hi] contains odd number of integers. If no duplicates, we should find # integers <= mid one more than # integers > mid.
e.g. [2, 8], mid = 5, thus smaller = #[2,3,4,5] = 4, larger = #[6,7,8] = 3.
If duplicate <= mid, thus we have smaller > larger, otherwise smaller <= larger
Thus we have come up with the recursive formula:
 - smaller > larger => check again for interval [lo, mid]
 - smaller < larger => check again for interval [mid+1, hi].
Repeat until lo == hi, where we know that duplicate is of course lo (the only possible choice between [lo, hi]).
*/

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        if(nums.empty()) return -1;
        int n = nums.size();
        return findDuplicateHelper(nums, 1, n-1);
    }
    int findDuplicateHelper(vector<int>& nums, int lo, int hi) {
        if(lo > hi) return -1;
        if(lo == hi) return lo;
        int n = nums.size();
        int mid = lo + (hi-lo)/2;
        int small = 0, large = 0;
        for(int i = 0; i < n; ++i) {
            if(nums[i] < lo || nums[i] > hi) continue; //ignore elements out of range [lo, hi]
            if(nums[i] <= mid) small++;
            else large++;
        }
        if(small > large) return findDuplicateHelper(nums, lo, mid);
        else return findDuplicateHelper(nums, mid+1, hi);
    }
};

// Solution 2. Same ideas as 1. Iterative solution.  O(nlgn) time.

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        if(nums.empty()) return -1;
        int n = nums.size();
        int lo = 1, hi = n-1;
        while(lo < hi) {
            int mid = lo + (hi-lo)/2;
            int small = 0, large = 0;
            for(auto it : nums) {
                if(it < lo || it > hi) continue; //ignore elements out of range [lo, hi]
                if(it <= mid) small++;
                else large++;                
            }
            if(small > large) hi = mid;
            else lo = mid+1;
        }
        return lo;
    }
};

/*
Solution 3. Another binary search solution. O(nlgn) time.
For each number i in [1 .. n-1], count number of elements smaller or equal than i, denoted as p[i]. What will we get?
If no duplicate, e.g. [1,2,3,4]. then p[i] = i, for i = 1,.. 4. But if there is a duplicate, e.g. [1,2,2,3,4], we have 
p[1] = 1, p[2] = 3, p[3] = 4, p[4] = 5. p[i] becomes larger than i starting from the duplicated number. Since we only have one unique duplicated number, this observation always holds. Thus we can use binary search to determine i. 
Initially lo = 1, hi = n-1, and mid = (lo+hi)/2. Scan whole array and count number of elements <= mid. if count > mid, then we know that duplicate lies in [lo, mid], so we make hi = mid. Otherwise, we know that we haven't encountered the duplicate yet, and duplicate lies in [mid+1, hi], so we make lo = mid+1. Break when lo == hi, and we return lo.
*/

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        if(nums.empty()) return -1;
        int n = nums.size();
        int lo = 1, hi = n-1;
        while(lo < hi) {
            int mid = lo + (hi-lo)/2;
            int count = 0;
            for(int i = 0; i < n; ++i) {
                if(nums[i] <= mid) count++;
            }
            if(count > mid) hi = mid;
            else lo = mid+1;
        }
        return lo;
    }
};

// Solution 4. Smart solution using cycle detection algorithm in linked-lists
// See http://keithschwarz.com/interesting/code/?dir=find-duplicate

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        int fast = n-1, slow = n-1;
        do {
            fast = nums[fast]-1;
            fast = nums[fast]-1;
            slow = nums[slow]-1;
        } while(fast != slow);
        slow = n-1;
        while(fast != slow) {
            fast = nums[fast]-1;
            slow = nums[slow]-1;
        }
        return slow+1;
    }
};



/**************************************************** 
 ***    291,Hard,Word Pattern II 
 ****************************************************/

/*
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty substring in str.

Examples:

    pattern = "abab", str = "redblueredblue" should return true.
    pattern = "aaaa", str = "asdasdasdasd" should return true.
    pattern = "aabb", str = "xyzabcxzyabc" should return false.

Notes:
You may assume both pattern and str contains only lowercase letters. 
*/

// Backtracking solution using recursive calls.
// Each time grab a character in pattern, and try to match all possibilities in str. Use two maps to store the current mapping relations between the character and str. We need both forward (pat2txt) and backward mapping (txt2pat). 
// The function dfs starts matching pattern[i, end) with str[j, end). If i or j reaches end, we terminate properly.
// Then we take a character from pattern[i], and try to match any strings starting at j in str. There are several cases:
// 1. If pattern[i] is already found in the pat2txt map, then we have to match the same entry for str[j, end). We extract the same size from str (possibly out of str' range, which we need to properly take care of), and compare with the entry pat2txt. If matches we continue to next step by matching pattern[i+1, end) with str[j+len, end). Otherwise, we simply return false.
// 2. If pattern[i] is not found in pat2txt map, then we try all possibilities from str[j, end), i.e. str[j, j+1), str[j, j+2) ...
// For each trials, we need to check if they are already assigned to a mapping formula in txt2pat. If yes, we need to skip it (to ensure bijection relation). Otherwise, we make this the current mapping trial, and insert it to the two maps, and move to next step. After we are done, we erase the entries in the two maps to retrace.
// During the search, whenever we find a valid match, we return true immediately.
// Caveats:
//  if(j+len > n || str.substr(j, len) != sub), the first condition is necessary to avoid going out of bounds!

class Solution {
public:
    bool wordPatternMatch(string pattern, string str) {
        if(pattern.empty()) return str.empty();
        if(str.empty()) return pattern.empty();
        return dfs(pattern, 0, str, 0);
    }

    bool dfs(const string& pattern, int i, const string& str, int j) {
        int m = pattern.size(), n = str.size();
        if(i == m || j == n) return i == m && j == n;
        //read one pattern character
        char c = pattern[i];
        if(!pat2txt.count(c)) { //new character
            //try all possibilities from str[j, end) if that is not already in txt2pat
            for(int len = 1; len <= n-j; ++len) {
                string sub = str.substr(j, len);
                if(txt2pat.count(sub)) continue;
                pat2txt[c] = sub; //insert
                txt2pat[sub] = c; //insert
                if(dfs(pattern, i+1, str, j+len)) return true;
                pat2txt.erase(c); //retrace
                txt2pat.erase(sub); //retrace
            }
        } else { //already found mapping
            string sub = pat2txt[c];
            int len = sub.size();
            if(j+len > n || str.substr(j, len) != sub) return false; //not found match
            if(dfs(pattern, i+1, str, j+len)) return true; //found match, move to next step
        }
        return false; //finished matching
    }

    unordered_map<char, string> pat2txt;
    unordered_map<string, char> txt2pat;
};


/**************************************************** 
 ***    295,Hard,Find Median from Data Stream 
 ****************************************************/

/*
Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.
Examples:

[2,3,4] , the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

    void addNum(int num) - Add a integer number from the data stream to the data structure.
    double findMedian() - Return the median of all elements so far.

For example:

add(1)
add(2)
findMedian() -> 1.5
add(3) 
findMedian() -> 2

*/

// Solution: use two priority queues, one max-queue and the other min-queue. Store first half of data in max-queue and second half of data in min-queue. Has to take care of corner cases (count == 0)

class MedianFinder {
public:
    MedianFinder() : count(0) {}

    // Adds a number into the data structure.
    void addNum(int num) {
        if(count == 0) maxHeap.push(num);
        else if(count % 2 == 0) { //even number of elements
            if(num <= maxHeap.top()) maxHeap.push(num);
            else {
                minHeap.push(num);
                maxHeap.push(minHeap.top()); //put smallest in minHeap to maxHeap
                minHeap.pop();
            }
        } else { //odd number of elements, maxHeap has the extra one
            if(num >= maxHeap.top()) minHeap.push(num);
            else {
                maxHeap.push(num);
                minHeap.push(maxHeap.top());
                maxHeap.pop();
            }
        }
        count++;
    }

    // Returns the median of current data stream
    double findMedian() {
        if(count == 0) return 0;
        else if(count % 2 == 1) return maxHeap.top();
        else return (maxHeap.top() + minHeap.top())/2.0;
    }

private:    
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int> > minHeap;
    int count;
};

// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();

/**************************************************** 
 ***    296,Hard,Best Meeting Point 
 ****************************************************/

/*
A group of two or more people wants to meet and minimize the total travel distance. You are given a 2D grid of values 0 or 1, where each 1 marks the home of someone in the group. The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

For example, given three people living at (0,0), (0,4), and (2,2):

1 - 0 - 0 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0

The point (0,2) is an ideal meeting point, as the total travel distance of 2+2+2=6 is minimal. So return 6.
*/

// Reduce the problem to 2 1D problems. For 1D problem, sort the coordinates, then place the meeting points in the middle, the min distance is thus the sum of pos[n-1] - pos[0], pos[n-2] - pos[1] ... and pos[i+1] - pos[i], pos[i+2]-pos[i] depending on polarity of n.
// Caveats: need to sort the coordinates for row first!

class Solution {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        vector<int> row, col;
        int m = grid.size(), n = grid[0].size();
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(grid[i][j] == 1) { col.push_back(i); row.push_back(j); }
            }
        }
        sort(row.begin(), row.end());
        int distance = 0;
        int n1 = row.size();
        for(int k = 0; k < n1/2; ++k) {
            distance += (row[n1-k-1] - row[k]) + (col[n1-k-1] - col[k]);
        }
        
        return distance;
    }
};


/**************************************************** 
 ***    302,Hard,Smallest Rectangle Enclosing Black Pixels 
 ****************************************************/

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


/**************************************************** 
 ***    305,Hard,Number of Islands II 
 ****************************************************/

/*
A 2d grid map of m rows and n columns is initially filled with water. We may perform an addLand operation which turns the water at position (row, col) into a land. Given a list of positions to operate, count the number of islands after each addLand operation. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example:

Given m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]].
Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).

0 0 0
0 0 0
0 0 0

Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.

1 0 0
0 0 0   Number of islands = 1
0 0 0

Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.

1 1 0
0 0 0   Number of islands = 1
0 0 0

Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.

1 1 0
0 0 1   Number of islands = 2
0 0 0

Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.

1 1 0
0 0 1   Number of islands = 3
0 1 0

We return the result as an array: [1, 1, 2, 3]

Challenge:

Can you do it in time complexity O(k log mn), where k is the length of the positions?
*/

// Weighted union find with path compression by halving.
// See Solution to Problem 200 for details.

class UnionFind {
public:
    UnionFind(int N) : n(0) {
        id.resize(N, -1);
        size.resize(N, 0);
    }
    void add(int i) {
        id[i] = i; size[i] = 1;
        n++;
    }
    void uni(int i, int j) {
        if(id[j] == -1) return; //only add valid ones
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
    vector<int> id;
    vector<int> size;
    int n;
};

class Solution {
public:
    vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
        int size = positions.size();
        vector<int> result(size, 0);
        UnionFind uf(m*n);
        for(int i = 0; i < size; ++i) {
            const int &x = positions[i].first, &y = positions[i].second;
            int idx = x*n+y;
            uf.add(idx);
            //check four neighbors
            if(x > 0) uf.uni(idx, idx-n);
            if(x < m-1) uf.uni(idx, idx+n);
            if(y > 0) uf.uni(idx, idx-1);
            if(y < n-1) uf.uni(idx, idx+1);
            result[i] = uf.count();
        }
        return result;
    }
};


/**************************************************** 
 ***    308,Hard,Range Sum Query 2D - Mutable 
 ****************************************************/

/*
Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:

Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
update(3, 2, 2)
sumRegion(2, 1, 4, 3) -> 10

Note:

    The matrix is only modifiable by the update function.
    You may assume the number of calls to update and sumRegion function is distributed evenly.
    You may assume that row1 ≤ row2 and col1 ≤ col2.
*/

// Your NumMatrix object will be instantiated and called as such:
// NumMatrix numMatrix(matrix);
// numMatrix.sumRegion(0, 1, 2, 3);
// numMatrix.update(1, 1, 10);
// numMatrix.sumRegion(1, 2, 3, 4);

// 2D binary indexed tree.

class NumMatrix {
public:
    NumMatrix(vector<vector<int>> &matrix) {
        if(matrix.empty() || matrix[0].empty()) {
            m = n = 0;
            return;
        }
        m = matrix.size(); n = matrix[0].size();
        bitsum.resize(m+1, vector<int>(n+1, 0));
        num.resize(m+1, vector<int>(n+1, 0));
        for(int i = 0; i < m; ++i) 
            for(int j = 0; j < n; ++j)
                update(i, j, matrix[i][j]);
    }

    void update(int row, int col, int val) {
        int delta = val - num[++row][++col];
        num[row][col] = val;
        int irow = row, jcol = col;
        while(irow <= m) {
           jcol = col;
           while(jcol <= n) {
               bitsum[irow][jcol] += delta;
               jcol += (jcol & (-jcol));
           }
           irow += (irow & (-irow));
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return getSum(row2, col2) - getSum(row1-1, col2) - getSum(row2, col1-1) + getSum(row1-1, col1-1);
    }

private:
    //get sum from [0, 0] to [row, col]
    int getSum(int row, int col) {
        if(row < 0 || row >= m || col < 0 || col >= n) return 0;
        row++; col++;
        int sum = 0;
        int irow = row, jcol = col;
        while(irow > 0) {
            jcol = col;
            while(jcol > 0) {
                sum += bitsum[irow][jcol];
                jcol -= (jcol & (-jcol));
            }
            irow -= (irow & (-irow));
        }
        return sum;
        
    }
    int m, n;
    vector<vector<int> > bitsum, num;
};


/**************************************************** 
 ***    312,Hard,Burst Balloons 
 ****************************************************/

/*
Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

Note:
(1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
(2) 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100

Example:

Given [3, 1, 5, 8]

Return 167

    nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
   coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167

Credits:
Special thanks to @dietpepsi for adding this problem and creating all test cases.
*/

/*
Standard dynamic programming. Use dp[i][j] to store the maximum coins for popping balloons [i .. j]. There are l = j-i+1 possibilities, each corresponds to popping k-th balloon at last ( i <= k <= j). The points obtained in this scenario is:

  i-1 i ... k-1 k k+1 ... j j+1
We keep k until the last step, so the coins we get will be the coins won from breaking [i .. k-1], and [k+1 .. j], and in the end, we are left with [i-1, k, j+1], so the last step we get nums[i-1]*nums[k]*nums[j+1].

To avoid array bounds checking, we insert 1 to front and end of the nums array.

We also need to have n+2 dimension for the dp vector.
*/

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.push_back(1);
        nums.insert(nums.begin(), 1);
        //dp[i][j]:  the maximum coins for nums[i .. j], 1 <= i <= j <= n
        vector<vector<int> > dp(n+2, vector<int>(n+2, 0));
        for(int len = 1; len <= n; ++len) {
            for(int i = 1; i + len <= n+1; ++i) {
                int j = i+len-1;
                //now check max for nums[i .. j], try all cases where k breaks last (i <= k <= j)
                for(int k = i; k <= j; ++k) {
                    dp[i][j] = max(dp[i][j], dp[i][k-1] + dp[k+1][j] + nums[i-1]*nums[k]*nums[j+1]);
                }
            }
        }
        return dp[1][n];
    }
};


