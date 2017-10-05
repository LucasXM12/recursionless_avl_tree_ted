// AVLTree.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <conio.h>
#include <iostream>

#include "Tree.h"
#include "AVLTree.h"

using namespace std;

int main() {
	Tree<int> aux;

	for (int i = 0; i < 6; i++)
		aux.addNode(i, i*i);

	aux.setWithKey(3, 8);
	aux.delWithKey(2);

	aux[0] = 666;
	int a = aux[5];

	for (int i = 0; i < 6; i++)
		if (i != 2)
			cout << aux[i] << " ";

	_getch();

	return 0;
}

