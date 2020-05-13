#pragma once
#include<iostream>
using namespace std;

static char screen[40][80];//屏幕打印专用缓冲区

struct BinTree {
	char data;//结点数据，这次不采用模板类 
	BinTree *lchild, *rchild;//左右孩子指针 
	BinTree(char d) {//构造函数 
		data = d; 
		lchild = NULL; 
		rchild = NULL; 
	}

	~BinTree() {//析构函数，递归释放子结点 
		if (lchild) delete lchild; 
		if (rchild) delete rchild; 
	}

	static BinTree* create(char *str, int &index) {//由先序遍历字符串创建二叉树
		char ch = str[index++]; 
		if (ch == '#') return NULL;
		BinTree *node = new BinTree(ch); 
		node->lchild = create(str, index); 
		node->rchild = create(str, index); 
		return node;
	}

	//递归求树深度 
	int deep() { 
		int ldeep = (lchild == NULL) ? 0 : lchild->deep(); 
		int rdeep = (rchild == NULL) ? 0 : rchild->deep(); 
		return 1 + (ldeep > rdeep ? ldeep : rdeep); 
	}

	//输入含叶子结点空指针标记的方式创建二叉树 
	BinTree* create() {
		char ch; 
		cin >> ch;
		if (ch == '#') return NULL;
		BinTree *node = new BinTree(ch); 
		node->lchild = create();
		node->rchild = create();
		return node;
	}

	//输出整个二叉树 
	void output() { 
		memset(screen, ' ', sizeof(screen));//不打印的地方用空格占位 
		draw(0, 0, NULL);//从(0,0)坐标和根节点开始，绘制树到screen缓冲区 
		int height = deep()*2;//打印高度等于树深度的2倍，因为元素值要间隔一行 
		for (int i = 0; i<height; i++) { 
			screen[i][40] = '\0'; 
			printf("%s\n", screen[i]); 
		} 
	}

	//利用中序遍历在screen缓冲区中绘制二叉树图形 
	int draw(int startx, int y, BinTree *parent) {
		//此算法虽然也用到递归遍历，但不属于教学和考核点，能够理解即可 
		//startx表示当前树最左端的起始x坐标 
		int endx = startx;//endx表示当前子树最右端的x坐标 
		if (lchild) endx = lchild->draw(startx, y + 2, this) + 1;//先左子树 
		int centerx = endx;//左子树结束的x坐标，就是根节点的x坐标 
		screen[y][endx++] = data; 
		if (rchild) endx = rchild->draw(endx, y + 2, this) + 1;//再右子树 
		if (parent) {//如果有父结点，下面的处理负责把自己的根节点打印连接线到父结点 
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

	void preOrder() {//先序遍历 
		cout << data;
		if (lchild) lchild->preOrder();
		if (rchild) rchild->preOrder();
	}
	
	void postOrder() {//后序遍历 
		if (lchild) lchild->postOrder();
		if (rchild) rchild->postOrder();
		cout << data;
	}

	void inOrder() {//中序遍历 
		if (lchild) lchild->inOrder();
		cout << data;
		if (rchild) rchild->inOrder();
	}

	//由先序和中序重构二叉树 
	static BinTree * rebuildByPreIn(char* PreOrder, char *InOrder, int Len) { 
		//如果P为空，立刻返回 
		if (Len == 0) return NULL; 
		//取PreOrder的第一个元素作为根节点r 
		char r = PreOrder[0]; 
		BinTree *R = new BinTree(r); 
		//查找r在InOrder中出现的位置pos 
		int pos = 0; 
		while (pos<Len) { 
			if (InOrder[pos] == r) 
				break; 
			pos++; 
		}
		//重构左子树：重构（R->lchild,PL,ML) 
		R->lchild = rebuildByPreIn(PreOrder + 1, InOrder, pos); 
		pos++; 
		//重构右子树：重构（R->rchild,PR,MR) 
		R->rchild = rebuildByPreIn(PreOrder + pos, InOrder + pos, Len - pos); 
		return R; 
	} 

	//由后序和中序重构二叉树 
	static BinTree * rebuildByPostIn(char* PostOder, char *InOrder, int Len) {
		//如果P为空，返回 
		if (Len == 0) return NULL; 
		//取PostOder的最后一个元素作为根节点r 
		char r = PostOder[Len-1];
		BinTree *R = new BinTree(r); //查找r在InOrder中出现的位置pos 
		int pos = 0;
		while (pos < Len) {
			if (InOrder[pos] == r)
				break;
			pos++;
		}
		//重构左子树：重构（R->lchild,PL,ML) 
		R->lchild = rebuildByPostIn(PostOder, InOrder, pos);
		//重构右子树：重构（R->rchild,PR,MR) 
		R->rchild = rebuildByPostIn(PostOder + pos, InOrder + pos + 1, Len - pos - 1);
		return R;
	}

	int count() {//默认返回1，根结点
		int lcount = (lchild == NULL) ? 0 : lchild->count();//如果左子树存在，递归调用count，不存在就是0
		int rcount = (rchild == NULL) ? 0 : rchild->count();//如果右子树存在，递归调用count，不存在就是0
		return 1 + lcount + rcount;//返回1+左右子树的结点数
	}

	void flipRL() {//交换树的所有结点的左右孩子
		BinTree *node = new BinTree('char');//交换时用到的中间变量
		if (lchild) lchild->flipRL();//根据先左后右的顺序
		if (rchild) rchild->flipRL();//递归调用，找到右子树为叶子结点为止
		if (lchild || rchild) {		//判断结点是否存在左子树或者右子树
			node = lchild;			//如果存在任意一个子树，那么就要执行交换，然后返回
			lchild = rchild;		//如果都不存在，证明是叶子结点，直接return到父结点
			rchild = node;			
		}
		return;
	}

	char maxNode(char max) {//传入一个参数，调用的时候，该参数默认为根结点的data
		if (lchild) max = lchild->maxNode(max);//递归调用
		if (rchild) max = rchild->maxNode(max);//递归调用，找到叶子节点为止
		max = max > data ? max : data;//比较叶子结点的data与max，返回大的那个
		return max;
	}
};