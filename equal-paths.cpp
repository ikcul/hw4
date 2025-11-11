#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int helperFunction(Node * root, int depth){
    //empty branch
    if (root == nullptr){
        return 0;
    }
    if (root->left == nullptr && root->right == nullptr){
        return depth;
    }
    int leftsum = helperFunction(root->left, depth+1);
    int rightsum = helperFunction(root->right, depth+1);
    //checks to see if any branch is invalid
    if (rightsum == -1 || leftsum == -1){
        return -1;
    }
    //checks if they are equal length
    if (rightsum == leftsum){
        return rightsum;
    }
    //checks if one branch is empty
    else if (leftsum == 0){
        return rightsum;
    }
    //checks the other
    else if (rightsum == 0){
        return leftsum;
    }
    return -1;
}

bool equalPaths(Node * root)
{
    // Add your code below
    return helperFunction(root, 0) != -1;
    
}

