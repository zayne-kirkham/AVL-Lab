//YOU MAY NOT MODIFY THIS DOCUMENT
/*
*/
#pragma once
#include <iostream>
#include "Node.h"

using namespace std;


/*
* Returns the data stored in this node
*
* @return the data stored in this node.
*/
int Node::getData() const{
    return value;
}

/*
* Returns the left child of this node or null if empty left child.
*
* @return the left child of this node or null if empty left child.
*/
NodeInterface* Node::getLeftChild() const{
    return left;
}

/*
* Returns the right child of this node or null if empty right child.
*
* @return the right child of this node or null if empty right child.
*/
NodeInterface* Node::getRightChild() const{
    return right;
}

/*
* Returns the height of this node. The height is the number of nodes
* along the longest path from this node to a leaf.  While a conventional
* interface only gives information on the functionality of a class and does
* not comment on how a class should be implemented, this function has been
* provided to point you in the right direction for your solution.  For an
* example on height, see page 448 of the text book.
*
* @return the height of this tree with this node as the local root.
*/
int Node::getHeight(){
    return height;
}

int Node::getHeight2(Node *localRoot){
    if (localRoot == NULL)
        return(-1);
    return localRoot->height;
}

void Node::updateHeight(Node *&localRoot){
    int left = getHeight2(localRoot->left);
    int right = getHeight2(localRoot->right);

    localRoot-> height = max(left, right) + 1;
    return;
}

