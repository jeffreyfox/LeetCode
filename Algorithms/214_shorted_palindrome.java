/// Find the longest palindrome substring starting at 0.Then reverse the remaining part and append it to the front of the string. Time complexity O(n2).

public class Solution {
    public String shortestPalindrome(String s) {
        int n = s.length();
        if (n == 0 || n == 1) return s;
        int l = 1; //maximum length of palindrome substring s[0 .. l-1]
        for (int i = 2; i <= n; ++i)
            if (isPalindrome(s, i)) l = i;
        String suffix = s.substring(l, n);
        String preffix = new StringBuffer(suffix).reverse().toString();
        return preffix + s;
    }
    //whether s[0 .. len-1] is palindrome?
    private boolean isPalindrome(String s, int len) {
        for (int i = 0; i < len/2; ++i) 
            if (s.charAt(i) != s.charAt(len-1-i)) return false;
        return true;
    }
}
