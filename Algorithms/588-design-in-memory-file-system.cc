// Use an N-ary tree to represent the file system structure. Each node can be a directory or a file.

class FileSystem {
public:
    FileSystem() {
        root = new TreeNode;
    }
    
    vector<string> ls(string path) {
        vector<string> path_vec = GetPath(path);        
        TreeNode* node = root;
        for (const auto &dir : path_vec) {
            node = node->children[dir];
        }
                
        if (node->isFile) return {*path_vec.rbegin()};
        
        vector<string> result;
        for (const auto &[dir, _] : node->children) {
            result.push_back(dir);
        }
        return result;
    }
    
    void mkdir(string path) {
        vector<string> path_vec = GetPath(path);
        TreeNode* node = root;
        for (const auto &dir : path_vec) {
            if (!node->children.count(dir)) {
                node->children[dir] = new TreeNode;
            }
            node = node->children[dir];
        }        
    }
    
    void addContentToFile(string filePath, string content) {
        vector<string> path_vec = GetPath(filePath);
        string fileName = *path_vec.rbegin();
        path_vec.pop_back();
        
        TreeNode* node = root;
        for (const auto &dir : path_vec) {
            node = node->children[dir];
        }
        if (node->children.count(fileName)) {
            node->children[fileName]->content.append(content);
        } else {
            node->children[fileName] = new TreeNode(true, content);            
        }
    }
    
    string readContentFromFile(string filePath) {
        vector<string> path_vec = GetPath(filePath);
        string fileName = *path_vec.rbegin();
        path_vec.pop_back();
        
        TreeNode* node = root;
        for (const auto &dir : path_vec) {
            node = node->children[dir];
        }
        return node->children[fileName]->content;
    }
    
    struct TreeNode {
        map<string, TreeNode*> children;
        bool isFile;        
        string content; // only set when isFile is true
        TreeNode() : isFile(false) {}
        TreeNode(bool _isFile, const string &_content) : isFile(_isFile), content(_content) {}
    };
    
private:
    vector<string> GetPath(const string &path) {
        if (path.empty()) return {};
        if (path.size() == 1)  return {};
        int i = 1;
        vector<string> result;
        while (i < path.size()) {
            int j = i;
            while (j < path.size() && path[j] != '/') j++;
            result.push_back(path.substr(i, j-i));
            i = j+1;
        }
        return result;
    }

    TreeNode* root;    
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * vector<string> param_1 = obj->ls(path);
 * obj->mkdir(path);
 * obj->addContentToFile(filePath,content);
 * string param_4 = obj->readContentFromFile(filePath);
 */
