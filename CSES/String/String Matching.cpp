//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

vector<int>compute_pi(string &s)
{
    int n=s.size();
    vector<int>pi(n);

    for(int i=1,j=0;i<n;i++){
        while(j>0 && s[j] != s[i]){
            j=pi[j-1];
        }
        if(s[i]==s[j]){
            j++;
        }

        pi[i]=j;
    }

    return pi;
}

void _144()
{
    string s,p;
    cin>>s>>p;

    int res=0;
    string big=p+'#'+s;
    vector<int>pi=compute_pi(big);

    for(auto &it:pi){
        if(it==p.size()){
            res++;
        }
    }

    cout<<res;
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
    // cin >> t;
    while (t--)
    {
        _144();
    }
}
