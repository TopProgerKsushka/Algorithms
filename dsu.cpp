#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 60000;
const int MAX_M = 300010;

struct node {
    long long x, y, w, id;
};
long long p[MAX_N];
bool used[MAX_M];
node a[MAX_M];
long long rang[MAX_N];

long long get_root(long long v) {
    if (p[v] == v) {
        return v;
    }
    return p[v] = get_root(p[v]);
}

void join(long long u, long long v) {
    long long c1 = get_root(u);
    long long c2 = get_root(v);
    if (rang[c1] == rang[c2]) {
        p[c2] = c1;
        rang[c2]++;
    } else {
        if (rang[c1] > rang[c2]) {
            p[c2] = c1;
        } else {
            p[c1] = c2;
        }
    }
}

bool cmp(node x, node y) {
    return (x.w < y.w || (x.w == y.w && x.x < y.x) || (x.w == y.w && x.x == y.x && x.y < y.y));
}

int main()
{
    freopen("oil.in", "r", stdin);
    freopen("oil.out", "w", stdout);
    long long n, m, s;
    long long sum = 0;
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++) {
        cin >> a[i].x >> a[i].y >> a[i].w;
        a[i].id = i + 1;
        sum += a[i].w;
        a[i].w *= -1;
    }
    sort(a, a + m, cmp);
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
    long long ans = 0;
    long long count = 0;
    for (int i = 0; i < m; i++) {
        if (get_root(a[i].x) != get_root(a[i].y)) {
            join(a[i].x, a[i].y);
            ans += (-a[i].w);
            count++;
            used[i] = true;
        }
    }
    long long max_id = 0;
    while (sum - ans > s && (max_id != m)) {
        if (!used[max_id]) {
            used[max_id] = true;
            count++;
            ans += -(a[max_id++].w);
        } else max_id++;
    }
    cout << m - count << endl;
    for (int i = 0; i < m; i++) {
        if (!used[i]) cout << a[i].id << " ";
    }
    return 0;
}
