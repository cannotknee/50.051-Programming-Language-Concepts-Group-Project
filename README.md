PetSim: Text-Based Pet Simulation Adventure
==================================================
![alt text](https://github.com/[cannotknee]/[50.051-Programming-Language-Concepts-Group-Project]/blob/[main]/demo.png?raw=true)
### Top-level directory layout
    
```
.
├── image                               # txt files of images for different pets
├── include                             # .h files
├── save_files                          # .csv files for saving game progress (maximum of 3 for our game)
├── src                                 # .c files
├── .gitignore                          # directories and files to ignore
├── 50-051_Project_Instructions.pdf     # project instructions
├── PLC Proposal.pdf                    # initial project proposal
├── demo.png                            # screenshot of the game
├── makefile                            # makefile for compiling the game
|── README.md                           # game information & what needs to be done to run the code
└── rungame                             # executable file for running the game
```

### To run the game:
1. Clone the repository
2. Run `make` in the terminal
3. Run `./rungame` in the terminal
4. Enjoy the game!

### Game Information:
- The game offers a captivating text-based pet simulation experience, allowing players to engage in a variety of activities such as purchasing and selling pets, nurturing them through feeding, cleaning, playing, training, and providing medical care when needed.
- Players can raise the pet to adulthood and sell it for a profit to buy more expensive pets, or keep it as a companion.
- In each day, players can choose to perform up to 3 activities, with each activity taking up a certain amount of time. When 3 activities are performed, the day needs to be ended to proceed to the next day.
- Performing activities will affect the pet's health, happiness, and hunger levels, which will be determine the pet's growth and state.
- When the pet reaches a dangerous state, it will die and the pet will be removed from the player's inventory.
- The game will end when the player runs out of money or when the player decides to quit the game.
- Players may save their progress and load it at a later time.

### How the game works:
- The game is written in C and compiled using the makefile.
- The game is run in the terminal.
- Players can interact with the game by inputting numbers corresponding to the actions they want to perform.
- There is a maximum of 3 csv save files for the game, which players can use to save their progress and load it at a later time.
- There is a maximum of 5 pets that players can own at any one time.
- "enable action confirmation" is a setting that players can enable to confirm their actions before proceeding.

### Authors
Cohort 1 Group 1:
* **Jobelle Lee** - [themaxermister](https://github.com/themaxermister)
* **Kenny Ong** - [cannotknee](https://github.com/cannotknee)
* **Lee Darren** - [hecatehonryuu](https://github.com/hecatehonryuu)
* **Wang Xingrui** - [Polaris106](https://github.com/Polaris106)