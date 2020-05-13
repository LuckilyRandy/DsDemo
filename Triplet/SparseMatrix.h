#pragma once
#include<iostream>
#include"SeqList.h"
#include<iomanip>
using namespace std;

template <typename ElemType>
struct Triplet {
	int row, col; //�����±� 
	ElemType e; //����
	Triplet() {} //�����ṩĬ�Ϲ��캯�����Ա㴴��������� 
	Triplet(int r, int c, ElemType v) {
		row = r; col = c; e = v;
	}
};

template <typename ElemType>
struct SparseMatrix :SeqList<Triplet<ElemType>> {
	int rows, cols;//���д�С 

	SparseMatrix(int r, int c, int n = 10) :SeqList<Triplet<ElemType>>(n) {//���캯�� 
		rows = r; cols = c;
	}

	int getIndex(int r, int c) {//�����ܾ�����±�ת��Ϊϡ������е��±꣬�Ա���� 
		//TODO���뽫�����˳����ң���Ϊ���ֲ��� 
		//�Ҳ�����ʱ�򣬷���ǡ�ñ�rc��Ĵ洢Ԫ�ص��±� 
		int i = 0;
		for (i = 0; i < this->length; i++) {
			Triplet<ElemType> &t = this->items[i];//ȡ���ã����ٶ��󿽱� 
			if (t.row > r || t.row == r && t.col >= c)
				break;
		}
		if (i == this->length)
			throw"NO VALUE";
		return i;
	}

	//int getIndex(int r, int c) {//���ֲ��ң��Ҳ�����ʱ�򣬷���ǡ�ñ�rc��Ĵ洢Ԫ�ص��±� 
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

	void get(int r, int c) {//��ȡԪ�� 
		int index = getIndex(r, c);
		if (index < this->length && this->items[index].row == r && this->items[index].col == c)
			cout << this->items[index].e << endl;
		else
			cout << ElemType() << endl;//�����ھͷ���Ĭ��ֵ 
	}

	void set(int r, int c, ElemType v) {//�޸�Ԫ�� 
		int index = getIndex(r, c);
		if (index < this->length && this->items[index].row == r && this->items[index].cols == c)
			this->items[index] = v;
		//TODO:����д����Ԫ��ʱ��Ӧ����ɾ������ 
		if (v == 0)
			this->deleteAt(index);
		else//��ǰ��ϡ������У�û�д洢r��c��Ԫ�أ������ֵ 
			this->insertAt(index, Triplet<ElemType>(r, c, v));
	}

	void output() {
		int k = 0;
		cout.setf(ios::right);//�Ҷ���
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				ElemType v = ElemType();//����ΪĬ��ֵ 
				if (k < this->length && i == this->items[k].row && j == this->items[k].col) {
					v = this->items[k].e;//�������Ԫ�أ��͸�ΪԪ��ֵ 
					k++;//һ����length������Ԫ�أ���K��������ÿ�ҵ�һ����k++ȥ�Ա���һ����ֱ���ҵ�items[length-1]Ϊֹ
				}
				cout << setw(4) << v;//�淶�����ʽ
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
		//TODO��ʵ����Ԫ�����Ŀ���ת�÷���
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