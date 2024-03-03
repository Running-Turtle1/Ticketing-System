#pragma once
#include "Basic.h"

template<class T1, class T2>
struct Pair
{
    T1 first;
    T2 second;
    Pair(){}
    Pair(T1 t1, T2 t2);
    Pair(const Pair<T1, T2> &P);
    Make_pair(T1 t1, T2 t2);
};
template<class T1, class T2>
Pair <T1, T2> :: Pair(T1 t1, T2 t2) : first(t1), second(t2){}
template<class T1, class T2>
Pair <T1, T2> :: Pair(const Pair<T1, T2> &P) : first(P.first), second(P.second){}
template<class T1, class T2>
bool operator < (const Pair<T1, T2> &P1, const Pair<T1, T2> &P2)
{
    if(P1.first == P2.first)    return P1.second < P2.second;
    return P1.first < P2.first;
};
template<class T1, class T2>
bool operator == (const Pair<T1, T2> &P1, const Pair<T1, T2> &P2)
{
    if(P1.first == P2.first && P1.second == P2.second)    return true;
    return false;
};

template<class T1, class T2>
inline Pair<T1, T2> Make_pair(const T1 &t1, const T2 &t2){return Pair<T1, T2>(t1, t2);}