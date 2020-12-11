# 最小k个数

输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4。



这是一篇针对初学者的题解。共用三种方法解决。
知识点：数组，堆，快排
难度：二星

------

# 题解

题目抽象：求给定数组的topK小问题。

## 方法一：排序

直接排序，然后去前k小数据。

### 代码

```
class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> ret;
        if (k==0 || k>input.size()) return ret;
        sort(input.begin(), input.end());
        return vector<int>({input.begin(), input.begin()+k});   
    }
};
```

时间复杂度：O(nlongn)
空间复杂度：O(1)

## 方法二：堆排序

建立一个容量为k的大根堆的优先队列。遍历一遍元素，如果队列大小<k,就直接入队，否则，让当前元素与队顶元素相比，如果队顶元素大，则出队，将当前元素入队

### 代码

```
class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> ret;
        if (k==0 || k > input.size()) return ret;
        priority_queue<int, vector<int>> pq;
        for (const int val : input) {
            if (pq.size() < k) {
                pq.push(val);
            }
            else {
                if (val < pq.top()) {
                    pq.pop();
                    pq.push(val);
                }

            }
        }

        while (!pq.empty()) {
            ret.push_back(pq.top());
            pq.pop();
        }
        return ret;
    }
};
```

时间复杂度：O(nlongk), 插入容量为k的大根堆时间复杂度为O(longk), 一共遍历n个元素
空间复杂度：O(k)

## 方法三：快排思想

对数组[l, r]一次快排partition过程可得到，[l, p), p, [p+1, r)三个区间,[l,p)为小于等于p的值
[p+1,r)为大于等于p的值。
然后再判断p，利用二分法

1. 如果[l,p), p，也就是p+1个元素（因为下标从0开始），如果p+1 == k, 找到答案
   2。 如果p+1 < k, 说明答案在[p+1, r)区间内，
   3， 如果p+1 > k , 说明答案在[l, p)内 

### 代码

```
class Solution {
public:
    int partition(vector<int> &input, int l, int r) {
        int pivot = input[r-1];
        int i = l;
        for (int j=l; j<r-1; ++j) {
            if (input[j] < pivot) {
                swap(input[i++], input[j]);
            }
        }
        swap(input[i], input[r-1]);
        return i;

    }
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> ret;
        if (k==0 || k > input.size()) return ret;
         int l = 0, r = input.size();
        while (l < r) {
            int p = partition(input, l, r);
            if (p+1 == k) {
                return vector<int>({input.begin(), input.begin()+k});
            }
            if (p+1 < k) {
                l = p + 1;
            }   
            else {
                r = p;
            }

        }
        return ret;
    }
};
```

时间复杂度：平均时间复杂度为O(n),每次partition的大小为`n+n/2+n/4+... = 2n`,最坏时间复杂度为O(n^2), 因为每次partition都只减少一个元素
空间复杂度：O(1)