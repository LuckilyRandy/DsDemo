#pragma once
#include <iostream>
#include "String.h" 
#include "time.h" 

//����ƥ���㷨
int Index(const char *S, const char *T, int pos = 0) {//��posλ�ÿ�ʼ����T������T������ֵ�λ�ã����������T������-1 
	int n = strlen(S), m = strlen(T);//n��S�ĳ��ȣ�m��T�ĳ���
	int i = pos, j = 0;
	while (i < n&&j < m) {
		if (S[i] == T[j]) {
			++i;
			++j;
		}//ƥ����һ���ƶ�����ָ�� 
		else {
			i = i - j + 1;
			j = 0;
		}//ʧ����������¿�ʼ 
	}
	if (j == m)
		return i - m;
	return -1;
}

void get_next(const char *T, int next[]) {
	int i = 0;
	next[i] = -1;
	int j = -1;
	int m = strlen(T);
	while (i < m) {
		if (j == -1 || T[i] == T[j]) {
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];
	}
}

int Index_KMP(const char *S, const char *T, int next[], int pos = 0) {
	//TODO��ʵ��KMPƥ���㷨 
	int n = strlen(S), m = strlen(T);//n��S�ĳ��ȣ�m��T�ĳ���
	int i = pos, j = 0;
	while (i < n&&j < m) {
		if (S[i] == T[j]) {
			++i;
			++j;
		}//ƥ����һ���ƶ�����ָ�� 
		else j = next[j];//ʧ��
	}
	if (j == m)
		return i - m;
	return -1;
}