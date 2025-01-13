void dfs(ll node, ll p)
{   st[node].insert(val[node]);

    for(auto &c:g[node]){
        if(c!=p){
            dfs(c,node);
            if(st[node].size()<st[c].size()) swap(st[node],st[c]);
            for(auto &it:st[c]) st[node].insert(it);
        }
    }

    res[node]=st[node].size();
}
