#include "Flight.h"

// 计算航班的飞行时间
int calFlyTime(Flight& flight) {
	// 格式 : 2024-05-10-08:00 2024-05-10-16:00 
	string s1 = flight.startTime;
	string s2 = flight.endTime;
	int day1 = (s1[8] - '0') * 10 + (s1[9] - '0');
	int day2 = (s2[8] - '0') * 10 + (s2[9] - '0');
	int hour1 = (s1[11] - '0') * 10 + (s1[12] - '0');
	int hour2 = (s2[11] - '0') * 10 + (s2[12] - '0');
	int minute1 = (s1[14] - '0') * 10 + (s1[15] - '0');
	int minute2 = (s2[14] - '0') * 10 + (s2[15] - '0');
	int res = (day2 - day1) * 24 * 60 + (hour2 - hour1) * 60 + (minute2 - minute1);
	return res;
}

// 检查日期是否存在
bool checkDay(Flight &flight) {
	int daysInMonth[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	string s1 = flight.startTime;
	string s2 = flight.endTime;
	int month1 = (s1[5] - '0') * 10 + (s1[6] - '0');
	int month2 = (s2[5] - '0') * 10 + (s2[6] - '0');
	int day1 = (s1[8] - '0') * 10 + (s1[9] - '0');
	int day2 = (s2[8] - '0') * 10 + (s2[9] - '0');
	
	auto check1 = [](int m) {
		if(m < 1 || m > 12) return false;
		return true;
	};

	auto check2 = [&](int m, int d) {
		if (d >= 1 && d <= daysInMonth[m - 1]) {
			return true;
		}
		return false;
	};

	if (!check1(month1) || !check1(month2) || !check2(month1, day1) || !check2(month2, day2) ) {
		return false;
	}
	return true;
}

// 检查机票信息是否合法 (用于添加航班和修改航班时使用)
bool checkTicket(Flight& flight) {
	if (flight.startTime.size() != 16 || flight.endTime.size() != 16) {
		cout << "日期长度不合法!" << '\n';
		return false;
	}

	// 日期长度合法，接下来检查起飞时间是否 <= 降落时间

	flight.flyTime = calFlyTime(flight);
	if (flight.flyTime < 0) {
		cout << "输入不合法, 错误类型 : 起飞时间 > 降落时间" << '\n';
		return false;
	}

	// 日期长度合法, 起飞时间 < 降落时间, 接下来检查日期是否存在

	if (checkDay(flight) == false) {
		cout << "日期输入不合法, 请检查后重新添加" << '\n';
		return false;
	}

	return true; // 回头再写
}