#pragma once
#include<string.h>
#include<stdio.h>

class Mytree {

public:
	int	data;	 //数据
	Mytree* pParent; //指向父节点
	Mytree* pBrother;//指向兄弟节点
	Mytree* pChild;	 //指向孩子节点

	Mytree() {//构造器
		pParent = pBrother = pChild = NULL;
	}

	~Mytree() {//析构器
		//TODO:先不写内存释放
		pParent = pBrother = pChild = NULL;
	}
	/*
		新节点如果是兄弟，那么就成为最小的兄弟
		新节点如果是孩子，就成为最小的孩子
	*/
	void insertNode(const int& data, bool isChild = true) {	//遍历整棵树
		//创建新节点
		Mytree* pnew = new Mytree();
		memset(pnew, 0, sizeof(Mytree));
		pnew->data = data;
		//临时指针指向最小的孩子
		Mytree*pTemp = this;//指向当前对象
		while (pTemp->pChild) {
			pTemp = pTemp->pChild;
		}
		if (isChild) {
			pTemp->pChild = pnew;
			pnew->pParent = pTemp;
		}
		else {
			//找最小的兄弟
			while (pTemp->pBrother) {
				pTemp = pTemp->pBrother;
			}
			pTemp->pBrother = pnew;
			pnew->pParent = pTemp->pParent;
		}
	}

	void travle() {//获得地址
		Mytree*pBortherTemp = NULL;
		Mytree*pChildTemp = this;

		while (pChildTemp) {
			//往右走
			pBortherTemp = pChildTemp;
			while (pBortherTemp) {
				printf("%d ", pBortherTemp->data);
				pBortherTemp = pBortherTemp->pBrother;
			}
			printf("\n");
			//往下走
			pChildTemp = pChildTemp->pChild;
		}
	}

	Mytree*getNodePos(const int& data) {

		Mytree*pBortherTemp = NULL;
		Mytree*pChildTemp = this;

		while (pChildTemp) {
			//往右走
			pBortherTemp = pChildTemp;
			while (pBortherTemp) {
				if (data == pBortherTemp->data) return pBortherTemp;
				pBortherTemp = pBortherTemp->pBrother;
			}
			//往下走
			pChildTemp = pChildTemp->pChild;
		}
		return NULL;
	}

	void showData() {
		printf("data:%d", data);
	}
	/*
		删除节点，删除成功返回true，删除失败，返回false
		tips：
			如果删除的是孩子，而且这个孩子有兄弟，那么他的第一个兄弟成为他父的孩子。
			如果删除的子树没有兄弟，则其孩子归它的父亲所有。
	*/
	bool deleteNode(const int& data) {
		Mytree*pDelete = getNodePos(data);//得到删除的结点的数据
		if (pDelete == NULL) return false;
		//要删除的结点的父亲
		//Mytree*pDelparnet = pDelete->pParent;
		if (pDelete->pParent == NULL) {//要删除的结点是父节点
			if (pDelete->pBrother) {
				Mytree*ptemp = NULL;
				if (this->pChild) {
					//如果要删除的结点有孩子，那么成为最小的孩子
					pDelete->pBrother->pChild = this->pChild;
					ptemp = this->pChild;
					while (ptemp) {
						ptemp->pParent = pDelete->pBrother;
						ptemp = ptemp->pChild;
					}
				}
				//根节点有兄弟
				this->data = this->pBrother->data;
				this->pChild = pDelete->pBrother->pChild;
				this->pBrother = pDelete->pBrother->pBrother;
			}

			else {
				if (this->pChild) {
					this->data = this->pChild->data;
					//TODO:
					this->pBrother = this->pChild->pBrother;
					this->pChild = this->pChild->pChild;
				}
			}
		}
	}
};


