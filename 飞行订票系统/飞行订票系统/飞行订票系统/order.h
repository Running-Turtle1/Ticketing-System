#pragma once
#include<bits/stdc++.h>
using namespace std;

class Order {
	public :
		// 显示订单界面
		void showOrderMenu();

		// 订单系统
		void OrderFuction();

		// 查询所有订单
		void queryAllOrder();

		// 查询对应账号的对应订单
		void queryOrderByAccount();
		vector<string> queryOrderByAccount2(string account);

		// 写入订单
		void addOrder(string p, string num, string lv);

		//删除账号 a 的航班号为 b 的订单
		void deleteOrder(string a, string b);
};

