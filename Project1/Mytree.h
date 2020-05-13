#pragma once
#include<string.h>
#include<stdio.h>

class Mytree {

public:
	int	data;	 //����
	Mytree* pParent; //ָ�򸸽ڵ�
	Mytree* pBrother;//ָ���ֵܽڵ�
	Mytree* pChild;	 //ָ���ӽڵ�

	Mytree() {//������
		pParent = pBrother = pChild = NULL;
	}

	~Mytree() {//������
		//TODO:�Ȳ�д�ڴ��ͷ�
		pParent = pBrother = pChild = NULL;
	}
	/*
		�½ڵ�������ֵܣ���ô�ͳ�Ϊ��С���ֵ�
		�½ڵ�����Ǻ��ӣ��ͳ�Ϊ��С�ĺ���
	*/
	void insertNode(const int& data, bool isChild = true) {	//����������
		//�����½ڵ�
		Mytree* pnew = new Mytree();
		memset(pnew, 0, sizeof(Mytree));
		pnew->data = data;
		//��ʱָ��ָ����С�ĺ���
		Mytree*pTemp = this;//ָ��ǰ����
		while (pTemp->pChild) {
			pTemp = pTemp->pChild;
		}
		if (isChild) {
			pTemp->pChild = pnew;
			pnew->pParent = pTemp;
		}
		else {
			//����С���ֵ�
			while (pTemp->pBrother) {
				pTemp = pTemp->pBrother;
			}
			pTemp->pBrother = pnew;
			pnew->pParent = pTemp->pParent;
		}
	}

	void travle() {//��õ�ַ
		Mytree*pBortherTemp = NULL;
		Mytree*pChildTemp = this;

		while (pChildTemp) {
			//������
			pBortherTemp = pChildTemp;
			while (pBortherTemp) {
				printf("%d ", pBortherTemp->data);
				pBortherTemp = pBortherTemp->pBrother;
			}
			printf("\n");
			//������
			pChildTemp = pChildTemp->pChild;
		}
	}

	Mytree*getNodePos(const int& data) {

		Mytree*pBortherTemp = NULL;
		Mytree*pChildTemp = this;

		while (pChildTemp) {
			//������
			pBortherTemp = pChildTemp;
			while (pBortherTemp) {
				if (data == pBortherTemp->data) return pBortherTemp;
				pBortherTemp = pBortherTemp->pBrother;
			}
			//������
			pChildTemp = pChildTemp->pChild;
		}
		return NULL;
	}

	void showData() {
		printf("data:%d", data);
	}
	/*
		ɾ���ڵ㣬ɾ���ɹ�����true��ɾ��ʧ�ܣ�����false
		tips��
			���ɾ�����Ǻ��ӣ���������������ֵܣ���ô���ĵ�һ���ֵܳ�Ϊ�����ĺ��ӡ�
			���ɾ��������û���ֵܣ����亢�ӹ����ĸ������С�
	*/
	bool deleteNode(const int& data) {
		Mytree*pDelete = getNodePos(data);//�õ�ɾ���Ľ�������
		if (pDelete == NULL) return false;
		//Ҫɾ���Ľ��ĸ���
		//Mytree*pDelparnet = pDelete->pParent;
		if (pDelete->pParent == NULL) {//Ҫɾ���Ľ���Ǹ��ڵ�
			if (pDelete->pBrother) {
				Mytree*ptemp = NULL;
				if (this->pChild) {
					//���Ҫɾ���Ľ���к��ӣ���ô��Ϊ��С�ĺ���
					pDelete->pBrother->pChild = this->pChild;
					ptemp = this->pChild;
					while (ptemp) {
						ptemp->pParent = pDelete->pBrother;
						ptemp = ptemp->pChild;
					}
				}
				//���ڵ����ֵ�
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


