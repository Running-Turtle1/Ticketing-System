#pragma once
#include "People.h"
#include <sstream>
#include <string.h>
#include "string.h"
#include <fstream>
#include <iomanip>
#include <cassert>
#include "conio.h"
#include "cstdlib"
#include "Priority_queue.h"
#include "Pair.h"
#include "Plane.h"
#include "Train.h"
#include "Function.h"
using namespace std;
class UI
{
    public:
        friend bool Show_UI();
        static void Management();
        static bool Management_UI_Plane();
        static bool Management_UI_Train();
        static bool Passenger();
        static void Init_train();
        static void Init_plane();
};

void UI :: Management()
{
    system("cls");
    string Account, Password;
    printf("�������ʺţ�");
    cin >> Account;
    // cout << Account << endl;
    printf("���������룺");
    char ch;
    while ((ch = _getch())!=13)
    {
        Password += ch;
        cout << "*";
    }
    printf("\n");
    ifstream fp2("A&P.txt");
    bool login = false;
    while(!fp2.eof())
    {
        string str1, str2;
        fp2 >> str1 >> str2;
        if(str1 == Account && str2 == Password) login = true;
    }
    fp2.close();
    if(!login)
    {
        printf("�ʺ��������\n");
        getchar();
        return;
    }
    cout << "��½�ɹ���\n" << endl;
    getchar();
    while(login)   
    {
        system("cls");
        cout << "��Ҫ�޸����ֽ�ͨ���ߵ������Ϣ?\n1.������Ϣ\n2.������Ϣ\n3.����������\n����ѡ���ǣ�";
        string ins1;
        cin >> ins1;
        while(Check_Choose(1, 3, ins1) == 0)    ReRead(ins1);
        if(ins1 == "1") UI :: Management_UI_Plane();
        else if(ins1 == "2")    UI :: Management_UI_Train();
        else if(ins1 == "3")   break;
    }
    return;
}
bool UI :: Management_UI_Plane()
{
    system("cls");
    printf("����Ա����֧�ֵĹ������£�\n��1.�޸�Ʊ��\n\n��2.ʵ�з�Ʊ\n\n��3.������\n\n��4.��ͣ/���ú���\n\n��5.������༰��˿���Ϣ\n\n��6.������һ��\n\n");
    printf("����ѡ���ǣ�");
    string ins;
    cin >> ins;
    while(Check_Choose(1, 6, ins) == false)  ReRead(ins);
    int Num = ToInt(ins);
    system("cls");
    if(Num == 1)
    {
        printf("��ǰ���ܣ��޸ĺ���Ʊ�ۣ�\n\n");
        string Plane_num;
        printf("��Ҫ�޸ĵĺ���ĺ�����ǣ�");
        cin >> Plane_num;
        int k = Plane :: Find_plane(Plane_num);
        if(k == -1)
        {
            printf("δ��ѯ���ú��࣡\n�޸�ʧ��\n����������أ�\n");
            getchar(); getchar();
        }
        else
        {
            printf("�ú������Ϣ���£�\n");
            Pla[k].Show_information();
            string Cost1;
            printf("��Ҫ�޸�Ϊ��");
            cin >> Cost1;
            while(Check_Num(Cost1) == 0)    ReRead(Cost1);
            Pla[k].Modify_ticket_price(ToInt(Cost1));
            printf("\n�޸ĳɹ�\n");
        }
        return 1;
    }
    else if(Num == 2)
    {
        printf("��ǰ���ܣ���Ʊ����\n\n");
        string Plane_num;
        printf("��Ҫ���з�Ʊ�ĺ���ĺ�����ǣ�");
        cin >> Plane_num;
        int k = Plane :: Find_plane(Plane_num);
        if(k == -1)
        {
            printf("δ��ѯ���ú��࣡\n�޸�ʧ��\n����������أ�\n");
            getchar();getchar();
        }
        else
        {
            printf("�ú������Ϣ���£�\n");
            Pla[k].Show_information();
            int waitnum = Wait[k].Size();
            if(waitnum == 0)
            {
                printf("�ú��������Ʊ��\n");
                getchar(); getchar();
                return true;
            }
            printf("�ú��೬������Ϊ��%d\n", waitnum);
            printf("������Ա��Ϣ���£�\n");
            Pla[k].Show_information();
            printf("��Ҫ������Ʊ��Ϊ��");
            string tnum;
            cin >> tnum;
            while(Check_Num(tnum) == 0) ReRead(tnum);
            int Curticket = Pla[k].Get_full_ticket(), Currstticket = Pla[k].Get_rest_ticket();
            Pla[k].Modify_full_ticket(Curticket + ToInt(tnum));
            Pla[k].Modify_rest_ticket(max(ToInt(tnum) - waitnum, 0));
            for(int i = 1; i <= min(waitnum, ToInt(tnum)); i++)
            {
                printf("��%2d����Ʊ�û���Ϣ���£�\n", i);
                People temp = Wait[k].Top().second;
                Pla[k].Insert(Wait[k].Top().second);
                int k3 = People :: Find_People(Wait[k].Top().second.Get_idnum());
                Peo[k3].Modify_Ticket(-k);
                temp.Show_Allinformation();
                Wait[k].Pop();
            }
            printf("\n��Ʊ�ɹ���\n");
            getchar();
        }
        return true;
    }
    else if(Num == 3)
    {
        printf("��ǰ���ܣ����Ӻ��࣡\n\n");
        string fcity, tcity, pnum;
        printf("������ú�������:");
        cin >> fcity;
        printf("������ú�����յ�:");
        cin >> tcity;
        printf("������ú���ĺ����:");
        cin >> pnum;
        while(Check_Planenum(pnum) == 0 || Plane :: Find_plane(pnum) != -1) ReRead(pnum);
        string costmoney, fullticket, distance;
        printf("������ú����Ʊ�ļ۸�");
        cin >> costmoney;
        while(Check_Num(costmoney) == 0)    ReRead(costmoney);
        printf("������ú����Ԥ�ƺ�ʱ��");
        cin >> distance;
        while(Check_Num(distance) == 0)     ReRead(distance);
        printf("������ú����Ʊ����Ʊ����");
        cin >> fullticket;
        while(Check_Num(fullticket) == 0)   ReRead(fullticket);
        int Pos = Plane :: Get_Count();
        Pla[++Pos] = Plane(fcity, tcity, pnum, ToInt(fullticket), ToInt(fullticket), ToInt(costmoney), ToInt(distance));
        system("cls");
        printf("��ӳɹ���\n�ú�����Ϣ���£�");
        Pla[Pos].Show_information();
        getchar();getchar();
    }
    else if(Num == 4)
    {
        printf("��ǰ���ܣ���ͣ/���ú��࣡\n\n");
        string Plane_num;
        printf("��Ҫ��ͣ�ĺ���ĺ�����ǣ�");
        cin >> Plane_num;
        int k = Plane :: Find_plane(Plane_num);
        if(k == -1)
        {
            printf("δ��ѯ���ú��࣡\n����ʧ��\n����������أ�\n");
            getchar(); getchar();
        }
        else
        {
            printf("�ú�����Ϣ���£�");
            Pla[k].Show_information();
            int Flag = Pla[k].Get_zt();
            if(Flag == 0)
            {
                printf("���Ƿ�ȷ�����øú��ࣿ\n���Y��ʾȷ��������N��ʾ��\n");
                string inst1;
                cin >> inst1;
                while(inst1 != "Y" && inst1 != "N") {printf("����������������룡\n"); cin >> inst1;}
                if(inst1 == "Y")    Pla[k].Modify_zt();
            }
            else
            {
                printf("���Ƿ�ȷ����ͣ�ú��ࣿ\n���Y��ʾȷ��������N��ʾ��\n");
                string inst1;
                cin >> inst1;
                while(inst1 != "Y" && inst1 != "N") {printf("����������������룡\n"); cin >> inst1;}
                if(inst1 == "Y")    Pla[k].Modify_zt();
            }
            getchar(); getchar();
            return true;
        }
    }
    else if(Num == 5)
    {
        printf("��ǰ���ܣ�������༰��˿���Ϣ��\n\n");
        printf("\n�ù���ϸ��Ϊ��\n1.��ѯָ������ŵĺ�����Ϣ\n2.���β�ѯ���к���\n3.�������յ��ѯ������Ϣ��\n\n");
        string instr;
        cin >> instr;
        while(Check_Choose(1, 3, instr) == 0)   ReRead(instr);
        system("cls");
        if(instr == "1")
        {
            printf("��������Ҫ��ѯ�ĺ���ĺ���ţ�");
            string idnum;
            cin >> idnum;
            while(Check_Planenum(idnum) == 0)   ReRead(idnum);
            int k = Plane :: Find_plane(idnum);
            if(k == -1) printf("δ�鵽�ú��࣡\n");
            else    Pla[k].Show_information();
        }
        else if(instr == "2")
        {
            int Cnt = Plane :: Get_Count();
            for(int i = 1; i <= Cnt; i++)
            {
                Pla[i].Show_information();
                printf("�Ƿ�鿴�ú���Ĺ�Ʊ��Ա��Ϣ��\n����鿴������Y���������N������E�������˵�\n����ѡ���ǣ�");
                string inst1;
                cin >> inst1;
                while(inst1 != "Y" && inst1 != "N" && inst1 != "E") {printf("�����������������룺"); cin >> inst1;}
                if(inst1 == "Y")    Pla[i].Output_people();
                if(inst1 == "E")    return true;
                printf("\n\n\n");
            }
            printf("\n\n��ѯ��ɣ�2��󷵻�");
            Sleep(2000);
        }
        else if(instr == "3")
        {
            bool flag = 0;
            string S, T;
            printf("��Ҫ��ѯ�ĺ��������ǣ�");
            cin >> S;
            printf("��Ҫ��ѯ�ĺ�����յ��ǣ�");
            cin >> T;
            int Cnt = Plane :: Get_Count();
            for(int i = 1; i <= Cnt; i++)
            {
                string s1 = Pla[i].Get_Fcity();
                string t1 = Pla[i].Get_Tcity();
                if(S == s1 && T == t1)
                {
                    flag = 1;
                    Pla[i].Show_information();
                }  
            }
            if(!flag)   printf("δ��ѯ����غ���\n");
        }
        Sleep(2000);
    }
    else if(Num == 6)    return 0;
    return 1;
}
bool UI :: Management_UI_Train()
{
    system("cls");
    printf("����Ա����֧�ֵĹ������£�\n��1.�޸�Ʊ��\n\n��2.ʵ�з�Ʊ\n\n��3.�������\n\n��4.��ͣ/���ø���\n\n��5.�����������˿���Ϣ\n\n��6.������һ��\n\n");
    printf("����ѡ���ǣ�");
    string ins;
    cin >> ins;
    while(Check_Choose(1, 6, ins) == false)  ReRead(ins);
    int Num = ToInt(ins);
    system("cls");
    if(Num == 1)
    {
        printf("��ǰ���ܣ��޸ĸ���Ʊ�ۣ�\n\n");
        string Train_num;
        printf("��Ҫ�޸ĵĸ����ĳ��κ��ǣ�");
        cin >> Train_num;
        int k = Train :: Find_Train(Train_num);
        if(k == -1)
        {
            printf("δ��ѯ���ø�����\n�޸�ʧ��\n����������أ�\n");
            getchar(); getchar();
        }
        else
        {
            printf("�ø�������Ϣ���£�\n");
            Tra[k].Show_information();
            string Cost1;
            printf("��Ҫ�޸�Ϊ��");
            cin >> Cost1;
            while(Check_Num(Cost1) == 0)    ReRead(Cost1);
            Tra[k].Modify_ticket_price(ToInt(Cost1));
            printf("\n�޸ĳɹ�\n");
        }
        return true;
    }
    else if(Num == 2)
    {
        printf("��ǰ���ܣ���Ʊ����\n\n");
        string Train_num;
        printf("��Ҫ���з�Ʊ�ĸ����ĳ��κ��ǣ�");
        cin >> Train_num;
        int k = Train :: Find_Train(Train_num);
        if(k == -1)
        {
            printf("δ��ѯ���ø�����\n�޸�ʧ��\n����������أ�\n");
            getchar();getchar();
        }
        else
        {
            printf("�ø�������Ϣ���£�\n");
            Tra[k].Show_information();
            int waitnum = Wait2[k].Size();
            if(waitnum == 0)
            {
                printf("�ø��������Ʊ��\n");
                getchar(); getchar();
                return true;
            }
            printf("�ø�����������Ϊ��%d\n", waitnum);
            printf("������Ա��Ϣ���£�\n");
            Tra[k].Show_information();
            printf("��Ҫ������Ʊ��Ϊ��");
            string tnum;
            cin >> tnum;
            while(Check_Num(tnum) == 0) ReRead(tnum);
            int Curticket = Tra[k].Get_full_ticket(), Currstticket = Tra[k].Get_rest_ticket();
            Tra[k].Modify_full_ticket(Curticket + ToInt(tnum));
            Tra[k].Modify_rest_ticket(max(ToInt(tnum) - waitnum, 0));
            for(int i = 1; i <= min(waitnum, ToInt(tnum)); i++)
            {
                printf("��%2d����Ʊ�û���Ϣ���£�\n", i);
                People temp = Wait2[k].Top().second;
                Tra[k].Insert(Wait2[k].Top().second);
                int k3 = People :: Find_People(Wait2[k].Top().second.Get_idnum());
                Peo[k3].Modify_Ticket(k);
                temp.Show_Allinformation();
                Wait2[k].Pop();
            }
            printf("\n��Ʊ�ɹ���\n");
            getchar();
        }
        return true;
    }
    else if(Num == 3)
    {
        printf("��ǰ���ܣ����Ӹ�����\n\n");
        string fcity, tcity, pnum;
        printf("������ø��������:");
        cin >> fcity;
        printf("������ø������յ�:");
        cin >> tcity;
        printf("������ø����ĳ��κ�:");
        cin >> pnum;
        while(Check_Planenum(pnum) == 0 || Train :: Find_Train(pnum) != -1) ReRead(pnum);
        string costmoney, fullticket, distance;
        printf("������ø���Ʊ�ļ۸�");
        cin >> costmoney;
        while(Check_Num(costmoney) == 0)    ReRead(costmoney);
        printf("������ú����Ԥ�ƺ�ʱ��");
        cin >> distance;
        while(Check_Num(distance) == 0)     ReRead(distance);
        printf("������ø���Ʊ����Ʊ����");
        cin >> fullticket;
        while(Check_Num(fullticket) == 0)   ReRead(fullticket);
        int Pos = Train :: Get_Count();
        Tra[++Pos] = Train(fcity, tcity, pnum, ToInt(fullticket), ToInt(fullticket), ToInt(costmoney), ToInt(distance));
        system("cls");
        printf("��ӳɹ���\n�ø�����Ϣ���£�");
        Tra[Pos].Show_information();
        getchar();getchar();
    }
    else if(Num == 4)
    {
        printf("��ǰ���ܣ���ͣ/���ø�����\n\n");
        string Train_num;
        printf("��Ҫ��ͣ�ĸ����ĳ��κ��ǣ�");
        cin >> Train_num;
        int k = Train :: Find_Train(Train_num);
        if(k == -1)
        {
            printf("δ��ѯ���ø�����\n����ʧ��\n����������أ�\n");
            getchar(); getchar();
        }
        else
        {
            printf("�ø�����Ϣ���£�");
            Tra[k].Show_information();
            int Flag = Pla[k].Get_zt();
            if(Flag == 0)
            {
                printf("���Ƿ�ȷ�����øø�����\n���Y��ʾȷ��������N��ʾ��\n");
                string inst1;
                cin >> inst1;
                while(inst1 != "Y" && inst1 != "N") {printf("����������������룡\n"); cin >> inst1;}
                if(inst1 == "Y")    Tra[k].Modify_zt();
            }
            else
            {
                printf("���Ƿ�ȷ����ͣ�ø�����\n���Y��ʾȷ��������N��ʾ��\n");
                string inst1;
                cin >> inst1;
                while(inst1 != "Y" && inst1 != "N") {printf("����������������룡\n"); cin >> inst1;}
                if(inst1 == "Y")    Tra[k].Modify_zt();
            }
            getchar(); getchar();
            return true;
        }
    }
    else if(Num == 5)
    {
        printf("��ǰ���ܣ������������˿���Ϣ��\n\n");
        printf("\n�ù���ϸ��Ϊ��\n1.��ѯָ�������ŵĺ�����Ϣ\n2.���β�ѯ���и���\n3.�������յ��ѯ������Ϣ��\n\n");
        string instr;
        cin >> instr;
        while(Check_Choose(1, 3, instr) == 0)   ReRead(instr);
        system("cls");
        if(instr == "1")
        {
            printf("��������Ҫ��ѯ�ĸ����ĸ����ţ�");
            string idnum;
            cin >> idnum;
            while(Check_Planenum(idnum) == 0)   ReRead(idnum);
            int k = Train :: Find_Train(idnum);
            if(k == -1) printf("δ�鵽�ø�����\n");
            else    Tra[k].Show_information();
        }
        else if(instr == "2")
        {
            int Cnt = Train :: Get_Count();
            for(int i = 1; i <= Cnt; i++)
            {
                Tra[i].Show_information();
                printf("�Ƿ�鿴�ø����Ĺ�Ʊ��Ա��Ϣ��\n����鿴������Y���������N������E�������˵�\n����ѡ���ǣ�");
                string inst1;
                cin >> inst1;
                while(inst1 != "Y" && inst1 != "N" && inst1 != "E") {printf("�����������������룺"); cin >> inst1;}
                if(inst1 == "Y")    Tra[i].Output_people();
                if(inst1 == "E")    return true;
                printf("\n\n\n");
            }
            printf("\n\n��ѯ��ɣ�2��󷵻�");
            Sleep(2000);
        }
        else if(instr == "3")
        {
            bool flag = 0;
            string S, T;
            printf("��Ҫ��ѯ�ĸ���������ǣ�");
            cin >> S;
            printf("��Ҫ��ѯ�ĸ������յ��ǣ�");
            cin >> T;
            int Cnt = Train :: Get_Count();
            for(int i = 1; i <= Cnt; i++)
            {
                string s1 = Tra[i].Get_Fcity();
                string t1 = Tra[i].Get_Tcity();
                if(S == s1 && T == t1)
                {
                    flag = 1;
                    Tra[i].Show_information();
                }  
            }
            if(!flag)   printf("δ��ѯ����ظ���\n");
        }
        Sleep(2000);
    }
    else if(Num == 6)    return 0;
    return 1;
}
void UI :: Init_plane()
{
    ifstream fp4("data_plane.txt");
    int n;
    fp4 >> n;
    for(int i = 1; i <= n; i++)
    {
        string fcity, tcity, pnum;
        fp4 >> fcity;
        fp4 >> tcity;
        fp4 >> pnum;
        string costmoney, fullticket, distance;
        fp4 >> costmoney;
        fp4 >> distance;
        fp4 >> fullticket;
        int Pos = Plane :: Get_Count();
        Pla[++Pos] = Plane(fcity, tcity, pnum, ToInt(fullticket), ToInt(fullticket), ToInt(costmoney), ToInt(distance));
    }
    fp4.close();
    cout << "������Ϣ¼��ɹ���\n";

    Sleep(2000);
}
void UI :: Init_train()
{
    system("cls");
    ifstream fp5("data_train.txt");
    int n;
    fp5 >> n;
    for(int i = 1; i <= n; i++)
    {
        string s1, s2, s3;
        fp5 >> s1;
        fp5 >> s2;
        fp5 >> s3;
        string s4, s5, s6;
        fp5 >> s4;
        fp5 >> s5;
        fp5 >> s6;
        // cout << costmoney << " " << distance << " " << fullticket << endl;
        int Pos = Train :: Get_Count();
        Tra[++Pos] = Train(s1, s2, s3, ToInt(s4), ToInt(s4), ToInt(s5), ToInt(s6));
        // cout << 222 << endl;
    }
    fp5.close();
    cout << "������Ϣ¼��ɹ���\n";
    Sleep(2000);
}
bool Show_UI()
{
    system("cls");
    ifstream fp1("UI.txt");
    while(!fp1.eof())
    {
        string str;
        getline(fp1, str, '\n');
        cout << str << endl;
    }
    fp1.close();
    printf("����ѡ���ǣ�");
    string ins;
    cin >> ins;
    while(Check_Choose(0, 5, ins) == 0) ReRead(ins);
    if(ins == "0")  return 0;
    else if(ins == "1")  UI :: Management();
    else if(ins == "2") UI :: Passenger();
    else if(ins == "3") Function :: UI_Function();
    else if(ins == "4") 
    {
        UI :: Init_train();
        UI :: Init_plane();
        
    }
    else {
        return false;
    }
    return true;
}
bool UI :: Passenger()
{
    system("cls");
    printf("�û�����֧�ֵĹ������£�\n\n");
    printf("��1.��Ʊ\n\n��2.��Ʊ\n\n��3.����/����Ʊ����\n\n");
    string ins;
    cin >> ins;
    while(Check_Choose(1, 3, ins) == 0) ReRead(ins);
    system("cls");
    if(ins == "1")
    {
        printf("��Ҫ�����Ʊ�������ǣ�\n\n");
        printf("1.�ɻ�Ʊ\n\n2.����Ʊ\n\n3.����/�ɻ�Ʊ\n\n����ѡ���ǣ�");
        string inst;
        cin >> inst;
        while(Check_Choose(1, 3, inst) == 0)    ReRead(inst);
        system("cls");
        string fcity, tcity;
        printf("������������㣺");
        cin >> fcity;
        printf("�����������յ㣺");
        cin >> tcity;

        printf("\n����Ϊ����ѯ...\n\n");
        Sleep(1000);

        int Count1 = Plane :: Get_Count(), Count2 = Train :: Get_Count(), Cnt = 0;
        if(inst == "1" || inst == "3")  
            for(int i = 1; i <= Count1; i++)    
                if(Pla[i].Get_Fcity() == fcity && Pla[i].Get_Tcity() == tcity)
                {
                    Cnt++;
                    printf("�Ѳ�ѯ����%2d��������Ϣ:\n", Cnt);
                    Pla[i].Show_information();
                }
        if(inst == "2" || inst == "3")  
            for(int i = 1; i <= Count2; i++)    
                if(Tra[i].Get_Fcity() == fcity && Tra[i].Get_Tcity() == tcity)
                {
                    Cnt++;
                    printf("�Ѳ�ѯ����%2d��������Ϣ:\n", Cnt);
                    Tra[i].Show_information();
                }
        if(Cnt == 0)
        {
            printf("δ��ѯ�������Ϣ...\n����������һ��\n");
            Sleep(1500);    return 1;
        }
        string inst2;
        printf("\n��ѯ��ϣ���Ʊ������Y��������һ������N\n���������ǣ�");
        cin >> inst2;
        if(inst2 == "N")    return 1;
        
        string idnum2;
        printf("�������������֤�ţ�");
        cin >> idnum2;
        int k3 = People :: Find_People(idnum2);
        if(k3 != -1)
        {
            printf("�Ѳ�ѯ��������Ϣ��");
            Peo[k3].Show_Allinformation();
        }
        else 
        {
            printf("δ��ѯ��������Ϣ,���ڽ������¼�룡\n");
            People :: Input();    
        }
        printf("��Ҫ�����Ʊ�ĺ���Ż򳵴κ��ǣ�");
        string idnum;
        Sleep(1000);
        int k1, k2;
        cin >> idnum;
        if(k3 == -1) k3 = People :: Find_People(Peo[People :: Get_Count()].Get_idnum());
        while(1)
        {
            k1 = Plane :: Find_plane(idnum);
            k2 = Train :: Find_Train(idnum);
            if(k1 != -1 && Pla[k1].Get_Fcity() == fcity && Pla[k1].Get_Tcity() == tcity)
            {
                printf("��Ҫ�����Ʊ�����Ϣ���£�\n");
                Pla[k1].Show_information();
                printf("\n���蹺������Y,��������N\n");
                if(Pla[k1].Get_rest_ticket() == 0)  printf("(�ú������޿���)\n");
                printf("����ѡ���ǣ�");
                string Answer;
                cin >> Answer;
                while(Answer != "Y" && Answer != "N"){printf("���������Ϣ�������������룺"); cin >> Answer;}
                if(Answer == "N")   return 1;
                if(Answer == "Y")
                {
                    int rest = Pla[k1].Get_rest_ticket();
                    if(rest != 0)
                    {
                        Pla[k1].Modify_rest_ticket(rest - 1);
                        Peo[k3].Modify_Ticket(-k1);
                        Pla[k1].Insert(Peo[k3]);
                        printf("\n��Ʊ�ɹ���\n");
                    }
                    else
                    {
                        printf("�ú������޿�����\n�������ȼ��ǣ�\n");
                        string _;
                        cin >> _;
                        while(Check_Num(_) == 0)    ReRead(_);
                        Wait[k1].Push(Make_pair(ToInt(_), Peo[k3]));
                        printf("����ɹ�!\n");
                    }
                    return 1;
                }
            }
            else if(k2 != -1 && Tra[k2].Get_Fcity() == fcity && Tra[k2].Get_Tcity() == tcity)
            {
                printf("��Ҫ�����Ʊ�����Ϣ���£�\n");
                Tra[k2].Show_information();
                printf("\n���蹺������Y,��������N\n");
                if(Tra[k2].Get_rest_ticket() == 0)  printf("(�ø������޿���)\n");
                printf("����ѡ���ǣ�");
                string Answer;
                cin >> Answer;
                while(Answer != "Y" && Answer != "N"){printf("���������Ϣ�������������룺"); cin >> Answer;}
                if(Answer == "N")   return 1;
                if(Answer == "Y")
                {
                    int rest = Tra[k2].Get_rest_ticket();
                    if(rest != 0)
                    {
                        Tra[k2].Modify_rest_ticket(rest - 1);
                        Peo[k3].Modify_Ticket(k2);
                        Tra[k2].Insert(Peo[k3]);
                        printf("\n��Ʊ�ɹ���\n");
                    }
                    else
                    {
                        printf("�ø������޿�����\n�������ȼ��ǣ�\n");
                        string _;
                        cin >> _;
                        while(Check_Num(_) == 0)    ReRead(_);
                        Wait2[k2].Push(Make_pair(ToInt(_), Peo[k3]));
                        printf("����ɹ�!\n");
                    }
                    return 1;
                }
            }
            else 
            {
                printf("δ��ѯ���ú���!\n��ȷ����������Ϸ�!\n��Ҫ�����Ʊ�ĺ���Ż򳵴κ���(����###������һ��)��\n");
                cin >> idnum;
                if(idnum == "###")  return 1;
            }
        }
        printf("���ܽ�����\n");
        Sleep(1000);
    }
    else if(ins == "2")
    {
        string idnum2;
        printf("�������������֤�ţ�");
        cin >> idnum2;
        int k3 = People :: Find_People(idnum2);
        if(k3 == -1)
        {
            printf("δ��ѯ�����Ĺ�Ʊ��Ϣ��");
            Sleep(1000);
            return true;
        }
        printf("\n\n\n������Ϣ���£�\n");
        Peo[k3].Show_Allinformation();
        printf("\n\n");
        printf("��ѯ��......\n");
        Sleep(1000);

        ass[0] = 0;
        Peo[k3].Exit_ticket();

        for(int i = 1; i <= ass[0]; i++)
        {
            if(ass[i] < 0)  Pla[abs(ass[i])].Show_information();
            else    Tra[ass[i]].Show_information();

            printf("\n���Ƿ�Ҫ��Ʊ��\n������Ʊ����Y���������N\n����ѡ���ǣ�");
            string ins;
            cin >> ins;
            while(ins != "Y" && ins != "N") {printf("���������������������룺"); cin >> ins;}
            if(ins == "N")  continue;
            if(ass[i] < 0)
            {
                int rst = Pla[abs(ass[i])].Get_rest_ticket();
                Pla[abs(ass[i])].Modify_rest_ticket(rst + 1);
                Pla[abs(ass[i])].Exit_Ticket(Peo[k3].Get_idnum());
                Peo[k3].Exit_one_ticket(ass[i]);
            }
            else
            {
                int rst = Tra[ass[i]].Get_rest_ticket();
                Tra[ass[i]].Modify_rest_ticket(rst + 1);
                Tra[ass[i]].Exit_Ticket(Peo[k3].Get_idnum());
                Peo[k3].Exit_one_ticket(ass[i]);
            }
            printf("\n\n��Ʊ�ɹ���\n\n");
            Sleep(1000);
        }
        
    }
    else if(ins == "3")
    {
        string Inst;
        printf("�����б�\n��1.������ѯ\n\n��2.���յ��ѯ\n\n����ѡ���ǣ�");
        cin >> Inst;
        while(Check_Choose(1, 2, Inst) == 0) ReRead(Inst);
        if(Inst == "1")
        {
            printf("��Ҫ���Ʊ����ʼ���ǣ�");
            string inst;
            cin >> inst;
            printf("\n���ڲ�ѯ...\n");
            Sleep(1000);
            int Count1 = Plane :: Get_Count(), Count2 = Train :: Get_Count();
            for(int i = 1; i <= Count1; i++)
                if(Pla[i].Get_Fcity() == inst)
                {
                    Pla[i].Show_information();
                    Sleep(400);
                }
            for(int i = 1; i <= Count2; i++)
                if(Tra[i].Get_Fcity() == inst)
                {
                    Tra[i].Show_information();
                    Sleep(400);
                }
            getchar();
        }
        else if(Inst == "2")
        {
            printf("��Ҫ���Ʊ���յ��ǣ�");
            string inst;
            cin >> inst;
            printf("\n���ڲ�ѯ...\n");
            Sleep(1000);
            int Count1 = Plane :: Get_Count(), Count2 = Train :: Get_Count();
            for(int i = 1; i <= Count1; i++)
                if(Pla[i].Get_Tcity() == inst)
                {
                    Pla[i].Show_information();
                    Sleep(400);
                }
            for(int i = 1; i <= Count2; i++)
                if(Tra[i].Get_Tcity() == inst)
                {
                    Tra[i].Show_information();
                    Sleep(400);
                }
            Sleep(1500);
        }
        getchar();
    }

}
