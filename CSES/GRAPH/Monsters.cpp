//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
#define pb push_back
 
vector<vector<ll>> dir = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
string flag = "RLUD";
 
//--------------------------------WRITE_HERE-------------------------------------------
ll n, m;
 
// To retrace the path
string f(vector<vector<char>> &par, ll x, ll y, ll d)
{
    string ans = "";
    while (1)
    {
        ans += par[x][y];
        if (ans.size() == d)
            break;
 
        if (par[x][y] == 'U')
            x++;
        else if (par[x][y] == 'D')
            x--;
        else if (par[x][y] == 'L')
            y++;
        else
            y--;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
 
void _144()
{
    cin >> n >> m;
 
    vector<string> v;
    for (ll i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        v.pb(s);
    }
 
    // finding positions of A and M.
    ll sx = -1, sy = -1;
    vector<pair<ll, ll>> mons;
    priority_queue<pair<ll, pair<ll, ll>>,
        vector<pair<ll, pair<ll, ll>>>,
        greater<pair<ll, pair<ll, ll>>>>
        pq2, pq3;
    vector<vector<ll>> dis2(n, vector<ll>(m, 1e9));
    vector<vector<ll>> dis(n, vector<ll>(m, 1e9));
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (v[i][j] == 'A')
            {
                sx = i;
                sy = j;
                pq3.push({0,{i,j}});
                dis[i][j]=0;
 
            }
            else if (v[i][j] == 'M')
            {
                pq2.push({0, {i, j}});
                dis2[i][j]=0;
            }
        }
    }
 
    // A lies on edge then NO.
    for (auto it : dir)
    {
        ll nx = sx + it[0];
        ll ny = sy + it[1];
        if (nx < 0 || ny < 0 || nx >= n || ny >= m)
        {
            cout << "YES" << endl;
            cout << "0";
            return;
        }
    }
 
    // chaaro trf dot absent hai A ke then NO.
    ll flag1 = 0;
    for (auto it : dir)
    {
        ll nx = sx + it[0];
        ll ny = sy + it[1];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && v[nx][ny] == '.')
        {
            flag1 = 1;
        }
    }
    if (flag1 == 0)
    {
        cout << "NO";
        return;
    }
 
    // now marking distance for all Monsters 1 by 1.---dis2
    while (!pq2.empty())
        {
            ll xc = pq2.top().second.first;
            ll yc = pq2.top().second.second;
 
            pq2.pop();
 
            for (ll i = 0; i < 4; i++)
            {
                ll nxc = xc + dir[i][0];
                ll nyc = yc + dir[i][1];
 
                if (nxc >= 0 && nxc < n && nyc >= 0 && nyc < m && v[nxc][nyc] == '.')
                {
                    if (dis2[xc][yc] + 1 < dis2[nxc][nyc])
                    {
                        dis2[nxc][nyc] = dis2[xc][yc] + 1;
                        pq2.push({dis2[nxc][nyc], {nxc, nyc}});
                    }
                }
            }
        }
 
    // now marking distance for Person A.---dis
    vector<vector<char>> par(n, vector<char>(m, 'X'));
    while (!pq3.empty())
    {
        ll xc = pq3.top().second.first;
        ll yc = pq3.top().second.second;
 
        pq3.pop();
 
        for (ll i = 0; i < 4; i++)
        {
            ll nxc = xc + dir[i][0];
            ll nyc = yc + dir[i][1];
 
            if (nxc >= 0 && nxc < n && nyc >= 0 && nyc < m && v[nxc][nyc] == '.')
            {
                if (dis[xc][yc] + 1 < dis[nxc][nyc])
                {
                    dis[nxc][nyc] = dis[xc][yc] + 1;
                    pq3.push({dis[nxc][nyc], {nxc, nyc}});
                    par[nxc][nyc] = flag[i];
 
                    if (nxc == 0 || nxc == n - 1 || nyc == 0 || nyc == m - 1)
                    {
 
                        if (dis[nxc][nyc] < dis2[nxc][nyc])
                        {
                            cout << "YES" << endl;
                            cout << dis[nxc][nyc] << endl;
                            cout << f(par, nxc, nyc, dis[nxc][nyc]);
                            return;
                        }
                    }
                }
            }
        }
    }
 
    // now
 
    cout << "NO";
    return;
}
 
//--------------------------------END--------------------------------------------------
 
// Main
int main()
{
 
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
