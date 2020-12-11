# 合并链表

将两个有序的链表合并为一个新链表，要求新的链表是通过拼接两个链表的节点来生成的，且合并后新链表依然有序。

```
示例1
输入

复制
{1},{2}
返回值

复制
{1,2}
示例2
输入

复制
{2},{1}
返回值

复制
{1,2}
```



```c
/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 * };
 */

class Solution {
public:
    /**
     * 
     * @param l1 ListNode类 
     * @param l2 ListNode类 
     * @return ListNode类
     */
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == nullptr){
            return l2;
        } else if (l2 == nullptr) {
            return l1;
        }
        ListNode* ll1 = l1;
        ListNode* ll2 = l2;
        ListNode* res = nullptr;
        if(ll1->val < ll2->val){
            res = ll1;
            ll1 = ll1->next;
        } else {
            res = ll2;
            ll2 = ll2->next;
        }
        ListNode* head = res;
        while(ll1!=nullptr && ll2 != nullptr){
            if(ll1->val < ll2->val){
                res->next = ll1;
                ll1 = ll1->next;
            } else {
                res->next = ll2;
                ll2 = ll2->next;
            }
            res = res->next;
        }
        if(ll1 != nullptr){
            res->next = ll1;
        } else if (ll2 != nullptr) {
            res->next = ll2;
        }
        return head;
        // write code here
    }
};
```

