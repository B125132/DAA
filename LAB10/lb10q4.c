/* Q4: Reverse-time DSU. Add vertices back in reverse deletion order.
   O((V+E) alpha(V)) time, O(V+E) space (adjacency list). */
#include <stdio.h>
#include <stdlib.h>
typedef long long ll;
int *p,*sz,*head,*nxt,*to,*P,*alive; ll *sum,*ans;
int find(int x){ 
    while(p[x]!=x){p[x]=p[p[x]];x=p[x];
    } 
    return x;
 }
int main(){
    int V,E,ec=0; scanf("%d %d",&V,&E);
    p=malloc((V+1)*sizeof(int)); sz=malloc((V+1)*sizeof(int)); sum=malloc((V+1)*sizeof(ll));
    head=malloc((V+1)*sizeof(int)); alive=calloc(V+1,sizeof(int));
    nxt=malloc(2*E*sizeof(int)); to=malloc(2*E*sizeof(int));
    P=malloc((V+1)*sizeof(int)); ans=malloc((V+1)*sizeof(ll));
    for(int i=1;i<=V;i++){ scanf("%lld",&sum[i]); p[i]=i; sz[i]=1; head[i]=-1; }
    for(int i=0;i<E;i++){
        int u,v; scanf("%d %d",&u,&v);
        to[ec]=v; nxt[ec]=head[u]; head[u]=ec++;
        to[ec]=u; nxt[ec]=head[v]; head[v]=ec++;
    }
    for(int i=1;i<=V;i++) scanf("%d",&P[i]);
    ll best=0;
    for(int i=V;i>=1;i--){
        ans[i]=best;                    /* state after deleting p1..pi */
        int x=P[i]; alive[x]=1;
        for(int e=head[x];e!=-1;e=nxt[e]){
            int y=to[e]; if(!alive[y]) continue;
            int a=find(x), b=find(y);
            if(a!=b){
                if(sz[a]<sz[b]){int t=a;a=b;b=t;}
                p[b]=a; sz[a]+=sz[b]; sum[a]+=sum[b];
            }
        }
        ll s=sum[find(x)]; if(s>best) best=s;
    }
    for(int i=1;i<=V;i++) printf("%lld\n",ans[i]);
    return 0;
}