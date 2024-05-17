#include "Plan.h"

// 构造函数 : 初始化规划所需要的航班信息 + 图的信息 + 映射信息
Plan::Plan() {
	// 初始化航班向量
	ifstream ifs;
	ifs.open("Flight.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "规划系统出现故障" << endl;
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

	// 初始化哈希映射
	ifs.open("num.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "规划系统出现故障" << endl;
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

	// 初始化邻接表存图
	for (auto& [num, stP, edP, stTm, edTm, len, pr] : flight) {
		auto id1 = mp[stP];
		e[id1].push_back({num,edP,pr[0].first,len});
	}
}

// 展示管理员功能菜单
void Plan::ShowMenu() {
	system("cls");
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***                         欢迎进入行程规划系统 		             ***" << endl;
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***                  1. 航班排序查看信息          	  	    	     ***" << endl;
	cout << "                 ***                                                                         ***" << endl;
	cout << "                 ***                  2. 行程最短时间计算          	  	    	     ***" << endl;
	cout << "                 ***                                                                         ***" << endl;
	cout << "                 ***                  3. 行程最小花费计算          	  	    	     ***" << endl;
	cout << "                 ***                                                                         ***" << endl;
	cout << "                 ***                  4. 查询最少换乘次数          	  	    	     ***" << endl;
	cout << "                 ***                                                                         ***" << endl;
	cout << "                 ***                  5. 任意城市之间行程最短时间计算          	  	     ***" << endl;
	cout << "                 ***                                                                         ***" << endl;
	cout << "                 ***                  6. 查询两城市之间所有路线                              ***" << endl;
	cout << "                 ***                                                                         ***" << endl;
	cout << "                 ***                  0. 返回主菜单     		                     ***" << endl;
	cout << "                 *******************************************************************************" << endl;
}

// 实现管理员功能
void  Plan::planFuction() {
	while (true)
	{
		this->ShowMenu();
		char opt;
		cin >> opt;
		switch (opt) {
			case '0': // 返回主菜单
				return;
				break;
			case '1': // 航班排序查看信息
				this->sortFunction();
				break;
			case '2': // 行程最短时间计算
				this->heap_dijkstra();
				break;
			case '3': // 行程最小花费计算
				this->spfa();
				break;
			case '4': // 查询最少换乘次数
				 this->bfs();
				break;
			case '5': // 任意城市之间行程最短时间计算
				this->floyd();
				break;
			case '6': // 查询两城市之间所有路线
				this->dfs();
				break;
			default:
				cout << "输入不合法\n";
				system("pause");
				break;
		}
	}
}

/*
	按照票价排序, 按照飞行时间排序
	(最小, 最大)
*/

void Plan::sortFunction() {
	cout << "选择按照票价排序还是按照飞行时间排序: " << '\n';
	cout << "1 代表按照票价从小到大排序" << '\n'; 
	cout << "2 代表按照票价从大到小排序" << '\n';
	cout << "3 代表按照飞行时间从小到大排序" << '\n';
	cout << "4 代表按照飞行时间从大到小排序" << '\n';
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
			cout << "输入错误, 请重新输入" << '\n';
		}
	}
	this->outputSortResult(); // 输出排序结果
}

// 快速排序 -> 根据花费时间从小到大排序
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

// 快速排序 -> 根据花费时间从大到小排序
void Plan::mySort2(vector<Flight>& flight, int l, int r) {
	this->mySort1(flight, l, r);
	reverse(flight.begin(), flight.end());
}

// 冒泡排序 -> 根据最小花费从小到大排序
void Plan::mySort3(vector<Flight>& flight, int L, int R) {
	for (int i = L; i <= R; i++) {
		for (int j = L; j <= R - (i - L + 1); j++) {
			if (flight[j].ticket[0].first > flight[j + 1].ticket[0].first) {
				swap(flight[j], flight[j + 1]);
			}
		}
	}
}

// 冒泡排序 -> 根据最小花费从大到小排序
void Plan::mySort4(vector<Flight>& flight, int L, int R) {
	for (int i = L; i <= R; i++) {
		for (int j = L; j <= R - (i - L + 1); j++) {
			if (flight[j].ticket[0].first < flight[j + 1].ticket[0].first) {
				swap(flight[j], flight[j + 1]);
			}
		}
	}
}

