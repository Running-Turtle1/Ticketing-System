#pragma once
#include<bits/stdc++.h>
using namespace std;

class User {
	public :
		// �û�ע�Ṧ��
		void userRegistration();

		// ��ʾ��Ʊ����
		void showBookTicketMenu();

		// ��Ʊ��Ʊϵͳ
		void bookTicketFuction();

		// �û���¼���� : ���ڽ�����Ʊϵͳ
		bool userLogin();

		// �û���Ʊ���� (ͬʱ��������ϵͳ)
		void buyTicket();

		// �û���Ʊ���� (ͬʱ��������ϵͳ)
		void refundTicket();

		string now_account; // �������ڵ�¼���û�
};

