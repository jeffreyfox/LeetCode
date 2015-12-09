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

