
//Kruskal (MST): Really Special Subtree - HACKERRANK
//Problem statement - https://www.hackerrank.com/challenges/kruskalmstrsub/problem - equivalent to kruskal except that same length ede cant be included twice.
#include "kruskal.hpp"
int parent[100000000];
int ranking[100000000];

void initialize(int n){
    for(int i=1;i<=n;i++){
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
        int x = a.weight + a.from + a.to;
        int y = b.weight + b.from + b.to;
            
        if(x<y)
            return true;
        else 
            return false;

        }
}


int find(int x){
    int u;
    if(parent[x]==x)
        return x;
    else 
        return parent[x]=find(parent[x]);
}


void union1(int a,int b){
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

        



int kruskal(struct edges *e,int g_edges,int g_nodes)
{

    initialize(g_nodes);
    //sort(e,e+g_edges,compare);
    int mst_wt=0;
    for(int i=0;i<g_edges;i++){
        int u = e[i].from;
        int v = e[i].to;

        u = parent[u];
        v = parent[v];
        parent[e[i].from]=u;
        parent[e[i].to]=v;
        
        if(u!=v){
           mst_wt+=e[i].weight;

           union1(u,v);
        }       
    }
    return mst_wt;
}
