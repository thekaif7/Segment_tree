#include<bits/stdc++.h>
using namespace std;

struct node{
  int f_max;
  int s_max;
};

void buildTree(int* arr,node* tree,int tree_node,int start, int end){

    if(start==end){
        tree[tree_node].f_max = arr[start];
        tree[tree_node].s_max = INT_MIN;
        return ;
    }


  int mid = (start+end)/2;
  buildTree(arr,tree,2*tree_node,start,mid);
  buildTree(arr,tree,2*tree_node+1,mid+1,end);

  node left = tree[2*tree_node];
  node right = tree[2*tree_node+1];

  tree[tree_node].f_max = max(left.f_max,right.f_max);
  tree[tree_node].s_max = min(max(right.f_max,left.s_max),max(left.f_max,right.s_max));

}

void update(int* arr,node* tree , int tree_node, int index , int value,int start, int end){

  if(start==end){
    tree[tree_node].f_max = value;

    return ;
  }
  int mid = (start+end)/2;

  if(index>mid){
    update(arr,tree,2*tree_node+1,index,value,mid+1,end);

  }
  else{
    update(arr,tree,2*tree_node,index,value,start,mid);
  }

  node left = tree[2*tree_node];
  node right = tree[2*tree_node+1];

  tree[tree_node].f_max = max(left.f_max,right.f_max);
  tree[tree_node].s_max = min(max(right.f_max,left.s_max),max(left.f_max,right.s_max));



}

node QUERY(node* tree, int start, int end , int tree_node, int left , int right){
  //completely outside the range
  if(start>right || end<left){
    node rr ;
    rr.f_max = INT_MIN;
    rr.s_max = INT_MIN;

    return rr;
  }

  //completely inside in range
  if(start>=left && end<=right){
    return tree[tree_node];
  }

  int mid = (start+end)/2;

  node l = QUERY(tree,start,mid,2*tree_node,left,right);
  node r = QUERY(tree,mid+1,end,2*tree_node+1,left,right);

  node ans;

  ans.f_max =  max(l.f_max,r.f_max);
  ans.s_max =  min(max(r.f_max,l.s_max),max(l.f_max,r.s_max));

  return ans;




}



int main(){

  int n;
    cin>>n;

    int* arr = new int[n];

    for(int i=0;i<n;i++){
        cin>>arr[i];
    }

    node* tree = new node[3*n];

    buildTree(arr,tree,1,0, n-1);

    int t;
    cin>>t;

    while(t--){
        char q;
        int l,r;


        cin>>q>>l>>r;

        if(q=='Q'){

            node d = QUERY(tree,0,n-1,1,l-1,r-1);

            cout<<d.f_max + d.s_max<<endl;

        }

        else{
            update(arr,tree,1,l-1,r,0,n-1);
        }

    }


    delete arr;
    delete tree;













}
