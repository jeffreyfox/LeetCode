// Java solution using Strings.split function and Integer.parseInt()
// Caveat: String.split method takes a regular expression as delimiter.
// can't use "." because it is a special character and means "any character", and will ignore any characters. Need to use escape "\\."
// Also, "1.0" is treated the same as "1"

public class Solution {
    public int compareVersion(String version1, String version2) {
        String[] v1 = version1.split("\\.");
        String[] v2 = version2.split("\\.");
        
        for (int i = 0; i < Math.max(v1.length, v2.length); ++i) {
            int n1 = (i < v1.length) ? Integer.parseInt(v1[i]) : 0;
            int n2 = (i < v2.length) ? Integer.parseInt(v2[i]) : 0;
            if      (n1 > n2) return  1;
            else if (n1 < n2) return -1;
        }
        return 0;
    }

/*  // function to parse int
    private int Str2Int(String num) {
        int ret = 0;
        for (int i = 0; i < num.length(); ++i) {
            ret = ret*10 + (num.charAt(i)-'0');
        }
        return ret;
    }
*/
}
