#pragma once

#include "stdafx.h"

#include <string>
#include <stdexcept>

#ifndef TREE_H
#define TREE_H

#define max(a, b) (a > b ? a : b)
#define height(n) (!n ? 0 : n->height) 
#define height_update(n) (max(height(n->left), height(n->right)) + 1)
#define balance_factor(n) (!n ? 0 : (height(n->left) - height(n->right)))

using namespace std;

template<class dataType>
class Tree {
private:
	typedef struct node {
		int key;

		dataType data;

		int height;

		node* left;
		node* right;
	} node;

	node* root;

	void delTree(node*&);

	string toString(const node*&) const;

	node*& minKey(node*&) const;
	node*& maxKey(node*&) const;

	bool existsKey(const int&, const node*&) const;

	node*& leftRotate(node*&);
	node*& rightRotate(node*&);

	node*& newNode(const int&, const dataType&) const;

	node*& addNode(node*&, const int&, const dataType&);
	node* delWithKey(node*&, const int&);
	dataType& getWithKey(node*&, const int&);
	void setWithKey(node*&, const int&, const dataType&);

public:
	Tree();
	virtual ~Tree();

	string toString() const;

	void addNode(const int&, const dataType&);
	void delWithKey(const int&);
	dataType& getWithKey(const int&);
	void setWithKey(const int&, const dataType&);

	int minKey() const;
	int maxKey() const;

	bool existsKey(const int&) const;

	void delMinKey();
	void delMaxKey();

	dataType& operator[](const int&);
	template<typename dataType> friend ostream& operator<<(ostream&, const Tree<dataType>&);
};

template<class dataType>
Tree<dataType>::Tree() {
	this->root = NULL;
}

template<class dataType>
Tree<dataType>::~Tree() {
	if (this->root)
		delTree(this->root);
}

template<class dataType>
void Tree<dataType>::delTree(node*& root) {
	if (root->left)
		delTree(root->left);

	if (root->right)
		delTree(root->right);

	delete root;
}

template<class dataType>
string Tree<dataType>::toString() const {
	if (!this->root)
		return "null";

	return toString(this->root);
}

template<class dataType>
string Tree<dataType>::toString(const node*& root) const {
	string ret;

	if (root->left)
		ret = "(" + toString(root->left) + ")<-";

	ret += "[" + to_string(root->key) + ':' + to_string(root->data) + "]";

	if (root->right)
		ret += "->(" + toString(root->right) + ")";

	return ret;
}

template<class dataType>
typename int Tree<dataType>::minKey() const {
	if (!this->root)
		throw exception("Empty tree");

	return minKey(this->root)->key;
}

template<class dataType>
typename Tree<dataType>::node*& Tree<dataType>::minKey(node*& root) const {
	if (root->left)
		return minKey(root->left);

	return root;
}

template<class dataType>
int Tree<dataType>::maxKey() const {
	if (!this->root)
		throw exception("Empty tree");

	return maxKey(this->root)->key;
}

template<class dataType>
typename Tree<dataType>::node*& Tree<dataType>::maxKey(node*& root) const {
	if (root->right != NULL)
		return maxKey(root->right);

	return root;
}

template<class dataType>
bool Tree<dataType>::existsKey(const int& key) const {
	if (!this->root)
		return false;

	return existsKey(key, this->root);
}

template<class dataType>
bool Tree<dataType>::existsKey(const int& key, const node*& root) const {
	if (key == root->key)
		return true;
	else if (key < root->key)
		return root->left ? existsKey(key, root->left) : false;
	else
		return root->right ? existsKey(key, root->right) : false;
}

template<typename dataType>
typename Tree<dataType>::node*& Tree<dataType>::leftRotate(node*& root) {
	node* y = root->right;
	node* T2 = y->left;

	//Update conections:
	y->left = root;
	root->right = T2;

	//Update heights:
	root->height = height_update(root);
	y->height = height_update(y);

	return y;
}

template<typename dataType>
typename Tree<dataType>::node*& Tree<dataType>::rightRotate(node*& root) {
	node* x = root->left;
	node* T2 = x->right;

	//Update conections:
	x->right = root;
	root->left = T2;

	//Update heights:
	root->height = height_update(root);
	x->height = height_update(x);

	return x;
}

template<class dataType>
typename Tree<dataType>::node*& Tree<dataType>::newNode(const int& key, const dataType& data) const {
	node* ret = new node();

	ret->key = key;
	ret->data = data;
	ret->height = 1;
	ret->left = NULL;
	ret->right = NULL;

	return ret;
}

