#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>
#include "kruskal.hpp"
#define INF 987654321
#define MAX_N 100002
using namespace std;
typedef long long lld;
typedef unsigned long long llu;

struct BinNode
{
    int key;
    int degree;
    BinNode *f, *p, *c;
    int  from;
    int to;
    
    BinNode()
    {
        this -> key = 0;
        this -> degree = 0;
        this -> f = this -> p = this -> c = NULL;
        int from = 0;
        int to = 0;
    }
    
    BinNode(int key,int from,int to)
    {
        this -> key = key;
        this -> from = from;
        this -> to = to;
        this -> degree = 0;
        this -> f = this -> p = this -> c = NULL;
    }
};

class BinHeap
{
    BinNode *roots;
    BinNode *min;
    void linkTrees(BinNode*, BinNode*);
    BinNode* mergeRoots(BinHeap*, BinHeap*);
    
public:
    BinHeap();
    BinHeap(BinNode*);
    bool isEmpty();
    void insert(BinNode*);
    void merge(BinHeap*);
    BinNode* first();
    BinNode* extractMin();
    void decreaseKey(BinNode*, int);
    void Delete(BinNode*);
};

BinHeap::BinHeap()
{
    this -> roots = NULL;
}

BinHeap::BinHeap(BinNode *x)
{
    this -> roots = x;
}

bool BinHeap::isEmpty()
{
    return (this -> roots == NULL);
}

void BinHeap::insert(BinNode *x)
{
    this -> merge(new BinHeap(x));
}

void BinHeap::linkTrees(BinNode *y, BinNode *z)
{
    // Precondition: y -> key >= z -> key
    y -> p = z;
    y -> f = z -> c;
    z -> c = y;
    z -> degree = z -> degree + 1;
}

BinNode* BinHeap::mergeRoots(BinHeap *x, BinHeap *y)
{
    BinNode *ret = new BinNode();
    BinNode *end = ret;
    
    BinNode *L = x -> roots;
    BinNode *R = y -> roots;
    if (L == NULL) return R;
    if (R == NULL) return L;
    while (L != NULL || R != NULL)
    {
        if (L == NULL)
        {
            end -> f = R;
            end = end -> f;
            R = R -> f;
        }
        else if (R == NULL)
        {
            end -> f = L;
            end = end -> f;
            L = L -> f;
        }
        else
        {
            if (L -> degree < R -> degree)
            {
                end -> f = L;
                end = end -> f;
                L = L -> f;
            }
            else
            {
                end -> f = R;
                end = end -> f;
                R = R -> f;
            }
        }
    }
    return (ret -> f);
}

void BinHeap::merge(BinHeap *bh)
{
    BinHeap *H = new BinHeap();
    H -> roots = mergeRoots(this, bh);
    
    if (H -> roots == NULL)
    {
        this -> roots = NULL;
        this -> min = NULL;
        return;
    }
    
    BinNode *prevX = NULL;
    BinNode *x = H -> roots;
    BinNode *nextX = x -> f;
    while (nextX != NULL)
    {
        if (x -> degree != nextX -> degree || (nextX -> f != NULL && nextX -> f -> degree == x -> degree))
        {
            prevX = x;
            x = nextX;
        }
        else if (x -> key <= nextX -> key)
        {
            x -> f = nextX -> f;
            linkTrees(nextX, x);
        }
        else
        {
            if (prevX == NULL) H -> roots = nextX;
            else prevX -> f = nextX;
            linkTrees(x, nextX);
            x = nextX;
        }
        nextX = x -> f;
    }
    
    this -> roots = H -> roots;
    this -> min = H -> roots;
    BinNode *cur = this -> roots;
    while (cur != NULL)
    {
        if (cur -> key < this -> min -> key) this -> min = cur;
        cur = cur -> f;
    }
}

BinNode* BinHeap::first()
{
    return this -> min;
}

BinNode* BinHeap::extractMin()
{
    BinNode *ret = this -> first();
    
    // delete ret from the list of roots
    BinNode *prevX = NULL;
    BinNode *x = this -> roots;
    while (x != ret)
    {
        prevX = x;
        x = x -> f;
    }
    if (prevX == NULL) this -> roots = x -> f;
    else prevX -> f = x -> f;
    
    // reverse the list of ret's children
    BinNode *revChd = NULL;
    BinNode *cur = ret -> c;
    while (cur != NULL)
    {
        BinNode *next = cur -> f;
        cur -> f = revChd;
        revChd = cur;
        cur = next;
    }
    
    // merge the two lists
    BinHeap *H = new BinHeap();
    H -> roots = revChd;
    this -> merge(H);
    
    return ret;
}

void BinHeap::decreaseKey(BinNode *x, int newKey)
{
    // Precondition: x -> key > newKey
    x -> key = newKey;
    BinNode *y = x;
    BinNode *z = y -> p;
    while (z != NULL && y -> key < z -> key)
    {
        // swap contents
        swap(y -> key, z -> key);
        
        y = z;
        z = y -> p;
    }
    
    if (y -> key < this -> min -> key) this -> min = y;
}

void BinHeap::Delete(BinNode *x)
{
    decreaseKey(x, -INF);
    extractMin();
}

int main()
{    srand(time(0));
    BinHeap *bh = new BinHeap();
    
    // BinNode *x = new BinNode(11);
    // BinNode *y = new BinNode(5);
    
    // bh -> insert(x);
    // bh -> insert(y);
    // bh -> insert(new BinNode(3));
    // bh -> insert(new BinNode(8));
    // bh -> insert(new BinNode(4));
    
    // bh -> decreaseKey(x, 2);

    int g_nodes;
    int g_edges;

    cin >> g_nodes >> g_edges;
    

    vector<int> g_from(g_edges);
    vector<int> g_to(g_edges);
    vector<int> g_weight(g_edges);
    multimap<int,pair<int,int>>map_of_edge;


    clock_t t;
    t=clock();
    for (int i = 0; i < g_edges; i++) {
        
        cin >> g_from[i] >> g_to[i] >> g_weight[i];
        
        if(map_of_edge.find(g_weight[i])==map_of_edge.end()){
            bh -> insert(new BinNode(g_weight[i],g_from[i],g_to[i]));
        }
        //inserting the weight in the temporary unoredered map if it's the first time this edge is encountered else inserting the multimap to handle duplicates
        pair<int,int>from_to = make_pair(g_from[i],g_to[i]);
        map_of_edge.insert({g_weight[i], from_to});
       // map_of_edge.insert({g_weight[i],new_e});
        
        
       
    }

    multimap<int,pair<int,int>>::iterator mul_itr;

    int y=0;
    struct edges new_e[g_edges+1];
    while (!bh -> isEmpty())
    {
        int x = bh -> extractMin() -> key;

        //sorting the structure of graph nodes along with handling the duplicates------------------------------------------------
        pair<multimap<int,pair<int,int>>::iterator,multimap<int,pair<int,int>>::iterator> ret;
        ret = map_of_edge.equal_range(x);
        
        for(multimap<int,pair<int,int>>::iterator it=ret.first;it!=ret.second;++it){
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