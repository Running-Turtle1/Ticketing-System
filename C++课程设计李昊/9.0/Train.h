#pragma once
#include "Basic.h"
#include "string.h"
#include "Trie.h"
#include "People.h"
using namespace std;

class Train
{
    public:
        Train(){}
        Train(string fcity, string tcity, string idnum, int full, int rest, int Cost, int dis);
        ~Train(){};

        void Modify_ticket_price(int money);
        void Modify_full_ticket(int num);
        void Modify_rest_ticket(int num);
        void Modify_zt();
        void Insert(People peo);
        void Output_people();
        void Exit_Ticket(string idnum);

        bool Get_zt();
        int Get_full_ticket();
        int Get_rest_ticket();
        int Get_ticket_cost();
        int Get_time_cost();
        string Get_Fcity();
        string Get_Tcity();
        string Get_idnum();
        static int Get_Count();
        static int Find_Train(string idnum);

        void Show_information();
    private:
        vector <People> vec;
        string Fcity, Tcity, Idnum;
        int Full, Rest, Cost, Dis;
        static int Count;
        static Trie Trie_tree;
        bool Suc;
}Tra[Maxn];
int Train :: Count = 0;
Trie Train :: Trie_tree;

void Train :: Modify_full_ticket(int num)   {Full = num; printf("修改成功!\n");}
void Train :: Modify_rest_ticket(int num)   {Rest = num; printf("修改成功!\n");}
void Train :: Modify_ticket_price(int money)    {Cost = money; printf("修改成功!\n");}
void Train :: Modify_zt()   {this->Suc = (this->Suc == 0 ? 1 : 0); printf("修改成功!\n");}

Train :: Train(string fcity, string tcity, string idnum, int full, int rest, int cost, int dis)
{
    ++Count;    Suc = 1;
    Fcity = fcity; Tcity = tcity; Idnum = idnum;
    Full = full; Rest = rest;   Cost = cost, Dis = dis;
    Trie_tree.Insert(Idnum, Count);
    vec.clear();
    return;
    cout << 111 << endl;
}
bool Train :: Get_zt()  {return Suc;}
int Train :: Get_full_ticket()  {return Full;}
int Train :: Get_rest_ticket()  {return Rest;}
int Train :: Get_ticket_cost()  {return Cost;}
int Train :: Get_time_cost()    {return Dis;}
string Train :: Get_Fcity() {return Fcity;}
string Train :: Get_Tcity() {return Tcity;}
string Train :: Get_idnum() {return Idnum;}

int Train :: Find_Train(string idnum)   {return Trie_tree.Find(idnum);}
int Train :: Get_Count()    {return Count;}
void Train :: Insert(People peo)
{
    this->vec.push_back(peo);
    printf("添加成功！\n");
}
void Train :: Output_people()
{
    int k = this->vec.size();
    if(k == 0)  printf("该高铁上暂无乘客购票！\n");
    else    for(int i = 0; i < k; i++)  this->vec[i].Show_Allinformation();
    getchar(); getchar();
}
void Train :: Show_information()
{
    printf("该高铁的车次号是：%8s\n", this->Idnum.c_str());
    printf("该高铁从 %6s 开往 %6s\n", this->Fcity.c_str(), this->Tcity.c_str());
    printf("该高铁总票数是：%3d张，剩余票数：%3d张\n", this->Full, this->Rest);
    printf("该高铁价格是：%3d元，预计耗时：%3d\n", this->Cost, this->Dis);
    printf("该高铁"); if(this->Suc == 0)    printf("暂不");printf("可用\n\n\n");    
}
void Train :: Exit_Ticket(string idnum)
{
    int k = this->vec.size();
    for(int i = 0; i < k; i++)
        if(vec[i].Get_idnum() == idnum)
        {
            vec[i].Modify_idnum_init();
            return;
        }
}