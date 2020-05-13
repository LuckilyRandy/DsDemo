#pragma once
#include<iostream>
#include<memory.h>
#include"String.h"
using namespace std;
#define  M 10 //顺序表空间
#define  N 10 //单次开辟长度

template <typename ElemType>
struct SeqList {
	ElemType *items;
	int length;
	int capacity;

	SeqList(int c) {
		items = new ElemType[c];
		if (items == NULL)
			throw"failed to new";
		length = 0;
		capacity = c;
	}
	SeqList() {
		items = new ElemType[M];
		if (items == NULL)
			throw"failed to new";
		length = 0;
		capacity = M;
	}

	void resize(int c) {//resize函数，扩展空间
		ElemType *newitems = new ElemType[c];
		if (newitems == NULL)
			throw"failed to resize";
		memcpy(newitems,items,length*sizeof(ElemType));//借助新开辟的newitems开辟空间
		delete[]items;//把不用的原来的空间delete
		items = newitems;
	}
	
	void append(ElemType e) {//添加函数，在顺序表的末尾添加
		if (length == capacity) {
			capacity = capacity + N;
			resize(capacity);
			items[length++] = e;
		}
		else items[length++] = e;
	}

	void outPut() {
		for (int i = 0; i < length; i++)
			cout << items[i] ;
		cout << endl;
		cout << "length= " << length << endl;
	}

	void printOut() { //专门用于SeqList<String>的输出函数
		for (int i = 0; i < length; i++)
			cout << items[i] << " ";//每个字符串之间有空格
		cout << endl;
		cout << "length= " << length << endl;
	}

	void insertAt(int index, ElemType e) {
		if (index >= capacity) {
			capacity = capacity + N;
			resize(capacity);
		}
		for (int i = length; i > index; i--)
			items[i] = items[i - 1];
		items[index] = e;
		length++;
	}
	
	//void queryElem(int index) {
	//	if (index > length || index <= 0)
	//		throw"CAN'T FIND IT";
	//	cout << items[index - 1] << endl;
	//}

	//void queryLoc(ElemType e) {
	//	for (int i = 0; i < length; i++)
	//		if (items[i] == e) {
	//			cout << "The Location is: " << i + 1 << endl;
	//			return;
	//		}
	//	cout << "CAN'T FIND IT" << endl;
	//}

};
