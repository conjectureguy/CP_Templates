#include<bits/stdc++.h>

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>


#define pb push_back
#define ff first
#define ss second
#define endl '\n'
#define all(a) (a).begin(), (a).end()
#define max3(a,b,c) max(max(a,b),c)
#define max4(a,b,c,d) max(max(a,b),max(c,d))
#define min3(a,b,c) min(min(a,b),c)
#define min4(a,b,c,d) min(min(a,b),min(c,d))
#define gap " "
#define vi vector<int>
#define vll vector<ll>
#define vpll vector<pair<ll,ll>>
#define rev_sort(v) sort(all(v),greater<int>())
const double PI = acos(-1);
const long long INF = 1e18;
const long long MOD = 1000000007;

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; // find_by_order, order_of_key

#ifdef ONLINE_JUDGE
#define debug(...) 42
#else
#include "debug.h"
#endif

/*-----------  END -----------*/

// https://codeforces.com/problemset/problem/1674/F 

template<class T, class U>
// T -> node, U->update.
struct Lsegtree{
    vector<T>st;
    vector<U>lazy;
    ll n;
    T identity_element;
    U identity_update;
    Lsegtree(ll n, T identity_element, U identity_update)
    {
        this->n = n;
        this->identity_element = identity_element;
        this->identity_update = identity_update;
        st.assign(4*n,identity_element);
        lazy.assign(4*n, identity_update);
    }
    T combine(T l, T r)
    {
        // change this function as required.
        T ans = (l + r);
        return ans;
    }
    void buildUtil(ll v, ll tl, ll tr, vector<T>&a)
    {
        if(tl == tr)
        {
            st[v] = a[tl];
            return;
        }
        ll tm = (tl + tr)>>1;
        buildUtil(2*v + 1, tl, tm,a);
        buildUtil(2*v + 2,tm+1,tr,a);
        st[v] = combine(st[2*v + 1], st[2*v + 2]);
    }
    // change the following 2 functions, and you're more or less done.
    T apply(T curr, U upd, ll tl, ll tr)
    {
        T ans = (tr-tl+1)*upd;
        return ans;
    }
    U combineUpdate(U old_upd, U new_upd, ll tl, ll tr)
    {
        U ans = old_upd;
        ans=new_upd;
        return ans;
    }  
    void push_down(ll v, ll tl, ll tr)
    {
        if(lazy[v] == identity_update)return;
        st[v] = apply(st[v], lazy[v], tl, tr);
        if(2*v + 2 < 4*n)
        {
            ll tm = (tl + tr)>>1;
            lazy[2*v + 1] = combineUpdate(lazy[2*v+1], lazy[v], tl, tm);
            lazy[2*v + 2] = combineUpdate(lazy[2*v+2], lazy[v], tm+1,tr);            
        }
        lazy[v] = identity_update;
    }
    T queryUtil(ll v, ll tl, ll tr, ll l, ll r)
    {
        push_down(v,tl,tr);
        if(l > r)return identity_element;
        if(tr < l or tl > r)
        {
            return identity_element;
        }
        if(l <= tl and r >= tr)
        {
            return st[v];
        }
        ll tm = (tl + tr)>>1;
        return combine(queryUtil(2*v+1,tl,tm,l,r), queryUtil(2*v+2,tm+1,tr,l,r));
    }
 
    void updateUtil(ll v, ll tl, ll tr, ll l, ll r, U upd)
    {
        push_down(v,tl,tr); 
        if(tr < l or tl > r)return;
        if(tl >=l and tr <=r)
        {
            lazy[v] = combineUpdate(lazy[v],upd,tl,tr);
            push_down(v,tl,tr);
        }
        else
        {
            ll tm = (tl + tr)>>1;
            updateUtil(2*v+1,tl,tm,l,r,upd);
            updateUtil(2*v+2,tm+1,tr,l,r,upd);
            st[v] = combine(st[2*v + 1], st[2*v+2]);
        }
    }



    void build(vector<T>a)
    {
        assert(a.size() == n);
        buildUtil(0,0,n-1,a);
    }
    T query(ll l, ll r)
    {
        return queryUtil(0,0,n-1,l,r);
    }
    void update(ll l,ll r, U upd)
    {
        updateUtil(0,0,n-1,l,r,upd);
    }
};

int getloc(ll x, ll y, ll n, ll m){
  ll loc = y*n + x;
  return loc;
}

void solve(int ts = 1)
{
  ll n, m, q; cin >> n >> m >> q;
  string a[n];
  for (int i = 0; i < n; ++i)
  {
    cin >> a[i];
  }
  vll v;
  ll cnt = 0;
  for (int i = 0; i < m; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      if (a[j][i] == '*')
      {
        v.pb(1);
        cnt++;
      }
      else v.pb(0);
    }
  }
  Lsegtree<ll,ll> st(n*m, 0, -1);
  st.build(v);
  // debug(v);
  while(q--){
    ll x, y; cin >> x >> y;
    x--; y--;
    ll loc = getloc(x, y, n, m);
    if (v[loc] == 1)
    {
      cnt--;
      v[loc] = 0;
      st.update(loc, loc, 0);
    }
    else{
      cnt++;
      v[loc] = 1;
      st.update(loc, loc, 1);
    }
    ll fill = st.query(0, cnt-1);
    // debug(v, cnt, loc);
    cout << cnt - fill << endl;
  }
}


int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    freopen("error.out", "w", stderr);
  #endif
 

  int ts;
  ts=1;
  // cin>>ts;
  for(int i = 1; i <= ts; i++){
    solve(i);
  }
}