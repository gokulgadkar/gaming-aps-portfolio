#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class RTNode {
public:
    map<string, RTNode*> children;
    bool endBool;
    RTNode() : endBool(false) {}
};

class RTree {
private:
    RTNode* root;

    void insertNode(RTNode* node, const string& key) {
        if (key.empty()) {
            node->endBool = true;
            return;
        }

        for (auto& child : node->children) {
            string commonPrefix = getCommonPrefix(child.first, key);
            if (!commonPrefix.empty()) {
                if (commonPrefix.length() == child.first.length()) {
                    insertNode(child.second, key.substr(commonPrefix.length()));
                } else {
                    RTNode* newChild = new RTNode();
                    string remainingChildKey = child.first.substr(commonPrefix.length());
                    string remainingKey = key.substr(commonPrefix.length());

                    newChild->children[remainingChildKey] = child.second;
                    node->children.erase(child.first);
                    node->children[commonPrefix] = newChild;

                    if (remainingKey.empty()) {
                        newChild->endBool = true;
                    } else {
                        insertNode(newChild, remainingKey);
                    }
                }
                return;
            }
        }

        node->children[key] = new RTNode();
        node->children[key]->endBool = true;
    }

    bool searchNode(RTNode* node, const string& key) const {
        if (key.empty()) {
            return node->endBool;
        }

        for (const auto& child : node->children) {
            string commonPrefix = getCommonPrefix(child.first, key);
            if (!commonPrefix.empty() && commonPrefix == child.first) {
                return searchNode(child.second, key.substr(commonPrefix.length()));
            }
        }

        return false;
    }

    string getCommonPrefix(const string& str1, const string& str2) const {
        size_t minLength = min(str1.length(), str2.length());
        for (size_t i = 0; i < minLength; ++i) {
            if (str1[i] != str2[i]) {
                return str1.substr(0, i);
            }
        }
        return str1.substr(0, minLength);
    }

    void deleteNode(RTNode* node) {
        for (auto& child : node->children) {
            deleteNode(child.second);
        }
        delete node;
    }

public:
    RTree() : root(new RTNode()) {}

    ~RTree() {
        deleteNode(root);
    }

    void insert(const string& key) {
        insertNode(root, key);
    }

    bool search(const string& key) const {
        return searchNode(root, key);
    }
};

int main() {
    RTree tree;
    tree.insert("utopia");

    tree.insert("utopai");


    cout << tree.search("utopay") << endl;


    return 0;
}

