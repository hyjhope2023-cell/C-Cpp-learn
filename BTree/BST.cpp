#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define EXIT 0
typedef struct TNode *Position;	
typedef Position BinTree;	/* 二叉树类型 */
typedef int ElementType;	/* 假设结点数据为整数 */

// 二叉树结点
struct TNode{
	ElementType Data;	/* 结点数据 */
	BinTree Left;		/* 指向左子树 */
	BinTree Right;		/* 指向右子树 */
};

Position Find(BinTree BST, ElementType X)
{
	while(BST){
		if(X > BST->Data){	
			// 当 X > Data 时，查找右子树
			BST = BST->Right;
		}
		else if(X < BST->Data){
			// 当 X < Data 时，查找左子树
			BST = BST->Left;
		}
		else{	//找到X所在结点，或结点不存在
			break;
		}
	}
	return BST;
}

Position FindMin(BinTree BST)
{
	if(!BST){
		return NULL;
	}
	else if(!BST->Left){	//当左子树为空时，返回当前结点
		return BST;
	}
	else{	//继续在左子树中寻找最小元素
		return FindMin(BST->Left);
	}
}

Position FindMax(BinTree BST)
{
	if(!BST){
		return NULL;
	}
	else if(!BST->Right){	//当右子树为空时，返回当前结点
		return BST;
	}
	else{	//继续在右子树中寻找最大元素
		return FindMax(BST->Right);
	}
}

BinTree Insert(BinTree BST, ElementType X)
{
	if(!BST){ //当前结点不存在时，生成Data=X的结点
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Right = BST->Left = NULL;
	}
	else{
		if(X>BST->Data){
			//当X>Data时，插入其右子树
			BST->Right = Insert(BST->Right,X);
		}
		else if(X<BST->Data){
			//当X<Data时，插入其左子树
			BST->Left = Insert(BST->Left,X);
		}
	}
	return BST;
}

Position Delete(BinTree BST, ElementType X)
{
	if(!BST){
		return NULL;
	}
	else if(X>BST->Data){
		//当X>Data时，在右子树中删除
		BST->Right = Delete(BST->Right,X);
	}
	else if(X< BST->Data){
		//当X<Data时，在左子树中删除
		BST->Left = Delete(BST->Left,X);
	}
	else{
		//找到要删除的结点
		if(BST->Left && BST->Right){	
			//当左右子树都存在时，找到右子树中的最小元素替换当前结点，并删除右子树中的最小元素
			BST->Data = FindMin(BST->Right)->Data;
			BST->Right = Delete(BST->Right, BST->Data);
		}
		else{	
			//当左右子树至少有一个不存在时，直接用非空子树替换当前结点，并删除当前结点
			BinTree temp = BST;
			if(!BST->Left){
				BST = BST->Right;
			}
			else{
				BST = BST->Left;
			}
			free(temp);
		}
	}
	return BST;
}
void orderTraversal(BinTree BT)
{
	if(BT){
		orderTraversal(BT->Left);
		printf("%d ", BT->Data);
		orderTraversal(BT->Right);
	}
}

BinTree CreateBST()
{
	BinTree temp=NULL;
	ElementType ch;
	/* ===循环创建=== */
	// 输入结点个数
	int cnt;
	if(scanf("%d", &cnt) != 1 || cnt <= 0){
		return NULL;
	}

	for(int i = 0; i < cnt; i++){
		if(scanf("%d", &ch) != 1){
			break;
		}
		temp = Insert(temp, ch);
	}
	return temp;
}



int main()
{
	BinTree tr;
	printf("input data\n");
	tr = CreateBST();
	orderTraversal(tr);
	printf("\n");

	// 插入10
	printf("insert 10\n");
	Insert(tr, 10);
	orderTraversal(tr);
	printf("\n");
	printf("find 10: %d\n",Find(tr, 10)->Data);
	printf("min: %d\n",FindMin(tr)->Data);
	printf("max: %d\n",FindMax(tr)->Data);
	// 删除10
	printf("delete 10\n");
	Delete(tr, 10);
	orderTraversal(tr);
	printf("\n");

	system("pause");
		
}




