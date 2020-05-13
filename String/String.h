#pragma once
#include"SeqList.h"
#include<memory.h>
using namespace std;
struct String :SeqList<char> {

	String(int c = 100) :SeqList(c) {

	}

	String(const char *chars) {//以'\0'结尾的串构造串，方便将C语言的字符串转换为当前封装的String 
		while (*chars) {
			append(*chars);
			chars++;
		}
	}

	bool operator==(String &T) { //重载==运算符
		return compare(T) == 0;
	}

	void operator=(const String& T) {//深拷贝函数，不重写会导致字符串的数组赋值出现浅拷贝
		length = T.length;
		resize(length);
		memcpy(items, T.items, sizeof(char)*T.length);
	}

	char &operator[](int i) {//实现下标访问运算符[]
		return items[i];  /*字符串下标访问从0开始*/
	}

	String &contact(String &T) {//连接字符串
		int len = length + T.length;
		if (capacity < len)//长度不够则扩容
			resize(len);
		memcpy(items + length, T.items, sizeof(char)*T.length);//连接第二部分 
		length = len;
		return *this;//返回自身，方便调用者连续使用
	}

	int compare(String &T) {//比较两个串是否相等，返回正数、零、负数分别表示大于、等于、小于
		int n = length, m = T.length;
		int i = 0, j = 0;
		while (i < n && j < m) {
			if (items[i] != T.items[i]) //存在一个字符不等则不等 
				return items[i] - T.items[i];//以第一个不相等的字符计算大小 
			i++; j++;
		}
		return n - m;//全部字符都没有不等，则两个串相等
	}

	String *subString(int pos, int len) {
		/*取子串 返回类型为String类型的指针 取pos位置后len长度的子串
		 因为想要把取出的子串单独定义为一个String类型的字符串，所以
		 这里利用返回类型为指针的函数*/
		if (pos + len >= length)
			throw"NO VALUES";
		String *result = new String(len);//利用定长构造函数 构造子串的对象
		memcpy(result->items, items + pos + 1, len * sizeof(char));
		result->length = len;
		return result;//将指向子串的指针返回
	}
	//split复杂版本，有错误，不知如何订正
	/*void split(SeqList<String> &subs, char splitter) {
		//TODO:依据splitter字符，将字符串的内容分割开，依次存储到subs中
		int i = 0;
		int t = 0;
		int j;
		while (i<length) {//判断是否已经扫描完主串
			int len = 0;//记录两个相邻的splitter之间的长度
			while (items[i] != splitter) {//判断主串中的第i个元素是否等于splitter
				len++;//如果不等于，长度++
				i++;//i++判断下一个
			}
			if (len != 0) {//考虑一开始就是splitter
				//TODO:循环结束，进行分割操作
				static String *s = new String();//初始化一个长度为len+1的字符串，以储存分割后得到的字符串，len+1是为了让capacity>length
				for (j = i - 1; j >= len; j--) {//循环赋值
					s->items[j-length] = items[j];//倒着赋值，因为i指向的是最后一个非splitter字符
					s->length++;//更新长度
				}
				subs.items[t] = *s;//依次存入subs中
				subs.length++;//更新subs的length
				t++;//t++为了存储下一个subs.items
			}
			i++;
		}
	}*/

	void split(SeqList<String> &subs, char splitter) {
		//TODO:依据splitter字符，将字符串的内容分割开，依次存储到subs中
		int i = 0;
		int t = 0;
		while (i < length) {//判断是否已经扫描完主串
			int len = 0;//记录两个相邻的splitter之间的长度
			while (items[i] != splitter && i < length) {//判断主串中的第i个元素是否等于splitter
				len++;//如果不等于，长度++
				i++;//i++判断下一个
			}
			if (len != 0) {//考虑一开始就是splitter
				//TODO:循环结束，进行分割操作
				subs.items[t] = *this->subString(i - len - 1, len);//借助subString函数依次存入subs中
				subs.length++;//更新subs的length
				t++;//t++为了存储下一个subs.items
			}
			i++;
		}
	}

	void remove(int pos, int len) {
		//TODO：删除从pos开始的len个字符
		int i;
		if (pos + len > length) {//如果要超过原字符串的长度，则直接修改原字符串的length
			length = pos + 1;
		}
		else {
			for (i = pos; i < length - len; i++) //把后面的字符提前，覆盖掉前面的字符
				items[i] = items[i + len];
			length = length - len;//更新长度
		}
	}

	void insert(String A, int pos) {
		//TODO：将A插入到pos位置上 
		if (pos >= length) {//如果pos超过了length，直接衔接字符串A
			contact(A);
		}
		else {
			int i;
			for (i = A.length - 1; i >= 0; i--) {
				insertAt(pos, A.items[i]);//直接调用SeqList里的insertAt函数
			}
		}
	}

	int index(String &T, int pos = 0) {
		//TODO：返回T出现的第一个位置，找不到则返回-1 
		if (T.length > length)//如果模式串的长度大于主串，直接返回-1
			return -1;
		else {
			while (pos <= length - T.length) {//while循环终止条件：pos再移动，后面的长度就小于模式串了，没必要再比较，直接返回-1
				int i = pos;//主串每次比较是从items[pos]开始的
				int j = 0;//模式串每次比较是从T.itmes[0]开始的
				while (items[i] == T.items[j])//只要出现不相等，就pos++
				{
					i++; j++;
					if (j == T.length)//比较结束
						return pos;//返回pos
				}
				pos++;
			}
			return -1;
		}
	}

	void replace(String &A, String &B) {
		//TODO:查找当前字符串中所有的A，替换成B
		int i = 0;
		int flag = 0;//记录找到的A的数量，为了判断是否存在A
		int pos;
		while (items[i]) {
			if (length - i - 1 < A.length)
				return;
			pos = index(A, i);
			if (flag == 0 && pos == -1)//只有flag=0且pos=-1这种情况才表示没有找到子串A
				throw"NOT FOUND A";
			else if (flag != 0 && pos == -1)//flag不等于0且pos=-1表示后续字符串已经没有子串A了
				return;
			else {
				remove(pos, A.length);
				insert(B, pos);
				flag++;
			}
			i = pos + B.length - 1;
		}
	}

	void clear() {//删除首尾空白字符
		int i = 0;
		int len = 0;
		while (items[i] == ' ') {
			len++;
			i++;
		}
		remove(0, len);
		i = length;
		len = 0;
		if (items[i - 1] == ' ') {
			while (items[i - 1] == ' ') {
				len++;
				i--;
			}
			remove(length - len, len);
		}
	}

	friend ostream& operator<< (ostream &os, String &st);
};