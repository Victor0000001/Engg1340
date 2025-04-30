#include <iostream>
#include <algorithm>
#include "game_mechanics.h"
using namespace std;

// 商店系统
void shop(Player& player, const Planet& planet) {
    cout << "欢迎来到 " << planet.name << " 的商店！当前货币：" << player.currency << endl;
    cout << "1. 购买\n2. 出售\n3. 退出\n";
    string choice;
    getline(cin, choice);

    //购买商品
    if (choice == "1") {
        cout << "商品列表：\n";
        vector<pair<string, int>> items = {
                {"Pickaxe", 50},
                {"Fishing Rod", 50},
                {"Axe", 50},
                {"Healing Potion", 30},
                {"Attack Potion", 30}
        };

        // 按星球解锁高级工具
        if (planet.name == "Glaciora" || planet.name == "Pyroterra" || planet.name == "Desolara") {
            items.push_back({"Cold-resistant Pickaxe", 100});
            items.push_back({"Ice Fishing Rod", 100});
            items.push_back({"Cold-resistant Suit", 150});
        }
        if (planet.name == "Pyroterra" || planet.name == "Desolara") {
            items.push_back({"Heat-resistant Pickaxe", 100});
            items.push_back({"Heat-resistant Axe", 100});
            items.push_back({"Heat-resistant Suit", 150});
        }
        if (planet.name == "Desolara") {
            items.push_back({"Alloy Drill", 200});
            items.push_back({"Radiation-resistant Suit", 150});
        }
        
	//展示商品价格
        for (int i = 0; i < items.size(); i++) {
            cout << i + 1 << ". " << items[i].first << " (" << items[i].second << " 货币)\n";
        }
	cout << items.size()+1 << ". Exit shop\n";
        
	//购买商品
        string itemChoice;
        getline(cin, itemChoice);
        int idx = stoi(itemChoice) - 1;
	if (idx==items.size()+1) {
            return;
	}
	bool choiceCorrect=false;
        if (idx >= 0 && idx < items.size()) {
	    choiceCorrect=true;
            if (player.currency >= items[idx].second) {
                player.currency -= items[idx].second;
                player.inventory.push_back(items[idx].first);
                cout << "购买成功：" << items[idx].first << endl;
            } else {
                cout << "货币不足！\n";
            }
            if (!choiceCorrect) {
                cout << "无效选择！\n";
            }
        }
    }

    //出售
    else if (choice == "2") {
        if (player.inventory.empty()) {
            cout << "背包中没有可出售的物品！\n";
            return;
        }
        vector<pair<string, int>> prices = {
                {"Starfruit", 10}, {"Verdantwood", 15}, {"Crystal Ore", 15}, {"Moonfish", 15},
                {"Chillberry", 12}, {"Frostwood", 15}, {"Glacial Crystal", 18}, {"Icefin Trout", 18},
                {"Cinderbloom", 15}, {"Emberwood", 20}, {"Magma Ore", 20}, {"Firefin", 20},
                {"Wildland Herbs", 15}, {"Desogrove", 18}, {"Arid Crystal", 25}, {"Voidfish", 18}
        };

        int totalEarned = 0;
        for (const auto& item : player.inventory) {
            for (const auto& price : prices) {
                if (item == price.first) {
                    totalEarned += price.second;
                    cout << "出售 " << item << " 获得 " << price.second << " 货币\n";
                }
            }
        }
        player.currency += totalEarned;
        if (totalEarned == 0) {
            cout << "没有可出售的资源！\n";
        }
        
	// 更新背包
        player.inventory.erase(
                remove_if(player.inventory.begin(), player.inventory.end(),
                          [&](const string& item) {
                              return find_if(prices.begin(), prices.end(),
                                             [&](const pair<string, int>& p) { return p.first == item; }) != prices.end();
                          }),
                player.inventory.end()
        );
    } else if (choice != "3") {
        cout << "无效选项！\n";
    }
}
