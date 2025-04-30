#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <thread>
#include <chrono>
#include "game_mechanics.h"
using namespace std;

// Typing Effect
void typeText(const string& text, int msPerChar) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(msPerChar));
    }
}

// Main Menu
void displayMenu() {
    cout << "\nMain Menu：\n";
    cout << "1. Departure\n2. Rule\n3. Save and Exit\n";
}

// Display Planet Background and Effects
void displayPlanetBackground(const Planet& planet) {
    typeText(planet.background + "\n", 50);
    cout << "Planet Effects：" << planet.effect << "\n";
}

// Combat Rules
void displayCombatRules() {
    cout << "\n============================ Combat Rules ================================\n";
    cout << "You engage in turn-based combat with monsters, choosing the following actions each time：\n";
    cout << "1. ATTACT（A）：\n";
    cout << "   - Enemy Chooses Heal (H): Deals full damage (equal to your Attack Power).\n";
    cout << "   - Enemy Chooses Attack (A): Both deal 50% damage\n";
    cout << "   - Enemy Chooses Defend (D): Enemy parries - You take 25% ATK damage\n";
    cout << "   - 10% Critical Chance: +50% DMG\n";
    cout << "2. DEFEND（D）：\n";
    cout << "   - Enemy Chooses Attack (A):Rebound! Enemy takes 25% of your ATK as damage.\n";
    cout << "   - Enemy Chooses Heal (H):Restores 10% HP\n";
    cout << "   - 10% Perfect Block Chance: 2x damage rebound。\n";
    cout << "3. HEAL（H）：Restores 10% of max HP.\n";
    cout << "   - Enemy Chooses Defend (D):Healing effect triggered.\n";
    cout << "   - Enemy Chooses Attack (A)：You take full damage from the Enemy.\n";
    cout << "4. HEALING POTION（P）：Restores 50% of max HP (consumes 1 Healing Potion from inventory).\n";
    cout << "5. ATTACK POTION（X）：Increases ATK by 50% for the entire battle (consumes 1 Attack Potion).\n";
    cout << "\n";
    cout << "Enemy randomly selects between [A]ttack, [D]efend, or [H]eal actions.";
    cout << "\n";
    cout << "Victory Condition: Reduce enemy HP to 0 and claim dropped items.\n";
    cout << "Defeat Condition: Your HP reaches 0 - Full health restored, battle ends.\n";
    cout << "========================================================================\n\n";
}

// Rules
void displayRules() {
    cout << "\n============================ Game Rules ================================\n";
    cout << "\n";
    cout << "1. Navigation Rules: \n";
    cout << "   - Initial access is limited to Sylvaris; subsequent planets unlock after completing planetary quests.\n";
    cout << "   - Each planet features unique environments and effects. All quests must be completed before departure.\n";
    cout << "\n";
    cout << "2. Collection Rules: \n";
    cout << "   - Collection Methods: Gathering | Logging | Mining | Fishing.\n";
    cout << "   - Collection Failure Chance (Per Attempt): \n";
    cout << "   * Easy Mode: 5% failure rate\n";
    cout << "   * Medium Mode: 10% failure rate\n";
    cout << "   * Hard Mode: 20% failure rate\n";\n";
    cout << "   - 10% chance: Lucky event (resources doubled).\n";
    cout << "   - Collection requires 2-3s wait.\n";
    cout << "\n";
    cout << "3. Combat Rules: \n";
    displayCombatRules();
    cout << "\n";
    cout << "4. Mission Rules：\n";
    cout << "   - Each planet has multiple quests requiring collection of specific items.\n";
    cout << "   - Complete all quests to obtain Planet Energy.\n";
    cout << "\n";
    cout << "5. Shop Rules:：\n";
    cout << "   - Available: Tools, Potions | Sell: Resources.\n";
    cout << "   - Advanced tools unlock on specific planets.\n";
    cout << "\n";
    cout << "========================================================================\n\n";
}

