#include <iostream>
#include"ALGraph.h"
using namespace std;
#define MAX_VERTEX_NUM 6
#define MAX_EDGE_NUM 10
#define INFINITY 100   //根据题目，将无穷远设置为100

void Prim(ALGraph &G) {
	int adjvex[MAX_VERTEX_NUM] = { 0 };
	int lowcost[MAX_VERTEX_NUM];
	bool U[MAX_VERTEX_NUM];	//已选顶点集合
	memset(U, 0, sizeof(U));
	//TODO:请实现Prim算法，约40行
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
		lowcost[i] = INFINITY;//lowcost数组都初始化为无穷远

	//第一次，先把第0个顶点加入U中
	int i = 0;
	int flag = 1;//定义一个标志位，表示顶点是否都已经加入U

	while (flag) {
		U[i] = 1;//把第一个顶点放进U中
		lowcost[i] = 0;//顶点到自身的lowcost设为0
		ArcNode *p = G.vertices[i].firstarc;//指针p指向图G的第一个顶点的第一个弧结点
		while (p) {//如果存在邻接的弧结点，则更新双表
			if (lowcost[p->adjvex] > p->info) {
				adjvex[p->adjvex] = i;
				lowcost[p->adjvex] = p->info;
			}
			p = p->nextarc;//p指向下一个邻接结点
		}
		//更新完成之后，要选出lowcost最小的结点放入U中
		int j = 0;
		while (lowcost[j] == 0)
			j++;
		int min = j;
		for (j; j < MAX_VERTEX_NUM; j++) {
			if (lowcost[j] == 0)
				continue;
			if (lowcost[min] > lowcost[j])
				min = j;
		}
		i = min;//找到lowcost最小的结点
		int k = 0;
		for (k = 0; k < MAX_VERTEX_NUM; k++) {//检查U是否装完
			if (U[k] == 0) break;
		}
		if (k == MAX_VERTEX_NUM)
			flag = 0;
	}
	i = 1;//output
	while (i<MAX_VERTEX_NUM) {
		ArcNode *p = G.vertices[i].firstarc;
		while (p) {
			if (p->adjvex == adjvex[i]) {
				cout << "v" << G.vertices[i].data << "-" << "v" << G.vertices[adjvex[i]].data << ":" << p->info << endl;
				i++;
				break;
			}
			else p = p->nextarc;
		}
	}
}

void Krusal(ALGraph &G) {
	int union_set[MAX_VERTEX_NUM];//并查集union_set
	for (int v = 0; v < G.vexnum; v++)
		union_set[v] = v;
	//TODO:请利用并查集实现Krusal算法，约20行
	Edge *edges = new Edge[MAX_EDGE_NUM];//边数组，方便接下来获得边排序表
	int j = 0;
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {//给边数组赋初值，乱序
		ArcNode*p = G.vertices[i].firstarc;
		while (p) {
			if (p->adjvex > i) {//因为这是个无向图，我们用邻接点是否>i来判断是否重复
				edges[j].v1 = i;
				edges[j].v2 = p->adjvex;
				edges[j].weight = p->info;
				j++;//j用来控制的是edges数组的行走
			}
			p = p->nextarc;
		}
	}

	//实现排序
	for (int i = 0; i < MAX_EDGE_NUM; i++)
	{
		Edge &w_min = edges[i];
		for (int j = i + 1; j < MAX_EDGE_NUM; j++)
			if (w_min.weight > edges[j].weight)
				swap(w_min, edges[j]);
	}

	//for (int i = 0; i < MAX_EDGE_NUM; i++)
	//	cout << endl << "(" << edges[i].v1 << "," << edges[i].v2 << "," << edges[i].weight << ")";

	//利用边排序和并查集求最小生成树
	int i = 0;
	int U[MAX_VERTEX_NUM];//U集合用来存放已经挑选的边
	int u_num = 0;
	while (1) {
		for (j = 0; j < MAX_VERTEX_NUM - 1; j++)//判断是否结束
			if (union_set[j] != union_set[j + 1])//结束条件是所有顶点标记一致
				break;
		if (j == MAX_VERTEX_NUM - 1)
			break;

		if (union_set[edges[i].v1] != union_set[edges[i].v2]) {//如果改变未被选中
			for (int k = 0; k < MAX_VERTEX_NUM; k++)//更新标记
				if (union_set[k] == union_set[edges[i].v2])
					union_set[k] = union_set[edges[i].v1];
			U[u_num] = i;		//加入到U集合中
			u_num++;			//U集合计数+1
		}
		i++;
	}
	for (int i = 0; i < MAX_VERTEX_NUM - 1; i++)
		cout << "v" << G.vertices[edges[U[i]].v1].data << "-" << "v" << G.vertices[edges[U[i]].v2].data <<":"<< edges[U[i]].weight << endl;
}

int main()
{
	////测试图的创建和输出
	//ALGraph g("ABCD");
	//g.addArc(0, 2);
	//g.addArc(0, 1);
	//g.addArc(2, 3);
	//g.addArc(3, 0);
	//g.output();

	ALGraph G("123456", 0);//6个结点的无向图
	G.addArc(0, 1, 6); G.addArc(0, 2, 1);
	G.addArc(0, 3, 5); G.addArc(1, 2, 5);
	G.addArc(1, 4, 3); G.addArc(2, 3, 5);
	G.addArc(2, 4, 6); G.addArc(2, 5, 4);
	G.addArc(3, 5, 2); G.addArc(4, 5, 6);
	cout << "图的邻接表存储：" << endl;
	G.output();

	cout << "Prim 选择的边：" << endl;
	Prim(G); //测试Prim算法
	cout << "Krusal 选择的边：" << endl;
	Krusal(G); //测试Krusal算法

	return 0;
}


