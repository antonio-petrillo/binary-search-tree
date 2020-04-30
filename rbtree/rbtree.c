 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rbtree.h"

rb_node grandparent(rb_node node){
    assert(node != NULL);
    assert(node->parent != NULL);
    assert(node->parent->parent != NULL);
    return node->parent->parent;
}

rb_node sibling(rb_node node){
    assert(node != NULL);
    assert(node->parent != NULL);
    if(node == node->parent->left)
        return node->parent->right;
    else
        return node->parent->left;
}

rb_node uncle(rb_node node){
    assert(node != NULL);
    assert(node->parent != NULL);
    assert(node->parent->parent != NULL);
    return sibling(node->parent);
}

color_t node_color(rb_node node){
    return (node == NULL) ? BLACK : node->color;
}

int is_black(rb_node node){
    return (node == NULL) ? 1 : node->color == BLACK;
}

int is_red(rb_node node){
    return (node == NULL) ? 0 : node->color == RED;
}

int num_child(rb_node node){
    int num = 0;
    if(node->left != NULL) num++;
    if(node->right != NULL) num++;
    return num;
}

rbtree make_rbtree(){
    rbtree tree = (rbtree) malloc(sizeof(struct rbtree_t));
    assert(tree != NULL);
    tree->root = NULL;
    return tree;
}

rbtree drop_rbtree(rbtree tree){
    tree->root = drop_rbtree_helper(tree->root);
    free(tree);
    tree = NULL;
    assert(tree == NULL);
    return tree;
}


rb_node drop_rbtree_helper(rb_node node){
    if(node){
        drop_rbtree_helper(node->left);
        drop_rbtree_helper(node->right);
        free(node);
    }
    return NULL;
}

rb_node make_rbnode(int value, color_t color, rb_node left, rb_node right){
    rb_node newnode = (rb_node) malloc(sizeof(struct rb_node_t));
    assert(newnode != NULL);
    newnode->left = left;
    newnode->right = right;
    newnode->value = value;
    newnode->parent = NULL;
    newnode->color = color;
    if(left != NULL) left->parent = newnode;
    if(right != NULL) right->parent = newnode;
    return newnode;
}

rb_node search_rb_node(rbtree tree, int value){
    rb_node ret_node = tree->root;
    while(ret_node != NULL){
        if(ret_node->value > value){
            ret_node = ret_node->left;
        }else if(ret_node->value < value){
            ret_node = ret_node->right;
        }else{
            return ret_node;
        }
    }
    return ret_node;
}

rb_node search_rb_node_from_node(rb_node node, int value){
    rb_node ret_node = node;
    while (ret_node != NULL){
        if(ret_node->value > value){
            ret_node = ret_node->left;
        }
        else if(ret_node->value < value){
            ret_node = ret_node->right;
        }
        else{
            return ret_node;
        }
    }
    return ret_node;
    
}

void rotate_left_rb(rbtree tree, rb_node node){
    rb_node newroot = node->right;
    replace_rb_node(tree, node, newroot);
    node->right = newroot->left;
    if(newroot->left){
        newroot->left->parent = node;
    }
    newroot->left = node;
    node->parent = newroot;
    return;
}

void rotate_right_rb(rbtree tree, rb_node node){
    rb_node newroot = node->left;
    replace_rb_node(tree, node, newroot);
    node->left = newroot->right;
    if(newroot->right){
        newroot->right->parent = node;
    }
    newroot->right = node;
    node->parent = newroot;
    return;
}

void replace_rb_node(rbtree tree, rb_node old_node, rb_node node){
    if(old_node->parent == NULL){
        tree->root = node;
    }else{
        if(old_node == old_node->parent->left){
            old_node->parent->left = node;
        }else{
            old_node->parent->right = node;
        }
        
    }
    if(node != NULL){
        node->parent = old_node->parent;
    }
    return;
}

void rbtree_insert(rbtree tree, int value){
    rb_node newnode = make_rbnode(value, RED, NULL, NULL);
    if(tree->root == NULL){
        tree->root = newnode;
    }else{
        rb_node iter = tree->root;
        while(1){
            if(iter->value > value){
                if(iter->left == NULL){
                    iter->left = newnode;
                    break;
                }else{
                    iter = iter->left;
                }
            }else{
                if(iter->right == NULL){
                    iter->right = newnode;
                    break;
                }else{
                    iter = iter->right;
                }
            }
        }       
        newnode->parent = iter;
    }
    rb_insert_fixup(tree, newnode);
    return;
}

