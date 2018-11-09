#include<iostream>
#include "veb.hpp"
#include "kruskal.hpp"
#include <map>

typedef long long ll;

using namespace std;

int main()
{
    //implmentation of Kruskal's algorithm using vEB tree........

    ll N;
    cout<<"enter the max range of edges: ";
    cin>>N;
    srand(time(0));
    vEB * vebtree = new vEB (N);

    ll g_nodes;
    ll g_edges;

    cin >> g_nodes >> g_edges;
    

    vector<ll> g_from(g_edges);
    vector<ll> g_to(g_edges);
    vector<ll> g_weight(g_edges);
    multimap<long long,pair<long long,long long>>map_of_edge;
    

    
    for (ll i = 0; i < g_edges; i++) {
        
        cin >> g_from[i] >> g_to[i] >> g_weight[i];
        
        if(map_of_edge.find(g_weight[i])==map_of_edge.end()){
            insert(vebtree, g_weight[i], g_from[i], g_to[i]);
        }
        pair<ll,ll>from_to = make_pair(g_from[i],g_to[i]);
        map_of_edge.insert({g_weight[i], from_to});
        
        
       
    }
    
    multimap<ll,pair<ll,ll>>::iterator mul_itr;
    // checking the insertion in multimap-----------------------------------------------------
    // for(mul_itr=map_of_edge.begin();mul_itr!=map_of_edge.end();++mul_itr){

    //     cout<<" weight: "<<mul_itr->first<<" ";
    //     cout<<" u and v: "<<(mul_itr->second).first<<","<<(mul_itr->second).second<<endl;
    // }
    //----------------------------------------------------------------------------------------

    //sorting using the extract minimum operation of fibonacci heap..
    ll y=0;
    struct edges new_e[g_edges+1];
    clock_t t;
    t=clock();
    while (tree_min(vebtree))
    {
        ll x =  extract_min(vebtree) -> weight;

        
        //sorting the structure of graph nodes along with handling the duplicates------------------------------------------------
        pair<multimap<ll,pair<ll,ll>>::iterator,multimap<ll,pair<ll,ll>>::iterator> ret;
        ret = map_of_edge.equal_range(x);
        
        for(multimap<ll,pair<ll,ll>>::iterator it=ret.first;it!=ret.second;++it){
            new_e[y].weight = x;
            new_e[y].from = (it->second).first;
            new_e[y].to = (it->second).second;
            y++;
            // cout<<" ("<<(it->second).first<<","<<(it->second).second<<")";
        }
        // cout<<endl;

        
     
       
    }




    //actual logic of kruskal to find the weight of MST using union operation
    cout<<kruskal(new_e,g_edges,g_nodes)<<endl;
    t=clock()-t;

    double time_taken1 = ((double) t) / CLOCKS_PER_SEC;
    cout<<(fixed)<<"time taken is : "<<time_taken1<<endl;
   
    return 0;
}
