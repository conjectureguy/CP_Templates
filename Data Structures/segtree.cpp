void construct_segment_tree(vector<ll>& segtree,
                            vector<ll>& a, ll n)
{
    // assign values to leaves of the segment tree
    for (ll i = 0; i < n; i++)
        segtree[n + i] = a[i];
 
    /* assign values to internal nodes
    to compute maximum in a given range */
    for (ll i = n - 1; i >= 1; i--)
        segtree[i] = max(segtree[2 * i],
                         segtree[2 * i + 1]);
}
 
void update(vector<ll>& segtree, ll pos, ll value,
            ll n)
{
    // change the index to leaf node first
    pos += n;
 
    // update the value at the leaf node
    // at the exact index
    segtree[pos] = value;
 
    while (pos > 1) {
 
        // move up one level at a time in the tree
        pos >>= 1;
 
        // update the values in the nodes in
        // the next higher level
        segtree[pos] = max(segtree[2 * pos],
                           segtree[2 * pos + 1]);
    }
}
 
long long range_query(vector<ll>& segtree, ll left, ll
                                                    right,
                ll n)
{
    /* Basically the left and right indices will move
        towards right and left respectively and with
        every each next higher level and compute the 
        maximum at each height. */
    // change the index to leaf node first
    left += n;
    right += n;
 
    // initialize maximum to a very low value
    ll ma = LONG_MIN;
 
    while (left < right) {
 
        // if left index in odd
        if (left & 1) {
            ma = max(ma, segtree[left]);
 
            // make left index even
            left++;
        }
 
        // if right index in odd
        if (right & 1) {
 
            // make right index even
            right--;
 
            ma = max(ma, segtree[right]);
        }
 
        // move to the next higher level
        left /= 2;
        right /= 2;
    }
    return ma;
}
