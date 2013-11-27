struct State {
	//suf means suffix pointer
	State *go[26], *suf;	
	int dep, id;
};
State pool[MAX_STATE], *p_p, *root, *sink; 
int size;

State* newState(int d) {
	p_p->id = size++; 
	p_p->dep = d;
	p_p->suf = 0; 
	for (int i = 0; i < 26; i++) p_p->go[i] = 0;
	return p_p++;
}

void Init() {
	p_p = pool;
	size = 0;
	root = sink = newState(0);
}

//p := newsink, q:=childstate, r:=newchildstate
//suffixstate = [tail(wa)]wa, childstate = [tail(wa)]w
void Insert(int a) {
	State *p = newState(sink->dep + 1), *cur = sink, *sufstate;
	while (cur && !cur->go[a]) 
		cur->go[a] = p, cur = cur->suf;
	if (!cur)
		sufstate = root;
	else {
		State *q = cur->go[a];
		if (q->dep == cur->dep + 1)
			sufstate = q;
		else {
			State *r = newState(cur->dep + 1);	
			for (int i = 0; i < 26; i++)
				r->go[i] = q->go[i];
			r->suf = q->suf;
			q->suf = r;
			sufstate = r;
			while (cur && cur->go[a] == q)
				cur->go[a] = r, cur = cur->suf;
		}
	}
	p->suf = sufstate;
	sink = p;
}

