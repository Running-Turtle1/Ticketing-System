#pragma once
#include<bits/stdc++.h>
#include "Flight.h"
using namespace std;

int const MAXN = 110;

struct Edge { // �ߵ���Ϣ
	string num; // ����
	string to; // �յ�
	int min_cost, time; // �����ڵ����С���Ѻ�ʱ��
};

class Plan{
	public :
		vector<Flight> flight; // �洢�������Ϣ
		vector<Edge> e[MAXN]; // ��ʼ���ڽӱ�洢
		unordered_map<string, int> mp; // �����б�ţ� ������±���в���

		// ���캯�� : ��ʼ���滮����Ҫ�ĺ�����Ϣ + ͼ����Ϣ + ӳ����Ϣ
		Plan();

		// ����չʾ
		void ShowMenu();

		// ���ܲ˵�
		void planFuction();

		// ������ͳһ
		void sortFunction();

		// �������� -> ���ݻ���ʱ���С��������
		void mySort1(vector<Flight>& flight, int l, int r);

		// �������� -> ���ݻ���ʱ��Ӵ�С����
		void mySort2(vector<Flight>& flight, int l, int r);

		// ð������ -> ������С���Ѵ�С��������
		void mySort3(vector<Flight>& flight, int l, int r);

		// ð������ -> ������С���ѴӴ�С����
		void mySort4(vector<Flight>& flight, int l, int r);

		// ���������
		void outputSortResult();

		// ���Ż� dijkstra �� s �� t �����ʱ��
		void heap_dijkstra();
		void heap_dijkstra(string s, string t);

		// spfa �� s �� t �� s �� t ����С����
		void spfa();
		void spfa(string s, string t);

		// Floyd ��������������֮�����̵���ʱ��
		void floyd();

		// bfs ��ĳ�����г��������������е����ٺ���������� 
		void bfs();
		void bfs(string& s, string& t);

		// �����ݵ� dfs ���ĳ�����г����Ƿ��ܵ�����һ������ -- ͬʱ������е��﷽��
		void dfs();
		void dfs(int& dest, int& now, vector<bool>& vis, vector<string>& path, vector<vector<string> >& sum_path);
};