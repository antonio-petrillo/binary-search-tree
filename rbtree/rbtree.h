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

// create tree function

void rbError(char* message);
rbTree makeRbTree();
rbNodePtr makeRbNode(int value, rbNodePtr parent);
rbNodePtr dropRbTree(rbTree tree);

// queue rb node function for breadth visit

void makeRbQueue(rbQueue* q);
rbQueueNodePtr makeRbQueueNode(rbNodePtr value);
void enqueue(rbQueue* q, rbNodePtr value);
rbNodePtr dequeue(rbQueue* q);

// visit (print) function

void inOrderRbVisit(rbTree tree);
void preOrderRbVisit(rbTree tree);
void postOrderRbVisit(rbTree tree);
void breadthRbVisit(rbTree tree);

// rotate function

rbNodePtr leftRotateRb(rbNodePtr root);
rbNodePtr rightRotateRb(rbNodePtr root);

// inert node function

rbTree insertRb(rbTree tree, int value);
rbNodePtr insertRb_helper(rbNodePtr root, int value, rbNodePtr parent);
rbNodePtr insertRbFixupLeft(rbNodePtr root);

// insert fixup left

int typeOfInsertFixupLeft(rbNodePtr root);
rbNodePtr insertRbFixupLeft1(rbNodePtr root);
rbNodePtr insertRbFixupLeft2(rbNodePtr root);
rbNodePtr insertRbFixupLeft3(rbNodePtr root);
rbNodePtr insertRbFixupRight(rbNodePtr root);

// insert fixup right 

int typeOfInsertFixupRight(rbNodePtr root);
rbNodePtr insertRbFixupRight1(rbNodePtr root);
rbNodePtr insertRbFixupRight2(rbNodePtr root);
rbNodePtr insertRbFixupRight3(rbNodePtr root);

// delete node function

rbTree deleteRbNode(rbTree tree, int key);
rbNodePtr deleteRbNode_helper(rbNodePtr root, int key);

// delete fixup (internal node)

rbNodePtr deleteRbFixupLeft(rbNodePtr root);
rbNodePtr deleteRbFixupRight(rbNodePtr root);

//delete fixup (root)

rbNodePtr deleteRbRootFixupLeft(rbNodePtr root);
rbNodePtr deleteRbRootFixupRight(rbNodePtr root);


rbNodePtr deleteRbNodeWithAddr_helper(rbNodePtr root, rbNodePtr key);

// delete fixup left (internal node)

int typeOfDeleteFixupLeft(rbNodePtr root);
rbNodePtr deleteRbFixupLeft1(rbNodePtr root);
rbNodePtr deleteRbFixupLeft2(rbNodePtr root);
rbNodePtr deleteRbFixupLeft3(rbNodePtr root);
rbNodePtr deleteRbFixupLeft4(rbNodePtr root);

// delete fixup left (root)

int typeOfDeleteRootFixupLeft(rbNodePtr root);
rbNodePtr deleteRbRootFixupLeft1(rbNodePtr root);
rbNodePtr deleteRbRootFixupLeft2(rbNodePtr root);
rbNodePtr deleteRbRootFixupLeft3(rbNodePtr root);
rbNodePtr deleteRbRootFixupLeft4(rbNodePtr root);
rbNodePtr deleteRbRootFixupLeft5(rbNodePtr root);
rbNodePtr deleteRbRootFixupLeft6(rbNodePtr root);
rbNodePtr deleteRbRootFixupLeft7(rbNodePtr root);
rbNodePtr deleteRbRootFixupLeft8(rbNodePtr root);

// delete fixup right (internal node)

int typeOfDeleteFixupRight(rbNodePtr root);
rbNodePtr deleteRbFixupRight1(rbNodePtr root);
rbNodePtr deleteRbFixupRight2(rbNodePtr root);
rbNodePtr deleteRbFixupRight3(rbNodePtr root);
rbNodePtr deleteRbFixupRight4(rbNodePtr root);

// delete fixup left (root)

int typeOfDeleteRootFixupRight(rbNodePtr root);
rbNodePtr deleteRbRootFixupRight1(rbNodePtr root);
rbNodePtr deleteRbRootFixupRight2(rbNodePtr root);
rbNodePtr deleteRbRootFixupRight3(rbNodePtr root);
rbNodePtr deleteRbRootFixupRight4(rbNodePtr root);
rbNodePtr deleteRbRootFixupRight5(rbNodePtr root);
rbNodePtr deleteRbRootFixupRight6(rbNodePtr root);
rbNodePtr deleteRbRootFixupRight7(rbNodePtr root);
rbNodePtr deleteRbRootFixupRight8(rbNodePtr root);

// utility function

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