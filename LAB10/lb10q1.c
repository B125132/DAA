/* Q1: Online bipartiteness via DSU with parity. O(E * alpha(V)) time, O(V) space. */
#include <stdio.h>
#include <stdlib.h>
int *p, *sz, *par; /* par[x] = parity (colour difference) of x relative to p[x] */
int find(int x){
    if(p[x]==x) return x;
    int px=p[x], r=find(px);
    par[x]^=par[px];      /* par[px] is now parity of px to root */
    p[x]=r; return r;
}
int main(){
    int V,E; scanf("%d %d",&V,&E);
    p=malloc((V+1)*sizeof(int)); sz=malloc((V+1)*sizeof(int)); par=calloc(V+1,sizeof(int));
    for(int i=1;i<=V;i++){p[i]=i;sz[i]=1;}
    for(int i=1;i<=E;i++){
        int u,v; scanf("%d %d",&u,&v);
        int ru=find(u), rv=find(v);
        if(ru==rv){
            if(par[u]==par[v]) printf("Edge %d (%d,%d): REJECTED (odd cycle)\n",i,u,v);
            else printf("Edge %d (%d,%d): added, still bipartite\n",i,u,v);
        } else {
            if(sz[ru]>sz[rv]){int t=ru;ru=rv;rv=t;}   /* attach smaller ru under rv */
            p[ru]=rv; par[ru]=par[u]^par[v]^1; sz[rv]+=sz[ru];
            printf("Edge %d (%d,%d): added, still bipartite\n",i,u,v);
        }
    }
    return 0;
}