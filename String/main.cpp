// String.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include"String.h"
#include"SeqList.h"
#include"KMP.h"
using namespace std;

ostream& operator<< (ostream &os, String &st) {//标准输出流方式接口 
	for (int i = 0; i < st.length; i++)
		os << st.items[i];
	return os;
}

int main()
{
	try {
		String string1(100);//指定容量构造函数测试
		String string2("abcdefghijklefghmn");//通过字符串构造String的构造函数测试
		String string3("ABCDEF");
		String string4("efgh");
		String A = "lanzixu";
		A.outPut();
		//string2.outPut();//测试构造函数2

		//string2.contact(string3);//测试连接字符串函数
		//string3.outPut();
		//string2.outPut();

		//cout << string2[2] << endl; //下标访问运算符[]的测试

		//string4.outPut();
		//cout << string2.compare(string4) << endl;//测试字符串比较函数compare

		//String *result = string2.subString(5, 2);//测试取子串函数subString
		//result->outPut();

		//string2.remove(10, 3);//测试字符串删除函数，从参数1处删除参数2个字符
		//string2.outPut();

		//string3.outPut();
		//string2.insert(string3, 6);//测试插入函数
		//string2.outPut();

		//string4.outPut();
		//cout << string2.index(string4,0);//测试查找子串函数

		//String string5 = "lanzixudsglanzixudsglan";
		//String string8 = "dsg";//测试replace函数
		//String string9 = "tsl";
		//cout << "替换前：";
		//string5.outPut();
		//string5.replace(string8, string9);//把string5中的dsg替换成tsl
		//cout << "替换后：";
		//string5.outPut();

		//String string6("*abc***GHI*L");//测试字符串分割函数
		//string6.outPut();
		//SeqList<String> subs;
		//string6.split(subs, '*');
		//subs.printOut();

		//String string7("   lanzixu  ");//测试去掉字符串首尾空格的函数
		//string7.outPut();
		//string7.clear();
		//string7.outPut();

		//const char* s("ababacababacaaabababacacadabadb");
		//cout << "主串：" << s << endl;
		//const char* t("ababacac");
		//cout << "模式串：" << t << endl;
		//cout << "暴力匹配算法-找到模式串，在主串的第" << Index(s, t, 3) << "个字符处" << endl;//测试暴力匹配算法
		//int next[20]; //next[j]表示T[j]前的最长前后缀相等的长度 
		//get_next(t, next);//测试KMP算法
		//cout << "KMP算法-找到模式串，在主串的第" << Index_KMP(s, t, next, 0) << "个字符处" << endl;

		//字符串匹配性能测试函数 
		//char S[] = "000000000000000000000000000000000000001";
		//char T[] = "0000000000001";
		//int next[20]; //next[j]表示T[j]前的最长前后缀相等的长度 
		//get_next(T, next);//测试KMP算法
		//int pos;
		//int repeats = 10000000;
		//time_t tBegin, tEnd;
		//time(&tBegin); //记录当前时间tBegin 
		//for (int i = 0; i < repeats; i++)
		//	pos = Index_KMP(S, T, next, 0); //TODO:实现KMP之后这里改调用
		//	time(&tEnd); //记录当前时间tEnd 
		//float cost = tEnd - tBegin; //计算耗时 
		//printf("子串搜索结果是：%d，耗时%.2fs\n", pos, cost);
		//return 0;
}
catch (const char *msg) {
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
