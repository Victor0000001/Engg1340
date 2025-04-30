#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <thread>
#include <chrono>
#include "game_mechanics.h"
using namespace std;

// 打字效果
void typeText(const string& text, int msPerChar) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(msPerChar));
    }
}

// Main Menu
void displayMenu() {
    cout << "\n主菜单：\n";
    cout << "1. 出发\n2. 规则\n3. 保存并退出\n";
}

// 显示星球背景和效果
void displayPlanetBackground(const Planet& planet) {
    typeText(planet.background + "\n", 50);
    cout << "星球效果：" << planet.effect << "\n";
}

// 战斗规则
void displayCombatRules() {
    cout << "\n============================ 战斗规则 ================================\n";
    cout << "你与怪物进行回合制战斗，每次选择以下行动：\n";
    cout << "1. 攻击（A）：\n";
    cout << "   - 怪物选择治疗（H）：造成全额伤害（你的攻击力）。\n";
    cout << "   - 怪物选择攻击（A）：双方造成一半伤害。\n";
    cout << "   - 怪物选择防御（D）：怪物反弹，你受到 1/4 攻击力伤害。\n";
    cout << "   - 10% 概率触发会心一击，伤害增加50%。\n";
    cout << "2. 防御（D）：\n";
    cout << "   - 怪物选择攻击（A）：怪物被反弹，受到 1/4 你的攻击力伤害。\n";
    cout << "   - 怪物选择治疗（H）：怪物恢复 10% 生命值。\n";
    cout << "   - 10% 概率触发完美格挡，反弹伤害翻倍。\n";
    cout << "3. 治疗（H）：恢复10%最大生命值。\n";
    cout << "   - 怪物选择防御（D）：治疗生效。\n";
    cout << "   - 怪物选择攻击（A）：你受到全额怪物伤害。\n";
    cout << "4. 药水（P）：恢复50%最大生命值，需消耗背包中的 Healing Potion。\n";
    cout << "5. 攻击药水（X）：提升50%攻击力，持续整场战斗，需消耗 Attack Potion。\n";
    cout << "\n";
    cout << "怪物随机选择A、D、H三种行动。";
    cout << "\n";
    cout << "胜利条件：怪物生命值降至0，获得掉落物。\n";
    cout << "失败条件：你的生命值降至0，恢复满血，战斗结束。\n";
    cout << "========================================================================\n\n";
}

// 规则
void displayRules() {
    cout << "\n============================ 游戏规则 ================================\n";
    cout << "\n";
    cout << "1. 航行规则：\n";
    cout << "   - 初始只能前往 Sylvaris，完成星球任务后解锁下一个星球。\n";
    cout << "   - 每个星球有独特背景和效果，需完成所有任务才能离开。\n";
    cout << "\n";
    cout << "2. 收集规则：\n";
    cout << "   - 分为采集、伐木、挖矿、钓鱼四种方式。\n";
    cout << "   - 每次收集有概率失败（根据难度：easy 5%, medium 10%, hard 20%）。\n";
    cout << "   - 10% 概率触发幸运事件，资源翻倍。\n";
    cout << "   - 收集需等待 2-3 秒，显示过场动画。\n";
    cout << "\n";
    cout << "3. 战斗规则：\n";
    displayCombatRules();
    cout << "\n";
    cout << "4. 任务规则：\n";
    cout << "   - 每个星球有若干任务，需收集指定数量的物品。\n";
    cout << "   - 完成所有任务后获得星球能源。\n";
    cout << "\n";
    cout << "5. 商店规则：\n";
    cout << "   - 可购买工具、药水或出售资源。\n";
    cout << "   - 高级工具在特定星球解锁。\n";
    cout << "\n";
    cout << "========================================================================\n\n";
}

