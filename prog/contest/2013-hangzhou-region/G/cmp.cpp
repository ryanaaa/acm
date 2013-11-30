#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn = 100100;
typedef long long ll;
struct Side{
	int to,next;
	ll w;
}side[maxn*2];
int node[maxn],top;
ll val[maxn];
void add_side(int u,int v,ll w){
	side[top]=(Side){v,node[u],w};node[u]=top++;
	side[top]=(Side){u,node[v],w};node[v]=top++;
}
bool vis[maxn];
void dfs(int u){
	vis[u]=true;
	for(int i=node[u];i!=-1;i=side[i].next){
		int v=side[i].to;
		if(vis[v])continue;
		val[v]=val[u]^side[i].w;
		dfs(v);
	}
}
ll bit[60];
int end[maxn],root=1,cnt;
struct Node{
	int ch[2];
	int cnt;
	int fa;
	ll val;
}trie[maxn*60];
struct E{
	ll val;
	int u,x,cnt;
	friend bool operator < (const E &a,const E &b){
		return a.val<b.val;
	}
};
priority_queue<E>q;
ll ans[2*maxn];
int find_max(int p,ll val,int b){
	for(int i=b;i>=0;i--){
		int t=(val&bit[i])?1:0;
		if(trie[p].ch[t^1])p=trie[p].ch[t^1];
		else p=trie[p].ch[t];
	}
	return p;
}
bool find_next(E &e){
	if(e.cnt>0){
		e.cnt--;
		return true;
	}
	if(e.x==end[e.u])return false;

	int u=e.u,x=e.x,cnt=e.cnt;
	//cout<<u<<' '<<x<<' '<<endl;
	int b=0;
	while(x!=root){
		int fa=trie[x].fa;
		int b1=(val[u]&bit[b])?1:0;
		int b2=(trie[x].val&1)?1:0;
		if(b1^b2){
			if(trie[fa].ch[b1]){
				x=find_max(trie[fa].ch[b1],val[u],b-1);
				break;
			}else x=fa;
		}else{
			x=fa;
		}
		b++;
	}
	e.x=x;
	e.cnt=trie[x].cnt-1;
	e.val=val[u]^trie[x].val;
	if(end[u]==x){
		e.cnt--;
		if(e.cnt<0)return false;
	}
	return true;
}
int main(){
	bit[0]=1;
	for(int i=1;i<60;i++)bit[i]=bit[i-1]*2;
	int n;
	while(~scanf("%d",&n)&&n){
		while(!q.empty())q.pop();
		memset(node,-1,sizeof(node));
		memset(ans,-1,sizeof(ans));
		memset(vis,false,sizeof(vis));
		top=0;
		for(int i=1;i<n;i++){
			int u,v;ll w;
			scanf("%d%d",&u,&v);cin>>w;
			add_side(u,v,w);
		}
		val[1]=0;
		dfs(1);
		trie[root].ch[0]=trie[root].ch[1]=0;
		trie[root].cnt=trie[root].fa=0;
		cnt=2;
		E tmp;
		for(int i=1;i<=n;i++){
			int p=root;
			for(int j=59;j>=0;j--){
				int b1=(bit[j]&val[i])?1:0;
				if(trie[p].ch[b1]==0){
					trie[cnt].ch[0]=trie[cnt].ch[1]=0;
					trie[cnt].val=trie[p].val*2+b1;
					trie[cnt].fa=p;
					trie[cnt].cnt=0;
					trie[p].ch[b1]=cnt++;
				}
				p=trie[p].ch[b1];
				//cout<<trie[p].val<<endl;
			}
			trie[p].cnt++;
			end[i]=p;
		}
		for(int i=1;i<=n;i++){
			int x=find_max(root,val[i],59);
			tmp.x=x;
			tmp.u=i;
			tmp.cnt=trie[x].cnt-1;
			tmp.val=trie[x].val^val[i];
			if(end[tmp.u]==x)tmp.cnt--;
			//printf("%d %lld %lld\n",i,val[i],tmp.val);
			if(tmp.x!=end[i]||tmp.cnt>=0)q.push(tmp);
		}
		//tmp = q.top();
		//printf("%lld\n",tmp.val);
		for(int k=1;k<=200000&&!q.empty();k++){
			tmp=q.top();q.pop();
			ans[k]=tmp.val;
			//printf("%d %lld\n",k,ans[k]);
			if(find_next(tmp))q.push(tmp);
		}
		int m;
		scanf("%d",&m);
		for(int i=0;i<m;i++){
			int k;
			scanf("%d",&k);
			printf("%lld\n",ans[k]);
		}
	}
}

