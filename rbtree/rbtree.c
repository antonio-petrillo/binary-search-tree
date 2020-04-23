#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

void rbError(char* message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

rbTree makeRbTree(){
    return NULL;
}

rbNodePtr makeRbNode(int value, rbNodePtr parent){
    rbNodePtr newnode = (rbNodePtr) malloc(sizeof(rbNode));
    if(!newnode) rbError("error in function makeRbNode");
    newnode->left = newnode->right = NULL;
    newnode->parent = parent;
    newnode->value = value;
    newnode->color = RED;
    return newnode;
}

rbNodePtr dropRbTree(rbTree tree){
    if(tree){
        tree->left = dropRbTree(tree->left);
        tree->right = dropRbTree(tree->right);
        free(tree);
    }
    return NULL;
}

void inOrderRbVisit(rbTree tree){
    if(tree){
        inOrderRbVisit(tree->left);
        printf("node's value: %d, node's color: %s\n", tree->value, (tree->color == RED) ? "RED" : "BLACK");
        inOrderRbVisit(tree->right);
    }
    return ;
}

void preOrderRbVisit(rbTree tree){
  if(!tree) return;
  printf("node's value: %d, node's color: %s\n", tree->value, (tree->color == RED) ? "RED" : "BLACK");
  preOrderRbVisit(tree->left);
  preOrderRbVisit(tree->right);
  return;
}

void postOrderRbVisit(rbTree tree){
  if(!tree) return;
  postOrderRbVisit(tree->left);
  postOrderRbVisit(tree->right);
  printf("node's value: %d, node's color: %s\n", tree->value, (tree->color == RED) ? "RED" : "BLACK");
  return;
}

void makeRbQueue(rbQueue* q){
    q->head = q->tail = NULL;
    return;
}

rbQueueNodePtr makeRbQueueNode(rbNodePtr value){
    rbQueueNodePtr newnode = (rbQueueNodePtr) malloc(sizeof(rbQueueNode));
    if(!newnode) rbError("error in function makeRbQueueNode");
    newnode->value = value;
    newnode->next = NULL;
}

void enqueue(rbQueue* q, rbNodePtr value){
    if(!q->tail) q->head = q->tail = makeRbQueueNode(value);
    else{
        rbQueueNodePtr newnode = makeRbQueueNode(value);
        q->tail->next = newnode;
        q->tail = newnode;
    }
    return;
}

rbNodePtr dequeue(rbQueue* q){
    rbNodePtr retNode = NULL;
    if(q->head){
        retNode = q->head->value;
        rbQueueNodePtr tmp = q->head;
        if(q->head == q->tail) q->head = q->tail = NULL;
        else q->head = q->head->next;
        tmp->value = NULL;
        free(tmp);
    }
    return retNode;
}

void breadthRbVisit(rbTree tree){
    rbQueue q;
    makeRbQueue(&q);
    if(tree) enqueue(&q, tree);
    rbNodePtr iter = NULL;
    while(q.head){
        iter = dequeue(&q);
        printf("node's value: %d, node's color: %s\n", iter->value, (iter->color == RED) ? "RED" : ((iter->color == DOUBLE_BLACK) ? "DOUBLE BLACK" : "BLACK"));
        if(iter->left){
            enqueue(&q, iter->left);
            //printf("(%d) left's child -> (%d)\n", iter->value, iter->left->value);
        } 
        if(iter->right){
            enqueue(&q, iter->right);
            //printf("(%d) right's child -> (%d)\n", iter->value, iter->right->value);
        }   
     }
    return;
}

rbTree insertRb(rbTree tree, int value){
    tree = insertRb_helper(tree, value, NULL);
    tree->color = BLACK;
    return tree;
}

rbNodePtr insertRb_helper(rbNodePtr root, int value, rbNodePtr parent){
    if(!root) root = makeRbNode(value, parent);
    else if(root->value > value){
        root->left = insertRb_helper(root->left, value, root);
        root = insertRbFixupLeft(root);
    }else/* if(root->value <= value)*/{
        root->right = insertRb_helper(root->right, value, root);
        root = insertRbFixupRight(root);
    }
    return root;
}

rbNodePtr insertRbFixupLeft(rbNodePtr root){
    switch (typeOfInsertFixupLeft(root)){
    case 1:
        root = insertRbFixupLeft1(root);
        break;
    case 2:
        root = insertRbFixupLeft2(root);
        break;
    case 3:
        root = insertRbFixupLeft3(root);
        break;
    default:
        break;
    }
    return root;
}

int typeOfInsertFixupLeft(rbNodePtr root){
    int violation = 0;
    if(root->right && root->right->color == RED){
        if(root->left && root->left->color == RED){
            if(root->left->left && root->left->left->color == RED) violation = 1;
            if(root->left->right && root->left->right->color == RED) violation = 1;
        }
    }else{
        if(root->left && root->left->color == RED){
            if(root->left->right && root->left->right->color == RED) violation = 2;
            else if(root->left->left && root->left->left->color == RED) violation = 3;
        }
    }
    return violation;
}

rbNodePtr insertRbFixupLeft1(rbNodePtr root){
    root->left->color = root->right->color = BLACK;
    root->color = RED;
    return root;
}

rbNodePtr insertRbFixupLeft2(rbNodePtr root){
    root->left = rightRotateRb(root->left);
    root = insertRbFixupLeft3(root);
    return root;
}

rbNodePtr insertRbFixupLeft3(rbNodePtr root){
    root = leftRotateRb(root);
    root->right->color = RED;
    root->color = BLACK;
    return root;
}

rbNodePtr insertRbFixupRight(rbNodePtr root){
    switch (typeOfInsertFixupRight(root)){
    case 1:
        root = insertRbFixupRight1(root);
        break;
    case 2:
        root = insertRbFixupRight2(root);
        break;
    case 3:
        root = insertRbFixupRight3(root);
        break;
    default:
        break;
    }
    return root;
}

int typeOfInsertFixupRight(rbNodePtr root){
        int violation = 0;
    if(root->left && root->left->color == RED){
        if(root->right && root->right->color == RED){
            if(root->right->left && root->right->left->color == RED) violation = 1;
            if(root->right->right && root->right->right->color == RED) violation = 1;
        }
    }else{
        if(root->right && root->right->color == RED){
            if(root->right->left && root->right->left->color == RED) violation = 2;
            else if(root->right->left && root->right->right->color == RED) violation = 3;
        }
    }
    return violation;
}

rbNodePtr insertRbFixupRight1(rbNodePtr root){
    root->left->color = root->right->color = BLACK;
    root->color = RED;
    return root;
}

rbNodePtr insertRbFixupRight2(rbNodePtr root){
    root->right = leftRotateRb(root->right);
    root = insertRbFixupRight3(root);
    return root;
}

rbNodePtr insertRbFixupRight3(rbNodePtr root){
    root = rightRotateRb(root);
    root->left->color = RED;
    root->color = BLACK;
    return root;
}

rbNodePtr leftRotateRb(rbNodePtr root){
    rbNodePtr newroot = root;
    if(root->left){
        newroot = root->left;
        newroot->parent = root->parent;
        root->left = newroot->right;
        if(root->left) root->left->parent = root;
        newroot->right = root;
        root->parent = newroot;
    }
    return newroot;
}

rbNodePtr rightRotateRb(rbNodePtr root){
    rbNodePtr newroot = root;
    if(root->right){
        newroot = root->right;
        newroot->parent = root->parent;
        root->right = newroot->left;
        if(root->right) root->right->parent = root;
        newroot->left = root;
        root->parent = newroot;
    }
    return newroot;
}

rbTree deleteRbNode(rbTree tree, int key){
    int select = -1;
    if(tree){
        if(tree->value > key){
            tree->left = deleteRbNode_helper(tree->left, key);
            tree = deleteRbFixupLeft(tree);
            select = 0;
        }else if(tree->value < key){
            tree->right = deleteRbNode_helper(tree->right, key);
            tree = deleteRbFixupRight(tree);
            select = 1;
        }else{
            if(!(tree->left && tree->right)){ // one child or no child
                rbNodePtr tmp = tree;
                if(tree->left){
                    tree = tree->left;
                    select = 0;
                } 
                else {
                    tree = tree->right;
                    select = 1;
                }
                if(tree){// at least one child
                    if(tmp->color == RED || tree->color == RED)//the child XOR parent are RED
                        tree->color = BLACK;
                    else// both child and parent are BLACK
                        tree->color = DOUBLE_BLACK;
                }else{
                    if(tmp->color == BLACK){
                        if(tmp->parent)
                            tmp->parent->color = DOUBLE_BLACK;
                    }
                }
                free(tmp);
            }else{
                rbNodePtr min = minRb(tree->right);
                tree->value = min->value;
                tree->right = deleteRbNode_helper(tree->right, min->value);
                tree = deleteRbFixupRight(tree);
                select = 1;
            }
        }
    }
    /* else 
    *    node not present into the tree
    *    return with no violation
    */
    if(select == 0){
        tree = deleteRbRootFixupLeft(tree);
    }else if(select == 1){
        tree =  deleteRbRootFixupRight(tree);
    }
    if(tree) tree->color = BLACK;
    return tree;
}

rbNodePtr deleteRbNode_helper(rbNodePtr root, int key){
    if(root){
        if(root->value > key){
            root->left = deleteRbNode_helper(root->left, key);
            root = deleteRbFixupLeft(root);
        }else if(root->value < key){
            root->right = deleteRbNode_helper(root->right, key);
            root = deleteRbFixupRight(root);
        }else{
            if(!(root->left && root->right)){ // one child or no child
                rbNodePtr tmp = root;
                if(root->left)
                    root = root->left;
                else
                    root = root->right;
                if(root){// at least one child
                    root->parent = tmp->parent;
                    if(tmp->color == RED || root->color == RED)//the child XOR parent are RED
                        root->color = BLACK;
                    else// both child and parent are BLACK
                        root->color = DOUBLE_BLACK;
                }else{//no child
                    if(tmp->color == BLACK){
                        if(tmp->parent)
                            tmp->parent->color = DOUBLE_BLACK;
                    }/*
                    * delete of a RED leaf, no violation in this case
                    */
                }
                free(tmp);
            }else{
                rbNodePtr min = minRb(root->right);
                root->value = min->value;
                root->right = deleteRbNode_helper(root->right, min->value);
                root = deleteRbFixupRight(root);
            }
        }
    }
    /* else 
    *    node not present into the tree
    *    return with no violation
    */
   return root;
}

rbNodePtr deleteRbRootFixupLeft(rbNodePtr root){
    switch (typeOfDeleteRootFixupLeft(root)){
    case 1:
        root = deleteRbRootFixupLeft1(root);
        break;
    case 2:
        root = deleteRbRootFixupLeft2(root);
        break;
    case 3:
        root = deleteRbRootFixupLeft3(root);
        break;
    case 4:
        root = deleteRbRootFixupLeft4(root);
        break;
    case 5:
        root = deleteRbRootFixupLeft5(root);
        break;
    case 6:
        root = deleteRbRootFixupLeft6(root);
        break;
    case 7:
        root = deleteRbRootFixupLeft7(root);
        break;
    default:
        // 0 no vioaltion
        break;
    }
    return root;
}

rbNodePtr deleteRbRootFixupRight(rbNodePtr root){
    switch (typeOfDeleteRootFixupRight(root)){
    case 1:
        root = deleteRbRootFixupRight1(root);
        break;
    case 2:
        root = deleteRbRootFixupRight2(root);
        break;
    case 3:
        root = deleteRbRootFixupRight3(root);
        break;
    case 4:
        root = deleteRbRootFixupRight4(root);
        break;
    case 5:
        root = deleteRbRootFixupRight5(root);
        break;
    case 6:
        root = deleteRbRootFixupRight6(root);
        break;
    case 7:
        root = deleteRbRootFixupRight7(root);
        break;
    default:
        // 0 no vioaltion
        break;
    }
    return root;
}


int typeOfDeleteRootFixupLeft(rbNodePtr root){
    int violation = 0;
    if(root){
        if(root->color == DOUBLE_BLACK){
            if(root->right && root->right->color == BLACK){
                violation = 1;
                if(root->right->left && root->right->left->color == RED) violation = 2;
                else if(root->right->right && root->right->right->color == RED) violation = 3;
            }else if(root->right && root->right->color == RED){
                if(root->right->right && root->right->right->color == BLACK){
                    if(root->right->left && root->right->left->color == BLACK){
                        violation = 4;
                        if((root->right->left->left && root->right->left->left->color == RED) && (!(root->right->left->right)))
                            violation = 5;
                        else if((root->right->left->right && root->right->left->right->color == RED) && (!(root->right->left->left)))
                            violation = 6;
                        else if((root->right->left->left && root->right->left->left->color == RED) && (root->right->left->right && root->right->left->right->color == RED))
                            violation = 7;
                    }
                }
            }
        }
    }
    return violation;
}

rbNodePtr deleteRbRootFixupLeft1(rbNodePtr root){
    root->right->color == RED;
    root->color == BLACK;
    return root;
}

rbNodePtr deleteRbRootFixupLeft2(rbNodePtr root){
    root->right = leftRotateRb(root->right);
    root->right->color = BLACK;
    root->right->right->color = RED;
    root = deleteRbRootFixupLeft3(root);
    return root;
}

rbNodePtr deleteRbRootFixupLeft3(rbNodePtr root){
    root = rightRotateRb(root);
    root->left->color = BLACK;
    root->color = BLACK;
    root->right->color = BLACK;
    return root;
}

rbNodePtr deleteRbRootFixupLeft4(rbNodePtr root){
    root = rightRotateRb(root);
    root->color = BLACK;
    root->left->color = BLACK;
    root->left->right->color = RED;
    return root;
}

rbNodePtr deleteRbRootFixupLeft5(rbNodePtr root){
    root->color = BLACK;
    root = rightRotateRb(root);
    root->color = BLACK;
    root->left->right = leftRotateRb(root->left->right);
    root->left = rightRotateRb(root->left);
    return root;
}

rbNodePtr deleteRbRootFixupLeft6(rbNodePtr root){
    root->color = RED;
    root = rightRotateRb(root);
    root->left = rightRotateRb(root->left);
    return root;
}

rbNodePtr deleteRbRootFixupLeft7(rbNodePtr root){
    root->color = BLACK;
    root = rightRotateRb(root);
    root->left->right = leftRotateRb(root->left->right);
    root->left = rightRotateRb(root->left);
    root->color = BLACK; 
    return root;
}

int typeOfDeleteRootFixupRight(rbNodePtr root){
    int violation = 0;
    if(root){
        if(root->color == DOUBLE_BLACK){
            if(root->left && root->left->color == BLACK){
                violation = 1;
                if(root->left->right && root->left->right->color == RED) violation = 2;
                else if(root->left->left && root->left->left->color == RED){
                    violation = 3;
                    printf("\nentro qua? \n\n");
                } 
            }else if(root->left && root->left->color == RED){
                if(root->left->left && root->left->left->color == BLACK){
                    if(root->left->right && root->left->right->color == BLACK){
                        violation = 4;
                        if((root->left->right->right && root->left->right->right->color == RED) && (!(root->left->right->left)))
                            violation = 5;
                        else if((root->left->right->left && root->left->right->left->color == RED) && (!(root->left->right->right)))
                            violation = 6;
                        else if((root->left->right->left && root->left->right->left->color == RED) && (root->left->right->right && root->left->right->right->color == RED))
                            violation = 7;
                    }
                }
            }
        }
    }
    return violation;
}

rbNodePtr deleteRbRootFixupRight1(rbNodePtr root){
    root->left->color == RED;
    root->color == BLACK;
    return root;
}

rbNodePtr deleteRbRootFixupRight2(rbNodePtr root){
    root->left = rightRotateRb(root->left);
    root->left->color = BLACK;
    root->left->left->color = RED;
    return root;
}

rbNodePtr deleteRbRootFixupRight3(rbNodePtr root){
    root = leftRotateRb(root);
    root->left->color = BLACK;
    root->color = BLACK;
    root->right->color = BLACK;
    return root;
}

rbNodePtr deleteRbRootFixupRight4(rbNodePtr root){
    root = leftRotateRb(root);
    root->color = BLACK;
    root->right->color = BLACK;
    root->right->left->color = RED;
    return root;
}

rbNodePtr deleteRbRootFixupRight5(rbNodePtr root){
    root->color = BLACK;
    root = leftRotateRb(root);
    root->color = BLACK;
    root->right->left = rightRotateRb(root->right->left);
    root->right = leftRotateRb(root->right);
    return root;
}

rbNodePtr deleteRbRootFixupRight6(rbNodePtr root){
    root->color = RED;
    root = leftRotateRb(root);
    root->right = leftRotateRb(root->right);
    return root;
}

rbNodePtr deleteRbRootFixupRight7(rbNodePtr root){
    root->color = BLACK;
    root = leftRotateRb(root);
    root->right->left = rightRotateRb(root->right->left);
    root->right = leftRotateRb(root->right); 
    root->color = BLACK;
    return root;
}

rbNodePtr minRb(rbTree tree){
    if(tree){
        if(tree->left) return minRb(tree->left);
        else return tree;
    }
    return NULL;
}

rbNodePtr maxRb(rbTree tree){
    if(tree){
        if(tree->right) return maxRb(tree->right);
        else return tree;
    }
    return NULL;
}

rbNodePtr deleteRbFixupLeft(rbNodePtr root){
    switch (typeOfDeleteFixupLeft(root)){
    case 1:
        root = deleteRbFixupLeft1(root);
        break;
    case 2:
        root = deleteRbFixupLeft2(root);
        break;
    case 3:
        root = deleteRbFixupLeft3(root);
        break;
    case 4:
        root = deleteRbFixupLeft4(root);
        break;
    default:
        //no violation
        break;
    }
    return root;
}

rbNodePtr deleteRbFixupRight(rbNodePtr root){
    switch (typeOfDeleteFixupLeft(root)){
    case 1:
        root = deleteRbFixupRight1(root);
        break;
    case 2:
        root = deleteRbFixupRight2(root);
        break;
    case 3:
        root = deleteRbFixupRight3(root);
        break;
    case 4:
        root = deleteRbFixupRight4(root);
        break;
    default:
        //no violation
        break;
    }
    return root;
}

rbNodePtr deleteRbNodeWithAddr_helper(rbNodePtr root, rbNodePtr key){
    if(root == key){//this node cannot have 2 children
        rbNodePtr tmp = root;
        if(root->left) root = root->left;
        else root = root->right;
        if(root){// at least one child
            if(tmp->color == RED || root->color == RED)//the child XOR parent are RED
                root->color = BLACK;
            else// both child and parent are BLACK
                root->color = DOUBLE_BLACK;
        }else{//no child
            if(tmp->color == BLACK){
                if(tmp->parent)
                    tmp->parent->color = DOUBLE_BLACK;
            }/*
            * delete of a RED leaf, no violation in this case
            */
        }
        free(tmp);
    }else if(root->value > key->value){
        root->left = deleteRbNodeWithAddr_helper(root->left, key);
        root = deleteRbFixupLeft(root);
    }else{//root->value <= key->value && root != key
        root->right = deleteRbNodeWithAddr_helper(root->right, key);
        root = deleteRbFixupRight(root);
    }
    return root;
}

int typeOfDeleteFixupLeft(rbNodePtr root){
    int violation = 0;
    if(root->left && root->left->color == DOUBLE_BLACK){
        if(root->right && root->right->color == BLACK){
            if(root->right->right && root->right->right->color == RED) violation = 1;
            else if(((root->right->right && root->right->right->color == BLACK) || !(root->right->right)) && (root->right->left && root->right->left->color == RED)) violation = 2;
            else{
                if(((root->right->right && root->right->right->color == BLACK) || !(root->right->right)) && ((root->right->left && root->right->left->color == BLACK) || !(root->right->left)))
                    violation = 3;
            }
        }else if(root->right && root->right->color == RED) violation = 4;
    }
    return violation;
}

int typeOfDeleteFixupRight(rbNodePtr root){
    int violation = 0;
    if(root->right && root->right->color == DOUBLE_BLACK){
        if(root->left && root->left->color == BLACK){
            if(root->left->left && root->left->left->color == RED) violation = 1;
            else if(((root->left->left && root->left->left->color == BLACK) || !(root->left->left)) && (root->left->right && root->left->right->color == RED)) violation = 2;
            else{
                if(((root->left->left && root->left->left->color == BLACK) || !(root->left->left)) && ((root->left->right && root->left->right->color == BLACK) || !(root->left->right)))
                    violation = 3;
            }
        }else if(root->left && root->left->color == RED) violation = 4;
    }
    return violation;
}

rbNodePtr deleteRbFixupLeft1(rbNodePtr root){
    root->right->color = root->color;
    root->color = BLACK;
    root->left->color = BLACK;//delete the double black
    root->right->right->color = BLACK;
    root = rightRotateRb(root);
    return root;
}

rbNodePtr deleteRbFixupLeft2(rbNodePtr root){
    root->right->color = RED;
    root->right->left->color = BLACK;
    root->right = leftRotateRb(root->right);
    root = deleteRbFixupLeft1(root);
    return root;
}

rbNodePtr deleteRbFixupLeft3(rbNodePtr root){
    root->right->color = RED;
    root->color = DOUBLE_BLACK;
    return root;
}

rbNodePtr deleteRbFixupLeft4(rbNodePtr root){
    root->color = RED;
    root->right->color = BLACK;
    root = rightRotateRb(root);
    root->left = deleteRbFixupLeft(root->left);
    return root;
}

rbNodePtr deleteRbFixupRight1(rbNodePtr root){
    root->left->color = root->color;
    root->color = BLACK;
    root->left->left->color = BLACK;
    root->right->color = BLACK;
    root = leftRotateRb(root);
    return root;
}

rbNodePtr deleteRbFixupRight2(rbNodePtr root){
    root->left->right->color = BLACK;
    root->left->color = RED;
    root->left = rightRotateRb(root->left);
    root = deleteRbFixupRight1(root);
    return root;
}

rbNodePtr deleteRbFixupRight3(rbNodePtr root){
    root->right->color = RED;
    root->left->color = BLACK;
    root->color = DOUBLE_BLACK;
    return root;
}

rbNodePtr deleteRbFixupRight4(rbNodePtr root){
    root->color = RED;
    root->left->color = BLACK;
    root = leftRotateRb(root);
    root->right = deleteRbFixupRight(root->right);
    return root;
}

int countRbTree(rbTree root){
    if(root) return countRbTree(root->left) + countRbTree(root->right) + 1;
    return 0;
}

int isEmptyRbTree(rbTree root){
  return root == NULL;
}

rbNodePtr searchRbTree(rbTree root, int value){
    if(!root) return NULL;
    else{
      if(root->value > value) return searchRbTree(root->left, value);
      else if(root->value < value) return searchRbTree(root->right, value);
      else return root;
    }
}

rbTree unionRbTree(rbTree tree1, rbTree tree2){
  rbTree ret = makeRbTree();
  unionRbTree_rc(tree1, tree2, &ret);
  return ret;
}

rbTree intersectRbTree(rbTree tree1, rbTree tree2){
  rbTree ret = makeRbTree();
  if(tree1) intersectRbTree_rc(tree1, tree2, &ret);
  return ret;
}

rbTree differenceRbTree(rbTree tree1, rbTree tree2){
  rbTree ret = makeRbTree();
  if(tree1) {
	ret = copyRbTree(tree1);
	removeDuplicatesRbTree(&ret);
	differenceRbTree_rc(tree2, &ret);
  }
  return ret;
}

void unionRbTree_rc(rbTree tree1, rbTree tree2, rbTree* tree3){
    if(!tree1 && !tree2){
      //do nothing
    }else if(tree1 && !tree2){
      if(!searchRbTree(*tree3, tree1->value)) *tree3 = insertRb(*tree3, tree1->value);
      unionRbTree_rc(tree1->left, tree2, tree3);
      unionRbTree_rc(tree1->right, tree2, tree3);
    }else if(!tree1 && tree2){
      if(!searchRbTree(*tree3, tree2->value)) *tree3 = insertRb(*tree3, tree2->value);
      unionRbTree_rc(tree1, tree2->left, tree3);
      unionRbTree_rc(tree1, tree2->right, tree3);
    }else{
      if(!searchRbTree(*tree3, tree1->value)) *tree3 = insertRb(*tree3, tree1->value);
      if(!searchRbTree(*tree3, tree2->value)) *tree3 = insertRb(*tree3, tree2->value);
      unionRbTree_rc(tree1->left, tree2, tree3);
      unionRbTree_rc(tree1->right, tree2, tree3);
      unionRbTree_rc(tree1, tree2->left, tree3);
      unionRbTree_rc(tree1, tree2->right, tree3);
    }
    return;
}

void intersectRbTree_rc(rbTree tree1, rbTree tree2, rbTree* tree3){
    if(tree2){
      if(searchRbTree(tree1, tree2->value))
        if(!searchRbTree(*tree3, tree2->value))
          *tree3 = insertRb(*tree3, tree2->value);
      intersectRbTree_rc(tree1, tree2->left, tree3);
      intersectRbTree_rc(tree1, tree2->right, tree3);
    }
    return;
}

void differenceRbTree_rc(rbTree tree2, rbTree* tree3){
  if(tree2){
    if(searchRbTree(*tree3, tree2->value))
      *tree3 = deleteRbNode(*tree3, tree2->value);
    differenceRbTree_rc(tree2->left, tree3);
    differenceRbTree_rc(tree2->right, tree3);
  }
  return;
}

rbTree copyRbTree(rbTree tree){
  rbTree copy = makeRbTree();
  copyRbTree_rec(tree, &copy);
  return copy;
}

void copyRbTree_rec(rbTree tree, rbTree* copy){
  if(!tree) return;
  *copy = insertRb(*copy, tree->value);
  copyRbTree_rec(tree->left, copy);
  copyRbTree_rec(tree->right, copy);
  return;
}

void removeDuplicatesRbTree(rbTree* tree){
  if(!(*tree)) return;
  if(searchRbTree((*tree)->left, (*tree)->value)){
    (*tree)->left = deleteRbNode((*tree)->left, (*tree)->value);
  }if(searchRbTree((*tree)->right, (*tree)->value)){
    (*tree)->right = deleteRbNode((*tree)->right, (*tree)->value);
  }
  removeDuplicatesRbTree(&(*tree)->left);
  removeDuplicatesRbTree(&(*tree)->right);
  return;
}

rbNodePtr successorRbTree(rbTree tree, int value){
    rbNodePtr ret = NULL;
    successorRbTree_rec(tree, value, &ret);
    return ret;
}

// ogni volta che scendo a sinistra devo salvare il nodo
void successorRbTree_rec(rbTree root, int value, rbNodePtr* candidate){
  if(root){
    if(root->value > value){
      *candidate = root;
      successorRbTree_rec(root->left, value, candidate);
    }else if(root->value < value){
      successorRbTree_rec(root->right, value, candidate);
    }else{
      rbNodePtr tmp = minRb(root->right);
      *candidate = (tmp) ? tmp : (*candidate);
    }
  }
  return;
}

rbNodePtr predeccessorRbTree(rbTree tree, int value){
  rbNodePtr ret = NULL;
  predecessorRbTree_rec(tree, value, &ret);
  return ret;
}

void predecessorRbTree_rec(rbTree root, int value, rbNodePtr* candidate){
  if(root){
    if(root->value > value){
      predecessorRbTree_rec(root->left, value, candidate);
    }else if(root->value < value){
      *candidate = root;
      predecessorRbTree_rec(root->right, value, candidate);
    }else{
      rbNodePtr tmp = maxRb(root->left);
      *candidate = (tmp) ? tmp : (*candidate);
    }
  }
  return;
}