// 收集资源
void collectResources(Player& player, Planet& planet) {
    string action;
    cout << "选择收集方式：\n1. 采集\n2. 伐木\n3. 挖矿\n4. 钓鱼\n";
    getline(cin, action);

    string resource;
    string animation;

    //特定物品收集判断（不同星球特定物品需要特定工具才可采集）
    bool isAction2=false,isAction3=false,isAction4=false;
    if (planet.name=="Sylvaris") {
        if ((find(player.inventory.begin(),player.inventory.end(),"Axe")!=player.inventory.end()) || (find(player.inventory.begin(),player.inventory.end(),"Heat-resistant Axe")!=player.inventory.end())) {
            isAction2=true;
	}
	if ((find(player.inventory.begin(),player.inventory.end(),"Pickaxe")!=player.inventory.end()) || (find(player.inventory.begin(),player.inventory.end(),"Cold-resistant Pickaxe")!=player.inventory.end()) || (find(player.inventory.begin(),player.inventory.end(),"Heat-resistant Pickaxe")!=player.inventory.end()) || (find(player.inventory.begin(),player.inventory.end(),"Alloy Drill")!=player.inventory.end())) {
            isAction3=true;
        }
	if ((find(player.inventory.begin(),player.inventory.end(),"Fishing Rod")!=player.inventory.end()) || (find(player.inventory.begin(),player.inventory.end(),"Ice Fishing Rod")!=player.inventory.end())) {
            isAction4=true;
        }
    } else if (planet.name=="Glaciora") {
        if ((find(player.inventory.begin(),player.inventory.end(),"Axe")!=player.inventory.end()) || (find(player.inventory.begin(),player.inventory.end(),"Heat-resistant Axe")!=player.inventory.end())) {
	    isAction2=true;
	}
        if (find(player.inventory.begin(),player.inventory.end(),"Cold-resistant Pickaxe")!=player.inventory.end()) {
            isAction3=true;
        }
	if (find(player.inventory.begin(),player.inventory.end(),"Ice Fishing Rod")!=player.inventory.end()) {
            isAction4=true;
        }
    } else if (planet.name=="Pyroterra") {
        if ((find(player.inventory.begin(),player.inventory.end(),"Fishing Rod")!=player.inventory.end()) || (find(player.inventory.begin(),player.inventory.end(),"Ice Fishing Rod")!=player.inventory.end())) {
            isAction4=true;
	}
        if (find(player.inventory.begin(),player.inventory.end(),"Heat-resistant Axe")!=player.inventory.end()) {
            isAction2=true;
        }
	if (find(player.inventory.begin(),player.inventory.end(),"Heat-resistant Pickaxe")!=player.inventory.end()) {
            isAction3=true;
        }
	if ((find(player.inventory.begin(),player.inventory.end(),"Fishing Rod")!=player.inventory.end()) || (find(player.inventory.begin(),player.inventory.end(),"Ice Fishing Rod")!=player.inventory.end())) {
	    isAction4=true;
        }
    } else if (planet.name=="Desolara") {
        if ((find(player.inventory.begin(),player.inventory.end(),"Axe")!=player.inventory.end()) || (find(player.inventory.begin(),player.inventory.end(),"Heat-resistant Axe")!=player.inventory.end())) {
            isAction2=true;
        }
        if (find(player.inventory.begin(),player.inventory.end(),"Alloy Drill")!=player.inventory.end()) {
            isAction3=true;
        }
	if ((find(player.inventory.begin(),player.inventory.end(),"Fishing Rod")!=player.inventory.end()) || (find(player.inventory.begin(),player.inventory.end(),"Ice Fishing Rod")!=player.inventory.end())) {
            isAction4=true;
        }
    }

    //收集方式选择
    if (action == "1") { //采集
        resource = planet.resources[0];
        animation = "正在摘取 " + resource + "...\n";
    } else if (action == "2") {
    	if (!isAction2) { //砍伐
            cout << "你没有可用于砍伐的工具！\n";
	    return;
	}
        resource = planet.resources[1];
        animation = "正在砍伐 " + resource + "...\n";
    } else if (action == "3") { //挖掘
        if (!isAction3) {
            cout << "你没有可用于挖掘的工具！\n";
            return;
        }
        resource = planet.resources[2];
        animation = "正在挖掘 " + resource + "...\n";
    } else if (action == "4") { //钓鱼
        if (!isAction4) {
            cout << "你没有可用于钓鱼的工具！\n";
            return;
        }
        resource = planet.resources[3];
        animation = "正在钓取 " + resource + "...\n";
    } else {
        cout << "无效选择！\n";
        return;
    }

    typeText(animation, 50);
    this_thread::sleep_for(chrono::seconds(2 + rand() % 2)); // 2-3秒延迟
    
    // 收集成功率
    int successRate = (player.difficulty == "easy") ? 95 : (player.difficulty == "medium") ? 90 : 80;
    bool luckyEvent = (rand() % 100) < 10;

    if (rand() % 100 < successRate) {
        int amount = luckyEvent ? 2 : 1;
        for (int i = 0; i < amount; i++) {
            if (player.inventory.size() < player.storage) {
                player.inventory.push_back(resource);
                cout << "成功收集到：" << resource << endl;
            }
        }
	// 幸运事件是否出发
        if (luckyEvent) {
            cout << "幸运女神的眷顾！资源翻倍！\n";
        }
    } else {
        cout << "收集失败！\n";
    }
}

