	
#include <bits/stdc++.h>
 
using namespace std;
 
const int SIZE = 1 << 20;
 
char s[SIZE];
int p = 0;
inline int eval ();
 
inline int fact () {
  int nr, sign;
  nr = 0;
  sign = 1;
  if (s[p] == '-') {
    p++;
    sign = -1;
  }
  if (s[p] == '(') {
    p++;
    nr = eval ();
    p++;
  }
  else {
    while (isdigit (s[p])) {
      nr = nr * 10 + s[p] - '0';
      p++;
    }
  }
  return nr * sign;
 
}
 
inline int term () {
  int sum = fact ();
  while (s[p] == '*' || s[p] == '/')
    if (s[p++] == '*')
      sum *= fact ();
    else
      sum /= fact ();
  return sum;
}
 
inline int eval () {
  int sum = term ();
  while (s[p] == '+' || s[p] == '-') {
    if (s[p++] == '+')
      sum += term ();
    else
      sum -= term ();
  }
  return sum;
}
 
int main() {
  freopen ("evaluare.in", "r", stdin);
  freopen ("evaluare.out", "w", stdout);
 
  scanf ("%s", s);
  p = 0; /// pointer
  printf ("%d\n", eval ());
 
  return 0;
}
