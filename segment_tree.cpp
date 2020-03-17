#include<bits/stdc++.h>
using namespace std;

void buildTree(int *arr,int *tree,int start,int end,int tree_node){
  if (start==end){tree[tree_node] = arr[start]; return ;}

  int mid = (start+end)/2;

  buildTree(arr,tree,start,mid,2*tree_node);
  buildTree(arr,tree,mid+1,end,2*tree_node+1);

  tree[tree_node] = min(tree[2*tree_node],tree[2*tree_node + 1]);




}

void updateTree(int *arr,int *tree,int start,int end,int tree_node , int idx , int value){
  if (start==end){

    tree[tree_node] = arr[start] + value;

    return ;
  }
  int mid = (start+end)/2;

  if(idx>mid){
    updateTree(arr,tree,mid+1,end,2*tree_node+1,idx,value);
  }else{
    updateTree(arr,tree,start,mid,2*tree_node,idx,value);
  }

  tree[tree_node] = min(tree[2*tree_node] , tree[2*tree_node+1]);


}

int QUERY(int *tree , int start, int end , int tree_node , int left , int right){
  //completely outside the range
  if(start>right || end<left){
    return INT_MAX;
  }

  //completely inside in range
  if(start>=left && end<=right){
    return tree[tree_node];
  }

  int mid = (start+end)/2;
  int ans1 = QUERY(tree,start,mid,2*tree_node,left,right);
  int ans2 = QUERY(tree,mid+1,end,2*tree_node+1,left,right);

  // any operation

  return min(ans1,ans2);


}

int main(){
  int arr[] = {1,2,3,4,5,6,7,8,9};
  int* tree = new int[18];
  cout<<"start"<<endl;
  buildTree(arr,tree,0,8,1);

  for(int i=1;i<18;i++){
    cout<<tree[i]<<" ";

  }

  cout<<endl;

  cout<<"update : Add -4 to last element "<<endl;
  updateTree(arr,tree,0,8,1,8,-4);
  for(int i=1;i<18;i++){
    cout<<tree[i]<<" ";

  }

  cout<<endl<<"QUery"<<endl;
  cout<<QUERY(tree,0,8,1,2,4)<<endl;
  cout<<QUERY(tree,0,8,1,0,4)<<endl;

  delete [] tree;

}
