#pragma once

#include "AVL.h"

using namespace std;


//Please note that the class that implements this interface must be made
//of objects which implement the NodeInterface

/*
* Returns the root node for this tree
*
* @return the root node for this tree.
*/
NodeInterface* AVL::getRootNode() const{
    return root;
}

/*
* Attempts to add the given int to the AVL tree
* Rebalances the tree if data is successfully added
*
* @return true if added
* @return false if unsuccessful (i.e. the int is already in tree)
*/

bool AVL::add(int data){
//    cout << "attempting to add"<< data << endl;
    return insert(data, root);
}

bool AVL::insert(int _val, Node *&localRoot) {
    // if root is null, add
    if (localRoot == NULL) {
        localRoot = new Node(_val);
        // cout << "value = " << localRoot->value;
        return true;
    }

    //add and rebalance
    else if (localRoot->value > _val) {

        bool added = insert(_val, localRoot->left);

        if (added)
            check_imbalance(localRoot);

        return added;
    }
    else if (localRoot->value < _val){

        bool added = insert(_val, localRoot->right);

        if (added)
            check_imbalance(localRoot);

        return added;
    }
    // Checks duplicates
    else {
        return false;
    }
}

/*
* Attempts to remove the given int from the AVL tree
* Rebalances the tree if data is successfully removed
*
* @return true if successfully removed
* @return false if remove is unsuccessful(i.e. the int is not in the tree)
*/
//todo add rebalancing
bool AVL::remove(int data){
//    cout << "attempting to remove"<< data << endl;
    return remove_val(data, root);
}

bool AVL::remove_val(int _val, Node *&localRoot){
    //Checks if the tree is empty
    if (localRoot == NULL){
        return false;
    }

    // Checks to see if the node matches the data and removes it
    if (localRoot->value == _val){
        // If node holds the value and there are no children, delete node
        if (localRoot->left == NULL && localRoot->right == NULL){
            delete localRoot;
            localRoot =  NULL;
            return true;
        }

        // no right child
        if (localRoot->right == NULL && localRoot->left != NULL){
            Node* Temp_Node = localRoot;
            localRoot = Temp_Node->left; // replaces the deleted node with its child
            delete Temp_Node;


            return true;
        }
            // no left child
        else if (localRoot->left == NULL && localRoot->right !=NULL){
            Node* Temp_Node = localRoot;
            localRoot = Temp_Node->right; // replaces the deleted node with its child
            delete Temp_Node;
            return true;
        }
            // if both children are present
        else{
            // finds the pivot node
            Node* Temp_Node = inOrderPredecessor(localRoot);
            cout << "pivot node val = " << Temp_Node->value << endl;

            //overides node with pivot node value
            localRoot->value = Temp_Node->value;

            //Removes pivot node
            bool removed = remove_val(Temp_Node->value, localRoot->left);

            if (removed){
                check_imbalance(localRoot);
            }
            return removed;
        }
    }
        // Checks the right branch
    else if (localRoot->value < _val){
        bool removed = remove_val(_val, localRoot->right);

        if (removed){
            check_imbalance(localRoot);
        }
        return removed;
    }
        // checks the left branch
    else if (localRoot->value > _val){
        bool removed = remove_val(_val, localRoot->left);
        if (removed){
            check_imbalance(localRoot);
        }
        return removed;
    }
    else
        return false;
}

Node* AVL::inOrderPredecessor(Node *&localRoot){
    // finds the rightmost value on the left branch for the pivot
    Node* leftChild = localRoot->left;
    if (leftChild->right == NULL)
        return leftChild;
    else{
        while (leftChild->right != NULL){
            leftChild = leftChild->right;
        }
        return leftChild;
    }
}
/*
* Removes all nodes from the tree, resulting in an empty tree.
*/
void AVL::clear(){
//    cout << "Clearing your BST ... ";
    remove_everything(root);
    root = NULL;
}
void AVL::remove_everything(Node *&localRoot){
    // Base case
    if (localRoot ==NULL)
        return;

    //traverse right branch
    if (localRoot->right != NULL)
        remove_everything(localRoot->right);

    //Traverse left branch
    if (localRoot->left != NULL)
        remove_everything(localRoot->left);

    //if at the bottom of branch, remove it.
    if (localRoot->right == NULL && localRoot->left ==NULL){
        delete localRoot;
        localRoot = NULL;
        return;
    }
}

//////////////////////////////////
// REBALANCING FUNCTIONS
/////////////////////////////////
void AVL::leftRotate(Node *& localRoot) {
    Node * defeated = localRoot;
    Node * upstart = localRoot ->right;
    localRoot = upstart;
    defeated ->right = upstart->left;
    upstart -> left = defeated;
    localRoot->updateHeight(defeated);
    localRoot->updateHeight(upstart);
}

void AVL::rightRotate(Node *& localRoot) {
    Node * defeated = localRoot;
    Node * upstart = localRoot ->left;
    localRoot = upstart;
    defeated ->left = upstart->right;
    upstart -> right = defeated;
    localRoot->updateHeight(defeated);
    localRoot->updateHeight(upstart);
}

bool AVL::left_left_Imbalance(Node *localRoot) {
    if ((localRoot->getHeight2(localRoot ->left) -
                localRoot->getHeight2(localRoot->right )) > 1){
        if (localRoot->getHeight2(localRoot ->left->left) >=
                    localRoot->getHeight2(localRoot->left->right )){
            return true;
        }
    }
}

bool AVL::right_right_Imbalance(Node *localRoot) {
    if ((localRoot->getHeight2(localRoot ->right) -
                localRoot->getHeight2(localRoot->left )) > 1){
        if (localRoot->getHeight2(localRoot ->right->right) >=
                    localRoot->getHeight2(localRoot->right->left)){
            return true;
        }
    }
}


bool AVL::right_left_Imbalance(Node *localRoot) {
    if ((localRoot->getHeight2(localRoot ->right) -
                localRoot->getHeight2(localRoot->left))>1){
        if (localRoot->getHeight2(localRoot ->right->left) >
                    localRoot->getHeight2(localRoot->right->right)){
            return true;
        }
    }
}


bool AVL::left_right_Imbalance(Node *localRoot) {
    if ((localRoot->getHeight2(localRoot->left) -
            localRoot->getHeight2(localRoot->right)) > 1){
        if (localRoot->getHeight2(localRoot->left->right) >
                localRoot->getHeight2(localRoot->left->left )){
            return true;
        }
    }
}

void AVL::check_imbalance(Node *&localRoot){
    localRoot->updateHeight(localRoot);
    if (left_left_Imbalance(localRoot)) {
        rightRotate(localRoot);
    }
    if (right_right_Imbalance(localRoot)) {
        leftRotate(localRoot);
    }
    if (right_left_Imbalance(localRoot)) {
        rightRotate(localRoot->right);
        leftRotate(localRoot);
    }
    if (left_right_Imbalance(localRoot)) {
        leftRotate(localRoot->left);
        rightRotate(localRoot);
    }
//    localRoot->updateHeight(localRoot);
}