#include "a.h"

void   initQueue()            {   front = back = -1;      }
int      isEmpty()            {   return front == back;   }
void   enqueue(int item)      {   q[++back] = item;      }
int      dequeue()            {   return q[++front];      }
double   min(double a,double b)   {   return a<b? a:b;      }

const double EPS = 1e-9;
int diff(double lhs,double rhs) {
    if ( lhs - EPS < rhs && rhs < lhs + EPS ) return 0;
    return lhs < rhs ? -1 : 1;
}

double nf(int source, int sink) {
    memset(flow, 0, sizeof(flow));
   double   totalFlow   = 0;
    while (true) {
        int parent[MAX_V];
        memset(parent,-1,sizeof(parent));
        parent[source]   =   source;
        initQueue();
        enqueue(source);
        while (!isEmpty()) {
            int here = dequeue();
            for (int there=0; there<V; ++there) 
//                if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
                if (diff(capacity[here][there]-flow[here][there],0.0f) != 0 && parent[there] == -1) {
               enqueue(there);
               parent[there]=here;
                }
        }
        if (parent[sink] == -1) break;
        double amount   = DBL_MAX;
        for(int p = sink; p != source; p = parent[p])
            amount   = min(capacity[parent[p]][p]-flow[parent[p]][p],amount);
        for(int p=sink; p!=source; p=parent[p]) {
            flow[parent[p]][p]   += amount;
            flow[p][parent[p]]   -= amount;
        }
        totalFlow   +=   amount;
    }
    return totalFlow;
}


void runMincut(double** graph, int vertexCnt) {
    V         = vertexCnt;
    capacity   = graph;
   
   double maxFlow = nf(V/2,V-1); // 최대유량을 구함
    printf("%.3lf\n",maxFlow);


    for ( int i = 0 ; i < V; i++ ) {
        for ( int j = 0 ; j < V ; j++ ) 
            printf("{%lf,%lf} ",capacity[i][j],flow[i][j]);
        puts("");
    }

    // min-cut 부분
    int isVisit[MAX_V],S[MAX_V],T[MAX_V],sn=0,tn=0;
   
    memset(isVisit,0,sizeof(isVisit));
    memset(S,0,sizeof(S));
    memset(T,0,sizeof(T));
    initQueue();
    enqueue(V/2);
    while (!isEmpty()) {
        int here = dequeue();
        isVisit[here] = true;
        for ( int there = 0 ; there < V ; there++ ) 
            if (diff(capacity[here][there]-flow[here][there],0.0f) != 0 && !isVisit[there]) 
                enqueue(there);
    }
    for ( int i = 0 ; i < V ; i++ ) {
        if ( isVisit[i] )   S[sn++] = i;
        else            T[tn++] = i;
    }
    printf("S: ");
    for (int i = 0 ; i < sn ; i++)   printf("%d ",S[i]);
    puts("");
    printf("T: ");
    for (int i = 0 ; i < tn ; i++)   printf("%d ",T[i]);
    puts("");
}
int main() {
    int vertexCnt = 5;
    double **graph = (double **)malloc(sizeof(double*)*vertexCnt);
    for ( int i = 0 ; i <vertexCnt ; i++ ) 
        graph[i] = (double*)malloc(sizeof(double)*vertexCnt);
    for ( int i = 0 ; i < vertexCnt ; i++ ) 
        for ( int j = 0 ; j < vertexCnt ; j++ ) 
            scanf("%lf",&graph[i][j]);
    runMincut(graph,vertexCnt);
    return 0;
}
