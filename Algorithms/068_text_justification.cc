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

