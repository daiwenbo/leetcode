/*
A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.
Return a deep copy of the list.
*/
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {//first insert a copy of each node after each node
        if (!head){
            return head;
        }
        
        //first insert a copy of each node after each node
        RandomListNode* x = head;
        while (x){
            //new Node
            RandomListNode* newNode = new RandomListNode(x->label);
            newNode->next = x->next;
            x->next = newNode;
            x = newNode->next;
        }
        
        //now reconstruct the random link for the copied list
        x = head;
        while(x){
            if (!x->random){
                x->next->random = NULL;
            }else{
                x->next->random = x->random->next;
            }
            x = x->next->next;
        }
        
        //break the original and copied list
        RandomListNode* copiedListHead = head->next; //store the head of copied list
        x = head;
        RandomListNode* y = copiedListHead;
        
        RandomListNode* nextOriginal;
        RandomListNode* nextCopied;
        while(x){
            nextOriginal = x->next->next;
            if (!nextOriginal){
                nextCopied = NULL;
            }else{
                nextCopied = nextOriginal->next;
            }
            
            x->next = nextOriginal;
            y->next = nextCopied;
            
            x = x->next;
            y = y->next;
        }
        
        return copiedListHead;
    }
};
