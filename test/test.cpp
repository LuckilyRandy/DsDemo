#include <iostream>
#include<memory.h>
using namespace std;
#define  M 10 //顺序表空间
#define  N 10 //单次开辟长度

template <typename ElemType>
struct SeqList {
	ElemType *items;
	int length;
	int capacity;

	SeqList(int c) {
		items = new ElemType[c];
		if (items == NULL)
			throw"failed to new";
		length = 0;
		capacity = c;
	}
	SeqList() {
		items = new ElemType[M];
		if (items == NULL)
			throw"failed to new";
		length = 0;
		capacity = M;
	}

	void resize(int c) {
		/*if (c <= capacity)
			throw"previous capacity is enough";*/
		ElemType *newitems = new ElemType[c];
		if (newitems == NULL)
			throw"failed to resize";
		memcpy(newitems, items, length * sizeof(ElemType));
		delete[]items;
		items = newitems;
		//cout << "succeed" << endl;
	}

	void append(ElemType e) {
		if (length == capacity) {
			capacity = capacity + N;
			resize(capacity);
			items[length++] = e;
		}
		else items[length++] = e;
	}

	void outPut() {
		for (int i = 0; i < length; i++)
			cout << items[i];
		cout << endl;
		cout << "length= " << length << endl;
	}

	void printOut() { //专门用于SeqList<String>的输出函数
		for (int i = 0; i < length; i++)
			cout << items[i] << " ";//每个字符串之间有空格
		cout << endl;
		cout << "length= " << length << endl;
	}

	void insertAt(int index, ElemType e) {
		if (index >= capacity) {
			capacity = capacity + N;
			resize(capacity);
		}
		for (int i = length; i > index; i--)
			items[i] = items[i - 1];
		items[index] = e;
		length++;
	}
};

struct String :SeqList<char> {

	String(int c = 100) :SeqList(c) {

	}

	String(const char *chars) {//以'\0'结尾的串构造串，方便将C语言的字符串转换为当前封装的String 
		while (*chars) {
			append(*chars);
			chars++;
		}
	}

	String *subString(int pos, int len) {
		/*取子串 返回类型为String类型的指针 取pos位置后len长度的子串
		 因为想要把取出的子串单独定义为一个String类型的字符串，所以
		 这里利用返回类型为指针的函数*/
		if (pos + len > length)
			throw"NO VALUES";
		String *result = new String(len);//利用定长构造函数 构造子串的对象
		memcpy(result->items, items + pos, len * sizeof(char));
		result->length = len;
		return result;//将指向子串的指针返回
	}

	//String& concat(String& T) {
	//	//连接字符串
	//	int len = length + T.length;
	//	if (capacity < len)
	//		resize(len);
	//	memcpy(items + length, T.items, sizeof(char) * T.length);//连接第二部分
	//	length = len;
	//	return *this;//返回自身，方便调用者连续使用
	//}

	//int compare(String& T) {
	//	//比较两个串是否相等，大于，等于，小于=1，0，-1
	//	int n = length, m = T.length;
	//	int i = 0, j = 0;
	//	while (i < n && j < m) {
	//		if (items[i] != T.items[i])
	//			return items[i] - T.items[i];
	//		i++, j++;
	//	}
	//	return n - m;
	//}

	//bool operator==(String& T) {//串相等判断
	//	return compare(T) == 0;
	//}

	void operator=(const String& T) {
		//深拷贝
		length = T.length;
		resize(length);
		memcpy(items, T.items, sizeof(char) * T.length);
	}

	void split(SeqList<String> &subs, char splitter) {
		//TODO:依据splitter字符，将字符串的内容分割开，依次存储到subs中
		int i = 0;
		int t = 0;
		while (i < length) {//判断是否已经扫描完主串
			int len = 0;//记录两个相邻的splitter之间的长度
			while (items[i] != splitter) {//判断主串中的第i个元素是否等于splitter
				len++;//如果不等于，长度++
				i++;//i++判断下一个
			}
			if (len != 0) {//考虑一开始就是splitter
				//TODO:循环结束，进行分割操作
				subs.items[t] = *this->subString(i - len, len);//借助subString函数依次存入subs中
				subs.length++;//更新subs的length
				t++;//t++为了存储下一个subs.items
			}
			i++;
		}
	}

	/*void replace(String A, String B) {
		int i = 0;
		int j = 0;
		while (i < this->length&& j < A.length) {
			if (items[i] == A.items[j]) {
				i++;
				j++;
			}
			else {
				i = i - j + 1;
				j = 0;
			}
		}
		if (j == A.length) {
			int len = i - j;
			memcpy(items + len, B.items, A.length);
		}
	}
	void remove(int pos, int len) {

	}
	void insert(String &T, int pos) {

	}*/
	//friend ostream& operator<<(ostream &os, String &st);


	//void split(SeqList<String>&subs, char spliter)
	//{
	//	if (subs.length < this->length)
	//		throw "target String not enough";
	//	
	//	for (int i = 0; i < length; i++) {
	//		if (subs.items[i] == (String)spliter) {
	//			items[i] = '\0';
	//			//deleteAt(items[i]);
	//		}				
	//	}
	//	memcpy(&subs, this, this->length);
	//}

};

ostream& operator<< (ostream &os, String &st) {//标准输出流方式接口 
	for (int i = 0; i < st.length; i++)
		os << st.items[i];
	return os;
}

int main() {
	////字符串测试函数 
	//String A("hello "); //测试显示构造函数 
	//String B = "world!"; //测试类型转换构造函数 
	//A.concat(B).outPutList();//测试A串连接B串并打印A串 
	//printf("A-B=%d\n", A.compare(B));//测试A串和B串比较
	//String S("acabaabaabcacaabc");
	//String T("abaabc");
	//S.outPutList();
	//T.outPutList();
	String string6("***abc*df*GHI*");//测试字符串分割函数
	string6.outPut();
	SeqList<String> subs;
	string6.split(subs, '*');
	subs.outPut();
	//S.replace("acaba", A);
	/*SeqList<String>s;
	printf("%d", s.length);
	A.split(s, 'o');
	printf("%d",s.length);
	printf("%c", s);
	s.outPutList();*/
	//printf("子串搜索结果是：%d\n", S.Index(T));//测试求子串位置 return 0;
}