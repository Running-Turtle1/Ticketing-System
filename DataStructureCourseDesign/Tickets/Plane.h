#pragma once
#include "Basic.h"
#include "string.h"
#include "People.h"
#include "Trie.h"
using namespace std;

class Plane
{
    public:
        Plane(){}
        Plane(string fcity, string tcity, string idnum, int full, int rest, int Cost, int dis);
        ~Plane(){};

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
        static int Find_plane(string idnum);

        void Show_information();
    private:
        vector <People> vec;
        string Fcity, Tcity, Idnum;
        int Full, Rest, Cost, Dis;
        static int Count;
        static Trie Trie_tree;
        bool Suc;
}Pla[Maxn];
int Plane :: Count = 0;
Trie Plane :: Trie_tree;

void Plane :: Modify_full_ticket(int num)   {Full = num; }
void Plane :: Modify_rest_ticket(int num)   {Rest = num; }
void Plane :: Modify_ticket_price(int money)    {Cost = money; printf("�޸ĳɹ�!\n");}
void Plane :: Modify_zt()   {this->Suc = (this->Suc == 0 ? 1 : 0); printf("�޸ĳɹ�!\n");}
void Plane :: Insert(People peo)
{
    this->vec.push_back(peo);
    printf("��ӳɹ���\n");
}
void Plane :: Output_people()
{
    int k = this->vec.size();
    if(k == 0)  printf("�ú��������޳˿͹�Ʊ��\n");
    else    for(int i = 0; i < k; i++)  
        if(vec[i].Get_idnum() == "000")   continue;
        else    vec[i].Show_Allinformation();
    getchar();
}
Plane :: Plane(string fcity, string tcity, string idnum, int full, int rest, int cost, int dis)
{
    ++Count;    Suc = 1;
    Fcity = fcity; Tcity = tcity; Idnum = idnum;
    Full = full; Rest = rest;   Cost = cost;  Dis = dis;
    Trie_tree.Insert(Idnum, Count);
}
bool Plane :: Get_zt()  {return Suc;}
int Plane :: Get_full_ticket()  {return Full;}
int Plane :: Get_rest_ticket()  {return Rest;}
int Plane :: Get_ticket_cost()  {return Cost;}
int Plane :: Get_time_cost()    {return Dis;}
string Plane :: Get_Fcity() {return Fcity;}
string Plane :: Get_Tcity() {return Tcity;}
string Plane :: Get_idnum() {return Idnum;}

int Plane :: Find_plane(string idnum)   {return Trie_tree.Find(idnum);}
int Plane :: Get_Count()    {return Count;}

void Plane :: Show_information()
{
    printf("�ú���ĺ�����ǣ�%8s\n", this->Idnum.c_str());
    printf("�ú���� %6s ���� %6s\n", this->Fcity.c_str(), this->Tcity.c_str());
    printf("�ú�����Ʊ���ǣ�%3d�ţ�ʣ��Ʊ����%3d��\n", this->Full, this->Rest);
    printf("�û�Ʊ�۸��ǣ�%3dԪ��Ԥ�ƺ�ʱ��%3d\n", this->Cost, this->Dis);
    printf("�ú���"); if(this->Suc == 0)    printf("�ݲ�");printf("����\n\n\n");  
    Sleep(400);  
}

void Plane :: Exit_Ticket(string idnum)
{
    int k = this->vec.size();
    for(int i = 0; i < k; i++)
        if(vec[i].Get_idnum() == idnum)
        {
            vec[i].Modify_idnum_init();
            return;
        }
}