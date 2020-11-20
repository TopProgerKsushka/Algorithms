#include <bits/stdc++.h>

using namespace std;

struct node {
    int x;
    node *l, *r;
    node(int x = 0): x(x), l(NULL), r(NULL) {}
};
vector <node*> path;

node *find_with_path(node *&root, int x) {
    path.push_back(root);
    if (root->x == x) return root;
    if (root->x < x) {
        if (root->r == NULL) return root;
        return find_with_path(root->r, x);
    }
    if (root->l == NULL) return root;
    return find_with_path(root->l, x);
}

node *find(node *&root, int x) {
    if (root->x == x) return root;
    if (root->x < x) {
        if (root->r == NULL) return root;
        return find(root->r, x);
    }
    if (root->l == NULL) return root;
    return find(root->l, x);
}

void splay(node *&root, node *v) {
    path.clear();
    find_with_path(root, v->x);
    for (int i = (int) path.size() - 1; i > 1; i--) {
        node *x = path[i], *p = path[i - 1], *g = path[i - 2];
        path.pop_back(); path.pop_back(); path.pop_back();
        if (g->x > p->x && p->x > x->x) {
            g->l = p->r;
            p->r = g; p->l = x->r;
            x->r = p;
        } else if (g->x < p->x && p->x < x->x) {
            g->r = p->l;
            p->l = g; p->r = x->l;
            x->l = p;
        } else if (g->x < p->x && p->x > x->x) {
            p->l = x->r;
            x->r = p;
            g->r = x->l;
            x->l = g;
        } else if (g->x > p->x && p->x < x->x) {
            p->r = x->l;
            x->l = p;
            g->l = x->r;
            x->r = g;
        }
        path.push_back(x); i--;
    }
    if ((int)path.size() > 1) {
        node *x = path[1], *p = path[0];
        path.pop_back(); path.pop_back();
        if (p->x > x->x) {
            p->l = x->r; x->r = p;
        } else if (p->x < x->x) {
            p->r = x->l; x->l = p;
        }
        path.push_back(x);
    }
    root = path[0];
}

node *merge(node *&l, node *&r) {
    if (l == NULL) return r;
    if (r == NULL) return l;
    node *x = l;
    while (x->r != NULL) x = x->r;
    splay(l, x);
    x->r = r;
    return x;
}

void split(node *&root, node *&l, node *&r, int key) {
    if (root == NULL) {
        l = r = NULL;
        return;
    }
    node *x = find(root, key);
    splay(root, x);
    if (x->x < key) {
        l = x, r = x->r; x->r = NULL;
    } else if (x->x > key) {
        l = x->l, r = x; x->l = NULL;
    }
}

bool is(node *&root, int key) {
    if (root == NULL) return false;
    node *x = find(root, key);
    splay(root, x);
    return root->x == key;
}

bool add(node *&root, int key) {
    if (is(root, key)) return false;
    node *l, *r;
    split(root, l, r, key);
    root = new node(key);
    root->l = l, root->r = r;
    return true;
}

bool del(node *&root, int key) {
    if (!is(root, key)) return false;
    node *x = find(root, key);
    node *l = x->l, *r = x->r;
    root = merge(l, r);
    return true;
}

node *next(node *root, int key) {
    node *r = NULL;
    while (root != NULL) {
        if (root->x > key) r = root, root = root->l;
        else root = root->r;
    }
    return r;
}

node *prev(node *root, int key) {
    node *l = NULL;
    while (root != NULL) {
        if (root->x >= key) root = root->l;
        else if (root->x < key) l = root, root = root->r;
    }
    return l;
}
node *root = NULL;

int main() {
    freopen("bst.in", "r", stdin);
    freopen("bst.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    string s;
    while (cin >> s) {
        int x; cin >> x;
        if (s == "insert") {
            add(root, x);
            continue;
        }
        if (s == "delete") {
            del(root, x);
            continue;
        }
        if (s == "exists") {
            cout << (is(root, x) ? "true" : "false") << endl;
            continue;
        }
        if (s == "next") {
            node *ans = next(root, x);
            if (ans != NULL) {
                cout << ans->x << endl;
                splay(root, ans);
                continue;
            }
            cout << "none" << endl;
            continue;
        }
        node *ans = prev(root, x);
        if (ans != NULL) {
            cout << ans->x << endl;
            splay(root, ans);
            continue;
        }
        cout << "none" << endl;
    }
    return 0;
}