#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>
using namespace std;




struct edges{
    int from;
    int to;
    int weight;
};

int kruskal(struct edges *e,int g_edges,int g_nodes);
void union1(int a,int b);
int find(int x);
void initialize(int n);
bool compare(struct edges a,struct edges b);