struct AC{
  static const int K = 26;
  
  struct Vertex{
    vll next, go;
    bool output = false;
    ll p = -1, link = -1;
    char pch;

    Vertex(ll p = -1, char ch = '$'): next(K), go(K), p(p), pch(ch) {
      fill(all(next), -1);
      fill(all(go), -1);
    }
  };

  vector<Vertex> t;

  AC(): t(1) {}

  void add_string(const string &s){
    ll v = 0;
    for (char ch: s){
      ll c = ch - 'a';
      if (t[v].next[c] == -1)
      {
        t[v].next[c] = sz(t);
        t.emplace_back(v, ch);
      }
      v = t[v].next[c];
    }
    t[v].output = true;
  }

  ll get_link(ll v){
    if (t[v].link == -1)
    {
      if (v == 0 || t[v].p == 0) t[v].link = 0;
      else t[v].link = go(get_link(t[v].p), t[v].pch);
    }
    return t[v].link;
  }

  ll go(ll v, char ch){
    ll c = ch - 'a';
    if (t[v].go[c] == -1)
    {
      if (t[v].next[c] != -1) t[v].go[c] = t[v].next[c];
      else{
        if (v == 0) t[v].go[c] = 0;
        else t[v].go[c] = go(get_link(v), ch);
      }
    }
    return t[v].go[c];
  }
};
