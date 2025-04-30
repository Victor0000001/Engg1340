#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include <string>
#include <vector>
using namespace std;

// 玩家结构
struct Player {
    string username; // 用户名
    string password; // 密码
    int atk; // 攻击力
    int hp; // 当前生命值
    int max_hp; // 最大生命值
    int currency; // 宇宙货币
    int storage; // 存储空间
    string difficulty; // 难度级别
    vector<string> inventory; // 背包
    vector<string> equipment; // 装备
    vector<string> energies; // 收集的能源
    bool autoLogin; // 注册后自动登录
    bool isGameComplete;
};

// 函数声明
void initializeUser(Player& player, string username, string password, string difficulty);//初始化玩家
void registerUser(Player& player);//注册
bool login(Player& player);//登录
void saveGame(const Player& player);//保存数据
void loadGame(Player& player);//加载数据
bool usernameExists(const string& username);//判断用户名是否存在

#endif
