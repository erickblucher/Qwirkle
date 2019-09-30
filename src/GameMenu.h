//
//  GameMenu.hpp
//  liza
//
//  Created by Elizabeth Tawaf on 3/5/19.
//  Copyright © 2019 Elizabeth Tawaf. All rights reserved.
//

#ifndef GameMenu_hpp
#define GameMenu_hpp
#define MAX_PLAYERS 4
#define NEXT_PLAYER 1
#define NO_PLAYERS 0
#define MIN_PLAYERS 2
#define NEW_GAME 1
#define LOAD_GAME 2
#define SHOW_PLAYER_INFO 3
#define QUIT 4
#define OPTION 0
#define FIRST_LETTER 0
#define LAST_LETTER 5
#define REPLACE 7
#define COMMAND_LENGTH 8
#define REPLACE_COMMAND 10
#define TILE 6
#define REPLACE_TILE 8
#define POSITION 2
#define COLUMN 1
#define GRID_POSITION 12





#include <string>

#include "GameEngine.h"

class GameMenu {
  public:
    GameMenu();
  ~GameMenu();
  GameEngine * gameEngine;
  //GameEngine* newGame();
  // takes the string of numbr of players and checks if it is a valid number
  bool isNum(std::string value);
  //checks for the user's input and output for the game
  void playGame();
  //the game menu
  //void showMenu();
  int getMenuSelected();
  //checks the number of players and validates for the user's input
  //if the put the right number of players
  void newGame();
  //calls the load game method form the gameEngine
  //asks the users for the file they want to upload the file for
  void loadGame();
  //calls the save game method form the gameEngine
  //asks the users for the file they want to save the file for
  void saveGame();
  //student information
  void playerInfo();
  // checkes if the input contains a lower case
  bool conatainsLower(std::string player);
  //the main menu
  void run();
  //checks for the ^D charechter
  void eof();
  //end game.
  void endGame();

};
//std::vector<Player> playerDetails;

#endif /* GameMenu_hpp */
