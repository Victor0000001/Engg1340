#include <iostream>
#include <algorithm>
#include "game_mechanics.h"
using namespace std;

// shopping system
void shop(Player& player, const Planet& planet) {
    cout << "Welcome to " << planet.name << "’s shop. Your have ：" << player.currency << " uni-coin now. "<< endl;
    cout << "1. Purchase\n2. Sell\n3. Exit\n";
    string choice;
    getline(cin, choice);

    //buy products
    if (choice == "1") {
        cout << "Goods list：\n";
        vector<pair<string, int>> items = {
                {"Pickaxe", 50},
                {"Fishing Rod", 50},
                {"Axe", 50},
                {"Healing Potion", 30},
                {"Attack Potion", 30}
        };

        // Unlock advanced tools by planet
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
        
	//show the price of the products
        for (int i = 0; i < items.size(); i++) {
            cout << i + 1 << ". " << items[i].first << " (" << items[i].second << " uni-coin)";
            // Add explanation based on item name
            if (items[i].first == "Pickaxe" || items[i].first == "Cold-resistant Pickaxe" || 
                items[i].first == "Heat-resistant Pickaxe" || items[i].first == "Alloy Drill") {
                cout << " - for mining";
            } else if (items[i].first == "Fishing Rod" || items[i].first == "Ice Fishing Rod") {
                cout << " - for fishing";
            } else if (items[i].first == "Axe" || items[i].first == "Heat-resistant Axe") {
                cout << " - for logging";
            } else if (items[i].first == "Healing Potion") {
                cout << " - restores 50% HP";
            } else if (items[i].first == "Attack Potion") {
                cout << " - increases ATK by 50%";
            } else if (items[i].first == "Cold-resistant Suit" || items[i].first == "Heat-resistant Suit" || 
                       items[i].first == "Radiation-resistant Suit") {
                cout << " - protects against planet effects";
            }
            cout << "\n";
        }
	cout << items.size()+1 << ". Exit shop\n";
        
	//buy products
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
                cout << "Purchase successful：" << items[idx].first << endl;
            } else {
                cout << "Your money is not enough！\n";
            }
            if (!choiceCorrect) {
                cout << "Invalid selection！\n";
            }
        }
    }

    //selling the products
    else if (choice == "2") {
        if (player.inventory.empty()) {
            cout << "There are nothing in your backpack can be sold！\n";
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
                    cout << "sell " << item << " get " << price.second << " uni-coin\n";
                }
            }
        }
        player.currency += totalEarned;
        if (totalEarned == 0) {
            cout << "You have no resources to sell！\n";
        }
        
	// update the backpack
        player.inventory.erase(
                remove_if(player.inventory.begin(), player.inventory.end(),
                          [&](const string& item) {
                              return find_if(prices.begin(), prices.end(),
                                             [&](const pair<string, int>& p) { return p.first == item; }) != prices.end();
                          }),
                player.inventory.end()
        );
    } else if (choice != "3") {
        cout << "Invalid selection！\n";
    }
}
