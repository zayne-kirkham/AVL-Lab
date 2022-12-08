#pragma once

#include "AVLInterface.h"
#include "Node.h"

using namespace std;

class AVL: AVLInterface {
    friend class Node;
protected:
    Node* root = NULL;
public:
	AVL() {}

	 ~AVL() {
        clear();
    }

	//Please note that the class that implements this interface must be made
	//of objects which implement the NodeInterface

	/*
	* Returns the root node for this tree
	*
	* @return the root node for this tree.
	*/
	NodeInterface * getRootNode() const;

	/*
	* Attempts to add the given int to the AVL tree
	* Rebalances the tree if data is successfully added
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool add(int data);

	/*
	* Attempts to remove the given int from the AVL tree
	* Rebalances the tree if data is successfully removed
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	bool remove(int data);

	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	void clear();

    bool insert(int _val, Node *&localRoot);

    bool remove_val(int _val, Node *&localRoot);

    Node* inOrderPredecessor(Node *&localRoot);

    void remove_everything(Node *&localRoot);

    void leftRotate(Node *& localRoot);

    void rightRotate(Node *& localRoot);

    bool left_left_Imbalance(Node *localRoot);

    bool right_right_Imbalance(Node *localRoot);

    bool right_left_Imbalance(Node *localRoot);

    bool left_right_Imbalance(Node *localRoot);

    void check_imbalance(Node*& localRoot);
};
