struct node{
  ll val, weight, sze, rv;
  char ch;
  node *left, *right;
  node(ll x, char _ch): val(x), weight(rng()), sze(1), rv(0), ch(_ch), left(NULL), right(NULL){}
};

int size(node *treap){
  if(treap) return treap->sze;
  else return 0;
}

void push(node *root){
  if (root && root->rv)
  {
    root->rv = 0;
    swap(root->left, root->right);
    if (root->left) root->left->rv ^= 1;
    if (root->right) root->right->rv ^= 1;
  }
}

void split(node *treap, node *&left, node *&right, ll rem){
  if (!treap)
  {
    left = right = NULL;
    return;
  }

  push(treap);

  if (size(treap->left) < rem)
  {
    // go to the right
    split(treap->right, treap->right, right, rem-size(treap->left)-1);
    left = treap;
  }
  else{
    // go to left
    split(treap->left, left, treap->left, rem);
    right = treap;
  }
  treap->sze = 1 + size(treap->left) + size(treap->right);
}

void merge(node *&treap, node *left, node *right){
  if (!left)
  {
    treap = right;
    return;
  }
  if (!right)
  {
    treap = left;
    return;
  }

  push(left);
  push(right);

  if (left->weight < right->weight)
  {
    merge(left->right, left->right, right);
    treap = left;
  }
  else{
    merge(right->left, left, right->left);
    treap = right;
  }
  treap->sze = 1 + size(treap->left) + size(treap->right);
}


void print(node *root){
  if (!root) return;
  push(root);
  print(root->left);
  cout << root->ch;
  print(root->right);
}

void reverse(node *&root, ll l, ll r){
  if (!root) return;
  node *left, *mid, *right;
  split(root, left, mid, l-1);
  split(mid, mid, right, r-l+1);
  mid->rv ^= 1;
  merge(left, left, mid);
  merge(root, left, right);
}
