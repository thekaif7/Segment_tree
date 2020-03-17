#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct node{
    ll ss;
    ll s;

};

struct lode {
    int type;
    ll value;

    lode(){value=0;} // we check in update and query if lazy.value is zero or not so always initialize who check most

};

void buildTree(int* arr,node* tree ,int start,int end , int tree_node){
    if(start==end){
        tree[tree_node].ss = arr[start]*arr[start];
        tree[tree_node].s =arr[start];
        return ;
    }

    int mid = (start+end)/2;

    buildTree(arr,tree,start,mid,2*tree_node);
    buildTree(arr,tree,mid+1,end,2*tree_node+1);

    tree[tree_node].ss = tree[2*tree_node].ss + tree[2*tree_node+1].ss;
    tree[tree_node].s = tree[2*tree_node].s + tree[2*tree_node+1].s;

}

void update(node*tree,lode* lazy , int start, int end,int tree_node,int l,int r,ll value,int type){
    if(start>end){
        return ;
    }

    if(lazy[tree_node].value!=0){

        ll v = lazy[tree_node].value;

        if(lazy[tree_node].type ==1){
            tree[tree_node].ss+=2*v*(end-start+1) + v*v*(end-start+1);
            tree[tree_node].s +=v*(end-start+1);

            if(start!=end){
                lazy[2*tree_node].value +=v;
                lazy[2*tree_node].type = 1;

                lazy[2*tree_node+1].value +=v;
                lazy[2*tree_node+1].type = 1;

            }
        }

        else{
            tree[tree_node].ss=v*v*(end-start+1);
            tree[tree_node].s =v*(end-start+1);

            if(start!=end){
                lazy[2*tree_node].value =v;
                lazy[2*tree_node].type = 2;

                lazy[2*tree_node+1].value =v;
                lazy[2*tree_node+1].type = 2;

            }
        }

        lazy[tree_node].value = 0;

    }

    if(start>r || end<l){
        return ;
    }

    if(start>=l && end<=r)
    {

        if(type ==1)
        {

        tree[tree_node].ss+=2*value*tree[tree_node].s + value*value*(end-start+1);
        tree[tree_node].s+=value*(end-start+1);

            if(start!=end)
            {
                lazy[2*tree_node].value+=value;
                lazy[2*tree_node].type = 1;
                lazy[2*tree_node+1].value+=value;
                lazy[2*tree_node+1].type = 1;
            }

            lazy[tree_node].type = 1;

        }


        else
        {
            tree[tree_node].ss=value*value*(end-start+1);
            tree[tree_node].s=value*(end-start+1);

            if(start!=end){
                lazy[2*tree_node].value=value;
                lazy[2*tree_node].type = 2;
                lazy[2*tree_node+1].value=value;
                lazy[2*tree_node+1].type = 2;
            }

            lazy[tree_node].type = 2;

        }


        lazy[tree_node].value = 0;
        return;



        }


    int mid =(start+end)/2;

    update(tree,lazy,start,mid,2*tree_node,l,r,value,type);
    update(tree,lazy,mid+1,end,2*tree_node+1,l,r,value,type);

    tree[tree_node].ss = tree[2*tree_node].ss + tree[2*tree_node+1].ss;
    tree[tree_node].s = tree[2*tree_node].s + tree[2*tree_node+1].s;

}

ll query(node* tree, lode* lazy, int start, int end , int tree_node, int l, int r){

    if (start>end){
        return 0;
    }

    if(lazy[tree_node].value!=0){

        ll v = lazy[tree_node].value;

        if(lazy[tree_node].type ==1){
            tree[tree_node].ss+=2*v*(end-start+1) + v*v*(end-start+1);
            tree[tree_node].s +=v*(end-start+1);

            if(start!=end){
                lazy[2*tree_node].value +=v;
                lazy[2*tree_node].type = 1;

                lazy[2*tree_node+1].value +=v;
                lazy[2*tree_node+1].type = 1;

            }
        }

        else{
            tree[tree_node].ss=v*v*(end-start+1);
            tree[tree_node].s =v*(end-start+1);

            if(start!=end){
                lazy[2*tree_node].value =v;
                lazy[2*tree_node].type = 2;

                lazy[2*tree_node+1].value =v;
                lazy[2*tree_node+1].type = 2;

            }
        }

        lazy[tree_node].value = 0;

    }


    if(start>r || end<l){
        return 0;
    }

    if(start>=l && end<=r){
        if(lazy[tree_node].value!=0){
            ll value = lazy[tree_node].value;

                    if(lazy[tree_node].type = 1){
                        tree[tree_node].ss+=2*value*tree[tree_node].s + value*value*(r-l+1);
                        tree[tree_node].s+=value*(r-l+1);

                        if(start!=end){
                            lazy[2*tree_node].value +=value;
                            lazy[2*tree_node].type = 1;
                            lazy[2*tree_node+1].value +=value;
                            lazy[2*tree_node+1].type = 1;
                        }

                    }
                else{

                     tree[tree_node].ss= value*value*(r-l+1);
                        tree[tree_node].s=value*(r-l+1);

                        if(start!=end){
                            lazy[2*tree_node].value =value;
                            lazy[2*tree_node].type = 2;
                            lazy[2*tree_node+1].value =value;
                            lazy[2*tree_node+1].type = 2;
                        }
                }

        }

        lazy[tree_node].value = 0;
        return tree[tree_node].ss;

    }




    int mid = (start+end)/2;

    ll left = query(tree,lazy,start,mid,2*tree_node,l,r);
    ll right = query(tree,lazy,mid+1,end,2*tree_node+1,l,r);

    return left+right;
}


int main() {

	int t;
    cin>>t;
    int k=1;

    while(t--){
        int n, q;
        cin>>n>>q;
        int *arr = new int[n];

        for(int i=0;i<n;i++){
            cin>>arr[i];
        }

        node* tree= new node[4*n];
        buildTree(arr,tree,0,n-1,1);
        lode *lazy = new lode[4*n];
        cout<<"Case"<<" "<<k<<":"<<endl;
        while(q--){
            int Q;
            cin>>Q;
            if(Q==2){
                int l,r;
                cin>>l>>r;

                cout<<query(tree,lazy,0,n-1,1,l-1,r-1)<<endl;
            }
            else if(Q==1){
                int l,r;
                ll value;
                cin>>l>>r>>value;
                update(tree,lazy,0,n-1,1,l-1,r-1,value,Q);
            }
            else{
                int l,r;
                ll value;
                cin>>l>>r>>value;
                update(tree,lazy,0,n-1,1,l-1,r-1,value,Q);
            }
        }

    delete arr;
    delete tree;
    delete lazy;
        k++;
    }



}
