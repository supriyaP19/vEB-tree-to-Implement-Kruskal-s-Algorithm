//
//  veb.hpp
//  APS project 1
//
//  Created by Rajat Kumar Verma on 31/10/18.
//  Copyright © 2018 APS. All rights reserved.
//


#include <iostream>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;


typedef long long ll;

struct edge
{
    edge(ll weight , ll from , ll to );
    ll weight;
    ll from;
    ll to;
};

struct vEB
{
    vEB ( ll universe_size );
    ll universe;
    ll universe_sqrt;
    ll low_universe_sqrt;
    ll hi_universe_sqrt;
    vEB * summary;
    vEB ** cluster;
    struct edge * min;
    struct edge * max;
    ~vEB();
};



ll nextpower_of_two(ll x); //Round up to next higher power of 2
ll sqrt_floor(ll x);
ll sqrt_ceil(ll x);
ll low(vEB * tree, ll x);
ll high(vEB * tree, ll x);
ll index(vEB * tree, ll high, ll low);
ll insert(vEB *& tree ,ll wt, ll frm , ll t, ll last_universe_sqrt = 0);
ll insert_vEB(vEB *& tree, struct edge *ed , ll last_universe_sqrt = 0);
ll delete_vEB(vEB *& tree, ll ed);
struct edge * tree_min(vEB *tree);
struct edge * tree_max(vEB *tree);
struct edge * extract_min(vEB *tree);