// mcmf
ll n, m, N=0, M=0;
struct edge {
   ll u, v, cost, cap;
   edge () {}
   edge(int u1, int v1, int cost1, int cap1){
       u = u1;
       v = v1;
       cost = cost1;
       cap = cap1;
   }
};
edge ed[MXE];
vector<int> adj[MX];

// edges from left to right
void add_edge(int u, int v, int cap, int cost=0) {
   ed[M] = edge(u, v, cost, cap);
   adj[u].pb(M++);
   ed[M] = edge(v, u, -cost, 0);
   adj[v].pb(M++);   
}

// used spfa
pii cheapest_flow(int source, int sink) {
   int d[MX] = {}, p[MX]={};
   bool inQ[MX] = {};
   queue<int> q;
   FOR(i, 1, N+2) d[i] = inf;
   d[source] = 0;
   int u = source;
   inQ[u] = true;
   q.push(u);
   while(!q.empty()) {
       u = q.front();
       q.pop();
       inQ[u] = false;
       for(int i:adj[u]) if(ed[i].cap) {
           int v = ed[i].v;
           if(d[v] > d[u] + ed[i].cost) {
               d[v] = d[u] + ed[i].cost;
               p[v] = i;
               if(!inQ[v]) q.push(v);
             }
           }
       }
       u = sink;
       pii ans = pii(0, 0);
       if(d[u] == inf) return ans;
       while(u != source) {
           int i=p[u];
           ed[i].cap --;
           ed[i^1].cap ++;
           ans.S += ed[i].cost;
           u = ed[i].u;
       }
       ans.F = 1;
       return ans;
}

// returns (max flow, min cost);
pii mcmf(int source, int sink) {
   pii fc; // fc : (flow, cost)
   pii ans = pii(0, 0);
   do {
       fc = cheapest_flow(source, sink);
       ans.F += fc.F;
       ans.S += fc.S;
   } while(fc.F > 0);
   return ans;
}
// build graph in main using add_edge, don't forget to check N, MX, source, sink
