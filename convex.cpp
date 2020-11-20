#include <bits/stdc++.h>

using namespace std;

const long long MAX_N = 400000;

const long double EPS = 1e-9;

struct Point {
    long long x, y, num;
    Point(){}
    Point(long long x, long long y) : x(x), y(y) {}
    Point operator - (Point p2) {
        return Point(x - p2.x, y - p2.y);
    }
};

Point st[MAX_N];
int en = 1;
Point p0(1e9 + 1, 1e9 + 1);
Point a[MAX_N];

long long S(Point x) {
    return x.x * x.x + x.y * x.y;
}

long double sqr(long double x) {
    return x * x;
}

long double S1(Point x, Point y) {
    return sqrt(sqr(x.x - y.x) + sqr(x.y - y.y));
}

long long cross(Point x, Point y) {
    return x.x * y.y - x.y * y.x;
}

bool cmp(Point x, Point y) {
    return ((cross(x - p0, y - p0) > 0) || (cross(x - p0, y - p0) == 0 && (S(x - p0) < S(y - p0))));
}

int main()
{
    freopen("convex.in", "r", stdin);
    freopen("convex.out", "w", stdout);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
        a[i].num = i;
        if ((a[i].y < p0.y) || (a[i].y == p0.y && a[i].x < p0.x)) {
            p0.x = a[i].x;
            p0.y = a[i].y;
        }
    }
    sort(a, a + n, cmp);
    cout.precision(15);
    st[0] = a[0];
    for (int i = 1; i < n; i++) {
        while (en > 1 && cross(a[i] - st[en - 1], st[en - 1] - st[en - 2]) >= 0) {
            en--;
        }
        st[en] = a[i];
        en++;
    }
    cout << en << endl;
    for (int i = 0; i < en; i++) {
        cout << (st[i].num + 1) << " ";
    }
    long double area = 0;
    for (int i = 0; i < en - 1; i++) {
        area += cross(st[i], st[i + 1]);
    }
    area += cross(st[en - 1], st[0]);
    cout << fixed << (fabs(area) / 2) << endl;
    return 0;
}
