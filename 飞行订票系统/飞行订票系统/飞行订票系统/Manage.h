#pragma once
#include<bits/stdc++.h>
#include "Flight.h"
using namespace std;

class Manage {
	public :
		bool loginSuccess = false; // �Ƿ��Ѿ���¼�ɹ���

		bool manageLogin(); // ����Ա��¼

		void manageShowMenu(); // ����Ա���ܲ˵�

		void manageFuction(); // ʵ�ֹ���Ա����

		/** ����Ա�������� **/
		
		// ��ӵ������� (��ߴ��븴����)
		void addOneFlight(Flight& flight);

		// ����º���
		void addFlight();

		// ɾ������
		void removeFlight();

		// �޸ĺ���
		void changeFlight();

		// ��ѯ����
		void queryFlight();
};