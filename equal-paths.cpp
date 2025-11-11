#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int helperFunction(Node * root, int depth){
    if (root == nullptr){
        return -1;
    }
    if (root->left == nullptr && root->right == nullptr){
        return depth;
    }
    int leftsum = helperFunction(root->left, depth+1);
    int rightsum = helperFunction(root->right, depth+1);
    if (rightsum == leftsum){
        return rightsum;
    }
    return -1;
    
}

bool equalPaths(Node * root)
{
    // Add your code below
    return helperFunction(root, 0) != -1;
    
}

