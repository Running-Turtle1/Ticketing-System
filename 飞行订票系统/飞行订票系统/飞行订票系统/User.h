#pragma once
#include<bits/stdc++.h>
using namespace std;

class User {
	public :
		// 用户注册功能
		void userRegistration();

		// 显示购票界面
		void showBookTicketMenu();

		// 购票买票系统
		void bookTicketFuction();

		// 用户登录功能 : 用于进入买票系统
		bool userLogin();

		// 用户购票功能 (同时联动订单系统)
		void buyTicket();

		// 用户退票功能 (同时联动订单系统)
		void refundTicket();

		string now_account; // 现在正在登录的用户
};

