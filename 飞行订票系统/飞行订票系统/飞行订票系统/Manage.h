#pragma once
#include<bits/stdc++.h>
#include "Flight.h"
using namespace std;

class Manage {
	public :
		bool loginSuccess = false; // 是否已经登录成功过

		bool manageLogin(); // 管理员登录

		void manageShowMenu(); // 管理员功能菜单

		void manageFuction(); // 实现管理员功能

		/** 管理员功能如下 **/
		
		// 添加单个航班 (提高代码复用率)
		void addOneFlight(Flight& flight);

		// 添加新航班
		void addFlight();

		// 删除航班
		void removeFlight();

		// 修改航班
		void changeFlight();

		// 查询航班
		void queryFlight();
};