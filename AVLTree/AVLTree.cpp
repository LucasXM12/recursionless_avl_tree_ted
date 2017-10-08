// AVLTree.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <conio.h>
#include <iostream>

#include "Tree.h"

using namespace std;

int main() {
	Tree<int> aux;

	for (int i = 0; i < 11; i++)
		aux.addNode(i, i*i);

	cout << aux << endl << endl;
	cout << aux.minKey();

	_getch();

	return 0;
}

