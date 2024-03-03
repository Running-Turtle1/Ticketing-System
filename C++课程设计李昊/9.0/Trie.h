#pragma once
#include "Basic.h"
#include "string.h"
class Trie
{
    public:
        Trie(){}
        void Clear();
        void Insert(char s[], int frm);
        void Insert(string s, int frm);
        int Find(char s[]);
        int Find(string s);
    private:
        static int Num;
        int Trie_tree[Maxn][Maxm];
        int Ans[Maxn];
};
int Trie :: Num = 0;
void Trie :: Clear()
{
    for(int i = 0; i< Maxn; i++)    for(int j = 0; j < Maxm; j++)   Trie_tree[i][j] = 0;
    for(int i = 0; i < Maxn; i++)   Ans[i] = 0;
}
void Trie :: Insert(char s[], int frm)
{
    int len = strlen(s), k = 0;
    for(int i = 0; i < len; i++)
    {
        int c = s[i] - '0';
        if(!Trie_tree[k][c]) Trie_tree[k][c] = ++Num;
        k = Trie_tree[k][c];
    }
    Ans[k] = frm;
}
void Trie :: Insert(string s, int frm)
{
    int len = s.size(), k = 0;
    for(int i = 0; i < len; i++)
    {
        int c = s[i] - '0';
        if(!Trie_tree[k][c]) Trie_tree[k][c] = ++Num;
        k = Trie_tree[k][c];
    }
    Ans[k] = frm;
}
int Trie :: Find(char s[])
{
    int len = strlen(s), k = 0;
    for(int i = 0; i < len; i++)
    {
        int c = s[i] - '0';
        if(!Trie_tree[k][c]) return Not_Find;
        k = Trie_tree[k][c];
    }
    return Ans[k] == 0 ? Not_Find : Ans[k];
}
int Trie :: Find(string s)
{
    int len = s.size(), k = 0;
    for(int i = 0; i < len; i++)
    {
        int c = s[i] - '0';
        if(!Trie_tree[k][c]) return Not_Find;
        k = Trie_tree[k][c];
    }
    return Ans[k] == 0 ? Not_Find : Ans[k];
}