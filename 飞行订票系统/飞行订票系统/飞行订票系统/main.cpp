#include "System.h"
#include "Manage.h"
#include "User.h"
#include "order.h"
#include "Plan.h"
using namespace std;

int main() {
	System sym = System();
	Manage manage = Manage();
	User user = User();
	Order order = Order();
	Plan plan = Plan();

	while (true) {
		char opt;
		sym.showMenu();
		cin >> opt;
		switch (opt) {
			case '1': // 订票系统
				if (user.userLogin() == true) { // 用户登录成功
					user.bookTicketFuction();
				}
				break;
			case '2': // 浏览全部航班信息
				sym.lookAllFlight();
				break;
			case '3': // 管理员登录
				if (manage.manageLogin()) {
					// 登录成功, 进入管理员功能菜单
					manage.manageFuction();
				}
				break;
			case '4': // 用户注册
				user.userRegistration();
				break;
			case '5': // 旅行规划
				plan.planFuction();
				break;
			case '6': // 订单系统
				order.OrderFuction();
				break;
			case '7': // 乘坐须知  
				sym.ridingInstructions();
				break;
			case '8': // 退出系统
				cout << "感谢使用" << endl;
				exit(0);
				break;
			default:
				cout << "输入不合法\n";
				system("pause");
				break;
		}
	}

	return 0;
}