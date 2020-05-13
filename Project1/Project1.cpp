#include<iostream>
#include"Mytree.h"

int main() {
	Mytree tree;
	tree.insertNode(1);
	tree.insertNode(2, false);
	tree.insertNode(3, false);
	tree.insertNode(11, true);
	tree.insertNode(12, false);
	tree.insertNode(13, false);
	tree.travle();
	tree.deleteNode(0);
	tree.travle();

	Mytree* p = tree.getNodePos(13);
	p->showData();
	return 0;
}