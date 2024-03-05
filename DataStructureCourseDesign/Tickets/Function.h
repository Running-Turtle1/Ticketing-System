#pragma once
#include "string.h"
#include "cstdlib"
#include "Priority_queue2.h"
#include "Pair.h"
#include "Check.h"
#include "Plane.h"
#include "Train.h"
using namespace std;
typedef Pair <int, int> pii;
struct assist{int to, nxt, w, sre, k;};
Priority_queue2 q;
class Function
{
    public:
        static void UI_Function();
        static void Init();
        static void Add_edge(int u, int v, int w, int flag, int k);
        static void Dijstra(int s, int t, bool use1, bool use2, int fuc);
        static void Output_Path(int t);
        static void Top_sort(int s, int t, bool use1, bool use2);
        static int Meeting(int s, bool use1, bool use2);
        assist e[Maxn * Maxn];
        int head[Maxn];
        int src[Maxn], path[Maxn];
        int dis[Maxn], w[Maxn], K[Maxn];
        bool vis[Maxn];
}A;
void Function :: Top_sort(int s, int t, bool use1, bool use2)
{
    Init();
    int Count1 = Plane :: Get_Count(), Count2 = Train :: Get_Count();
    if(use1)
        for(int i = 1; i <= Count1; i++)
            if(Pla[i].Get_zt() == 1)
            {
                int u = ToInt(Pla[i].Get_Fcity()), v = ToInt(Pla[i].Get_Tcity()), w = 0, k = Plane :: Find_plane(Pla[i].Get_idnum());
                A.Add_edge(u, v, 1, 1, k);
            }
    if(use2)
        for(int i = 1; i <= Count2; i++)
            if(Tra[i].Get_zt() == 1)
            {
                int u = ToInt(Tra[i].Get_Fcity()), v = ToInt(Tra[i].Get_Tcity()), w = 0, k = Train :: Find_Train(Tra[i].Get_idnum());
                A.Add_edge(u, v, 1, 2, k);
            }
    A.dis[s] = 0;
    q.Push(Make_pair(A.dis[s], s));
    while(!q.Empty())
    {
        int x = q.Top().second;
        q.Pop();
        if(A.vis[x])  continue;
        A.vis[x] = 1;
        for(int i = A.head[x]; i; i = A.e[i].nxt)
            if(A.dis[x] + A.e[i].w < A.dis[A.e[i].to])
            {
                A.dis[A.e[i].to] = A.dis[x] + A.e[i].w;
                A.path[A.e[i].to] = x; A.src[A.e[i].to] = A.e[i].sre; A.K[A.e[i].to] = A.e[i].k;
                q.Push(Make_pair(A.dis[A.e[i].to], A.e[i].to));
            }
    }
    Function :: Output_Path(t);
    getchar(); getchar();
    Sleep(1000);
}
int Function :: Meeting(int s, bool use1, bool use2)
{
    Init();
    int Count1 = Plane :: Get_Count(), Count2 = Train :: Get_Count();
    if(use1)
        for(int i = 1; i <= Count1; i++)
            if(Pla[i].Get_zt() == 1)
            {
                int u = ToInt(Pla[i].Get_Fcity()), v = ToInt(Pla[i].Get_Tcity()), w = 0, k = Plane :: Find_plane(Pla[i].Get_idnum());
                A.Add_edge(v, u, Tra[i].Get_ticket_cost(), 1, k);
            }
    if(use2)
        for(int i = 1; i <= Count2; i++)
            if(Tra[i].Get_zt() == 1)
            {
                int u = ToInt(Tra[i].Get_Fcity()), v = ToInt(Tra[i].Get_Tcity()), w = 0, k = Train :: Find_Train(Tra[i].Get_idnum());
                A.Add_edge(v, u, w, 2, k);
            }
    A.dis[s] = 0;
    q.Push(Make_pair(A.dis[s], s));
    while(!q.Empty())
    {
        int x = q.Top().second;
        q.Pop();
        if(A.vis[x])  continue;
        A.vis[x] = 1;
        for(int i = A.head[x]; i; i = A.e[i].nxt)
            if(A.dis[x] + A.e[i].w < A.dis[A.e[i].to])
            {
                A.dis[A.e[i].to] = A.dis[x] + A.e[i].w;
                A.path[A.e[i].to] = x; A.src[A.e[i].to] = A.e[i].sre; A.K[A.e[i].to] = A.e[i].k;
                q.Push(Make_pair(A.dis[A.e[i].to], A.e[i].to));
            }
    }
    int Ans = 0;
    for(int i = 1; ; i++)
        if(A.dis[i] > 1e5)    break;
        else Ans += A.w[i] * A.dis[i];
    return Ans;
}
void Function :: UI_Function()
{
    system("cls");
    printf("本次操作所能进行的功能有：\n\n※1.以最低价格去往某城市\n\n※2.以最短时间去往某城市\n\n※3.以最少换乘去往某城市\n\n※4.会议选址\n\n");
    printf("（会议选址）是在稠密的地图中选择一个地点，使得所有人到这个地点的花费的花费最低！\n\n\n");
    printf("您的选择是：");
    string ins;
    cin >> ins;
    while(Check_Choose(1, 4, ins) == 0) ReRead(ins);
    
    bool use1 = 0, use2 = 0;
    string inst;

    printf("您是否愿意乘航班，如愿意输入Y，否则输出N:");
    cin >> inst;
    while(inst != "Y" && inst != "N"){printf("输入错误，请重新输入："); cin >> inst;}
    if(inst == "Y") use1 = true;

    printf("您是否愿意乘高铁，如愿意输入Y，否则输出N:");
    cin >> inst;
    while(inst != "Y" && inst != "N"){printf("输入错误，请重新输入："); cin >> inst;}
    if(inst == "Y") use2 = true;
    if(use1 == 0 && use2 == 0)
    {
        printf("暂时不能提供该服务！\n");
        Sleep(1000);
        return;
    }
    if(ins == "1" || ins == "2" || ins == "3")
    {
        string s, t;
        printf("请输入您的起点：");
        cin >> s;
        while(Check_Num(s) == 0)    ReRead(s);
        printf("请输入您的终点：");
        cin >> t;
        while(Check_Num(t) == 0)    ReRead(t);
        int Func = ToInt(ins);
        if(ins == "1" || ins == "2")    Function :: Dijstra(ToInt(s), ToInt(t), use1, use2, Func);
        else if(ins == "3") Top_sort(ToInt(s), ToInt(t), use1, use2);
    }
    if(ins == "4")
    {
        printf("会议的人数是：");
        int n_ = read();
        for(int i = 0; i < Maxn; i++)    A.w[i]++;
        for(int i = 1; i <= n_; i++)
        {
            printf("第%2d 个人所在城市编号是： ", i);
            int x = read();
            A.w[x]++;
        }
        int Ans = 0, Min = 2e9;
        for(int i = 1; i <= Maxn; i++)
        {
            int tot = Meeting(i, use1, use2);
            if(tot < Min)
            {
                Min = tot;
                Ans = i;
            }
        }
        printf("会议的最佳地点是：%d", Ans);
        getchar();
        Sleep(1000);
    }
}
void Function :: Init()
{
    for(int i = 0; i <= A.head[0]; i++)   A.e[i].nxt = A.e[i].to = A.e[i].w = 0;
    for(int i = 0; i < Maxn; i++)   A.head[i] = A.vis[i] = A.src[i] = A.path[i] = 0, A.dis[i] = 2e9;
}
void Function :: Add_edge(int u, int v, int w, int flag, int k)
{
    A.e[++A.head[0]].to = v;
    A.e[A.head[0]].w = w;
    A.e[A.head[0]].sre = flag;
    A.e[A.head[0]].k = k;
    A.e[A.head[0]].nxt = A.head[u];
    A.head[u] = A.head[0];  
}
void Function :: Dijstra(int s, int t, bool use1, bool use2, int fuc)
{
    A.Init();
    int Count1 = Plane :: Get_Count(), Count2 = Train :: Get_Count();
    if(use1)
        for(int i = 1; i <= Count1; i++)
            if(Pla[i].Get_zt() == 1)
            {
                int u = ToInt(Pla[i].Get_Fcity()), v = ToInt(Pla[i].Get_Tcity()), w = 0, k = Plane :: Find_plane(Pla[i].Get_idnum());
                if(fuc == 1)    w = Pla[i].Get_ticket_cost();
                else            w = Pla[i].Get_time_cost();
                A.Add_edge(u, v, w, 1, k);
            }
    if(use2)
        for(int i = 1; i <= Count2; i++)
            if(Tra[i].Get_zt() == 1)
            {
                int u = ToInt(Tra[i].Get_Fcity()), v = ToInt(Tra[i].Get_Tcity()), w = 0, k = Train :: Find_Train(Tra[i].Get_idnum());
                if(fuc == 1)    w = Tra[i].Get_ticket_cost();
                else            w = Tra[i].Get_time_cost();
                A.Add_edge(u, v, w, 2, k);
            }
    A.dis[s] = 0;
    q.Push(Make_pair(A.dis[s], s));
    while(!q.Empty())
    {
        int x = q.Top().second;
        q.Pop();
        if(A.vis[x])  continue;
        A.vis[x] = 1;
        for(int i = A.head[x]; i; i = A.e[i].nxt)
            if(A.dis[x] + A.e[i].w < A.dis[A.e[i].to])
            {
                A.dis[A.e[i].to] = A.dis[x] + A.e[i].w;
                A.path[A.e[i].to] = x; A.src[A.e[i].to] = A.e[i].sre; A.K[A.e[i].to] = A.e[i].k;
                q.Push(Make_pair(A.dis[A.e[i].to], A.e[i].to));
            }
    }
    Function :: Output_Path(t);
    getchar(); getchar();
    Sleep(1000);
}
void Function :: Output_Path(int t)
{
    if(A.path[t] == 0)  return;
    if(A.path[t] != 0)  Output_Path(A.path[t]);
    printf("从 %2d 乘坐", A.path[t]);
    if(A.src[t] == 1)   printf(" 航班 %s ", Pla[A.K[t]].Get_idnum().c_str());
    else printf(" 高铁 %s ", Tra[A.K[t]].Get_idnum().c_str());
    printf("前往 %d,", t);
    if(A.src[t] == 1)   printf("花费 %3d RMB， 消耗 %3d 分钟\n", Pla[A.K[t]].Get_ticket_cost(), Pla[A.K[t]].Get_time_cost());
    else printf("花费 %3d RMB， 消耗 %3d 分钟\n", Tra[A.K[t]].Get_ticket_cost(), Tra[A.K[t]].Get_time_cost());
}