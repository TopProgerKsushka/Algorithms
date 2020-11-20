#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int inf = (int)(1e9 + 7);
const int max_st = 30;

struct node {
    node *next, *down, *up;
    int x;
    node(int k) : next(NULL), down(NULL), up(NULL), x(k) {}
};

vector <node*> anc;
node *r;

bool exists(int a) {
    node *cur = r;
    while (true) {
        if (cur->next == NULL) {
            if (cur->down == NULL) break;
            cur = cur->down;
            continue;
        }
        while (cur->next != NULL && cur->next->x < a) cur = cur->next;
        anc.push_back(cur);
        if (cur->down == NULL) break;
        cur = cur->down;
    }
    if (cur->next != NULL && cur->next->x == a) return true;
    return false;
}

void insert(int x) {
    node *last = NULL; bool ok = true;
    int id = (int)(anc.size() - 1);
    while (ok) {
        node *v = new node(x);
        if (last != NULL) last->up = v;
        v->next = anc[id]->next;
        v->down = last;
        anc[id--]->next = v;
        last = v;
        ok = (rand() % 2 == 0);
    }
}

void remove() {
    node *cur = NULL;
    cur = anc[(int)anc.size() - 1]->next;
    int id = (int)anc.size() - 1;
    while (cur != NULL) {
        anc[id]->next = cur->next;
        cur = cur->up;
        id--;
    }
}

int main() {
    freopen("skiplist.in", "r", stdin);
    freopen("skiplist.out", "w", stdout);

    cin.sync_with_stdio(0);
    string s; int x;
    node* end_ = new node(inf);
    r = new node(-inf);
    r->next = end_;
    node *r2 = r;
    for (int i = 1; i < max_st; i++) {
        node *ri = new node(inf);
        ri->up = end_;
        end_->down = ri;
        node *l = new node(-inf);
        l->next = ri;
        l->up = r2;
        r2->down = l;
        r2 = l;
    }

    while (cin >> s) {
        cin >> x;
        anc.clear();
        if (s == "exists") {
            cout << (exists(x) ? "YES" : "NO") << endl;
            continue;
        }
        if (s == "insert") {
            if (!exists(x)) insert(x);
            continue;
        }
        if (exists(x)) remove();
    }
    return 0;
}
