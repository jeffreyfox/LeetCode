/*
/*
Design a simplified version of Twitter where users can post tweets, follow/unfollow another user, and is able to see the 10 most recent tweets in the user's news feed.

Implement the Twitter class:

    Twitter() Initializes your twitter object.
    void postTweet(int userId, int tweetId) Composes a new tweet with ID tweetId by the user userId. Each call to this function will be made with a unique tweetId.
    List<Integer> getNewsFeed(int userId) Retrieves the 10 most recent tweet IDs in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user themself. Tweets must be ordered from most recent to least recent.
    void follow(int followerId, int followeeId) The user with ID followerId started following the user with ID followeeId.
    void unfollow(int followerId, int followeeId) The user with ID followerId started unfollowing the user with ID followeeId. 

Example 1:

Input
["Twitter", "postTweet", "getNewsFeed", "follow", "postTweet", "getNewsFeed", "unfollow", "getNewsFeed"]
[[], [1, 5], [1], [1, 2], [2, 6], [1], [1, 2], [1]]
Output
[null, null, [5], null, null, [6, 5], null, [5]]

Explanation
Twitter twitter = new Twitter();
twitter.postTweet(1, 5); // User 1 posts a new tweet (id = 5).
twitter.getNewsFeed(1);  // User 1's news feed should return a list with 1 tweet id -> [5]. return [5]
twitter.follow(1, 2);    // User 1 follows user 2.
twitter.postTweet(2, 6); // User 2 posts a new tweet (id = 6).
twitter.getNewsFeed(1);  // User 1's news feed should return a list with 2 tweet ids -> [6, 5]. Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
twitter.unfollow(1, 2);  // User 1 unfollows user 2.
twitter.getNewsFeed(1);  // User 1's news feed should return a list with 1 tweet id -> [5], since user 1 is no longer following user 2.

Constraints:

    1 <= userId, followerId, followeeId <= 500
    0 <= tweetId <= 104
    All the tweets have unique IDs.
    At most 3 * 104 calls will be made to postTweet, getNewsFeed, follow, and unfollow.
*/

// Solution using a priority queue. Can futher simplify.
// Caveats: the tweetId cannot be used to determine the order. Need to have a counter variable which increments every time postTweet is called.
class Twitter {
public:
    struct Tweet {
        int tweetId;
        int timestamp;
        Tweet() : tweetId(-1), timestamp(-1) {}
        Tweet(int tId, int ts) : tweetId(tId), timestamp(ts) {}
    };
    
    struct Record {        
        int userId;
        int idx;  // idx of the tweet in tweets[i]
        Tweet tweet;        
        Record() : userId(-1), idx(-1), tweet() {}
        Record(int u, int i, const Tweet &t) : userId(u), idx(i), tweet(t) {}
    };
    
    Twitter() {
        tweets.resize(501);
        followees.resize(501);
        counter = 0;
    }
    
    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back(Tweet(tweetId, counter++));     
    }
    

    vector<int> getNewsFeed(int userId) {
        // merges tweets[userId] and the tweets from followees[userId]        
        auto compare = [](Record a, Record b) { return a.tweet.timestamp < b.tweet.timestamp;};
        priority_queue<Record, vector<Record>, decltype(compare)> pq(compare);
        // merges tweets from userId and the followees[userId].
        if (!tweets[userId].empty()) {
            int size = tweets[userId].size();
            pq.push(Record(userId, size-1, tweets[userId][size-1]));
        }
        for (const auto followeeId : followees[userId]) {
            if (!tweets[followeeId].empty())  {
                int size = tweets[followeeId].size();
                pq.push(Record(followeeId, size-1, tweets[followeeId][size-1]));
            }
        }
        vector<int> result;
        while (!pq.empty()){
            int tweetId = pq.top().tweet.tweetId;
            int uId = pq.top().userId;
            int idx = pq.top().idx;
            pq.pop();
            if (idx > 0) {
                pq.push(Record(uId, idx-1, tweets[uId][idx-1]));  
            }            
            result.push_back(tweetId);
            if (result.size() == 10) break;
        }
        return result;
    }
    
    void follow(int followerId, int followeeId) {
        followees[followerId].insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        followees[followerId].erase(followeeId);        
    }
    
private:
    // tweets[i] gives the tweet ID of user[i]'s tweets in ascending order.
    std::vector<std::vector<Tweet>> tweets;
    // followees[i] gives the list of users that user[i] follows.
    std::vector<std::unordered_set<int>> followees;
    int counter;
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */
