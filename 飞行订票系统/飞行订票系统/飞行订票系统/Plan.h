#pragma once
#include<bits/stdc++.h>
#include "Flight.h"
using namespace std;

int const MAXN = 110;

struct Edge { // 边的信息
	string num; // 航班
	string to; // 终点
	int min_cost, time; // 到达邻点的最小花费和时间
};

class Plan{
	public :
		vector<Flight> flight; // 存储航班的信息
		vector<Edge> e[MAXN]; // 初始化邻接表存储
		unordered_map<string, int> mp; // 将城市编号， 方便对下标进行操作

		// 构造函数 : 初始化规划所需要的航班信息 + 图的信息 + 映射信息
		Plan();

		// 界面展示
		void ShowMenu();

		// 功能菜单
		void planFuction();

		// 排序功能统一
		void sortFunction();

		// 快速排序 -> 根据花费时间从小到大排序
		void mySort1(vector<Flight>& flight, int l, int r);

		// 快速排序 -> 根据花费时间从大到小排序
		void mySort2(vector<Flight>& flight, int l, int r);

		// 冒泡排序 -> 根据最小花费从小到大排序
		void mySort3(vector<Flight>& flight, int l, int r);

		// 冒泡排序 -> 根据最小花费从大到小排序
		void mySort4(vector<Flight>& flight, int l, int r);

		// 输出排序结果
		void outputSortResult();

		// 堆优化 dijkstra 求 s 到 t 的最短时间
		void heap_dijkstra();
		void heap_dijkstra(string s, string t);

		// spfa 求 s 到 t 的 s 到 t 的最小花费
		void spfa();
		void spfa(string s, string t);

		// Floyd 求任意两个城市之间的最短到达时间
		void floyd();

		// bfs 从某个城市出发到达其他城市的最少航班乘坐次数 
		void bfs();
		void bfs(string& s, string& t);

		// 带回溯的 dfs 求从某个城市出现是否能到达另一个城市 -- 同时输出所有到达方案
		void dfs();
		void dfs(int& dest, int& now, vector<bool>& vis, vector<string>& path, vector<vector<string> >& sum_path);
};