/*
 * prepare:
 *	cti : 將字符串映射到整数
 *	branch 赋值
 * function: 
 *	AC::init() 初始化
 *	AC::insert(char str[], int len) 插入str[0..len-1]
 *	AC::finish() 构造AC自动机
 */
const int MAX_NODE = 100 + 5, MAX_BRANCH = 4;

struct Node {
	Node *fl, *go[MAX_BRANCH];
	int id, acc;
	void reset(int indice) {
		id = indice;
		acc = 0;
		memset(go, 0, sizeof(go));
	}	
};
Node node[MAX_NODE], *root, *que[MAX_NODE];
int sz, branch;

Node* newNode() {
	node[sz].reset(sz);
	return &node[sz++];
}

int cti[256];
namespace AC {
	void init() {
		sz = 0;
		root = newNode();
	}
	void insert(char* str, int len) {
		Node *x = root;
		for (int i = 0; i < len; i++) {
			int a = cti[str[i]];
			if (!(x->go[a]))
				x->go[a] = newNode();
			x = x->go[a];
		}
		x->acc = 1;
	}
	void finish() {
		int ll = 0, rr = 0;
		root->fl = root;
		for (int i = 0; i < branch; i++)
			if (root->go[i]) {
				root->go[i]->fl = root;
				que[rr++] = root->go[i];
			} else 
				root->go[i] = root;
		Node *x, *y;
		while (ll < rr) {
			x = que[ll++];
			for (int i = 0; i < branch; i++) {
				if (y = (x->go[i])) {
					y->fl = x->fl->go[i];
					// Update y->acc By x->acc, y->fl->acc
					que[rr++] = x->go[i];
				} else
					x->go[i] = x->fl->go[i];
			}
		}
	}
};

void work() {
	memset(dp, 0, sizeof(dp));
	dp[0][root->id] = 1;
	for (int l = 0; l < n; l++) for (int i = 0; i < sz; i++)
		for (int c = 0; c < branch; c++) {
			// int j = node[i]->go[c] - node;
			// Update dp[l + 1][j] By dp[l][i]
		}
	}
}
