//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

int dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

int findDeg(ll x,ll y,vector<vector<ll>>&board){
    int cnt=0;
    for(ll k=0;k<8;k+=1){
        ll nx=x+dx[k];
        ll ny=y+dy[k];
        if(nx>=0 && ny>=0 && nx<8 && ny<8 && board[nx][ny]==-1){
            cnt+=1;
        }
    }
    return cnt;
}

bool Warnsdorff(ll x,ll y,vector<vector<ll>>&board,ll cnt){
    if(cnt==64) return 1;

    vector<pair<ll,pair<ll,ll>>>moves;
    for(ll k=0;k<8;k+=1){
        ll nx=x+dx[k];
        ll ny=y+dy[k];
        if(nx>=0 && ny>=0 && nx<8 && ny<8 && board[nx][ny]==-1){
            int deg=findDeg(nx,ny,board);
            moves.push_back({deg,{nx,ny}});
        }
    }

    sort(moves.begin(),moves.end());

    for(auto &it:moves){
        ll nx=it.second.first;
        ll ny=it.second.second;

        board[nx][ny]=cnt+1;
        if(Warnsdorff(nx,ny,board,cnt+1)){
            return 1;
        }
        board[nx][ny]=-1;
    }

    return 0;
}

void _144()
{
    ll c,r;
    cin>>c>>r;

    c-=1;r-=1;

    vector<vector<ll>>board(8,vector<ll>(8,-1));
    board[r][c]=1;

    Warnsdorff(r,c,board,1);

    for(ll i=0;i<8;i+=1){
        for(ll j=0;j<8;j+=1){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
    // freopen("input.in", "r", stdin);
    // freopen("output.out", "w", stdout);

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
