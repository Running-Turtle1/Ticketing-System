#include "Plan.h"

// ���캯�� : ��ʼ���滮����Ҫ�ĺ�����Ϣ + ͼ����Ϣ + ӳ����Ϣ
Plan::Plan() {
	// ��ʼ����������
	ifstream ifs;
	ifs.open("Flight.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "�滮ϵͳ���ֹ���" << endl;
		system("pause");
		system("cls");
		return;
	}
	Flight tmp;
	while (ifs >> tmp.flightNum >> tmp.startPosition >> tmp.endPosotion) {
		ifs >> tmp.startTime >> tmp.endTime;
		ifs >> tmp.flyTime;
		for (int i = 0; i < 3; i++) {
			ifs >> tmp.ticket[i].first >> tmp.ticket[i].second;
		}
		flight.push_back(tmp);
	}
	ifs.close();

	// ��ʼ����ϣӳ��
	ifs.open("num.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "�滮ϵͳ���ֹ���" << endl;
		system("pause");
		system("cls");
		return;
	}
	string a;
	int b;
	while (ifs >> a >> b) {
		mp[a] = b;
	}
	ifs.close();

	// ��ʼ���ڽӱ��ͼ
	for (auto& [num, stP, edP, stTm, edTm, len, pr] : flight) {
		auto id1 = mp[stP];
		e[id1].push_back({num,edP,pr[0].first,len});
	}
}

// չʾ����Ա���ܲ˵�
void Plan::ShowMenu() {
	system("cls");
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***                         ��ӭ�����г̹滮ϵͳ 		             ***" << endl;
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***                  1. ��������鿴��Ϣ          	  	    	     ***" << endl;
	cout << "                 ***                                                                         ***" << endl;
	cout << "                 ***                  2. �г����ʱ�����          	  	    	     ***" << endl;
	cout << "                 ***                                                                         ***" << endl;
	cout << "                 ***                  3. �г���С���Ѽ���          	  	    	     ***" << endl;
	cout << "                 ***                                                                         ***" << endl;
	cout << "                 ***                  4. ��ѯ���ٻ��˴���          	  	    	     ***" << endl;
	cout << "                 ***                                                                         ***" << endl;
	cout << "                 ***                  5. �������֮���г����ʱ�����          	  	     ***" << endl;
	cout << "                 ***                                                                         ***" << endl;
	cout << "                 ***                  6. ��ѯ������֮������·��                              ***" << endl;
	cout << "                 ***                                                                         ***" << endl;
	cout << "                 ***                  0. �������˵�     		                     ***" << endl;
	cout << "                 *******************************************************************************" << endl;
}

// ʵ�ֹ���Ա����
void  Plan::planFuction() {
	while (true)
	{
		this->ShowMenu();
		char opt;
		cin >> opt;
		switch (opt) {
			case '0': // �������˵�
				return;
				break;
			case '1': // ��������鿴��Ϣ
				this->sortFunction();
				break;
			case '2': // �г����ʱ�����
				this->heap_dijkstra();
				break;
			case '3': // �г���С���Ѽ���
				this->spfa();
				break;
			case '4': // ��ѯ���ٻ��˴���
				 this->bfs();
				break;
			case '5': // �������֮���г����ʱ�����
				this->floyd();
				break;
			case '6': // ��ѯ������֮������·��
				this->dfs();
				break;
			default:
				cout << "���벻�Ϸ�\n";
				system("pause");
				break;
		}
	}
}

/*
	����Ʊ������, ���շ���ʱ������
	(��С, ���)
*/

void Plan::sortFunction() {
	cout << "ѡ����Ʊ�������ǰ��շ���ʱ������: " << '\n';
	cout << "1 ������Ʊ�۴�С��������" << '\n'; 
	cout << "2 ������Ʊ�۴Ӵ�С����" << '\n';
	cout << "3 �����շ���ʱ���С��������" << '\n';
	cout << "4 �����շ���ʱ��Ӵ�С����" << '\n';
	string opt;
	while (cin >> opt) {
		if (opt == "1" || opt == "2" || opt == "3" || opt == "4") {
			if (opt == "1") {
				this->mySort3(this->flight, 0, this->flight.size() - 1);
			}
			else if (opt == "2") {
				this->mySort4(this->flight, 0, this->flight.size() - 1);
			}
			else if (opt == "3") {
				this->mySort1(this->flight, 0, this->flight.size() - 1);
			}
			else {
				this->mySort2(this->flight, 0, this->flight.size() - 1);
			}
			break;
		}
		else {
			cout << "�������, ����������" << '\n';
		}
	}
	this->outputSortResult(); // ���������
}

