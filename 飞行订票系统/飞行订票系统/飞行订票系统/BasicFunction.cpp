#include "BasicFuction.h"

// 输入密码， 并对隐私做保护
string getPassword() {
	int i = 0;
	char tmp[20] = { '\0' };
	cout << "请输入密码: ";
	while (i < 15 && (tmp[i] = _getch()) && tmp[i] != '\r') { // 保护登陆者隐私, 将输入的密码隐藏
		cout << "*";
		i++;
	}
	tmp[i] = '\0'; // 字符串结尾标志
	string password(tmp);

	return password;
}

// 输入密码， 并对隐私做保护
string getPassword(int fg) {
	int i = 0;
	char tmp[20] = { '\0' };
	cout << "请再次输入密码: ";
	while (i < 15 && (tmp[i] = _getch()) && tmp[i] != '\r') { // 保护登陆者隐私, 将输入的密码隐藏
		cout << "*";
		i++;
	}
	tmp[i] = '\0'; // 字符串结尾标志
	string password(tmp);

	return password;
}

// 获取一次登录请求，二元组形式返回用户输入的账号和密码
pair< string, string>  LoginAccount() {
	string account;
	cout << "请输入账号: ";
	cin >> account;
	
	string password = getPassword();

	return make_pair(account, password);
}