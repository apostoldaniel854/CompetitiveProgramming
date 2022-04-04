#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5;

int perm[1 + maxn];
string dir;

/**
the answer is actually how much we find if we continue doing LIS for continous seq of U and LDS for D
**/

int main() {
    int N;
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> perm[i];
    cin >> dir;
    int p = 0;
    int i = 2;
    int lst = perm[1];
    while (i <= N && p < dir.size()) {
        char curdir = dir[p];
        if (curdir == 'U') {
            /// LIS
            set <int> LIS;
            LIS.insert(lst);
            while (i <= N && p < dir.size() && dir[p] == curdir) {
                /// add to LIS
                lst = perm[i];
                auto it = LIS.lower_bound(perm[i]);
                if (it == LIS.end())
                    p++;
                else
                    LIS.erase(it);
                LIS.insert(perm[i]);
                i++;
            }
        }
        else {
            /// LDS
            set <int> LDS;
            LDS.insert(-lst);
            while (i <= N && p < dir.size() && dir[p] == curdir) {
                /// add to LDS
                lst = perm[i];
                auto it = LDS.lower_bound(-perm[i]);
                if (it == LDS.end())
                    p++;
                else
                    LDS.erase(it);
                LDS.insert(-perm[i]);
                i++;
            }
        }
    }
    cout << p << "\n";
    return 0;
}
