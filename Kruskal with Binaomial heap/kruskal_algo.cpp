
//Kruskal (MST): Really Special Subtree - HACKERRANK
//Problem statement - https://www.hackerrank.com/challenges/kruskalmstrsub/problem - equivalent to kruskal except that same length ede cant be included twice.
#include "kruskal.hpp"
<<<<<<< HEAD:kruskal_algo.cpp
lld parent[100000000];
lld ranking[100000000];

void initialize(lld n){
    for(lld i=1;i<=n;i++){
=======

ll parent[100000000];
ll ranking[100000000];

void initialize(ll n){
    for(ll i=1;i<=n;i++){
>>>>>>> 7c24e157188f31bfe1a0a4b9e7ceee08ec5ace8a:Kruskal with Binaomial heap/kruskal_algo.cpp
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
<<<<<<< HEAD:kruskal_algo.cpp
        lld x = a.weight + a.from + a.to;
        lld y = b.weight + b.from + b.to;
=======
        ll x = a.weight + a.from + a.to;
        ll y = b.weight + b.from + b.to;
>>>>>>> 7c24e157188f31bfe1a0a4b9e7ceee08ec5ace8a:Kruskal with Binaomial heap/kruskal_algo.cpp
            
        if(x<y)
            return true;
        else 
            return false;

        }
}


<<<<<<< HEAD:kruskal_algo.cpp
lld find(lld x){
    lld u;
=======
ll find(ll x){
//    ll u;
>>>>>>> 7c24e157188f31bfe1a0a4b9e7ceee08ec5ace8a:Kruskal with Binaomial heap/kruskal_algo.cpp
    if(parent[x]==x)
        return x;
    else 
        return parent[x]=find(parent[x]);
}


<<<<<<< HEAD:kruskal_algo.cpp
void union1(lld a,lld b){
=======

void union1(ll a,ll b){
>>>>>>> 7c24e157188f31bfe1a0a4b9e7ceee08ec5ace8a:Kruskal with Binaomial heap/kruskal_algo.cpp
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

        



<<<<<<< HEAD:kruskal_algo.cpp
lld kruskal(struct edges *e,lld g_edges,lld g_nodes)
=======
ll kruskal(struct edges *e,ll g_edges,ll g_nodes)
>>>>>>> 7c24e157188f31bfe1a0a4b9e7ceee08ec5ace8a:Kruskal with Binaomial heap/kruskal_algo.cpp
{


    // for (lld i=0;i<g_edges;i++){
    //     cout<<e[i].weight<<" ";
    // }
    // cout<<endl;
    initialize(g_nodes);
    //sort(e,e+g_edges,compare);
<<<<<<< HEAD:kruskal_algo.cpp
    lld mst_wt=0;
    for(lld i=0;i<g_edges;i++){
        lld u = e[i].from;
        lld v = e[i].to;

        u = find(u);
        v = find(v);
=======
    ll mst_wt=0;
    for(ll i=0;i<g_edges;i++){
        ll u = e[i].from;
        ll v = e[i].to;

>>>>>>> 7c24e157188f31bfe1a0a4b9e7ceee08ec5ace8a:Kruskal with Binaomial heap/kruskal_algo.cpp
        
        u = find(u);
        v = find(v);
        if(u!=v){
           mst_wt+=e[i].weight;

           union1(u,v);
   
        }       
    }
    return mst_wt;
}
