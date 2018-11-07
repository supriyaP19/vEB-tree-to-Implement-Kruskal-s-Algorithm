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
    
    vEB ( ll uniSize );
    ~vEB();
    ll uni;
    ll uniSqrt;
    ll lowerUniSqrt;
    ll higherUniSqrt;
    struct edge * min;
    struct edge * max;
    vEB * summary;
    vEB ** cluster;
    
};



ll powTwoRoundUp ( ll val ); //Round up to next higher power of 2
float lowerSqrt ( ll val );
float higherSqrt ( ll val );
ll low ( vEB * tree, ll val );
ll high ( vEB * tree, ll val );
ll index ( vEB * tree, ll high, ll low );
struct edge * tree_min(vEB *tree);
struct edge * tree_max(vEB *tree);
struct edge * extract_min(vEB *tree);
ll insert(vEB *& tree ,ll wt, ll frm , ll t, ll parenrUniSqrt = 131072);
ll vEB_insert ( vEB *& tree, struct edge *val , ll parentUniSqrt = 131072 );
ll vEB_delete ( vEB *& tree, ll val );
ll vEB_member ( vEB * tree, ll val );
