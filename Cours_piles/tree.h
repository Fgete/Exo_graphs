#pragma once
#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

// ------------ CLASSES ------------
template<class T> class binary_node {
protected:
	int id;
	T data;
public:
	binary_node* leftChild;
	binary_node* rightChild;

	binary_node();
	binary_node(const int& id);
	binary_node(const int& id, const T& data);
	~binary_node();

	void setId(const int& id);
	void setData(const T& data);
	int getId() const;
	T getData() const;
	void print() const;

	binary_node<T>* succ();
	binary_node<T>* pred();
};

template<class T> class binary_tree {
private:
	void treePrint(binary_node<T>* root);
	void setNewNode(binary_node<T>* currentNode, binary_node<T>* newNode);
	binary_node<T>* subExtractNode(binary_node<T>* node, const int key);
	binary_node<T>* subFindNode(binary_node<T>* root, const int key);
	void prefixedNav(binary_node<T>* node);
	void postfixedNav(binary_node<T>* node);
	int subDepth(binary_node<T>* root) const;
	int subCount(binary_node<T>* root) const;
	int subBalance(binary_node<T>* root) const;
protected:
	int length;
public:
	binary_node<T>* root;

	binary_tree();
	binary_tree(binary_node<T>* root);
	~binary_tree();

	int getLength() const;
	void setRoot(binary_node<T>* root);
	void addNode(binary_node<T>* node);
	binary_node<T>* extractNode(binary_node<T>* node, const int key);
	binary_node<T>* findNode(const int key);
	int depth() const;
	int balance() const;
	void doBalance();
	void print();
};

// ------------ FUNCTIONS ------------
template<class T>
inline binary_node<T>::binary_node()
{
	this->id = -1;
	this->data = NULL;
	this->leftChild = nullptr;
	this->rightChild = nullptr;
}

template<class T>
inline binary_node<T>::binary_node(const int& id)
{
	this->id = id;
	this->data = NULL;
	this->leftChild = nullptr;
	this->rightChild = nullptr;
}

template<class T>
inline binary_node<T>::binary_node(const int& id, const T& data)
{
	this->id = id;
	this->data = data;
	this->leftChild = nullptr;
	this->rightChild = nullptr;
}

template<class T>
inline binary_node<T>::~binary_node()
{
}

template<class T>
inline void binary_node<T>::setId(const int& id)
{
	this->id = id;
}

template<class T>
inline void binary_node<T>::setData(const T& data)
{
	this->data = data;
}

template<class T>
inline int binary_node<T>::getId() const
{
	return this->id;
}

template<class T>
inline T binary_node<T>::getData() const
{
	return this->data;
}

template<class T>
inline void binary_node<T>::print() const
{
	cout << this->id << " : " << this->data << endl;
}

template<class T>
inline binary_node<T>* binary_node<T>::succ()
{
	binary_node<T>* current = this;
	while (current->leftChild != nullptr)
		current = current->leftChild;
	return current;
}

template<class T>
inline binary_node<T>* binary_node<T>::pred()
{
	binary_node<T>* current = this;
	while (current->rightChild != nullptr)
		current = current->rightChild;
	return current;
}

template<class T>
inline void binary_tree<T>::treePrint(binary_node<T>* root)
{
	if (root == nullptr) return;
	cout << root->getId() << " : " << root->getData() << endl;
	treePrint(root->leftChild);
	treePrint(root->rightChild);
}

template<class T>
inline void binary_tree<T>::setNewNode(binary_node<T>* currentNode, binary_node<T>* newNode)
{
	if (currentNode->getId() > newNode->getId()) {
		if (currentNode->leftChild != nullptr)
			setNewNode(currentNode->leftChild, newNode);
		else
			currentNode->leftChild = newNode;
	}
	else {
		if (currentNode->rightChild != nullptr)
			setNewNode(currentNode->rightChild, newNode);
		else
			currentNode->rightChild = newNode;
	}
}

template<class T>
inline binary_node<T>* binary_tree<T>::subExtractNode(binary_node<T>* node, const int key)
{
	if (node == nullptr) return nullptr;

	if (key < node->getId())
		node->leftChild = extractNode(node->leftChild, key);
	else if (key > node->getId())
		node->rightChild = extractNode(node->rightChild, key);
	else {
		if (node->leftChild == nullptr) {
			binary_node<T>* temp = node->rightChild;
			node = nullptr;
			return temp;
		}
		else if (node->rightChild == nullptr) {
			binary_node<T>* temp = node->leftChild;
			node = nullptr;
			return temp;
		}

		binary_node<T>* succ = node->rightChild->succ();
		// binary_node<T>* pred = node->leftChild->pred;

		node->setId(succ->getId());

		node->rightChild = extractNode(node->rightChild, succ->getId());
		// node->leftChild = extractNode(node->leftChild, succ->getId());
	}

	return node;
}

