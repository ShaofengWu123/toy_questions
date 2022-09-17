#include <stdio.h>

/*
给你一个链表的头节点 head 和一个整数 val ，请你删除链表中所有满足 Node.val == val 的节点，并返回 新的头节点 。
*/

/**
 * Definition for singly-linked list.
 */

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* removeElements(struct ListNode* head, int val){
    struct ListNode* cur = head;
    struct ListNode* pre = head;
    
    while(cur != NULL && head->val == val){
        head = cur->next;
        cur = head;
    }
    
    if(head == NULL){
        return head;
    }

    pre = head;
    cur = head->next;

    while(cur != NULL){
        if(cur->val == val){
            pre->next = cur->next;
        }
        else{
            pre = cur;
        }
        cur = cur->next;
    }
    return head;
}



