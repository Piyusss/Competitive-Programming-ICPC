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

int count_distinct_substrings(const string &s)
{
    int n = s.size();
    int res = 0;
    string t = "";

    for (int i = 0; i < n; i++)
    {
        t = s.substr(0, i + 1);
        reverse(t.begin(), t.end());
        vector<int> pi = compute_pi(t);
        int pi_max = *max_element(pi.begin(), pi.end());
        res += (i + 1) - pi_max;
    }

    return res;
}

void _144()
{
    string s;
    cin >> s;

    cout << count_distinct_substrings(s);
    return;
}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
    // freopen("input.in", "r",stdin);
    // freopen("output.out", "w",stdout);

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
