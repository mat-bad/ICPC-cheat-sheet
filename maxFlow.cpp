// min-cut & max-flow
// e[u][v] represents the remaining capacity of the uv edge in that direction
// look out for MX!

const ll MX = 1e3, LOGW = 31;

ll N, n, m, e[MX][MX], flow[MX][MX];
bool mark_f[MX];

void add_edge(int u, int v, ll cap) {
   e[u][v] += cap;
}

void push_flow(int u, int v, ll f) {
   flow[u][v] += f;
   flow[v][u] -= f;
   e[u][v]-=f;
   e[v][u]+=f;
}

ll dfs(int u, ll in_f, ll min_w, int sink){
   if(u==sink) return in_f;
   mark_f[u] = true;
   for(int v=1; v<=N; v++) if(!mark_f[v] and e[u][v]>=min_w){
       ll f = dfs(v, min(in_f, e[u][v]), min_w, sink);
       if(f) {
           push_flow(u, v, f);
           return f;
       }
   }
   return 0;
}

int main(){
   cin>>n;
   N = 2*n+2;
   FOR(i, 1, n){
       string s;
       cin>>s;
       FOR(j, 0, n-1) if(s[j] != '.'){
           add_edge(i, j+n+1, inf);
       }
   }
   int source = 2*n+1;
   int sink = 2*n+2;
   FOR(i, 1, n) {
       add_edge(source, i, 1);
   }
   FOR(i, n+1, 2*n) {
       add_edge(i, sink, 1);
   }
   ll max_flow = 0;
   // LOGW is the log of max edge capacity
   ll i = 1ll<<LOGW; while(i>0){
       FOR(u, 1, N) mark_f[u] = false;
       ll f = dfs(source, infl, i, sink);
       max_flow+= f;
       if(f==0) i>>=1;
   }
   cout<<max_flow<<'\n';
   //iterate all existing edges:
   FOR(u, 1, N) FOR(v, 1, N) if(flow[u][v])
       // condition for an edge to be in min cut
       if(mark_f[u] and !mark_f[v])
           cout<<u<<' '<<v<<'\n';
}
/*
  in bipartite graphs:
  min edge cover = n - max matching
  min vertex cover = n - max independent set
*/