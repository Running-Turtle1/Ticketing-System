#pragma once
#include "Basic.h"
#include "Pair.h"
class Priority_queue2
{
    public:
        void Push(Pair<int, int> p);
        void Pop();
        void Clear();
        bool Empty();
        int Size();
        Pair<int, int> Top();
        void Show_Information();
    private:
        int Cnt;
        Pair<int, int> Heap[Maxn];
};

void Priority_queue2 :: Push(Pair<int, int> p)
{
    Heap[++Cnt] = p;
    int x = Cnt;
    while(x / 2 >= 1)
    {
        int y = x / 2;
        if(Heap[y].first > Heap[x].first)
        {
            Pair<int, int> t = Heap[y];
            Heap[y] = Heap[x];
            Heap[x] = t;
            x = y;
        }
        else    break;
    }
}
void Priority_queue2 :: Pop()
{
    Heap[1] = Heap[Cnt--];
    int x = 1;
    while(x * 2 <= Cnt)
    {
        int y = x * 2;
        if(Heap[y+1].first < Heap[y].first && y + 1 <= Cnt) y++;
        if(Heap[y].first < Heap[x].first)
        {
            Pair<int, int> t = Heap[y];
            Heap[y] = Heap[x];
            Heap[x] = t;
            x = y;
        }
        else    break;
    }
}
Pair<int, int> Priority_queue2 :: Top()
{
    return Heap[1];
}
int Priority_queue2 :: Size()
{
    return Cnt;
}
bool Priority_queue2 :: Empty()
{
    return Cnt == 0 ? true : false;
}
void Priority_queue2 :: Clear()
{
    for(int i = 0; i <= Cnt; i++)   Heap[i].first = Heap[i].second = 0;
    Cnt = 0;
}