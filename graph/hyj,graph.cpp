#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MaxVertexNum 100	/* 最大顶点个数 */

typedef int Vertex;
typedef int WeightType;		/* 边的权重 */
typedef char DataType;		/* 顶点储存的数据类型 */
typedef int Bool;

/* 边的定义 */
typedef struct ENode{
	Vertex V1,V2;		/* 有向边<V1,V2> */
	WeightType Weight;	/* 边的权重 */
}*PtrToENode,*Edge;

/* 邻接点的定义 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
	Vertex AdjV;		/* 邻接点的下标 */
	WeightType Weight;	/* 边权重 */
	PtrToAdjVNode Next;	/* 指向下一个邻接点的指针 */
};

/* 顶点表头结点的定义 */
typedef struct VNode{
	PtrToAdjVNode FirstEdge;	/*边表头指针 */
	DataType Data;	/* 顶点的数据 */
}AdjList[MaxVertexNum];

/* 图结点的定义 */
typedef struct GNode{
	int Nv;		/* 顶点数 */
	int Ne;		/* 边数 */
	AdjList G;	/* 邻接表 */
 }*PtrToGNode,*LGraph;	/* LGraph 以邻接表方式存储的图类型 */

/* 创建无边的顶点图 */
LGraph CreateGraph(int VertexNum){
	LGraph graph = (LGraph)malloc(sizeof(struct GNode));
	if(!graph){return graph;}
	graph->Nv = VertexNum;
	graph->Ne = 0;
	for (int i=0;i<VertexNum;i++){
		graph->G[i].FirstEdge = NULL;
		graph->G[i].Data = 0;
	}
	return graph;
}

void InsertEdge(LGraph Graph, Edge E)
{
	PtrToAdjVNode newNode = (PtrToAdjVNode)malloc(sizeof(PtrToAdjVNode));
	if(!newNode){return;}
	/* V1->V2 */
	newNode->AdjV = E->V2;
	newNode->Weight = E->Weight;
	newNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = newNode;

	/* V2->V1 */
	newNode = (PtrToAdjVNode)malloc(sizeof(PtrToAdjVNode));
	newNode->AdjV = E->V1;
	newNode->Weight = E->Weight;
	newNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = newNode;
}

LGraph BuildGraph(){
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv,i;

	/* 初始化顶点图 */
	printf("请输入顶点个数：");
	scanf("%d",&Nv);
	Graph = CreateGraph(Nv);	

	/* 输入边数 */
	printf("请输入边数：");
	scanf("%d",&Graph->Ne);	

	/* 如果无边，则退出 */
	if(Graph->Ne <= 0){ return Graph;}
	/*有边时 */
	E = (Edge)malloc(sizeof(struct ENode));	/* 建立边结点 */

	/* 读入边，格式为"起点 终点 权重", 插入邻接矩阵 */
	printf("输入边(格式为：起点 终点 权重):\n");

	for(i=0;i<Graph->Ne;i++){
		scanf("%d %d %d",&E->V1,&E->V2,&E->Weight);
		InsertEdge(Graph,E);
	}
	return Graph;
}

/* 深度优先搜索 */
bool visited[MaxVertexNum];	/* 访问结点标记 */

void DFS(LGraph graph,Vertex index)
{
	PtrToAdjVNode temp;	

	printf("下标：%d,权重：%d\n",graph->G[index].FirstEdge->AdjV,graph->G[index].FirstEdge->Weight);
	visited[index] = TRUE;

	temp = graph->G[index].FirstEdge->Next;
	while(temp){
		if(!visited[temp->AdjV]){
			DFS(graph,temp->AdjV);
		}
		temp = temp->Next;
	}
}

void DFS_Visit(LGraph graph){
	/* 消除访问标示 */
	for(int i=0;i<MaxVertexNum;i++){
		visited[i] = 0;
	}

	for(int i=0;i<graph->Nv;i++){
		if(!visited[i]){
			DFS(graph,i);
		}
	}

}


int main()
{
	LGraph graph;

	graph = BuildGraph();


	DFS_Visit(graph);

	system("pause");
}



