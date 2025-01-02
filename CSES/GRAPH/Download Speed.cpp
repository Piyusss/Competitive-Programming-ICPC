//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------
struct flow_network {

    struct edge {
        ll u, v, cap;
        edge *rev;
        bool forward;
        edge(ll _u, ll _v, ll _cap, bool forw)
            : u(_u), v(_v), cap(_cap), forward(forw) {}
    };

    ll n;
    vector<vector<edge*> > adj;
    flow_network(ll _n) : n(_n), adj(_n) {}

    void add_edge(ll u, ll v, ll cap) {
        edge *e = new edge(u, v, cap, true);
        edge *rev = new edge(v, u, 0, false);
        e->rev = rev;
        rev->rev = e;
        adj[u].push_back(e);
        adj[v].push_back(rev);
    }

    ll augment(ll s, ll t) {
        vector<edge*> back(n, (edge*)0);
        queue<int> Q;
        Q.push(s);
        back[s] = (edge*)1;
        while (!Q.empty()) {
            ll u = Q.front(); Q.pop();
            for (ll i = 0; i < adj[u].size(); i++) {
                ll v = adj[u][i]->v;
                if (back[v] == NULL && adj[u][i]->cap > 0) {
                    back[v] = adj[u][i];
                    Q.push(v);
                }
            }
        }

        if (back[t] == NULL)
            return 0;

        stack<edge*> S;
        S.push(back[t]);
        ll bneck = back[t]->cap;
        while (S.top()->u != s) {
            S.push(back[S.top()->u]);
            bneck = min(bneck, S.top()->cap);
        }

        while (!S.empty()) {
            S.top()->cap -= bneck;
            S.top()->rev->cap += bneck;
            S.pop();
        }

        return bneck;
    }

    ll max_flow(ll source, ll sink) {
        ll flow = 0;
        while (1) {
            ll f = augment(source, sink);
            if (f == 0) break;
            flow += f;
        }
        return flow;
    }
};


void _144()
{
    ll n,m;
    cin>>n>>m;

    flow_network net(n);

    for(ll i=0;i<m;i+=1){
        ll a,b,c;
        cin>>a>>b>>c;

        net.add_edge(--a,--b,c);
    }

    cout<<net.max_flow(0,n-1);

    return;
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
