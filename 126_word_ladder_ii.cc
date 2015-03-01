class Solution {
public:
 	map<string, vector<string> > rev_map; //reverse map from end to start

	vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict) {
		//first step, bfs to build the predecessor map of graph (start to end).
		//for a string, it can have many predecessors, which are stored as a vector in rev_map
		bfs(dict, start, end);

		vector<string> path;
		vector<vector<string> > ret;
		dfs(start, end, path, ret); 
		return ret;
	}
	/// Function to build the predecessor map. We need to do BFS search, and once we hit "end",
	/// we need to continue the search until we finish the current level
	/// when we construct map, we erase elements from dict (just like tagging visited sites)
	/// We break when next_lev contains end or next_level is empty
	void bfs(unordered_set<string>& dict, const string& start, const string& end) {
		dict.insert(start);
		dict.insert(end);

		unordered_set<string> cur_lev, next_lev;
		cur_lev.insert(start);
		while(1) {
			for(unordered_set<string>::const_iterator it = cur_lev.begin(); it != cur_lev.end(); ++it) dict.erase(*it);
			//prepare next level
			next_lev.clear();
			for(unordered_set<string>::const_iterator it = cur_lev.begin(); it != cur_lev.end(); ++it) {
				string str = *it;
				//find all possible string variations from str
				for(unsigned k = 0; k < str.size(); ++k) {
					string newstr = str;
					for(char c = 'a'; c <= 'z'; ++c) {
						if(c == str[k]) continue;
						newstr[k] = c;
						if(dict.find(newstr) != dict.end()) { //found a new str
							next_lev.insert(newstr); //insert to next level
							rev_map[newstr].push_back(str); // add str as one predecessor of newstr
						}
					}
				}
			}
			if(next_lev.empty() || next_lev.find(end) != next_lev.end()) break;
			cur_lev = next_lev; //move to next level
		}
	}

	/// Function to perform DFS to find the path from source to destination (in the reverse order)
	void dfs(const string &start, const string &end, vector<string>& path, vector<vector<string> > &ret) {
		path.insert(path.begin(), end); //insert the last species at the beginning of vector
		if(start == end) {
			ret.push_back(path); 
			path.erase(path.begin()); //erase newly added element
			return;
		} else { 
			for(int j = 0; j < rev_map[end].size(); ++j)  //dfs on neighbors
				dfs(start, rev_map[end][j], path, ret);
			path.erase(path.begin()); //erase newly added element
		} 
	}
};
