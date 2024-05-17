#include "Manage.h"
#include "BasicFuction.h"
#include "Flight.h"
#include "System.h"

// 管理员登录
bool Manage::manageLogin() {
	if (this->loginSuccess) { // 之前已经成功登录过
		return true;
	}

	// 登录界面
	system("cls");
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***                         欢迎进入管理员登录界面		             ***" << endl;
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***                         << 请确保周围环境安全 >>		             ***" << endl;
	cout << "                 *******************************************************************************" << endl;

	// 读取管理员账户信息
	ifstream ifs;
	ifs.open("ManageInfo.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "文件打开失败!" << endl;
		system("pause");
		return false;
	}

	pair<string, string> RightPassword;
	pair<string, string> LoginPassword;
	ifs >> RightPassword.first >> RightPassword.second;
	ifs.close();

	LoginPassword = LoginAccount(); // 存储登录账号

	if (LoginPassword.first == RightPassword.first && LoginPassword.second == RightPassword.second) {
		this->loginSuccess = true;
		cout << '\n';
		cout << "登录成功" << '\n';
		system("pause");
		return true;
	}
	else {
		cout << '\n';
		cout << "登录失败" << '\n';
		system("pause");
		return false;
	}
}

// 展示管理员功能菜单
void Manage::manageShowMenu() {
	system("cls");
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***                         欢迎进入管理员功能界面		             ***" << endl;
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***                  1. 增加航班          2.删除航班	  	    	     ***" << endl;
	cout << "                 ***                                                                         ***" << endl;
	cout << "                 ***                  3. 修改航班          4.查询航班         	      	     ***" << endl;
	cout << "                 ***                                                                         ***" << endl;
	cout << "                 ***                           0. 返回主菜单     		             ***" << endl;
	cout << "                 *******************************************************************************" << endl;
}

// 实现管理员功能
void Manage::manageFuction() {
	while (true)
	{
		this->manageShowMenu();
		char opt;
		cin >> opt;
		switch (opt) {
			case '0': // 返回主菜单
				return;
				break;
			case '1': // 添加新航班
				this->addFlight();
				break;
			case '2': // 删除航班
				this->removeFlight();
				break;
			case '3': // 修改航班
				this->changeFlight();
				break;
			case '4': // 查询航班
				this->queryFlight();
				break;
			default:
				cout << "输入不合法\n";
				system("pause");
				break;
		}
	}
}

// 添加单个航班 (提高代码复用率)
void Manage::addOneFlight(Flight &flight) {
	ofstream ofs;
	ofs.open("Flight.txt", ios::out | ios::app);
	if (ofs.is_open() == false) {
		cout << "系统运行时出现故障" << endl;
		system("pause");
		system("cls");
		return ;
	}

	ofs << flight.flightNum << ' ' << flight.startPosition << ' ' << flight.endPosotion << '\n';
	ofs << flight.startTime << ' ' << flight.endTime << '\n';
	ofs << flight.flyTime << '\n';
	for (int i = 0; i < 3; i++) {
		ofs << flight.ticket[i].first << ' ' << flight.ticket[i].second << '\n';
	}
	ofs << '\n';
	ofs.close();
}

// 添加新航班
void Manage::addFlight() {
	system("cls");
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***				  添加航班    				     ***" << endl;
	cout << "                 *******************************************************************************" << endl;
	auto askAndCheck = [&](Flight &flight) -> bool {
		if (checkTicket(flight) == false) { // 填写信息有误
			// checkTicket 函数会回显错误信息
			cout << "添加失败 !" << '\n';
		}
		else { // 添加航班信息
			this->addOneFlight(flight);
			cout << "添加成功!" << '\n';
		}
		cout << "是否继续添加 ? <是 或 否>" << '\n';
		string opt;
		while (cin >> opt) {
			if (opt == "是") {
				return true;
			}
			else if (opt == "否") {
				return false;
			}
			else {
				cout << "输入不合法 !" << '\n';
			}
		}
	};
	Flight flight = Flight();
	do {
		cout << "请输入要添加的航班号: ";
		cin >> flight.flightNum;
		cout << "请输入出发地: ";
		cin >> flight.startPosition;
		cout << "请输入降落地: ";
		cin >> flight.endPosotion;
		cout << "请输入起飞时间: ";
		cin >> flight.startTime;
		cout << "请输入降落时间: ";
		cin >> flight.endTime;
		
		for (int i = 0; i < 3; i++) {
			if (i == 0) {
				cout << "请输入经济舱信息: " << '\n';
			}
			else if (i == 1) {
				cout << "请输入商务舱信息: " << '\n';
			}
			else {
				cout << "请输入头等舱信息: " << '\n';
			}
			cout << "票价: ";
			cin >> flight.ticket[i].first;
			cout << "票数: ";
			cin >> flight.ticket[i].second;
		}
	}
	while(askAndCheck(flight));
}

