//IN the name of Allah.
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5, L = 18;
int n, par[N][L], st[N], en[N], cnt, h[N], Q, imp[N], start[N], power[N], k, m;
vector <pair <int, int>> tree[N];
vector <int> adj[N], all;

void dfsBuild(int u = 1, int p = 0) {
	st[u] = cnt++;
	for (int i = 1; i < L; i++)
		par[u][i] = par[par[u][i - 1]][i - 1];
	for (int v: adj[u])
		if (v ^ p) {
			h[v] = h[u] + 1;
			par[v][0] = u;
			dfsBuild(v, u);
		}
	en[u] = cnt;
}

int lca(int u, int v) {
	if (h[u] < h[v])
		swap(u, v);
	for (int i = L - 1, len = h[u] - h[v]; ~i; i--)
		if (1 << i & len)
			u = par[u][i];
	if (u == v)
		return u;
	for (int i = L - 1; ~i; i--)
		if (par[u][i] ^ par[v][i]) {
			u = par[u][i];
			v = par[v][i];
		}
	return par[u][0];
}

bool cmp(int u, int v) {
	return st[u] < st[v];
}

void auxiliary() {
	sort(all.begin(), all.end(), cmp);
	for (int i = 0; i < m + k - 1; i++)
		all.push_back(lca(all[i], all[i + 1]));
	sort(all.begin(), all.end(), cmp);
	all.resize(unique(all.begin(), all.end()) - all.begin());
	stack <int> s;
	for (int u: all) {
		while (s.size() && (st[s.top()] > st[u] || en[s.top()] <= st[u]))
			s.pop();
		if (s.size())
			tree[s.top()].push_back({u, h[u] - h[s.top()]});
		s.push(u);
	}
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 0, u, v; i < n - 1; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfsBuild();
}		
