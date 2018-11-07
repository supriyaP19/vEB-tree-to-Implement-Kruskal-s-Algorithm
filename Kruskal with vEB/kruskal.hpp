//#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>
using namespace std;
typedef long long ll;




struct edges{
    ll from;
    ll to;
    ll weight;
};

ll kruskal(struct edges *e,ll g_edges,ll g_nodes);
void union1(ll a,ll b);
ll find(ll x);
void initialize(ll n);
bool compare(struct edges a,struct edges b);
