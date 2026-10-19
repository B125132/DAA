/* Q3: Max total weight of a component with size <= K after each edge insertion.
   DSU (sum,size) + max-heap with lazy deletion. Edge weights do not affect vertex-weight sums.
   O((V+E) log(V+E)) time, O(V+E) space. */
#include <stdio.h>
#include <stdlib.h>
typedef long long ll;
typedef struct{ll s; int r,z;} H;
H *h; int hn=0;
void push(H x){ int i=hn++; while(i&&h[(i-1)/2].s<x.s){h[i]=h[(i-1)/2];i=(i-1)/2;} h[i]=x; }
void pop(){
    H x=h[--hn]; int i=0;
    while(2*i+1<hn){
        int c=2*i+1; if(c+1<hn&&h[c+1].s>h[c].s) c++;
        if(h[c].s>x.s){h[i]=h[c];i=c;} else break;
    }
    if(hn>0) h[i]=x;
}
int *p,*sz; ll *sum;
int find(int x){ while(p[x]!=x){p[x]=p[p[x]];x=p[x];} return x; }
int main(){
    int V,K,E; scanf("%d %d",&V,&K);
    p=malloc((V+1)*sizeof(int)); sz=malloc((V+1)*sizeof(int)); sum=malloc((V+1)*sizeof(ll));
    for(int i=1;i<=V;i++){ scanf("%lld",&sum[i]); p[i]=i; sz[i]=1; }
    scanf("%d",&E);
    h=malloc((size_t)(V+E+1)*sizeof(H));
    if(K>=1) for(int i=1;i<=V;i++) push((H){sum[i],i,1});
    for(int i=1;i<=E;i++){
        int u,v; ll w; scanf("%d %d %lld",&u,&v,&w);
        int a=find(u), b=find(v);
        if(a!=b){
            if(sz[a]<sz[b]){int t=a;a=b;b=t;}
            p[b]=a; sz[a]+=sz[b]; sum[a]+=sum[b];
            if(sz[a]<=K) push((H){sum[a],a,sz[a]});
        }
        while(hn && (find(h[0].r)!=h[0].r || sz[h[0].r]!=h[0].z)) pop();  /* stale entries */
        printf("After edge %d: %lld\n",i,hn?h[0].s:0LL);
    }
    return 0;
}