void rb_insert_fixup(rbtree tree, rb_node node){
    rb_node tmp = NULL;
    while(is_red(node->parent)){
        if(node->parent == node->parent->parent->left){//left violation
            tmp = uncle(node);
            if(is_red(tmp)){// uncle red
                node->parent->color = BLACK;
                tmp->color = BLACK;
                grandparent(node)->color = RED;
                node = grandparent(node);
            }
            else{ //uncle black
                if(node == node->parent->right){
                    node = node->parent;
                    rotate_left_rb(tree, node);
                }
                node->parent->color = BLACK;
                grandparent(node)->color = RED;
                rotate_right_rb(tree, grandparent(node));
            }
        }
        else{//right violation
            tmp = uncle(node);
            if(is_red(tmp)){//uncle red
                node->parent->color = BLACK;
                tmp->color = BLACK;
                grandparent(node)->color = RED;
                node = grandparent(node);
            }
            else{// uncle black
                if(node == node->parent->left){
                    node = node->parent;
                    rotate_right_rb(tree, node);
                }
                node->parent->color = BLACK;
                grandparent(node)->color = RED;
                rotate_left_rb(tree, grandparent(node));
            }
        }
    }
    tree->root->color = BLACK;
    return;
}

void in_order_rbvisit(rbtree tree){
    in_order_rbvisit_helper(tree->root);
    return;
}

void in_order_rbvisit_helper(rb_node node){
    if(node){
        in_order_rbvisit_helper(node->left);
        printf("node's value: %d , node's color: %s", node->value, color_to_string(node));
        if(node->left){
            printf(", left child: %d", node->left->value);
        }
        if(node->right){
            printf(", right child: %d", node->right->value);
        }
        if(node->parent){
            printf(", node's parent: %d \n", node->parent->value);
        }
        else{
            printf(", this is the root \n");
        }
        in_order_rbvisit_helper(node->right);
    }
    return;
}

void post_order_rbvisit(rbtree tree){
    post_order_rbvisit_helper(tree->root);
    return;
}

void post_order_rbvisit_helper(rb_node node){
    if(node){
        post_order_rbvisit_helper(node->left);
        post_order_rbvisit_helper(node->right);
        if(node->left){
            printf(", left child: %d", node->left->value);
        }
        if(node->right){
            printf(", right child: %d", node->right->value);
        }
        if(node->parent){
            printf(", node's parent: %d \n", node->parent->value);
        }
        else{
            printf(", this is the root \n");
        }
    }
    return;
}

void pre_order_rbvisit(rbtree tree){
    pre_order_rbvisit_helper(tree->root);
    return;
}

void pre_order_rbvisit_helper(rb_node node){
    if(node){
        if(node->left){
            printf(", left child: %d", node->left->value);
        }
        if(node->right){
            printf(", right child: %d", node->right->value);
        }
        if(node->parent){
            printf(", node's parent: %d \n", node->parent->value);
        }
        else{
            printf(", this is the root \n");
        }
        pre_order_rbvisit_helper(node->left);
        pre_order_rbvisit_helper(node->right);
    }
    return;
}


void rbtree_remove(rbtree tree, int key){
    rb_node del_node = search_rb_node(tree, key);
    rb_node child = NULL;
    if(del_node == NULL) return; // key not present into the tree
    if(num_child(del_node) == 2){
        rb_node predecessor = min_rb_from_node(del_node);
        del_node->value = predecessor->value;
        del_node = predecessor;
    }
    assert(del_node->left == NULL || del_node->right == NULL);
    child = (del_node->right == NULL) ? del_node->left : del_node->right;
    if(is_black(del_node)){
        del_node->color = node_color(child);
        delete_case1(tree, del_node);
    }
    replace_rb_node(tree, del_node, child);
    if(del_node->parent == NULL && child != NULL)
        child->color = BLACK;
    free(del_node);
    return;
}

void rbtree_remove_with_addr(rbtree tree, rb_node key){
    rb_node del_node = key;
    rb_node child = NULL;
    if(del_node == NULL) return; // key not present into the tree
    if(num_child(del_node) == 2){
        rb_node predecessor = min_rb_from_node(del_node);
        del_node->value = predecessor->value;
        del_node = predecessor;
    }
    assert(del_node->left == NULL || del_node->right == NULL);
    child = (del_node->right == NULL) ? del_node->left : del_node->right;
    if(is_black(del_node)){
        del_node->color = node_color(child);
        delete_case1(tree, del_node);
    }
    replace_rb_node(tree, del_node, child);
    if(del_node->parent == NULL && child != NULL)
        child->color = BLACK;
    free(del_node);
    return;
}