// 删除航班
void Manage::removeFlight() {
	// 显示删除航班界面
	system("cls");
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***				  删除航班    				     ***" << endl;
	cout << "                 *******************************************************************************" << endl;

	vector<Flight> tmpVector; // 存储目前所有航班
	ifstream ifs;
	ifs.open("Flight.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "删除航班出现故障" << endl;
		system("pause");
		system("cls");
		return ;
	}
	Flight tmp;
	while (ifs >> tmp.flightNum >> tmp.startPosition >> tmp.endPosotion) {
		ifs >> tmp.startTime >> tmp.endTime;
		ifs >> tmp.flyTime;
		for (int i = 0; i < 3; i++) {
			ifs >> tmp.ticket[i].first >> tmp.ticket[i].second;
		}
		tmpVector.push_back(tmp);
	}
	ifs.close();

	int cnt = 0;
	cout << "查询到所有航班号如下: " << '\n';
	cout << "共有: " << tmpVector.size() << "个航班" << '\n';
	for (auto& x : tmpVector) {
		cout << "第 " << ++ cnt << " 个航班的航班号:" << ' ';
		cout << x.flightNum << '\n';
	}

	string removeNum;
	int pos = -1;
	bool hasFlight = false; 
	cout << "请输入要删除航班的航班号: ";
	cin >> removeNum;
	for (int i = 0; i < tmpVector.size(); i++) {
		string flightNum = tmpVector[i].flightNum;
		if (flightNum == removeNum) {
			hasFlight = true;
			pos = i;
			break;
		}
	}

	// 不存在航班编号
	if (hasFlight == false) {
		cout << "航班不存在，请检查输入是否有误" << '\n';
		system("pause");
		return ;
	}

	// 清空文件 , 将除被下架图书以外的信息重新写入文件
	ofstream ofs;
	ofs.open("Flight.txt", ios::trunc);
	for (int i = 0; i < tmpVector.size(); i++) {
		if(i == pos) continue;
		this->addOneFlight(tmpVector[i]);
	}
	ofs.close();

	cout << "删除航班号为 " << removeNum << " 的航班成功" << '\n';
	system("pause");
}

