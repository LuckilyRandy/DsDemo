// Map_cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<string.h>
using namespace std;
#define N 7 //地图区域数量 
#define M 4 //最多允许使用的颜色数量

template <typename ElemType>
struct MapFiller {
	ElemType *items;
	int capacity;
	int top = 0;
	bool map[N][N] = {
	{ 0, 1, 1, 1, 1, 1, 0 },//0
	{ 1, 0, 0, 0, 0, 1, 0 },//1
	{ 1, 0, 0, 1, 1, 0, 0 },//2
	{ 1, 0, 1, 0, 1, 1, 0 },//3
	{ 1, 0, 1, 1, 0, 1, 0 },//4
	{ 1, 1, 0, 1, 1, 0, 0 },//5
	{ 0, 0, 0, 0, 0, 0, 0 }//6
	};
	int color[M] = { 1,2,3,4 };//颜色数组

	MapFiller(int c) {
		capacity = c;
		items = new ElemType[capacity];
		if (items == NULL)
			throw "failed to new";
	}
	~MapFiller() {}
	void push(ElemType &e) {
		//TODO:	栈满检查和处理
		if (top == capacity)
			throw"OVERFLOW";
		items[top++] = e;
	}

	ElemType &pop() {
		if (top == 0)
			throw"POP FRPM EMPTY STACK";
		ElemType e = items[--top];
		items[top] = 0;
		return e;
	}

	bool anyConflict(int r) {
		int i;
		for (i = 0; i < N; i++)
			if (map[r][i] == 1)
				if (items[r] == items[i])
					return true;
		return false;
	}

	void printOut() {
		int i = 0;
		while (i < capacity) {
			cout << items[i] << " ";
			i++;
		}
	}

	void fillColor() {
		push(color[0]);
		int i = 0;
		while (top > 0 && top < N) {
			while (i < M) {
				push(color[i]);
				if (anyConflict(top - 1) == true) {
					i = (int)pop();
				}
				else {
					i = 0;
					break;
				}
			}
			if (i >= M) {//填M种颜色都不行，则回退
				i = (int)pop();
			}
		}
		if (top == N) {
			cout << "找到着色方案:" << endl;
			printOut();
		}
		else cout << "该地图不存在仅" << M << "种颜色的着色方案" << endl;
	}
};

int main()
{
	int capacity = N;
	try {
		MapFiller<int> map(capacity);
		map.fillColor();
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
