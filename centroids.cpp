#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4 * 1e5;

vector <int, int> a[MAX_N];
vector <int, int> c[MAX_N];

int main() {
    int n, x, y;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> x >> y;
        a[x - 1].push_back(y - 1);
        a[y - 1].push_back(x - 1);
    }

    return 0;
}