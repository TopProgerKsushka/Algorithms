#include <bits/stdc++.h>

using namespace std;

#define div ___div
#define mod ___mod

const int k1 = 100005;

int n, m, k;
int a[k1];
int h[k1];
int add[1000];
int div[k1], mod[k1];

inline void process_block(int block) {
    int l = block * k, r = (block + 1) * k;
    for (int i = l ; i < min(r, n); i++)
        a[i] = h[i];
    sort(a + l, a + min(r, n));
}

inline bool find_x(int l, int r, long long x) {
    while (l != r) {
        int mid = (l + r) >> 1;
        a[mid] < x ? l = (mid + 1): r = mid;
    }
    return a[l] == x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("fabro.in", "r", stdin);
    freopen("fabro.out", "w", stdout);

    cin >> n >> m;
    k = 150;

    for (int i = 0; i < n; i++) {
        cin >> h[i];
        a[i] = h[i];
    }

    for (int i = 0; i <= n; i++) {
        div[i] = i / k;
        mod[i] = i % k;
    }

    for (int i = 0; i < n; i += k)
        sort(a + i, a + min(n, i + k));

    char c;
    int l, r, x;
    for (int i = 0; i < m; i++) {
        cin >> c;
        cin >> l >> r >> x;
        l--;
        if (c == '+') {
            if (mod[l] != 0) {
                while (mod[l] != 0 && l < min(r, n))
                    h[l++] += x;
                process_block(div[l] - int(mod[l] == 0));
            }

            while (l + k <= r) {
                add[div[l]] += x;
                l += k;
            }

            while (l < r)
                h[l++] += x;
            process_block(div[l] - int(mod[l] == 0));
        } else {
            bool flag = false;

            if (mod[l] != 0) {
                while (mod[l] != 0 && l < min(r, n)) {
                    flag |= h[l] + add[div[l]] == x;
                    if (flag)
                        break;
                    l++;
                }
            }

            while (l + k <= r) {
                flag |= find_x(l, l + k - 1, x - add[div[l]]);
                if (flag)
                    break;
                l += k;
            }

            while (l < r) {
                flag |= h[l] + add[div[l]] == x;
                if (flag)
                    break;
                l++;
            }

            cout << (flag ? "YES\n" : "NO\n");
        }
    }
    return 0;
}
