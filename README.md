# Engg1340
Group 23 Group Project

Group Members: 

Han Jiale       3036390279
Huang Hoi Yan   3036392473
Li Louhanyu     3036392291
Song Kening     3036289743
Yao Yonghao     3036395243
Zhu Chit Wai    3036390827

Game Introduction:

In the game "Star Energy Mystery," you're tasked with a crritical mission to save Earth from an energy crisis. You will go to four distinct planets, each with its unique challenges. Your main tasks are collecting rare energy sources, engaging in straregic combat, and gathering the four essential energies to synthesize endless energy. Your actions will determine Earth's future. Are you ready for the challenge?

Game's Background:
In the year 2147, Earth finds itself in the "Great Exhaustion Era." Fossil fuels have been completely depleted, controlled nuclear fusion technology has failed, and the global power grid has collapsed, leading to a state of rotating power supply in cities. The third resource war erupts, and the United Nations disintegrates. However, hope arises in 2150 with the discovery of the "Endless Energy" theory by quantum physicists. They uncover the "source-matter resonance" phenomenon, which proves that four extreme planetary environments can produce special energy crystals. In response to this groundbreaking discovery, the "Savior Plan" is launched in 2151. Agents, or player characters, are secretly selected and transformed. It is now up to the players to collect four different extreme energy sources to synthesize endless energy, with the ultimate goal of saving Earth from its energy crisis.

Compilation/Execution：

Download all the files to Linux, create an executable main program by entering the “make main” command, and then run it through ./main. Players can make choices by entering the corresponding numbers of the options in the game; then they can play the game according to the rules.

Game Rules:

Bellow are the main rules of the game. Players must follow them to progress, complete quests, enhance their abilities, and unlock more content.

1. Navigation Rules
- Initial Access: Players start on the planet Sylvaris and unlock other planets by completing planetary quests.
- Planet Features: Each planet has unique environments and effects. All quests on a planet must be completed before the player can leave.

2. Collection Rules
- Collection Methods: Gathering, Logging, Mining, Fishing.
- Failure Rates:
  - Easy Mode: 5% failure rate
  - Medium Mode: 10% failure rate
  - Hard Mode: 20% failure rate
- Lucky Events: There is a 10% chance for a lucky event, which doubles the collected resources.
- Wait Time: Each collection attempt requires a 2-3 second wait.

3. Combat Rules
- Combat Style: Turn-based combat with enemy, with the following actions available:
  1. Attack (A):
     - Enemy Chooses Heal (H): Deals full damage (equal to your Attack Power).
     - Enemy Chooses Attack (A): Both deal 50% damage.
     - Enemy Chooses Defend (D): Enemy parries - You take 25% ATK damage.
     - 10% Critical Chance: +50% DMG.
  2. Defend (D):
     - Enemy Chooses Attack (A): Rebound! Enemy takes 25% of your ATK as damage.
     - Enemy Chooses Heal (H): Restores 10% HP.
     - 10% Perfect Block Chance: 2x damage rebound.
  3. Heal (H): Restores 10% of max HP.
     - Enemy Chooses Defend (D): Healing effect triggered.
     - Enemy Chooses Attack (A): You take full damage from the Enemy.
  4. Healing Potion (P): Restores 50% of max HP (consumes 1 Healing Potion from inventory).
  5. Attack Potion (X): Increases ATK by 50% for the entire battle (consumes 1 Attack Potion).

!!! All invalid inputs during combat will be defaulted to Attack(A) !!! 
- Enemy Actions: The enemy randomly selects between Attack (A), Defend (D), or Heal (H).
- Victory Condition: Reduce enemy HP to 0 and claim dropped items.
- Defeat Condition: Your HP reaches 0 - Full health restored, battle ends.

4. Mission Rules
- Quest Content: Each planet has multiple quests that require the collection of specific items.
- Quest Rewards: Completing all requests on a planet earns Planet Energy.

 5. Shop Rules
- Available for Purchase: Tools, Potions.
- Available for Sale: Resources.
- Advanced Tools: Unlock advanced tools on specific planets.

Five requirement:

1. Generation of random events:
   When the player is in combat with a guardian, the guardian's behavior is random. Also, lucky events happen randomly.
2. Data structures for storing data:
   The players' structure and the planets' structure in user_management.h and game_machanics.h files.
3. Dynamic memory management:
   When storing the data, we used the vector data structure.
4. File input/output:
   When players register, we will store the player's username and password in a file. When the players play the game, their corresponding data 
   will also be saved in the corresponding file. When the players log into the game later, the previous saved file can be read out.
5. Multiple Difficulty Levels:
   There are three difficulty mode - Easy, Medium, and Hard. In different mode, the failure rates are different.

Non-standard Libraries:

In this game, we create two files, user_management.h and game_mechanics.h, for non-standard library. user_management.h is mainly used to store player game data, and game_mechanics.h is used to build specific gameplay. The two .h files define a struct data structure and various functions used.
