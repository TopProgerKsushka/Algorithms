#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 400000;
ll a[MAX_N];
ll tree[MAX_N];
ll add[MAX_N];


void push(int v, int l, int r) {
    tree[2 * v + 1] += add[v];
    tree[2 * v + 2] += add[v];

    add[2 * v + 1] += add[v];
    add[2 * v + 2] += add[v];
    add[v] = 0;
}

void init(int v, int l, int r) {
    if (l == r - 1) {
        tree[v] = a[l];
        return;
    }
    int m = (l + r) / 2;
    init(2 * v + 1, l, m);
    init(2 * v + 2, m, r);
    tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
}

ll max_(int v, int l, int r, int a, int b) {
    push(v, l, r);
    if (l >= b || r <= a) {
        return -1;
    }
    if (a <= l && r <= b) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return max(max_(2 * v + 1, l, m, a, b), max_(2 * v + 2, m, r, a, b));
}

void add_(int v, int l, int r, int a, int b, ll x) {
    push(v, l, r);
    if (l >= b || r <= a) {
        return;
    }
    if (a <= l && r <= b) {
        tree[v] += x;
        add[v] += x;
        return;
    }
    int m = (l + r) / 2;
    add_(2 * v + 1, l, m, a, b, x);
    add_(2 * v + 2, m, r, a, b, x);
    tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
}


int main()
{
    //freopen("segment-tree.in", "r", stdin);
    //freopen("segment-tree.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    int x, y;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    init(0, 0, n);
    for (int i = 0; i < m; i++) {
        string c;
        cin >> c;
        if (c[0] == 'm' || c[1] == 'a' && c[2] == 'x') {
            cin >> x >> y;
            cout << max_(0, 0, n, x - 1, y) << endl;
        } else {
            ll val;
            cin >> x >> y >> val;
            add_(0, 0, n, x - 1, y, val);
        }
    }
    return 0;
}
