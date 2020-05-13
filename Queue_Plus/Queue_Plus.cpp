// Queue.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string.h>
using namespace std;

struct Point {
	int x, y;
	int F, G, H;
	Point() {//默认构造函数 
		x = 0; y = 0;
	}
	Point(int x, int y) {//带参构造函数 
		this->x = x;
		this->y = y;
	}
	int getF() {
		return G + H;
	}
	int getG(Point src) {
		if (src.x + src.y - x - y != 1)
			return 15;
		return 10;
	}
	int getH(Point dst) {
		return 10 * (dst.x + dst.y - x - y);
	}
	void ouput() {//TODO:实现坐标打印 
		cout << "(" << x << "," << y << ")";
	}
	Point move(Point vector) {//坐标偏移 
		return Point(x + vector.x, y + vector.y);
	}
};

#define N 10 //迷宫大小 
#define M 8 //图的联通数，"4-联通"对应“上下左右” //迷宫地图字符板 
char map[N][N + 1] = {
	"XXXXXXXXXX",
	"X  X   X X",
	"X  X   X X",
	"X    XX  X",
	"X XXX    X",
	"X   X X  X",
	"X X   X  X",
	"X XXX XX X",
	"XX       X",
	"XXXXXXXXXX",
};

Point direction[M] = {
	Point{ 0, -1 }, //上 
	Point{ 0, 1 }, //下 
	Point{ -1, 0 }, //左 
	Point{ 1, 0 }, //右
	Point{ -1, -1 },
	Point{ 1, -1 },
	Point{ -1, 1 },
	Point{ 1, 1 }
};

Point previous[N][N + 1];

struct Queue {
	Point *points;
	int capacity;
	int head, tail;
	Queue() {
		capacity = 100;
		head = 0;
		tail = 0;
		points = new Point[capacity];
		if (points == NULL)
			throw"failed to new";
	}

	bool isEmpty() {
		if (head == tail)
			return true;
		return false;
	}

	void enqueue(Point &point) {
		if (tail == capacity)
			throw"OVERFLOW";
		points[tail++] = point;
	}

	Point dequeue() {
		if (isEmpty() == true)
			throw"Empty Queue!";
		return points[head++];
	}
};

//相邻点排序
Point open[M];
void Astar(Point src, Point dst, Point pt) {
	int i, j;
	for (i=0; i < M; i++) {
		open[i] = pt.move(direction[i]);
		char ch = map[open[i].y][open[i].x];
		if (ch == ' ') {
			open[i].G = open[i].getG(src);
			open[i].H = open[i].getH(dst);
			open[i].F = open[i].getF();
		}
		else
			open[i].F = -1;
	}
	Point middle;
	for(i=0;i<M-1;i++)
		for (j = i + 1; j < M; j++)
			if (open[i].F > open[j].F) {
				middle = open[i];
				open[i] = open[j];
				open[j] = middle;
			}
}

void printPath(Point &c) {
	//TODO:从c一路回退，直到碰到A终止，打印路径坐标 
	Point pt = previous[c.y][c.x];
	cout << "B";
	while (map[pt.y][pt.x] != 'A') {
		cout << " -> ";
		pt.ouput();
		pt = previous[pt.y][pt.x];
	}
	cout << " -> A" << endl;
}

void findPath(Point src, Point dst) {
	map[src.y][src.x] = 'A';//出发点A
	map[dst.y][dst.x] = 'B';//目的地B
	Point open[M];
	Queue Q;
	Q.enqueue(src);
	while (Q.isEmpty() == false) {
		Point pt = Q.dequeue();//取出一点，进行处理 
		Astar(src, dst, pt);
		for (int i = 0; i < M; i++)//遍历M个联通方向 
		{
			if (open[i].F != -1) {
				Point c = open[i];
				char ch = map[c.y][c.x];
				if (ch == ' ') {//如果该位置可以进入
					previous[c.y][c.x] = pt;//标记c点的前驱点为pt点
					map[c.y][c.x] = 'X';
					Q.enqueue(c);
				}
				if (ch == 'B') {
					previous[c.y][c.x] = pt;//标记c点的前驱点为pt点
					cout << "找到出口B，路径是：";
					printPath(c);
					return;
				}
			}
		}
	}
	cout << "A和B之间没有路径！" << endl;
}

int main()
{
	try {
		findPath(Point(1, 1), Point(8, 8));
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