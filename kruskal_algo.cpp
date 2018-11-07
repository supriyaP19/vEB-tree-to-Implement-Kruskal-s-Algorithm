
//Kruskal (MST): Really Special Subtree - HACKERRANK
//Problem statement - https://www.hackerrank.com/challenges/kruskalmstrsub/problem - equivalent to kruskal except that same length ede cant be included twice.
#include "kruskal.hpp"
lld parent[100000000];
lld ranking[100000000];

void initialize(lld n){
    for(lld i=1;i<=n;i++){
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
        lld x = a.weight + a.from + a.to;
        lld y = b.weight + b.from + b.to;
            
        if(x<y)
            return true;
        else 
            return false;

        }
}


lld find(lld x){
    lld u;
    if(parent[x]==x)
        return x;
    else 
        return parent[x]=find(parent[x]);
}


void union1(lld a,lld b){
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

        



lld kruskal(struct edges *e,lld g_edges,lld g_nodes)
{


    // for (lld i=0;i<g_edges;i++){
    //     cout<<e[i].weight<<" ";
    // }
    // cout<<endl;
    initialize(g_nodes);
    //sort(e,e+g_edges,compare);
    lld mst_wt=0;
    for(lld i=0;i<g_edges;i++){
        lld u = e[i].from;
        lld v = e[i].to;

        u = find(u);
        v = find(v);
        
        if(u!=v){
           mst_wt+=e[i].weight;

           union1(u,v);
        }       
    }
    return mst_wt;
}
