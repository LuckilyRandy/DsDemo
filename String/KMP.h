#pragma once
#include <iostream>
#include "String.h" 
#include "time.h" 

//暴力匹配算法
int Index(const char *S, const char *T, int pos = 0) {//从pos位置开始查找T，返回T最早出现的位置，如果不存在T，返回-1 
	int n = strlen(S), m = strlen(T);//n是S的长度，m是T的长度
	int i = pos, j = 0;
	while (i < n&&j < m) {
		if (S[i] == T[j]) {
			++i;
			++j;
		}//匹配则一并移动两个指针 
		else {
			i = i - j + 1;
			j = 0;
		}//失配则后退重新开始 
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
	//TODO：实现KMP匹配算法 
	int n = strlen(S), m = strlen(T);//n是S的长度，m是T的长度
	int i = pos, j = 0;
	while (i < n&&j < m) {
		if (S[i] == T[j]) {
			++i;
			++j;
		}//匹配则一并移动两个指针 
		else j = next[j];//失配
	}
	if (j == m)
		return i - m;
	return -1;
}