//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

vector<vector<int>>dir={{0,1},{0,-1},{-1,0},{1,0}};

int __01Bfs(vector<string>&jail,int n,int m){
    vector<vector<int>>dis(n,vector<int>(m,1E9));
    dis[0][0]=0;

    deque<pair<int,int>>dq;
    dq.push_back({0,0});

    while(!dq.empty()){
        auto it=dq.front();
        int r=it.first;
        int c=it.second;

        dq.pop_front();

        for(auto &d:dir){
            int nr=r+d[0];
            int nc=c+d[1];

            if(nr>=0 && nc>=0 && nr<n && nc<m){

                if (jail[r][c] == jail[nr][nc] && dis[r][c]+0<dis[nr][nc])
                {
                    dis[nr][nc] = dis[r][c]+0;
                    dq.push_front({nr, nc});
                }
                else if (jail[r][c] != jail[nr][nc] && dis[r][c] + 1 < dis[nr][nc])
                {
                    dis[nr][nc] = dis[r][c] + 1;
                    dq.push_back({nr, nc});
                }

            }
        }
    }

    return dis[n-1][m-1];
}


void _144()
{
    int n,m;
    cin>>n>>m;

    vector<string>jail(n);
    for(int i=0;i<n;i++) cin>>jail[i];

    int mini=__01Bfs(jail,n,m);

    if(mini==1E9) {
        cout<<-1<<"\n";
    }
    else{
        cout<<mini<<"\n";
    }
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
    cin >> t;
    while (t--)
    {
        _144();
    }
}
