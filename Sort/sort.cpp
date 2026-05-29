#include <stdio.h>
#include <stdlib.h>

/* --- 函数声明 --- */
void QuickSort(int arr[], int left, int right);
void ShellSort(int arr[], int n);
void PrintArray(int arr[], int n);

/* --- 1. 快速排序 (Quick Sort) --- */
/* 原理：分治法。选取基准值(Pivot)，通过一趟排序将数组分为独立的两部分 */
void QuickSort(int arr[], int left, int right) {
    if (left >= right) return; // 递归终止条件

    int i = left;
    int j = right;
    int pivot = arr[left]; // 选取第一个数为分界值

    printf("[快速排序调试] 当前基准值: %d, 区间: [%d, %d]\n", pivot, left, right);

    while (i < j) {
        // 从右向左找第一个小于 pivot 的数
        while (i < j && arr[j] >= pivot) {
            j--;
        }
        if (i < j) {
            arr[i] = arr[j]; // 将小的数移动到左边
        }

        // 从左向右找第一个大于 pivot 的数
        while (i < j && arr[i] <= pivot) {
            i++;
        }
        if (i < j) {
            arr[j] = arr[i]; // 将大的数移动到右边
        }
    }
    arr[i] = pivot; // 基准值归位

    // 递归处理左半部分
    QuickSort(arr, left, i - 1);
    // 递归处理右半部分
    QuickSort(arr, i + 1, right);
}

/* --- 2. 希尔排序 (Shell Sort) --- */
/**
 * @brief 希尔排序算法实现（缩小增量排序）
 * @param arr 待排序的数组指针
 * @param n   数组元素个数
 * @note 算法思想：通过分组预处理使数组提前有序，最终进行普通插入排序
 *       时间复杂度：平均 O(n^1.3)，空间复杂度：O(1)，不稳定排序
 */
void ShellSort(int arr[], int n) {
    int gap;  // 增量（分组间隔），控制分组粒度
    int i;    // 外层循环变量，遍历数组元素
    int j;    // 内层循环变量，在分组内向前比较
    int temp; // 暂存当前待插入元素
    
    // 外层循环：控制增量 gap，从 n/2 递减到 1
    // 每次将增量减半，直到 gap = 1 时进行最终插入排序
    for (gap = n / 2; gap > 0; gap /= 2) {
        printf("[希尔排序调试] 当前增量 gap = %d\n", gap);
        
        // 中层循环：从 gap 位置开始遍历后续所有元素
        // 每个元素 arr[i] 都是其所在分组的待插入元素
        for (i = gap; i < n; i++) {
            temp = arr[i];  // 暂存当前待插入元素
            
            // 内层循环：在同一分组内向前扫描并比较
            // 条件：j >= gap（不越界）且 arr[j-gap] > temp（需要后移）
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];  // 将较大元素向后移动 gap 位
            }
            arr[j] = temp;  // 将 temp 插入到分组内的正确位置
        }
        PrintArray(arr, n); // 输出当前增量排序后的数组状态（调试用）
    }
}

/* 打印数组辅助函数 */
void PrintArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/* --- 主函数 --- */
int main() {
    int n, i;
    int choice;
    int test_arr[100];

    printf("请输入待排序元素的个数: ");
    scanf("%d", &n);

    printf("请输入 %d 个整数:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &test_arr[i]);
    }

    printf("\n请选择排序算法:\n");
    printf("1. 快速排序\n");
    printf("2. 希尔排序\n");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("\n开始快速排序...\n");
        QuickSort(test_arr, 0, n - 1);
    } else if (choice == 2) {
        printf("\n开始希尔排序...\n");
        ShellSort(test_arr, n);
    } else {
        printf("无效选择。\n");
        return 0;
    }

    printf("\n排序完成！最终结果:\n");
    PrintArray(test_arr, n);

    return 0;
}