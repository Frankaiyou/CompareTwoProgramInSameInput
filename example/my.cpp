#include <stdio.h>
#include <string.h>
#include <algorithm>
const int N = 50005;
const int inf = 0x3f3f3f3f;
using std:: max;

struct Node {
	int v, val, la, ra;
	Node *ls, *rs;
	Node () { v = la = ra = -inf, val = 0; ls = rs = NULL; }
	void merge () {
		val = ls->val + rs->val,
		v = max(ls->ra + rs->la, max(ls->v, rs->v)),
		la = ls->la, ra = rs->ra, v = max(v, max(la, ra)),
		ra = max(ra, rs->val + ls->ra), la = max(la, ls->val + rs->la);
	}
	Node* merge(Node *rs) {
		Node* ls = this;
		Node* res = new Node();
		res->val = ls->val + rs->val,
		res->v = max(ls->ra + rs->la, max(ls->v, rs->v)),
		res->la = ls->la, res->ra = rs->ra, 
		res->v = max(res->v, max(res->la, res->ra)),
		res->ra = max(res->ra, rs->val + ls->ra), 
		res->la = max(res->la, ls->val + rs->la);
		return res;
	}
};


template <typename T> 
class Tree {
 	Node *root; int n;
public :
 	Tree () { root = new Node(); }
 	void build(int l, int r, Node *node, int *a) {
 		if (l == r) {
 			node->val = node->v = node->la = node->ra = a[l];
 			return ;
 		}
 		int mid = l + r >> 1;
 		node->ls = new Node(); node->rs = new Node();
 		build(l, mid, node->ls, a);
 		build(mid + 1, r, node->rs, a);
 		node->merge();
 	}
 	void Build(int _, int *a) { return n = _, build(1, n, root, a); }
 	Node* query(int l, int r, int L, int R, Node *node) {
 		if (l >= L and r <= R) return node;
 		int mid = l + r >> 1; Node *res = new Node(), *tmp = res;
 		if (L <= mid) res = res->merge(query(l, mid, L, R, node->ls)), delete tmp, tmp = res;
 		if (R >  mid) res = res->merge(query(mid + 1, r, L, R, node->rs)), delete tmp;
 		return res;
 	}
 	int Query(int L, int R) { Node* res = query(1, n, L, R, root); return res->v; }
};

int A[N];
int main () {
	int n; 
	scanf("%d", &n);
	for (int i = 1; i <= n; i += 1) scanf("%d", &A[i]);
	int m, l, r;
	scanf("%d", &m);
	Tree<Node> *T = new Tree<Node>(); T->Build(n, A);
	while (m--) {
		scanf("%d%d", &l, &r);
		printf("%d\n", T->Query(l, r));
	}
	return 0;
}