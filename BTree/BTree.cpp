#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef char ElementType;   // 定义数据类型
typedef struct TreeNode *Node;

// 定义树节点结构
typedef struct TreeNode{
	ElementType Data;
	Node left;
	Node right;
}TREE, *PTREE;


//==========层序创建队列定义=================
// 定义层序创建队列
typedef struct TQueue *PtrTQ;
struct TQueue{
	PTREE bt[MAXSIZE];
	int front;
	int rear;
};

// 创建队列
PtrTQ createQueue()
{
	PtrTQ q;
	q = (PtrTQ)malloc(sizeof(struct TQueue));
	if(q == NULL){
		printf("队列创建失败");
		return NULL;
	}
	q->front = 0;
	q->rear = 0;
	return q;
}
// 判断队列是否为满
bool IsFull(PtrTQ q)
{
	return q->front == (q->rear+1)%MAXSIZE;
}
// 判断队列是否为空
bool IsEmpty(PtrTQ q)
{
	return q->front == q->rear;
}
// 在队列中添加二叉树结点
void Add(PtrTQ q,PTREE bt)
{
	if(IsFull(q)){
		printf("队列已满");
		return;
	}
	q->rear = (q->rear+1)%MAXSIZE;
	q->bt[q->rear] = bt;
}
// 从队列中取出二叉树结点
PTREE Pop(PtrTQ q)
{
	if(IsEmpty(q)){
		printf("队列为空");
		return NULL;
	}
	q->front = (q->front + 1) % MAXSIZE;
	return q->bt[q->front];
}


//============二叉树的操作函数=============
// 先序遍历
void PreOrderTree(PTREE Root)
{
	if(Root == NULL){return;}
	putchar(Root->Data);
	PreOrderTree(Root->left);
	PreOrderTree(Root->right);
}

// 中序遍历
void InOrderTree(PTREE Root)
{
	if(Root == NULL){return;}
	PreOrderTree(Root->left);
	putchar(Root->Data);
	PreOrderTree(Root->right);
}

// 后序遍历
void PostOrderTree(PTREE Root)
{
	if(Root == NULL){return;}
	PreOrderTree(Root->left);
	PreOrderTree(Root->right);
	putchar(Root->Data);
}

// 创建二叉树结点
Node createTreeNode()
{
	Node temp;
	temp = (Node)malloc(sizeof(TREE));
	if (temp == NULL) {
		printf("内存分配失败");
		return NULL;
	}
	temp->Data = NULL;
	temp->left = temp->right = NULL;
	return temp;
}

// 先序创建二叉树
PTREE createBTree()
{
	
	ElementType ch;
	PTREE t;
	//printf("请输入%d节点数据：",cnt++);
	scanf("%c",&ch);
	
	if(ch == '#'){
		t = NULL;
	}
	else{
		t = createTreeNode();
		t->Data = ch;
		//printf("left\n");
		t->left = createBTree();
		//printf("right\n");
		t->right = createBTree();
	}
	return t;
}

// 层序创建二叉树
PTREE createBTbyLevel()
{
	ElementType ch;  //存储结点值
	PTREE root = NULL,			// 二叉树根节点
		temp,					// 指向当前操作的节点
		newNode;				// ch为有效值时生成的新结点
	PtrTQ q = createQueue();	// 二叉树层序创建结点队列

	printf("请按层序输入节点数据（#表示空）：");

	scanf(" %c", &ch); 
	if (ch != '#') {
		root = createTreeNode();
		root->Data = ch;
		Add(q, root);
	}
	else {
		return NULL;
	}

	while (!IsEmpty(q)) {
		temp = Pop(q);

		// 处理左孩子
		scanf(" %c", &ch);
		if (ch != '#') {
			newNode = createTreeNode();
			newNode->Data = ch;
			temp->left = newNode;
			Add(q, newNode); 
		}
		else {
			temp->left = NULL;
		}

		// 处理右孩子
		scanf(" %c", &ch);
		if (ch != '#') {
			newNode = createTreeNode();
			newNode->Data = ch;
			temp->right = newNode;
			Add(q, newNode);
		}
		else {
			temp->right = NULL;
		}
	}

	return root;
}

// 计算树结点个数
int Count(PTREE bt)
{
	if(bt == NULL){
		return 0;
	}
	return Count(bt->left)+Count(bt->right)+1;
}

// 计算树高
int GetHeight(PTREE bt)
{
	if(bt == NULL){
		return 0;
	}
	int left = GetHeight(bt->left);
	int right = GetHeight(bt->right);
	int max = left>right?left:right;
	return max+1;
}

int main()
{
	PTREE Root;
	printf("请层序输入二叉树的结点数据\n");
	Root = createBTbyLevel();

	printf("\n先序遍历结果为：");
	PreOrderTree(Root);
	
	printf("\n中序遍历结果为：");
	InOrderTree(Root);
	
	printf("\n后序遍历结果为：");
	PostOrderTree(Root);

	printf("结点个数为：%d\n",Count(Root));
	printf("树高度为：%d\n",GetHeight(Root));

	system("pause");

}
