#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3000000;

int p[MAX_N];

int main()
{
    //freopen("prefix-function.in", "r", stdin);
    //freopen("prefix-function.out", "w", stdout);
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++) {
        p[i] = 0;
    }
    for (int i = 1; i < s.length(); i++) {
        int k = p[i - 1];
        cout << "i = " << i << " k = ";
        while (k > 0 && s[k] != s[i]) {
            k = p[k - 1];
            cout << k << ", ";
        }
        if (s[i] == s[k]) {
            p[i] = k + 1;
        }
        cout << endl;
    }
    return 0;
}
