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
#define INF 999999999
using namespace std;
typedef long long lld;
typedef unsigned long long llu;

int parent[100000000];
int ranking[100000000];


struct edges{
    int from;
    int to;
    int weight;
};

void initialize(int n){
    for(int i=1;i<=n;i++){
        // parent.push_back(i);
        // ranking.push_back(0);
        parent[i]=i;

        ranking[i]=0;
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


struct Node_Fibonacci
{
    
    Node_Fibonacci *backward;
    Node_Fibonacci *forward;
    Node_Fibonacci *parent;
    Node_Fibonacci *child;
    int key;
    bool marked;
    int degree;

    Node_Fibonacci()
    {
        this -> backward =NULL;
        this -> forward =NULL;
        this -> parent =NULL;
        this -> child = NULL;
        this -> key = 0;
        this -> marked = false;
        this -> degree = 0;
    }
    
    Node_Fibonacci(int key)
    {
        this -> key = key;
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
    unordered_map<int,pair<int,int>>edge_node_map;

    initialize(g_nodes);

    for (int i = 0; i < g_edges; i++) {
        
        cin >> g_from[i] >> g_to[i] >> g_weight[i];
        fh -> insert(new Node_Fibonacci(g_weight[i]));
        
       
    }
    
    // adding from-to pair to map corresponding to the index equal to the weight
    for(int i=0;i<g_edges;i++){

        pair<int,int>from_to = make_pair(g_from[i],g_to[i]);
        edge_node_map[g_weight[i]]=from_to;
    }
    
    //sorting using the extract minimum operation of fibonacci heap..
    int y=0;
    struct edges new_e[g_edges+1];
    while (!fh -> is_Heap_Empty())
    {
        int x =  fh -> extractMin() -> key;
        new_e[y].from=(edge_node_map[x]).first;
        new_e[y].to=(edge_node_map[x]).second;
        new_e[y].weight = x;
        printf("%d ",x);
        y++;
    }

    // actual logic of kruskal to find the weight of MST using union operation
    printf("\n");
    int mst_wt=0;
    for(int i=0;i<g_edges;i++){
        int u = new_e[i].from;
        int v = new_e[i].to;

        u = parent[u];
        v = parent[v];
        parent[new_e[i].from]=u;
        parent[new_e[i].to]=v;
        
        if(u!=v){
           mst_wt+=new_e[i].weight;

           union1(u,v);
        }       
    }
    cout<<mst_wt<<endl;
   
    return 0;
}
