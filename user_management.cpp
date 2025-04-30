#include <iostream>
#include <fstream>
#include <sstream>
#include "user_management.h"
using namespace std;

// 检查用户名是否已存在
bool usernameExists(const string& username) {
    ifstream file("users.txt");
    if (!file) {
        return 0;
    }
    string line;
    while (getline(file, line)) {
        string u;
        stringstream ss(line);
        ss >> u;
        if (u == username) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void initializeUser(Player& player, string username, string password, string difficulty){
    player.username = username;
    player.password = password;
    player.difficulty = difficulty;
    player.atk = 10;
    player.hp = 100;
    player.max_hp = 100;
    player.currency = 0;
    player.storage = 1000;
    player.autoLogin = true;
    player.isGameComplete= false;
    player.inventory.clear();
    player.energies.clear();
    player.equipment.clear();
}

// 注册新用户
void registerUser(Player& player) {
    string username, password, difficulty;
    while (true) {
        cout << "Please enter a username：";
        getline(cin,username);
        if (usernameExists(username)) {
            cout << "Username already exists, please select another username.\n";
            continue;
        }
	break;
    }
    cout << "Please enter a password：";
    getline(cin,password);
    while (true) {
        cout << "Please select difficulty (easy/medium/hard)：";
        getline(cin,difficulty);
        if (difficulty != "easy" && difficulty != "medium" && difficulty != "hard") {
            cout << "Invalid difficulty, please select again.\n";
            continue;
        }
        break;
    }
    initializeUser(player, username, password, difficulty);
    
    ofstream file("users.txt", ios::app);
    if (!file) {
        cerr << "Cannot open the file.\n"; // Error message if file can't be opened
        exit(1); // Exit with an error code
    }
    file << username << " " << password << " " << username << " " << difficulty << " 10 100 100 0 1000 1 false\n"; //autoLogin=1
    file.close();
}

// 用户登录
bool login(Player& player) {
    string username, password;
    cout << "Please enter a username：";
    getline(cin, username);
    cout << "Please enter a password：";
    getline(cin, password);

    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        string u, p, diff;
        int atk, hp, max_hp, currency, storage;
        bool autoLogin, isGameComplete;
        stringstream ss(line);
        ss >> u >> p >> diff >> atk >> hp >> max_hp >> currency >> storage >> autoLogin >> isGameComplete;

        if (u == username && p == password) {
            player.username = u;
	    player.password = password;
            player.difficulty = diff;
            player.atk = atk;
            player.hp = hp;
            player.max_hp = max_hp;
            player.currency = currency;
            player.storage = storage;
            player.autoLogin = false; // 登录后禁用自动登录
	    player.isGameComplete = isGameComplete;
            file.close();
            loadGame(player);
            return true;
        }
    }
    file.close();
    cout << "The username or password is wrong.\n";
    return false;
}

// 保存游戏数据
void saveGame(const Player& player) {
    vector<string> lines;
    ifstream file("users.txt");
    string line;

    while (getline(file, line)) {
        string u;
        stringstream ss(line);
        ss >> u;
        if (u == player.username) {
            stringstream newLine;
            newLine << player.username << " " << player.password << " " << player.difficulty << " "
                    << player.atk << " " << player.hp << " " << player.max_hp << " "
                    << player.currency << " " << player.storage << " "
                    << " " << player.autoLogin << " " << player.isGameComplete;
            line = newLine.str();
        }
        lines.push_back(line);
    }
    file.close();

    ofstream outFile("users.txt");
    for (const auto& l : lines) {
        outFile << l << "\n";
    }
    outFile.close();

    // 保存背包和能源到 saves/ 目录
    ofstream invFile(player.username + "_inventory.txt");
    for (const auto& item : player.inventory) {
        invFile << item << "\n";
    }
    for (const auto& energy : player.energies) {
        invFile << "ENERGY_" << energy << "\n";
    }
    invFile.close();
}

// 加载游戏数据
void loadGame(Player& player) {
    ifstream invFile(player.username + "_inventory.txt");
    string item;
    player.inventory.clear();
    player.energies.clear();

    while (getline(invFile, item)) {
        if (item.find("ENERGY_") == 0) {
            player.energies.push_back(item.substr(7));
        } else {
            player.inventory.push_back(item);
        }
    }
    invFile.close();
}