// Collect Resources
void collectResources(Player& player, Planet& planet) {
    string action;
    cout << "Collection Method: \n1. Gathering\n2. Logging\n3. Mining\n4. Fishing\n";
    getline(cin, action);

    string resource;
    string animation;

    //Special Item Collection Check (Requires specific tools to gather planet-specific items)
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

    //Collection Method Selection
    if (action == "1") { //Gathering
        resource = planet.resources[0];
        animation = "Harvesting " + resource + "...\n";
    } else if (action == "2") {
    	if (!isAction2) { //Logging
            cout << "You lack the proper tool for chopping! \n";
	    return;
	}
        resource = planet.resources[1];
        animation = "Chopping " + resource + "...\n";
    } else if (action == "3") { //Mining
        if (!isAction3) {
            cout << "You have no tool for digging!\n";
            return;
        }
        resource = planet.resources[2];
        animation = "Digging " + resource + "...\n";
    } else if (action == "4") { //Fishing
        if (!isAction4) {
            cout << "You have no tool for fishing!\n";
            return;
        }
        resource = planet.resources[3];
        animation = "Fishing " + resource + "...\n";
    } else {
        cout << "Invalid Choice\n";
        return;
    }

    typeText(animation, 50);
    this_thread::sleep_for(chrono::seconds(2 + rand() % 2)); // 2-3 second delay
    
    // Collection Success Rate
    int successRate = (player.difficulty == "easy") ? 95 : (player.difficulty == "medium") ? 90 : 80;
    bool luckyEvent = (rand() % 100) < 10;

    if (rand() % 100 < successRate) {
        int amount = luckyEvent ? 2 : 1;
        for (int i = 0; i < amount; i++) {
            if (player.inventory.size() < player.storage) {
                player.inventory.push_back(resource);
                cout << "Successfully Collected:" << resource << endl;
            }
        }
	// Whether the lucky event is triggered
        if (luckyEvent) {
            cout << "Blessing of the Goddess of Fortune! Resources doubled!\n";
        }
    } else {
        cout << "Collection failed!\n";
    }
}

