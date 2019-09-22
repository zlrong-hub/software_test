#include"stdafx.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h> 
#pragma warning(disable:4996)
using namespace std;
bool sign = false;
int w[10][10] = { 0 };
class sudoku
{
private:
	int n;
	int s[10][10];
public:
	sudoku()
	{
		n = 0;
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				s[i][j] = 0;
	}
	void sudoku_set(int m, int w[10][10])
	{
		n = m;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				s[i][j] = w[i][j];
		}
	}
	void output()//sudoku output
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				w[i][j] = s[i][j];
		}
	}
	bool check1(int m, int key);
	bool check2(int m, int key);
	int f(int m);
};
bool sudoku::check1(int m, int key)//judge line and row
{
	for (int i = 0; i < n; i++) //judge line
	{
		int j = m / n;
		if (s[j][i] == key) return false;
	}
	for (int i = 0; i < n; i++) //judge row
	{
		int j = m % n;
		if (s[i][j] == key) return false;
	}
	return true;
}
bool sudoku::check2(int m, int key)
{
	int x, y;
	if (n == 9)
	{
		x = m / 9 / 3 * 3;
		y = m % 9 / 3 * 3;
		for (int i = x; i < x + 3; i++)
			for (int j = y; j < y + 3; j++)
				if (s[i][j] == key) return false;
	}
	else if (n == 8)
	{
		x = m / 8 / 2 * 2;//small sudoku's x
		y = m % 8 / 2 * 2;//small sudoku's y
		for (int i = x; i < x + 4; i++)
			for (int j = y; j < y + 2; j++)
				if (s[i][j] == key) return false;
	}
	else if (n == 6)
	{
		x = m / 6 / 2 * 2;
		y = m % 6 / 3 * 3;
		for (int i = x; i < x + 2; i++)
			for (int j = y; j < y + 3; j++)
				if (s[i][j] == key) return false;
	}
	else {
		x = m / 4 / 2 * 2;
		y = m % 4 / 2 * 2;
		for (int i = x; i < x + 2; i++)
			for (int j = y; j < y + 2; j++)
				if (s[i][j] == key) return false;
	}
	return true;
}
int sudoku::f(int m)
{
	if (m >= n * n) {
		sign = true;
		return 0;
	}
	if (s[m / n][m%n] != 0) f(m + 1);
	else {
		for (int i = 1; i <= n; i++)
		{
			if (n == 3 || n == 5 || n == 7)
			{
				if (check1(m, i) == true)
				{
					s[m / n][m%n] = i;
					f(m + 1);
					if (sign == true) return 0;
					s[m / n][m%n] = 0;
				}
			}
			else
			{
				if (check1(m, i) == true && check2(m, i) == true)
				{
					s[m / n][m%n] = i;
					f(m + 1);
					if (sign == true) return 0;
					s[m / n][m%n] = 0;
				}
			}
		}
	}
	return 0;
}
sudoku p[100];
int main(int argc, char *argv[])
{
	int m=0, x=0;
	FILE *fp;
	if (argc > 1)
	{
		m = atoi(argv[2]);
		x = atoi(argv[4]);
	}
	fp = fopen("input.txt", "r");
	if (fp == NULL) return 1;
	for (int i = 0; i < x; i++)
	{
		sign = false;
		int j = 0, k = 0;
		while (j != m)
		{
			fscanf(fp, "%d", &w[j][k]);
			k++;
			if (k == m)
			{
				k = 0;
				j++;
			}
		}
		p[i].sudoku_set(m, w);
		p[i].f(0);
	}
	fclose(fp);
	fp = fopen("output.txt", "w");
	if (fp == NULL) return 1;
	for (int i = 0; i < x; i++)
	{
		p[i].output();
		for (int j = 0; j < m; j++)
		{
			for (int k = 0; k < m; k++)
				fprintf(fp, "%d ", w[j][k]);
			fprintf(fp, "\n");
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	return 0;
}


