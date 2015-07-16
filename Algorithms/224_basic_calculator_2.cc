// Use only one stack, push sign (1/-1) and value to the same stack, when pop, pop twice

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

