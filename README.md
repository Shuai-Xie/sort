## [八大排序 - 简书博客](http://www.jianshu.com/p/4dabdcb6d945)

[八大排序算法 - 真实的归宿 - CSDN](http://blog.csdn.net/hguisu/article/details/7776068/)

### 内部排序和外部排序
- 内部排序数据少，数据记录在内存中进行排序，八大排序都是内部排序。
- 外部排序数据很大，一次不能容纳全部的排序记录，在排序过程中需要访问外存。

![](http://upload-images.jianshu.io/upload_images/1877813-ad5d00b8a219f203.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

当 n 较大，则应采用时间复杂度为 ***O(nlog~2~n)*** 的排序方法：快速排序、堆排序或归并排序。快速排序是目前基于比较的内部排序中被认为是最好的方法，**当待排序的关键字是随机分布时，快速排序的平均时间最短。**

**各种排序的稳定性，时间复杂度和空间复杂度总结：**

![八大排序复杂度](http://upload-images.jianshu.io/upload_images/1877813-52e56a535f47f086.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


### 1. 直接插入排序
- **基本思想**：将一个记录插入到已排序好的有序表中，从而得到一个新，记录数增1的有序表。即：先将序列的第1个记录看成是一个有序的子序列，然后从第2个记录逐个进行插入，直至整个序列有序为止。
- **要点**：设立哨兵，作为临时存储和判断数组边界之用。
- **稳定**：如果碰见一个和插入元素相等的，那么插入元素把想插入的元素放在相等元素的后面。所以，**相等元素的前后顺序没有改变（因为从前往后插入）**，从原无序序列出去的顺序就是排好序后的顺序，所以插入排序是稳定的。
- **时间复杂度**： ***O（n^2^）***

直接插入排序示例：

![](http://upload-images.jianshu.io/upload_images/1877813-cfb270186a2c1bee.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```C++
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
```

### 2. Shell排序
希尔排序又叫缩小增量排序，在直排基础上改进。
增量序列通常为：d = {n/2 ,n/4, n/8 .....1} 依次减小，最后必须为1。
- **基本思想**：先将整个待排序的记录序列分割成为若干子序列分别进行直接插入排序，待整个序列中的记录**“基本有序”**时，再对全体记录进行依次直接插入排序。
- **不稳定**：因为有元素交换。
- **复杂度**：取决于增量因子序列d的选取，目前还没有选取最好的增量因子序列的方法。
- **操作方法**：如下图示例。


希尔排序的示例：

![](http://upload-images.jianshu.io/upload_images/1877813-8efb47d9b5b954dc.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

非递归实现
```C++
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
```

递归实现
```C++
// dk是shell排序的增量
void shellInsertSort(int *arr, int len, int dk) {
    // 一层for 
    for (int i = dk; i < len; ++i) { // i=dk，其实是以dk为增量的子序列的第2个元素，与基本插入排序一样从第2个元素开始

        if (arr[i] < arr[i - dk]) {
            int x = arr[i]; // 哨兵
            int j = i - dk;

            while (x < arr[j] && j >= 0) { // 一定要判断j>0，因为while循环体中j会<0
                arr[j + dk] = arr[j];
                j -= dk;
            }
            // 跳出时，x >= arr[j]
            arr[j + dk] = x;
        }
    }
}

void shellSort(int *arr, int len) {
    int dk = len / 2;
    while (dk >= 1) {
        shellInsertSort(arr, len, dk);
        dk /= 2;
    }
}
```
注意：最外层for是dk..len-1，相当于从arr[dk]开始，把后面的元素都进行了插入排序，比如上图一趟排序的结果，增量为3，先插入55，再插入4，而不是先完成 13, 55, 38, 76 这4个数的排序。如果想一次完成，需要写2个for，其实参加排序的数是一样的。
```C++
void shellInsertSort(int *arr, int len, int dk) {
    // 两层for
    for (int k = 0; k < dk; ++k) { // 每次完成从arr[k]开始的增量序列
        for (int i = k + dk; i < len; i += dk) { // 第2个元素开始 
            // 内部不变
            if (arr[i] < arr[i - dk]) {
                int x = arr[i]; // 哨兵
                int j = i - dk;
                while (x < arr[j] && j >= 0) { // 一定要判断j>0，因为while循环体中j会<0
                    arr[j + dk] = arr[j];
                    j -= dk;
                }
                // 跳出时，x >= arr[j]
                arr[j + dk] = x;
            }
        }
    }
}
```

### 3. 直接选择排序
最小值放前思想
```C++
// 选择排序
void selectSort(int *arr, int len) {
    for (int i = 0; i < len - 1; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (arr[i] > arr[j]) swap(arr[i], arr[j]); // 最小值放前思想
        }
    }
}
```

### 4. 堆排序
堆排序是一种树形选择排序，是对直接选择排序的有效改进。
- **基本思想**：将序列调整成大顶堆，然后 ```swap(arr[0], arr[len-1])```，最大值放后的思想，然后再将剩下的序列调整成大顶堆，再将次大值放后……
- **误区**：依次从 0..len-2 到 len-1 建立小顶堆，这是一种思路，但是这样去掉的是堆顶，直接就破坏了堆结构，而大顶堆去掉的是堆尾，不会破坏堆结构。


![大顶 小顶](http://upload-images.jianshu.io/upload_images/1877813-fa1da89853fe1c59.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


![构建小顶堆](http://upload-images.jianshu.io/upload_images/1877813-211a6d71917996ee.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


![输出堆顶后调整堆](http://upload-images.jianshu.io/upload_images/1877813-be69b7a344feb299.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


```C++
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

// 4.堆排序
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
```
```C++
          49   38   65   97   76   13   27   49   55    4
build     97   76   65   55   49   13   27   49   38    4
len=10     4   76   65   55   49   13   27   49   38   97
len=9     38   55   65   49   49   13   27    4   76
len=8      4   55   38   49   49   13   27   65
len=7     27   49   38    4   49   13   55
len=6     13   49   38    4   27   49
len=5     13   27   38    4   49
len=4      4   27   13   38
len=3     13    4   27
len=2      4   13
    4   13   27   38   49   49   55   65   76   97
```


### 5. 冒泡排序
最大值放后思想
```C++
// 冒泡排序
void bubbleSort(int *arr, int len) {
    for (int i = 0; i < len - 1; ++i) {
        for (int j = 0; j < len - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]); // 最大值放后思想
        }
    }
}
```

### 6. 快速排序
**基本思想**：
1. 选择一个基准元素,通常选择第一个元素或者最后一个元素,
2. 通过一趟排序将序列分成两部分，一部分比基准值小，另一部分比基准值大。
3. 此时基准元素正好在其排好序后的正确位置（第k小数）
4. 然后分别对这两部分记录用同样的方法继续进行排序，直到整个序列有序。

寻找 pivot 的位置很关键。
```C++
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
```
### 7. 归并排序
- **基本思想**：归并（Merge）排序法是将两个（或两个以上）有序表合并成一个新的有序表，即把待排序序列分为若干个子序列，每个子序列是有序的。然后再把有序子序列合并为整体有序序列。

归并排序示例：

![](http://upload-images.jianshu.io/upload_images/1877813-1366dba764df2ca2.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```C++
void merge(int *arr, int low, int mid, int high) {
    int tmp[high - low + 1]; // 暂存数据

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
```

### 8. 基数排序
- **基本思想**：把数据分组，放在一个个的桶中，然后对每个桶里面的在进行排序。  
- **操作方法**：例如要对大小为 [1..1000] 范围内的 n 个整数 A[1..n] 排序：
  1. 把桶设为大小为10的范围，具体而言，设集合 B[1] 存储 [1..10] 的整数，集合B[2] 存储 [11..20] 的整数……总共100个桶
  2. 对 A[1..n] 从头到尾扫描一遍，把每个 A[i] 放入对应的桶 B[j] 中
  3. 再对这100个桶中每个桶里的数字排序，可用任何排序方法
  4. 依次输出每个桶里面的数字。

- **复杂度：**
假设有n个数字，m个桶，如果数字是平均分布的，每个桶里面平均有n/m个数字
如果对每个桶中的数字采用快速排序，那么整个算法的复杂度是：
  O(n + m × **n/m×log(n/m)**)   =   O(n + n(log(n/m)))  
从上式看出，当 m 接近 n 的时候，桶排序复杂度接近O(n)  
  当然，以上复杂度的计算是基于输入的n个数字是平均分布这个假设的。**这个假设是很强的  ，实际应用中效果并没有这么好。如果所有的数字都落在同一个桶中，那就退化成一般的排序了。**
- **特点**：非常耗费空间，如果能实现每个桶刚好1个数字，这是数列就已经有序了。

```C++
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
```
```C++
 83   86   77   15   93   35   86   92   49   21   62   27   90   59   63   26   40   26   72   36

元素进桶
10,19:    15
20,29:    21   27   26   26
30,39:    35   36
40,49:    49   40
50,59:    59
60,69:    62   63
70,79:    77   72
80,89:    83   86   86
90,99:    93   92   90

桶内排序
10,19:    15
20,29:    21   26   26   27
30,39:    35   36
40,49:    40   49
50,59:    59
60,69:    62   63
70,79:    72   77
80,89:    83   86   86
90,99:    90   92   93

   15   21   26   26   27   35   36   40   49   59   62   63   72   77   83   86   86   90   92   93
```
