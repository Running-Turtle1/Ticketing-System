#pragma once
#include "Basic.h"

class Check
{
    public:
        friend bool Check_Name(string s);
        friend bool Check_Idnum(string s);
        friend bool Check_Telephonenum(string s);
        friend bool Check_Sex(string s);
        friend bool Check_Choose(int l, int r, string s);
        friend bool Check_Num(string s);
        friend bool Check_Planenum(string s);
        friend void ReRead(string &s);
};

bool Check_Name(string s)
{
    bool flag = 1;
    if(s.size() < 1 || s.size() > 20)   flag = 0;
    return flag == 1 ? true : false;
}

bool Check_Idnum(string s)
{
    bool flag = 1;
    int len = s.size();
    for(int i = 0; i < len - 1; i++)
        if(s[i] < '0' || s[i] > '9')    flag = 0;
    if(len != 18)   flag = 0;
    if(!(s[len - 1] == 'x' || s[len - 1] == 'X' || (s[len - 1] >= '0' && s[len - 1] <= '9') )) flag = 0;
    // if(s[len - 1] != 'x' && s[len - 1] != 'X' && (s[len - 1] >= '0' && s[len - 1] <= '9'))  flag = 0;
    return flag == 1 ? true : false;
}

bool Check_Telephonenum(string s)
{
    int len = s.size();
    bool flag = 1;
    if(len != 11)   flag = 0;
    for(int i = 0; i < len; i++)
        if(s[i] < '0' || s[i] > '9')    flag = 0;
    return flag == 1 ? true : false;
}

bool Check_Sex(string s)
{
    bool flag = 0;
    if(s == "?" || s == "?")  flag = 1;
    return flag == 1 ? true :false;
}

bool Check_Age(string s)
{
    bool flag = 1;
    int len = s.size();
    for(int i = 0; i < len; i++)
        if(s[i] < '0' || s[i] > '9')    flag = 0;
    if(len > 2) flag = 0;
    return flag == 1 ? true : false;
}

bool Check_Choose(int l, int r, string s)
{
    bool flag = 1;
    int len = s.size();
    for(int i = 0; i < len; i++)
        if(s[i] < '0' || s[i] > '9')    flag = 0;
    if(!flag)   return false;
    int Num = ToInt(s);
    if(Num < l || Num > r)  return false;
    return true;
}
bool Check_Num(string s)
{
    int k = s.size();
    bool flag = true;
    for(int i = 0; i < k; i++)
        if(s[i] < '0' || s[i] > '9')
            flag = false;
    return flag;
}
bool Check_Planenum(string s)
{
    int k = s.size();
    bool flag = true;
    if(k != 6)  flag = false;
    if(!flag)   return false;
    for(int i = 0; i < 2; i++)
        if(s[i] < 'A' || s[i] > 'Z')    flag = false;
    for(int i = 2; i < 6; i++)
        if(s[i] < '0' || s[i] > '9')    flag = false;
    return flag;
}
void ReRead(string &s)  {printf("您的输入不合法,请重新输入:"); cin >> s;}

