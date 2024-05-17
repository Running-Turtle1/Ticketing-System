#include "User.h"
#include "BasicFuction.h"
#include "System.h"
#include "Flight.h"
#include "Manage.h"
#include "order.h"

// 用户注册功能
void User::userRegistration() {
	system("cls");
	// 显示注册界面
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***				  用户注册    				     ***" << endl;
	cout << "                 *******************************************************************************" << endl;
	
	pair<string, string> account = LoginAccount(); // 获取账号密码
	
	// 判断账号是否已经被注册过
	ifstream ifs;
	ifs.open("User.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "注册系统故障, 请稍后再试" << endl;
		system("pause");
		return;
	}

	string tmpString;
	while (ifs >> tmpString) {
		if (tmpString == account.first) {
			cout << '\n';
			cout << "该账号已经被注册过, 请更换账号后注册" << endl;
			system("pause");
			ifs.close();
			return;
		}
		ifs >> tmpString; // 过滤掉密码
	}
	ifs.close();

	// 再次输入密码, 确认两次密码是否一致
	cout << '\n';
	tmpString = getPassword(0);
	if (tmpString != account.second) {
		cout << "两次输入的密码不一致!" << endl;
		cout << "请重新进行注册 " << endl;
		system("pause");
		return;
	}

	// 注册成功, 打开存放用户注册信息的文件, 并写入新用户信息
	ofstream ofs;
	ofs.open("User.txt", ios::out | ios::app);
	if (ofs.is_open() == false) { // 打开文件失败
		cout << "注册系统故障, 请稍后再试" << endl;
		system("pause");
		return;
	}
	ofs << account.first << ' ' << account.second << endl;
	ofs.close();
	cout << '\n';
	cout << "[注册成功]" << endl;

	system("pause");
}

void User::showBookTicketMenu() {
	// 展示功能菜单
	system("cls");
	cout << "                 **********************************************************************************" << endl;
	cout << "                 ***                           欢迎使用订票系统    		                ***" << endl;
	cout << "                 **********************************************************************************" << endl;
	cout << "                 ***  1. 网上购票                                       2. 网上退票             ***" << endl;
	cout << "                 ***                                                                            ***" << endl;
	cout << "                 ***  0. 返回主菜单							        ***" << endl;
	cout << "                 **********************************************************************************" << endl;
}

// 实现买票功能
void User::bookTicketFuction() {
	while (true)
	{
		this->showBookTicketMenu();
		char opt;
		cin >> opt;
		switch (opt) {
			case '0': // 返回主菜单
				return;
				break;
			case '1': // 网上购票
				this->buyTicket();
				break;
			case '2': // 网上退票
				this->refundTicket();
				break;
			default:
				cout << "输入不合法\n";
				system("pause");
				break;
		}
	}
}

// 用户登录功能
bool User::userLogin() {
	// 登录界面
	system("cls");
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***                            欢迎进入登录界面          		     ***" << endl;
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***                         << 请确保周围环境安全 >>		             ***" << endl;
	cout << "                 *******************************************************************************" << endl;

	// 读取用户账户信息
	ifstream ifs;
	ifs.open("User.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "文件打开失败!" << endl;
		system("pause");
		return false;
	}

	vector< pair<string, string> > info;
	{
		string a, b;
		while (ifs >> a >> b) {
			info.push_back({a, b});
		}
	}
	ifs.close();

	pair<string ,string> LoginInfo = LoginAccount(); // 存储登录账号
	bool find_flag = false;

	for (auto& [a, b] : info) {
		if (a == LoginInfo.first && b == LoginInfo.second) {
			find_flag = true;
			break;
		}
	}

	if (find_flag) {
		this->now_account = LoginInfo.first; // 存储目前登录的用户
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

// 用户购票功能 (同时联动订单系统)
void User::buyTicket() {
	System sys;
	Manage manage;
	Order order;

	// 首先向用户展示所有的航空信息
	system("cls");
	sys.lookAllFlight();

	// 用户选择航班号以及什么舱位
	system("cls");
	string num, level;
	cout << "请选择航班号: ";
	cin >> num;
	cout << "请选择舱位(头等舱、商务舱、经济舱): ";
	cin >> level;

	if (level != "经济舱" && level != "商务舱" && level != "头等舱") {
		cout << "舱位选择错误" << '\n';
		system("pause");
		return;
	}

	// 临时存储所有航班
	vector<Flight> tmpVector; // 存储目前所有航班
	ifstream ifs;
	ifs.open("Flight.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "系统出现故障" << endl;
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

	// 查询用户输入信息是否正确
	bool hasFlight = false;
	int pos; // 对应位置
	for (int i = 0; i < tmpVector.size(); i++) {
		string flightNum = tmpVector[i].flightNum;
		if (flightNum == num) {
			hasFlight = true;
			pos = i;
			break;
		}
	}

	if (hasFlight == false) { // 不存在航班编号
		cout << "航班不存在，请检查输入是否有误" << '\n';
		system("pause");
		return;
	}

	// 修改余票
	int wh;
	if (level == "经济舱") {
		wh = 0;
	}
	else if (level == "商务舱") {
		wh = 1;
	}
	else {
		wh = 2;
	}
	tmpVector[pos].ticket[wh].second --;

	// 修改票务文件信息
	ofstream ofs;
	ofs.open("Flight.txt", ios::trunc);
	for (int i = 0; i < tmpVector.size(); i++) {
		manage.addOneFlight(tmpVector[i]);
	}
	ofs.close();

	// 使用订单系统存储订单信息
	order.addOrder(this->now_account, num, level);
	cout << "购票成功, 已上传订单系统" << '\n';
	system("pause");
}

// 用户退票功能 (同时联动订单系统)
void User::refundTicket() {
	System sys;
	Manage manage;
	Order order;

	// 使用订单系统展示这位用户的全部订单信息
	system("cls");
	cout << "您目前的订票情况如下: " << '\n';
	vector<string> vc = order.queryOrderByAccount2(this->now_account);

	// 询问用户要退掉的票对应的航班号
	string num;
	cout << "请输出您要退票的航班号: ";
	cin >> num;


	// 调用订单系统删除对应订单
	string level;
	int pos = -1;
	for (int i = 0; i < vc.size(); i += 3) {
		string stra = vc[i];
		string strb = vc[i + 1];
		string strc = vc[i + 2];
		if (strb == num) {
			pos = i;
			level = strc;
			order.deleteOrder(this->now_account, num);
			break;
		}
	}
	if (pos == -1) {
		cout << "请检查要退票的航班号是否有误!\n";
		system("pause");
		return ;
	}

	// 修改余票
	vector<Flight> tmpVector; // 存储目前所有航班
	ifstream ifs;
	ifs.open("Flight.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "系统出现故障" << endl;
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
	int wh;
	if (level == "经济舱") {
		wh = 0;
	}
	else if (level == "商务舱") {
		wh = 1;
	}
	else {
		wh = 2;
	}

	for (int i = 0; i < tmpVector.size(); i++) {
		string flightNum = tmpVector[i].flightNum;
		if (flightNum == num) {
			tmpVector[i].ticket[wh].second ++;
			break;
		}
	}

	// 修改票务文件信息
	ofstream ofs;
	ofs.open("Flight.txt", ios::trunc);
	for (int i = 0; i < tmpVector.size(); i++) {
		manage.addOneFlight(tmpVector[i]);
	}
	ofs.close();
	
	cout << "退票成功, 已上传订单系统" << '\n';
	system("pause");
}