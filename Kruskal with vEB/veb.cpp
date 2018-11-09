
//
//  vEB.cpp
//  APS project 1
//
//  Created by Rajat Kumar Verma on 31/10/18.
//  Copyright © 2018 APS. All rights reserved.
//

#include "vEB.hpp"



edge::edge(ll wt , ll frm , ll t )
{
    weight = wt;
    from = frm;
    to = t;
}

vEB::vEB(ll universe_size)
{
    min = NULL;
    max = NULL;
    summary = NULL;
    cluster = NULL;
    if(universe_size <= 0)
    {
        return;
    }
    universe = nextpower_of_two(universe_size);
    universe_sqrt = sqrt(universe);
    low_universe_sqrt = sqrt_floor(universe);
    hi_universe_sqrt = sqrt_ceil(universe);

    if (universe > 2)
    {
        cluster = new vEB * [hi_universe_sqrt];
        for (ll i = 0; i < hi_universe_sqrt; ++i)
        {
            cluster[i] = NULL;
        }
    }
    else
    {
        cluster = NULL;
    }
}

vEB::~vEB()
{
    if(cluster != NULL)
    {
        for(ll i = 0; i < hi_universe_sqrt; i++)
        {
            if(cluster[i] != NULL) 
            delete cluster[i];
        }
        delete [] cluster;
    }
    if(summary != NULL) 
    delete summary;
}

ll nextpower_of_two(ll next_exp)
{
    if (next_exp < 0)
        return 0;
    next_exp--;
    next_exp |= next_exp >> 1;
    next_exp |= next_exp >> 2;
    next_exp |= next_exp >> 4;
    next_exp |= next_exp >> 8;
    next_exp |= next_exp >> 16;
    next_exp++;
    return next_exp;
}

ll sqrt_floor(ll x)
{
    return pow(2, floor(log2(x)/2));
}

ll sqrt_ceil(ll x)
{
    return pow(2, ceil(log2(x)/2));
}

ll low(vEB * tree, ll x)
{
    return x%(ll)sqrt_floor(tree->universe);
}

ll high(vEB * tree, ll x)
{
    return x/sqrt_floor(tree->universe);
}

ll index (vEB * tree, ll high, ll low)
{
    return high * sqrt_floor(tree->universe) + low;
}


struct edge * tree_min(vEB *tree)
{
    if(tree)
    {
        if(tree->min !=NULL)
            return tree->min;
    }
    return NULL;
}

struct edge * tree_max(vEB *tree)
{
    if(tree)
    {
        if(tree->max!=NULL)
            return tree->max;
    }
    return NULL;
}

struct edge * extract_min(vEB *tree)
{
    struct edge * x = tree_min(tree);
    struct edge *y = new edge(x->weight , x->from , x->to);

    if(x != NULL)
    {
        delete_vEB(tree, x->weight);
        return y;
    }
    // cout << "Could not delete ll_MIN !!"<<endl;
    return x;
}

struct vEB * empty_insert_mem(ll size)
{
    struct vEB *tree = new vEB(size);
    return tree;
}

struct vEB * empty_insert(vEB *& tree, struct edge *ed)
{
    tree->min = tree->max = ed;
    return tree;
}

struct vEB * set_new_min(vEB *& tree,  struct edge *new_min)
{
    tree->min = new_min;
    return tree;
}


ll insert(vEB *& tree ,ll wt, ll frm , ll t, ll last_universe_sqrt)
{
    struct edge *ed = new edge(wt , frm , t);
    
    insert_vEB(tree , ed , last_universe_sqrt);
    return 1;
}



ll insert_vEB(vEB *& tree, struct edge *ed, ll last_universe_sqrt)
{
    if ( !tree )
    {
        tree = empty_insert_mem(last_universe_sqrt);
    }
    if(tree_min(tree) == NULL)
    {
        empty_insert(tree , ed);
        return 1;
    }
    
    if(ed->weight < 0 || ed->weight >= tree->universe)
    {
        return 0;
    }
    if(tree_min(tree)->weight == ed->weight || tree_max(tree)->weight == ed->weight)
    {
        return 0;
    }
    
    
    if(ed->weight < tree_min(tree)->weight)
    {
        struct edge *new_min = ed;
        ed = tree->min;
        set_new_min(tree , new_min);
    }
    
    if(tree->universe > 2)
    {
        ll low_of_x = low ( tree, ed->weight );
        ll high_of_x = high ( tree, ed->weight );
        if(tree_min(tree->cluster[high_of_x]) == NULL)
        {
            if (insert(tree->summary, high_of_x , ed->from, ed->to , tree->hi_universe_sqrt)== 0)
            {
                return 0;
            }
        }
        
        if (insert(tree->cluster[high_of_x], low_of_x, ed->from , ed->to , tree->low_universe_sqrt)== 0)
        {
            return 0;
        }
    }
    if (ed->weight > tree_max(tree)->weight)
    {
        tree->max = ed ;
    }
    return 1;
}

ll delete_vEB(vEB *& tree, ll ed)
{
    if ( !tree )
    {
        return 0;
    }
    if(ed < 0 || tree->universe <= ed)
    {
        return 0;
    }
    if(ed < tree->min->weight || tree->max->weight < ed)
    {
        return 0;
    }
    if(ed == tree->min->weight)
    {
        
        struct edge *x = tree_min(tree->summary);
        if(x == NULL)
        {
            if(tree->min->weight != tree->max->weight)
            {
                tree->min = tree->max;
                return 1;
            }
            
            tree->min = tree->max = NULL;
            delete tree;
            tree = NULL;
            return 1;
        }
        ll i = tree_min(tree->summary)->weight;
        ed = tree->min->weight = index(tree, i, tree_min(tree->cluster[i])->weight);
        tree->min->from = tree_min(tree->cluster[i])->from;
        tree->min->to = tree_min(tree->cluster[i])->to;
        
    }
    
    if(tree->universe > 2)
    {
        ll high_of_x = high(tree, ed);
        ll low_of_x = low(tree, ed);
        if ( delete_vEB(tree->cluster[high_of_x], low_of_x) == 0)
        {
            return 0;
        }
        struct edge  *tmp = tree_min(tree->cluster[high_of_x]);
        if ( tmp == NULL )
        {
            if (delete_vEB(tree->summary, high_of_x) == 0)
            {
                return 0;
            }
        }
    }
    
    if (ed == tree->max->weight)
    {
        struct edge  *x = tree_max(tree->summary);
        if (x == NULL)
        {
            tree->max = tree->min;
            return 1;
        }
        else
        {
            ll i = tree_max(tree->summary)->weight;
            tree->max->weight = index(tree, i, tree_max(tree->cluster[i])->weight);
            tree->max->from = tree_max(tree->cluster[i])->from;
            tree->max->to = tree_max(tree->cluster[i])->to;
        }
    }
    return 1;
}


