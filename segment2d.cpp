struct seg2d{
   int n, m;
   node arr[N][N];
   node seg[4 * N][4 * N];
   node emp;
   node merge(node a, node b){
       node rt;
       rt.x = max(a.x, b.x);
       return rt;
   }
	void buildy(int idx, int lx, int rx, int idy, int ly, int ry){
       if(ry - ly == 1){
           if (rx - lx == 1)
               seg[idx][idy] = arr[lx][ly];
           else
               seg[idx][idy] = merge(seg[2 * idx][idy], seg[2 * idx + 1][idy]);
       }else {
           int mid = (ly + ry) / 2;
           buildy(idx, lx, rx, 2 * idy, ly, mid);
           buildy(idx, lx, rx, 2 * idy + 1, mid, ry);
           seg[idx][idy] = merge(seg[idx][2 * idy], seg[idx][2 * idy + 1]);
       }
   }
   void buildx(int idx, int lx, int rx){
       if(rx - lx != 1){
           int mid = (lx + rx) / 2;
           buildx(2 * idx, lx, mid);
           buildx(2 * idx + 1, mid, rx);
       }
       buildy(idx, lx, rx, 1, 1, m + 1);
   }
   node gety(int idx, int idy, int ly, int ry, int st, int en) {
       if (st >= en)
           return emp;
       if (ly == st && ry == en)
           return seg[idx][idy];
       int mid = (ly + ry) / 2;
       return merge(gety(idx, 2 * idy, ly, mid, st, min(en, mid))
               , gety(idx, 2 * idy + 1, mid, ry, max(st, mid), en));
   }

   node getx(int idx, int lx, int rx, int stx, int enx, int sty, int eny) {
       if (stx >= enx)
           return emp;
       if (lx == stx && rx == enx)
           return gety(idx, 1, 1, m + 1, sty, eny);
       int mid = (lx + rx) / 2;
       return merge(getx(2 * idx, lx, mid, stx, min(enx, mid), sty, eny)
               , getx(2 * idx + 1, mid, rx, max(stx, mid), enx, sty, eny));
   }
   void updatey(int idx, int lx, int rx, int idy, int ly, int ry, int x, int y, int new_val) {
       if (ry - ly == 1) {
           if (rx - lx == 1){
               node X;
               X.x = new_val;
               seg[idx][idy] = X;
           }
           else
               seg[idx][idy] = merge(seg[2 * idx][idy], seg[2 * idx + 1][idy]);
       } else {
           int mid = (ly + ry) / 2;
           if (y < mid)
               updatey(idx, lx, rx, 2 * idy, ly, mid, x, y, new_val);
           else
               updatey(idx, lx, rx, 2 * idy + 1, mid, ry, x, y, new_val);
           seg[idx][idy] = merge(seg[idx][2 * idy], seg[idx][2 * idy + 1]);
       }
   }

   void updatex(int idx, int lx, int rx, int x, int y, int new_val) {
       if (rx - lx > 1) {
           int mid = (lx + rx) / 2;
           if (x < mid)
               updatex(2 * idx, lx, mid, x, y, new_val);
           else
               updatex(2 * idx + 1, mid, rx, x, y, new_val);
       }
       updatey(idx, lx, rx, 1, 1, m + 1, x, y, new_val);
   }
};
