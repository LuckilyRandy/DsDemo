#pragma once
#include<iostream>
#include"SeqList.h"
#include<iomanip>
using namespace std;

template <typename ElemType>
struct Triplet {
	int row, col; //行列下标 
	ElemType e; //数据
	Triplet() {} //必须提供默认构造函数，以便创建对象矩阵 
	Triplet(int r, int c, ElemType v) {
		row = r; col = c; e = v;
	}
};

template <typename ElemType>
struct SparseMatrix :SeqList<Triplet<ElemType>> {
	int rows, cols;//行列大小 

	SparseMatrix(int r, int c, int n = 10) :SeqList<Triplet<ElemType>>(n) {//构造函数 
		rows = r; cols = c;
	}

	int getIndex(int r, int c) {//将稠密矩阵的下标转换为稀疏矩阵中的下标，以便访问 
		//TODO：请将下面的顺序查找，改为二分查找 
		//找不到的时候，返回恰好比rc大的存储元素的下标 
		int i = 0;
		for (i = 0; i < this->length; i++) {
			Triplet<ElemType> &t = this->items[i];//取引用，减少对象拷贝 
			if (t.row > r || t.row == r && t.col >= c)
				break;
		}
		if (i == this->length)
			throw"NO VALUE";
		return i;
	}

	//int getIndex(int r, int c) {//二分查找，找不到的时候，返回恰好比rc大的存储元素的下标 
	//	int low = 0;
	//	int high = this->length;
	//	int mid = 0;
	//	Triplet<ElemType> &t = this->items[mid];
	//	while (low < high) {
	//		mid = (low + high) / 2;
	//		t = this->items[mid];
	//		if (t.row == r && t.col == c)
	//			return mid;
	//		if (t.row > r || t.row == r && t.col > c)
	//			high = mid - 1;
	//		if (t.row == r && t.col < c)
	//			low = mid + 1;
	//		if (t.row < r)
	//			low = mid + 1;
	//	}
	//	if (high == this->length)
	//		throw"NO VALUE";
	//	return high;
	//}

	void get(int r, int c) {//获取元素 
		int index = getIndex(r, c);
		if (index < this->length && this->items[index].row == r && this->items[index].col == c)
			cout << this->items[index].e << endl;
		else
			cout << ElemType() << endl;//不存在就返回默认值 
	}

	void set(int r, int c, ElemType v) {//修改元素 
		int index = getIndex(r, c);
		if (index < this->length && this->items[index].row == r && this->items[index].cols == c)
			this->items[index] = v;
		//TODO:增加写入零元素时，应该做删除处理 
		if (v == 0)
			this->deleteAt(index);
		else//当前的稀疏矩阵中，没有存储r行c列元素，则插入值 
			this->insertAt(index, Triplet<ElemType>(r, c, v));
	}

	void output() {
		int k = 0;
		cout.setf(ios::right);//右对齐
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				ElemType v = ElemType();//设置为默认值 
				if (k < this->length && i == this->items[k].row && j == this->items[k].col) {
					v = this->items[k].e;//如果存在元素，就改为元素值 
					k++;//一共有length个非零元素，用K来遍历，每找到一个，k++去对比下一个，直到找到items[length-1]为止
				}
				cout << setw(4) << v;//规范输出格式
			}
			cout << endl;
		}
		cout << endl;
	}

	int* get_num_cols() {
		int *num = new int[cols];
		int i;
		int j;
		for (i = 0; i < cols; i++)
			num[i] = 0;
		i = 0;
		while (i < this->length) {
			j = this->items[i].col;
			num[j]++;
			i++;
		}
		return num;
	}

	int* get_cpot_cols() {
		int *num = get_num_cols();
		int i;
		int *cpot = new int[cols];
		cpot[0] = 0;
		for (i = 1; i < cols; i++) {
			cpot[i] = cpot[i - 1] + num[i-1];
		}
		return cpot;
	}
	void transpose() {
		//TODO：实现三元组矩阵的快速转置方法
		int *num = get_num_cols();
		int *cpot = get_cpot_cols();
		SparseMatrix<int> t(cols, rows);
		t.length = this->length;
		int l = 0;
		int pos;
		while (l < this->length) {
			pos = cpot[this->items[l].col];
			t.items[pos].row = this->items[l].col;
			t.items[pos].col = this->items[l].row;
			t.items[pos].e = this->items[l].e;
			cpot[this->items[l].col]++;
			l++;
		}
		t.output();
	}
};