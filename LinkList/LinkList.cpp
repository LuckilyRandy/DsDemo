// LinkList.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<String>
#include<stdlib.h>
using namespace std;

template <typename ElemType>
struct LinkNode {
	ElemType data;
	LinkNode *next = NULL;
};

template <typename ElemType>
struct LinkList {
	int length = 0;
	LinkNode<ElemType> header;

	//插入函数
	void insert(ElemType e) {//这里会用到空构造函数
		LinkNode<ElemType> *p = new LinkNode<ElemType>();
		p->data = e;
		p->next = header.next;
		header.next = p;
		length++;
	}
};

struct Monomial {
	double coef;//系数
	int exp;//指数

	Monomial() {
	}

	Monomial(double c, int e) {
		coef = c;
		exp = e;
	}
	//输出函数
	void printOut() {
		if (coef) {
			cout << coef;
			if (exp)
				cout << "x^" << exp;
		}
		else cout << 0;
	}
};

struct Polynomial : public LinkList<Monomial> {	//仅仅实现多项式的特有运算

	//输出多项式
	void outPut() {
		LinkNode<Monomial> *p = header.next;
		//for (int i = 0; i < length; i++) {
		//	p->data.printOut();
		//}
		while (p) {              /*链表输出优先考虑while循环*/
			if (p->data.coef) {
				if (p != header.next&&p->data.coef > 0)
					cout << "+";
				p->data.printOut();
			}
			p = p->next;
		}
		cout << endl;
	} 

	//加法
	Polynomial add(Polynomial &other) {
		if (&other == NULL)
			throw "WARNING";
		//新建多项式类型的指针，指向多项式
		Polynomial *result = new Polynomial();
		//新建三个指针指向三个多项式的第一个结点
		LinkNode<Monomial> *p = header.next;  //指向本类中的this.polynomial的第一个结点
		LinkNode<Monomial> *q = other.header.next;  //指向传入的多项式的第一个结点
		LinkNode<Monomial> *r = &result->header;
		/*新建结点指针r指向结果的header结点，这里要用 *r表示声明的是个指针变量，类型是Polynomial
		，所以等号右边也要用取地址符号*/


		while (p&&q) {
			//作比较
			if (p->data.exp > q->data.exp) {
				LinkNode<Monomial> *s = new LinkNode<Monomial>();
				r->next = s;
				r = s;
				r->data.exp = p->data.exp;
				r->data.coef = p->data.coef;
				p = p->next;
			}
			else if (p->data.exp < q->data.exp) {
				LinkNode<Monomial> *s = new LinkNode<Monomial>();
				r->next = s;
				r = s;
				r->data.exp = q->data.exp;
				r->data.coef = q->data.coef;
				q = q->next;
			}
			else {
				LinkNode<Monomial> *s = new LinkNode<Monomial>();
				r->next = s;
				r = s;
				r->data.exp = p->data.exp;
				r->data.coef = q->data.coef + p->data.coef;
				p = p->next;
				q = q->next;
			}
		}
		while (q) {
			LinkNode<Monomial> *s = new LinkNode<Monomial>();
			r->next = s;
			r = s;
			r->data.coef = q->data.coef;
			r->data.exp = q->data.exp;
			q = q->next;
		}
		while (p) {
			LinkNode<Monomial> *s = new LinkNode<Monomial>();
			r->next = s;
			r = s;
			r->data.coef = p->data.coef;
			r->data.exp = p->data.exp;
			p = p->next;
		}
		r->next = NULL;
		return *result;//这里返回*，表示取内容
	}
};

int main()
{
	try {
		Polynomial A;		//多项式一
		A.insert(Monomial(0.0, 0));
		A.insert(Monomial(1.0, 0));
		A.insert(Monomial(2.4, 1));
		A.insert(Monomial(-3.5, 4));
		A.insert(Monomial(4.0, 8));
		A.outPut();

		Polynomial B;   //多项式二
		B.insert(Monomial(-5.3, 0));
		B.insert(Monomial(6.0, 4));
		B.insert(Monomial(-2.2, 5));
		B.insert(Monomial(9.0, 8));
		B.insert(Monomial(-8.8, 10));
		B.insert(Monomial(1.0, 12));
		B.outPut();

		Polynomial C = A.add(B);
		C.outPut();

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
