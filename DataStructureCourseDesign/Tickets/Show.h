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
    printf("请输入帐号：");
    cin >> Account;
    // cout << Account << endl;
    printf("请输入密码：");
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
        printf("帐号密码错误！\n");
        getchar();
        return;
    }
    cout << "登陆成功！\n" << endl;
    getchar();
    while(login)   
    {
        system("cls");
        cout << "您要修改哪种交通工具的相关信息?\n1.航班信息\n2.高铁信息\n3.返回主界面\n您的选择是：";
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
    printf("管理员部分支持的功能如下：\n※1.修改票价\n\n※2.实行放票\n\n※3.增添航班\n\n※4.暂停/启用航班\n\n※5.浏览航班及其乘客信息\n\n※6.返回上一层\n\n");
    printf("您的选择是：");
    string ins;
    cin >> ins;
    while(Check_Choose(1, 6, ins) == false)  ReRead(ins);
    int Num = ToInt(ins);
    system("cls");
    if(Num == 1)
    {
        printf("当前功能：修改航班票价！\n\n");
        string Plane_num;
        printf("您要修改的航班的航班号是：");
        cin >> Plane_num;
        int k = Plane :: Find_plane(Plane_num);
        if(k == -1)
        {
            printf("未查询到该航班！\n修改失败\n按任意键返回！\n");
            getchar(); getchar();
        }
        else
        {
            printf("该航班的信息如下：\n");
            Pla[k].Show_information();
            string Cost1;
            printf("您要修改为：");
            cin >> Cost1;
            while(Check_Num(Cost1) == 0)    ReRead(Cost1);
            Pla[k].Modify_ticket_price(ToInt(Cost1));
            printf("\n修改成功\n");
        }
        return 1;
    }
    else if(Num == 2)
    {
        printf("当前功能：放票管理！\n\n");
        string Plane_num;
        printf("您要进行放票的航班的航班号是：");
        cin >> Plane_num;
        int k = Plane :: Find_plane(Plane_num);
        if(k == -1)
        {
            printf("未查询到该航班！\n修改失败\n按任意键返回！\n");
            getchar();getchar();
        }
        else
        {
            printf("该航班的信息如下：\n");
            Pla[k].Show_information();
            int waitnum = Wait[k].Size();
            if(waitnum == 0)
            {
                printf("该航班无需放票！\n");
                getchar(); getchar();
                return true;
            }
            printf("该航班超额人数为：%d\n", waitnum);
            printf("超额人员信息如下：\n");
            Pla[k].Show_information();
            printf("您要增补的票数为：");
            string tnum;
            cin >> tnum;
            while(Check_Num(tnum) == 0) ReRead(tnum);
            int Curticket = Pla[k].Get_full_ticket(), Currstticket = Pla[k].Get_rest_ticket();
            Pla[k].Modify_full_ticket(Curticket + ToInt(tnum));
            Pla[k].Modify_rest_ticket(max(ToInt(tnum) - waitnum, 0));
            for(int i = 1; i <= min(waitnum, ToInt(tnum)); i++)
            {
                printf("第%2d名得票用户信息如下：\n", i);
                People temp = Wait[k].Top().second;
                Pla[k].Insert(Wait[k].Top().second);
                int k3 = People :: Find_People(Wait[k].Top().second.Get_idnum());
                Peo[k3].Modify_Ticket(-k);
                temp.Show_Allinformation();
                Wait[k].Pop();
            }
            printf("\n放票成功！\n");
            getchar();
        }
        return true;
    }
    else if(Num == 3)
    {
        printf("当前功能：增加航班！\n\n");
        string fcity, tcity, pnum;
        printf("请输入该航班的起点:");
        cin >> fcity;
        printf("请输入该航班的终点:");
        cin >> tcity;
        printf("请输入该航班的航班号:");
        cin >> pnum;
        while(Check_Planenum(pnum) == 0 || Plane :: Find_plane(pnum) != -1) ReRead(pnum);
        string costmoney, fullticket, distance;
        printf("请输入该航班机票的价格：");
        cin >> costmoney;
        while(Check_Num(costmoney) == 0)    ReRead(costmoney);
        printf("请输入该航班的预计耗时：");
        cin >> distance;
        while(Check_Num(distance) == 0)     ReRead(distance);
        printf("请输入该航班机票的总票数：");
        cin >> fullticket;
        while(Check_Num(fullticket) == 0)   ReRead(fullticket);
        int Pos = Plane :: Get_Count();
        Pla[++Pos] = Plane(fcity, tcity, pnum, ToInt(fullticket), ToInt(fullticket), ToInt(costmoney), ToInt(distance));
        system("cls");
        printf("添加成功！\n该航班信息如下：");
        Pla[Pos].Show_information();
        getchar();getchar();
    }
    else if(Num == 4)
    {
        printf("当前功能：暂停/启用航班！\n\n");
        string Plane_num;
        printf("您要暂停的航班的航班号是：");
        cin >> Plane_num;
        int k = Plane :: Find_plane(Plane_num);
        if(k == -1)
        {
            printf("未查询到该航班！\n操作失败\n按任意键返回！\n");
            getchar(); getchar();
        }
        else
        {
            printf("该航班信息如下：");
            Pla[k].Show_information();
            int Flag = Pla[k].Get_zt();
            if(Flag == 0)
            {
                printf("您是否确定启用该航班？\n输出Y表示确定，输入N表示否定\n");
                string inst1;
                cin >> inst1;
                while(inst1 != "Y" && inst1 != "N") {printf("输入错误！请重新输入！\n"); cin >> inst1;}
                if(inst1 == "Y")    Pla[k].Modify_zt();
            }
            else
            {
                printf("您是否确定暂停该航班？\n输出Y表示确定，输入N表示否定\n");
                string inst1;
                cin >> inst1;
                while(inst1 != "Y" && inst1 != "N") {printf("输入错误！请重新输入！\n"); cin >> inst1;}
                if(inst1 == "Y")    Pla[k].Modify_zt();
            }
            getchar(); getchar();
            return true;
        }
    }
    else if(Num == 5)
    {
        printf("当前功能：浏览航班及其乘客信息！\n\n");
        printf("\n该功能细分为：\n1.查询指定航班号的航班信息\n2.依次查询所有航班\n3.根据起终点查询航班信息：\n\n");
        string instr;
        cin >> instr;
        while(Check_Choose(1, 3, instr) == 0)   ReRead(instr);
        system("cls");
        if(instr == "1")
        {
            printf("请输入您要查询的航班的航班号：");
            string idnum;
            cin >> idnum;
            while(Check_Planenum(idnum) == 0)   ReRead(idnum);
            int k = Plane :: Find_plane(idnum);
            if(k == -1) printf("未查到该航班！\n");
            else    Pla[k].Show_information();
        }
        else if(instr == "2")
        {
            int Cnt = Plane :: Get_Count();
            for(int i = 1; i <= Cnt; i++)
            {
                Pla[i].Show_information();
                printf("是否查看该航班的购票人员信息？\n如需查看请输入Y，否则输出N，输入E返回主菜单\n您的选择是：");
                string inst1;
                cin >> inst1;
                while(inst1 != "Y" && inst1 != "N" && inst1 != "E") {printf("输入有误！请重新输入："); cin >> inst1;}
                if(inst1 == "Y")    Pla[i].Output_people();
                if(inst1 == "E")    return true;
                printf("\n\n\n");
            }
            printf("\n\n查询完成，2秒后返回");
            Sleep(2000);
        }
        else if(instr == "3")
        {
            bool flag = 0;
            string S, T;
            printf("您要查询的航班的起点是：");
            cin >> S;
            printf("您要查询的航班的终点是：");
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
            if(!flag)   printf("未查询到相关航班\n");
        }
        Sleep(2000);
    }
    else if(Num == 6)    return 0;
    return 1;
}
bool UI :: Management_UI_Train()
{
    system("cls");
    printf("管理员部分支持的功能如下：\n※1.修改票价\n\n※2.实行放票\n\n※3.增添高铁\n\n※4.暂停/启用高铁\n\n※5.浏览高铁及其乘客信息\n\n※6.返回上一层\n\n");
    printf("您的选择是：");
    string ins;
    cin >> ins;
    while(Check_Choose(1, 6, ins) == false)  ReRead(ins);
    int Num = ToInt(ins);
    system("cls");
    if(Num == 1)
    {
        printf("当前功能：修改高铁票价！\n\n");
        string Train_num;
        printf("您要修改的高铁的车次号是：");
        cin >> Train_num;
        int k = Train :: Find_Train(Train_num);
        if(k == -1)
        {
            printf("未查询到该高铁！\n修改失败\n按任意键返回！\n");
            getchar(); getchar();
        }
        else
        {
            printf("该高铁的信息如下：\n");
            Tra[k].Show_information();
            string Cost1;
            printf("您要修改为：");
            cin >> Cost1;
            while(Check_Num(Cost1) == 0)    ReRead(Cost1);
            Tra[k].Modify_ticket_price(ToInt(Cost1));
            printf("\n修改成功\n");
        }
        return true;
    }
    else if(Num == 2)
    {
        printf("当前功能：放票管理！\n\n");
        string Train_num;
        printf("您要进行放票的高铁的车次号是：");
        cin >> Train_num;
        int k = Train :: Find_Train(Train_num);
        if(k == -1)
        {
            printf("未查询到该高铁！\n修改失败\n按任意键返回！\n");
            getchar();getchar();
        }
        else
        {
            printf("该高铁的信息如下：\n");
            Tra[k].Show_information();
            int waitnum = Wait2[k].Size();
            if(waitnum == 0)
            {
                printf("该高铁无需放票！\n");
                getchar(); getchar();
                return true;
            }
            printf("该高铁超额人数为：%d\n", waitnum);
            printf("超额人员信息如下：\n");
            Tra[k].Show_information();
            printf("您要增补的票数为：");
            string tnum;
            cin >> tnum;
            while(Check_Num(tnum) == 0) ReRead(tnum);
            int Curticket = Tra[k].Get_full_ticket(), Currstticket = Tra[k].Get_rest_ticket();
            Tra[k].Modify_full_ticket(Curticket + ToInt(tnum));
            Tra[k].Modify_rest_ticket(max(ToInt(tnum) - waitnum, 0));
            for(int i = 1; i <= min(waitnum, ToInt(tnum)); i++)
            {
                printf("第%2d名得票用户信息如下：\n", i);
                People temp = Wait2[k].Top().second;
                Tra[k].Insert(Wait2[k].Top().second);
                int k3 = People :: Find_People(Wait2[k].Top().second.Get_idnum());
                Peo[k3].Modify_Ticket(k);
                temp.Show_Allinformation();
                Wait2[k].Pop();
            }
            printf("\n放票成功！\n");
            getchar();
        }
        return true;
    }
    else if(Num == 3)
    {
        printf("当前功能：增加高铁！\n\n");
        string fcity, tcity, pnum;
        printf("请输入该高铁的起点:");
        cin >> fcity;
        printf("请输入该高铁的终点:");
        cin >> tcity;
        printf("请输入该高铁的车次号:");
        cin >> pnum;
        while(Check_Planenum(pnum) == 0 || Train :: Find_Train(pnum) != -1) ReRead(pnum);
        string costmoney, fullticket, distance;
        printf("请输入该高铁票的价格：");
        cin >> costmoney;
        while(Check_Num(costmoney) == 0)    ReRead(costmoney);
        printf("请输入该航班的预计耗时：");
        cin >> distance;
        while(Check_Num(distance) == 0)     ReRead(distance);
        printf("请输入该高铁票的总票数：");
        cin >> fullticket;
        while(Check_Num(fullticket) == 0)   ReRead(fullticket);
        int Pos = Train :: Get_Count();
        Tra[++Pos] = Train(fcity, tcity, pnum, ToInt(fullticket), ToInt(fullticket), ToInt(costmoney), ToInt(distance));
        system("cls");
        printf("添加成功！\n该高铁信息如下：");
        Tra[Pos].Show_information();
        getchar();getchar();
    }
    else if(Num == 4)
    {
        printf("当前功能：暂停/启用高铁！\n\n");
        string Train_num;
        printf("您要暂停的高铁的车次号是：");
        cin >> Train_num;
        int k = Train :: Find_Train(Train_num);
        if(k == -1)
        {
            printf("未查询到该高铁！\n操作失败\n按任意键返回！\n");
            getchar(); getchar();
        }
        else
        {
            printf("该高铁信息如下：");
            Tra[k].Show_information();
            int Flag = Pla[k].Get_zt();
            if(Flag == 0)
            {
                printf("您是否确定启用该高铁？\n输出Y表示确定，输入N表示否定\n");
                string inst1;
                cin >> inst1;
                while(inst1 != "Y" && inst1 != "N") {printf("输入错误！请重新输入！\n"); cin >> inst1;}
                if(inst1 == "Y")    Tra[k].Modify_zt();
            }
            else
            {
                printf("您是否确定暂停该高铁？\n输出Y表示确定，输入N表示否定\n");
                string inst1;
                cin >> inst1;
                while(inst1 != "Y" && inst1 != "N") {printf("输入错误！请重新输入！\n"); cin >> inst1;}
                if(inst1 == "Y")    Tra[k].Modify_zt();
            }
            getchar(); getchar();
            return true;
        }
    }
    else if(Num == 5)
    {
        printf("当前功能：浏览高铁及其乘客信息！\n\n");
        printf("\n该功能细分为：\n1.查询指定高铁号的航班信息\n2.依次查询所有高铁\n3.根据起终点查询高铁信息：\n\n");
        string instr;
        cin >> instr;
        while(Check_Choose(1, 3, instr) == 0)   ReRead(instr);
        system("cls");
        if(instr == "1")
        {
            printf("请输入您要查询的高铁的高铁号：");
            string idnum;
            cin >> idnum;
            while(Check_Planenum(idnum) == 0)   ReRead(idnum);
            int k = Train :: Find_Train(idnum);
            if(k == -1) printf("未查到该高铁！\n");
            else    Tra[k].Show_information();
        }
        else if(instr == "2")
        {
            int Cnt = Train :: Get_Count();
            for(int i = 1; i <= Cnt; i++)
            {
                Tra[i].Show_information();
                printf("是否查看该高铁的购票人员信息？\n如需查看请输入Y，否则输出N，输入E返回主菜单\n您的选择是：");
                string inst1;
                cin >> inst1;
                while(inst1 != "Y" && inst1 != "N" && inst1 != "E") {printf("输入有误！请重新输入："); cin >> inst1;}
                if(inst1 == "Y")    Tra[i].Output_people();
                if(inst1 == "E")    return true;
                printf("\n\n\n");
            }
            printf("\n\n查询完成，2秒后返回");
            Sleep(2000);
        }
        else if(instr == "3")
        {
            bool flag = 0;
            string S, T;
            printf("您要查询的高铁的起点是：");
            cin >> S;
            printf("您要查询的高铁的终点是：");
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
            if(!flag)   printf("未查询到相关高铁\n");
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
    cout << "航班信息录入成功！\n";

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
    cout << "高铁信息录入成功！\n";
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
    printf("您的选择是：");
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
    printf("用户部分支持的功能如下：\n\n");
    printf("※1.购票\n\n※2.退票\n\n※3.高铁/航班票总览\n\n");
    string ins;
    cin >> ins;
    while(Check_Choose(1, 3, ins) == 0) ReRead(ins);
    system("cls");
    if(ins == "1")
    {
        printf("您要购买的票的类型是：\n\n");
        printf("1.飞机票\n\n2.高铁票\n\n3.高铁/飞机票\n\n您的选择是：");
        string inst;
        cin >> inst;
        while(Check_Choose(1, 3, inst) == 0)    ReRead(inst);
        system("cls");
        string fcity, tcity;
        printf("请输入您的起点：");
        cin >> fcity;
        printf("请输入您的终点：");
        cin >> tcity;

        printf("\n正在为您查询...\n\n");
        Sleep(1000);

        int Count1 = Plane :: Get_Count(), Count2 = Train :: Get_Count(), Cnt = 0;
        if(inst == "1" || inst == "3")  
            for(int i = 1; i <= Count1; i++)    
                if(Pla[i].Get_Fcity() == fcity && Pla[i].Get_Tcity() == tcity)
                {
                    Cnt++;
                    printf("已查询到第%2d条航班信息:\n", Cnt);
                    Pla[i].Show_information();
                }
        if(inst == "2" || inst == "3")  
            for(int i = 1; i <= Count2; i++)    
                if(Tra[i].Get_Fcity() == fcity && Tra[i].Get_Tcity() == tcity)
                {
                    Cnt++;
                    printf("已查询到第%2d条高铁信息:\n", Cnt);
                    Tra[i].Show_information();
                }
        if(Cnt == 0)
        {
            printf("未查询到相关信息...\n即将返回上一层\n");
            Sleep(1500);    return 1;
        }
        string inst2;
        printf("\n查询完毕，购票请输入Y，返回上一层输入N\n您的输入是：");
        cin >> inst2;
        if(inst2 == "N")    return 1;
        
        string idnum2;
        printf("请输入您的身份证号：");
        cin >> idnum2;
        int k3 = People :: Find_People(idnum2);
        if(k3 != -1)
        {
            printf("已查询到您的信息：");
            Peo[k3].Show_Allinformation();
        }
        else 
        {
            printf("未查询到您的信息,现在进行身份录入！\n");
            People :: Input();    
        }
        printf("您要购买的票的航班号或车次号是：");
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
                printf("您要购买的票相关信息如下：\n");
                Pla[k1].Show_information();
                printf("\n如需购买输入Y,否则输入N\n");
                if(Pla[k1].Get_rest_ticket() == 0)  printf("(该航班已无空座)\n");
                printf("您的选择是：");
                string Answer;
                cin >> Answer;
                while(Answer != "Y" && Answer != "N"){printf("您输入的信息有误！请重新输入："); cin >> Answer;}
                if(Answer == "N")   return 1;
                if(Answer == "Y")
                {
                    int rest = Pla[k1].Get_rest_ticket();
                    if(rest != 0)
                    {
                        Pla[k1].Modify_rest_ticket(rest - 1);
                        Peo[k3].Modify_Ticket(-k1);
                        Pla[k1].Insert(Peo[k3]);
                        printf("\n购票成功！\n");
                    }
                    else
                    {
                        printf("该航班已无空座！\n您的优先级是：\n");
                        string _;
                        cin >> _;
                        while(Check_Num(_) == 0)    ReRead(_);
                        Wait[k1].Push(Make_pair(ToInt(_), Peo[k3]));
                        printf("处理成功!\n");
                    }
                    return 1;
                }
            }
            else if(k2 != -1 && Tra[k2].Get_Fcity() == fcity && Tra[k2].Get_Tcity() == tcity)
            {
                printf("您要购买的票相关信息如下：\n");
                Tra[k2].Show_information();
                printf("\n如需购买输入Y,否则输入N\n");
                if(Tra[k2].Get_rest_ticket() == 0)  printf("(该高铁已无空座)\n");
                printf("您的选择是：");
                string Answer;
                cin >> Answer;
                while(Answer != "Y" && Answer != "N"){printf("您输入的信息有误！请重新输入："); cin >> Answer;}
                if(Answer == "N")   return 1;
                if(Answer == "Y")
                {
                    int rest = Tra[k2].Get_rest_ticket();
                    if(rest != 0)
                    {
                        Tra[k2].Modify_rest_ticket(rest - 1);
                        Peo[k3].Modify_Ticket(k2);
                        Tra[k2].Insert(Peo[k3]);
                        printf("\n购票成功！\n");
                    }
                    else
                    {
                        printf("该高铁已无空座！\n您的优先级是：\n");
                        string _;
                        cin >> _;
                        while(Check_Num(_) == 0)    ReRead(_);
                        Wait2[k2].Push(Make_pair(ToInt(_), Peo[k3]));
                        printf("处理成功!\n");
                    }
                    return 1;
                }
            }
            else 
            {
                printf("未查询到该航班!\n请确定您的输入合法!\n您要购买的票的航班号或车次号是(输入###返回上一层)：\n");
                cin >> idnum;
                if(idnum == "###")  return 1;
            }
        }
        printf("功能结束！\n");
        Sleep(1000);
    }
    else if(ins == "2")
    {
        string idnum2;
        printf("请输入您的身份证号：");
        cin >> idnum2;
        int k3 = People :: Find_People(idnum2);
        if(k3 == -1)
        {
            printf("未查询到您的购票信息！");
            Sleep(1000);
            return true;
        }
        printf("\n\n\n您的信息如下：\n");
        Peo[k3].Show_Allinformation();
        printf("\n\n");
        printf("查询中......\n");
        Sleep(1000);

        ass[0] = 0;
        Peo[k3].Exit_ticket();

        for(int i = 1; i <= ass[0]; i++)
        {
            if(ass[i] < 0)  Pla[abs(ass[i])].Show_information();
            else    Tra[ass[i]].Show_information();

            printf("\n您是否要退票？\n如需退票输入Y，否则输出N\n您的选择是：");
            string ins;
            cin >> ins;
            while(ins != "Y" && ins != "N") {printf("您的输入有误，请重新输入："); cin >> ins;}
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
            printf("\n\n退票成功！\n\n");
            Sleep(1000);
        }
        
    }
    else if(ins == "3")
    {
        string Inst;
        printf("功能列表：\n※1.按起点查询\n\n※2.按终点查询\n\n您的选择是：");
        cin >> Inst;
        while(Check_Choose(1, 2, Inst) == 0) ReRead(Inst);
        if(Inst == "1")
        {
            printf("您要查的票的起始地是：");
            string inst;
            cin >> inst;
            printf("\n正在查询...\n");
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
            printf("您要查的票的终点是：");
            string inst;
            cin >> inst;
            printf("\n正在查询...\n");
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
