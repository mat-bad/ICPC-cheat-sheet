// NTT mode = 988244353
const int md = 998244353;
int w[24], wi[24], inv2;

inline int mkey(int a,int b){
   int rt=a + b;
   if(rt >= md)
       rt-=md;
   return rt;
}

int pw(int a, int b){
   int rt = 1;
   while(b > 0){
       if(b & 1)
           rt = 1LL * rt * a % md;
       b /= 2;
       a = 1LL * a * a % md;
   }
   return rt;
}

void pre(){
   w[23] = 31;
   for(int i = 22; i >= 0; i--)
       w[i] = 1LL * w[i + 1] * w[i + 1] % md;
   for(int i = 0; i <= 23; i++)
       wi[i] = pw(w[i], md - 2);
   inv2 = pw(2, md - 2);
}
void fft(vector<int> &a, bool invert){
   int n = a.size();
   if(n == 1)
       return;
   vector<int> a0(n / 2), a1(n / 2);
   for(int i = 0; i <= n / 2 - 1; i++){
       a0[i] = a[2 * i];
       a1[i] = a[2 * i + 1];
   }
   fft(a0, invert);
   fft(a1, invert);

   int W = 1;
   int wn = w[__builtin_ctz(n)];
   if(invert)
       wn = wi[__builtin_ctz(n)];
	for(int i = 0; i <= n / 2 - 1; i++){
       a[i] = mkey(a0[i], (1LL * W * a1[i] % md));
       a[i + n / 2] = mkey(a0[i], (md - (1LL * W * a1[i] % md)));
       if(invert){
           a[i] = 1LL * a[i] * inv2 % md;
           a[i + n / 2] = 1LL * a[i + n / 2] * inv2 % md;
       }
       W = 1LL * wn * W % md;
   }
}

vector<int> mul(vector<int> a, vector<int> b){
   vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
   int n=1;
   while(n < (int)a.size() + (int)b.size()) n *= 2;
   fa.resize(n);
   fb.resize(n);
   fft(fa,0);
   fft(fb,0);
   for(int i = 0; i <= n - 1; i++)
       fa[i] = 1LL * fa[i] * fb[i] % md;
   fft(fa, 1);
   vector<int> res(n);
   for(int i = 0; i <= n - 1; i++){
       res[i] = fa[i];
   }
   return res;
}
