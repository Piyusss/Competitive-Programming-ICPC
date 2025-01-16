//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

template <typename T>
struct Fenwick2D
{
private:
    const int n, m;
    vector<vector<T>> arr;

public:
    Fenwick2D(int _n, int _m) : n(_n), m(_m), arr(n + 1, vector<T>(m + 1)) {}

    void add(int r, int c, T val)
    {
        r++, c++;
        for (; r <= n; r += r & -r)
        {
            for (int i = c; i <= m; i += i & -i)
            {
                arr[r][i] += val;
            }
        }
    }

    T rect_sum(int r, int c)
    {
        r++, c++;
        T sum = 0;
        for (; r > 0; r -= r & -r)
        {
            for (int i = c; i > 0; i -= i & -i)
            {
                sum += arr[r][i];
            }
        }
        return sum;
    }

    T rect_sum(int r1, int c1, int r2, int c2)
    {
        return rect_sum(r2, c2) - rect_sum(r2, c1 - 1) -
               rect_sum(r1 - 1, c2) + rect_sum(r1 - 1, c1 - 1);
    }
};

void _144()
{
    int n, q;
    cin >> n >> q;

    Fenwick2D<int> bit2d(n, n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            char x;
            cin >> x;
            if (x == '*')
            {
                bit2d.add(i, j, 1);
            }
        }
    }

    while (q--)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 -= 1;
        y1 -= 1;
        x2 -= 1;
        y2 -= 1;
        cout << bit2d.rect_sum(x1, y1, x2, y2) << "\n";
    }

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
