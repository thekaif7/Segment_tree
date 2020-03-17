#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;


void buildTree(ll *arr,ll* tree,int start,int end,int tree_node)
{
        if(start==end){
            tree[tree_node] = arr[start];
            return ;
        }

    int mid = (start+end)/2;

    buildTree(arr,tree,start,mid,2*tree_node);
    buildTree(arr,tree,mid+1,end,2*tree_node+1);

    tree[tree_node] = tree[2*tree_node+1]+tree[2*tree_node];


}


void update(ll* arr,ll* tree,ll* lazy, int start,int end, int tree_node, int l, int r,ll inc){

    if(start>end){
        return ;
    }

    if(lazy[tree_node]!=0){
        tree[tree_node]+=lazy[tree_node]*(end-start+1);

        if(start!=end){
            lazy[2*tree_node]+=lazy[tree_node];
            lazy[2*tree_node+1]+=lazy[tree_node];
        }

        lazy[tree_node] = 0;
    }

    if(start>r || end<l){
        return ;
    }

    if(start>=l && end<=r){
        tree[tree_node]+=inc*(end-start+1);

        if(start!=end){
            lazy[2*tree_node]+=inc;
            lazy[2*tree_node+1]+=inc;
        }

        return ;
    }

    int mid = (start+end)/2;

    update(arr,tree,lazy,start,mid,2*tree_node,l,r,inc);
    update(arr,tree,lazy,mid+1,end,2*tree_node+1,l,r,inc);

    tree[tree_node] = tree[2*tree_node]+tree[2*tree_node+1];

}


ll query(ll* tree, ll* lazy , int start, int end, int tree_node , int l , int r ){
    if(start>end){
        return 0;
    }

    if(lazy[tree_node]!=0){
        tree[tree_node]+=lazy[tree_node]*(end-start+1);

        if(start!=end){
            lazy[2*tree_node]+=lazy[tree_node];
            lazy[2*tree_node+1]+=lazy[tree_node];
        }

        lazy[tree_node] = 0;
    }

    if(start>r || end<l){
        return 0;
    }

    if(start>=l && end<=r){


        return tree[tree_node];
    }

    int mid = (start+end)/2;

    ll left=query(tree,lazy,start,mid,2*tree_node,l,r);
    ll right=query(tree,lazy,mid+1,end,2*tree_node+1,l,r);

    return left+right;


}

int main() {

	// Write your code here
    int t;
    cin>>t;

    while(t--){

        int n,c;
        cin>>n>>c;

        ll* arr = new ll[n]();
        ll* lazy = new ll[4*n]();
        ll* tree = new ll[4*n]();

        buildTree(arr,tree,0,n-1,1);

        while(c--){

            int q;
            cin>>q;

            if(q==0){

                int l,r;
                ll v;
                cin>>l>>r>>v;
                update(arr,tree,lazy,0,n-1,1,l-1,r-1,v);


            }

            else{
                ll l,r;
                cin>>l>>r;
                cout<<query(tree,lazy,0,n-1,1,l-1,r-1)<<endl;
            }
        }

        delete arr;
    }


}