// 输出排序结果
void Plan::outputSortResult() {
	cout << "排序后的结果如下: " << '\n';
	for (int i = 0; i < flight.size(); i++) {
		auto& [num, stP, edP, stTm, edTm, len, pr] = flight[i];
		string toStringpr[3][2]; // 将 {票价 余票} 信息用 string 形式存储
		for (int i = 0; i < 3; i++) { // 将长度小于 4 的左边加空格补齐到 4, 美化输出格式
			toStringpr[i][0] = to_string(pr[i].first);
			toStringpr[i][1] = to_string(pr[i].second);
			if (toStringpr[i][0].size() == 3) toStringpr[i][0] = ' ' + toStringpr[i][0];
			else if (toStringpr[i][0].size() == 2) toStringpr[i][0] = "  " + toStringpr[i][0];
			if (toStringpr[i][1].size() == 3) toStringpr[i][1] = ' ' + toStringpr[i][1];
			else if (toStringpr[i][1].size() == 2) toStringpr[i][1] = "  " + toStringpr[i][1];
		}
		cout << '\n';
		cout << "所要查询的航班情况如下: " << '\n';
		cout << "航班号: " << num << '\n';
		cout << "起落位置: " << stP << "--->" << edP << '\n';
		cout << "起始时间: " << stTm << '\n';
		cout << "降落时间: " << edTm << '\n';
		cout << "飞行时长: " << len << "min" << '\n';
		cout << "机票情况如下: " << '\n';
		cout << "经济舱 : " << "{ 价格: " << toStringpr[0][0] << " ; " << "余票: " << toStringpr[0][1] << " }" << '\n';
		cout << "商务舱 : " << "{ 价格: " << toStringpr[1][0] << " ; " << "余票: " << toStringpr[1][1] << " }" << '\n';
		cout << "头等舱 : " << "{ 价格: " << toStringpr[2][0] << " ; " << "余票: " << toStringpr[2][1] << " }" << '\n';
		cout << '\n';
	}

	system("pause");
}

// 堆优化 dijkstra 求 s 到 t 的最短时间
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
	cout << "从" << s << "到" << t << "的最短时间是: " << d[id2] << '\n';

	system("pause");
}
void Plan::heap_dijkstra() {
	string s, t;
	cout << "请输入始发地: ";
	cin >> s;
	cout << "请输入目的地: ";
	cin >> t;
	heap_dijkstra(s, t);
}

// spfa 求 s 到 t 的 s 到 t 的最小花费
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
	cout << "从" << s << "到" << t << "的最小花费是: " << d[id2] << '\n';

	system("pause");
}
void Plan::spfa() {
	string s, t;
	cout << "请输入始发地: ";
	cin >> s;
	cout << "请输入目的地: ";
	cin >> t;
	spfa(s, t);
}

// Floyd 求任意两个城市之间的最短到达时间
void Plan::floyd() {
	int d[MAXN][MAXN];
	int n = mp.size(); // 总城市数量

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			d[i][j] = (i == j ? 0 : 1e9);
		}
	}

	// 初始化邻接矩阵
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
		cout << "系统故障!" << '\n';
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
				cout << "从 " << city1 << " 到 " << city2 << " 的最短时间是 " << d[i][j] << " min" << '\n';
			}
			else {
				string tmp = city1 + " 无法到达 " + city2;
				output.push_back(tmp);
			}
		}
	}
	for(auto &x : output) cout << x << '\n'; // 输出无法到达的城市

	system("pause");
}

// bfs 从某个城市出发到达其他城市的最小换乘次数 
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
			cout << "从 " << s << " 到 " << t << " 的最少航班乘坐次数 是 " << d[id2] << " 次" << '\n';
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
	cout << (string)(s + " 无法到达 " + t) << '\n';

	system("pause");
}
void Plan::bfs() {
	string s, t;
	cout << "请输入始发地: ";
	cin >> s;
	cout << "请输入目的地: ";
	cin >> t;
	bfs(s, t);
}


// 带回溯的 dfs 求从某个城市出现是否能到达另一个城市 -- 同时输出所有到达方案
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
	cout << "请输入始发地: ";
	cin >> s;
	cout << "请输入目的地: ";
	cin >> t;
	vector<vector<string> > sum_path; // 存储所有路径
	vector<string> path; // 存储目前路径
	vector<bool> vis(MAXN, false);
	dfs(mp[t], mp[s], vis, path, sum_path);
	if (sum_path.size() == 0) {
		cout << (string)(s + " 无法到达 " + t) << '\n';
		return ;
	}
	cout << "从 " << s << " 到 " << t << "共有以下航班路线: " << '\n';
	for (auto& p : sum_path) {
		for (int i = 0; i < p.size(); i++) {
			cout << p[i];
			if(i != p.size() - 1) cout << " --> ";
		}
		cout << '\n';
	}

	system("pause");
}