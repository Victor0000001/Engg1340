#ifndef GAME_MECHANICS_H
#define GAME_MECHANICS_H

#include <string>
#include <vector>
#include "user_management.h"
using namespace std;

// Planet structure
struct Planet {
    string name; // Planet name
    vector<string> resources; // Resources that can be collected
    string combat_item; // Combat items
    vector<pair<string, int>> tasks; // Task list (item, quantity)
    string background; // Background of the Planet
    string effect; // The effect of the Planet
    bool isTaskDone;
};

// Function declaration
void collectResources(Player& player, Planet& planet);//collect resources
void combat(Player& player, Planet& planet);//combat
void showTasks(const Planet& planet, Player& player);//show the task
bool checkTasksCompleted(const Planet& planet, const Player& player);//check if the task is completed
void initializePlanets(vector<Planet>& planets);//Initialize planet data
void shop(Player& player, const Planet& planet);//shop
void displayMenu();//Show the menu
void displayCombatRules();//Show the combat rules
void displayRules();//Show all rules
void displayPlanetBackground(const Planet& planet);//Show background of the Planet
void typeText(const string& text, int msPerChar);//Typing effect

#endif
