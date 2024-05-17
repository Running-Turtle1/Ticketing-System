#include "Manage.h"
#include "BasicFuction.h"
#include "Flight.h"
#include "System.h"

// ����Ա��¼
bool Manage::manageLogin() {
	if (this->loginSuccess) { // ֮ǰ�Ѿ��ɹ���¼��
		return true;
	}

	// ��¼����
	system("cls");
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***                         ��ӭ�������Ա��¼����		             ***" << endl;
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***                         << ��ȷ����Χ������ȫ >>		             ***" << endl;
	cout << "                 *******************************************************************************" << endl;

	// ��ȡ����Ա�˻���Ϣ
	ifstream ifs;
	ifs.open("ManageInfo.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ���ʧ��!" << endl;
		system("pause");
		return false;
	}

	pair<string, string> RightPassword;
	pair<string, string> LoginPassword;
	ifs >> RightPassword.first >> RightPassword.second;
	ifs.close();

	LoginPassword = LoginAccount(); // �洢��¼�˺�

	if (LoginPassword.first == RightPassword.first && LoginPassword.second == RightPassword.second) {
		this->loginSuccess = true;
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

// չʾ����Ա���ܲ˵�
void Manage::manageShowMenu() {
	system("cls");
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***                         ��ӭ�������Ա���ܽ���		             ***" << endl;
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***                  1. ���Ӻ���          2.ɾ������	  	    	     ***" << endl;
	cout << "                 ***                                                                         ***" << endl;
	cout << "                 ***                  3. �޸ĺ���          4.��ѯ����         	      	     ***" << endl;
	cout << "                 ***                                                                         ***" << endl;
	cout << "                 ***                           0. �������˵�     		             ***" << endl;
	cout << "                 *******************************************************************************" << endl;
}

// ʵ�ֹ���Ա����
void Manage::manageFuction() {
	while (true)
	{
		this->manageShowMenu();
		char opt;
		cin >> opt;
		switch (opt) {
			case '0': // �������˵�
				return;
				break;
			case '1': // ����º���
				this->addFlight();
				break;
			case '2': // ɾ������
				this->removeFlight();
				break;
			case '3': // �޸ĺ���
				this->changeFlight();
				break;
			case '4': // ��ѯ����
				this->queryFlight();
				break;
			default:
				cout << "���벻�Ϸ�\n";
				system("pause");
				break;
		}
	}
}

// ��ӵ������� (��ߴ��븴����)
void Manage::addOneFlight(Flight &flight) {
	ofstream ofs;
	ofs.open("Flight.txt", ios::out | ios::app);
	if (ofs.is_open() == false) {
		cout << "ϵͳ����ʱ���ֹ���" << endl;
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

// ����º���
void Manage::addFlight() {
	system("cls");
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***				  ��Ӻ���    				     ***" << endl;
	cout << "                 *******************************************************************************" << endl;
	auto askAndCheck = [&](Flight &flight) -> bool {
		if (checkTicket(flight) == false) { // ��д��Ϣ����
			// checkTicket ��������Դ�����Ϣ
			cout << "���ʧ�� !" << '\n';
		}
		else { // ��Ӻ�����Ϣ
			this->addOneFlight(flight);
			cout << "��ӳɹ�!" << '\n';
		}
		cout << "�Ƿ������� ? <�� �� ��>" << '\n';
		string opt;
		while (cin >> opt) {
			if (opt == "��") {
				return true;
			}
			else if (opt == "��") {
				return false;
			}
			else {
				cout << "���벻�Ϸ� !" << '\n';
			}
		}
	};
	Flight flight = Flight();
	do {
		cout << "������Ҫ��ӵĺ����: ";
		cin >> flight.flightNum;
		cout << "�����������: ";
		cin >> flight.startPosition;
		cout << "�����뽵���: ";
		cin >> flight.endPosotion;
		cout << "���������ʱ��: ";
		cin >> flight.startTime;
		cout << "�����뽵��ʱ��: ";
		cin >> flight.endTime;
		
		for (int i = 0; i < 3; i++) {
			if (i == 0) {
				cout << "�����뾭�ò���Ϣ: " << '\n';
			}
			else if (i == 1) {
				cout << "�������������Ϣ: " << '\n';
			}
			else {
				cout << "������ͷ�Ȳ���Ϣ: " << '\n';
			}
			cout << "Ʊ��: ";
			cin >> flight.ticket[i].first;
			cout << "Ʊ��: ";
			cin >> flight.ticket[i].second;
		}
	}
	while(askAndCheck(flight));
}

// ɾ������
void Manage::removeFlight() {
	// ��ʾɾ���������
	system("cls");
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***				  ɾ������    				     ***" << endl;
	cout << "                 *******************************************************************************" << endl;

	vector<Flight> tmpVector; // �洢Ŀǰ���к���
	ifstream ifs;
	ifs.open("Flight.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "ɾ��������ֹ���" << endl;
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
	cout << "��ѯ�����к��������: " << '\n';
	cout << "����: " << tmpVector.size() << "������" << '\n';
	for (auto& x : tmpVector) {
		cout << "�� " << ++ cnt << " ������ĺ����:" << ' ';
		cout << x.flightNum << '\n';
	}

	string removeNum;
	int pos = -1;
	bool hasFlight = false; 
	cout << "������Ҫɾ������ĺ����: ";
	cin >> removeNum;
	for (int i = 0; i < tmpVector.size(); i++) {
		string flightNum = tmpVector[i].flightNum;
		if (flightNum == removeNum) {
			hasFlight = true;
			pos = i;
			break;
		}
	}

	// �����ں�����
	if (hasFlight == false) {
		cout << "���಻���ڣ����������Ƿ�����" << '\n';
		system("pause");
		return ;
	}

	// ����ļ� , �������¼�ͼ���������Ϣ����д���ļ�
	ofstream ofs;
	ofs.open("Flight.txt", ios::trunc);
	for (int i = 0; i < tmpVector.size(); i++) {
		if(i == pos) continue;
		this->addOneFlight(tmpVector[i]);
	}
	ofs.close();

	cout << "ɾ�������Ϊ " << removeNum << " �ĺ���ɹ�" << '\n';
	system("pause");
}

// �޸ĺ���
void Manage::changeFlight() {
	/*
		����� ��ɵص� ����ص�
		���ʱ�� ����ʱ��
		����ʱ��
		Ʊ�� / Ʊ�� --> ���ò�, �����, ͷ�Ȳ�
	*/
	// ��ʾ�޸ĺ������
	system("cls");
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***				  �޸ĺ���    				     ***" << endl;
	cout << "                 *******************************************************************************" << endl;

	
	vector<Flight> tmpVector; // �洢Ŀǰ���к���
	ifstream ifs;
	ifs.open("Flight.txt", ios::in);
	if (ifs.is_open() == false) {
		cout << "�޸ĺ�����ֹ���" << endl;
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
	cout << "������Ҫ�޸ĺ���ĺ����: ";
	cin >> askNum;
	for (int i = 0; i < tmpVector.size(); i++) {
		string flightNum = tmpVector[i].flightNum;
		if (flightNum == askNum) {
			hasFlight = true;
			pos = i;
			break;
		}
	}

	// �����ں�����
	if (hasFlight == false) {
		cout << "���಻���ڣ����������Ƿ�����" << '\n';
		system("pause");
		return;
	}

	// ��ѯ��Ӧ������Ϣ
	for (int i = 0; i < tmpVector.size(); i++) {
		if (i != pos) continue;
		auto& [num, stP, edP, stTm, edTm, len, pr] = tmpVector[i];
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
		cout << "��Ҫ�޸ĵĺ����������: ";
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
	
	auto askContinue = []() {
		cout << "�Ƿ�����޸�������Ϣ" << '\n';
		cout << "1. �� ; 2. ��" << '\n';
		string opt;
		while (cin >> opt) {
			if (opt == "1") return true;
			else if (opt == "2") return false;
			else cout << "���벻�Ϸ�!" << '\n';
		}
	};

	do {
		// չʾ�޸�ѡ��
		cout << "������Ҫ�޸�ʲô��Ϣ ?" << '\n';
		cout << "1. �޸ĺ����" << '\n';
		cout << "2. �޸�ʼ����" << '\n';
		cout << "3. �޸�Ŀ�ĵ�" << '\n';
		cout << "4. �޸����ʱ��" << '\n';
		cout << "5. �޸Ľ���ʱ��" << '\n';
		cout << "6. �޸�Ʊ����Ϣ" << '\n';

		bool fg = true; // �Ƿ�ɹ��޸�
		string opt, info;
		cin >> opt;
		if (opt == "1") {
			cout << "�������µĺ����: ";
			cin >> info;
			tmpVector[pos].flightNum = info;
		}
		else if (opt == "2") {
			cout << "�������µ�ʼ����: ";
			cin >> info;
			tmpVector[pos].startPosition = info;
		}
		else if (opt == "3") {
			cout << "�������µ�Ŀ�ĵ�: ";
			cin >> info;
			tmpVector[pos].endPosotion = info;
		}
		else if (opt == "4") {
			cout << "�������µ�ʼ��ʱ��: ";
			cin >> info;
			string tmp = tmpVector[pos].startTime;
			tmpVector[pos].startTime = info;
			// ����������ʱ���Ƿ�Ϸ�
			if (checkTicket(tmpVector[pos]) == false) {
				cout << "������Ϣ���Ϸ� !" << '\n';
				tmpVector[pos].startTime = tmp;
				continue;
			}
		}
		else if (opt == "5") {
			cout << "�������µĽ���ʱ��: ";
			cin >> info;
			string tmp = tmpVector[pos].startTime;
			tmpVector[pos].endTime = info;
			// ����������ʱ���Ƿ�Ϸ�
			if (checkTicket(tmpVector[pos]) == false) {
				cout << "������Ϣ���Ϸ� !" << '\n';
				tmpVector[pos].startTime = tmp;
				continue;
			}
		}
		else if (opt == "6") {
			string num;
			cout << "��������Ҫ�޸�ʲô���͵Ļ�Ʊ ?" << '\n';
			cout << "1. ���ò�" << '\n';
			cout << "2. �����" << '\n';
			cout << "3. ͷ�Ȳ�" << '\n';
			while (cin >> num) {
				if (num == "1") {
					string ch;
					int info;
					cout << "���� 1 �޸�Ʊ�� ; ���� 2 �޸�Ʊ�� :";
					while (cin >> ch) {
						if (ch == "1") {
							cout << "��Ҫ��Ʊ���޸�Ϊ: ";
							cin >> info;
							tmpVector[pos].ticket[0].first = info;
							break;
						}
						else if (ch == "2") {
							cout << "��Ҫ��Ʊ���޸�Ϊ: ";
							cin >> info;
							tmpVector[pos].ticket[0].first = info;
							break;
						}
						else {
							cout << "���벻�Ϸ� !" << '\n';
						}
					}
					
					break;
				}
				else if (num == "2") {
					string ch;
					int info;
					cout << "���� 1 �޸�Ʊ�� ; ���� 2 �޸�Ʊ�� :";
					while (cin >> ch) {
						if (ch == "1") {
							cout << "��Ҫ��Ʊ���޸�Ϊ: ";
							cin >> info;
							tmpVector[pos].ticket[1].first = info;
							break;
						}
						else if (ch == "2") {
							cout << "��Ҫ��Ʊ���޸�Ϊ: ";
							cin >> info;
							tmpVector[pos].ticket[1].first = info;
							break;
						}
						else {
							cout << "���벻�Ϸ� !" << '\n';
						}
					}

					break;
				}
				else if (num == "3") {
					string ch;
					int info;
					cout << "���� 1 �޸�Ʊ�� ; ���� 2 �޸�Ʊ�� :";
					while (cin >> ch) {
						if (ch == "1") {
							cout << "��Ҫ��Ʊ���޸�Ϊ: ";
							cin >> info;
							tmpVector[pos].ticket[2].first = info;
							break;
						}
						else if (ch == "2") {
							cout << "��Ҫ��Ʊ���޸�Ϊ: ";
							cin >> info;
							tmpVector[pos].ticket[2].first = info;
							break;
						}
						else {
							cout << "���벻�Ϸ� !" << '\n';
						}
					}

					break;
				}
				else {
					cout << "���벻�Ϸ� !" << '\n';
				}
			}
		}
		else {
			fg = false;
			cout << "���벻�Ϸ� !" << '\n';
		}

		if (fg) {
			// ����ļ� , ��������Ϣд���ļ�
			ofstream ofs;
			ofs.open("Flight.txt", ios::trunc);
			for (int i = 0; i < tmpVector.size(); i++) {
				this->addOneFlight(tmpVector[i]);
			}
			ofs.close();


			cout << "�޸ĳɹ�, �޸ĺ�ĺ�����Ϣ����: " << '\n';
			auto& [num, stP, edP, stTm, edTm, len, pr] = tmpVector[pos];
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
			cout << "��Ҫ�޸ĵĺ����������: ";
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

			system("pause");
		}
	}
	while(askContinue());

	system("pause");

}

// ��ѯ����
void Manage::queryFlight() {
	// ��ѯ�������
	system("cls");
	cout << "                 *******************************************************************************" << endl;
	cout << "                 ***				  ��ѯ����    				     ***" << endl;
	cout << "                 *******************************************************************************" << endl;

	cout << "������Ҫ��ѯȫ�����໹�ǵ������� ?" << '\n';
	cout << "���� 1 ��ѯȫ������ ; ���� 2 ��ѯ��������" << '\n';
	string opt;
	while (cin >> opt) {
		if (opt == "1" || opt == "2") {
			if (opt == "1") {
				System tmp = System();
				tmp.lookAllFlight(); // ���� System.h �������ľ�̬��������ѯ���к���
			}
			else {
				vector<Flight> tmpVector; // �洢Ŀǰ���к���
				ifstream ifs;
				ifs.open("Flight.txt", ios::in);
				if (ifs.is_open() == false) {
					cout << "ɾ��������ֹ���" << endl;
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
				cout << "������Ҫ��ѯ����ĺ����: ";
				cin >> askNum;
				for (int i = 0; i < tmpVector.size(); i++) {
					string flightNum = tmpVector[i].flightNum;
					if (flightNum == askNum) {
						hasFlight = true;
						pos = i;
						break;
					}
				}

				// �����ں�����
				if (hasFlight == false) {
					cout << "���಻���ڣ����������Ƿ�����" << '\n';
					system("pause");
					return;
				}

				// ��ѯ��Ӧ������Ϣ
				for (int i = 0; i < tmpVector.size(); i ++ ){
					if(i != pos) continue; 
					auto& [num, stP, edP, stTm, edTm, len, pr] = tmpVector[i];
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
					cout << "��Ҫ��ѯ�ĺ����������: ";
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
			break;
		}
		else {
			cout << "���벻�Ϸ�, ������" << '\n';
		}
	}
}