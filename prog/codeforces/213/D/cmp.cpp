#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<ctime>
#define int64 long long
using namespace std;
int64 d[12000],ans,v,a[1200000];
int tot,n,i,t,j,q[12000],sum;
int Find(int64 x){
	return lower_bound(d+1,d+tot+1,x)-d;
}
int main(){
	srand(time(0));
	scanf("%d",&n);
	for(i=1;i<=n;++i)scanf("%lld",&a[i]);
	for(t=10;t--;){
		v=a[((((int)rand()<<14)+rand())%n + n) % n+1];
		tot=0;
		for(i=1;(int64)i*i<=v;++i)if(v%i==0){
			d[++tot]=i;
			if((int64)i*i!=v)d[++tot]=v/i;
		}
		sort(d+1,d+tot+1);
		for(i=1;i<=tot;++i)q[i]=0;
		for(i=1;i<=n;++i)q[Find(__gcd(v,a[i]))]++;
		for(i=1;i<=tot;++i){
			sum=0;
			for(j=i;j<=tot;++j)if(d[j]%d[i]==0)sum+=q[j];
			if(sum*2>=n)ans=max(ans,d[i]);
		}
	}
	printf("%lld\n",ans);
}