rb_node min_rb(rbtree tree){
    rb_node ret_node = tree->root;
    while(ret_node != NULL && ret_node->left != NULL) 
        ret_node = ret_node->left;
    return ret_node;
}

rb_node max_rb(rbtree tree){
    rb_node ret_node = tree->root;
    while(ret_node != NULL && ret_node->right != NULL)
        ret_node = ret_node->right;
    return ret_node;
}

rb_node min_rb_from_node(rb_node node){
    if(node && node->left == NULL) return node;
    return min_rb_from_node(node->left);
}

rb_node max_rb_from_node(rb_node node){
    if(node && node->right == NULL) return node;
    return max_rb_from_node(node->right);
}

void delete_case1(rbtree tree, rb_node node){
    if(node->parent != NULL){
        delete_case2(tree, node);
    }
    return;
}

void delete_case2(rbtree tree, rb_node node){
    if(is_red(sibling(node))){
        node->parent->color = RED;
        sibling(node)->color = BLACK;
        if(node == node->parent->left){
            rotate_left_rb(tree, node->parent);
        }
        else{
            rotate_right_rb(tree, node->parent);
        }
    }
    delete_case3(tree, node);
    return;
}

void delete_case3(rbtree tree, rb_node node){
    if(is_black(node->parent) && is_black(sibling(node)) && is_black(sibling(node)->left) && is_black(sibling(node)->right)){
        sibling(node)->color = RED;
        delete_case1(tree, node->parent);
    }else{
        delete_case4(tree, node);
    }
    return;
}

void delete_case4(rbtree tree, rb_node node){
    if(is_red(node->parent) && is_black(sibling(node)) && is_black(sibling(node)->left) && is_black(sibling(node)->right)){
        sibling(node)->color = RED;
        node->parent->color = BLACK;
    } 
    else{
        delete_case5(tree, node);
    }
    return;
}

void delete_case5(rbtree tree, rb_node node){
    if(node == node->parent->left && is_black(sibling(node)) && is_red(sibling(node)->left) && is_black(sibling(node)->right)){
        sibling(node)->color = RED;
        sibling(node)->left->color = BLACK;
        rotate_right_rb(tree, node);
    }
    else if(node == node->parent->right && is_black(sibling(node)) && is_red(sibling(node)->right) && is_black(sibling(node)->left)){
        sibling(node)->color = RED;
        sibling(node)->right->color = BLACK;
        rotate_left_rb(tree, node);
    }
    delete_case6(tree, node);
    return;
}

void delete_case6(rbtree tree, rb_node node){
    sibling(node)->color = node_color(node->parent);
    node->parent->color = BLACK;
    if(node == node->parent->left){
        assert(is_red(sibling(node)->right));
        sibling(node)->right->color = BLACK;
        rotate_left_rb(tree, node->parent);
    }
    else{
        assert(is_red(sibling(node)->left));
        sibling(node)->left->color = BLACK;
        rotate_right_rb(tree, node->parent);
    }
    return;
}

int count_rb_node(rbtree tree){
    return count_rb_node_helper(tree->root);
}

int count_rb_node_helper(rb_node node){
    if(!node) return 0;
    return count_rb_node_helper(node->left) + count_rb_node_helper(node->right) + 1;
}

int is_empty_rb(rbtree tree){
    return tree->root == NULL;
}

rbtree union_rbtree(rbtree tree1, rbtree tree2){
    rbtree ret_tree = make_rbtree();
    union_rbtree_helper(tree1->root, tree2->root, ret_tree);
    return ret_tree;
}

