// Note that here we use a sorted map with vector<string> as key because vector<string> has comparison operators. If we want to use unordered map, we need to
// provide a hash function which leads to unnecessary code complications during an interview.

// Steps:
// 1. For each user, generate a map of website visits keyed by the visit timestamp. Store the map in another map keyed by the user name.
// 2. Scan the map from #1, for each user, generate the unique 3-website patterns
//    2a. first scan the website visit sorted map and convert it into a vector of websites (dropping out the key and keeping the order by timestamp)
//    2b. Scan the vector and generate the unique patterns using a 3-level for loop. We return a set to dedup (e.g. "a", "a", "a", "a" => only return one "a", "a", "a")
// 3. Insert each 3-website pattern into a counting map (pattern to score) and update the current max score if needed (need to break ties properly)

class Solution {
public:
    vector<string> mostVisitedPattern(vector<string>& username, vector<int>& timestamp, vector<string>& website) {
        // user => {timestamp, website }
        unordered_map<string, map<int, string>> website_visits;
        for (int i = 0; i < username.size(); ++i) {           
            const auto &user = username[i];
            const int t = timestamp[i];
            website_visits[user][t] = website[i];
        }
        
        map<vector<string>, int> pattern_counts;
        vector<string> max_pattern;
        int max_score = 0;
        for (const auto &[user, websites] : website_visits) {
            vector<string> pattern(3);            
            const vector<string> sorted_websites = getWebsitesSortedByTimestamp(websites);
            const set<vector<string>> unique_patterns = getUniquePatterns(sorted_websites);
           
            for (const auto &pattern : unique_patterns) {
                int score = ++pattern_counts[pattern];              
                if (max_score < score || (max_score == score && isSmaller(pattern, max_pattern))) {
                    max_score = score;
                    max_pattern = pattern;
                }
            }
        }
        return max_pattern;
    }
    
    vector<string> getWebsitesSortedByTimestamp(const map<int, string> &timestamps_and_websites) {
        vector<string> result;
        for (const auto &[timestamp, website] : timestamps_and_websites) {
            result.push_back(website);            
        }
        return result;
    }

    set<vector<string>> getUniquePatterns(const vector<string> &websites) {
        set<vector<string>> result;
        int n = websites.size();
        vector<string> pattern(3);
        for (int i = 0; i < n-2; ++i) {
            pattern[0] = websites[i];
            for (int j = i+1; j < n-1; ++j) {
                pattern[1] = websites[j];
                for (int k = j+1; k < n; ++k) {
                    pattern[2] = websites[k];   
                    result.insert(pattern);
                }
            }            
        }
        return result;
    }

    bool isSmaller(const vector<string> &vec1, const vector<string> &vec2) {
        for (int i = 0; i < 3; ++i) {
            if (vec1[i] != vec2[i]) return vec1[i] < vec2[i];
        }
        return true;
    }  
};
