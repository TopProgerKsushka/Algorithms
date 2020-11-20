#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100010;
const int m1 = 21563;
const int m2 = 16714589;

int d[30][MAX_N];
int a[MAX_N];
int u, p_u;
int v, p_v;
int ans, p_ans;
int max_power[MAX_N];

int get(int l, int r) {
    int p = max_power[r - l];
    return min(d[p][l], d[p][r - (1 << p)]);
}

int main()
{
    int n, m;
    cin >> n >> m >> a[0];
    for (int i = 1; i < n; i++) {
        a[i] = (23 * a[i - 1] + m1) % m2;
    }
    cin >> p_u >> p_v;
    max_power[0] = 0;
    for (int i = 1; i < n; i++) {
        if (i == (1 << (max_power[i - 1] + 1))) {
            max_power[i] = max_power[i - 1] + 1;
        } else {
            max_power[i] = max_power[i - 1];
        }
    }
    for (int i = 0; i < n; i++) {
        d[0][i] = a[i];
    }
    for (int i = 1; i < 30; i++) {
        for (int k = 0; k < n; k++) {
            if (k + (1 << (i - 1)) < n) {
                d[i][k] = min(d[i - 1][k], d[i - 1][k + (1 << (i - 1))]);
            } else {
                d[i][k] = d[i - 1][k];
            }
        }
    }
    for (int i = 1; i < m; i++) {
        p_ans = get(min(p_u, p_v) - 1, max(p_u, p_v));
        u = (17 * p_u + 751 + p_ans + 2 * i) % n + 1;
        v = (13 * p_v + 593 + p_ans + 5 * i) % n + 1;
        p_u = u;
        p_v = v;
    }
    printf("%d", p_u);
    cout << " ";
    printf("%d", p_v);
    cout << " ";
    p_ans = get(min(p_u, p_v) - 1, max(p_v, p_u));
    printf("%d", p_ans);
    return 0;
}
