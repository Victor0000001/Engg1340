#include <iostream>
#include <algorithm>
#include <locale>
#include <thread>
#include <chrono>
#include <cstdio>
#include "user_management.h"
#include "game_mechanics.h"
using namespace std;

// 主函数，游戏入口
int main() {
    setlocale(LC_ALL, "en_US.UTF-8"); // 设置 UTF-8 编码
    srand(time(0)); // 初始化随机种子

    // 显示标题
    cout << "\n=========================================\n";
    cout << "              星际能源探秘              \n";
    cout << "=========================================\n";
    cout << "按 Enter 键开始游戏...\n";
    cin.get();

    Player player;
    vector<Planet> planets;
    initializePlanets(planets); // 初始化星球数据

    cout << "1. 注册\n2. 登录\n3. 退出\n";
    string choice;
    getline(cin, choice);

    bool isRegister=false;
    if (choice == "1") {
        registerUser(player); // 用户注册
        if (player.autoLogin) {
            cout << "注册成功，自动登录！\n";
        } else {
            cout << "请登录。\n";
            if (!login(player)) return 1;
        }
	isRegister=true;
    } 
    else if (choice == "2") {
        if (!login(player)) return 1; // 用户登录
    } else {
        return 0;
    }
    
    // 判断该玩家有没有完成游戏
    if (player.isGameComplete) {
        string restartRequest = "You have completed the game.\n"
	                        "Would you like to restart? (y/n)\n";
        typeText(restartRequest, 50);
	while (true) {
            string select;
	    getline(cin,select);
	    // 询问玩家是否重新游玩
	    if ((select == "y") || (select == "Y")) {
                break;
	    } else if ((select == "n") || (select == "N")) {
	        cout << "Game exits.\n";
                return 0;
	    } else {
                cout << "无效输入\n";
		cout << "\n";
		cout << "Would you like to restart? (y/n)\n";
	    }
	}
	// 如果重来，重新选择难度
	typeText("You can choose the difficulty again.\n", 50);
	string difficulty;
	while (true) {
            cout << "选择难度 (easy/medium/hard)：";
            getline(cin,difficulty);
            if (difficulty != "easy" && difficulty != "medium" && difficulty != "hard") {
                cout << "无效难度，请重新选择。\n";
                continue;
            }
            break;
        }
	// 如果重来，重新设置玩家初始数据
	initializeUser(player, player.username, player.password, difficulty);
	remove((player.username + "_inventory.txt").c_str());
        loadGame(player);
        isRegister=true;
    }
    
    //开始游戏
    typeText("Game begins!\n",50);
    cout << "\n";

    // 首次游玩，展示背景故事
    if (isRegister) {
        string backstory = "公元2378年，地球能源枯竭，人类面临灭顶之灾。\n"
                           "你是一名星际探险者，肩负着寻找四种神秘能源的使命。\n"
                           "这些能源散落在宇宙的四个星球：Sylvaris、Glaciora、\n"
                           "Pyroterra 和 Desolara。\n"
                           "只有集齐所有能源，才能合成无尽能源，拯救地球！\n"
                           "准备好，你的星际之旅即将开始...\n";
        typeText(backstory, 50);
    }

    while (true) {
        displayMenu(); // 显示主菜单
        getline(cin, choice);

        if (choice == "1") {
            // 按序解锁星球
            cout << "可前往的星球：\n";
            int unlocked = player.energies.size() + 1; // 解锁的星球数
	    // 展示可选择星球
            for (int i = 0; i < min(unlocked, (int)planets.size()); i++) {
                cout << i + 1 << ". " << planets[i].name << endl;
            }
            string planetChoice;
            getline(cin, planetChoice);
            int idx = stoi(planetChoice) - 1;
            if (idx >= 0 && idx < unlocked && idx < planets.size()) {
                Planet& currentPlanet = planets[idx];
                displayPlanetBackground(currentPlanet); // 展示星球背景和效果

                // 星球子菜单，停留直到任务完成
                while (true) {
		    // 判断有没有完成星球任务
		    if (checkTasksCompleted(currentPlanet, player)) {
                        currentPlanet.isTaskDone = true;
                        if (find(player.energies.begin(), player.energies.end(), currentPlanet.name) == player.energies.end()) {
                            player.energies.push_back(currentPlanet.name);
                            cout << "恭喜！获得 " << currentPlanet.name << " 能源！\n";
                            if (player.energies.size() < 4) {
                                cout << "你可以前往下一个星球！\n";
                            }
                        }
                    }
                    cout << "\n星球菜单：\n";
                    cout << "1. 收集资源\n2. 战斗\n3. 商店\n4. 查看任务\n5. 返回飞船\n";
                    string action;
                    getline(cin, action);

                    if (action == "1") {
                        collectResources(player, currentPlanet); //收集资源
                    } else if (action == "2") {
                        combat(player, currentPlanet); //战斗
                    } else if (action == "3") {
                        shop(player, currentPlanet); //商店
                    } else if (action == "4") { //查看任务
		        if (currentPlanet.isTaskDone) {
                            cout << "\n";
                            cout << "本星球任务已完成。\n";
                        }
                        else {
                            showTasks(currentPlanet, player);
                        }
                    } else if (action == "5") { //返回
                        break;
                    } else {
                        cout << "无效选项，请重新输入。\n";
                    }
                }
            } else {
                cout << "无效星球选择！\n";
            }
        } else if (choice == "2") {
            displayRules(); // 显示规则
        } else if (choice == "3") {
            saveGame(player); // 保存游戏
            cout << "游戏已保存，即将退出...\n";
            break;
        } else {
            cout << "无效选项，请重新输入。\n";
        }

        // 检查是否集齐所有能源
        if (player.energies.size() == 4) {
	    player.isGameComplete=true;
	    saveGame(player);
            string ending = "恭喜你，星际探险者！\n"
                            "你成功集齐了四种神秘能源，合成了无尽能源。\n"
                            "地球的能源危机得以解除，人类文明迎来了新生。\n"
                            "你的名字将永远铭刻在星际探险史册上！\n"
                            "感谢你的勇敢与智慧!\n"
			    "\n"
			    "游戏结束！\n";
            typeText(ending, 50);
            break;
        }
    }

    return 0;
}
