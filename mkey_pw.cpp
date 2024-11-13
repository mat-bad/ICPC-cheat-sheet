inline int mkey(int a, int b) {
   int rt = a + b;
   if(rt >= md)
       rt -= md;
   return rt;
}

int pw(int a, int b) {
   int rt = 1;
   while(b > 0){
       if(b & 1)
           rt = 1LL * rt * a % md;
       b /= 2;
       a = 1LL * a * a % md;
   }
   return rt;
}
