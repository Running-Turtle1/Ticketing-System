#pragma once
#include<bits/stdc++.h>
using namespace std;

class Order {
	public :
		// ��ʾ��������
		void showOrderMenu();

		// ����ϵͳ
		void OrderFuction();

		// ��ѯ���ж���
		void queryAllOrder();

		// ��ѯ��Ӧ�˺ŵĶ�Ӧ����
		void queryOrderByAccount();
		vector<string> queryOrderByAccount2(string account);

		// д�붩��
		void addOrder(string p, string num, string lv);

		//ɾ���˺� a �ĺ����Ϊ b �Ķ���
		void deleteOrder(string a, string b);
};

