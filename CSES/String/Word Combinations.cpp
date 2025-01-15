//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------
const int mod = 1e9 + 7;

vector<int> dp(5005);
vector<vector<int>> trie(1e6 + 5, vector<int>(26));
vector<bool> isEndOfWord(1e6 + 5);
int trieNodeCount = 0;

void insertWordInTrie(string &word)
{
    int currentNode = 0;
    for (char &ch : word)
    {
        if (!trie[currentNode][ch - 'a'])
            trie[currentNode][ch - 'a'] = ++trieNodeCount;
        currentNode = trie[currentNode][ch - 'a'];
    }
    isEndOfWord[currentNode] = true;
}

int countWays(int start, string &S)
{
    int currentNode = 0, ways = 0;
    for (int i = start; i < S.size(); i++)
    {
        if (!trie[currentNode][S[i] - 'a'])
            return ways;
        currentNode = trie[currentNode][S[i] - 'a'];
        if (isEndOfWord[currentNode])
            ways = (ways + dp[i + 1]) % mod;
    }
    return ways;
}

void solve(string &S, int K)
{
    dp[S.size()] = 1;
    for (int i = S.size() - 1; i >= 0; i--)
    {
        dp[i] = countWays(i, S);
    }
}

string s,p;

void _144()
{
    cin>>s;
    int k;cin>>k;

    while(k--){
        cin>>p;
        insertWordInTrie(p);
    }

    solve(s,k);
    cout << dp[0];

    return;
}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
//freopen("input.in", "r",stdin);
//freopen("output.out", "w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll t = 1;
    // cin >> t;
    while (t--)
    {
        _144();
    }
}
