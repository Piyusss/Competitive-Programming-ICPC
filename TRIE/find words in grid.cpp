#include <bits/stdc++.h>
using namespace std;

#define ll long long

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
    Node *getRoot()
    {
        return root;
    }
};

vector<pair<int, int>> directions = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

void dfs(int x, int y, Node *node, vector<vector<char>> &grid, vector<vector<bool>> &visited, string &currentWord, set<string> &result)
{
    int n = grid.size();
    int m = grid[0].size();

    visited[x][y] = true;
    currentWord += grid[x][y];

    if (node->isEnd()) result.insert(currentWord);

    for (auto it : directions)
    {   int dx=it.first;
        int dy=it.second;

        int newX = x + dx;
        int newY = y + dy;

        if (newX >= 0 && newX < n && newY >= 0 && newY < m && !visited[newX][newY])
        {
            char nextChar = grid[newX][newY];
            if (node->containsKey(nextChar))
            {
                dfs(newX, newY, node->get(nextChar), grid, visited, currentWord, result);
            }
        }
    }

    visited[x][y] = false;
    currentWord.pop_back();
}

set<string> findWordsInGrid(vector<vector<char>> &grid, Trie &trie)
{
    int n = grid.size();
    int m = grid[0].size();
    set<string> result;
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    Node* root = trie.getRoot();

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            char startChar = grid[i][j];
            if (root->containsKey(startChar))
            {
                string currentWord = "";
                dfs(i, j, root->get(startChar), grid, visited, currentWord, result);
            }
        }
    }

    return result;
}

// Main function
int main()
{
    vector<vector<char>> grid = {
        {'a', 'x', 'm', 'y'},
        {'b', 'g', 'd', 'f'},
        {'x', 'e', 'e', 't'},
        {'r', 'a', 'k', 's'}};

    vector<string> dictionary = {"geeks", "geek", "raks", "xmyft", "xmyftt", "ages", "redy","xgeek","xgeeek"};

    Trie trie;
    for (auto &word : dictionary) trie.insert(word);

    set<string> result = findWordsInGrid(grid, trie);

    cout << "Words found in the grid:" << endl;
    for (auto &word : result) cout << word << endl;

    return 0;
}
