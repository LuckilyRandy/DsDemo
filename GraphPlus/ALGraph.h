#pragma once
#include<iostream>
using namespace std;

//弧结点
struct ArcNode {
	int adjvex;		//邻接点域，存放与其邻接的点在表头数组中的位置
	ArcNode *nextarc;//指针域，指向下一条边或弧
	int info;//弧自带的信息

	ArcNode(int adj, int w) {
		adjvex = adj;
		info = w;
		nextarc = NULL;
	}

	void output() {
		cout << "->" << "(" << adjvex << "," << info << ")";
	}
};

//顶点结点
struct VexNode {
	char data;//存放顶点信息
	ArcNode *firstarc;//指示第一个邻接点
	int set = 0;//顶点编号
	VexNode() {
		firstarc = NULL;
	}

	~VexNode() {}

	void output() {
		cout << "顶点" << data;//顶点的打印
		ArcNode *p = firstarc;
		while (p) {
			p->output();
			p = p->nextarc;//弧的打印
		}
		cout << endl;
	}

	void addArc(int adj, int w) {
		//向顶点添加弧
		ArcNode *p = new ArcNode(adj, w);
		p->nextarc = firstarc;//链表的插入
		firstarc = p;
	}
};

struct Edge//边
{
	int v1;//v1顶点
	int v2;//v2顶点
	int weight;//权重
};

struct ALGraph {
	VexNode *vertices;
	int vexnum;//顶点数量
	int kind;//图的种类，0-无向图，1-有向图
	ALGraph(char *names, int k = 1) {
		kind = k;
		vexnum = strlen(names);
		vertices = new VexNode[vexnum];
		for (int i = 0; i < vexnum; i++) {
			vertices[i].data = names[i];
		}
	}

	~ALGraph() {}

	void output() {
		//输出图
		for (int i = 0; i < vexnum; i++)
			vertices[i].output();
	}

	void addArc(int tail, int head, int w = 0) {
		//向图添加弧
		vertices[tail].addArc(head, w);
		if (kind == 0)//如果是无向图
			vertices[head].addArc(tail, w);//双向连通
	}

};