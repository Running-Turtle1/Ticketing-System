#pragma once
#include <bits/stdc++.h>
using namespace std;

// ��Ʊ��Ϣ
class Flight {
	public :
		string flightNum; // �����
		string startPosition, endPosotion; // ������ / Ŀ�ĵ�
		string startTime, endTime; // ���ʱ�� / ����ʱ��
		int flyTime; // ����ʱ�� (min)
		pair<int, int> ticket[3]; // {���ò�+�����+ͷ�Ȳ�} : Ʊ�� / ʣ��Ʊ��
};

// ��������Ƿ�Ϸ� (ĿǰĬ��ֻ�� 2024��ĺ���)
bool checkDay(Flight& flight);

// ���㺽��ķ���ʱ��
int calFlyTime(Flight& flight);

// ����Ʊ��Ϣ�Ƿ�Ϸ� (������Ӻ�����޸ĺ���ʱʹ��), ���Զ����㺽�����ʱ��
bool checkTicket(Flight &flight);