template<typename dataType>
void Tree<dataType>::addNode(const int& key, const dataType& data) {
	this->root = addNode(this->root, key, data);
}

template<typename dataType>
typename Tree<dataType>::node*& Tree<dataType>::addNode(node*& root, const int& key, const dataType& data) {
	//Normal insertion:--------------------------- 
	if (root == NULL)
		return newNode(key, data);

	if (key < root->key)
		root->left = addNode(root->left, key, data);
	else if (key > root->key)
		root->right = addNode(root->right, key, data);

	//Update height:---------------------------
	root->height = height_update(root);

	//Get balance factor:---------------------------
	int balance = balance_factor(root);

	//Balance this sub tree:---------------------------
	//LL Case:
	if (balance > 1 && key < root->left->key)
		return rightRotate(root);

	//RR Case:
	if (balance < -1 && key > root->right->key)
		return leftRotate(root);

	//LR Case:
	if (balance > 1 && key > root->left->key) {
		root->left = leftRotate(root->left);

		return rightRotate(root);
	}

	//RL Case:
	if (balance < -1 && key < root->right->key) {
		root->right = rightRotate(root->right);

		return leftRotate(root);
	}

	//If is balanced:
	return root;
}

template<typename dataType>
void Tree<dataType>::delWithKey(const int& key) {
	this->root = delWithKey(this->root, key);
}

template<typename dataType>
typename Tree<dataType>::node* Tree<dataType>::delWithKey(node*& root, const int& key) {
	//Normal deletion:---------------------------
	if (!root)
		return root;
	else if (key < root->key) //The node is on the left sub tree:
		root->left = delWithKey(root->left, key);
	else if (key > root->key) //The node is on the right sub tree:
		root->right = delWithKey(root->right, key);
	else { //The node is the current one:
		if (!root->left || !root->right) { //One or none children:
			node* aux = root->left ? root->left : root->right;

			//No child:
			if (!aux) {
				aux = root;
				root = NULL;
			} else //One child:
				*root = *aux;

			delete aux;
		} else { //Two children:
			node* aux = minKey(root->right);

			root->key = aux->key;

			root->right = delWithKey(root->right, aux->key);
		}
	}

	if (!root)
		return NULL;

	//Update height:---------------------------
	root->height = height_update(root);

	//Get balance factor:---------------------------
	int balance = balance_factor(root);

	//Balance this sub tree:---------------------------
	//LL Case:
	if (balance > 1 && balance_factor(root->left) >= 0)
		return rightRotate(root);

	//LR Case:
	if (balance > 1 && balance_factor(root->left) < 0) {
		root->left = leftRotate(root->left);

		return rightRotate(root);
	}

	//RR Case:
	if (balance < -1 && balance_factor(root->right) <= 0)
		return leftRotate(root);

	//RL Case:
	if (balance < -1 && balance_factor(root->right) > 0) {
		root->right = rightRotate(root->right);

		return leftRotate(root);
	}

	//If is balanced:
	return root;
}

template<typename dataType>
void Tree<dataType>::delMinKey() {
	this->root = delWithKey(this->root, minKey());
}

template<typename dataType>
void Tree<dataType>::delMaxKey() {
	this->root = delWithKey(this->root, maxKey());
}

template<typename dataType>
dataType& Tree<dataType>::getWithKey(const int& key) {
	return getWithKey(this->root, key);
}

template<typename dataType>
dataType& Tree<dataType>::getWithKey(node*& root, const int& key) {
	if (key < root->key)
		if (root->left)
			return getWithKey(root->left, key);
		else
			throw out_of_range("Index out of range");

	if (key > root->key)
		if (root->right)
			return getWithKey(root->right, key);
		else
			throw out_of_range("Index out of range");

	return root->data;
}

template<typename dataType>
void Tree<dataType>::setWithKey(const int& key, const dataType& data) {
	setWithKey(this->root, key, data);
}

template<typename dataType>
void Tree<dataType>::setWithKey(node*& root, const int& key, const dataType& data) {
	if (key < root->key)
		if (root->left)
			setWithKey(root->left, key, data);
		else
			return;

	if (key > root->key)
		if (root->right)
			setWithKey(root->right, key, data);
		else
			return;

	if (key == root->key)
		root->data = data;
}

template<typename dataType>
ostream& operator<<(ostream& os, const Tree<dataType>& tree) {
	return os << tree.toString();
}

template<typename dataType>
dataType& Tree<dataType>::operator[](const int& key) {
	return getWithKey(key);
}

#endif // TREE_H