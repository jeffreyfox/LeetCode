class Solution {
public:
	vector<vector<string> > partition(string s) {
		vector<vector<string> > ret;
		int n = s.size();
		vector<int> lens(n, 0);
		vector<int> begs(n, -1);
		int k(0);
		//invalirant: k-1 segments have been partitioned
		while(k >= 0) {
			//initialize begs and lens properly
			if(begs[k] == -1) begs[k] = (k == 0 ? 0 : begs[k-1] + lens[k-1]);
			lens[k] ++; //increase length by 1
			while(begs[k] + lens[k] <= n && ! isPalindrome(s, begs[k], lens[k])) lens[k] ++;
			
			if(begs[k] + lens[k] > n) { //exhausted all choices, reset and retrace
				begs[k] = -1;
				lens[k] = 0;
				k --;
			} else if(begs[k] + lens[k] == n) { //already found a valid partition, need to retrace
				ret.push_back(makeSolution(s, begs, lens));
				begs[k] = -1;
				lens[k] = 0;
				k --;
			} else { //move to next segment
				k++;
			}
		}
		return ret;
	}

	bool isPalindrome(const string &s, int beg, int len) {
		if(len <= 1) return true;
		int end = beg + len-1;
		for(int k = 0; k < len/2; ++k) {
			if(s[beg+k] != s[end-k])  return false;
		}
		return true;
	}

	vector<string> makeSolution(const string&s, vector<int> begs, vector<int> lens) {
		vector<string> ret;
		for(int k = 0; k < begs.size(); ++k) {
			if(lens[k] > 0) { 
				ret.push_back(s.substr(begs[k], lens[k]));
			}
			else break;
		}
		return ret;
	}
};
