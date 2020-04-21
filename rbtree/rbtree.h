#ifndef RBTREE_H
#define RBTREE_H 1

typedef enum{RED, BLACK, DOUBLE_BLACK} Color;

typedef struct rb_node{
    struct rb_node* parent;
    struct rb_node* left;
    struct rb_node* right;
    int value;
    Color color;
}rbNode;

typedef rbNode* rbNodePtr;
typedef rbNodePtr rbTree;

typedef struct rb_queue_node{
    struct rb_queue_node* next;
    rbNodePtr value;
}rbQueueNode;

typedef rbQueueNode* rbQueueNodePtr;

typedef struct{
    rbQueueNodePtr head;
    rbQueueNodePtr tail;
}rbQueue;

void rbError(char* message);
rbTree makeRbTree();
rbNodePtr makeRbNode(int value, rbNodePtr parent);
rbNodePtr dropRbTree(rbTree tree);

void makeRbQueue(rbQueue* q);
rbQueueNodePtr makeRbQueueNode(rbNodePtr value);
void enqueue(rbQueue* q, rbNodePtr value);
rbNodePtr dequeue(rbQueue* q);

void inOrderRbVisit(rbTree tree);
void preOrderRbVisit(rbTree tree);
void postOrderRbVisit(rbTree tree);
void breadthRbVisit(rbTree tree);

rbNodePtr leftRotateRb(rbNodePtr root);
rbNodePtr rightRotateRb(rbNodePtr root);

rbTree insertRb(rbTree tree, int value);
rbNodePtr insertRb_helper(rbNodePtr root, int value, rbNodePtr parent);
rbNodePtr insertRbFixupLeft(rbNodePtr root);

int typeOfInsertFixupLeft(rbNodePtr root);
rbNodePtr insertRbFixupLeft1(rbNodePtr root);
rbNodePtr insertRbFixupLeft2(rbNodePtr root);
rbNodePtr insertRbFixupLeft3(rbNodePtr root);
rbNodePtr insertRbFixupRight(rbNodePtr root);

int typeOfInsertFixupRight(rbNodePtr root);
rbNodePtr insertRbFixupRight1(rbNodePtr root);
rbNodePtr insertRbFixupRight2(rbNodePtr root);
rbNodePtr insertRbFixupRight3(rbNodePtr root);

rbTree deleteRbNode(rbTree tree, int key);
rbNodePtr deleteRbNode_helper(rbNodePtr root, int key);

rbNodePtr deleteRbFixupLeft(rbNodePtr root);
rbNodePtr deleteRbFixupRight(rbNodePtr root);

rbNodePtr deleteRbNodeWithAddr_helper(rbNodePtr root, rbNodePtr key);

int typeOfDeleteFixupLeft(rbNodePtr root);
rbNodePtr deleteRbFixupLeft1(rbNodePtr root);
rbNodePtr deleteRbFixupLeft2(rbNodePtr root);
rbNodePtr deleteRbFixupLeft3(rbNodePtr root);
rbNodePtr deleteRbFixupLeft4(rbNodePtr root);

int typeOfDeleteFixupRight(rbNodePtr root);
rbNodePtr deleteRbFixupRight1(rbNodePtr root);
rbNodePtr deleteRbFixupRight2(rbNodePtr root);
rbNodePtr deleteRbFixupRight3(rbNodePtr root);
rbNodePtr deleteRbFixupRight4(rbNodePtr root);

rbNodePtr minRb(rbTree tree);
rbNodePtr maxRb(rbTree tree);

int countRbTree(rbTree root);
rbTree maxRbTree(rbTree root);
rbTree minRbTree(rbTree root);
int isEmptyRbTree(rbTree root);
rbTree searchRbTree(rbTree root, int value);
rbTree unionRbTree(rbTree tree1, rbTree tree2);
rbTree intersectRbTree(rbTree tree1, rbTree tree2);
rbTree differenceRbTree(rbTree tree1, rbTree tree2);
void unionRbTree_rc(rbTree tree1, rbTree tree2, rbTree* tree3);
void intersectRbTree_rc(rbTree tree1, rbTree tree2, rbTree* tree3);
void differenceRbTree_rc(rbTree tree2, rbTree* tree3);
rbTree copyRbTree(rbTree tree);
void copyRbTree_rec(rbTree tree, rbTree* copy);
void removeDuplicatesRbTree(rbTree* tree);
rbNodePtr successorRbTree(rbTree tree, int value);
void successorRbTree_rec(rbTree root, int value, rbTree* candidate);
rbNodePtr predeccessorRbTree(rbTree tree, int value);
void predecessorRbTree_rec(rbTree root, int value, rbTree* candidate);

#endif