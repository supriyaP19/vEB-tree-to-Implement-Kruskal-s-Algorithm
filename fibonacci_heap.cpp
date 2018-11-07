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
#include <unordered_map>
#include <stack>
#include <set>
#include <map>
#include <complex>
#include "kruskal.hpp"
#define INF 999999999
using namespace std;
typedef long long lld;
typedef unsigned long long llu;

struct Node_Fibonacci
{
    
    Node_Fibonacci *backward;
    Node_Fibonacci *forward;
    Node_Fibonacci *parent;
    Node_Fibonacci *child;
    int key;
    int from;
    int to;
    bool marked;
    int degree;

    Node_Fibonacci()
    {
        this -> backward =NULL;
        this -> forward =NULL;
        this -> parent =NULL;
        this -> child = NULL;
        this -> key = 0;
        this -> from = 0;
        this -> to = 0;
        this -> marked = false;
        this -> degree = 0;
    }
    
    Node_Fibonacci(int key,int f,int t)
    {
        this -> key = key;
        this -> from = f;
        this -> to =t;
        this -> marked = false;
        this -> degree = 0;
        this -> backward =NULL;
        this -> forward =NULL;
        this -> parent =NULL;
        this -> child = NULL;
    }
};

class Heap
{
    Node_Fibonacci *min;
    int N;
    
public:
    Heap();
    Heap(Node_Fibonacci*);
    bool is_Heap_Empty();
    void insert(Node_Fibonacci*);
    void merge(Heap*);
    Node_Fibonacci* first();
    Node_Fibonacci* extractMin();
    void decreaseKey(Node_Fibonacci*, int);
    void Delete(Node_Fibonacci*);
};

Heap::Heap()
{
    this -> min = NULL;
    this -> N = 0;
}

Heap::Heap(Node_Fibonacci *n)
{
    this -> min = n;
    n -> backward = n -> forward = n;
    n -> parent = n -> child = NULL;
    
    this -> N = 1;
}

bool Heap::is_Heap_Empty()
{
    return (this -> min == NULL);
}

void Heap::insert(Node_Fibonacci *n)
{
    this -> merge(new Heap(n));
}

void Heap::merge(Heap *h)
{
    this -> N = this -> N + h -> N;
    if (h -> is_Heap_Empty())
        return;
    if (this -> is_Heap_Empty())
    {
        this -> min = h -> min;
        return;
    }
    else{
        Node_Fibonacci *first_heap_min = this -> min;
        Node_Fibonacci *first_heap_min_back = this -> min -> backward;
        Node_Fibonacci *second_heap_min = h -> min;
        Node_Fibonacci *second_heap_min_back = h -> min -> backward;
        first_heap_min -> backward = second_heap_min_back;
        first_heap_min_back -> forward = second_heap_min;
        second_heap_min -> backward = first_heap_min_back;
        second_heap_min_back -> forward = first_heap_min;
        if (h -> min -> key < this -> min -> key) this -> min = h -> min;
    }
   
}

Node_Fibonacci* Heap::first()
{
    return this -> min;
}

