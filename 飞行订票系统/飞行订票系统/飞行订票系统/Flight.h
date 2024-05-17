#pragma once
#include <bits/stdc++.h>
using namespace std;

// 机票信息
class Flight {
	public :
		string flightNum; // 航班号
		string startPosition, endPosotion; // 出发地 / 目的地
		string startTime, endTime; // 起飞时间 / 降落时间
		int flyTime; // 飞行时间 (min)
		pair<int, int> ticket[3]; // {经济舱+商务舱+头等舱} : 票价 / 剩余票数
};

// 检查日期是否合法 (目前默认只有 2024年的航班)
bool checkDay(Flight& flight);

// 计算航班的飞行时间
int calFlyTime(Flight& flight);

// 检查机票信息是否合法 (用于添加航班和修改航班时使用), 并自动计算航班飞行时间
bool checkTicket(Flight &flight);
