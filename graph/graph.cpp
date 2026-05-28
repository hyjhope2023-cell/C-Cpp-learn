#include <stdio.h> 
#include <stdlib.h>

#define TRUE 1 
#define FALSE 0
#define MaxVertexNum 100 

typedef int Vertex;     
typedef int WeightType; 
typedef char DataType;  
typedef int Bool;

Bool Visited[MaxVertexNum]; 

/* --- 结构定义 --- */
typedef struct ENode *PtrToENode;
struct ENode {
    Vertex V1, V2;      
    WeightType Weight;  
};
typedef PtrToENode Edge;

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
    Vertex AdjV;        
    WeightType Weight;  
    PtrToAdjVNode Next; 
};

typedef struct Vnode {
    PtrToAdjVNode FirstEdge; 
    DataType Data;           
} AdjList[MaxVertexNum];     

typedef struct GNode *PtrToGNode;
struct GNode {
    int Nv;     
    int Ne;     
    AdjList G;  
};
typedef PtrToGNode LGraph;

/* --- 队列辅助调试 --- */
typedef struct {
    Vertex Data[MaxVertexNum];
    int Front, Rear;
} Queue;

void FlushQueue(Queue *Q) { Q->Front = Q->Rear = 0; }
void EnQueue(Queue *Q, Vertex V) { 
    printf("    [队列] 节点 %d 入队\n", V);
    Q->Data[Q->Rear++] = V; 
}
Vertex DeQueue(Queue *Q) { 
    Vertex V = Q->Data[Q->Front++];
    printf("    [队列] 节点 %d 出队\n", V);
    return V;
}
int IsEmpty(Queue *Q) { return Q->Front == Q->Rear; }

/* --- 图创建函数 --- */
LGraph CreateGraph(int VertexNum) {
    Vertex V;
    LGraph Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for (V = 0; V < Graph->Nv; V++) Graph->G[V].FirstEdge = NULL;
    printf("[系统] 已初始化包含 %d 个顶点的空图\n", VertexNum);
    return Graph;
}

void InsertEdge(LGraph Graph, Edge E) {
    PtrToAdjVNode NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
    
    // 头插法
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;
    
    printf("[调试] 插入边: %d -> %d (权重: %d)\n", E->V1, E->V2, E->Weight);
}

LGraph BuildGraph() {
    LGraph Graph;
    Edge E;
    int Nv, Ne, i;
    printf("请输入顶点个数: ");
    scanf("%d", &Nv);
    Graph = CreateGraph(Nv);
    printf("请输入边数: ");
    scanf("%d", &Ne);
    Graph->Ne = Ne;
    if (Ne != 0) {
        E = (Edge)malloc(sizeof(struct ENode));
        printf("请依次输入 %d 条边 (起点 终点 权重):\n", Ne);
        for (i = 0; i < Ne; i++) {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            InsertEdge(Graph, E);
        }
        free(E);
    }
    return Graph;
}

/* --- 深度优先搜索 DFS --- */
void DFS(LGraph Graph, Vertex V) {
    PtrToAdjVNode W;
    
    Visited[V] = TRUE;
    printf("\n--> 进入 DFS(%d)", V);
    
    // 遍历邻接点
    for (W = Graph->G[V].FirstEdge; W; W = W->Next) {
        printf("\n    [DFS(%d)] 检查邻接点 %d...", V, W->AdjV);
        if (!Visited[W->AdjV]) {
            printf(" 未访问，准备递归...");
            DFS(Graph, W->AdjV);
        } else {
            printf(" 已访问过，跳过。");
        }
    }
    printf("\n<-- 退出 DFS(%d)", V);
}

/* --- 广度优先搜索 BFS --- */
void BFS(LGraph Graph, Vertex S) {
    Queue Q;
    FlushQueue(&Q);
    PtrToAdjVNode W;
    Vertex V;

    printf("\n开始 BFS 起始点: %d\n", S);
    Visited[S] = TRUE;
    EnQueue(&Q, S);

    while (!IsEmpty(&Q)) {
        V = DeQueue(&Q);
        printf("  正在处理节点 %d 的邻接点:\n", V);
        
        for (W = Graph->G[V].FirstEdge; W; W = W->Next) {
            printf("    检查邻接点 %d...", W->AdjV);
            if (!Visited[W->AdjV]) {
                printf(" 发现新节点，标记并入队\n");
                Visited[W->AdjV] = TRUE;
                EnQueue(&Q, W->AdjV);
            } else {
                printf(" 已访问过\n");
            }
        }
    }
}

/* --- 主函数 --- */
int main() {
    Vertex V;
    LGraph Graph = BuildGraph();

    printf("\n========== 开始 DFS 遍历 ==========\n");
    for (V = 0; V < Graph->Nv; V++) Visited[V] = FALSE;
    for (V = 0; V < Graph->Nv; V++) {
        if (!Visited[V]) {
            printf("\n[连通分量启动] 从节点 %d 开始:", V);
            DFS(Graph, V);
        }
    }

    printf("\n\n========== 开始 BFS 遍历 ==========\n");
    for (V = 0; V < Graph->Nv; V++) Visited[V] = FALSE;
    for (V = 0; V < Graph->Nv; V++) {
        if (!Visited[V]) {
            printf("\n[连通分量启动] 从节点 %d 开始:", V);
            BFS(Graph, V);
        }
    }

    printf("\n==================================\n");
    printf("实验完成。\n");
    return 0;
}