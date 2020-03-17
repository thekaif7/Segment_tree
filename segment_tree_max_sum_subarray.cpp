#include<bits/stdc++.h>
using namespace std;

#define inf 0x3f3f

struct node{
  int max_sum;
  int b_pr;
  int b_sf;
  int sum;
  //by default initialization
  node(){
    max_sum=b_pr=b_sf=sum=-inf;

  }
};
node merge(node left , node right){
  node tree_node;

  tree_node.b_pr = max(left.b_pr,left.sum+right.b_pr);
  tree_node.b_sf = max(right.b_sf,right.sum+left.b_sf);
  tree_node.sum = left.sum + right.sum;
  tree_node.max_sum = max({left.max_sum,right.max_sum,left.sum+right.b_pr,right.sum+left.b_sf,left.b_sf+right.b_pr});

  return tree_node;
}

void buildTree(int* arr,node *tree, int start , int end,int index){
  if(start==end){
    tree[index].sum=arr[start];
    tree[index].max_sum=arr[start];
    tree[index].b_sf=arr[start];
    tree[index].b_pr=arr[start];
    return ;
  }

  int mid = (start+end)/2;

  buildTree(arr,tree,start,mid,2*index);
  buildTree(arr,tree,mid+1,end,2*index +1);

  tree[index] = merge(tree[2*index],tree[2*index+1]);



}

node query(node *tree,int start,int end ,int index,int left , int right){
  //completely outside the range
  if(start>right || end<left){
    node null_node;
    return null_node;
  }

  //completely inside in range
  if(start>=left && end<=right){
    return tree[index];
  }

  int mid = (start+end)/2;

  node l = query(tree,start,mid,2*index,left,right);
  node r = query(tree,mid+1,end,2*index+1,left,right);

  node ans = merge(l,r);

  return ans;



}





int main(){

    int n;
    cin>>n;

    int *arr = new int[n];

    for(int i=0;i<n;i++){
        cin>>arr[i];
    }

    int t;
    cin>>t;

    node* tree = new node[4*n];
    buildTree(arr,tree,0,n-1,1);

    while(t--){
        int l,r;
        cin>>l>>r;

        node answer = query(tree,0,n-1,1,l-1,r-1);
        cout<<answer.max_sum<<endl;
    }
















}
