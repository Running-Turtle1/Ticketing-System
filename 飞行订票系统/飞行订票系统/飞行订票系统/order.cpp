#include "order.h"

// ��ʾ��������
void Order::showOrderMenu() {
	// չʾ���ܲ˵�
	system("cls");
	cout << "                 **********************************************************************************" << endl;
	cout << "                 ***                           ��ӭʹ�ö���ϵͳ    		                ***" << endl;
	cout << "                 **********************************************************************************" << endl;
	cout << "                 ***  1. �鿴���ж���                               2. �鿴ָ������             ***" << endl;
	cout << "                 ***                                                                            ***" << endl;
	cout << "                 ***  0. �������˵�							        ***" << endl;
	cout << "                 **********************************************************************************" << endl;
}

// ����ϵͳ
void Order::OrderFuction() {
	while (true)
	{
		this->showOrderMenu();
		char opt;
		cin >> opt;
		switch (opt) {
			case '0': // �������˵�
				return;
				break;
			case '1': // �鿴���ж���
				this->queryAllOrder();
				break;
			case '2': // �鿴ָ������
				this->queryOrderByAccount();
				break;
			default:
				cout << "���벻�Ϸ�\n";
				system("pause");
				break;
		}
	}
}

// ��ѯ���ж���
void Order::queryAllOrder() {
    system("cls");
    cout << "*******************************************************************************" << endl;
    cout << "***				  ȫ������    				    ***" << endl;
    cout << "*******************************************************************************" << endl;


    ifstream ifs;
    ifs.open("Order.txt", ios::in);
    if (ifs.is_open() == false) {
        cout << "ɾ��������ֹ���" << endl;
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

// ��ѯ��Ӧ�˺ŵĶ�Ӧ����
void Order::queryOrderByAccount() {
	system("cls");

	ifstream ifs;
	ifs.open("Order.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "ɾ��������ֹ���" << endl;
		system("pause");
		system("cls");
		return;
	}

	string account;
	cout << "������Ҫ��ѯ�ĸ��˺ŵĶ���: ";
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
		cout << "δ��ѯ���κζ���!" << '\n';
	}

	system("pause");
}

// ��ѯ��Ӧ�˺ŵĶ�Ӧ����
vector<string> Order::queryOrderByAccount2(string account) {
	system("cls");

	ifstream ifs;
	ifs.open("Order.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "ɾ��������ֹ���" << endl;
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

// ��Ӷ���
void Order::addOrder(string p, string num, string lv) {
	ofstream ofs;
	ofs.open("order.txt", ios::out | ios::app);
	if (ofs.is_open() == false) {
		cout << "ϵͳ����ʱ���ֹ���" << endl;
		system("pause");
		system("cls");
		return;
	}

	ofs << p << ' ' << num << ' ' << lv << '\n';

	ofs.close();
}

//ɾ���˺� a �ĺ����Ϊ b �Ķ��� (��Ʊʱʹ��)
void Order::deleteOrder(string a, string b) {

	vector<string> tmpVector; // �洢Ŀǰ���ж���
	ifstream ifs;
	ifs.open("Order.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "ϵͳ���ֹ���" << endl;
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

	// ����ļ� , �������¼�ͼ���������Ϣ����д���ļ�
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