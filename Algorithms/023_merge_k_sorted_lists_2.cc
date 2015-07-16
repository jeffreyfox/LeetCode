/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
// Priority queue solution O(nlgk)
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
