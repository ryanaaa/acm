#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
#define MP(a, b) make_pair(a, b)
#define FOREACH(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
#pragma comment(linker, "/STACK:1024000000,1024000000") 

const int MAX_LEN = 600000 + 50;
const int MAX_NODE = MAX_LEN * 2;
struct Node {
    Node *son[2], *par;	// suf
	int cnt, add;

	Node *suf;
	Node *go[26];	
	int id, dep;
	int dir() {
		if (par->son[0] == this) return 0;
		if (par->son[1] == this) return 1;
		return 2;
	}
	void setSon(Node *s, int d) {
		if (d == 0 || d == 1) son[d] = s;
		s->par = this;
	}
	void init(Node *null) {
		son[0] = son[1] = par = null;
		add = cnt = 0;
	} 
	void relax();
	void pull();
	void update(int a);
} *NIL;

Node node[MAX_NODE], *p_p, *root, *sink;
int size;

Node* newState(int d) {
	p_p->init(NIL);
	p_p->id = size++; 
	p_p->dep = d;
	p_p->suf = NIL;
	for (int i = 0; i < 26; i++)
		p_p->go[i] = NIL;
	return p_p++;
}


void Node::update(int a) {
	if (this == NIL) return;
	cnt += a;
	add += a;
}
void Node::relax() {
	if (this == NIL) return;
	son[0]->update(add);
	son[1]->update(add);
	add = 0;
}
void Node::pull() {
}

struct SplayTree {
	// assert(x->par != NIL)
	void rotate(Node *x) {
		Node *y = x->par;
		y->relax();	x->relax();
		int dx = x->dir(), dy = y->dir();
		y->par->setSon(x, dy);	//!!!
		y->setSon(x->son[dx ^ 1], dx);
		x->setSon(y, dx ^ 1);
		y->pull();	x->pull();
	}
	void splay(Node *x) {
		if (x == NIL) return;
		NIL->son[0] = NIL->son[1] = NIL->par = NIL;
		x->relax();
		while (x->dir() != 2) {
			if (x->par->dir() == 2)
				rotate(x);
			else if (x->dir() == x->par->dir()) {
				rotate(x->par); rotate(x);
			} else {
				rotate(x); rotate(x);
			}
		}
		x->pull();
	}
	void access0(Node *x) {
		static Node *stack[MAX_NODE];
		int top = 0; 
		while (x->par != NIL) {
			stack[top++] = x;
			x = x->par;
		}
		for (int i = top - 1; i >= 0; i--)
			stack[i]->relax();
	}
	// after acess, x->son[0] = NIL
    void access(Node *x) {
        access0(x);
        for (Node *v = NIL, *u = x; u != NIL; u = u->par) {
            splay(u);
            u->son[0] = v;  v->par = u;
            v = u;
			v->pull();
        }
		// x is in the top-level solid tree, v is root, u is NIL
        splay(x);
    }
    void cut(Node *x) {
        access(x);
		x->relax();	//
        x->son[1]->par = NIL;
        x->son[1] = NIL;
		x->pull();
    }

    void init() {
        //init properly is Important
        NIL = &node[0];
        NIL->son[0] = NIL->son[1] = NIL->par = NIL;
		NIL->cnt = NIL->add = 0;
    }
} spt;

//p := newsink, q:=childstate, r:=newchildstate
//suffixstate = [tail(wa)]wa, childstate = [tail(wa)]w
void Insert(int a) {
	Node *p = newState(sink->dep + 1), *cur = sink, *sufstate;
	while (cur != NIL && cur->go[a] == NIL) 
		cur->go[a] = p, cur = cur->suf;
	if (cur == NIL)
		sufstate = root;
	else {
		Node *q = cur->go[a];
		if (q->dep == cur->dep + 1)
			sufstate = q;
		else {
			Node *r = newState(cur->dep + 1);	
			for (int i = 0; i < 26; i++) r->go[i] = q->go[i];
			spt.cut(q);
			q->par = r;
			r->par = q->suf;
			r->cnt = q->cnt;

			r->suf = q->suf;
			q->suf = r;
			sufstate = r;
			while (cur != NIL && cur->go[a] == q)
				cur->go[a] = r, cur = cur->suf;
		}
	}
	p->suf = sufstate;
	p->par = sufstate;
	p->cnt = 1;
	spt.access(p);
	p->son[1]->update(1);
	sink = p;
}

void print(Node* cur, int t) {
	for (int i = 0; i < t; i++)
		putchar('\t');
	printf("%d %d %d %d\n", cur->id, cur->dep, cur->cnt, cur->add);
	for (int i = 0; i < 26; i++)
	if (cur->go[i] != NIL)
		print(cur->go[i], t + 1);
}

void SAinit() {
	p_p = node + 1;
	size = 0;
	root = sink = newState(0);
}

char T[MAX_LEN], S[MAX_LEN];
int qnum, QA, QB;
int main() {
	spt.init();
	SAinit();
	scanf("%s", T);
	scanf("%d %d %d", &qnum, &QA, &QB);
	for (int i = 0, _i; i < strlen(T); i++)
		Insert(T[i] - 'a');
	//print(root, 0);

	while (qnum--) {
		scanf("%s", S);
		Node* cur = root;
		int res = -1;
		for (int i = 0, _i = strlen(S); i < _i; i++)
			if (cur->go[S[i] - 'a'] == NIL) {
				res = 0;
				break;
			} else {
				cur = cur->go[S[i] - 'a'];
			}
		if (res == -1) {
			spt.access(cur);
			res = cur->cnt;
		}
		printf("%d\n", res);
		Insert((QA * res + QB) % 26);
		//printf("%d\n", (QA * res + QB));
	}

	return 0;
}
