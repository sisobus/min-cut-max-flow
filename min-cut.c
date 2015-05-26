#include <stdio.h>
#include <string.h>

#define MAX_V 1000
#ifndef false
#define false 0
#endif 
#ifndef true
#define true !(false)
#endif
const int INF=987654321;
int V;

/* queue */
int q[(1<<20)];
int front,back;
void initQueue(){front=back=-1;}
int isEmpty() {return front == back;}
void enqueue(int item) {q[++back] = item;}
int dequeue() {return q[++front];}
/* queue */

int min(int a,int b){return a<b?a:b;}
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];
int nf(int source, int sink) {
    memset(flow, 0, sizeof(flow));
    int totalFlow=0;
    while(true) {
        int parent[MAX_V];
        memset(parent,-1,sizeof(parent));
        parent[source]=source;
        initQueue();
        enqueue(source);
        while( !isEmpty() ) {
            int here = dequeue();
            for(int there=0; there<V; ++there)
                if(capacity[here][there]-flow[here][there]>0 && parent[there]==-1) {
                    enqueue(there);
                    parent[there]=here;
                }
        }
        if(parent[sink]==-1) break;
        int amount=INF;
        for(int p=sink; p!=source; p=parent[p])
            amount=min(capacity[parent[p]][p]-flow[parent[p]][p],amount);
        for(int p=sink; p!=source; p=parent[p]) {
            flow[parent[p]][p]+=amount;
            flow[p][parent[p]]-=amount;
        }
        totalFlow+=amount;
    }
    return totalFlow;
}

void test() {
    scanf("%d",&V);
    for ( int i = 0 ; i < V ; i++ ) 
        for ( int j = 0 ; j < V ; j++ ) 
            scanf("%d",&capacity[i][j]);
    int maxFlow = nf(0,V-1); // 최대유량을 구함
    printf("%d\n",maxFlow);

    // min-cut 부분
    int isVisit[MAX_V],S[MAX_V],T[MAX_V],sn=0,tn=0;
    memset(isVisit,0,sizeof(isVisit));
    memset(S,0,sizeof(S));
    memset(T,0,sizeof(T));
    initQueue();
    enqueue(0);
    while ( !isEmpty() ) {
        int here = dequeue();
        isVisit[here] = true;
        for ( int there = 0 ; there < V ; there++ ) 
            if ( capacity[here][there]-flow[here][there] > 0 && !isVisit[there] ) 
                enqueue(there);
    }
    for ( int i = 0 ; i < V ; i++ ) {
        if ( isVisit[i] ) S[sn++] = i;
        else T[tn++] = i;
    }
    printf("S: ");
    for ( int i = 0 ; i < sn ; i++ ) 
        printf("%d ",S[i]);
    puts("");
    printf("T: ");
    for ( int i = 0 ; i < tn ; i++ ) 
        printf("%d ",T[i]);
    puts("");
    
}
int main() {
    test();
    return 0;
}
