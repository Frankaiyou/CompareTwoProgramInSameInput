#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
#include<set>
#include<queue>
#include<cmath>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Pair pair<int, int>
#define MP(x, y) make_pair(x, y)
#define fi first
#define se second
//#define int long long 
#define LL long long 
#define rg register 
#define sc(x) scanf("%d", &x);
#define pt(x) printf("%d ", x);
#define db(x) double x 
#define rep(x) for(int i = 1; i <= x; i++)
// #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1<<22, stdin), p1 == p2) ? EOF : *p1++)
char buf[(1 << 22)], *p1 = buf, *p2 = buf;
char obuf[1<<24], *O = obuf;
#define OS  *O++ = '\n';
using namespace std;
using namespace __gnu_pbds;
const int MAXN = 50001, INF = 1e9 + 10, mod = 1e9 + 7;
const double eps = 1e-9;
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
void print(int x) {
    if(x > 9) print(x / 10);
    *O++ = x % 10 + '0';
}
#define ls k << 1
#define rs k << 1 | 1
int N, M;
int a[MAXN];
struct Node {
    int l, r, lmx, rmx, mx, sum;
}T[MAXN << 2];
void update(int k) {
    T[k].sum = T[ls].sum + T[rs].sum;
    T[k].mx = max(T[ls].mx, T[rs].mx);
    T[k].mx = max(T[k].mx, T[ls].rmx + T[rs].lmx);
    T[k].rmx = max(T[rs].rmx, T[rs].sum + T[ls].rmx);
    T[k].lmx = max(T[ls].lmx, T[ls].sum + T[rs].lmx);
}
void Build(int k, int ll, int rr) {
    T[k] = (Node) {ll, rr, 0, 0, 0};
    if(ll == rr) {
        T[k].lmx = T[k].rmx = T[k].mx = T[k].sum = a[ll]; 
        return ;
    }
    int mid = ll + rr >> 1;
    Build(ls, ll, mid);
    Build(rs, mid + 1, rr);
    update(k);
}
Node merge(Node a, Node b) {
    Node now;
    now.sum = a.sum + b.sum;
    now.mx = max(a.mx, b.mx);
    now.mx = max(now.mx, a.rmx + b.lmx);
    now.rmx = max(b.rmx, b.sum + a.rmx);
    now.lmx = max(a.lmx, a.sum + b.lmx);    
//    printf("%d %d %d %d\n", now.mx, now.lmx, now.rmx, now.sum);
    return now;
}
Node Query(int k, int ll, int rr) {
    Node ans = (Node) {0, 0, 0, 0, 0};
    if(ll <= T[k].l && T[k].r <= rr) return T[k];
    int mid = T[k].l + T[k].r >> 1;
    /*if(ll <= mid) ans = Query(ls, ll, rr);
    if(rr  > mid) ans = merge(ans, Query(rs, ll, rr)); WA!*/
    if(ll > mid) return Query(rs, ll, rr);
    else if(rr <= mid) return Query(ls, ll, rr);
    else return merge(Query(ls, ll, rr), Query(rs, ll, rr));
    return ans;
}
main() {
    //freopen("a.in", "r", stdin);
    N = read();
    for(int i = 1; i <= N; i++) a[i] = read();
    Build(1, 1, N);    
    int M = read();
    while(M--) {
        int x = read(), y = read();
        printf("%d\n", Query(1, x, y).mx);
    }
    //fwrite(obuf, O-obuf, 1 , stdout);
    return 0;
}