void union_rbtree_helper(rb_node tree1, rb_node tree2, rbtree tree3){
    if(!tree1 && !tree2){
      //do nothing
    }else if(tree1 && !tree2){
      if(!search_rb_node(tree3, tree1->value)) rbtree_insert(tree3, tree1->value);
      union_rbtree_helper(tree1->left, tree2, tree3);
      union_rbtree_helper(tree1->right, tree2, tree3);
    }else if(!tree1 && tree2){
      if(!search_rb_node(tree3, tree2->value)) rbtree_insert(tree3, tree2->value);
      union_rbtree_helper(tree1, tree2->left, tree3);
      union_rbtree_helper(tree1, tree2->right, tree3);
    }else{
      if(!search_rb_node(tree3, tree1->value)) rbtree_insert(tree3, tree1->value);
      if(!search_rb_node(tree3, tree2->value)) rbtree_insert(tree3, tree2->value);
      union_rbtree_helper(tree1->left, tree2, tree3);
      union_rbtree_helper(tree1->right, tree2, tree3);
      union_rbtree_helper(tree1, tree2->left, tree3);
      union_rbtree_helper(tree1, tree2->right, tree3);
    }
    return;
}

rbtree intersect_rbtree(rbtree tree1, rbtree tree2){
    rbtree ret_tree = make_rbtree();
    if(!is_empty_rb(tree1))intersect_rbtree_helper(tree1->root, tree2->root, ret_tree);
    return ret_tree;
}

void intersect_rbtree_helper(rb_node tree1, rb_node tree2, rbtree tree3){
    if(tree2){
      if(search_rb_node_from_node(tree1, tree2->value))
        if(!search_rb_node(tree3, tree2->value))
          rbtree_insert(tree3, tree2->value);
      intersect_rbtree_helper(tree1, tree2->left, tree3);
      intersect_rbtree_helper(tree1, tree2->right, tree3);
    }
    return;
}

rbtree difference_rbtree(rbtree tree1, rbtree tree2){
    rbtree ret_tree = make_rbtree();
    ret_tree = copy_rbtree(tree1);
    if(!is_empty_rb(tree2)) difference_rbtree_helper(tree2->root, ret_tree);
    return ret_tree;
}

void difference_rbtree_helper(rb_node tree2, rbtree tree3){
    if(tree2){
        if(search_rb_node(tree3, tree2->value)){
            rbtree_remove(tree3, tree2->value);
        }
        difference_rbtree_helper(tree2->left, tree3);
        difference_rbtree_helper(tree2->right, tree3);
    }
    return;
}

rbtree copy_rbtree(rbtree src){
    rbtree copy = make_rbtree();
    copy_rbtree_helper(copy, src->root);
    return copy;
}

void copy_rbtree_helper(rbtree dest, rb_node node){
    if(node){
        rbtree_insert(dest, node->value);
        copy_rbtree_helper(dest, node->left);
        copy_rbtree_helper(dest, node->right);
    }
    return;
}

void remove_rb_duplicates(rbtree tree){
    remove_rb_duplicates_helper(tree, tree->root);
    return;
}

void remove_rb_duplicates_helper(rbtree tree, rb_node node){
    if(node){
        rb_node tmp = NULL;
        if(tmp = search_rb_node_from_node(node->left, node->value), tmp){
            rbtree_remove_with_addr(tree, tmp);
        }
        if(tmp = search_rb_node_from_node(node->right, node->value), tmp){
            rbtree_remove_with_addr(tree, tmp);
        }
        remove_rb_duplicates_helper(tree, node->left);
        remove_rb_duplicates_helper(tree, node->right);
    }
    return;
}

rb_node rb_successor(rbtree tree, int key){
    rb_node ret_node = NULL;
    if(!is_empty_rb(tree)) rb_successor_helper(tree->root, key, &ret_node);
    return ret_node;
}

void rb_successor_helper(rb_node node, int key, rb_node* candidate){
    if(node){
        if(node->value > key){
            *candidate = node;
            rb_successor_helper(node->left, key, candidate);
        }else if(node->value < key){
            rb_successor_helper(node->right, key, candidate);
        }else{
            rb_node tmp = min_rb_from_node(node->right);
            *candidate = (tmp != NULL) ? tmp : (*candidate);
        }
    }
    return;
}

rb_node rb_predecessor(rbtree tree, int key){
    rb_node ret_node = NULL;
    if(!is_empty_rb(tree)) rb_predecessor_helper(tree->root, key, &ret_node);
    return ret_node;
}

void rb_predecessor_helper(rb_node node, int key, rb_node* candidate){
        if(node){
        if(node->value > key){
            rb_predecessor_helper(node->left, key, candidate);
        }else if(node->value < key){
            *candidate = node;
            rb_predecessor_helper(node->right, key, candidate);
        }else{
            rb_node tmp = max_rb_from_node(node->left);
            *candidate = (tmp != NULL) ? tmp : (*candidate);
        }
    }
    return;
}