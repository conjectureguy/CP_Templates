 for (ll i = 1; i <= n; i++) {
    cin >> a[i];
    fq[a[i]]++;
  }
  
  for (ll i = 1; i < 200006; i++) {
    for (ll j = i; j < 200006; j+=i) {
      // mul2[i] += fq[j];
      // mul3[i] += fq[j];
      mul4[i] += fq[j];
      cnt[i] += fq[j];
    }
    // mul2[i] = NC2(mul2[i]);
    // mul3[i] = NC2(mul3[i]);
    mul4[i] = mul4[i]*mul4[i];
    cnt[i] = cnt[i]*cnt[i];
  }
  
  for(ll i=200005;i>=1;i--) {
    for(ll j=2*i;j<=200005;j+=i){
      // mul2[i] -= mul2[j];
      // mul3[i] -= mul3[j];
      mul4[i] -= mul4[j];
    }
  }
  // cout << mul4[1] << endl;
  // cout << mul2[1] << endl;
  //mul[i] -> pairs with gcd exactly equal to i