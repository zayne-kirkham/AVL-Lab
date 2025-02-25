//YOU MAY NOT MODIFY THIS DOCUMENT
/*
*/
#pragma once
#include <iostream>
#include "NodeInterface.h"

using namespace std;

class Node: NodeInterface {
friend class AVL;

private:
    int value;
    Node* left = NULL;
    Node* right = NULL;
    int height = 0;

public:
    Node(int _data){
        value = _data;
    }

    ~Node(){}

	/*
	* Returns the data stored in this node
	*
	* @return the data stored in this node.
	*/
	int getData() const;

	/*
	* Returns the left child of this node or null if empty left child.
	*
	* @return the left child of this node or null if empty left child.
	*/
	NodeInterface * getLeftChild() const;

	/*
	* Returns the right child of this node or null if empty right child.
	*
	* @return the right child of this node or null if empty right child.
	*/
	NodeInterface * getRightChild() const;

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
	int getHeight();

    int getHeight2(Node *localRoot);

    void updateHeight(Node *&localRoot);
};
