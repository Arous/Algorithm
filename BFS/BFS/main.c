#include <stdio.h>

#define MAXVERTEX	1000
#define MAXQUEUE	1000
#define MAXSTACK	1000

// queue
typedef struct queue {
	int n;
	int arrQ[MAXQUEUE];
} Queue;

void InitQueue(Queue *q);
int Dequeue(Queue *q);
void Enqueue(Queue *q, int n);

// stack
typedef struct stack{
	int n;
	int arrSt[MAXSTACK];
} Stack;

void InitStack(Stack *st);
int Pop(Stack *st);
void Push(Stack *st, int n);


// graph
typedef struct graph {
	int n;
	int adjM[MAXVERTEX][MAXVERTEX];
} Graph;

void InitGraph(Graph *g);
void InsertVertex(Graph *g, int v);
void InsertEdge(Graph *g, int start, int end);


void BFS(Graph *g, Queue *q, int V);
void DFS(Graph *g, Stack *st, int V);

Graph graph;
Queue queue;
Stack stack;

int main()
{

	int N, M, V;

	scanf("%d %d %d", &N, &M, &V);

	InitGraph(&graph);
	InitQueue(&queue);
	InitStack(&stack);

	for (int i = 0; i < N; i++) {
		InsertVertex(&graph, i + 1);
	}

	for (int i = 0; i < M; i++) {
		int start, end;
		scanf("%d %d", &start, &end);
		InsertEdge(&graph, start-1, end-1);
	}

	BFS(&graph, &queue, V);
	printf("\n");
	DFS(&graph, &stack, V);

	return 0;
}

// Graph
void InitGraph(Graph *g)
{
	int i, j;

	g->n = 0;

	for (i = 0; i < MAXVERTEX; i++) {
		for (j = 0; j < MAXVERTEX; j++) {
			g->adjM[i][j] = -1;
		}
	}
}

void InsertVertex(Graph *g, int v)
{
	if ((g->n) + 1 > MAXVERTEX) {
		printf("Error, out of range[VERTEX]\n");
		exit(-1);
	}

	g->n++;
}

void InsertEdge(Graph *g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		printf("Incorrect edge\n");
		exit(-1);
	}

	g->adjM[start][end] = 1;
	g->adjM[end][start] = 1;
}

// Queue
void InitQueue(Queue *q)
{
	for (int i = 0; i < MAXQUEUE; i++) {
		q->arrQ[i] = -1;
	}

	q->n = 0;
}

void Enqueue(Queue *q, int n)
{
	if (q->arrQ[0] == -1) {
		q->arrQ[0] = n;
	}

	else {
		for (int i = 0; i < MAXQUEUE; i++) {
			if (q->arrQ[i] == n) {
				return;
			}

			if (q->arrQ[i] == -1) {
				q->arrQ[i] = n;
				break;
			}
		}
	}

	q->n++;
}

int Dequeue(Queue *q)
{
	int head = 0;

	if (q->arrQ[0] == -1) {
		printf("Already Empty Queue\n");
	}

	else {
		head = q->arrQ[0];
		
		for (int i = 0; i < MAXQUEUE-1; i++) {
			q->arrQ[i] = q->arrQ[i + 1];
		}
		
		q->arrQ[MAXQUEUE] = -1;
		q->n--;
	}

	printf("%d ", head+1);
	return head;
}

// stack
void InitStack(Stack *st)
{
	for (int i = 0; i < MAXSTACK; i++) {
		st->arrSt[i] = -1;
	}

	st->n = 0;
}

int Pop(Stack *st)
{
	int ret = -1;

	if (st->n == 0) {
		printf("Stack is Empty\n");
		
		return -1;
	}

	else {
		for (int i = 0; i < MAXSTACK; i++) {
			if (st->arrSt[i] != -1) {
				ret = st->arrSt[i];
				st->arrSt[i] = -1;
				st->n--;
				break;
			}
		}
	}

	printf("%d ", ret+1);

	return ret;
}

void Push(Stack *st, int n)
{
	for (int i = 0; i < MAXSTACK; i++) {
		if (st->arrSt[i] == -1) {
			st->arrSt[i] = n;
			st->n++;
			break;
		}
	}
}

void BFS(Graph *g, Queue *q, int V)
{
	int visit[MAXVERTEX] = { 0, };
	int vertex = 0;

	Enqueue(q, V-1);

	while (q->arrQ[0] != -1) {
		vertex = Dequeue(q);

		for (int i = 0; i < MAXVERTEX; i++) {
			if (g->adjM[vertex][i] == 1 && visit[i] != 1) {
				Enqueue(q, i);
			}
		}

		visit[vertex] = 1;
	}
}

void DFS(Graph *g, Stack *st, int V)
{
	int visit[MAXVERTEX] = { 0, };
	int vertex = 0;

	Push(st, V - 1);

	while (st->arrSt[0] != -1) {
		vertex = Pop(st);

		for (int i = 0; i < MAXVERTEX; i++) {
			if (g->adjM[vertex][i] == 1 && visit[i] != 1) {
				Push(st, i);
			}
		}

		visit[vertex] = 1;
	}
}