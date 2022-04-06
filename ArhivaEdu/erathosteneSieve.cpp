#include <bits/stdc++.h>
 
using namespace std;
 
FILE *fin = fopen ("ciur.in", "r"), *fout = fopen ("ciur.out", "w");
 
const int MAXN  = 2e6;
 
bool ciur[MAXN + 1];
 
int main() {
  int n, d, sol, i;
  fscanf (fin, "%d", &n);
  ciur[1] = ciur[0] = 1;
  for (d = 2; d * d <= n; d++)
    if (ciur[d] == 0)
      for (i = d * d; i <= n; i = i + d)
        ciur[i] = 1;
  sol = 0;
  for (i = 2; i <= n; i++)
    sol = sol + (1 - ciur[i]);
  fprintf (fout, "%d", sol);
  return 0;
}
