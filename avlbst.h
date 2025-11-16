#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rotateLeft(AVLNode<Key, Value> *node);
    void rotateRight(AVLNode<Key, Value> *node);

};

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value> *node){
    //start with middle node
    //get the parent node
    if (node == nullptr){
        return ;
    }
    AVLNode<Key, Value> *par = node->getParent();
    AVLNode<Key, Value> *right = node->getRight();

    if (!right){
        return;
    }
    if (right->getLeft()){
        AVLNode<Key, Value> *rightLeftSub = right->getLeft();

        node->setRight(rightLeftSub);
        rightLeftSub->setParent(node);
    }else{
        node->setRight(nullptr);
    }
    right->setParent(par);
    if(par == nullptr){
        this->root_ = right;
    }
    else if(par->getLeft() == node){
        par->setLeft(right);
    }else{
        par->setRight(right);
    }
    
    right->setLeft(node);
    node->setParent(right);

    int8_t nodeOldBal = node->getBalance();
    int8_t rightOldBal = right->getBalance();

    node->setBalance(nodeOldBal - 1 - std::max(rightOldBal, (int8_t)0));
    right->setBalance(rightOldBal - 1 + std::min(node->getBalance(), (int8_t)0));

    // return right;

}
template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value> *node){
    //start with middle node
    //get the parent node
    if (node == nullptr){
        return ;
    }
    AVLNode<Key, Value> *par = node->getParent();
    AVLNode<Key, Value> *left = node->getLeft();
    if (!left){
        return;
    }
    if (left->getRight()){
        AVLNode<Key, Value> *leftRightSub = left->getRight();

        node->setLeft(leftRightSub);
        leftRightSub->setParent(node);
    }else{
        node->setLeft(nullptr);
    }
    left->setParent(par);
    if(par == nullptr){
        this->root_ = left;
    }
    else if(par->getRight() == node){
        par->setRight(left);
    }else{
        par->setLeft(left);
    }
    
    left->setRight(node);
    node->setParent(left);
    // return left;
    int8_t nodeOldBal = node->getBalance();
    int8_t leftOldBal  = left->getBalance();

    node->setBalance(nodeOldBal + 1 - std::min(leftOldBal, (int8_t)0));
    left->setBalance(leftOldBal  + 1 + std::max(node->getBalance(), (int8_t)0));
}
/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    // BinarySearchTree<Key, Value>::insert(new_item);
    // AVLNode<Key, Value> *temp = (AVLNode<Key, Value>*)BinarySearchTree<Key, Value>::internalFind(new_item.first);
    if (this->root_ == nullptr){
        this->root_ = new AVLNode<Key, Value> (new_item.first, new_item.second, nullptr);
        return;
    }
    AVLNode<Key, Value> *curr = (AVLNode<Key, Value>*)this->root_;
    const Key& newKey = new_item.first;
    AVLNode<Key, Value> *temp = curr;
    while (curr != nullptr){
        if (newKey > curr->getKey()){
            if (curr->getRight()){
                curr = curr->getRight();
            }else{
                AVLNode<Key, Value> *newNode = new AVLNode<Key, Value> (new_item.first, new_item.second, curr);
                curr->setRight(newNode);
                temp = newNode;
                break;
            }
        }else if (newKey < curr->getKey()){
            if (curr->getLeft()){
                curr = curr->getLeft();
            }else{
                AVLNode<Key, Value> *newNode = new AVLNode<Key, Value> (new_item.first, new_item.second, curr);
                curr->setLeft(newNode);
                temp = newNode;
                break;
            }
        }else{
            curr->setValue(new_item.second);
            return;
        }
    }
    while (temp->getParent()){
        if (temp == temp->getParent()->getRight()){
            temp->getParent()->updateBalance(1);
        }else{
            temp->getParent()->updateBalance(-1);
        }
        int tempBalance = temp->getParent()->getBalance();
        AVLNode<Key, Value> *tempParent = temp->getParent();
        if (tempBalance == 0){
            break;
        }
        if (abs(tempBalance) == 1) {
            temp = temp->getParent();
            continue;
        }
        if (tempBalance == -2){
            AVLNode<Key, Value> *tempChild = tempParent->getLeft();
            if (tempChild && tempChild->getBalance() <= 0){
                rotateRight(tempParent);
            }else{
                if (tempChild){
                    rotateLeft(tempChild);
                }
                rotateRight(tempParent);
            }
            break;
        }else if(tempBalance == 2){
            AVLNode<Key, Value> *tempChild = tempParent->getRight();
            if (tempChild && tempChild->getBalance() >= 0){
                rotateLeft(tempParent);
            }else{
                if(tempChild){
                    rotateRight(tempChild);
                }
                rotateLeft(tempParent);
            }
            break;
        }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key){
    if (this->root_ == nullptr){
        return;
    }
    AVLNode<Key, Value> *curr = (AVLNode<Key, Value>*)this->root_;
    while (curr != nullptr){
        if (key > curr->getKey()){
            if (curr->getRight()){
                curr = curr->getRight();
            }else{
                return; 
            }
        }else if (key < curr->getKey()){
            if (curr->getLeft()){
                curr = curr->getLeft();
            }else{
                return;
            }
        }else{
            break;
        }
    }
    if (curr == nullptr){
        return;
    }
    if (curr->getRight() != nullptr && curr->getLeft() != nullptr){
        AVLNode<Key, Value>* pred = (AVLNode<Key, Value>*)(BinarySearchTree<Key, Value>::predecessor(curr));
        nodeSwap(pred, curr);
    }
    AVLNode<Key, Value>* par = curr->getParent();
    int diff = 0;
    if (par != nullptr) {
        if (par->getLeft() == curr) {
            diff = 1; 
        } else {
            diff = -1;
        }
    }
    if (curr == this->root_){
        if (curr->getLeft()){
            this->root_ = curr->getLeft();
            if(curr->getLeft() != nullptr){
                curr->getLeft()->setParent(nullptr);
                delete curr;
            }
        }else if (curr->getRight()){
            this->root_ = curr->getRight();
            if (curr->getRight()){
                curr->getRight()->setParent(nullptr);
                delete curr;
            }
        }else{
            this->root_ = nullptr;
            delete curr;
        }
        return;
    }
    if (curr->getLeft() != nullptr){
        if (curr->getParent()->getLeft() == curr){
            curr->getParent()->setLeft(curr->getLeft());
        }else{
            curr->getParent()->setRight(curr->getLeft());
        }
        curr->getLeft()->setParent(curr->getParent());
    }else if(curr->getRight() != nullptr){
        if (curr->getParent()->getLeft() == curr){
            curr->getParent()->setLeft(curr->getRight());
        }else{
            curr->getParent()->setRight(curr->getRight());
        }
        curr->getRight()->setParent(curr->getParent());
    }else{  
        if(curr->getParent()->getLeft() == curr){
            curr->getParent()->setLeft(nullptr);
        }else{
            curr->getParent()->setRight(nullptr);
        }
    }
    delete curr;
    AVLNode<Key, Value>* temp = par;
    while (temp != nullptr){
        temp->updateBalance(diff);
        int tempBalance = temp->getBalance();
        AVLNode<Key, Value> *tempParent = temp->getParent();
        if (tempParent != nullptr) {
            if (tempParent->getLeft() == temp) {
                diff = 1;
            } else {
                diff = -1;
            }
        }
        if (abs(tempBalance) == 1) {
            break;  
        }
        if (tempBalance == -2){
            AVLNode<Key, Value> *tempChild = temp->getLeft();
            int childBalance;
            if (tempChild != nullptr) {
                childBalance = tempChild->getBalance();
            } else {
                childBalance = 0;
            }    
            if (tempChild && childBalance <= 0){
                rotateRight(temp);
                if (tempChild->getBalance() != 0) {
                    break;
                }
            }else{
                if (tempChild){
                    rotateLeft(tempChild);
                }
                rotateRight(temp);
            }
            temp = tempParent;
        }else if(tempBalance == 2){
            AVLNode<Key, Value> *tempChild = temp->getRight();
            int childBalance;
            if (tempChild != nullptr) {
                childBalance = tempChild->getBalance();
            } else {
                childBalance = 0;
            } 
            if (tempChild && childBalance >= 0){
                rotateLeft(temp);
                if (tempChild->getBalance() != 0) {
                    break;
                }
            }else{
                if(tempChild){
                    rotateRight(tempChild);
                }
                rotateLeft(temp);
            }
            temp = tempParent;
        }else{
            temp = tempParent;
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
