#include <bits/stdc++.h>
 
using namespace std;
 
const int MAXN = 1e5;
 
int nr;
int sol[1 + MAXN], a[1 + MAXN], poz[1 + MAXN], scm[1 + MAXN];
 
inline int get (int n) {
  int st, dr, p;
  st = 1; dr = nr;
  p = 0;
  while (st <= dr) {
    int mij = (st + dr) / 2;
    if (sol[mij] >= n) {
      dr = mij - 1;
      p = mij;
    }
    else
      st = mij + 1;
  }
  return p;
}
 
int main() {
  int n, i, p;
 
  freopen ("scmax.in", "r", stdin);
  freopen ("scmax.out", "w", stdout);
 
  scanf ("%d", &n);
  for (i = 1; i <= n; i++)
    scanf ("%d", &a[i]);
 
  sol[1] = a[1];
  poz[1] = nr = 1;
  for (i = 2; i <= n; i++)
    if (a[i] > sol[nr]) {
      nr++;
      poz[i] = nr;
      sol[nr] = a[i];
    }
    else {
      p = get (a[i]);
      sol[p] = a[i];
      poz[i] = p;
    }
 
  printf ("%d\n", nr);
  i = n;
  n = nr;
  while (nr) {
    if (poz[i] == nr) {
      scm[nr] = a[i];
      nr--;
    }
    i--;
  }
  for (i = 1; i <= n; i++)
    printf ("%d ", scm[i]);
  return 0;
}
