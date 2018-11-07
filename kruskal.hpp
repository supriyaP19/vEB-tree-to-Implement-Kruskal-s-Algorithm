#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>
using namespace std;
typedef long long lld;



struct edges{
    lld from;
    lld to;
    lld weight;
};

lld kruskal(struct edges *e,lld g_edges,lld g_nodes);
void union1(lld a,lld b);
lld find(lld x);
void initialize(lld n);
bool compare(struct edges a,struct edges b);