// Combat System
void combat(Player& player, Planet& planet) {
    // Choose whether to display rules
    cout << "View combat rules?(y/n)：";
    string viewRules;
    getline(cin, viewRules);
    if (viewRules == "y" || viewRules == "Y") {
        displayCombatRules();
    }

    //Enemy attributes scale with game progress.
    int monsterDifficulty=1;
    if (planet.name=="Glaciora")
        monsterDifficulty=1.2;
    if (planet.name=="Pyroterra")
        monsterDifficulty=1.3;
    if (planet.name=="Desolara")
        monsterDifficulty=1.5;

    //Initialize enemy stats
    int monsterAtk = (player.difficulty == "easy") ? 8 :
                     (player.difficulty == "medium") ? 10 : 12;
    monsterAtk *= monsterDifficulty;
    int monsterHp = (player.difficulty == "easy") ? 80 :
                    (player.difficulty == "medium") ? 100 : 120;
    monsterHp *= monsterDifficulty;
    int maxMonsterHp = monsterHp;

    bool usedAttackPotion = false;
    int originalAtk = player.atk;
    
    //Combat
    while (player.hp > 0 && monsterHp > 0) {
        cout << "Current Status: Player HP: " << player.hp << ", Enemy HP: " << monsterHp << endl;
        cout << "Choose action (A: Attack, H: Heal, D: Defend, P: Potion, X: Attack Potion): ";
        string action;
        getline(cin, action);

        // Combat Effect
        bool frozen = ((planet.name == "Glaciora") && (rand() % 100 < 50) && (find(player.inventory.begin(),player.inventory.end(),"Cold-resistant Suit")==player.inventory.end()));
	bool furnaceEffect = ((planet.name == "Pyroterra") && (find(player.inventory.begin(),player.inventory.end(),"Heat-resistant Suit")==player.inventory.end()));
	bool desolaraEffect = ((planet.name == "Desolara") && (find(player.inventory.begin(),player.inventory.end(),"Radiation-resistant Suit")==player.inventory.end()));
	
        // Healing Potion
        if (action == "P") {
            auto it = find(player.inventory.begin(), player.inventory.end(), "Healing Potion");
            if (it != player.inventory.end()) {
                player.hp = min(player.max_hp, player.hp + player.max_hp / 2);
                player.inventory.erase(it);
                cout << "Combat Flow: You used a Healing Potion (P), restoring 50% of max HP（+" << player.max_hp / 2 << " HP）。\n";
                continue;
            } else {
                cout << "No Healing Potion in inventory!\n";
                continue;
            }
        }

        // Attack Potion
        if (action == "X" && !usedAttackPotion) {
            auto it = find(player.inventory.begin(), player.inventory.end(), "Attack Potion");
            if (it != player.inventory.end()) {
                player.atk *= 1.5;
                usedAttackPotion = true;
                player.inventory.erase(it);
                cout << "Attack Flow: You used a Power Potion (X), increasing ATK by 50%!\n";
                continue;
            } else {
                cout << "No Attack Potion in inventory！\n";
                continue;
            }
        }

        // Enemy Action
        char monsterAction = "AHD"[rand() % 3];

        // Check Effects
        if (frozen) { //Frozen
            cout << "Freeze effect triggered! You cannot act this turn.\n";
            cout << "- The Enemy chooses：";
            switch (monsterAction) {
                case 'A': cout << "ATTACK（A）"; player.hp -= monsterAtk; cout << ", you take " << monsterAtk << " damage.\n"; break;
                case 'H': cout << "HEAL（H）"; monsterHp = min(maxMonsterHp, monsterHp + maxMonsterHp / 10); cout << ", Enemy recovery " << maxMonsterHp / 10 << " HP.\n"; break;
                case 'D': cout << "DEFEND（D）, no effect.\n"; break;
            }
            continue;
        }
        if (furnaceEffect) { //Burns
            player.hp -= 5;
            cout << "Burning effect! Loses 5 HP each turn.\n";
        }
        if (desolaraEffect) { //Radiation
            player.hp -= 5;
	    player.atk = 9;
            cout << "Radiation effect! Loses 5 HP and reduces ATK by 10% each turn.\n";
        }

        // Output player and monster actions
        cout << "Combat Flow：\n";
        cout << "- You have chosen：";
        char playerAction = action.empty() ? 'A' : toupper(action[0]);
        switch (playerAction) {
            case 'A': cout << "ATTACK（A）"; break;
            case 'H': cout << "HEAL（H）"; break;
            case 'D': cout << "DEFEND（D）"; break;
            default: cout << "INVALID ACTION (treated as an attack)."; playerAction = 'A'; break;
        }
        cout << "\n";
        cout << "- Your Enemy have chosen ：";
        switch (monsterAction) {
            case 'A': cout << "ATTACK（A）"; break;
            case 'H': cout << "HEAL（H）"; break;
            case 'D': cout << "DEFEND（D）"; break;
        }
        cout << "\n";

        // Combat results
        bool criticalHit = (playerAction == 'A' && rand() % 100 < 10);
        bool perfectBlock = (playerAction == 'D' && monsterAction == 'A' && rand() % 100 < 10);

        if (playerAction == 'A' && monsterAction == 'H') {
            int damage = desolaraEffect ? player.atk / 2 : player.atk;
            if (criticalHit) {
                damage *= 1.5;
                cout << "- Critical hit! Your attack deals " << damage << " damage.\n";
            } else {
                cout << "- Your attack deals " << damage << " damage.\n";
            }
            monsterHp -= damage;
        } else if (playerAction == 'A' && monsterAction == 'A') {
            int playerDamage = desolaraEffect ? player.atk / 2 : player.atk;
            player.hp -= monsterAtk;
            monsterHp -= playerDamage;
            cout << "- Double attack! You deal " << playerDamage << " damage to the enemy，Enemy deals " << monsterAtk << " damage to you.\n";
        } else if (playerAction == 'A' && monsterAction == 'D') {
            int damage = player.atk / 4;
            player.hp -= damage;
            cout << "- Enemy's defense reflects the attack. You take " << damage << " damage.\n";
        } else if (playerAction == 'H' && monsterAction == 'D') {
            int heal = player.max_hp / 10;
            player.hp = min(player.max_hp, player.hp + heal);
            cout << "- Healed successfully. Restored " << heal << " HP。\n";
        } else if (playerAction == 'H' && monsterAction == 'A') {
            player.hp -= monsterAtk;
            cout << "- Enemy attacks. You take " << monsterAtk << " damage.\n";
        } else if (playerAction == 'D' && monsterAction == 'A') {
            int damage = perfectBlock ? player.atk / 2 : player.atk / 4;
            monsterHp -= damage;
            if (perfectBlock) {
                cout << "- Perfect Parry! Enemy is countered, taking " << damage << " damage.\n";
            } else {
                cout << "- Enemy is reflected, taking " << damage << " damage.\n";
            }
        } else if (playerAction == 'D' && monsterAction == 'H') {
            int heal = maxMonsterHp / 10;
            monsterHp = min(maxMonsterHp, monsterHp + heal);
            cout << "- Enemy heals, restoring " << heal << " HP.\n";
        } else {
            cout << "- Both actions fail.\n";
        }

        // Check player's HP.
        if (player.hp <= 0) {
            cout << "Your HP have dropped to 0, you are defeated!\n";
            player.hp = player.max_hp;
            player.atk = originalAtk; // Initialize ATK
            return;
        }
    }
    
    //Check if enemy's HK is below 0.
    if (monsterHp <= 0) {
        cout << "Enemy's HP has dropped to 0, you win!\n";
        cout << "Acquired drop: " << planet.combat_item << endl;
        player.inventory.push_back(planet.combat_item);
    }
    player.atk = originalAtk; // Reset ATK.
}