// 战斗系统
void combat(Player& player, Planet& planet) {
    // 选择是否展示规则
    cout << "是否查看战斗规则？(y/n)：";
    string viewRules;
    getline(cin, viewRules);
    if (viewRules == "y" || viewRules == "Y") {
        displayCombatRules();
    }

    //怪物属性随游戏进行程度增强
    int monsterDifficulty=1;
    if (planet.name=="Glaciora")
        monsterDifficulty=1.2;
    if (planet.name=="Pyroterra")
        monsterDifficulty=1.3;
    if (planet.name=="Desolara")
        monsterDifficulty=1.5;

    //初始化怪物数值
    int monsterAtk = (player.difficulty == "easy") ? 8 :
                     (player.difficulty == "medium") ? 10 : 12;
    monsterAtk *= monsterDifficulty;
    int monsterHp = (player.difficulty == "easy") ? 80 :
                    (player.difficulty == "medium") ? 100 : 120;
    monsterHp *= monsterDifficulty;
    int maxMonsterHp = monsterHp;

    bool usedAttackPotion = false;
    int originalAtk = player.atk;
    
    //战斗
    while (player.hp > 0 && monsterHp > 0) {
        cout << "当前状态：玩家 HP: " << player.hp << ", 怪物 HP: " << monsterHp << endl;
        cout << "选择行动 (A: 攻击, H: 治疗, D: 防御, P: 药水, X: 攻击药水): ";
        string action;
        getline(cin, action);

        // 战斗效果
        bool frozen = ((planet.name == "Glaciora") && (rand() % 100 < 50) && (find(player.inventory.begin(),player.inventory.end(),"Cold-resistant Suit")==player.inventory.end()));
	bool furnaceEffect = ((planet.name == "Pyroterra") && (find(player.inventory.begin(),player.inventory.end(),"Heat-resistant Suit")==player.inventory.end()));
	bool desolaraEffect = ((planet.name == "Desolara") && (find(player.inventory.begin(),player.inventory.end(),"Radiation-resistant Suit")==player.inventory.end()));
	
        // 恢复药水
        if (action == "P") {
            auto it = find(player.inventory.begin(), player.inventory.end(), "Healing Potion");
            if (it != player.inventory.end()) {
                player.hp = min(player.max_hp, player.hp + player.max_hp / 2);
                player.inventory.erase(it);
                cout << "战斗流程：你使用了药水（P），恢复 50% 最大生命值（+" << player.max_hp / 2 << " HP）。\n";
                continue;
            } else {
                cout << "背包中没有 Healing Potion！\n";
                continue;
            }
        }

        // 攻击药水
        if (action == "X" && !usedAttackPotion) {
            auto it = find(player.inventory.begin(), player.inventory.end(), "Attack Potion");
            if (it != player.inventory.end()) {
                player.atk *= 1.5;
                usedAttackPotion = true;
                player.inventory.erase(it);
                cout << "战斗流程：你使用了攻击药水（X），攻击力提升 50%！\n";
                continue;
            } else {
                cout << "背包中没有 Attack Potion！\n";
                continue;
            }
        }

        // 怪物行动
        char monsterAction = "AHD"[rand() % 3];

        // 检查效果
        if (frozen) { //冰冻
            cout << "冰冻效果触发！本回合你无法行动。\n";
            cout << "- 怪物选择了：";
            switch (monsterAction) {
                case 'A': cout << "攻击（A）"; player.hp -= monsterAtk; cout << ", 你受到 " << monsterAtk << " 点伤害。\n"; break;
                case 'H': cout << "治疗（H）"; monsterHp = min(maxMonsterHp, monsterHp + maxMonsterHp / 10); cout << ", 怪物恢复 " << maxMonsterHp / 10 << " 点生命值。\n"; break;
                case 'D': cout << "防御（D）, 无效果。\n"; break;
            }
            continue;
        }
        if (furnaceEffect) { //灼烧
            player.hp -= 5;
            cout << "灼烧效果!每回合减少 5 点生命值。\n";
        }
        if (desolaraEffect) { //辐射
            player.hp -= 5;
	    player.atk = 9;
            cout << "辐射效果！每回合减少 5 点生命值，并减少10%攻击力。\n";
        }

        // 输出玩家和怪物行动
        cout << "战斗流程：\n";
        cout << "- 你选择了：";
        char playerAction = action.empty() ? 'A' : toupper(action[0]);
        switch (playerAction) {
            case 'A': cout << "攻击（A）"; break;
            case 'H': cout << "治疗（H）"; break;
            case 'D': cout << "防御（D）"; break;
            default: cout << "无效行动（按攻击处理）"; playerAction = 'A'; break;
        }
        cout << "\n";
        cout << "- 怪物选择了：";
        switch (monsterAction) {
            case 'A': cout << "攻击（A）"; break;
            case 'H': cout << "治疗（H）"; break;
            case 'D': cout << "防御（D）"; break;
        }
        cout << "\n";

        // 战斗结果
        bool criticalHit = (playerAction == 'A' && rand() % 100 < 10);
        bool perfectBlock = (playerAction == 'D' && monsterAction == 'A' && rand() % 100 < 10);

        if (playerAction == 'A' && monsterAction == 'H') {
            int damage = desolaraEffect ? player.atk / 2 : player.atk;
            if (criticalHit) {
                damage *= 1.5;
                cout << "- 会心一击！你的攻击造成 " << damage << " 点伤害。\n";
            } else {
                cout << "- 你的攻击造成 " << damage << " 点伤害。\n";
            }
            monsterHp -= damage;
        } else if (playerAction == 'A' && monsterAction == 'A') {
            int playerDamage = desolaraEffect ? player.atk / 2 : player.atk;
            player.hp -= monsterAtk;
            monsterHp -= playerDamage;
            cout << "- 双方攻击！你对怪物造成 " << playerDamage << " 点伤害，怪物对你造成 " << monsterAtk << " 点伤害。\n";
        } else if (playerAction == 'A' && monsterAction == 'D') {
            int damage = player.atk / 4;
            player.hp -= damage;
            cout << "- 怪物防御反弹，你受到 " << damage << " 点伤害。\n";
        } else if (playerAction == 'H' && monsterAction == 'D') {
            int heal = player.max_hp / 10;
            player.hp = min(player.max_hp, player.hp + heal);
            cout << "- 治疗成功，恢复 " << heal << " 点生命值。\n";
        } else if (playerAction == 'H' && monsterAction == 'A') {
            player.hp -= monsterAtk;
            cout << "- 怪物攻击，你受到 " << monsterAtk << " 点伤害。\n";
        } else if (playerAction == 'D' && monsterAction == 'A') {
            int damage = perfectBlock ? player.atk / 2 : player.atk / 4;
            monsterHp -= damage;
            if (perfectBlock) {
                cout << "- 完美格挡！怪物被反弹，受到 " << damage << " 点伤害。\n";
            } else {
                cout << "- 怪物被反弹，受到 " << damage << " 点伤害。\n";
            }
        } else if (playerAction == 'D' && monsterAction == 'H') {
            int heal = maxMonsterHp / 10;
            monsterHp = min(maxMonsterHp, monsterHp + heal);
            cout << "- 怪物治疗，恢复 " << heal << " 点生命值。\n";
        } else {
            cout << "- 双方行动无效。\n";
        }

        // 检查玩家生命值
        if (player.hp <= 0) {
            cout << "你的生命值降至 0，你被击败了！\n";
            player.hp = player.max_hp;
            player.atk = originalAtk; // 重置攻击力
            return;
        }
    }
    
    //检查怪物生命值是否降至0以下
    if (monsterHp <= 0) {
        cout << "怪物生命值降至 0，你胜利了！\n";
        cout << "获得掉落物：" << planet.combat_item << endl;
        player.inventory.push_back(planet.combat_item);
    }
    player.atk = originalAtk; // 重置攻击力
}