// �������� -> ���ݻ���ʱ���С��������
void Plan::mySort1(vector<Flight>& flight, int l, int r) {
	if(l >= r) return ;
	int x = flight[(l + r) >> 1].flyTime, i = l - 1, j = r + 1;
	while (i < j) {
		do i++; while (flight[i].flyTime < x);
		do j--; while (flight[j].flyTime > x);
		if (i < j) swap(flight[i], flight[j]);
	}
	mySort1(flight, l, j); mySort1(flight, j + 1, r);
}

// �������� -> ���ݻ���ʱ��Ӵ�С����
void Plan::mySort2(vector<Flight>& flight, int l, int r) {
	this->mySort1(flight, l, r);
	reverse(flight.begin(), flight.end());
}

// ð������ -> ������С���Ѵ�С��������
void Plan::mySort3(vector<Flight>& flight, int L, int R) {
	for (int i = L; i <= R; i++) {
		for (int j = L; j <= R - (i - L + 1); j++) {
			if (flight[j].ticket[0].first > flight[j + 1].ticket[0].first) {
				swap(flight[j], flight[j + 1]);
			}
		}
	}
}

// ð������ -> ������С���ѴӴ�С����
void Plan::mySort4(vector<Flight>& flight, int L, int R) {
	for (int i = L; i <= R; i++) {
		for (int j = L; j <= R - (i - L + 1); j++) {
			if (flight[j].ticket[0].first < flight[j + 1].ticket[0].first) {
				swap(flight[j], flight[j + 1]);
			}
		}
	}
}

// ���������
void Plan::outputSortResult() {
	cout << "�����Ľ������: " << '\n';
	for (int i = 0; i < flight.size(); i++) {
		auto& [num, stP, edP, stTm, edTm, len, pr] = flight[i];
		string toStringpr[3][2]; // �� {Ʊ�� ��Ʊ} ��Ϣ�� string ��ʽ�洢
		for (int i = 0; i < 3; i++) { // ������С�� 4 ����߼ӿո��뵽 4, ���������ʽ
			toStringpr[i][0] = to_string(pr[i].first);
			toStringpr[i][1] = to_string(pr[i].second);
			if (toStringpr[i][0].size() == 3) toStringpr[i][0] = ' ' + toStringpr[i][0];
			else if (toStringpr[i][0].size() == 2) toStringpr[i][0] = "  " + toStringpr[i][0];
			if (toStringpr[i][1].size() == 3) toStringpr[i][1] = ' ' + toStringpr[i][1];
			else if (toStringpr[i][1].size() == 2) toStringpr[i][1] = "  " + toStringpr[i][1];
		}
		cout << '\n';
		cout << "��Ҫ��ѯ�ĺ����������: " << '\n';
		cout << "�����: " << num << '\n';
		cout << "����λ��: " << stP << "--->" << edP << '\n';
		cout << "��ʼʱ��: " << stTm << '\n';
		cout << "����ʱ��: " << edTm << '\n';
		cout << "����ʱ��: " << len << "min" << '\n';
		cout << "��Ʊ�������: " << '\n';
		cout << "���ò� : " << "{ �۸�: " << toStringpr[0][0] << " ; " << "��Ʊ: " << toStringpr[0][1] << " }" << '\n';
		cout << "����� : " << "{ �۸�: " << toStringpr[1][0] << " ; " << "��Ʊ: " << toStringpr[1][1] << " }" << '\n';
		cout << "ͷ�Ȳ� : " << "{ �۸�: " << toStringpr[2][0] << " ; " << "��Ʊ: " << toStringpr[2][1] << " }" << '\n';
		cout << '\n';
	}

	system("pause");
}

// ���Ż� dijkstra �� s �� t �����ʱ��
void Plan::heap_dijkstra(string s, string t) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > heap;
	vector<int> d(MAXN);
	vector<bool> vis(MAXN);
	for (int i = 0; i < d.size(); i++) {
		d[i] = INT_MAX;
	}
	for (int i = 0; i < vis.size(); i++) {
		vis[i] = false;
	}
	int id1 = mp[s], id2 = mp[t];
	d[id1] = 0;
	heap.push({ d[id1], id1 });
	while (heap.size()) {
		pair<int, int> t = heap.top();
		heap.pop();
		auto u = t.second;
		if (vis[u] == true) continue;
		for (auto edge : e[u]) {
			int v = mp[edge.to];
			if (d[u] + edge.time < d[v]) {
				d[v] = d[u] + edge.time;
				heap.push({ d[v], v });
			}
		}
	}
	cout << "��" << s << "��" << t << "�����ʱ����: " << d[id2] << '\n';

	system("pause");
}
void Plan::heap_dijkstra() {
	string s, t;
	cout << "������ʼ����: ";
	cin >> s;
	cout << "������Ŀ�ĵ�: ";
	cin >> t;
	heap_dijkstra(s, t);
}

