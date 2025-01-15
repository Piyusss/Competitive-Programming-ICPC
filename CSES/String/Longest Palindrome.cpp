//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

string manacher_algo(string s)
{
    string t = "$";
    for (char c : s)
        t += "#" + string(1, c);
    t += "#";

    int n = t.length();
    vector<int> p(n, 0);
    int center = 0, right = 0;

    for (int i = 1; i < n - 1; ++i)
    {
        if (i < right)
        {
            p[i] = min(right - i, p[2 * center - i]);
        }

        while (t[i + p[i] + 1] == t[i - p[i] - 1])
        {
            p[i]++;
        }

        if (i + p[i] > right)
        {
            center = i;
            right = i + p[i];
        }
    }

    int maxLen = 0, start = 0;
    for (int i = 1; i < n - 1; ++i)
    {
        if (p[i] > maxLen)
        {
            maxLen = p[i];
            start = (i - p[i]) / 2;
        }
    }

    return s.substr(start, maxLen);
}

void _144()
{
    string s;
    cin >> s;
    cout << manacher_algo(s) << "\n";

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
