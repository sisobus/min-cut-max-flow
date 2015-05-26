#ifndef MINCUT_H_
#define MINCUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

#define MAX_V 1000
#ifndef false
#define false 0
#endif 
#ifndef true
#define true !(false)
#endif

static int V;

/* queue */
static int q[(1<<20)];
static int front,back;

static void initQueue();
static int isEmpty();
static void enqueue(int item);
static int dequeue();
/* queue */

static double** capacity, flow[MAX_V][MAX_V];

double   min(double a,double b);
double   nf(int source, int sink);
void   runMincut(double** graph, int vertexCnt);

#endif /*MINCUT_H_*/
