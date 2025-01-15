//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

vector<int> compute_pi(string &s)
{
    int n = s.size();
    vector<int> pi(n);

    for (int i = 1, j = 0; i < n; i++)
    {
        while (j > 0 && s[j] != s[i])
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

vector<int> compute_z(const string &s)
{
    int n = (int)s.size();
    vector<int> z_S(n);
    for (int i = 1, l = 0, r = 0; i < n; i++)
    {
        if (i <= r)
        {
            z_S[i] = min(z_S[i - l], r - i + 1);
        }
        while (i + z_S[i] < n && s[z_S[i]] == s[i + z_S[i]])
        {
            z_S[i]++;
        }
        if (i + z_S[i] - 1 > r)
        {
            l = i;
            r = i + z_S[i] - 1;
        }
    }
    return z_S;
}

void _144()
{
    string s;cin>>s;

    vector<int>pi=compute_pi(s);
    vector<int>z=compute_z(s);
    
    for (auto &it : z) cout << it << " ";
    cout<<"\n";
    for (auto &it : pi) cout << it << " ";

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
