#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
using namespace std;
#define Not_Find -1
#define Maxn 1000 + 40
#define Maxm 300 + 3
int ass[1000];
int read()
{
    int rt = 0, in = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-') in = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') {rt = rt * 10 + ch - '0'; ch = getchar();}
    return rt * in;
}

void print(int x)
{
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
int ToInt(string s)
{
    int Num = 0, len = s.size();
    for(int i = 0; i < len; i++)
        Num = Num * 10 + s[i] - '0';
    return Num;
}

double ToDouble(string s)
{
    double Num1 = 0, Num2 = 0, len = s.size();
    bool flag = 0;
    for(int i = 0; i < len; i++)
        if(!flag)   Num1 = Num1 * 10 + s[i] - '0';
        else if(s[i] == '.')    flag = 1;
        else    Num2 = Num2 * 10 + s[i] - '0';
    while(Num2 >= 1)    Num2 /= 10;
    return Num1 + Num2;
}