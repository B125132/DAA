/* Q5: Lexicographically smallest permutation via DSU. Within each component, sorted values go to
   sorted positions. Bucketing by root (no comparison sort): O((n+m) alpha(n)) time, O(n) space. */
#include <stdio.h>
#include <stdlib.h>
int *p;
int find(int x){ 
    while(p[x]!=x){
        p[x]=p[p[x]];x=p[x];
    } 
    return x; 
}
int main(){
    int n,m; scanf("%d",&n);
    int *A=malloc((n+1)*sizeof(int)), *pos=malloc((n+1)*sizeof(int));
    p=malloc((n+1)*sizeof(int));
    for(int i=1;i<=n;i++){ scanf("%d",&A[i]); pos[A[i]]=i; p[i]=i; }
    scanf("%d",&m);
    for(int i=0;i<m;i++){
        int u,v; scanf("%d %d",&u,&v);
        int a=find(u), b=find(v); if(a!=b) p[a]=b;
    }
    int *start=calloc(n+2,sizeof(int)), *fp=malloc(n*sizeof(int)), *fv=malloc(n*sizeof(int));
    int *cp=malloc((n+2)*sizeof(int)), *cv=malloc((n+2)*sizeof(int)), *R=malloc((n+1)*sizeof(int));
    for(int i=1;i<=n;i++){ R[i]=find(i); start[R[i]+1]++; }
    for(int r=1;r<=n+1;r++) start[r]+=start[r-1];   /* start[r] = offset of root r's group */
    for(int r=0;r<=n+1;r++){cp[r]=cv[r]=start[r];}
    for(int i=1;i<=n;i++) fp[cp[R[i]]++]=i;          /* positions, increasing */
    for(int v=1;v<=n;v++) fv[cv[R[pos[v]]]++]=v;     /* values, increasing */
    int *res=malloc((n+1)*sizeof(int));
    for(int k=0;k<n;k++) res[fp[k]]=fv[k];
    for(int i=1;i<=n;i++) printf("%d ",res[i]);
    printf("\n"); return 0;
}