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
	vector<int> par;
	vector<vector<int>> pow2ends;
	vector<int> depth;

	void process(int at, int prev) {
		depth[at] = depth[prev] + 1;
		for (int n : adjList[at]) {
			if (n != prev) {
				process(n, at);
				par[n] = at;
			}
		}
	}

  public:
	Tree(const vector<int>* adjList, int size)
	    : adjList(adjList), log2dist(ceil(log2(size))), par(size),
	      pow2ends(size, vector<int>(log2dist + 1)), depth(size) {
		par[root] = depth[root] = -1;
		process(root, root);

		for (int n = 0; n < par.size(); n++) { pow2ends[n][0] = par[n]; }
		for (int p = 1; p <= log2dist; p++) {
			for (int n = 0; n < par.size(); n++) {
				int halfway = pow2ends[n][p - 1];
				if (halfway == -1) {
					pow2ends[n][p] = -1;
				} else {
					pow2ends[n][p] = pow2ends[halfway][p - 1];
				}
			}
		}
	}

	/** @return the kth parent of node n */
	int kth_parent(int n, int k) {
		if (k > par.size()) { return -1; }
		int at = n;
		for (int pow = 0; pow <= log2dist; pow++) {
			if ((k & (1 << pow)) != 0) {
				at = pow2ends[at][pow];
				if (at == -1) { break; }
			}
		}
		return at;
	}

	/** @return the LCA of nodes n1 and n2 */
	int lca(int n1, int n2) {
		if (depth[n1] < depth[n2]) { return lca(n2, n1); }
		n1 = kth_parent(n1, depth[n1] - depth[n2]);
		if (n1 == n2) {
			return n2;
		}

		for (int i = log2dist; i >= 0; i--) {
			if (pow2ends[n1][i] != pow2ends[n2][i]) {
				n1 = pow2ends[n1][i];
				n2 = pow2ends[n2][i];
			}
		}
		return pow2ends[n1][0];
	}
    /** @return the distance between n1 and n2. */
    int dist(int n1, int n2)
    {
        return depth[n1] + depth[n2] - 2 * depth[lca(n1, n2)];
    }
};

void _144()
{
    ll n,q;
    cin>>n>>q;

    vector<int>adjList[n];
    for(int i=1;i<=n-1;i+=1){
        ll x;cin>>x;x-=1;
        adjList[x].push_back(i);
        adjList[i].push_back(x);
    }

    Tree tree(adjList,n);

    cout<<tree.dist(0,0);

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
