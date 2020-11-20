#include <iostream>
#include <algorithm>
#include <stdio.h>

using namespace std;

const int MAX_M = 500000;
const int MAX_N = 110;
const long long INF = 1e10;
long long pr[MAX_N][MAX_N];
long long b[MAX_N][MAX_N];
long long num[MAX_N][MAX_N];
long long ans[MAX_M];
long long ar[MAX_M];
long long c[MAX_M];
int cnt_k = 0;

int main()
{
    freopen("floyd.in", "r", stdin);
    freopen("floyd.out", "w", stdout);
    int n, m, cnt;
    cin >> n >> m >> cnt;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                b[i][j] = INF;
            }
        }
        b[i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        x--;
        y--;
        if (-w < b[x][y]) {
            b[x][y] = -w;
            pr[x][y] = x;
            num[x][y] = i;
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (b[i][k] + b[k][j] < b[i][j] && b[i][k] != INF && b[k][j] != INF) {
                    if (i == k || k == j) {
                        pr[i][j] = i;
                    } else {
                        pr[i][j] = pr[k][j];
                    }
                    b[i][j] = b[i][k] + b[k][j];
                }
            }
        }
    }
    for (int i = 0; i < cnt; i++) {
        cin >> ar[i];
        ar[i]--;
        if (i != 0) {
            for (int j = 0; j < n; j++) {
                if (b[ar[i - 1]][j] != INF && b[j][ar[i]] != INF && b[j][j] < 0) {
                    cout << "infinitely kind" << endl;
                    return 0;
                }
            }
        }
    }
    int p, sum = 0, e;
    for (int i = 0; i < cnt; i++) {
        e = 0;
        if (i != 0) {
            int u = ar[i];
            while (u != p) {
                int u1 = pr[p][u];
                c[e] = num[u1][u];
                u = u1;
                e++;
            }
            for (int i = e - 1; i >= 0; i--) {
                ans[cnt_k] = c[i] + 1;
                cnt_k++;
            }
            sum += e;
        }
        p = ar[i];
    }
    cout << sum;
    cout << "\n";
    for (int i = 0; i < cnt_k; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
