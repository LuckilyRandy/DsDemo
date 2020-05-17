#include <iostream>
#include"ALGraph.h"
using namespace std;
#define MAX_VERTEX_NUM 6
#define MAX_EDGE_NUM 10
#define INFINITY 100   //������Ŀ��������Զ����Ϊ100

void Prim(ALGraph &G) {
	int adjvex[MAX_VERTEX_NUM] = { 0 };
	int lowcost[MAX_VERTEX_NUM];
	bool U[MAX_VERTEX_NUM];	//��ѡ���㼯��
	memset(U, 0, sizeof(U));
	//TODO:��ʵ��Prim�㷨��Լ40��
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
		lowcost[i] = INFINITY;//lowcost���鶼��ʼ��Ϊ����Զ

	//��һ�Σ��Ȱѵ�0���������U��
	int i = 0;
	int flag = 1;//����һ����־λ����ʾ�����Ƿ��Ѿ�����U

	while (flag) {
		U[i] = 1;//�ѵ�һ������Ž�U��
		lowcost[i] = 0;//���㵽�����lowcost��Ϊ0
		ArcNode *p = G.vertices[i].firstarc;//ָ��pָ��ͼG�ĵ�һ������ĵ�һ�������
		while (p) {//��������ڽӵĻ���㣬�����˫��
			if (lowcost[p->adjvex] > p->info) {
				adjvex[p->adjvex] = i;
				lowcost[p->adjvex] = p->info;
			}
			p = p->nextarc;//pָ����һ���ڽӽ��
		}
		//�������֮��Ҫѡ��lowcost��С�Ľ�����U��
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
		i = min;//�ҵ�lowcost��С�Ľ��
		int k = 0;
		for (k = 0; k < MAX_VERTEX_NUM; k++) {//���U�Ƿ�װ��
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
	int union_set[MAX_VERTEX_NUM];//���鼯union_set
	for (int v = 0; v < G.vexnum; v++)
		union_set[v] = v;
	//TODO:�����ò��鼯ʵ��Krusal�㷨��Լ20��
	Edge *edges = new Edge[MAX_EDGE_NUM];//�����飬�����������ñ������
	int j = 0;
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {//�������鸳��ֵ������
		ArcNode*p = G.vertices[i].firstarc;
		while (p) {
			if (p->adjvex > i) {//��Ϊ���Ǹ�����ͼ���������ڽӵ��Ƿ�>i���ж��Ƿ��ظ�
				edges[j].v1 = i;
				edges[j].v2 = p->adjvex;
				edges[j].weight = p->info;
				j++;//j�������Ƶ���edges���������
			}
			p = p->nextarc;
		}
	}

	//ʵ������
	for (int i = 0; i < MAX_EDGE_NUM; i++)
	{
		Edge &w_min = edges[i];
		for (int j = i + 1; j < MAX_EDGE_NUM; j++)
			if (w_min.weight > edges[j].weight)
				swap(w_min, edges[j]);
	}

	//for (int i = 0; i < MAX_EDGE_NUM; i++)
	//	cout << endl << "(" << edges[i].v1 << "," << edges[i].v2 << "," << edges[i].weight << ")";

	//���ñ�����Ͳ��鼯����С������
	int i = 0;
	int U[MAX_VERTEX_NUM];//U������������Ѿ���ѡ�ı�
	int u_num = 0;
	while (1) {
		for (j = 0; j < MAX_VERTEX_NUM - 1; j++)//�ж��Ƿ����
			if (union_set[j] != union_set[j + 1])//�������������ж�����һ��
				break;
		if (j == MAX_VERTEX_NUM - 1)
			break;

		if (union_set[edges[i].v1] != union_set[edges[i].v2]) {//����ı�δ��ѡ��
			for (int k = 0; k < MAX_VERTEX_NUM; k++)//���±��
				if (union_set[k] == union_set[edges[i].v2])
					union_set[k] = union_set[edges[i].v1];
			U[u_num] = i;		//���뵽U������
			u_num++;			//U���ϼ���+1
		}
		i++;
	}
	for (int i = 0; i < MAX_VERTEX_NUM - 1; i++)
		cout << "v" << G.vertices[edges[U[i]].v1].data << "-" << "v" << G.vertices[edges[U[i]].v2].data <<":"<< edges[U[i]].weight << endl;
}

int main()
{
	////����ͼ�Ĵ��������
	//ALGraph g("ABCD");
	//g.addArc(0, 2);
	//g.addArc(0, 1);
	//g.addArc(2, 3);
	//g.addArc(3, 0);
	//g.output();

	ALGraph G("123456", 0);//6����������ͼ
	G.addArc(0, 1, 6); G.addArc(0, 2, 1);
	G.addArc(0, 3, 5); G.addArc(1, 2, 5);
	G.addArc(1, 4, 3); G.addArc(2, 3, 5);
	G.addArc(2, 4, 6); G.addArc(2, 5, 4);
	G.addArc(3, 5, 2); G.addArc(4, 5, 6);
	cout << "ͼ���ڽӱ�洢��" << endl;
	G.output();

	cout << "Prim ѡ��ıߣ�" << endl;
	Prim(G); //����Prim�㷨
	cout << "Krusal ѡ��ıߣ�" << endl;
	Krusal(G); //����Krusal�㷨

	return 0;
}


