//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------
class TarjanSolver {
  private:
	vector<vector<int>> rev_adj;
	vector<int> post;
	vector<int> comp;

	vector<bool> visited;
	int timer = 0;
	int id = 0;

	void fill_post(int at) {
		visited[at] = true;
		for (int n : rev_adj[at]) {
			if (!visited[n]) { fill_post(n); }
		}
		post[at] = timer++;
	}

	void find_comp(int at) {
		visited[at] = true;
		comp[at] = id;
		for (int n : adj[at]) {
			if (!visited[n]) { find_comp(n); }
		}
	}

  public:
	const vector<vector<int>> &adj;
	TarjanSolver(const vector<vector<int>> &adj)
	    : adj(adj), rev_adj(adj.size()), post(adj.size()), comp(adj.size()),
	      visited(adj.size()) {
		vector<int> nodes(adj.size());
		for (int n = 0; n < adj.size(); n++) {
			nodes[n] = n;
			for (int next : adj[n]) { rev_adj[next].push_back(n); }
		}

		for (int n = 0; n < adj.size(); n++) {
			if (!visited[n]) { fill_post(n); }
		}
		sort(nodes.begin(), nodes.end(),
		          [&](int n1, int n2) { return post[n1] > post[n2]; });

		visited.assign(adj.size(), false);
		for (int n : nodes) {
			if (!visited[n]) {
				find_comp(n);
				id++;
			}
		}
	}

	int tot_sccs() const { return id; }

	int get_comp_id(int n) const { return comp[n]; }
};

struct Clause{
    bool neg1;
    int var1;
    bool neg2;
    int var2;
};

vector<int>_2SATsolver(vector<Clause>&clauses,int vars){
    vector<vector<int>>adj(2*vars);

    //Construct-Implication-Graph
    for(auto &c:clauses){
        adj[2*c.var1+!(c.neg1)].push_back(2*c.var2+(c.neg2));
        adj[2*c.var2+!(c.neg2)].push_back(2*c.var1+(c.neg1));
    }

    //Apply-SCC's-Logic(Tarjan since 2-SAT)
    TarjanSolver sccData(adj);

    vector<vector<ll>> comps(sccData.tot_sccs());
    for(int i=0;i<2*vars;i+=2){
        if(sccData.get_comp_id(i)==sccData.get_comp_id(i+1)) return {};
        comps[sccData.get_comp_id(i)].push_back(i);
        comps[sccData.get_comp_id(i + 1)].push_back(i + 1);
    }

    vector<int>val(2*vars,-1);
    for(auto &comp:comps){
        ll set_to=1;
        for(auto &v:comp){
            ll neg=v%2==1 ? v-1 : v+1;
            if(val[neg]!=-1){
                set_to=!val[neg];
                break;
            }
        }
        for(auto v:comp) val[v]=set_to;
    }


    vector<int>actual_val(vars);
    for(int i=0;i<vars;i+=1) actual_val[i]=val[2*i];
    return actual_val;

}


void _144()
{
    ll n,m;
    cin>>n>>m;

    vector<Clause>clauses(n);
    for(auto &c:clauses){
        char neg1,neg2;
        int var1,var2;
        cin >> neg1 >> var1 >> neg2 >> var2;

        var1-=1; var2-=1;

        c.var1=var1;c.var2=var2;
        c.neg1=(neg1=='-');c.neg2=(neg2=='-');
        
    }

    vector<int>res=_2SATsolver(clauses,m);
    if(res.empty()){
        cout<<"IMPOSSIBLE";
        return;
    }
    
    for(int i=0;i<m;i+=1){
        if(res[i]){
            cout<<"+"<<" ";
        }
        else{
            cout<<"-"<<" ";
        }
    }

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
