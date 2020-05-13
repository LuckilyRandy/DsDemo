#pragma once
#include"SeqList.h"
#include<memory.h>
using namespace std;
struct String :SeqList<char> {

	String(int c = 100) :SeqList(c) {

	}

	String(const char *chars) {//��'\0'��β�Ĵ����촮�����㽫C���Ե��ַ���ת��Ϊ��ǰ��װ��String 
		while (*chars) {
			append(*chars);
			chars++;
		}
	}

	bool operator==(String &T) { //����==�����
		return compare(T) == 0;
	}

	void operator=(const String& T) {//�������������д�ᵼ���ַ��������鸳ֵ����ǳ����
		length = T.length;
		resize(length);
		memcpy(items, T.items, sizeof(char)*T.length);
	}

	char &operator[](int i) {//ʵ���±���������[]
		return items[i];  /*�ַ����±���ʴ�0��ʼ*/
	}

	String &contact(String &T) {//�����ַ���
		int len = length + T.length;
		if (capacity < len)//���Ȳ���������
			resize(len);
		memcpy(items + length, T.items, sizeof(char)*T.length);//���ӵڶ����� 
		length = len;
		return *this;//���������������������ʹ��
	}

	int compare(String &T) {//�Ƚ��������Ƿ���ȣ������������㡢�����ֱ��ʾ���ڡ����ڡ�С��
		int n = length, m = T.length;
		int i = 0, j = 0;
		while (i < n && j < m) {
			if (items[i] != T.items[i]) //����һ���ַ������򲻵� 
				return items[i] - T.items[i];//�Ե�һ������ȵ��ַ������С 
			i++; j++;
		}
		return n - m;//ȫ���ַ���û�в��ȣ������������
	}

	String *subString(int pos, int len) {
		/*ȡ�Ӵ� ��������ΪString���͵�ָ�� ȡposλ�ú�len���ȵ��Ӵ�
		 ��Ϊ��Ҫ��ȡ�����Ӵ���������Ϊһ��String���͵��ַ���������
		 �������÷�������Ϊָ��ĺ���*/
		if (pos + len >= length)
			throw"NO VALUES";
		String *result = new String(len);//���ö������캯�� �����Ӵ��Ķ���
		memcpy(result->items, items + pos + 1, len * sizeof(char));
		result->length = len;
		return result;//��ָ���Ӵ���ָ�뷵��
	}
	//split���Ӱ汾���д��󣬲�֪��ζ���
	/*void split(SeqList<String> &subs, char splitter) {
		//TODO:����splitter�ַ������ַ��������ݷָ�����δ洢��subs��
		int i = 0;
		int t = 0;
		int j;
		while (i<length) {//�ж��Ƿ��Ѿ�ɨ��������
			int len = 0;//��¼�������ڵ�splitter֮��ĳ���
			while (items[i] != splitter) {//�ж������еĵ�i��Ԫ���Ƿ����splitter
				len++;//��������ڣ�����++
				i++;//i++�ж���һ��
			}
			if (len != 0) {//����һ��ʼ����splitter
				//TODO:ѭ�����������зָ����
				static String *s = new String();//��ʼ��һ������Ϊlen+1���ַ������Դ���ָ��õ����ַ�����len+1��Ϊ����capacity>length
				for (j = i - 1; j >= len; j--) {//ѭ����ֵ
					s->items[j-length] = items[j];//���Ÿ�ֵ����Ϊiָ��������һ����splitter�ַ�
					s->length++;//���³���
				}
				subs.items[t] = *s;//���δ���subs��
				subs.length++;//����subs��length
				t++;//t++Ϊ�˴洢��һ��subs.items
			}
			i++;
		}
	}*/

	void split(SeqList<String> &subs, char splitter) {
		//TODO:����splitter�ַ������ַ��������ݷָ�����δ洢��subs��
		int i = 0;
		int t = 0;
		while (i < length) {//�ж��Ƿ��Ѿ�ɨ��������
			int len = 0;//��¼�������ڵ�splitter֮��ĳ���
			while (items[i] != splitter && i < length) {//�ж������еĵ�i��Ԫ���Ƿ����splitter
				len++;//��������ڣ�����++
				i++;//i++�ж���һ��
			}
			if (len != 0) {//����һ��ʼ����splitter
				//TODO:ѭ�����������зָ����
				subs.items[t] = *this->subString(i - len - 1, len);//����subString�������δ���subs��
				subs.length++;//����subs��length
				t++;//t++Ϊ�˴洢��һ��subs.items
			}
			i++;
		}
	}

	void remove(int pos, int len) {
		//TODO��ɾ����pos��ʼ��len���ַ�
		int i;
		if (pos + len > length) {//���Ҫ����ԭ�ַ����ĳ��ȣ���ֱ���޸�ԭ�ַ�����length
			length = pos + 1;
		}
		else {
			for (i = pos; i < length - len; i++) //�Ѻ�����ַ���ǰ�����ǵ�ǰ����ַ�
				items[i] = items[i + len];
			length = length - len;//���³���
		}
	}

	void insert(String A, int pos) {
		//TODO����A���뵽posλ���� 
		if (pos >= length) {//���pos������length��ֱ���ν��ַ���A
			contact(A);
		}
		else {
			int i;
			for (i = A.length - 1; i >= 0; i--) {
				insertAt(pos, A.items[i]);//ֱ�ӵ���SeqList���insertAt����
			}
		}
	}

	int index(String &T, int pos = 0) {
		//TODO������T���ֵĵ�һ��λ�ã��Ҳ����򷵻�-1 
		if (T.length > length)//���ģʽ���ĳ��ȴ���������ֱ�ӷ���-1
			return -1;
		else {
			while (pos <= length - T.length) {//whileѭ����ֹ������pos���ƶ�������ĳ��Ⱦ�С��ģʽ���ˣ�û��Ҫ�ٱȽϣ�ֱ�ӷ���-1
				int i = pos;//����ÿ�αȽ��Ǵ�items[pos]��ʼ��
				int j = 0;//ģʽ��ÿ�αȽ��Ǵ�T.itmes[0]��ʼ��
				while (items[i] == T.items[j])//ֻҪ���ֲ���ȣ���pos++
				{
					i++; j++;
					if (j == T.length)//�ȽϽ���
						return pos;//����pos
				}
				pos++;
			}
			return -1;
		}
	}

	void replace(String &A, String &B) {
		//TODO:���ҵ�ǰ�ַ��������е�A���滻��B
		int i = 0;
		int flag = 0;//��¼�ҵ���A��������Ϊ���ж��Ƿ����A
		int pos;
		while (items[i]) {
			if (length - i - 1 < A.length)
				return;
			pos = index(A, i);
			if (flag == 0 && pos == -1)//ֻ��flag=0��pos=-1��������ű�ʾû���ҵ��Ӵ�A
				throw"NOT FOUND A";
			else if (flag != 0 && pos == -1)//flag������0��pos=-1��ʾ�����ַ����Ѿ�û���Ӵ�A��
				return;
			else {
				remove(pos, A.length);
				insert(B, pos);
				flag++;
			}
			i = pos + B.length - 1;
		}
	}

	void clear() {//ɾ����β�հ��ַ�
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