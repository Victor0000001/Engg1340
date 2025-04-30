#include <iostream>
#include <algorithm>
#include <locale>
#include <thread>
#include <chrono>
#include <cstdio>
#include "user_management.h"
#include "game_mechanics.h"
using namespace std;

// Main function, the entrance to the game
int main() {
    setlocale(LC_ALL, "en_US.UTF-8"); // Set UTF-8 encoding
    srand(time(0));// Initialize random seed

    // Show the title
    cout << "\n=========================================\n";
    cout << "              Star Energy Mystery             \n";
    cout << "=========================================\n";
    cout << "Press Enter to start the game...\n";
    cin.get();

    Player player;
    vector<Planet> planets;
    initializePlanets(planets); // Initialize planet data

    cout << "1. Register\n2. Log in\n3. Exit\n";
    string choice;
    getline(cin, choice);

    bool isRegister=false;
    if (choice == "1") {
        registerUser(player); // User Registration
        if (player.autoLogin) {
            cout << "You have successfully registered, log in automatically...\n";
        } else {
            cout << "Please log in\n";
            if (!login(player)) return 1;
        }
	isRegister=true;
    } 
    else if (choice == "2") {
        if (!login(player)) return 1; // user log in
    } else {
        return 0;
    }
    
    // check if the player have completed the game
    if (player.isGameComplete) {
        string restartRequest = "You have completed the game.\n"
	                        "Would you like to restart? (y/n)\n";
        typeText(restartRequest, 50);
	while (true) {
            string select;
	    getline(cin,select);
	    // ask the player if he/she wants to play again
	    if ((select == "y") || (select == "Y")) {
                break;
	    } else if ((select == "n") || (select == "N")) {
	        cout << "Game exits.\n";
                return 0;
	    } else {
                cout << "Invalid input\n";
		cout << "\n";
		cout << "Would you like to restart? (y/n)\n";
	    }
	}
	// If the player choosed play again, reselect the difficulty
	typeText("You can choose the difficulty again.\n", 50);
	string difficulty;
	while (true) {
            cout << "Choose Difficulty Level (easy/medium/hard)：";
            getline(cin,difficulty);
            if (difficulty != "easy" && difficulty != "medium" && difficulty != "hard") {
                cout << "This is an invalid difficulty level, please select again\n";
                continue;
            }
            break;
        }
	// If restart, reset the player's initial data
	initializeUser(player, player.username, player.password, difficulty);
	remove((player.username + "_inventory.txt").c_str());
        loadGame(player);
        isRegister=true;
    }
    
    //Start the game
    typeText("Game begins!\n",50);
    cout << "\n";

    // First play, showing the background story
    if (isRegister) {
        string backstory = "In 2378 AD, the earth's energy was exhausted and humanity was facing a catastrophe.\n"
                           "You are an interstellar explorer on a mission to find four mysterious energy sources.\n"
                           "These energies are scattered across four planets in the universe：Sylvaris, Glaciora, \n"
                           "Pyroterra, and Desolara.\n"
                           "Only by collecting all energy sources can we synthesize endless energy and save the earth!\n"
                           "Get ready, your interstellar journey is about to begin...\n";
        typeText(backstory, 50);
    }

    while (true) {
        displayMenu(); // Show main menu
        getline(cin, choice);

        if (choice == "1") {
            // Unlock planets in order
            cout << "Planets you can visit:\n";
            int unlocked = player.energies.size() + 1; // Number of planets unlocked
	    // Show available planets
            for (int i = 0; i < min(unlocked, (int)planets.size()); i++) {
                cout << i + 1 << ". " << planets[i].name << endl;
            }
            string planetChoice;
            getline(cin, planetChoice);
            int idx = stoi(planetChoice) - 1;
            if (idx >= 0 && idx < unlocked && idx < planets.size()) {
                Planet& currentPlanet = planets[idx];
                displayPlanetBackground(currentPlanet); // Show planet background and effects

                // Planet submenu, stay until the mission is completed
                while (true) {
		    // Determine whether the planet mission has been completed
		    if (checkTasksCompleted(currentPlanet, player)) {
                        currentPlanet.isTaskDone = true;
                        if (find(player.energies.begin(), player.energies.end(), currentPlanet.name) == player.energies.end()) {
                            player.energies.push_back(currentPlanet.name);
                            cout << "Congratulations! You have received " << currentPlanet.name << " sources！\n";
                            if (player.energies.size() < 4) {
                                cout << "You can go to the next planet！\n";
                            }
                        }
                    }
                    cout << "\nPlanet Menu：\n";
                    cout << "1. Collect resources\n2. Combat\n3. Shop\n4. View Tasks\n5. Return to the spacecraft\n";
                    string action;
                    getline(cin, action);

                    if (action == "1") {
                        collectResources(player, currentPlanet); //collecting the resources
                    } else if (action == "2") {
                        combat(player, currentPlanet); //combat
                    } else if (action == "3") {
                        shop(player, currentPlanet); //Shop
                    } else if (action == "4") { //view the tasks
		        if (currentPlanet.isTaskDone) {
                            cout << "\n";
                            cout << "The mission on this planet has been completed\n";
                        }
                        else {
                            showTasks(currentPlanet, player);
                        }
                    } else if (action == "5") { //return
                        break;
                    } else {
                        cout << "It is an invaild selection, place enter again!\n";
                    }
                }
            } else {
                cout << "Invalid planet selection!\n";
            }
        } else if (choice == "2") {
            displayRules(); // show the tasks
        } else if (choice == "3") {
            saveGame(player); // save the data of the game
            cout << "You have saved your game, exiting...\n";
            break;
        } else {
            cout << "It is an invaild selection, place enter again!\n";
        }

        // Check if all energy sources are collected
        if (player.energies.size() == 4) {
	    player.isGameComplete=true;
	    saveGame(player);
            string ending = "Congratulations, interstellar explorer!\n"
                            "You have successfully collected four mysterious energies and synthesized endless energy.\n"
                            "the earth's energy crisis has been resolved and human civilization has been reborn.\n"
                            "Your name will be forever engraved in the history of interstellar exploration!\n"
                            "Thank you for your courage and wisdom!\n"
			    "\n"
			    "Game over!\n";
            typeText(ending, 50);
            break;
        }
    }

    return 0;
}
