#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int helperFunction(Node * root, int depth){
    if (root == nullptr){
        return depth;
    }
    int leftsum = helperFunction(root->left, depth+1);
    int rightsum = helperFunction(root->right, depth+1);

    if (root->left == nullptr && root->right == nullptr){
        if (rightsum != leftsum){
        return -1;
        }
        return 0;
    }
    return -1;
    
}

bool equalPaths(Node * root)
{
    // Add your code below
    int x = helperFunction(root, 0);
    if (x == 0){
        return true;
    }
    return false;
    
}

