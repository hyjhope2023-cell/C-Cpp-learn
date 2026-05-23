#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#define Number 5

typedef std::string Name;
typedef int Student_ID;
typedef int Position;

typedef struct Student {
    Name name[Number];
    Student_ID ID[Number];
    Position Last;
} *List, seqlist_t;

//typedef struct Student seqlist_t;

// 辅助函数：显示顺序表元素
void show_seqlist(seqlist_t* L)
{
    if (L == NULL )
    {
        puts("seqlist_t *L is NULL\n");
        return;
    }
    
    else if (L->Last == -1)
    {
        printf("%d", L->Last);
        printf("顺序表内无学生信息\n");
        return;

    }
    printf("开始显示顺序表元素\n");
    for (int i = 0; i <= L->Last; i++)
    {
        std::cout << "位序" << i + 1 << " " << "姓名：" << L->name[i] << " " << "学号：" << L->ID[i] << std::endl;
    }
}

/* 初始化 */
List MakeEmpty()
{
    List PtrL = NULL;
    PtrL = new Student;
    //PtrL = (Student*)malloc(sizeof(Student));
    if (PtrL == NULL) {
        printf("内存分配失败");
        return NULL;
    }
    PtrL->Last = -1;
    return PtrL;
}

void Input_List(List L)
{

    Position i = 0;
    while (i < Number)
    {
        printf("输入第 %d 位学生的姓名和学号 (输入姓名 '#' 结束)\n", i + 1);
        printf("姓名：");
        std::string tempName;
        std::cin >> tempName;
        if (tempName == "#") break;

        printf("学号：");
        int tempID;
        if (!(std::cin >> tempID))  // 防止输入非数字
        {
            printf("\n");
            break;
        }

        L->name[i] = tempName;
        L->ID[i] = tempID;
        L->Last = i;
        i++;
    }
}

/* 查找 */
#define ERROR -1
#define INVALID_ID -1  // 定义无效学号值
Position Find(List L, Name n = "", Student_ID id = INVALID_ID)
{
    Position i = 0; //查找值所在数组下标
    if (n.empty() && id == INVALID_ID)
    {
        printf("未指定查找对象");
        return ERROR;
    }
    if (!n.empty()) // 按姓名查找
    {
        while (i <= L->Last && L->name[i] != n) {
            i++;
        }
    }
    else if(id != INVALID_ID)   // 按学号查找
    {
        while (i <= L->Last && L->ID[i] != id) {
            i++;
        }
    }
    if (i > L->Last) {
        printf("未找到指定对象\n");
        return ERROR;
    }
    else {
        std::cout << "学员：" << L->name[i] << " " << "学号为：" << L->ID[i] << " " << "位序为" << i+1 << std::endl;
        return i;
    }
}

/* 插入 */
bool Insert(List L, Name n, Student_ID id, int i)
{
    Position j;
    if (L->Last == Number - 1) {
        printf("表满,无法插入\n"); return false;
    }
    if (i < 1 || i > L->Last + 2) {
        printf("位序不合法,无法插入\n");
        return false;
    }
    for (j = L->Last; j >= i - 1; j--)
    {
        L->name[j + 1] = L->name[j];
        L->ID[j + 1] = L->ID[j];
    }
    L->name[i - 1] = n;
    L->ID[i - 1] = id;

    L->Last++;
    printf("成功在位序 %d 前面插入元素\n", i);
    return true;
}

/* 删除 */
bool Delete(List L, int i)
{
    Position j;
    if (i < 1 || i > L->Last + 1) {
        printf("位序%d 不存在元素，删除失败\n", i);
        return false;
    }
    for (j = i; j <= L->Last; j++)
    {
        L->name[j - 1] = L->name[j];
        L->ID[j - 1] = L->ID[j];
    }

    L->Last--;
    printf("成功删除位序 %d 的元素\n", i);
    return true;
}

int main() {
    List L = MakeEmpty();
    // 初始化顺序表
    Input_List(L);
    

    show_seqlist(L);

    // 在位序为 2 的地方插入
    Insert(L, "张三", 666, 2);
    //显示顺序表所有元素
    show_seqlist(L);

    //删除第 3 个元素
    Delete(L, 3);
    //显示顺序表所有元素
    show_seqlist(L);

    //查找值为 x 的元素位置并显示
    Position p =Find(L, "张三");
    p = Find(L, "", 666);

    // 释放内存
    delete L;

    system("pause");
    return 0;
}