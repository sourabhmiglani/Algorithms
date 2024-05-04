#include <bits/stdc++.h>
using namespace std;

#define mod  1000000007
#define mod2 1000000009
#define MAX 212345

typedef long long ll;

// String Hashing
//
// Complexidades:
// construtor - O(|s|)
// operator() - O(1)

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

int uniform(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

template<int MOD> struct str_hash { // 116fcb
	static int P;
	vector<ll> h, p;
	str_hash(string s) : h(s.size()), p(s.size()) {
		p[0] = 1, h[0] = s[0];
		for (int i = 1; i < (int)s.size(); i++)
			p[i] = p[i - 1]*P%MOD, h[i] = (h[i - 1]*P + s[i])%MOD;
	}
	ll operator()(int l, int r) { // retorna hash s[l...r]
		ll hash = h[r] - (l ? h[l - 1]*p[r - l + 1]%MOD : 0);
		return hash < 0 ? hash + MOD : hash;
	}
};
template<int MOD> int str_hash<MOD>::P = uniform(256, MOD - 1); // l > |sigma|




void solve() {
	int n, L, R;
	cin >> n >> L >> R;
	string s;
	cin >> s;


	str_hash<mod> hash(s);
	str_hash<mod2> hash2(s);

	auto eq = [&](int i, int j) -> bool {
		return hash(0, j-i) == hash(i, j) and hash2(0,j-i) == hash2(i,j);	
	};
	
	int l=1, r=n+1;
	while(l < r) {
		int m = (l+r)/2;
		int cnt = 0;
		for(int i=0; i+m <= n; ) {
			if(eq(i, i+m-1)) i+=m, cnt++;
			else i++;
		}
		if(cnt >= L) l = m+1;
		else r = m;
	}
	cout << r-1 << endl;
}


int32_t main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
