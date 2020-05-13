#pragma once
#include<iostream>
using namespace std;

static char screen[40][80];//��Ļ��ӡר�û�����

struct BinTree {
	char data;//������ݣ���β�����ģ���� 
	BinTree *lchild, *rchild;//���Һ���ָ�� 
	BinTree(char d) {//���캯�� 
		data = d; 
		lchild = NULL; 
		rchild = NULL; 
	}

	~BinTree() {//�����������ݹ��ͷ��ӽ�� 
		if (lchild) delete lchild; 
		if (rchild) delete rchild; 
	}

	static BinTree* create(char *str, int &index) {//����������ַ�������������
		char ch = str[index++]; 
		if (ch == '#') return NULL;
		BinTree *node = new BinTree(ch); 
		node->lchild = create(str, index); 
		node->rchild = create(str, index); 
		return node;
	}

	//�ݹ�������� 
	int deep() { 
		int ldeep = (lchild == NULL) ? 0 : lchild->deep(); 
		int rdeep = (rchild == NULL) ? 0 : rchild->deep(); 
		return 1 + (ldeep > rdeep ? ldeep : rdeep); 
	}

	//���뺬Ҷ�ӽ���ָ���ǵķ�ʽ���������� 
	BinTree* create() {
		char ch; 
		cin >> ch;
		if (ch == '#') return NULL;
		BinTree *node = new BinTree(ch); 
		node->lchild = create();
		node->rchild = create();
		return node;
	}

	//������������� 
	void output() { 
		memset(screen, ' ', sizeof(screen));//����ӡ�ĵط��ÿո�ռλ 
		draw(0, 0, NULL);//��(0,0)����͸��ڵ㿪ʼ����������screen������ 
		int height = deep()*2;//��ӡ�߶ȵ�������ȵ�2������ΪԪ��ֵҪ���һ�� 
		for (int i = 0; i<height; i++) { 
			screen[i][40] = '\0'; 
			printf("%s\n", screen[i]); 
		} 
	}

	//�������������screen�������л��ƶ�����ͼ�� 
	int draw(int startx, int y, BinTree *parent) {
		//���㷨��ȻҲ�õ��ݹ�������������ڽ�ѧ�Ϳ��˵㣬�ܹ���⼴�� 
		//startx��ʾ��ǰ������˵���ʼx���� 
		int endx = startx;//endx��ʾ��ǰ�������Ҷ˵�x���� 
		if (lchild) endx = lchild->draw(startx, y + 2, this) + 1;//�������� 
		int centerx = endx;//������������x���꣬���Ǹ��ڵ��x���� 
		screen[y][endx++] = data; 
		if (rchild) endx = rchild->draw(endx, y + 2, this) + 1;//�������� 
		if (parent) {//����и���㣬����Ĵ�������Լ��ĸ��ڵ��ӡ�����ߵ������ 
			if (parent->lchild == this) { 
				for (int x = centerx; x <= endx; x++) 
					screen[y - 1][x] = '-'; 
				screen[y - 1][centerx] = '/'; 
			}
			else { 
				for (int x = startx; x <= centerx; x++) 
					screen[y - 1][x] = '-'; 
				screen[y - 1][centerx] = '\\'; 
			} 
		}
		return endx; 
	}

	void preOrder() {//������� 
		cout << data;
		if (lchild) lchild->preOrder();
		if (rchild) rchild->preOrder();
	}
	
	void postOrder() {//������� 
		if (lchild) lchild->postOrder();
		if (rchild) rchild->postOrder();
		cout << data;
	}

	void inOrder() {//������� 
		if (lchild) lchild->inOrder();
		cout << data;
		if (rchild) rchild->inOrder();
	}

	//������������ع������� 
	static BinTree * rebuildByPreIn(char* PreOrder, char *InOrder, int Len) { 
		//���PΪ�գ����̷��� 
		if (Len == 0) return NULL; 
		//ȡPreOrder�ĵ�һ��Ԫ����Ϊ���ڵ�r 
		char r = PreOrder[0]; 
		BinTree *R = new BinTree(r); 
		//����r��InOrder�г��ֵ�λ��pos 
		int pos = 0; 
		while (pos<Len) { 
			if (InOrder[pos] == r) 
				break; 
			pos++; 
		}
		//�ع����������ع���R->lchild,PL,ML) 
		R->lchild = rebuildByPreIn(PreOrder + 1, InOrder, pos); 
		pos++; 
		//�ع����������ع���R->rchild,PR,MR) 
		R->rchild = rebuildByPreIn(PreOrder + pos, InOrder + pos, Len - pos); 
		return R; 
	} 

	//�ɺ���������ع������� 
	static BinTree * rebuildByPostIn(char* PostOder, char *InOrder, int Len) {
		//���PΪ�գ����� 
		if (Len == 0) return NULL; 
		//ȡPostOder�����һ��Ԫ����Ϊ���ڵ�r 
		char r = PostOder[Len-1];
		BinTree *R = new BinTree(r); //����r��InOrder�г��ֵ�λ��pos 
		int pos = 0;
		while (pos < Len) {
			if (InOrder[pos] == r)
				break;
			pos++;
		}
		//�ع����������ع���R->lchild,PL,ML) 
		R->lchild = rebuildByPostIn(PostOder, InOrder, pos);
		//�ع����������ع���R->rchild,PR,MR) 
		R->rchild = rebuildByPostIn(PostOder + pos, InOrder + pos + 1, Len - pos - 1);
		return R;
	}

	int count() {//Ĭ�Ϸ���1�������
		int lcount = (lchild == NULL) ? 0 : lchild->count();//������������ڣ��ݹ����count�������ھ���0
		int rcount = (rchild == NULL) ? 0 : rchild->count();//������������ڣ��ݹ����count�������ھ���0
		return 1 + lcount + rcount;//����1+���������Ľ����
	}

	void flipRL() {//�����������н������Һ���
		BinTree *node = new BinTree('char');//����ʱ�õ����м����
		if (lchild) lchild->flipRL();//����������ҵ�˳��
		if (rchild) rchild->flipRL();//�ݹ���ã��ҵ�������ΪҶ�ӽ��Ϊֹ
		if (lchild || rchild) {		//�жϽ���Ƿ��������������������
			node = lchild;			//�����������һ����������ô��Ҫִ�н�����Ȼ�󷵻�
			lchild = rchild;		//����������ڣ�֤����Ҷ�ӽ�㣬ֱ��return�������
			rchild = node;			
		}
		return;
	}

	char maxNode(char max) {//����һ�����������õ�ʱ�򣬸ò���Ĭ��Ϊ������data
		if (lchild) max = lchild->maxNode(max);//�ݹ����
		if (rchild) max = rchild->maxNode(max);//�ݹ���ã��ҵ�Ҷ�ӽڵ�Ϊֹ
		max = max > data ? max : data;//�Ƚ�Ҷ�ӽ���data��max�����ش���Ǹ�
		return max;
	}
};