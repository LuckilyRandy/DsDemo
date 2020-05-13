// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include"SparseMatrix.h"
#include"SeqList.h"
using namespace std;
#define ROW  6 //行
#define COL  6 //列

int main()
{
	try {
		//测试稀疏矩阵及其运算 
		SparseMatrix<int> m(ROW, COL);
		m.append(Triplet<int>(0, 1, 12));
		m.append(Triplet<int>(0, 2, 9));
		m.append(Triplet<int>(2, 0, -3));
		m.append(Triplet<int>(2, 4, 14));
		m.append(Triplet<int>(3, 2, 24));
		m.append(Triplet<int>(4, 1, 18));
		m.append(Triplet<int>(5, 0, 15));
		m.append(Triplet<int>(5, 3, -7));
		m.output();//测试矩阵打印函数

		cout << m.getIndex(0, 1) << endl;
		m.get(0, 1);//测试获取元素值函数

		//cout << m.getIndex(2, 4) << endl;//测试获取下标函数
		//cout << m.getIndex(5, 4) << endl;

		//int *num = m.get_num_cols();
		//int *cpot = m.get_cpot_cols();
		//m.transpose();//测试快速转置 
	}
	catch (const char* msg) {
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
