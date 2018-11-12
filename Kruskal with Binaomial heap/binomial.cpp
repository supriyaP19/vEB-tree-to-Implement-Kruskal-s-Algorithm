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

struct BinomialNode
{
    int key;
    int degree;
    BinomialNode *forward;
    BinomialNode *parent;
    BinomialNode *child;
    int  from;
    int to;
    
    BinomialNode()
    {
        this -> key = 0;
        this -> degree = 0;
        this -> forward = this -> parent = this -> child = NULL;
        int from = 0;
        int to = 0;
    }
    
    BinomialNode(int key,int from,int to)
    {
        this -> key = key;
        this -> from = from;
        this -> to = to;
        this -> degree = 0;
        this -> forward = this -> parent = this -> child = NULL;
    }
};

class BinomialHeap
{
    BinomialNode *roots;
    BinomialNode *min;
    void linkTrees(BinomialNode*, BinomialNode*);
    BinomialNode* merge_heap_roots(BinomialHeap*, BinomialHeap*);
    
public:
    BinomialHeap();
    BinomialHeap(BinomialNode*);
    bool is_heap_empty();
    void insert_bin(BinomialNode*);
    void merge_heap(BinomialHeap*);
    BinomialNode* first();
    BinomialNode* extractMin();
    void decreaseKey(BinomialNode*, int);
    void Delete(BinomialNode*);
};

BinomialHeap::BinomialHeap()
{
    this -> roots = NULL;
}

BinomialHeap::BinomialHeap(BinomialNode *x)
{
    this -> roots = x;
}

bool BinomialHeap::is_heap_empty()
{
    return (this -> roots == NULL);
}

void BinomialHeap::insert_bin(BinomialNode *x)
{
    this -> merge_heap(new BinomialHeap(x));
}

void BinomialHeap::linkTrees(BinomialNode *y, BinomialNode *z)
{
    // Precondition: y -> key >= z -> key
    y -> parent = z;
    y -> forward = z -> child;
    z -> child = y;
    z -> degree = z -> degree + 1;
}

BinomialNode* BinomialHeap::merge_heap_roots(BinomialHeap *x, BinomialHeap *y)
{
    BinomialNode *ret = new BinomialNode();
    BinomialNode *end = ret;
    
    BinomialNode *L = x -> roots;
    BinomialNode *R = y -> roots;
    if (L == NULL) return R;
    if (R == NULL) return L;
    while (L != NULL || R != NULL)
    {
        if (L == NULL)
        {
            end -> forward = R;
            end = end -> forward;
            R = R -> forward;
        }
        else if (R == NULL)
        {
            end -> forward = L;
            end = end -> forward;
            L = L -> forward;
        }
        else
        {
            if (L -> degree < R -> degree)
            {
                end -> forward = L;
                end = end -> forward;
                L = L -> forward;
            }
            else
            {
                end -> forward = R;
                end = end -> forward;
                R = R -> forward;
            }
        }
    }
    return (ret -> forward);
}

void BinomialHeap::merge_heap(BinomialHeap *bh)
{
    BinomialHeap *H = new BinomialHeap();
    H -> roots = merge_heap_roots(this, bh);
    
    if (H -> roots == NULL)
    {
        this -> roots = NULL;
        this -> min = NULL;
        return;
    }
    
    BinomialNode *prevX = NULL;
    BinomialNode *x = H -> roots;
    BinomialNode *nextX = x -> forward;
    while (nextX != NULL)
    {
        if (x -> degree != nextX -> degree || (nextX -> forward != NULL && nextX -> forward -> degree == x -> degree))
        {
            prevX = x;
            x = nextX;
        }
        else if (x -> key <= nextX -> key)
        {
            x -> forward = nextX -> forward;
            linkTrees(nextX, x);
        }
        else
        {
            if (prevX == NULL) H -> roots = nextX;
            else prevX -> forward = nextX;
            linkTrees(x, nextX);
            x = nextX;
        }
        nextX = x -> forward;
    }
    
    this -> roots = H -> roots;
    this -> min = H -> roots;
    BinomialNode *cur = this -> roots;
    while (cur != NULL)
    {
        if (cur -> key < this -> min -> key) this -> min = cur;
        cur = cur -> forward;
    }
}

BinomialNode* BinomialHeap::first()
{
    return this -> min;
}

BinomialNode* BinomialHeap::extractMin()
{
    BinomialNode *ret = this -> first();
    
    // delete ret from the list of roots
    BinomialNode *prevX = NULL;
    BinomialNode *x = this -> roots;
    while (x != ret)
    {
        prevX = x;
        x = x -> forward;
    }
    if (prevX == NULL) this -> roots = x -> forward;
    else prevX -> forward = x -> forward;
    
    // reverse the list of ret's children
    BinomialNode *revChd = NULL;
    BinomialNode *cur = ret -> child;
    while (cur != NULL)
    {
        BinomialNode *next = cur -> forward;
        cur -> forward = revChd;
        revChd = cur;
        cur = next;
    }
    
    // merge_heap the two lists
    BinomialHeap *H = new BinomialHeap();
    H -> roots = revChd;
    this -> merge_heap(H);
    
    return ret;
}

void BinomialHeap::decreaseKey(BinomialNode *x, int newKey)
{
    // Precondition: x -> key > newKey
    x -> key = newKey;
    BinomialNode *y = x;
    BinomialNode *z = y -> parent;
    while (z != NULL && y -> key < z -> key)
    {
        // swap contents
        swap(y -> key, z -> key);
        
        y = z;
        z = y -> parent;
    }
    
    if (y -> key < this -> min -> key) this -> min = y;
}

void BinomialHeap::Delete(BinomialNode *x)
{
    decreaseKey(x, -INF);
    extractMin();
}

int main()
{    srand(time(0));
    BinomialHeap *bh = new BinomialHeap();
    
    // BinomialNode *x = new BinomialNode(11);
    // BinomialNode *y = new BinomialNode(5);
    
    // bh -> insert_bin(x);
    // bh -> insert_bin(y);
    // bh -> insert_bin(new BinomialNode(3));
    // bh -> insert_bin(new BinomialNode(8));
    // bh -> insert_bin(new BinomialNode(4));
    
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
            bh -> insert_bin(new BinomialNode(g_weight[i],g_from[i],g_to[i]));
        }
        //inserting the weight in the temporary unoredered map if it's the first time this edge is encountered else inserting the multimap to handle duplicates
        pair<int,int>from_to = make_pair(g_from[i],g_to[i]);
        map_of_edge.insert({g_weight[i], from_to});
       // map_of_edge.insert_bin({g_weight[i],new_e});
        
        
       
    }

    multimap<int,pair<int,int>>::iterator mul_itr;

    int y=0;
    struct edges new_e[g_edges+1];
    while (!bh -> is_heap_empty())
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