// 修改航班
void Manage::changeFlight() {
	/*
		航班号 起飞地点 降落地点
		起飞时间 降落时间
		飞行时长
		票价 / 票数 --> 经济舱, 商务舱, 头等舱
	*/
	// 显示修改航班界面
	system("cls");
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***				  修改航班    				     ***" << endl;
	cout << "                 *******************************************************************************" << endl;

	
	vector<Flight> tmpVector; // 存储目前所有航班
	ifstream ifs;
	ifs.open("Flight.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "修改航班出现故障" << endl;
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
		tmpVector.push_back(tmp);
	}
	ifs.close();

	string askNum;
	int pos = -1;
	bool hasFlight = false;
	cout << "请输入要修改航班的航班号: ";
	cin >> askNum;
	for (int i = 0; i < tmpVector.size(); i++) {
		string flightNum = tmpVector[i].flightNum;
		if (flightNum == askNum) {
			hasFlight = true;
			pos = i;
			break;
		}
	}

	// 不存在航班编号
	if (hasFlight == false) {
		cout << "航班不存在，请检查输入是否有误" << '\n';
		system("pause");
		return;
	}

	// 查询对应航班信息
	for (int i = 0; i < tmpVector.size(); i++) {
		if (i != pos) continue;
		auto& [num, stP, edP, stTm, edTm, len, pr] = tmpVector[i];
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
		cout << "所要修改的航班情况如下: ";
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
	
	auto askContinue = []() {
		cout << "是否继续修改其他信息" << '\n';
		cout << "1. 是 ; 2. 否" << '\n';
		string opt;
		while (cin >> opt) {
			if (opt == "1") return true;
			else if (opt == "2") return false;
			else cout << "输入不合法!" << '\n';
		}
	};

	do {
		// 展示修改选项
		cout << "请问您要修改什么信息 ?" << '\n';
		cout << "1. 修改航班号" << '\n';
		cout << "2. 修改始发地" << '\n';
		cout << "3. 修改目的地" << '\n';
		cout << "4. 修改起飞时间" << '\n';
		cout << "5. 修改降落时间" << '\n';
		cout << "6. 修改票务信息" << '\n';

		bool fg = true; // 是否成功修改
		string opt, info;
		cin >> opt;
		if (opt == "1") {
			cout << "请输入新的航班号: ";
			cin >> info;
			tmpVector[pos].flightNum = info;
		}
		else if (opt == "2") {
			cout << "请输入新的始发地: ";
			cin >> info;
			tmpVector[pos].startPosition = info;
		}
		else if (opt == "3") {
			cout << "请输入新的目的地: ";
			cin >> info;
			tmpVector[pos].endPosotion = info;
		}
		else if (opt == "4") {
			cout << "请输入新的始发时间: ";
			cin >> info;
			string tmp = tmpVector[pos].startTime;
			tmpVector[pos].startTime = info;
			// 检查输入的新时间是否合法
			if (checkTicket(tmpVector[pos]) == false) {
				cout << "输入信息不合法 !" << '\n';
				tmpVector[pos].startTime = tmp;
				continue;
			}
		}
		else if (opt == "5") {
			cout << "请输入新的降落时间: ";
			cin >> info;
			string tmp = tmpVector[pos].startTime;
			tmpVector[pos].endTime = info;
			// 检查输入的新时间是否合法
			if (checkTicket(tmpVector[pos]) == false) {
				cout << "输入信息不合法 !" << '\n';
				tmpVector[pos].startTime = tmp;
				continue;
			}
		}
		else if (opt == "6") {
			string num;
			cout << "请输入您要修改什么类型的机票 ?" << '\n';
			cout << "1. 经济舱" << '\n';
			cout << "2. 商务舱" << '\n';
			cout << "3. 头等舱" << '\n';
			while (cin >> num) {
				if (num == "1") {
					string ch;
					int info;
					cout << "输入 1 修改票价 ; 输入 2 修改票数 :";
					while (cin >> ch) {
						if (ch == "1") {
							cout << "将要将票价修改为: ";
							cin >> info;
							tmpVector[pos].ticket[0].first = info;
							break;
						}
						else if (ch == "2") {
							cout << "将要将票数修改为: ";
							cin >> info;
							tmpVector[pos].ticket[0].first = info;
							break;
						}
						else {
							cout << "输入不合法 !" << '\n';
						}
					}
					
					break;
				}
				else if (num == "2") {
					string ch;
					int info;
					cout << "输入 1 修改票价 ; 输入 2 修改票数 :";
					while (cin >> ch) {
						if (ch == "1") {
							cout << "将要将票价修改为: ";
							cin >> info;
							tmpVector[pos].ticket[1].first = info;
							break;
						}
						else if (ch == "2") {
							cout << "将要将票数修改为: ";
							cin >> info;
							tmpVector[pos].ticket[1].first = info;
							break;
						}
						else {
							cout << "输入不合法 !" << '\n';
						}
					}

					break;
				}
				else if (num == "3") {
					string ch;
					int info;
					cout << "输入 1 修改票价 ; 输入 2 修改票数 :";
					while (cin >> ch) {
						if (ch == "1") {
							cout << "将要将票价修改为: ";
							cin >> info;
							tmpVector[pos].ticket[2].first = info;
							break;
						}
						else if (ch == "2") {
							cout << "将要将票数修改为: ";
							cin >> info;
							tmpVector[pos].ticket[2].first = info;
							break;
						}
						else {
							cout << "输入不合法 !" << '\n';
						}
					}

					break;
				}
				else {
					cout << "输入不合法 !" << '\n';
				}
			}
		}
		else {
			fg = false;
			cout << "输入不合法 !" << '\n';
		}

		if (fg) {
			// 清空文件 , 将容器信息写回文件
			ofstream ofs;
			ofs.open("Flight.txt", ios::trunc);
			for (int i = 0; i < tmpVector.size(); i++) {
				this->addOneFlight(tmpVector[i]);
			}
			ofs.close();


			cout << "修改成功, 修改后的航班信息如下: " << '\n';
			auto& [num, stP, edP, stTm, edTm, len, pr] = tmpVector[pos];
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
			cout << "所要修改的航班情况如下: ";
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

			system("pause");
		}
	}
	while(askContinue());

	system("pause");

}

// 查询航班
void Manage::queryFlight() {
	// 查询航班界面
	system("cls");
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***				  查询航班    				     ***" << endl;
	cout << "                 *******************************************************************************" << endl;

	cout << "请问您要查询全部航班还是单个航班 ?" << '\n';
	cout << "输入 1 查询全部航班 ; 输入 2 查询单个航班" << '\n';
	string opt;
	while (cin >> opt) {
		if (opt == "1" || opt == "2") {
			if (opt == "1") {
				System tmp = System();
				tmp.lookAllFlight(); // 调用 System.h 中声明的静态方法来查询所有航班
			}
			else {
				vector<Flight> tmpVector; // 存储目前所有航班
				ifstream ifs;
				ifs.open("Flight.txt", ios::in);
				if (ifs.is_open() == false) {
					cout << "删除航班出现故障" << endl;
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
					tmpVector.push_back(tmp);
				}
				ifs.close();

				string askNum;
				int pos = -1;
				bool hasFlight = false;
				cout << "请输入要查询航班的航班号: ";
				cin >> askNum;
				for (int i = 0; i < tmpVector.size(); i++) {
					string flightNum = tmpVector[i].flightNum;
					if (flightNum == askNum) {
						hasFlight = true;
						pos = i;
						break;
					}
				}

				// 不存在航班编号
				if (hasFlight == false) {
					cout << "航班不存在，请检查输入是否有误" << '\n';
					system("pause");
					return;
				}

				// 查询对应航班信息
				for (int i = 0; i < tmpVector.size(); i ++ ){
					if(i != pos) continue; 
					auto& [num, stP, edP, stTm, edTm, len, pr] = tmpVector[i];
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
					cout << "所要查询的航班情况如下: ";
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
			break;
		}
		else {
			cout << "输入不合法, 请重试" << '\n';
		}
	}
}