#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// 定义一个 Employee 类来存储每个员工的信息
class Employee {
public:
    // 构造函数，用于初始化员工的 ID
    Employee(string id) {
        this->id = id;
    }

    // 记录签到时间
    void signIn(string time) {
        signInTime = time;
    }

    // 记录签退时间，并计算工作时长
    void signOut(string time) {
        signOutTime = time;
        // 计算工作时长
        int signInHour = stoi(signInTime.substr(11, 2));
        int signInMin = stoi(signInTime.substr(14, 2));
        int signOutHour = stoi(signOutTime.substr(11, 2));
        int signOutMin = stoi(signOutTime.substr(14, 2));
        int workTime = (signOutHour - signInHour) * 60 + (signOutMin - signInMin);
        // 如果工作时长超过 8 小时，则工作天数加 1
        if (workTime > 8 * 60) {
            overloadingDays++;
        }
        // 记录该天已经签到和签退
        string date = signInTime.substr(0, 10);
        if (signMap[date] == 0) {
            signMap[date] = 1;
        }
        else {
            signForgetDays++;
        }
    }

    // 打印该员工的信息，格式为 "id, #overloading_days, #sign_forget_days"
    void printInfo() {
        cout << id << ", " << overloadingDays << ", " << signForgetDays << endl;
    }

private:
    string id; // 员工 ID
    string signInTime; // 签到时间
    string signOutTime; // 签退时间
    int overloadingDays = 0; // 工作时长超过 8 小时的天数
    int signForgetDays = 0; // 忘记签到或签退的天数
    unordered_map<string, int> signMap; // 记录每天是否签到或签退的映射表
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " file_path" << endl;
        return 1;
    }

    string file_path = argv[1];

    ifstream file(file_path);
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        return 1;
    }

    unordered_map<string, Employee*> employeeMap; // 员工 ID 到 Employee* 的映射表
    string line;
    while (getline(file, line)) {
        // 将每一行按逗号分隔成三个部分
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1+1);
        string employeeId = line.substr(0, pos1);
        string signType = line.substr(pos1+1, pos2-pos