// Display mission progress.
void showTasks(const Planet& planet, Player& player) {
    // Missions on this planet have been completed.
    if (planet.isTaskDone) {
        cout << "The task of this planet is done!\n";
        return;
    }
    //Missions on this planet are not yet complete.
    cout << "\n" << "Missions in" << planet.name << "：\n";
    for (const auto& task : planet.tasks) {
        int count = count_if(player.inventory.begin(), player.inventory.end(),
                             [&](const string& item) { return item == task.first; });
        cout << task.first << ": " << count << "/" << task.second << endl;
    }
}

// Check if all missions are complete.
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

// Initialize planet data.
void initializePlanets(vector<Planet>& planets) {
    planets = {
            {
                    "Sylvaris",
                    {"Starfruit", "Ironwood", "Crystal Ore", "Moonfish"},
                    "Forest Guardian's Badge",
                    {{"Ironwood", 2}, {"Crystal Ore", 1}, {"Forest Guardian's Badge", 1}},
                    "Sylvaris, a lush forest planet, where the air is filled with the scent of flowers.\n"
                    "Towering trees block out the sun, and streams shimmer with schools of fish glowing strangely. \n",
                    "No special effects.",
		    false
            },
            {
                    "Glaciora",
                    {"Chillberry", "Frostwood", "Glacial Crystal", "Icefin Trout"},
                    "Ice Prison Warrior's Amulet",
                    {{"Frostwood", 1}, {"Glacial Crystal", 2}, {"Ice Prison Warrior's Amulet", 1}},
                    "Glaciora，a frozen tundra, with piercing cold winds. \n"
                    "Precious minerals lie hidden beneath the ice, and rare fish swim in the lakes.\n",
                    "In combats, without armor equipped, there's a 50% chance of being frozen, skipping your turn.",
		    false
            },
            {
                    "Pyroterra",
                    {"Cinderbloom", "Emberwood", "Magma Ore", "Firefin"},
                    "Alchemist's Mark",
                    {{"Emberwood", 1}, {"Magma Ore", 3}, {"Alchemist's Mark", 1}},
                    "Pyroterra，a scorching volcanic planet, with cracks in the ground spewing flames.\n"
                    "The lava rivers hold precious ores, and the blazing lakes are home to unique fish species.\n",
                    "In combats, without armor equipped, lose 5 health points per turn.",
		    false
            },
            {
                    "Desolara",
                    {"Wildland Herbs", "Desogrove", "Arid Crystal", "Voidfish"},
                    "Ruins Warrior's Relic",
                    {{"Desogrove", 2}, {"Arid Crystal", 3}, {"Ruins Warrior's Relic", 1}},
                    "Desolara，a desolate desert planet, with sandstorms sweeping across the land.\n"
                    "In the abandoned ruins, ancient treasures lie hidden, and rare plants grow tenaciously.\n",
                    "In combats, if not equipped with armor, lose 5 health points and reduce attack power by 20% each turn.",
		    false
            }
    };
}
