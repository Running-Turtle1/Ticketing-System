#include "iostream"
#include "algorithm"
#include "cstdio"
#include "ctime"
#include "cstdlib"
#include <iomanip>
#include <cassert>
#include <fstream>
#include <set>
#include <string>
using namespace std;
set <string> S;
int f[100100];
int read()
{
    int rt = 0, in = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-') in = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') {rt = rt * 10 + ch - '0'; ch = getchar();}
    return rt * in;
}

int main()
{
    ofstream data1("data_train.txt");
    printf("生成城市数量：");
    int n = read();
    for(int i = 1; i <= n; i++) f[i] = i;
    random_shuffle(f+1, f+1+n);

    printf("生成航班数量(至少2n)：");
    int m = read();
    m = max(2 * n, m);
    data1 << m << endl;
    m -= 2 * n;
    for(int i = 1; i <= n; i++)
    {
        if (i != n) data1 << f[i] << " " << f[i + 1] << " ";
        else data1 << f[i] << " " << f[0] << " ";

        while(1)
        {
            string s;
            s.clear();
            for(int j = 1; j <= 2; j++) s += rand() * rand() % 26 + 'A';
            for(int j = 1; j <= 4; j++) s += rand() * rand() % 10 + '0';
            if(S.count(s) == 0)
            {
                data1 << s << " ";
                S.insert(s);
                break;
            }
        }
        
        int a = rand() * rand() % 900 + 1;
        int b = rand() * rand() % 900 + 1;
        int c = 100 + rand() % 900;
        if(a < b)   swap(a, b);
        data1 << a << " " << b << " " << c << endl;   
    }
    for(int i = n; i >= 1; i--)
    {
        if (i != 1) data1 << f[i] << " " << f[i - 1] << " ";
        else data1 << f[i] << " " << f[n] << " ";

        while(1)
        {
            string s;
            s.clear();
            for(int j = 1; j <= 2; j++) s += rand() * rand() % 26 + 'A';
            for(int j = 1; j <= 4; j++) s += rand() * rand() % 10 + '0';
            if(S.count(s) == 0)
            {
                data1 << s << " ";
                S.insert(s);
                break;
            }
        }
        
        int a = rand() * rand() % 900 + 1;
        int b = rand() * rand() % 900 + 1;
        int c = 100 + rand() % 900;
        if(a < b)   swap(a, b);
        data1 << a << " " << b << " " << c << endl;   
    }
    for(int i = 1; i <= m; i++)
    {
        int x = f[rand() * rand() % n + 1];
        int y = f[rand() * rand() % n + 1];
        while (x == y) y = f[rand() * rand() % n + 1];
        data1 << x << " " << y << " ";

        while(1)
        {
            string s;
            s.clear();
            for(int j = 1; j <= 2; j++) s += rand() * rand() % 26 + 'A';
            for(int j = 1; j <= 4; j++) s += rand() * rand() % 10 + '0';
            if(S.count(s) == 0)
            {
                data1 << s << " ";
                S.insert(s);
                break;
            }
        }
        
        int a = rand() * rand() % 900 + 1;
        int b = rand() * rand() % 900 + 1;
        int c = 100 + rand() % 900;
        if(a < b)   swap(a, b);
        data1 << a << " " << b << " " << c << endl;   
    }
    data1.close();
    return 0;
}
