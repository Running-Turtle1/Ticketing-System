#include "System.h"
#include "Flight.h"

// 展示功能菜单
void System::showMenu() {
    system("cls");
    cout << "                 **********************************************************************************" << endl;
    cout << "                 ***                           欢迎使用飞行订票系统		                ***" << endl;
    cout << "                 **********************************************************************************" << endl;
    cout << "                 ***  1. 订票系统                                       2. 浏览全部航班信息     ***" << endl;
    cout << "                 ***                                                                            ***" << endl;
    cout << "                 ***  3. 管理员系统                                     4. 用户注册             ***" << endl;
    cout << "                 ***                                                                            ***" << endl;
    cout << "                 ***  5. 旅行规划                                       6. 订单系统             ***" << endl;
    cout << "                 ***                                                                            ***" << endl;
    cout << "                 ***  7. 乘坐须知                                       8. 退出系统             ***" << endl;
    cout << "                 **********************************************************************************" << endl;
}

// 联系客服功能
void System::contactService() {
    system("cls");
    
    system("pause");
}

// 乘坐须知
void System::ridingInstructions() {
    system("cls");
    // 打印乘坐须知
    cout << "******************************************************************************" << '\n';
    cout << "*                                 乘坐须知                                   *" << '\n';
    cout << "******************************************************************************" << '\n';
    cout << "* 1. 请提前到达机场，办理登机手续。                                          *" << '\n';
    cout << "* 2. 请携带有效证件，如身份证或护照。                                        *" << '\n';
    cout << "* 3. 在登机过程中，请遵循机场和航空公司的安全规定和要求。                    *" << '\n';
    cout << "* 4. 如有特殊需求（如餐饮、座位、残疾人服务等），请提前联系航空公司或旅行社。*" << '\n';
    cout << "* 5. 如遇紧急情况，请听从机组人员的指示并配合他们的工作。                    *" << '\n';
    cout << "* 6. 不要携带违禁品和易燃易爆物品上飞机。                                    *" << '\n';
    cout << "* 7. 请在起飞前关闭手机等电子设备。                                          *" << '\n';
    cout << "* 8. 请注意保管好您的随身行李，避免丢失或遗弃。                              *" << '\n';
    cout << "* 9. 请在座位上系好安全带，尽量避免起飞和降落时走动。                        *" << '\n';
    cout << "* 10. 如有晕机或不适，请及时告知机组人员。                                   *" << '\n';
    cout << "* 11. 请勿在飞机上吸烟。                                                     *" << '\n';
    cout << "* 12. 请遵守机舱内的安静规定，尊重他人的休息。                               *" << '\n';
    cout << "* 13. 在飞行过程中请勿打开安全门。                                           *" << '\n';
    cout << "* 14. 如需更改航班或退票，请提前联系航空公司或旅行社。                       *" << '\n';
    cout << "* 15. 到达目的地后，请遵循机场的出站流程。                                   *" << '\n';
    cout << "******************************************************************************" << '\n';
    // 显示客服联系方式
    cout << "*                                 联系客服                                   *" << '\n';
    cout << "******************************************************************************" << '\n';
    cout << "* 电话：123-456-7890                                                         *" << '\n';
    cout << "* 邮箱：Aviation@163.com                                                     *" << '\n';
    cout << "* 在线客服：请访问 fly.com 获取在线客服支持                                  *" << '\n';
    cout << "* 客服投诉电话: 198-6223-9750                                                *" << '\n';
    cout << "* 我们竭诚为您服务!                                                          *" << '\n';
    cout << "******************************************************************************" << '\n';
    cout << "祝您旅途愉快 ！" << '\n';
    system("pause");
}

// 查询所有航班
void System::lookAllFlight() {
    system("cls");
    cout << "*******************************************************************************" << endl;
    cout << "***				  全部航班    				    ***" << endl;
    cout << "*******************************************************************************" << endl;


    // 存储目前所有航班
    vector<Flight> tmpVector;
    ifstream ifs;
    ifs.open("Flight.txt", ios::in);
    if (ifs.is_open() == false) {
        cout << "删除航班出现故障" << endl;
        system("pause");
        system("cls");
        return;
    }
    Flight tmp;
    while (ifs >> tmp.flightNum >> tmp.startPosition >> tmp.endPosotion) {
        ifs >> tmp.startTime >> tmp.endTime;
        ifs >> tmp.flyTime;
        for (int i = 0; i < 3; i++) {
            ifs >> tmp.ticket[i].first >> tmp.ticket[i].second;
        }
        tmpVector.push_back(tmp);
    }
    ifs.close();

    if (tmpVector.size() == 0) {
        cout << "当前并未导入任何航班!" << '\n';
        system("pause");
        return;
    }

    // 输出全部航班信息
    int cnt = 0;
    for (auto& flight : tmpVector) {
        auto &[num, stP, edP, stTm, edTm, len,  pr] = flight;
        string toStringpr[3][2]; // 将 {票价 余票} 信息用 string 形式存储
        for (int i = 0; i < 3; i++) { // 将长度小于 4 的左边加空格补齐到 4, 美化输出格式
            toStringpr[i][0] = to_string(pr[i].first);
            toStringpr[i][1] = to_string(pr[i].second);
            if (toStringpr[i][0].size() == 3) toStringpr[i][0] = ' ' + toStringpr[i][0];
            else if (toStringpr[i][0].size() == 2) toStringpr[i][0] = "  " + toStringpr[i][0];
            if (toStringpr[i][1].size() == 3) toStringpr[i][1] = ' ' + toStringpr[i][1];
            else if (toStringpr[i][1].size() == 2) toStringpr[i][1] = "  " + toStringpr[i][1];
        }
        cout << '\n';
        cout << "第 " << ++ cnt << " 所航班情况如下: ";
        cout << "航班号: " << num << '\n';
        cout << "起落位置: " << stP << "--->" << edP << '\n';
        cout << "起始时间: " << stTm << '\n';
        cout << "降落时间: " << edTm << '\n';
        cout << "飞行时长: " << len << "min" << '\n';
        cout << "机票情况如下: " << '\n';
        cout << "经济舱 : " << "{ 价格: " << toStringpr[0][0] << " ; " << "余票: " << toStringpr[0][1] << " }" << '\n';
        cout << "商务舱 : " << "{ 价格: " << toStringpr[1][0] << " ; " << "余票: " << toStringpr[1][1] << " }" << '\n';
        cout << "头等舱 : " << "{ 价格: " << toStringpr[2][0] << " ; " << "余票: " << toStringpr[2][1] << " }" << '\n';
        cout << '\n';
    }

    system("pause");
}
