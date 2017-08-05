#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

void printArr(int *arr, int len) {
    for (int i = 0; i < len; ++i) {
        cout << setw(5) << arr[i];
    }
    cout << endl;
}

// 1.直接插入排序
void insertSort(int *arr, int len) {
    for (int i = 1; i < len; ++i) { // 从第2个元素开始插入，原始单个元素视为有序
        if (arr[i] < arr[i - 1]) {
            int x = arr[i];
            int j = i - 1; // 原始序列的最后一个
            while (x < arr[j] && j >= 0) {
                arr[j + 1] = arr[j];
                j--;
            }
            // 跳出时，x >= arr[j]
            arr[j + 1] = x;
        }
    }
}

// 2.希尔排序
void shellSort(int *arr, int len) {
    for (int dk = len / 2; dk > 0; --dk) { // dk增量
        for (int i = dk; i < len; ++i) { // 1层for
            if (arr[i] < arr[i - dk]) {
                int x = arr[i]; // 哨兵
                int j = i - dk; // 原有序序列最后一个元素
                while (x < arr[j] && j >= 0) {
                    arr[j + dk] = arr[j];
                    j -= dk;
                }
                arr[j + dk] = x;
            }
        }
    }
}

// 3.选择排序
void selectSort(int *arr, int len) {
    for (int i = 0; i < len - 1; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (arr[i] > arr[j]) swap(arr[i], arr[j]); // 最小值放前思想
        }
    }
}

// 4.堆排序
// 调整大顶堆
void heapAdjust(int *arr, int root, int len) {
    int child = 2 * root + 1;
    while (child < len) { // child可以去最后一个元素：len-1
        if (child + 1 < len && arr[child] < arr[child + 1]) child++; // child指向大孩子
        if (arr[root] < arr[child]) {
            swap(arr[root], arr[child]);
            root = child;
            child = 2 * root + 1;
        } else {
            break; // 基于下面已经满足大顶堆
        }
    }
}

// 构建大顶堆
void buildHeap(int *arr, int len) {
    for (int i = (len - 1) / 2; i >= 0; --i) { // (length-1)/2 最大的非叶节点
        heapAdjust(arr, i, len); // i遍历所有的root
    }
}

void heapSort(int *arr, int len) {
    buildHeap(arr, len);
    cout << "调整之后";
    printArr(arr, len);
    while (len > 1) {
        swap(arr[0], arr[len - 1]); // 首尾元素互换
        cout << "len=" << len;
        printArr(arr, len);
        len--;
        heapAdjust(arr, 0, len);
    }
}


// 5.冒泡排序
void bubbleSort(int *arr, int len) {
    for (int i = 0; i < len - 1; ++i) {
        for (int j = 0; j < len - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]); // 最大值放后思想
        }
    }
}

// 6.快速排序
// 分成两部分
int partition(int *arr, int low, int high) {
    int pivot = arr[low]; // 选第1个值为基准值
    while (low < high) {
        while (low < high && arr[high] >= pivot) high--;
        swap(arr[high], arr[low]); // 大小值更换，注意：更换的不是pivot
        while (low < high && arr[low] <= pivot) low++;
        swap(arr[high], arr[low]); // 大小值更换
    }
    return low;
}

void quickSort(int *arr, int low, int high) {
    if (low < high) {
        int pivotLoc = partition(arr, low, high); // 基准值位置
//        printArr(arr, high + 1);
        quickSort(arr, low, pivotLoc - 1);
        quickSort(arr, pivotLoc + 1, high);
    }
}

// 7.归并排序
void merge(int *arr, int low, int mid, int high) {
    auto *tmp = new int[high - low + 1]; // 暂存数据
//    int tmp[high - low + 1]; // 也OK

    // 3个序列迭代器
    int i = low; // 序列1开始
    int j = mid + 1; // 序列2开始
    int k = 0; // 合并新序列开始

    while (i <= mid && j <= high) { // 都得小于最后一个元素
        tmp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    }

    while (i <= mid) tmp[k++] = arr[i++];
    while (j <= high) tmp[k++] = arr[j++];

    i = low; // arr序列开始的位置
    k = 0;
    while (i <= high) arr[i++] = tmp[k++];
}

void mergeSort(int *arr, int low, int high) {
    int mid;
    if (low < high) {
        mid = (low + high) / 2;
        mergeSort(arr, low, mid); // 这里和merge中的j值有关
        mergeSort(arr, mid + 1, high); // 先mergeSort成2个有序序列，再将2个序列合并有完整有序
        merge(arr, low, mid, high);
    }
}

// 8.基数排序
void radixSort(int *arr, int len, int radix) {

    // 先找到待排序元素的上下界
    int max = arr[0];
    int min = arr[0];
    for (int i = 1; i < len; ++i) {
        if (max < arr[i]) max = arr[i];
        if (min > arr[i]) min = arr[i];
    }
//    cout << max << "\t" << min << endl;

    int bucket_num = max / radix - min / radix + 1; // 桶的数量，一定要分开除
    int bucket_arr[bucket_num][len]; // 存储元素
    int bucket_len[bucket_num]; // 记录每个桶的元素个数

    for (int i = 0; i < bucket_num; ++i) bucket_len[i] = 0; // 赋初值

    // 元素进入桶
    cout << "元素进桶" << endl;
    for (int i = 0; i < len; ++i) {
        int bucket_id = arr[i] / radix - min / radix; // 桶id转移到数列下标，一定要分开除
        bucket_arr[bucket_id][bucket_len[bucket_id]] = arr[i];
        bucket_len[bucket_id]++;
    }

    // 打印各桶元素
    for (int i = 0; i < bucket_num; ++i) {
        cout << radix * (min / radix + i) << "," << radix * (min / radix + i + 1) - 1 << ": ";
        printArr(bucket_arr[i], bucket_len[i]);
    }

    cout << "桶内排序" << endl;
    for (int i = 0; i < bucket_num; ++i) {
        if (bucket_len[i] > 1) quickSort(bucket_arr[i], 0, bucket_len[i] - 1);
    }

    // 打印排序后各桶元素
    for (int i = 0; i < bucket_num; ++i) {
        cout << radix * (min / radix + i) << "," << radix * (min / radix + i + 1) - 1 << ": ";
        printArr(bucket_arr[i], bucket_len[i]);
    }

    // 排序后元素拷贝
    int k = 0;
    for (int i = 0; i < bucket_num; ++i) {
        for (int j = 0; j < bucket_len[i]; ++j) {
            arr[k] = bucket_arr[i][j];
            k++;
        }
    }
}

int main() {

    // 随机生成数据
    int len = 20;
    auto *arr = new int[len];
    srand((unsigned int) time(nullptr));
    for (int i = 0; i < len; ++i) arr[i] = (int) random() % 100;

    printArr(arr, len);

    radixSort(arr, len, 10); // 可以调整radix值

    printArr(arr, len);
}