// 显示任务进度
void showTasks(const Planet& planet, Player& player) {
    // 该星球任务已完成
    if (planet.isTaskDone) {
        cout << "The task of this planet is done!\n";
        return;
    }
    //该星球任务未完成
    cout << "\n" << planet.name << "的任务：\n";
    for (const auto& task : planet.tasks) {
        int count = count_if(player.inventory.begin(), player.inventory.end(),
                             [&](const string& item) { return item == task.first; });
        cout << task.first << ": " << count << "/" << task.second << endl;
    }
}

// 检查任务是否全部完成
bool checkTasksCompleted(const Planet& planet, const Player& player) {
    for (const auto& task : planet.tasks) {
        int count = count_if(player.inventory.begin(), player.inventory.end(),
                             [&](const string& item) { return item == task.first; });
        if (count < task.second) {
            return false;
        }
    }
    return true;
}

// 初始化星球数据
void initializePlanets(vector<Planet>& planets) {
    planets = {
            {
                    "Sylvaris",
                    {"Starfruit", "Ironwood", "Crystal Ore", "Moonfish"},
                    "Forest Guardian's Badge",
                    {{"Ironwood", 2}, {"Crystal Ore", 1}, {"Forest Guardian's Badge", 1}},
                    "你降落在 Sylvaris，一片郁郁葱葱的森林星球，空气中弥漫着花香。\n"
                    "参天大树遮天蔽日，溪流中闪烁着奇异光芒的鱼群。\n",
                    "无特殊效果",
		    false
            },
            {
                    "Glaciora",
                    {"Chillberry", "Frostwood", "Glacial Crystal", "Icefin Trout"},
                    "Ice Prison Warrior's Amulet",
                    {{"Frostwood", 1}, {"Glacial Crystal", 2}, {"Ice Prison Warrior's Amulet", 1}},
                    "Glaciora，一座冰封的荒原，寒风刺骨。\n"
                    "冰面下隐藏着珍贵的矿物，湖泊中游动着稀有鱼类。\n",
                    "战斗中，若没有装备防具，50% 概率触发冰冻，跳过你的行动",
		    false
            },
            {
                    "Pyroterra",
                    {"Cinderbloom", "Emberwood", "Magma Ore", "Firefin"},
                    "Alchemist's Mark",
                    {{"Emberwood", 1}, {"Magma Ore", 3}, {"Alchemist's Mark", 1}},
                    "Pyroterra，一颗炽热的熔岩星球，地面裂缝喷出火焰。\n"
                    "岩浆河流中蕴藏着珍贵的矿石，炽热的湖泊中有独特的鱼类。\n",
                    "战斗中，若没有装备防具，每回合减少 5 点生命值",
		    false
            },
            {
                    "Desolara",
                    {"Wildland Herbs", "Desogrove", "Arid Crystal", "Voidfish"},
                    "Ruins Warrior's Relic",
                    {{"Desogrove", 2}, {"Arid Crystal", 3}, {"Ruins Warrior's Relic", 1}},
                    "Desolara，一片荒凉的沙漠星球，沙尘暴席卷大地。\n"
                    "废弃的遗迹中隐藏着古老的宝物，稀有的植物顽强生长。\n",
                    "战斗中，若没有装备防具，每回合减少 5 点生命值，并且攻击力减少20%",
		    false
            }
    };
}
