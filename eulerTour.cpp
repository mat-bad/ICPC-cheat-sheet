// EULER
int deg[N];
vector <int> adj[N], tour;
void add_edge(int u, int v) {
   adj[u].push_back(v);
   deg[u]++;
   deg[v]--;
}
void euler(int u) {
   while (adj[u].size()) {
       int v = adj[u].back();
       adj[u].pop_back();
       euler(v);
   }
   tour.push_back(u);
}
void make_graph() {
   cin >> n >> m;
   while (m--) {
       int u, v;
       cin >> u >> v;
       add_edge(--u, --v);
   }
}
void find_euler_tour() {
   int x1 = -1, x2 = -1;
   for (int u = 0; u < N; u++)
       if (x1 == -1 && deg[u] == 1)
           x1 = u;
       else if (x2 == -1 && deg[u] == -1)
           x2 = u;
       else if (deg[u] != 0)
           return cout << "NO" << endl, 0;
   for (int u = 0; u < N; u++)
       if (adj[u].size() && (u == x1 || x1 == -1)) {
           euler(u);
           break;
       }

   for (int u = 0; u < N; u++)
       if (adj[u].size())
           return cout << "NO" << endl, 0;
   reverse(tour.begin(), tour.end());
   for (int x: tour)
       cout << x + 1 << ' ';
}
