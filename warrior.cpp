#include<bits/stdc++.h>
using namespace std;

struct node1{
    int a,b,index;

    node1(){
        a=b=0;
        index=0;
    }
};
struct node{
    int a,b,index;

    node(){
        a=b=0;
        index=-1;
    }
};

void buildTree(node1* arr,node* tree, int start, int end, int tree_node){
    if(start==end){
        tree[tree_node].a = arr[start].a;
        tree[tree_node].b = arr[start].b;
        tree[tree_node].index = arr[start].index;
        return;
    }

    int mid =(start+end)/2;

    buildTree(arr,tree,start,mid,2*tree_node);
    buildTree(arr,tree,mid+1,end,2*tree_node+1);

    node left = tree[2*tree_node];
    node right = tree[2*tree_node+1];

    if(left.a>right.a){

        tree[tree_node].a = left.a;
        tree[tree_node].b = left.b;
        tree[tree_node].index = left.index;

    }

    else if(right.a>left.a){

        tree[tree_node].a = right.a;
        tree[tree_node].b = right.b;
        tree[tree_node].index = right.index;

    }

    else if(right.a==left.a && right.b==left.a){
        if(left.index<right.index){

        tree[tree_node].a = left.a;
        tree[tree_node].b = left.b;
        tree[tree_node].index = left.index;

        }
        else{

        tree[tree_node].a =right.a;
        tree[tree_node].b =right.b;
        tree[tree_node].index =right.index;

        }
    }

    else{
        if (left.b<right.b){
        tree[tree_node].a = left.a;
        tree[tree_node].b = left.b;
        tree[tree_node].index = left.index;}
        else{
        tree[tree_node].a = right.a;
        tree[tree_node].b = right.b;
        tree[tree_node].index = right.index;
        }
    }
}


node query(node* tree,int start,int end, int tree_node,int l , int r){
    if(start>r || end<l){
        node null_node;
        return null_node;
    }

    if(start>=l && end<=r){
        return tree[tree_node];
    }

    int mid = (start+end)/2;

    node left  = query(tree,start,mid,2*tree_node,l,r);
    node right = query(tree,mid+1,end,2*tree_node+1,l,r);
    node ans;
    if(left.a>right.a){

        ans.a = left.a;
        ans.b = left.b;
        ans.index = left.index;

    }

    else if(right.a>left.a){

        ans.a = right.a;
        ans.b = right.b;
        ans.index = right.index;

    }

    else if(right.a==left.a && right.b==left.a){
        if(left.index<right.index){

        ans.a = left.a;
        ans.b = left.b;
        ans.index = left.index;

        }
        else{

        ans.a =right.a;
        ans.b =right.b;
        ans.index =right.index;

        }
    }

    else{
        if (left.b<right.b){
        ans.a = left.a;
        ans.b = left.b;
        ans.index = left.index;}
        else{
        ans.a = right.a;
        ans.b = right.b;
        ans.index = right.index;
        }
    }


    return ans;

}

int main() {

	// Write your code here
    int n;
    cin>>n;

    node1 *arr=new node1[n];

    for(int i=0;i<n;i++){
        cin>>arr[i].a;
    }
    for(int i=0;i<n;i++){
        cin>>arr[i].b;
        arr[i].index = i+1;
    }

    node* tree=new node[4*n];
    buildTree(arr,tree,0,n-1,1);

    int t;
    cin>>t;

    while(t--){
        int l,r;
        cin>>l>>r;

        node answer;
        answer = query(tree,0,n-1,1,l-1,r-1);
        cout<<answer.index<<endl;
    }


    delete arr;
    delete tree;







}
