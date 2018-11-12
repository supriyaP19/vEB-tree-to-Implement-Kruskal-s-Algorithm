
//Kruskal (MST): Really Special Subtree - HACKERRANK
//Problem statement - https://www.hackerrank.com/challenges/kruskalmstrsub/problem - equivalent to kruskal except that same length ede cant be included twice.
#include "kruskal.hpp"


ll parent[100000000];
ll ranking[100000000];

void initialize(ll n){
    for(ll i=1;i<=n;i++){
        // parent.push_back(i);
        // ranking.push_back(0);
        parent[i]=i;

        ranking[i]=0;
    }
}

bool compare(struct edges a,struct edges b){
    if(a.weight<b.weight)
        return true;
    else if(b.weight<a.weight)
        return false;
    else{

        ll x = a.weight + a.from + a.to;
        ll y = b.weight + b.from + b.to;
            
        if(x<y)
            return true;
        else 
            return false;

        }
}



ll find(ll x){
//    ll u;
    if(parent[x]==x)
        return x;
    else 
        return parent[x]=find(parent[x]);
}




void union1(ll a,ll b){
    a=find(a);
    b=find(b);
    
    if(ranking[a]==ranking[b]){

        parent[a]=b;
        ranking[b]++;
    
    }
    else if(ranking[a]>ranking[b]){
        parent[b]=a;
        ranking[a]++;
        
    }
    else{
        parent[a]=b;
        ranking[b]++;
    }

}

        



ll kruskal(struct edges *e,ll g_edges,ll g_nodes)
{


    // for (lld i=0;i<g_edges;i++){
    //     cout<<e[i].weight<<" ";
    // }
    // cout<<endl;
    initialize(g_nodes);
    //sort(e,e+g_edges,compare);
    ll mst_wt=0;
    for(ll i=0;i<g_edges;i++){
        ll u = e[i].from;
        ll v = e[i].to;

        
        u = find(u);
        v = find(v);
        if(u!=v){
           mst_wt+=e[i].weight;

           union1(u,v);
   
        }       
    }
    return mst_wt;
}
