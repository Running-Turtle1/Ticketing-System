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
			case '1': // ��Ʊϵͳ
				if (user.userLogin() == true) { // �û���¼�ɹ�
					user.bookTicketFuction();
				}
				break;
			case '2': // ���ȫ��������Ϣ
				sym.lookAllFlight();
				break;
			case '3': // ����Ա��¼
				if (manage.manageLogin()) {
					// ��¼�ɹ�, �������Ա���ܲ˵�
					manage.manageFuction();
				}
				break;
			case '4': // �û�ע��
				user.userRegistration();
				break;
			case '5': // ���й滮
				plan.planFuction();
				break;
			case '6': // ����ϵͳ
				order.OrderFuction();
				break;
			case '7': // ������֪  
				sym.ridingInstructions();
				break;
			case '8': // �˳�ϵͳ
				cout << "��лʹ��" << endl;
				exit(0);
				break;
			default:
				cout << "���벻�Ϸ�\n";
				system("pause");
				break;
		}
	}

	return 0;
}