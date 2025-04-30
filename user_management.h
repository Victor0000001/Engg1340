#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include <string>
#include <vector>
using namespace std;

// Player structure
struct Player {
    string username; // username
    string password; // password
    int atk; // attack damage
    int hp; // current hp
    int max_hp; // max hp
    int currency; // cosmic currency
    int storage; // storage space
    string difficulty; // difficulty level
    vector<string> inventory; // backpack
    vector<string> equipment; // equipment
    vector<string> energies; // collected energy
    bool autoLogin; // automatically log in after registration
    bool isGameComplete;
};

// function declaration
void initializeUser(Player& player, string username, string password, string difficulty); //initialize player
void registerUser(Player& player);//registration
bool login(Player& player);//log in
void saveGame(const Player& player);//save data
void loadGame(Player& player);//loading data
bool usernameExists(const string& username);//Determine if the username exists

#endif
