///recursive solution
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
public class Solution {
    public ListNode reverseList(ListNode head) {
        if (head == null) return null;
        if (head.next == null) return head;
        ListNode p = head.next;
        ListNode newhead = reverseList(p);
        p.next = head;
        head.next = null; // remember to set tail's next to null!
        return newhead;
    }
}
