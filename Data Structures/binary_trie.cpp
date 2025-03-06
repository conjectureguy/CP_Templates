struct BinaryTrie{
  ll ct = 0;
  ll n;
  vector<vll> Trie;

  BinaryTrie(ll m){
    n = m + 100; //change this if RE
    Trie = vector<vll>(2, vll(n*30, 0));
  }

  void insert(ll x) {
    ll node = 0;
    for (int i = 30; i >= 0; i--) {
      ll y = (x>>i)&1;
      if (!Trie[y][node]) Trie[y][node] = ++ct;
      node = Trie[y][node];
    }
  }

  ll search(ll x){
    ll node = 0, ans = 0;
    for (int i = 30; i >= 0; --i)
    {
      ll y = (x>>i)&1;
      if (Trie[y][node])
      {
        // implement
        node = Trie[y][node];
      }
      else{
        // implement
        node = Trie[y^1][node];
      }
    }
    // check what to return
    return ans;
  }
};
