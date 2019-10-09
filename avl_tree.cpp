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

  if(key == node->key) cout<<"\nError, Duplicate node!";

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

  if(node->bfactor < -1 && key > node->right->key)  
    return left_rotate(node);

  if(node->bfactor > 1 && key < node->left->key)  
    return right_rotate(node); 

  if(node->bfactor > 1 && key > node->left->key){
    node->left = left_rotate(node->left);  
    return right_rotate(node);  
  } 
  
  if(node->bfactor < -1 && key < node->right->key){
    node->right = right_rotate(node->right);  
    return left_rotate(node);  
  } 
  
  return node;
}

void AVLTree::print_tree(char option){

  int level = 0;

  if(root == NULL){ cout << "\nEmpty Tree!"; return;}

  rec_print(root, option, level);
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
          cout <<" Height: "<< height(root);
          rec_print(root->right, option, level);
      } 
  }

int AVLTree::update_bf(BinaryNode* root){
  if(root == NULL) return 0;

  update_bf(root->left);
  root->bfactor = find_bf(root);
  update_bf(root->right);
}

int AVLTree::height(BinaryNode* root){
    if(root == NULL) return 0;
    return max(height(root->left), height(root->right))+1;
}

int AVLTree::find_bf(BinaryNode* root){
  if(root == NULL) return 0;

  return (height(root->left) - height(root->right));
}

