#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 250 * 1000 + 100;

struct node {
    int id; int type_l; int type_r;
};

node a[MAX_N];
node b[MAX_N];
int soot[MAX_N];
node fake[MAX_N];
int cnt[MAX_N];
char t[MAX_N];
long long k;
int n;

bool cmp(node x, node y) {
    return (t[x.id] < t[y.id] || (t[x.id] == t[y.id] && x.id > y.id));
}

bool comp(node x, node y) {
    if (x.type_l == y.type_l) return (x.type_r < y.type_r);
    return x.type_l < y.type_l;
}

const long long M = (long long)1e9 + 7;
const long long p = 239;
long long pow1[MAX_N];
long long h[MAX_N];

long long get_hash(int l, int r) {
    return ((h[r] - h[l] * pow1[r - l] + 10000 * M) % M + 10000 * M) % M;
}

int main()
{
    freopen("kthsubstr.in", "r", stdin);
    freopen("kthsubstr.out", "w", stdout);
    string start; cin >> start;
    for (int i = 0; i < (int)start.length(); i++) t[i] = start[i];
    string s = start;
    n = (int)start.length();
    pow1[0] = 1;
    for (int i = 1; i <= n; i++) {
        pow1[i] = pow1[i - 1] * p;
        pow1[i] %= M;
    }
    h[0] = (long long)s[0];
    for (int i = 1; i <= n; i++) h[i] = (long long)(h[i - 1] * p + s[i]) % M;
    long long num;
    cin >> num;
    t[n] = '#';
    for (int i = 0; i <= n; i++) a[i].id = i;
    stable_sort(a, a + n + 1, cmp);
    a[0].type_l = 0;
    a[0].type_r = 0;
    soot[a[0].id] = 0;
    for (int i = 1; i <= n; i++) {
        if (t[a[i].id] == t[a[i - 1].id]) {
            a[i].type_l = a[i - 1].type_l;
            a[i].type_r = a[i - 1].type_r;
        } else {
            a[i].type_l = a[i - 1].type_l + 1;
            a[i].type_r = a[i - 1].type_r + 1;
        }
        soot[a[i].id] = i;
    }
    k = 1;
    while (true) {
        for (int i = 0; i <= n; i++) {
            b[i].id = (int)(a[i].id - k + 2 * (n + 1)); while (b[i].id >= n + 1) b[i].id -= n + 1;
            b[i].type_l = a[soot[b[i].id]].type_l;
            b[i].type_r = a[i].type_r;
        }
        for (int i = 0; i <= n; i++) cnt[i] = 0;
        for (int i = 0; i <= n; i++) cnt[b[i].type_r + 1]++;
        for (int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
        for (int i = 0; i <= n; i++) fake[cnt[b[i].type_l]++] = b[i];
        for (int i = 0; i <= n; i++) b[i] = fake[i];
        //stable_sort(b, b + n + 1, comp);
        b[0].type_l = 0;
        b[0].type_r = 0;
        soot[b[0].id] = 0;
        for (int i = 1; i <= n; i++) {
            if ((a[soot[b[i].id]].type_l == a[soot[b[i - 1].id]].type_l) && (a[soot[(b[i].id + k) % (n + 1)]].type_r == a[soot[(b[i - 1].id + k) % (n + 1)]].type_r)) {
                b[i].type_l = b[i - 1].type_l;
                b[i].type_r = b[i - 1].type_r;
            } else {
                b[i].type_l = b[i - 1].type_l + 1;
                b[i].type_r = b[i - 1].type_r + 1;
            }
            soot[b[i].id] = i;
        }
        for (int i = 0; i <= n; i++) {
            a[i] = b[i];
        }
        if (k > n) break;
        k *= 2;
    }
    long long cur = 0;
    long long lst = -1;
    int last = 0;
    for (int i = 1; i <= n; i++) {
        if (i == 1) { cur += n - a[i].id; lst = 0;}
        else {
            int l = 0;
            int r = min(n - a[i].id, n - a[i - 1].id) + 1;
            while (l < r - 1) {
                int m = (l + r) / 2;
                if (get_hash(a[i - 1].id - 1, a[i - 1].id + m - 1) == get_hash(a[i].id - 1, a[i].id + m - 1)) {
                    l = m;
                } else {
                    r = m;
                }
            }
            last = l;
            lst = cur;
            cur += n - a[i].id - l;
        }
        if (cur >= num) {
            for (int j = 0; j < last; j++) {
                cout << s[a[i].id + j];
            }
            for (int j = 0; j < num - lst; j++) {
                cout << s[a[i].id + j + last];
            }
            exit(0);
        }
    }
    for (int i = 0; i < n - a[n].id; i++) {
        cout << s[a[n].id + i];
    }
    return 0;
}