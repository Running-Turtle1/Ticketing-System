#include "order.h"

// 显示订单界面
void Order::showOrderMenu() {
	// 展示功能菜单
	system("cls");
	cout << "                 **********************************************************************************" << endl;
	cout << "                 ***                           欢迎使用订单系统    		                ***" << endl;
	cout << "                 **********************************************************************************" << endl;
	cout << "                 ***  1. 查看所有订单                               2. 查看指定订单             ***" << endl;
	cout << "                 ***                                                                            ***" << endl;
	cout << "                 ***  0. 返回主菜单							        ***" << endl;
	cout << "                 **********************************************************************************" << endl;
}

// 订单系统
void Order::OrderFuction() {
	while (true)
	{
		this->showOrderMenu();
		char opt;
		cin >> opt;
		switch (opt) {
			case '0': // 返回主菜单
				return;
				break;
			case '1': // 查看所有订单
				this->queryAllOrder();
				break;
			case '2': // 查看指定订单
				this->queryOrderByAccount();
				break;
			default:
				cout << "输入不合法\n";
				system("pause");
				break;
		}
	}
}

// 查询所有订单
void Order::queryAllOrder() {
    system("cls");
    cout << "*******************************************************************************" << endl;
    cout << "***				  全部订单    				    ***" << endl;
    cout << "*******************************************************************************" << endl;


    ifstream ifs;
    ifs.open("Order.txt", ios::in);
    if (ifs.is_open() == false) {
        cout << "删除航班出现故障" << endl;
        system("pause");
        system("cls");
        return;
    }
    
    string p, num, level;
    while (ifs >> p >> num >> level) {
        cout << p << ' ' << num << ' ' << level << '\n';
    }

	system("pause");
}

// 查询对应账号的对应订单
void Order::queryOrderByAccount() {
	system("cls");

	ifstream ifs;
	ifs.open("Order.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "删除航班出现故障" << endl;
		system("pause");
		system("cls");
		return;
	}

	string account;
	cout << "请输入要查询哪个账号的订单: ";
	cin >> account;

	int cnt = 0;
	string p, num, level;
	while (ifs >> p >> num >> level) {
		if (p == account) {
			cnt ++;
			cout << p << ' ' << num << ' ' << level << '\n';
		}
	}

	if (!cnt) {
		cout << "未查询到任何订单!" << '\n';
	}

	system("pause");
}

// 查询对应账号的对应订单
vector<string> Order::queryOrderByAccount2(string account) {
	system("cls");

	ifstream ifs;
	ifs.open("Order.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "删除航班出现故障" << endl;
		system("pause");
		system("cls");
		return vector<string> ();
	}

	vector<string> vc;

	int cnt = 0;
	string p, num, level;
	while (ifs >> p >> num >> level) {
		if (p == account) {
			cnt++;
			cout << p << ' ' << num << ' ' << level << '\n';
			vc.push_back(p);
			vc.push_back(num);
			vc.push_back(level);
		}
	}

	return vc;
}

// 添加订单
void Order::addOrder(string p, string num, string lv) {
	ofstream ofs;
	ofs.open("order.txt", ios::out | ios::app);
	if (ofs.is_open() == false) {
		cout << "系统运行时出现故障" << endl;
		system("pause");
		system("cls");
		return;
	}

	ofs << p << ' ' << num << ' ' << lv << '\n';

	ofs.close();
}

//删除账号 a 的航班号为 b 的订单 (退票时使用)
void Order::deleteOrder(string a, string b) {

	vector<string> tmpVector; // 存储目前所有订单
	ifstream ifs;
	ifs.open("Order.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "系统出现故障" << endl;
		system("pause");
		system("cls");
		return;
	}
	string x;
	while (ifs >> x) {
		tmpVector.push_back(x);
	}
	ifs.close();

	int pos = -1;
	for (int i = 0; i < tmpVector.size(); i += 3) {
		string stra = tmpVector[i];
		string strb = tmpVector[i + 1];
		string strc = tmpVector[i + 2];
		if (stra == a && strb == b) {
			pos = i;
		}
	}

	if (pos == -1) {
		return ;
	}

	// 清空文件 , 将除被下架图书以外的信息重新写入文件
	ofstream ofs;
	ofs.open("Order.txt", ios::trunc);
	for (int i = 0; i < tmpVector.size(); i += 3) {
		string stra = tmpVector[i];
		string strb = tmpVector[i + 1];
		string strc = tmpVector[i + 2];
		if(pos == i) continue;
		ofs << stra << ' ' << strb << ' ' << strc << '\n';
	}
	ofs.close();
}