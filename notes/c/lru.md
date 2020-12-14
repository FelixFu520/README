# 设计LRU缓存结构

设计LRU缓存结构，该结构在构造时确定大小，假设大小为K，并有如下两个功能 

- set(key, value)：将记录(key, value)插入该结构 
- get(key)：返回key对应的value值 

[要求] 

1. set和get方法的时间复杂度为O(1) 
2. 某个key的set或get操作一旦发生，认为这个key的记录成了最常使用的。 
3. 当缓存的大小超过K时，移除最不经常使用的记录，即set或get最久远的。 

若opt=1，接下来两个整数x, y，表示set(x, y)
若opt=2，接下来一个整数x，表示get(x)，若x未出现过或已被移除，则返回-1
对于每个操作2，输出一个答案



https://www.nowcoder.com/practice/e3769a5f49894d49b871c09cadd13a61?tpId=191&&tqId=36124&rp=1&ru=/ta/job-code-high-algorithm&qru=/ta/job-code-high-algorithm/question-ranking

```c
#include <unordered_map>
class Solution {
    
    public:
    /**
     * lru design
     * @param operators int整型vector<vector<>> the ops
     * @param k int整型 the k
     * @return int整型vector
     */
    int capacity;//容量大小
    list<pair<int,int>> cache;//用双链表实现cache结构
    unordered_map<int,list<pair<int,int>>::iterator> map;
    int get(int key)
    {
        if(map.find(key)==map.end())
            return -1;
        auto key_value=*map[key];
        cache.erase(map[key]);//删除旧关于key的记录
        cache.push_front(key_value);//把key压入到cache的首部
        map[key]=cache.begin();//更新map里面对应key的迭代器
        return key_value.second;
    }
    void set(int key,int value)
    {
        if(map.find(key)==map.end())
        {
            if(cache.size()==capacity)
            {
                map.erase(cache.back().first);
                cache.pop_back();
            }
        }
        else
        {
            cache.erase(map[key]);
        }
        cache.push_front({key,value});
        map[key]=cache.begin();
    }
    vector<int> LRU(vector<vector<int> >& operators, int k) {
        capacity=k;
        vector<int> res;
        for(int i=0;i<operators.size();i++)
        {
            if(operators[i].size()==2)
            {
                int key=operators[i][1];
                res.push_back(get(key));
                
            }
            if(operators[i].size()==3)
            {
                int key=operators[i][1];
                int value=operators[i][2];
                set(key,value);
            }
        }
        return res;// write code here
        
    }
};
```

