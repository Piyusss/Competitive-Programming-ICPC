struct Node {
    Node* links[26];
    int cntEndWith = 0;
    int cntPrefix = 0;
    bool flag = false;

    bool containsKey(char ch) {
        return (links[ch - 'a'] != NULL); 
    }

    Node* get(char ch) {
        return links[ch - 'a']; 
    }

    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }

    void setEnd()
    {
        flag = true;
    }

    bool isEnd()
    {
        return flag;
    }

    void increaseEnd() {
        cntEndWith++; 
    }

    void increasePrefix() {
        cntPrefix++;
    }

    void deleteEnd() {
        cntEndWith--; 
    }

    void reducePrefix() {
        cntPrefix--; 
    }
};

class Trie {
private:
    Node* root; 

public:
    Trie() {
        root = new Node(); 
    }

    void insert(string word) {
        Node* node = root; 
        for (int i = 0; i < word.size(); i++) { 
            if (!node->containsKey(word[i])) {
                node->put(word[i], new Node()); 
            }
            node = node->get(word[i]);
            node->increasePrefix(); 
        }
        node->increaseEnd();
        node->setEnd();
    }

    bool search(string word)
    {
        Node *node = root;
        for (int i = 0; i < word.length(); i++)
        {
            if (!node->containsKey(word[i]))
            {
                return false;
            }
            node = node->get(word[i]);
        }
        return node->isEnd();
    }

    bool startsWith(string prefix)
    {
        Node *node = root;
        for (int i = 0; i < prefix.length(); i++)
        {
            if (!node->containsKey(prefix[i]))
            {
                return false;
            }
            node = node->get(prefix[i]);
        }
        return true;
    }

    int countWordsEqualTo(string word) {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) { 
            if (node->containsKey(word[i])) { 
                node = node->get(word[i]); 
            }else{
                return 0;
            }
        }
        return node->cntEndWith; 
    }

    int countWordsStartingWith(string word) {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) { 
            if (node->containsKey(word[i])) { 
                node = node->get(word[i]); 
            }else{
                return 0; 
            }
        }
        return node->cntPrefix; 
    }

    void erase(string word) {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) { 
            if (node->containsKey(word[i])) { 
                node = node->get(word[i]);
                node->reducePrefix(); 
            } else {
                return; 
            }
        }
        node->deleteEnd(); 
    }
};
