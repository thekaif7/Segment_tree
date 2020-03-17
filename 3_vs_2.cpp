#include <bits/stdc++.h>
using namespace std;
struct _ { ios_base::Init i; _() { cin.sync_with_stdio(0); cin.tie(0);cout.tie(0); } } _;

#define READ(FILE) freopen(FILE,"r",stdin)
#define WRITE(FILE) freopen(FILE,"w",stdout)

#define ict int t;cin>>t;while(t--)
#define lct long long int t;cin>>t;while(t--)
#define in(a) int a; cin>>a;
#define llin(a) ll a; cin>>a;

#define srep(i,a,b) for(ll i=a;i<b;i++)
#define rep(i,n) for(ll i=0;i<n;i++)

#define pb push_back

typedef long long int ll; // [9,223,372,036,854,775,807 to -9.....808]
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef pair<int, int> pii;
typedef pair<ll,ll> pll;
typedef set<int> si;
typedef set<ll> sl;
typedef map<string, ll> mapsl;
typedef map<string, int> mapsi;
typedef map<int,int> mapii;
typedef map<ll, ll> mapll;

ll tree[300000];
ll arr[100005];
ll p[100005];

void fastpow()
{
    p[0]=1;
    for(int i=1;i<=100000;++i)
        p[i]=(p[i-1]*2)%3;
}

void build(ll i, ll st, ll en)
{
    if(st == en)
    {
        tree[i] = arr[st];
    }
    else
    {
        ll mid = (st + en) / 2;
        build(2*i, st, mid);
        build(2*i+1, mid+1, en);
        tree[i] = (tree[2*i]*p[en-mid] + tree[2*i+1])%3;
    }
}

void update(ll i, ll st, ll en, ll idx)
{
    if(st == en)
    {
        tree[i] = 1;
        arr[idx] = 1;
    }
    else
    {
        ll mid = (st + en) / 2;
        if(st <= idx and idx <= mid)
        {
            update(2*i, st, mid, idx);
        }
        else
        {
            update(2*i+1, mid+1, en, idx);
        }
        tree[i] = ((tree[2*i]*p[en-mid]%3) + tree[2*i+1])%3;
    }
}

ll query(ll i, ll st, ll en, ll l, ll r)
{
    if(r < st or en < l)
    {
        return 0;
    }
    if(l <= st and en <= r)
    {
        return (tree[i]*p[r-en])%3;
    }
    ll mid = (st + en) / 2;
    ll p1 = query(2*i, st, mid, l, r);
    ll p2 = query(2*i+1, mid+1, en, l, r);
    return (p1 + p2)%3;
}


int main()
{
    llin(n);
    string str;
    cin>>str;
    fastpow();
    for(ll i=1;i<=n;i++)
    {
        arr[i]=str[i-1]-48;
    }
    build(1,1,n);
    lct
    {
        llin(chk);
        llin(l);
        if(chk==0)
        {
            llin(r);
            cout<<query(1,1,n,l+1,r+1)<<endl;
        }
        else
        {
            if(str[l]=='0')
            {
                str[l]='1';
                arr[l+1]=1;
                update(1,1,n,l+1);
            }
        }
    }
}
