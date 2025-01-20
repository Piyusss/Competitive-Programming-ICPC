//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
#define pb push_back
 
vector<pair<char,pair<ll,ll>>>dir={{'R',{0,1}},{'L',{0,-1}},{'U',{-1,0}},{'D',{1,0}}};
vector<vector<ll>>dir2={{0,1},{0,-1},{-1,0},{1,0}};
 
 
//--------------------------------WRITE_HERE-------------------------------------------
ll n,m;
ll EX,EY;
 
 
 
void _144(){
    cin>>n>>m;
 
    vector<string>v;
    for(ll i=1;i<=n;i++){
        string s;
        cin>>s;
        v.pb(s);
    }
 
    ll sx=-1,sy=-1,ex=-1,ey=-1;
    for(ll i=0;i<n;i++){
        for(ll j=0;j<m;j++){
            if(v[i][j]=='A'){
                sx=i;sy=j;
            }
            else if(v[i][j]=='B'){
                ex=i;ey=j;
            }
            else continue;
        }
    }
 
    //now
    EX=ex;EY=ey;
    priority_queue<pair<ll,pair<ll,ll>> ,
    vector<pair<ll,pair<ll,ll>>> , 
    greater<pair<ll,pair<ll,ll>>>>pq;
    pq.push({0,{sx,sy}});
 
    vector<vector<ll>>dis(n,vector<ll>(m,1e9));
    dis[sx][sy]=0;
 
    vector<vector<char>>par(n,vector<char>(m,'X'));
    string goal="RLUD";
 
    while(!pq.empty()){
        ll xc=pq.top().second.first;
        ll yc=pq.top().second.second;
        ll d=pq.top().first;
 
        pq.pop();
 
        for(ll i=0;i<4;i++){
            ll nx=xc+dir[i].second.first;
            ll ny=yc+dir[i].second.second;
 
            if(nx>=0 && nx<n && ny>=0 && ny<m
            && (v[nx][ny]=='.' || v[nx][ny]=='B')){
 
                if(dis[xc][yc]+1<dis[nx][ny]){
                    dis[nx][ny]=dis[xc][yc]+1;
                    pq.push({dis[nx][ny], {nx, ny}});
                    par[nx][ny]=goal[i];
                }
            }
        }
    }
 
    //now
    if(dis[ex][ey]==1e9){
        cout<<"NO";return;
    }
 
    cout<<"YES"<<endl;
    cout<<dis[ex][ey]<<endl;
    
    string ans="";
    ll EX=ex;
    ll EY=ey;
    while(1){
        ans+= (par[ex][ey]);
        if(ans.size()==dis[EX][EY])break;
        if(par[ex][ey]=='U'){
            ex++;
        }
        else if(par[ex][ey]=='D'){
            ex--;
        }
        else if(par[ex][ey]=='R'){
            ey--;
        }
        else{
            ey++;
        }
    }
 
    reverse(ans.begin(),ans.end());
    // cout<<par[2][4];
    cout<<ans;
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
