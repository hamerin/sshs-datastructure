#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX 10

typedef struct StackNode {
    int data;
    struct StackNode *link;

} StackNode;

typedef struct Stack {
    StackNode *top;

    bool (*empty)(struct Stack *this);
    void (*emplace)(struct Stack *this, int data);
    int (*pop)(struct Stack *this);
} Stack;

bool _internal_Stack_empty(Stack *this) {
    return this->top == NULL;
}

void _internal_Stack_emplace(Stack *this, int data) {
    StackNode *apd = (StackNode *)malloc(sizeof(StackNode));
    apd->data = data;
    apd->link = this->top;
    this->top = apd;
}

int _internal_Stack_pop(Stack *this) {
    if (this->empty(this)) exit(1);

    StackNode *del = this->top;
    int popped = del->data;

    this->top = del->link;
    free(del);

    return popped;
}

void initStack(Stack *stk) {
    stk->top = NULL;
    stk->empty = _internal_Stack_empty;
    stk->emplace = _internal_Stack_emplace;
    stk->pop = _internal_Stack_pop;
}


typedef struct QueueNode {
    int data;
    struct QueueNode *link;
} QueueNode;

typedef struct Queue {
    QueueNode *front, *rear;

    bool (*empty)(struct Queue *this);
    void (*emplace)(struct Queue *this, int item);
    int (*pop)(struct Queue *this);
} Queue;

bool _internal_Queue_empty(Queue *this) {
    return this->front == NULL && this->rear == NULL;
}

void _internal_Queue_emplace(Queue *this, int item) {
    if (this->empty(this)) {
        this->rear = (QueueNode *)malloc(sizeof(QueueNode));
        this->rear->data = item;
        this->front = this->rear;
    } else {
        this->rear->link = (QueueNode *)malloc(sizeof(QueueNode));
        this->rear = this->rear->link;
        this->rear->data = item;
    }
}

int _internal_Queue_pop(Queue *this) {
    if (this->empty(this)) exit(1);

    QueueNode *del = this->front;
    int ret = del->data;

    if (del == this->rear) {
        this->front = NULL;
        this->rear = NULL;
    } else {
        this->front = del->link;
    }

    free(del);

    return ret;
}

void initQueue(Queue *Q) {
    Q->front = NULL;
    Q->rear = NULL;
    Q->empty = _internal_Queue_empty;
    Q->emplace = _internal_Queue_emplace;
    Q->pop = _internal_Queue_pop;
}


typedef struct GraphNode {
    int vertex;
    struct GraphNode *link;
} GraphNode;

typedef struct Graph {
    int N;
    GraphNode *adjList_H[MAX_VERTEX];

    void (*insertVertex)(struct Graph *this);
    void (*insertEdge)(struct Graph *this, int u, int v);
    void (*printAdj)(struct Graph *this);
    void (*DFS)(struct Graph *this, int v);
    void (*BFS)(struct Graph *this, int v);
} Graph;

void _internal_Graph_insertVertex(Graph *this) {
    GraphNode *apd = (GraphNode *)malloc(sizeof(GraphNode));
    apd->vertex = this->N;
    this->adjList_H[this->N++] = apd;
}

void _internal_Graph_insertEdge(Graph *this, int u, int v) {
    GraphNode *apd = (GraphNode *)malloc(sizeof(GraphNode));
    apd->vertex = v;
    apd->link = this->adjList_H[u]->link;
    this->adjList_H[u]->link = apd;
}

void _internal_Graph_printAdj(Graph *this) {
    for (int i = 0; i < this->N; i++) {
        printf("\n\t정점 %d의 인접 리스트", i);
        GraphNode *cur = this->adjList_H[i];
        while (cur) {
            printf(" -> %d", cur->vertex);
            cur = cur->link;
        }
    }
}

void _internal_Graph_DFS(Graph *this, int s) {
    bool *vst = (bool *)malloc(sizeof(bool) * this->N);
    Stack *stk = (Stack *)malloc(sizeof(Stack));

    memset(vst, 0, sizeof(vst));
    initStack(stk);

    vst[s] = true;
    stk->emplace(stk, s);
    printf("%d ", s);

    while (!stk->empty(stk)) {
        int h = stk->top->data;
        GraphNode *cur = this->adjList_H[h];

        while (cur) {
            int t = cur->vertex;

            if (!vst[t]) {
                printf("%d ", t);
                vst[t] = true;
                stk->emplace(stk, t);
                goto nextLoop;
            }

            cur = cur->link;
        }

        stk->pop(stk);

    nextLoop:;
    }

    printf("\n");

    free(vst);
    free(stk);
}

void _internal_Graph_BFS(Graph *this, int s) {
    bool *vst = (bool *)malloc(sizeof(bool) * this->N);
    Queue *que = (Queue *)malloc(sizeof(Queue));

    memset(vst, 0, sizeof(vst));
    initQueue(que);

    vst[s] = true;
    que->emplace(que, s);
    printf("%d ", s);

    while (!que->empty(que)) {
        int h = que->pop(que);
        GraphNode *cur = this->adjList_H[h];

        while (cur) {
            int t = cur->vertex;

            if (!vst[t]) {
                printf("%d ", t);
                vst[t] = true;
                que->emplace(que, t);
            }

            cur = cur->link;
        }
    }

    printf("\n");

    free(vst);
    free(que);
}

void initGraph(Graph *G) {
    G->N = 0;
    G->insertVertex = _internal_Graph_insertVertex;
    G->insertEdge = _internal_Graph_insertEdge;
    G->printAdj = _internal_Graph_printAdj;
    G->DFS = _internal_Graph_DFS;
    G->BFS = _internal_Graph_BFS;
}

int main() {
    Graph *G;
    G = (Graph *)malloc(sizeof(Graph));
    initGraph(G);

    for (int i = 0; i < 7; i++) G->insertVertex(G);

    G->insertEdge(G, 0, 2);
    G->insertEdge(G, 0, 1);
    G->insertEdge(G, 1, 4);
    G->insertEdge(G, 1, 3);
    G->insertEdge(G, 1, 0);
    G->insertEdge(G, 2, 4);
    G->insertEdge(G, 2, 0);
    G->insertEdge(G, 3, 6);
    G->insertEdge(G, 3, 1);
    G->insertEdge(G, 4, 6);
    G->insertEdge(G, 4, 2);
    G->insertEdge(G, 4, 1);
    G->insertEdge(G, 5, 6);
    G->insertEdge(G, 6, 5);
    G->insertEdge(G, 6, 4);
    G->insertEdge(G, 6, 3);

    printf("\n G의 인접 리스트");
    G->printAdj(G);

    printf("\n\n//////////////////////////////////////////////\n\n깊이 우선 탐색 >> ");
    G->DFS(G, 0);

    printf("\n//////////////////////////////////////////////\n\n너비 우선 탐색 >> ");
    G->BFS(G, 0);

    return 0;
}