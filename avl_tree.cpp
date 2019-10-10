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
      //update_bf(node);
    } 
    else {
      node->left = insert(key, node->left);
    }
  }
  else {
    if(node->right == NULL) {
      node->right = new BinaryNode(key); 
      //update_bf(node);
    } 
    else {
      node->right = insert(key, node->right);
    }
  }
  
  node->bfactor = height(node->left) - height(node->right);

  //cout<<"\nHello!";

  if(node->bfactor > 1 && node->left != NULL && key < node->left->key)  
    return right_rotate(node); 

  if(node->bfactor < -1 && node->right != NULL && key > node->right->key)  
    return left_rotate(node);

  if(node->bfactor > 1 && node->left != NULL && key > node->left->key){
    node->left = left_rotate(node->left);  
    return right_rotate(node);  
  } 
  
  if(node->bfactor < -1 && node->right != NULL && key < node->right->key){
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

// int AVLTree::update_bf(BinaryNode* root){
//   if(root == NULL) return 0;

//   update_bf(root->left);
//   cout<<" heigh";
//   update_bf(root->right);
// }

int AVLTree::height(BinaryNode* node){
    if(node == NULL) return 0;
    return max(height(node->left), height(node->right))+1;
}

// int AVLTree::find_bf(BinaryNode* root){
//   if(root == NULL) return 0;

//   return (height(root->left) - height(root->right));
// }

BinaryNode* AVLTree::left_rotate(BinaryNode* node){
  //cout<<"\nHello! from left rotate 1";
  BinaryNode* previous_right = node->right;
  BinaryNode* previous_left = previous_right->left;

  previous_right->left = node;
  node->right = previous_left;


  //cout<<"\nHello! from left rotate 2";

  return previous_right;
}

BinaryNode* AVLTree::right_rotate(BinaryNode* node){
  //cout<<"\nHello! from right rotate 1";

  BinaryNode* previous_left = node->left;
  BinaryNode* previous_right = previous_left->right;

  previous_left->right = node;
  node->left = previous_right;

  //cout<<"\nHello! from right rotate 2";


  return previous_left;
}

BinaryNode* AVLTree::remove(BinaryNode *root, int key){

  if(root == NULL)
    return root;

  // go down left subtree to find matching key
  if(key < root->key){
    root->left = remove(root->left, key);
  // if it wasn't smaller, we must go down right subtree
  }else if(key > root->key){
    root->right = remove(root->right, key);
  //this is the case where we find the key that needs to be deleted
  }else if(root->key == key){
    if((root->left == NULL) || (root->right == NULL)){
      
      BinaryNode* newnode;

      if(root->left){
        newnode = root->left;
      }else{ 
        newnode = root->right;
      }

      if(newnode == NULL){
        newnode=root;
        root = NULL;
      }else{
        *root = *newnode;
      }
      free(newnode);
    } 

  }

}