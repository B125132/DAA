/* Q2: Number of Islands II. Cell (r,c) -> id r*C+c. O(K * alpha(RC)) time, O(RC) space. */
#include <stdio.h>
#include <stdlib.h>
int *p, *sz;
int find(int x){ while(p[x]!=x){ p[x]=p[p[x]]; x=p[x]; } return x; }
int main(){
    int R,C,K; scanf("%d %d %d",&R,&C,&K);
    p=malloc(R*C*sizeof(int)); sz=calloc(R*C,sizeof(int));  /* sz==0 -> water */
    int dr[4]={-1,1,0,0}, dc[4]={0,0,-1,1}, cnt=0;
    for(int i=0;i<R*C;i++) p[i]=i;
    for(int k=0;k<K;k++){
        int r,c; scanf("%d %d",&r,&c);          /* 0-indexed */
        int id=r*C+c;
        if(sz[id]==0){
            sz[id]=1; cnt++;
            for(int d=0;d<4;d++){
                int nr=r+dr[d], nc=c+dc[d];
                if(nr<0||nc<0||nr>=R||nc>=C) continue;
                int nid=nr*C+nc;
                if(sz[nid]==0) continue;
                int a=find(id), b=find(nid);
                if(a!=b){
                    if(sz[a]<sz[b]){int t=a;a=b;b=t;}
                    p[b]=a; sz[a]+=sz[b]; cnt--;
                }
            }
        }
        printf("%d ",cnt);
    }
    printf("\n"); return 0;
}