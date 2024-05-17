#include "User.h"
#include "BasicFuction.h"
#include "System.h"
#include "Flight.h"
#include "Manage.h"
#include "order.h"

// �û�ע�Ṧ��
void User::userRegistration() {
	system("cls");
	// ��ʾע�����
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***				  �û�ע��    				     ***" << endl;
	cout << "                 *******************************************************************************" << endl;
	
	pair<string, string> account = LoginAccount(); // ��ȡ�˺�����
	
	// �ж��˺��Ƿ��Ѿ���ע���
	ifstream ifs;
	ifs.open("User.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "ע��ϵͳ����, ���Ժ�����" << endl;
		system("pause");
		return;
	}

	string tmpString;
	while (ifs >> tmpString) {
		if (tmpString == account.first) {
			cout << '\n';
			cout << "���˺��Ѿ���ע���, ������˺ź�ע��" << endl;
			system("pause");
			ifs.close();
			return;
		}
		ifs >> tmpString; // ���˵�����
	}
	ifs.close();

	// �ٴ���������, ȷ�����������Ƿ�һ��
	cout << '\n';
	tmpString = getPassword(0);
	if (tmpString != account.second) {
		cout << "������������벻һ��!" << endl;
		cout << "�����½���ע�� " << endl;
		system("pause");
		return;
	}

	// ע��ɹ�, �򿪴���û�ע����Ϣ���ļ�, ��д�����û���Ϣ
	ofstream ofs;
	ofs.open("User.txt", ios::out | ios::app);
	if (ofs.is_open() == false) { // ���ļ�ʧ��
		cout << "ע��ϵͳ����, ���Ժ�����" << endl;
		system("pause");
		return;
	}
	ofs << account.first << ' ' << account.second << endl;
	ofs.close();
	cout << '\n';
	cout << "[ע��ɹ�]" << endl;

	system("pause");
}

void User::showBookTicketMenu() {
	// չʾ���ܲ˵�
	system("cls");
	cout << "                 **********************************************************************************" << endl;
	cout << "                 ***                           ��ӭʹ�ö�Ʊϵͳ    		                ***" << endl;
	cout << "                 **********************************************************************************" << endl;
	cout << "                 ***  1. ���Ϲ�Ʊ                                       2. ������Ʊ             ***" << endl;
	cout << "                 ***                                                                            ***" << endl;
	cout << "                 ***  0. �������˵�							        ***" << endl;
	cout << "                 **********************************************************************************" << endl;
}

// ʵ����Ʊ����
void User::bookTicketFuction() {
	while (true)
	{
		this->showBookTicketMenu();
		char opt;
		cin >> opt;
		switch (opt) {
			case '0': // �������˵�
				return;
				break;
			case '1': // ���Ϲ�Ʊ
				this->buyTicket();
				break;
			case '2': // ������Ʊ
				this->refundTicket();
				break;
			default:
				cout << "���벻�Ϸ�\n";
				system("pause");
				break;
		}
	}
}

