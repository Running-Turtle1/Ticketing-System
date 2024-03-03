#pragma once
#include "Basic.h"
#include "Pair.h"
#include "string.h"
#include "vector"
#include "Check.h"
#include "Trie.h"
class People
{
    public:
        People(){}
        People(string name, string idnum, string sex, int age, string tpnum);
        People(const People &p);
        ~People(){}

        void Clear();
        void Show_Allinformation(int Pos);
        void Show_Allinformation();
        void Modify_Telephonenum(string s);
        void Modify_Ticket(int pos);
        void Modify_idnum_init();
        void Exit_one_ticket(int k);
        string Get_idnum(){return Idnum;}
        void Exit_ticket();
        static int Get_Count(){return Count;}
        static int Find_People(string idnum);
        static void Input();

    private:
        static int Count;
        string Name, Idnum, Sex, Tpnum;
        vector <int> vec;
        static Trie Trie_tree;
        int Age;
}Peo[Maxn];
Trie People :: Trie_tree;
int People :: Count = 0;

People :: People(string name, string idnum, string sex, int age, string tpnum)
{
    Name = name, Idnum = idnum, Sex = sex, Age = age, Tpnum = tpnum;
}
People :: People(const People &p)
{
    Name = p.Name, Idnum = p.Idnum, Sex = p.Sex, Age = p.Age, Tpnum = p.Tpnum;
}
void People :: Exit_ticket()
{
    int k = this->vec.size();
    for(int i = 0; i < k; i++)
        if(vec[i] != 0)
        {
            ass[++ass[0]] = vec[i];
        }
}
void People :: Clear()
{
    this->Idnum = "000";
}
void People :: Exit_one_ticket(int k)
{
    int len = this->vec.size();
    for(int i = 0; i < len; i++)
        if(this->vec[i] == k)
        {
            this->vec[i] = 0;
            return;
        }
}
void People :: Input()
{
    string name, idnum, tpnum, sex, age;
    
    printf("请输入您的姓名：");
    cin >> name;
    while(Check_Name(name) == 0)    ReRead(name);

    printf("请输入您的身份证号：");
    cin >> idnum;
    while(Check_Idnum(idnum) == 0)  ReRead(idnum);

    printf("请输入您的联系方式：");
    cin >> tpnum;
    while(Check_Telephonenum(tpnum) == 0)   ReRead(tpnum);

    printf("请输入您的性别：");
    cin >> sex;
    while(Check_Sex(sex) == 0)  ReRead(sex);

    printf("请输入您的年龄：");
    cin >> age;
    while(Check_Age(age) == 0)  ReRead(age);

    Peo[++Count] = People(name, idnum, sex, ToInt(age), tpnum);
    Trie_tree.Insert(idnum, Count);
}

void People :: Modify_Telephonenum(string s)
{
    while(Check_Telephonenum(s) == 0)   ReRead(s);
    printf("修改成功！\n");
    Tpnum = s;
}
void People :: Modify_Ticket(int pos)
{
    this->vec.push_back(pos);
}
void People :: Modify_idnum_init()
{
    this->Idnum = "000";
}
void People :: Show_Allinformation(int Pos)
{
    printf("姓名：%s", Peo[Pos].Name.c_str());
    printf("\n身份证号：%s", Peo[Pos].Idnum.c_str());
    printf("\n性别：%s     年龄：%d", Peo[Pos].Sex.c_str(), Peo[Pos].Age);
    printf("\n手机号：%s", Peo[Pos].Tpnum.c_str());
    printf("\n");
    Sleep(300);
}
void People :: Show_Allinformation()
{
    printf("姓名：%s", this->Name.c_str());
    printf("\n身份证号：%s", this->Idnum.c_str());
    printf("\n性别：%s     年龄：%d", this->Sex.c_str(), this->Age);
    printf("\n手机号：%s", this->Tpnum.c_str());
    printf("\n");
    Sleep(300);
}
int People :: Find_People(string idnum)   {return Trie_tree.Find(idnum);}