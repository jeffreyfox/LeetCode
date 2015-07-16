///Java solutin (with dummy head)
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
public class Solution {
    public ListNode removeNthFromEnd(ListNode head, int n) {
        ListNode dummy = new ListNode(0);
        dummy.next = head;
        ListNode front = dummy, back = dummy, p = null;
        for(int i = 0; i < n-1; ++i) front = front.next;
        while(front.next != null) {
            front = front.next;
            p = back;
            back = back.next;
        }
        p.next = back.next; //delete back
        return dummy.next;
    }
}
