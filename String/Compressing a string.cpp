//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

vector<int> compute_pi(const string &s)
{
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1, j = 0; i < n; i++)
    {
        while (j > 0 && s[i] != s[j])
        {
            j = pi[j - 1];
        }
        if (s[i] == s[j])
        {
            j++;
        }
        pi[i] = j;
    }
    return pi;
}

pair<int, string> find_compressed_string(const string &s)
{
    int n = s.size();
    vector<int> pi = compute_pi(s);
    int k = n - pi[n - 1];

    if (n % k == 0)
    {
        return {k, s.substr(0, k)};
    }
    return {n, s};
}

void _144()
{
    string s;
    cin >> s;

    pair<int, string> result = find_compressed_string(s);
    cout << "Compressed Length: " << result.first << "\n";
    cout << "Compressed String: " << result.second << "\n";
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
