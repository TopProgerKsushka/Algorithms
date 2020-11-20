#include <bits/stdc++.h>

using namespace std;

const int MAX_K = 30;
const int MAX_N = 30000;
const long long M = 15000001;
long long p = 239;

struct st {
    long long h;
    int num, last;
};

int k = 0;
char s[MAX_K][MAX_N];
long long pow1[MAX_N];
int len[MAX_N];
int len_ans = 0;
char ans[MAX_N];
st a[MAX_N];
long long h[MAX_K][MAX_N];

long long get_hash(int num, int l, int r) {
    return ((h[num][r] - h[num][l] * pow1[r - l]) % M + M) % M;
}

bool can(int x) {
    unordered_map <long long, st> m;
    int cnt = 0;
    for (int i = 0; i <= len[0] - x; i++) {
        a[cnt].h = get_hash(0, i, i + x);
        a[cnt].num = 1;
        a[cnt].last = 0;
        m[a[cnt].h] = a[cnt];
        cnt++;
    }
    for (int i = 1; i < k; i++) {
        for (int j = 0; j <= len[i] - x; j++) {
            if (m.count(get_hash(i, j, j + x)) && m[get_hash(i, j, j + x)].last != i) {
                m[get_hash(i, j, j + x)].num++;
                m[get_hash(i, j, j + x)].last = i;
                if (m[get_hash(i, j, j + x)].num == k) {
                    if (x > len_ans) {
                        for (int z = 0; z < x; z++) {
                            ans[z] = s[i][j + z];
                            len_ans = x;
                        }
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    freopen("substr.in", "r", stdin);
    freopen("substr.out", "w", stdout);
    int n;
    cin >> n;
    k = 0;
    int mn = 100000;
    int mx = -1;
    for (int i = 0; i < n; i++) {
       //cin >> s[k];
       string t;
       cin >> t;
       for (int i = 0; i < t.length(); i++) {
            s[k][len[k]] = t[i];
            len[k]++;
       }
       mn = min(mn, len[k]);
       mx = max(mx, len[k]);
       k++;
    }
    pow1[0] = 1;
    for (int i = 1; i <= mx; i++) {
        pow1[i] = (pow1[i - 1] * p) % M;
    }
    for (int i = 0; i < k; i++) {
        for (int j = 1; j <= len[i]; j++) {
            h[i][j] = (h[i][j - 1] * p + s[i][j - 1]) % M;
        }
    }
    int l = 0;
    int r = mn + 1;
    while (r - l > 1) {
        int m1 = (l + r) / 2;
        if (can(m1)) {
            l = m1;
        } else {
            r = m1;
        }
    }
    if (k == 1) {
        cout << s[0];
    } else {
        cout << ans;
    }
    return 0;
}
