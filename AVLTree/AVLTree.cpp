// AVLTree.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <conio.h>
#include <iostream>

#include "Tree.h"

using namespace std;

int main() {
	Tree<int> aux;

	for (int i = 0; i < 6; i++)
		aux.addNode(i, 0);

	aux.delWithKey(4);
	aux.delWithKey(1);
	aux.delWithKey(3);

	cout << aux << endl;
	_getch();

	return 0;
}

