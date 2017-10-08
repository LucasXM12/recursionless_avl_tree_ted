// AVLTree.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <conio.h>
#include <iostream>

#include "Tree.h"

using namespace std;

int main() {
	Tree<int> aux;

	try {
		for (int i = 0; i <= 9; i++) {
			aux.addNode(i, 0);
			aux.addNode(13 - i, 0);
			cout << i << " " << 13 - i << endl;
			cout << aux << endl;
		}
	}
	catch (exception e) {
	}

	aux.addNode(20, 0);

	cout << aux << endl;
	_getch();

	return 0;
}

