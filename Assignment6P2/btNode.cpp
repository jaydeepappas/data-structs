#include "btNode.h"

void dumpToArrayInOrder(btNode* bst_root, int* dumpArray)
{
   if (bst_root == 0) return;
   int dumpIndex = 0;
   dumpToArrayInOrderAux(bst_root, dumpArray, dumpIndex);
}

void dumpToArrayInOrderAux(btNode* bst_root, int* dumpArray, int& dumpIndex)
{
   if (bst_root == 0) return;
   dumpToArrayInOrderAux(bst_root->left, dumpArray, dumpIndex);
   dumpArray[dumpIndex++] = bst_root->data;
   dumpToArrayInOrderAux(bst_root->right, dumpArray, dumpIndex);
}

void tree_clear(btNode*& root)
{
   if (root == 0) return;
   tree_clear(root->left);
   tree_clear(root->right);
   delete root;
   root = 0;
}

int bst_size(btNode* bst_root)
{
   if (bst_root == 0) return 0;
   return 1 + bst_size(bst_root->left) + bst_size(bst_root->right);
}

void bst_insert(btNode*& bst_root, int newInt){
    if (bst_root == 0){
        btNode* new_root = new btNode;
        new_root->data = newInt;
        new_root->left = new_root->right = 0;
        bst_root = new_root;
        return;
    }
    
    else{
        btNode* cursor = bst_root;
    start:
        if (newInt < cursor->data){
            if (cursor->left == 0){
                cursor->left = new btNode;
                cursor->left->data = newInt;
                cursor->left->left = cursor->left->right = 0;
                return;
            }
            else{
                cursor = cursor->left;
                goto start;
            }
        }
        else if (newInt > cursor->data){
            if (cursor->right == 0){
                cursor->right = new btNode;
                cursor->right->data = newInt;
                cursor->right->left = cursor->right->right = 0;
                return;
            }
            else{
                cursor = cursor->right;
                goto start;
            }
        }
        else{
            return;
        }
    }
}

bool bst_remove(btNode*& bst_root, int remInt){
    if(bst_root == 0){
        return false;
    }

    if (remInt != bst_root->data){
        if (remInt > bst_root->data){
            return bst_remove(bst_root->right, remInt);
        }
        else {
            return bst_remove(bst_root->left, remInt);
        }
    }
    
    if (bst_root->left == 0){
        btNode* old_bst_root = bst_root;
        if(bst_root->right != 0){
            bst_root = bst_root->right;
        }
        else{
            bst_root = 0;
        }
        delete old_bst_root;
        return true;
    }
    else{
        bst_remove_max(bst_root->left, bst_root->data);
        return true;
    }
    return false;
}

void bst_remove_max(btNode*& bst_root, int& data){
    if(bst_root == 0){
        return;
    }

    if(bst_root->right == 0){
        btNode* temp = bst_root;
        data = bst_root->data;
        bst_root = bst_root->left;
        delete temp;
    }
    else{
        bst_remove_max(bst_root->right, data);
    }
    
}

