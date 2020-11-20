#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <vector>


using namespace std;

const int MAX_M = 200001;
const int MAX_N = 20001;

struct node {
    int x, next, cnt;
};

struct node2 {
    int in, out, up;
};

vector <pair <int, int> > q[MAX_N];
int e = 0;
node2 t[MAX_N];
bool vis[MAX_N];
bool b[MAX_M];
int tim = 0;

void dfs(int v, int p) {
    vis[v] = true;
    t[v].in = tim;
    tim++;
    t[v].up = t[v].in;
    for (int i = 0; i < q[v].size(); i++) {
        if (q[v][i].second != p) {
            if (vis[q[v][i].second]) {
                t[v].up = min(t[v].up, t[q[v][i].second].in);
            } else {
                dfs(q[v][i].second, v);
                t[v].up = min(t[v].up, t[q[v][i].second].up);
                if (t[q[v][i].second].up > t[v].in) {
                    b[q[v][i].first] = true;
                }
            }
        }
    }
}


int main()
{
    //freopen("bridges.in", "r", stdin);
    //freopen("bridges.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        q[x].push_back(make_pair(i, y));
        q[y].push_back(make_pair(i, x));
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, -1);
        }
    }
    for (int i = 0; i < m; i++) {
        if (b[i]) {
            e++;
        }
    }
    cout << e << endl;
    for (int i = 0; i < m; i++) {
        if (b[i]) {
            cout << i + 1 << " ";
        }
    }
    cout << endl;
    return 0;
}
