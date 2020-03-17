#include<bits/stdc++.h>
using namespace std;

struct node{
    int even;
    int odd;

    node(){
        even=odd=0;
    }
};

void buildTree(int* arr, node *tree, int start,int end , int tree_node){
    if(start==end){
        tree[tree_node].even = (arr[start]%2==0)?1:0;
        tree[tree_node].odd = (arr[start]%2!=0)?1:0;

        return;
    }

    int mid = (start+end)/2;
    buildTree(arr,tree,start,mid,2*tree_node);
    buildTree(arr,tree,mid+1,end,2*tree_node+1);

    tree[tree_node].even = tree[2*tree_node].even + tree[2*tree_node+1].even;
    tree[tree_node].odd = tree[2*tree_node].odd + tree[2*tree_node+1].odd;


}

void update(int* arr, node *tree,int start,int end, int tree_node,int index,int value){
    if(start==end){
        tree[tree_node].even = (value%2==0)?1:0;
        tree[tree_node].odd = (value%2!=0)?1:0;
        return ;
    }

    int mid = (start+end)/2;

    if(index>mid){
        update(arr,tree,mid+1,end,2*tree_node+1,index,value);
    }
    else{
        update(arr,tree,start,mid,2*tree_node,index,value);
    }

    tree[tree_node].even = tree[2*tree_node].even + tree[2*tree_node+1].even;
    tree[tree_node].odd = tree[2*tree_node].odd + tree[2*tree_node+1].odd;


}

node query(node* tree,int start,int end, int tree_node, int left ,int right){
    if(start>right || end<left){
        node null_node;
        return null_node;
    }


    if(start>=left && end<=right){
        return tree[tree_node];
    }


    int mid=(start+end)/2;

    node l = query(tree,start,mid,2*tree_node,left,right);
    node r = query(tree,mid+1,end,2*tree_node+1,left,right);

    node ans;
    ans.even = l.even+r.even;
    ans.odd = l.odd+r.odd;

    return ans;


}

int main() {

	// Write your code here
    int  n;
    cin>>n;

    int* arr= new int[n];

    for(int i=0;i<n;i++){
        cin>>arr[i];

    }

    node* tree= new node[4*n];
    buildTree(arr,tree,0,n-1,1);

    int t;
    cin>>t;

    while(t--){

        int q,l,r;
        cin>>q>>l>>r;

        if (q==0){
            update(arr,tree,0,n-1,1,l-1,r);
        }
        else if(q==1){
            node ans = query(tree,0,n-1,1,l-1,r-1);
            cout<<ans.even<<endl;
        }
        else{
            node ans = query(tree,0,n-1,1,l-1,r-1);
            cout<<ans.odd<<endl;
        }

    }

    delete tree;
    delete arr;





}
