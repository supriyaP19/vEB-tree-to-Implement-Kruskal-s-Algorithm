//
//  veb.cpp
//  APS project 1
//
//  Created by Rajat Kumar Verma on 31/10/18.
//  Copyright © 2018 APS. All rights reserved.
//

#include "veb.hpp"



edge::edge(ll wt , ll frm , ll t )
{
    weight = wt;
    from = frm;
    to = t;
}

vEB::vEB ( ll uniSize )
{
    
    uni = powTwoRoundUp ( uniSize );
    uniSqrt = sqrt ( uni );
    lowerUniSqrt = lowerSqrt ( uni );
    higherUniSqrt = higherSqrt ( uni );
    
    //    min = new edge();
    //
    //    max = new edge();
    
    min = NULL;
    max = NULL;
    
    summary = NULL;
    cluster = NULL;
    if ( uniSize <= 0 )
    {
        std::cerr << "universe size of vEB must be bigger than 0" << std::endl;
        return;
    }
    
    if ( uni > 2 )
    {
        cluster = new vEB * [higherUniSqrt];
        for ( ll i = 0; i < higherUniSqrt; ++i )
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
    //    if(min) delete min;
    //    if(max) delete max;
    if ( summary ) delete summary;
    if ( cluster )
    {
        for ( ll i = 0; i < higherUniSqrt; ++i )
        {
            if ( cluster[i] ) delete cluster[i];
        }
        delete [] cluster;
    }
}

ll powTwoRoundUp ( ll x )
{
    if ( x < 0 ) return 0;
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x + 1;
}

float lowerSqrt ( ll val )
{
    return pow ( 2, floor ( log2 ( val )  / 2 ) );
}

float higherSqrt ( ll val )
{
    return pow ( 2, ceil ( log2 ( val )  / 2 ) );
}

ll low ( vEB * tree, ll val )
{
    return val % ( ll ) lowerSqrt ( tree->uni );
}

ll high ( vEB * tree, ll val )
{
    return val / lowerSqrt ( tree->uni );
}

ll index ( vEB * tree, ll high, ll low )
{
    return high * lowerSqrt ( tree->uni ) + low;
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
        vEB_delete ( tree, x->weight);
        return y;
    }
    cout << "Could not delete ll_MIN !!"<<endl;
    return x;
}

struct vEB * empty_insert_mem(ll size)
{
    struct vEB *tree = new vEB ( size );
    return tree;
}

struct vEB * empty_insert(vEB *& tree, struct edge *val)
{
    tree->min = tree->max = val;
    return tree;
}

struct vEB * set_new_min(vEB *& tree,  struct edge *oldstr)
{
    tree->min = oldstr;
    return tree;
}


ll insert(vEB *& tree ,ll wt, ll frm , ll t, ll parenrUniSqrt)
{
    struct edge *x = new edge(wt , frm , t);
    
    vEB_insert(tree , x , parenrUniSqrt );
    return 1;
}



ll vEB_insert ( vEB *& tree, struct edge *val, ll parentUniSqrt )
{
    if ( !tree )
    {
        tree = empty_insert_mem(parentUniSqrt);
    }
    if ( tree_min(tree) == NULL )
    {
        empty_insert(tree , val);
        return 1;
    }
    
    if ( val->weight < 0 || val->weight >= tree->uni )
    {
        return 0;
    }
    if ( tree_min(tree)->weight == val->weight || tree_max(tree)->weight == val->weight )
    {
        return 0;
    }
    
    
    if ( val->weight < tree_min(tree)->weight )
    {
        struct edge *oldstr = val;
        
        val = tree->min;
        set_new_min(tree , oldstr);
    }
    
    if ( tree->uni > 2 )
    {
        ll lowVal = low ( tree, val->weight );
        ll highVal = high ( tree, val->weight );
        if ( tree_min(tree->cluster[highVal]) == NULL )
        {
            if ( insert ( tree->summary, highVal , val->from, val->to , tree->higherUniSqrt )== 0 )
            {
                return 0;
            }
        }
        
        if ( insert ( tree->cluster[highVal], lowVal, val->from , val->to , tree->lowerUniSqrt )== 0 )
        {
            return 0;
        }
    }
    if ( val->weight > tree_max(tree)->weight )
    {
        tree->max = val ;
    }
    return 1;
}

ll vEB_delete ( vEB *& tree, ll val )
{
    if ( !tree )
    {
        return 0;
    }
    if ( val < 0 || val >= tree->uni )
    {
        return 0;
    }
    if ( val < tree->min->weight || tree->max->weight < val )
    {
        return 0;
    }
    if ( val == tree->min->weight )
    {
        
        struct edge *x = tree_min ( tree->summary);
        if ( x == NULL )
        {
            if ( tree->min->weight != tree->max->weight )
            {
                tree->min = tree->max;
                return 1;
            }
            
            tree->min = tree->max = NULL;
            delete tree;
            tree = NULL;
            return 1;
        }
        ll i = tree_min ( tree->summary)->weight;
        val = tree->min->weight = index ( tree, i, tree_min(tree->cluster[i])->weight);
        tree->min->from = tree_min(tree->cluster[i])->from;
        tree->min->to = tree_min(tree->cluster[i])->to;
        
    }
    
    if ( tree->uni > 2 )
    {
        ll highVal = high ( tree, val );
        ll lowVal = low ( tree, val );
        if ( vEB_delete ( tree->cluster[highVal], lowVal) == 0 )
        {
            return 0;
        }
        struct edge  *tmp = tree_min ( tree->cluster[highVal]);
        if ( tmp == NULL )
        {
            if ( vEB_delete ( tree->summary, highVal ) == 0 )
            {
                return 0;
            }
        }
    }
    
    if ( val == tree->max->weight )
    {
        struct edge  *x = tree_max ( tree->summary);
        if ( x == NULL )
        {
            tree->max = tree->min;
            return 1;
        }
        else
        {
            ll i = tree_max ( tree->summary)->weight;
            tree->max->weight = index ( tree, i, tree_max(tree->cluster[i])->weight );
            tree->max->from = tree_max(tree->cluster[i])->from;
            tree->max->to = tree_max(tree->cluster[i])->to;
        }
    }
    return 1;
}

ll vEB_member ( vEB * tree, ll val )
{
    if ( !tree ) return 0;
    
    if ( val < 0 || val >= tree->uni ) return 0;
    if ( tree->min->weight > val || tree->max->weight < val ) return 0;
    if ( tree->min->weight == val ) return val;
    if ( !tree->summary )
    {
        return tree->max->weight == val;
    }
    if ( !vEB_member ( tree->cluster[high ( tree, val )], low ( tree, val ) ) )
        return 0;
    return val;
}

