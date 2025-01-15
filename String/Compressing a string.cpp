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

int find_compressed_length(const string &s)
{
    int n = s.size();
    vector<int> pi = compute_pi(s);
    int k = n - pi[n - 1];
    if (n % k == 0)
        return k;
    return n;
}

void _144()
{
    string s;
    cin >> s;

    int compressed_length = find_compressed_length(s);
    cout << compressed_length << "\n";
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
