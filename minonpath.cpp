#include <bits/stdc++.h>

using namespace std;

const int max_n = 300000;
const int max_lg = 30;
const int inf = (int)1e9;

int tim = 0;
int tin[max_n];
int tout[max_n];
int tup[max_n][max_lg];
int mup[max_n][max_lg];
bool vis[max_n];
int cost[max_n];
vector <pair<int, int>> a[max_n];
int deep[max_n];

bool pr(int u, int v) {
    return (tin[u] <= tin[v] && tout[v] <= tout[u]);
}

int lca(int x, int y) {
    int ans = inf;
    bool b = false, b1 = false;
    if (pr(x, y)) b = true;
    if (pr(y, x)) b1 = true;
    if (!b) {
        for (int i = max_lg - 1; i >= 0; i--) {
            if (!pr(tup[x][i], y)) {
                ans = min(ans, mup[x][i]);
                x = tup[x][i];
            }
        }
        ans = min(ans, cost[x]);
    }
    if (!b1) {
        for (int i = max_lg - 1; i >= 0; i--) {
            if (!pr(tup[y][i], x)) {
                ans = min(ans, mup[y][i]);
                y = tup[y][i];
            }
        }
        ans = min(ans, cost[y]);
    }
    return ans;
}

void dfs(int v, int p, int dp, int cost1) {
    vis[v] = true;
    tin[v] = tim++;
    tup[v][0] = p;
    mup[v][0] = cost1;
    cost[v] = cost1;
    deep[v] = dp;
    for (int i = 1; i < max_lg; i++) {
        tup[v][i] = tup[tup[v][i - 1]][i - 1];
        mup[v][i] = min(mup[v][i - 1], mup[tup[v][i - 1]][i - 1]);
    }
    for (int i = 0; i < (int)a[v].size(); i++) {
        if (!vis[a[v][i].first]) {
            dfs(a[v][i].first, v, dp + 1, a[v][i].second);
        }
    }
    tout[v] = tim++;
}

int main() {
    freopen("minonpath.in", "r", stdin);
    freopen("minonpath.out", "w", stdout);
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        a[i + 1].push_back(make_pair(x - 1, y));
        a[x - 1].push_back(make_pair(i + 1, y));
    }
    dfs(0, 0, 0, inf);

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        cout << lca(x - 1, y - 1) << endl;
    }
}

