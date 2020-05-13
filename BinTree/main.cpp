#include <iostream>
#include"BinTree.h"
using namespace std;

int main() {//二叉树创建、遍历、重构和输出测试用例
	BinTree *tree; 
	int index=0; 
	//先序遍历创建二叉树
	//tree = BinTree::create("AB##CDF###E##", index); 
	//tree->output(); 

	//cout << "后序遍历顺序为："; 
	//tree->postOrder();//测试后序遍历结果

	//cout << endl<< "先序遍历顺序为：";
	//tree->preOrder();//测试先序序遍历结果

	//cout << endl << "中序遍历顺序为：";
	//tree->inOrder();//测试先序序遍历结果

	//delete tree; 
	//cout << endl; 

	////已知先序和中序，重构二叉树
	//tree = BinTree::rebuildByPreIn("abdgcefh", "dgbaechf", 8);
	//tree->output(); 

	//已知后序和中序，重构二叉树
	tree = BinTree::rebuildByPostIn("IJDKEBGHFCA", "IDJBKEACGFH", 11);
	tree->output();

	//测试求结点个数的函数
	cout << "结点个数为：" << tree->count() << endl;

	//测试左右子树互换函数
	tree->flipRL();
	tree->output();

	//测试求结点最大值的函数
	cout << "结点最大值为：" << tree->maxNode(tree->data) << endl;

	//BinTree bt('a');//测试输入含叶子结点空指针标记的方式创建二叉树
	//tree=bt.create();
	//tree->output();
	delete tree; 
	return 0; 
}