template<class T>
inline binary_node<T>* binary_tree<T>::subFindNode(binary_node<T>* root, const int key)
{
	if (this->length == 0) return nullptr;

	if (root->getId() == key) return root;
	else {
		if (root->leftChild != nullptr)
			if (subFindNode(root->leftChild, key) != nullptr)
				return subFindNode(root->leftChild, key);
		if (root->rightChild != nullptr)
			if (subFindNode(root->rightChild, key) != nullptr)
				return subFindNode(root->rightChild, key);
		return nullptr;
	}
}

template<class T>
inline void binary_tree<T>::prefixedNav(binary_node<T>* node)
{
	if (node == nullptr) return;

	// Do something

	prefixedNav(node->leftChild);
	prefixedNav(node->rightChild);
}

template<class T>
inline void binary_tree<T>::postfixedNav(binary_node<T>* node)
{
	if (node == nullptr) return;

	prefixedNav(node->leftChild);
	prefixedNav(node->rightChild);
	
	// Do something
}

template<class T>
inline int binary_tree<T>::subDepth(binary_node<T>* root) const
{
	if (root == nullptr) return -1;

	int depthLeft, depthRight, depthVal;
	depthLeft = subDepth(root->leftChild);
	depthRight = subDepth(root->rightChild);
	depthVal = 1 + (depthLeft > depthRight ? depthLeft : depthRight);

	return depthVal;
}

template<class T>
inline int binary_tree<T>::subCount(binary_node<T>* root) const
{
	if (root == nullptr) return 0;
	return 1 + subCount(root->leftChild) + subCount(root->rightChild);
}

template<class T>
inline int binary_tree<T>::subBalance(binary_node<T>* root) const
{
	if (root == nullptr) return 0;
	return subCount(root->rightChild) - subCount(root->leftChild);
}

template<class T>
inline binary_tree<T>::binary_tree()
{
	this->length = 0;
	this->root = nullptr;
}

template<class T>
inline binary_tree<T>::binary_tree(binary_node<T>* root)
{
	this->length = 0;
	this->root = root;
}

template<class T>
inline binary_tree<T>::~binary_tree()
{
}

template<class T>
inline int binary_tree<T>::getLength() const
{
	return this->length;
}

template<class T>
inline void binary_tree<T>::setRoot(binary_node<T>* root)
{
	this->root = root;
}

template<class T>
inline void binary_tree<T>::addNode(binary_node<T>* node)
{
	// Add an ID to the new node
	if (node->getId() < 0)
		node->setId(this->length);

	// Verify if there is root (and set root if not)
	if (root == nullptr)
		this->root = node;
	else
		setNewNode(this->root, node);

	this->length++;
}

template<class T>
inline binary_node<T>* binary_tree<T>::extractNode(binary_node<T>* node, const int key)
{
	if (this->length == 0) return nullptr;

	this->length--;
	return subExtractNode(node, key);
}

template<class T>
inline binary_node<T>* binary_tree<T>::findNode(const int key)
{
	return subFindNode(this->root, key);
}

template<class T>
inline int binary_tree<T>::depth() const
{
	return subDepth(this->root);
}

template<class T>
inline int binary_tree<T>::balance() const
{
	return subBalance(this->root);
}

template<class T>
inline void binary_tree<T>::doBalance()
{
	if (root == nullptr) return;
	else {
		if (subBalance(root) == -2 && subBalance(root->leftChild) == -1) { // DO LEFT TURN
			// SET
			binary_node<T>* Y = root;
			binary_node<T>* X = Y->rightChild;
			binary_node<T>* beta = X->leftChild;
			// RESET
			root = X;
			X->leftChild = Y;
			Y->rightChild = beta;
		}
		else if (subBalance(root) == 2 && subBalance(root->rightChild) == 1) { // DO RIGHT TURN
			// SET
			binary_node<T>* Y = root;
			binary_node<T>* X = Y->leftChild;
			binary_node<T>* beta = X->rightChild;
			// RESET
			root = X;
			X->rightChild = Y;
			Y->leftChild = beta;
		}
		else if (subBalance(root) == 2 && subBalance(root->rightChild) == -1) { // DO RIGHT & LEFT TURN
			// SET
			binary_node<T>* Z = root;
			binary_node<T>* Y = Z->rightChild;
			binary_node<T>* X = Y->leftChild;
			binary_node<T>* beta = X->leftChild;
			binary_node<T>* gamma = X->rightChild;
			// RESET
			root = X;
			X->leftChild = Z;
			X->rightChild = Y;
			Y->leftChild = gamma;
			Z->rightChild = beta;
		}
		else if (subBalance(root) == -2 && subBalance(root->leftChild) == 1) { // DO LEFT & RIGHT TURN
			// SET
			binary_node<T>* Z = root;
			binary_node<T>* Y = Z->leftChild;
			binary_node<T>* X = Y->rightChild;
			binary_node<T>* beta = X->leftChild;
			binary_node<T>* gamma = X->rightChild;
			// RESET
			root = X;
			X->leftChild = Y;
			X->rightChild = Z;
			Y->rightChild = beta;
			Z->leftChild = gamma;
		}
	}
}

template<class T>
inline void binary_tree<T>::print()
{
	treePrint(this->root);
	cout << endl;
}