// �û���¼����
bool User::userLogin() {
	// ��¼����
	system("cls");
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***                            ��ӭ�����¼����          		     ***" << endl;
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***                         << ��ȷ����Χ������ȫ >>		             ***" << endl;
	cout << "                 *******************************************************************************" << endl;

	// ��ȡ�û��˻���Ϣ
	ifstream ifs;
	ifs.open("User.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ���ʧ��!" << endl;
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

	pair<string ,string> LoginInfo = LoginAccount(); // �洢��¼�˺�
	bool find_flag = false;

	for (auto& [a, b] : info) {
		if (a == LoginInfo.first && b == LoginInfo.second) {
			find_flag = true;
			break;
		}
	}

	if (find_flag) {
		this->now_account = LoginInfo.first; // �洢Ŀǰ��¼���û�
		cout << '\n';
		cout << "��¼�ɹ�" << '\n';
		system("pause");
		return true;
	}
	else {
		cout << '\n';
		cout << "��¼ʧ��" << '\n';
		system("pause");
		return false;
	}
}

// �û���Ʊ���� (ͬʱ��������ϵͳ)
void User::buyTicket() {
	System sys;
	Manage manage;
	Order order;

	// �������û�չʾ���еĺ�����Ϣ
	system("cls");
	sys.lookAllFlight();

	// �û�ѡ�񺽰���Լ�ʲô��λ
	system("cls");
	string num, level;
	cout << "��ѡ�񺽰��: ";
	cin >> num;
	cout << "��ѡ���λ(ͷ�Ȳա�����ա����ò�): ";
	cin >> level;

	if (level != "���ò�" && level != "�����" && level != "ͷ�Ȳ�") {
		cout << "��λѡ�����" << '\n';
		system("pause");
		return;
	}

	// ��ʱ�洢���к���
	vector<Flight> tmpVector; // �洢Ŀǰ���к���
	ifstream ifs;
	ifs.open("Flight.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "ϵͳ���ֹ���" << endl;
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

	// ��ѯ�û�������Ϣ�Ƿ���ȷ
	bool hasFlight = false;
	int pos; // ��Ӧλ��
	for (int i = 0; i < tmpVector.size(); i++) {
		string flightNum = tmpVector[i].flightNum;
		if (flightNum == num) {
			hasFlight = true;
			pos = i;
			break;
		}
	}

	if (hasFlight == false) { // �����ں�����
		cout << "���಻���ڣ����������Ƿ�����" << '\n';
		system("pause");
		return;
	}

	// �޸���Ʊ
	int wh;
	if (level == "���ò�") {
		wh = 0;
	}
	else if (level == "�����") {
		wh = 1;
	}
	else {
		wh = 2;
	}
	tmpVector[pos].ticket[wh].second --;

	// �޸�Ʊ���ļ���Ϣ
	ofstream ofs;
	ofs.open("Flight.txt", ios::trunc);
	for (int i = 0; i < tmpVector.size(); i++) {
		manage.addOneFlight(tmpVector[i]);
	}
	ofs.close();

	// ʹ�ö���ϵͳ�洢������Ϣ
	order.addOrder(this->now_account, num, level);
	cout << "��Ʊ�ɹ�, ���ϴ�����ϵͳ" << '\n';
	system("pause");
}

// �û���Ʊ���� (ͬʱ��������ϵͳ)
void User::refundTicket() {
	System sys;
	Manage manage;
	Order order;

	// ʹ�ö���ϵͳչʾ��λ�û���ȫ��������Ϣ
	system("cls");
	cout << "��Ŀǰ�Ķ�Ʊ�������: " << '\n';
	vector<string> vc = order.queryOrderByAccount2(this->now_account);

	// ѯ���û�Ҫ�˵���Ʊ��Ӧ�ĺ����
	string num;
	cout << "�������Ҫ��Ʊ�ĺ����: ";
	cin >> num;


	// ���ö���ϵͳɾ����Ӧ����
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
		cout << "����Ҫ��Ʊ�ĺ�����Ƿ�����!\n";
		system("pause");
		return ;
	}

	// �޸���Ʊ
	vector<Flight> tmpVector; // �洢Ŀǰ���к���
	ifstream ifs;
	ifs.open("Flight.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "ϵͳ���ֹ���" << endl;
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
	if (level == "���ò�") {
		wh = 0;
	}
	else if (level == "�����") {
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

	// �޸�Ʊ���ļ���Ϣ
	ofstream ofs;
	ofs.open("Flight.txt", ios::trunc);
	for (int i = 0; i < tmpVector.size(); i++) {
		manage.addOneFlight(tmpVector[i]);
	}
	ofs.close();
	
	cout << "��Ʊ�ɹ�, ���ϴ�����ϵͳ" << '\n';
	system("pause");
}