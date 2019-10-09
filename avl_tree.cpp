#include <iostream>
#include "avl_tree.h"
#include <algorithm>

using namespace std;

void AVLTree::insert(const int key) {
  this->root = insert(key, this->root);
}

BinaryNode* AVLTree::insert(const int key, BinaryNode* node) {
  if (node == NULL) {
    return new BinaryNode(key);
  }

  if(key < node->key) {
    if(node->left == NULL) {
      node->left = new BinaryNode(key); 
      update_bf(node);
    } 
    else {
      node->left = insert(key, node->left);
    }
  }
  else {
    if(node->right == NULL) {
      node->right = new BinaryNode(key); 
      update_bf(node);
    } 
    else {
      node->right = insert(key, node->right);
    }
  }
  return node;
}

void AVLTree::rec_print(BinaryNode* root, char option, int level){

      if(root == NULL) return;

      if(option == 'p'){
          rec_print(root->left, option, level);
          std::cout<<" key: "<<root->key;
          rec_print(root->right, option, level);
      } 

      if(option == 'h'){

          rec_print(root->left, option, level);
      } 
  }

int AVLTree::height(BinaryNode* root){
    if(root == NULL) return 0;
    return max(height(root->left), height(root->right))+1;
}