// spfa �� s �� t �� s �� t ����С����
void Plan::spfa(string s, string t) {
	vector<int> d(MAXN);
	vector<bool> vis(MAXN);
	for (int i = 0; i < d.size(); i++) {
		d[i] = INT_MAX;
	}
	for (int i = 0; i < vis.size(); i++) {
		vis[i] = false;
	}
	int id1 = mp[s], id2 = mp[t];
	d[id1] = 0;
	vis[id1] = 1;
	queue<int> q;
	q.push(id1);
	while (q.size()) {
		int u = q.front(); q.pop();
		vis[u] = 0;
		for (auto ed : e[u]) {
			int v = mp[ed.to], w = ed.min_cost;
			if (d[u] + w < d[v]) {
				d[v] = d[u] + w;
				if (!vis[v]) q.push(v),vis[v] = 1;
			}
		}
	}
	cout << "��" << s << "��" << t << "����С������: " << d[id2] << '\n';

	system("pause");
}
void Plan::spfa() {
	string s, t;
	cout << "������ʼ����: ";
	cin >> s;
	cout << "������Ŀ�ĵ�: ";
	cin >> t;
	spfa(s, t);
}

// Floyd ��������������֮�����̵���ʱ��
void Plan::floyd() {
	int d[MAXN][MAXN];
	int n = mp.size(); // �ܳ�������

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			d[i][j] = (i == j ? 0 : 1e9);
		}
	}

	// ��ʼ���ڽӾ���
	for (int u = 1; u <= n; u++) {
		for (auto edge : e[u]) {
			d[u][mp[edge.to]] = min(d[u][mp[edge.to]], edge.time);
		}
	}

	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}

	ifstream ifs;
	ifs.open("num.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "ϵͳ����!" << '\n';
		system("pause");
		return ;
	}

	map<int, string> numToCity;
	string a;
	int b;
	while (ifs >> a >> b) {
		numToCity[b] = a;
	}
	ifs.close();

	vector<string> output;
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			auto city1 = numToCity[i];
			auto city2 = numToCity[j];
			if (d[i][j] != 1e9) {
				cout << "�� " << city1 << " �� " << city2 << " �����ʱ���� " << d[i][j] << " min" << '\n';
			}
			else {
				string tmp = city1 + " �޷����� " + city2;
				output.push_back(tmp);
			}
		}
	}
	for(auto &x : output) cout << x << '\n'; // ����޷�����ĳ���

	system("pause");
}

// bfs ��ĳ�����г��������������е���С���˴��� 
void Plan::bfs(string& s, string& t) {
	vector<int> d(MAXN, -1);
	queue<int> q;
	auto id1 = mp[s];
	auto id2 = mp[t];
	d[id1] = 0;
	q.push(id1);
	while (q.size()) {
		auto u = q.front();
		q.pop();
		if (u == id2) {
			cout << "�� " << s << " �� " << t << " �����ٺ���������� �� " << d[id2] << " ��" << '\n';
			system("pause");
			return ;
		}
		for (auto edge : e[u]) {
			auto v = mp[edge.to];
			if (d[v] == -1) {
				d[v] = d[u] + 1;
				q.push(v);
			}
		}
	}
	cout << (string)(s + " �޷����� " + t) << '\n';

	system("pause");
}
void Plan::bfs() {
	string s, t;
	cout << "������ʼ����: ";
	cin >> s;
	cout << "������Ŀ�ĵ�: ";
	cin >> t;
	bfs(s, t);
}


// �����ݵ� dfs ���ĳ�����г����Ƿ��ܵ�����һ������ -- ͬʱ������е��﷽��
void Plan::dfs(int& dest, int &now, vector<bool>& vis, vector<string> &path, vector<vector<string> > &sum_path) {
	if (now == dest) {
		sum_path.push_back(path);
		return ;
	}

	for (auto edge : e[now]) {
		auto v = mp[edge.to];
		auto fl = edge.num;
		if (vis[v] == false) {
			vis[v] = true;
			path.push_back(fl);
			dfs(dest, v, vis, path, sum_path);
			vis[v] = false;
			path.pop_back();
		}
	}
}
void Plan::dfs(){
	string s, t;
	cout << "������ʼ����: ";
	cin >> s;
	cout << "������Ŀ�ĵ�: ";
	cin >> t;
	vector<vector<string> > sum_path; // �洢����·��
	vector<string> path; // �洢Ŀǰ·��
	vector<bool> vis(MAXN, false);
	dfs(mp[t], mp[s], vis, path, sum_path);
	if (sum_path.size() == 0) {
		cout << (string)(s + " �޷����� " + t) << '\n';
		return ;
	}
	cout << "�� " << s << " �� " << t << "�������º���·��: " << '\n';
	for (auto& p : sum_path) {
		for (int i = 0; i < p.size(); i++) {
			cout << p[i];
			if(i != p.size() - 1) cout << " --> ";
		}
		cout << '\n';
	}

	system("pause");
}