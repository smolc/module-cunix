#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"

node_t  *allocnode(){
  node_t *node = (node_t*) malloc(sizeof(node_t));
  node->left =  0;
  node->right = 0;
  return node;
}

node_t  *insert(node_t *root, char *key, void *data){
  if (root){
    if (root->key > key)
     root->right = insert(root->right, key, data);
    if (root->key < key)
     root->left = insert(root->left, key, data);
  }
  else{
    root = allocnode();
    root->key = key;
    root->data = data;
  }
  return root;
}

void print_node(node_t *node){
  if(node)
    printf(node->data);
}

void visit_tree(node_t *node, void (*fp)(node_t *root)){
  if(node){
    fp(node);
    visit_tree(node->left, fp);
    visit_tree(node->right, fp);
  }
}

void destroy_tree(node_t *node, void (*fdestroy)(node_t *root)){
  if(node){
    destroy_tree(node->left, fdestroy);
    destroy_tree(node->right, fdestroy);
    fdestroy(node);
    node = 0;
  }
  free(node);
}