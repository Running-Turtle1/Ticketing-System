#pragma once
#include "Basic.h"
#include "Pair.h"
#include "People.h"
class Priority_queue
{
    public:
        void Push(Pair<int, People> p);
        void Pop();
        void Clear();
        bool Empty();
        int Size();
        Pair<int, People> Top();
        void Show_Information();
        void Show_Information(int k);
    private:
        int Cnt;
        Pair<int, People> Heap[Maxn];
}Wait[1000], Wait2[1000];

void Priority_queue :: Push(Pair<int, People> p)
{
    Heap[++Cnt] = p;
    int x = Cnt;
    while(x / 2 >= 1)
    {
        int y = x / 2;
        if(Heap[y].first > Heap[x].first)
        {
            Pair<int, People> t = Heap[y];
            Heap[y] = Heap[x];
            Heap[x] = t;
            x = y;
        }
        else    break;
    }
}
void Priority_queue :: Pop()
{
    Heap[1] = Heap[Cnt--];
    int x = 1;
    while(x * 2 <= Cnt)
    {
        int y = x * 2;
        if(Heap[y+1].first < Heap[y].first && y + 1 <= Cnt) y++;
        if(Heap[y].first < Heap[x].first)
        {
            Pair<int, People> t = Heap[y];
            Heap[y] = Heap[x];
            Heap[x] = t;
            x = y;
        }
        else    break;
    }
}
Pair<int, People> Priority_queue :: Top()
{
    return Heap[1];
}
int Priority_queue :: Size()
{
    return Cnt;
}
bool Priority_queue :: Empty()
{
    return Cnt == 0 ? true : false;
}
void Priority_queue :: Clear()
{
    for(int i = 0; i <= Cnt; i++)
    {
        Heap[i].first = 0;
        // Heap[i].second.Age = 0;
        // Heap[i].second.Idnum = "\0";
        // Heap[i].second.Name = "\0";
        // Heap[i].second.Sex = "\0";
    }
    Cnt = 0;
}
void Priority_queue :: Show_Information()
{
    for(int i = 1; i <= Cnt; i++)
    {
        People x = Heap[i].second;
        printf("第%2d名超额人的信息如下:\n", i);
        x.Show_Allinformation(i);
    }
}
void Priority_queue :: Show_Information(int k)
{
    for(int i = 1; i <= min(Cnt, k); i++)
    {
        People x = Heap[i].second;
        printf("第%2d名得票人的信息如下:\n", i);
        x.Show_Allinformation(i);
    }
}