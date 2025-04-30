#ifndef GAME_MECHANICS_H
#define GAME_MECHANICS_H

#include <string>
#include <vector>
#include "user_management.h"
using namespace std;

// 星球结构体
struct Planet {
    string name; // 星球名称
    vector<string> resources; // 可采集资源
    string combat_item; // 战斗掉落物
    vector<pair<string, int>> tasks; // 任务列表（物品，数量）
    string background; // 星球背景
    string effect; // 星球效果
    bool isTaskDone;
};

// 函数声明
void collectResources(Player& player, Planet& planet);//收集
void combat(Player& player, Planet& planet);//战斗
void showTasks(const Planet& planet, Player& player);//展示任务
bool checkTasksCompleted(const Planet& planet, const Player& player);//判断任务是否完成
void initializePlanets(vector<Planet>& planets);//初始化星球数据
void shop(Player& player, const Planet& planet);//商店
void displayMenu();//展示菜单
void displayCombatRules();//展示战斗规则
void displayRules();//展示所有规则
void displayPlanetBackground(const Planet& planet);//展示星球背景
void typeText(const string& text, int msPerChar);//打字效果

#endif
