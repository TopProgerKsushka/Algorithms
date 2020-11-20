#include <bits/stdc++.h>

using namespace std;

int n, m;
long long max_ = 0;
struct ed {
    int v;
    int u;
    long long c;
    long long f;
};
long long const inf = 1000000000000000000;
vector <vector <int> > edges, edges_d;
vector <ed> ab_ed;
vector <long long> d;
void add_ed(int v, int u, int c) {
    ed x = {v, u, c, 0};
    ab_ed.push_back(x);
    max_ = max(max_, x.c);
    x = {u, v, 0, 0};
    ab_ed.push_back(x);
    edges[v].push_back(ab_ed.size() - 2);
    edges[u].push_back(ab_ed.size() - 1);
}
void bfs(long long min_f) {
    deque <int> q;
    q.push_back(0);
    d[0] = 0;
    while (true) {
        if (q.empty())
            return;
        int v = q.front();
        q.pop_front();
        for (int i : edges[v]) {
            int u = ab_ed[i].u;
            if ((d[u] <= d[v] + 1) || (ab_ed[i].c - ab_ed[i].f < min_f))
                continue;
            d[u] = d[v] + 1;
            q.push_back(u);
        }
    }
}
void change_sys(long long min_f)
{
    bfs(min_f);
    edges_d.clear();
    edges_d.resize(n);
    for (int i = 0; i < (int)ab_ed.size(); i++)
    {
        int v = ab_ed[i].v;
        int u = ab_ed[i].u;
        long long c = ab_ed[i].c;
        long long f = ab_ed[i].f;
        if ((d[u] != d[v] + 1) || (c - f < min_f))
            continue;
        edges_d[v].push_back(i);
    }
    for (int v = 0; v < n; v++)
        random_shuffle(edges_d[v].begin(), edges_d[v].end());
}
long long ff(int v, long long cmin, long long min_f) {
    if (v == n - 1)
        return cmin;
    while (!(edges_d[v].empty()))
    {
        int i = edges_d[v].back();
        int u = ab_ed[i].u;
        if (ab_ed[i].c - ab_ed[i].f < min_f) {
            edges_d[v].pop_back();
            continue;
        }
        long long new_min = ff(u, min(cmin, ab_ed[i].c - ab_ed[i].f), min_f);
        if (new_min != 0)
        {
            ab_ed[i].f += new_min;
            ab_ed[i ^ 1].f -= new_min;
            return new_min;
        }
        else
            edges_d[v].pop_back();
    }
    return 0;
}
int main()
{
    freopen("flow2.in", "r", stdin);
    freopen("flow2.out", "w", stdout);
    cin >> n >> m;
    edges.resize(n);
    for (int i = 0; i < m; i++) {
        int a0, b0, c0;
        cin >> a0 >> b0 >> c0;
        add_ed(a0 - 1, b0 - 1, c0);
    }
    int k = 0;
    while (max_ > 0)
    {
        max_ /= 2;
        k++;
    }
    long long ans = 0;
    long long min_f = 1LL << min(31, k + 1);
    while (min_f >= 1) {
        while (true) {
            d.clear();
            d.resize(n, inf);
            change_sys(min_f);
            if (d[n - 1] == inf)
                break;
            while (true) {
                long long add_flow = ff(0, 1000000000, min_f);
                ans += add_flow;
                if (add_flow == 0)
                    break;
            }
        }
        min_f /= 2;
    }
    cout << ans;
    return 0;
}