// SeqSeqListCpp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <String>
#include"stdlib.h"
using namespace std;
#define SeqList_INIT_SIZE 30

template <typename ElemType>
struct LinkNode {
	ElemType data;
	LinkNode*next = NULL;
};

template <typename ElemType>
struct LinkList {
	int length = 0;
	LinkNode<ElemType> header;

	void printOut() {
		cout << "The LinkList is:" << endl;
		LinkNode<ElemType>*p = header.next;
		for (int i = 0; i < length; i++) {
			cout << p->data << " ";
			p = p->next;
			if (p == NULL)
				return;
		}
	}
};


template <typename ElemType>
struct SeqList {
	ElemType *items;
	int length;
	int capacity;

	SeqList() {
		capacity = SeqList_INIT_SIZE;
		items = new ElemType[capacity];
		if (items == NULL)
			throw "failed to new";
		length = 0;

	}

	~SeqList() {
			delete[]items;
	}

	void insertAt(int index, ElemType e) {
		if (index == capacity)
			throw"OVER FLOWED";
		for (int i = length; i > index;i--)
			items[i] = items[i - 1];
		items[index] = e;
		length++;
	}

	void queryElem(int index) {
		if (index > length || index <= 0)
			throw"CAN'T FIND IT";
		cout << items[index - 1] << endl;
	}

	void queryLoc(ElemType e) {
		for (int i = 0; i < length; i++)
			if (items[i] == e) {
				cout << "The Location is: " << i + 1 << endl;
				return;
			}
		cout << "CAN'T FIND IT" << endl;
	}

	void tanLinkList(LinkList<ElemType> &link) {
		if (link.header.next != NULL)
			throw"WARNING";
		if(items == NULL)
			throw"No SeqList";
		if (length == 0)
			throw"WARNING";
		for (int i = length - 1; i >= 0; i--) {
			LinkNode<ElemType> *p = new LinkNode<ElemType>();
			p->data = items[i];
			p->next = link.header.next;
			link.header.next = p;
			link.length++;
		}
	}

	void outPut() {
		for (int i = 0; i < length; i++)
			cout << items[i] << " ";
		cout << endl;
		cout << "length= " << length << endl;
	}
};


int main()
{
	try {
		SeqList<int> l1;
		LinkList<int> link1;
		l1.insertAt(0, 0);
		l1.insertAt(0, 1);
		l1.insertAt(0, 2);
		l1.insertAt(0, 3);
		l1.insertAt(0, 4);
		l1.insertAt(0, 5);
		l1.outPut();

		l1.queryElem(2);
		//l1.queryElem(9);

		l1.queryLoc(5);
		l1.queryLoc(0);
		l1.queryLoc(8);

		l1.tanLinkList(link1);
		link1.printOut();
	}
	catch (const char*msg) {
		cout << msg << endl;
	}

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
