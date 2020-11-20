#include <iostream>

using namespace std;

const int MAX_N = 3000000;

int z[MAX_N];

int main()
{
    freopen("z-function.in", "r", stdin);
    freopen("z-function.out", "w", stdout);
    string s;
    cin >> s;
    int n = s.length();
    int r = 0;
    int l = 0;
    for (int i = 1; i < s.length(); i++) {
        if (i < r) {
            z[i] = min(z[i - l], r - i);
        }
        while (s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    cout << s.length() << " ";
    for (int i = 1; i < n; i++) {
        cout << z[i] << " ";
    }
    return 0;
}