Node_Fibonacci* Heap::extractMin()
{
    Node_Fibonacci *cur = this -> min;
    this -> N -= 1;
    
    if (cur -> forward == cur)
    {
        this -> min = NULL;
    }
    else
    {
        //removing the minimum node from the heap by changing the links of the previous and backward node of the min node
        Node_Fibonacci *prev_node = cur -> backward;
        Node_Fibonacci *next_node = cur -> forward;
        prev_node-> forward = next_node;
        next_node -> backward = prev_node;
        this -> min = next_node; 
    }
    
    //cur contains the removed minimum node, checking if it has child...
    if (cur -> child != NULL)
    {
        Node_Fibonacci *first_Child_of_min = cur -> child;
        Node_Fibonacci *currChd = first_Child_of_min;
        
        do
        {
            currChd -> parent = NULL;
            currChd = currChd -> forward;
        } while (currChd != first_Child_of_min);
        
        if (this -> is_Heap_Empty())
        {
            this -> min = first_Child_of_min;
        }
        else
        {
            Node_Fibonacci *first_heap_min = this -> min;
            Node_Fibonacci *first_heap_min_back = this -> min -> backward;
            Node_Fibonacci *second_heap_min = first_Child_of_min;
            Node_Fibonacci *second_heap_min_back = first_Child_of_min -> backward;

            first_heap_min -> backward = second_heap_min_back;
            first_heap_min_back -> forward = second_heap_min;
            second_heap_min -> backward = first_heap_min_back;
            second_heap_min_back -> forward = first_heap_min;

            
        }
    }
    
    if (this -> min != NULL)
    {
        int max_degree = 0;
        int size_of_aux_arr = 5 * (((int)log2(this -> N + 1)) + 1);
        Node_Fibonacci *aux_arr[size_of_aux_arr + 1];
        int k=size_of_aux_arr;
        while(k>=0){
             aux_arr[k] = NULL;
             k--;
        }
        
        Node_Fibonacci *current_node = this -> min;
        
        do
        {   
            //traversing all the children of the removed minimum node...
            Node_Fibonacci *next_node = current_node -> forward;
            int degree = current_node -> degree;
            Node_Fibonacci *node1 = current_node;
          
            if(aux_arr[degree] != NULL)
            {
                aux:
                Node_Fibonacci *node2 = aux_arr[degree];
                aux_arr[degree] = NULL;
                
                if (node2 -> key < node1 -> key)
                {
                    Node_Fibonacci *temp_var = node1;
                    node1 = node2;
                    node2 = temp_var;
                }
                
                node2 -> parent = node1;
                if (node1 -> child == NULL)
                {
                    node1 -> child = node2;
                    node2 -> backward = node2 -> forward = node2;
                }
                else
                {
                    Node_Fibonacci *last_node = node1 -> child -> backward;
                    last_node -> forward = node2;
                    node2 -> backward = last_node;
                    node1 -> child -> backward = node2;
                    node2 -> forward = node1 -> child;
                }
                
                degree++;
                node1 -> degree = degree;
                if(aux_arr[degree] != NULL)
                    goto aux;
            }
            aux_arr[degree] = node1;
            if (degree > max_degree) max_degree = degree;
            current_node = next_node;
        } while (current_node != this -> min);
        
        
        Node_Fibonacci *previous = aux_arr[max_degree];
        this -> min = previous;
        for (int i=0;i<=max_degree;i++)
        {
            if (aux_arr[i] != NULL)
            {
                previous -> forward = aux_arr[i];
                aux_arr[i] -> backward = previous;
                if (aux_arr[i] -> key < this -> min -> key) this -> min = aux_arr[i];
                previous = aux_arr[i];
            }
        }
        
    }
    
    return cur;
}



int main()
{
    //implmentation of Kruskal's algorithm using fibonacci heap........
    Heap *fh = new Heap();

    int g_nodes;
    int g_edges;

    cin >> g_nodes >> g_edges;
    

    vector<int> g_from(g_edges);
    vector<int> g_to(g_edges);
    vector<int> g_weight(g_edges);
    multimap<int,pair<int,int>>map_of_edge;
    

    
    for (int i = 0; i < g_edges; i++) {
        
        cin >> g_from[i] >> g_to[i] >> g_weight[i];
        
        if(map_of_edge.find(g_weight[i])==map_of_edge.end()){
            fh -> insert(new Node_Fibonacci(g_weight[i],g_from[i],g_to[i]));
        }
        //inserting the weight in the temporary unoredered map if it's the first time this edge is encountered else inserting the multimap to handle duplicates
        pair<int,int>from_to = make_pair(g_from[i],g_to[i]);
        map_of_edge.insert({g_weight[i], from_to});
       // map_of_edge.insert({g_weight[i],new_e});
        
        
       
    }
    
    multimap<int,pair<int,int>>::iterator mul_itr;
    // checking the insertion in multimap-----------------------------------------------------
    // for(mul_itr=map_of_edge.begin();mul_itr!=map_of_edge.end();++mul_itr){

    //     cout<<" weight: "<<mul_itr->first<<" ";
    //     cout<<" u and v: "<<(mul_itr->second).first<<","<<(mul_itr->second).second<<endl;
    // }
    //----------------------------------------------------------------------------------------

    //sorting using the extract minimum operation of fibonacci heap..
    int y=0;
    struct edges new_e[g_edges+1];
    while (!fh -> is_Heap_Empty())
    {
        int x =  fh -> extractMin() -> key;

        
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

   
    return 0;
}
