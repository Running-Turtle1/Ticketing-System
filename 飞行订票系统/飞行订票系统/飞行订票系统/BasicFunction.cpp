#include "BasicFuction.h"

// �������룬 ������˽������
string getPassword() {
	int i = 0;
	char tmp[20] = { '\0' };
	cout << "����������: ";
	while (i < 15 && (tmp[i] = _getch()) && tmp[i] != '\r') { // ������½����˽, ���������������
		cout << "*";
		i++;
	}
	tmp[i] = '\0'; // �ַ�����β��־
	string password(tmp);

	return password;
}

// �������룬 ������˽������
string getPassword(int fg) {
	int i = 0;
	char tmp[20] = { '\0' };
	cout << "���ٴ���������: ";
	while (i < 15 && (tmp[i] = _getch()) && tmp[i] != '\r') { // ������½����˽, ���������������
		cout << "*";
		i++;
	}
	tmp[i] = '\0'; // �ַ�����β��־
	string password(tmp);

	return password;
}

// ��ȡһ�ε�¼���󣬶�Ԫ����ʽ�����û�������˺ź�����
pair< string, string>  LoginAccount() {
	string account;
	cout << "�������˺�: ";
	cin >> account;
	
	string password = getPassword();

	return make_pair(account, password);
}