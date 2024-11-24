//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
//--------------------------------WRITE_HERE-------------------------------------------
 
 
class Tree {
  private:
	const int root = 0;
 
	const vector<int>* adjList;
	const int log2dist;
	vector<vector<int>> pow2ends;
	vector<int> depth;
 
  public:
	Tree(const vector<int>* adjList, int size,vector<int>&next)
	    : adjList(adjList), log2dist(ceil(log2(size))),
	      pow2ends(size, vector<int>(log2dist + 1)), depth(size) {
 
		for (int n = 0; n < next.size(); n++) { pow2ends[n][0] = next[n]; }
		for (int p = 1; p <= log2dist; p++) {
			for (int n = 0; n < next.size(); n++) {
				int halfway = pow2ends[n][p - 1];
                pow2ends[n][p] = pow2ends[halfway][p - 1];
            }
		}
	}
 
	/** @return the kth parent of node n */
	int kth_parent(int n, int k) {
		for (int pow = 0; pow <= log2dist; pow++) {
			if ((k & (1 << pow)) != 0) {
				n = pow2ends[n][pow];
			}
		}
		return n;
	}
 
    vector<vector<int>> getPow2Ends(){
        return pow2ends;
    }
    int getlog2(){
        return log2dist;
    }
};
 
void _144()
{
    ll n,q;
    cin>>n>>q;
 
    vector<int>adjList[n];
    vector<int>next(n);
    for(int i=0;i<n;i+=1){
        ll x;cin>>x;--x;
        next[i]=x;
        adjList[x].push_back(i);
    }
 
    Tree tree(adjList,n,next);
 
    vector<int>cycle_id(n,-2);
    vector<map<int, int>> cycles;
    for (int p = 0; p < n; p++)
    {
        if (cycle_id[p] != -2)
        {
            continue;
        }
        vector<int> path{p};
        int at = p;
        while (cycle_id[next[at]] == -2)
        {
            at = next[at];
            cycle_id[at] = -3;
            path.push_back(at);
        }
 
        map<int, int> cycle;
        bool in_cycle = false;
        for (int i : path)
        {
            in_cycle = in_cycle || i == next[at];
            if (in_cycle)
            {
                cycle[i] = cycle.size();
            }
            cycle_id[i] = in_cycle ? cycles.size() : -1;
        }
        cycles.push_back(cycle);
    }
 
    vector<int> cyc_dist(n);
    for (int p = 0; p < n; p++)
    {
        if (cycle_id[next[p]] == -1 || cycle_id[p] != -1)
        {
            continue;
        }
        cyc_dist[p] = 1;
        vector<int> stack(adjList[p]);
        while (!stack.empty())
        {
            int curr = stack.back();
            stack.pop_back();
            cyc_dist[curr] = cyc_dist[next[curr]] + 1;
            stack.insert(stack.end(), adjList[curr].begin(), adjList[curr].end());
        }
    }
 
    vector<vector<int>>pow2end=tree.getPow2Ends();
    int LOG2=tree.getlog2();
    while(q--){
        ll u,v;
        cin>>u>>v;
 
        u--;v--;
 
        if (cycle_id[pow2end[u][LOG2]] != cycle_id[pow2end[v][LOG2]])
        {
            cout<<"-1"<<endl;continue;
        }
 
        if(cycle_id[u]!=-1 || cycle_id[v]!=-1){
            if(cycle_id[v]==-1 && cycle_id[u]!=-1){
                cout<<"-1"<<endl;continue;
            }
 
            int dist=cyc_dist[u];
            int u_cyc=tree.kth_parent(u,dist);
            map<int,int>&cyc=cycles[cycle_id[u_cyc]];
            int u_idx=cyc[u_cyc];
            int v_idx=cyc[v];
            if(v_idx>=u_idx){
                cout<<v_idx-u_idx+dist<<endl;continue;
            }
            else{
                cout<<cyc.size()-(u_idx-v_idx)+dist<<endl;continue;
            }
        }
 
        else{
            if(cyc_dist[v]>cyc_dist[u]){
                cout<<"-1"<<endl;continue;
            }
            else{
                int difDist=cyc_dist[u]-cyc_dist[v];
                int liftUpUNode=tree.kth_parent(u,difDist);
                if(liftUpUNode==v){
                    cout<<difDist<<endl;continue;
                }
                else{
                    cout<<"-1"<<endl;continue;
                }
            }
        }
    }
 
    return;
}
 
//--------------------------------END--------------------------------------------------
 
// Main
int main()
{
	//freopen("input.in", "r", stdin);
	//freopen("output.out", "w", stdout);
 
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
