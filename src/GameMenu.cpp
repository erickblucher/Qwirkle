//
//  GameMenu.cpp
//  liza
//
//  Created by Elizabeth Tawaf on 3/5/19.
//  Copyright © 2019 Elizabeth Tawaf. All rights reserved.
//

#include "GameMenu.h"

#include <iostream>

#include <fstream>

GameMenu::GameMenu() {
  gameEngine = new GameEngine();
}

GameMenu::~GameMenu() {
  delete gameEngine;
}

void GameMenu::run() {
  bool repeat = true;
  std::string menuString = "";
  menuString.append("\nWelcome to Qwirkle!\n-------------------\n");
  menuString.append("\nMenu\n----\n");
  menuString.append("1. New Game\n");
  menuString.append("2. Load Game\n");
  menuString.append("3. Show student information\n");
  menuString.append("4. Quit\n");

  while (repeat) {
    std::cout << menuString;
    int menuChoice = getMenuSelected();
    if (menuChoice == NEW_GAME) {
      newGame();
      playGame();
    } else if (menuChoice == LOAD_GAME) {
      loadGame();
    } else if (menuChoice == SHOW_PLAYER_INFO) {
      playerInfo();
    } else if (menuChoice == QUIT) {
      std::cout << "Goodbye";
      repeat = false;
    }
  }
}
bool GameMenu::isNum(std::string value) {
  bool result = true;
  for (int i = 0; value[i] != '\0'; i++) {
    if (!(value[i] >= '0' && value[i] <= '9'))
      result = false;
  }
  return result;
}

int GameMenu::getMenuSelected() {
  int menuOption;
  std::string option;
  bool validInput = false;
  while (!validInput) {
    std::cout << " Enter your choice : ";
    std::cout << ">  ";
    getline(std::cin, option);
    if (std::cin.eof())
      option = "4";
    if (option.length() != NEW_GAME)
      validInput = false;
    else {
      if (!(option[OPTION] >= '1' && option[OPTION] <= '4'))
        validInput = false;
      else
        validInput = true;
    }
    if (validInput == false)
      std::cout << " Please enter a valid option\n";
  }

  menuOption = stoi(option);
  return menuOption;
}

bool GameMenu::conatainsLower(std::string player) {
  bool res = false;
  for (int i = 0; player[i] != '\0'; i++) {
    if (!(player[i] >= 'A' && player[i] <= 'Z')) {
      res = true;
    }
  }
  return res;
}

void GameMenu::newGame() {
  std::cout << "Starting a New Game" << std::endl;
  int numPlayers = NO_PLAYERS;
  std::string number = "";
  std::string players[MAX_PLAYERS];
  gameEngine -> createTileBag();
  while (numPlayers < MIN_PLAYERS || numPlayers > MAX_PLAYERS) {
    std::cout << "How many players are there?" << std::endl;
    std::cout << ">  ";
    getline(std::cin, number);
    eof();
    if (isNum(number)) {
      numPlayers = stoi(number);
      if (numPlayers < MIN_PLAYERS || numPlayers > MAX_PLAYERS)
        //handle nonint values
        std::cout << "No. of players has to be between 2 and 4 inclusively\n";
    } else {
      std::cout << "Please enter integer value only\n";
      numPlayers = NO_PLAYERS;
    }
  }
  for (int i = NO_PLAYERS; i < numPlayers; i++) {
    bool addPlayer = true;
    do {
      addPlayer = true;
      std::cout << "Enter a name for player " << i + NEXT_PLAYER;
      std::cout << "  (uppercase characters only)" << std::endl;
      std::cout << ">  ";
      std::string newPlayer = "";
      getline(std::cin, newPlayer);
      eof();

      if (conatainsLower(newPlayer)) {
        std::cout << "Only upper case letter are allowed, please enter again\n";
        addPlayer = false;
      }
      for (int j = 0; j != i; ++j) { //itterate for each previous player
        if (players[j].compare(newPlayer) == 0) {
          std::cout << "Error: entered names must be unique\n";
          addPlayer = false;
        }
      }
      if (addPlayer) {
        players[i] = newPlayer;
      }
    } while (!addPlayer);
  }
  gameEngine -> dealInPlayers(players, numPlayers);
  std::cout << "\nLets's Play!" << std::endl;

}
void GameMenu::eof() {
  if (std::cin.eof()) {
    endGame();
  }
}

void GameMenu::endGame() {
  std::cout << "Goodbye\n";
  exit(EXIT_SUCCESS);
}
void GameMenu::loadGame() {
  std::string fileName;
  std::string player2;
  std::cout << "Enter the filename from which load a game" << std::endl;
  std::cout << ">  ";
  getline(std::cin, fileName);
  eof();
  std::fstream File;
  File.open(fileName, std::ios:: in | std::ios::binary);
  if (File.fail())
    std::cout << "The file specified cant be read, make sure it exists\n";
  else {
    gameEngine -> loadFile(fileName);

    std::cout << "\nQwirkle game successfully loaded\n" << std::endl;
    playGame();
  }
}
void GameMenu::saveGame() {
  std::string fileName;
  std::cout << "Enter the name of the file to save the game ";
  std::cout << ">  ";
  getline(std::cin, fileName);
  eof();
  std::fstream File;
  File.open(fileName, std::ios::out | std::ios::binary);
  File << gameEngine -> toString();
  File.close();
  std::cout << "Game Saved Successfully\n";
}

void GameMenu::playGame() {
  //players = numOfPlayers;
  std::string command;
  bool stop = false;
  while (!stop) {
    if (gameEngine -> gameFinishCheck()) {
      std::cout << gameEngine -> gameWinDetails() << '\n';
      endGame();
    }
    std::cout << gameEngine -> turnDetails();
    std::cout << "\nEnter any of the following commands";
    std::cout << "\n\nplace <<Tile>> at <<Position>>\n";
    std::cout << "replace <<Tile>>\nsave\n";
    //cin can not be used to a function
    std::cout << ">  ";
    getline(std::cin, command);
    eof();
    if (command.compare("save") == OPTION) {
      saveGame();
      bool cnt = true;
      while (cnt) {
        std::cout << "Do you want to continue playing the game (yes/no) ";
        std::cout << ">  ";
        getline(std::cin, command);
        eof();
        if (command.compare("yes") == OPTION) {
          stop = false;
          cnt = false;
        } else if (command.compare("no") == OPTION) {
          endGame();
        } else {
          std::cout << "Invalid selection\n";
          cnt = true;
        }
      }
    } else if (command.substr(FIRST_LETTER, REPLACE).compare("replace") == OPTION) {
      if (command.length() == REPLACE_COMMAND) {
        std::string tileToTrade = command.substr(REPLACE_TILE);
        if (gameEngine -> replace(tileToTrade)) {
          std::cout << "Replace Complete\n";
        } else {
          std::cout << "Tile given is not in hand, make sure you enter a valid tile\n";
        }
      } else {
        std::cout << "Incorect command format, please read the guidelines\n";
      }
    } else if (command.substr(FIRST_LETTER, LAST_LETTER).compare("place") == OPTION) {
      std::string syntax = "place -- at --";
      bool result = true;
      if (command.length() < syntax.length()) {
        // can be equal or greater than, double digit coordinate

        result = false;
      }
      for (int i = 0; syntax[i] != '\0' && result; i++) {
        if (syntax[i] != '-')
          if (command[i] != syntax[i])
            result = false;
      }

      if (result == false) {
        std::cout << "Invalid mode of command, please follow the instructions";
      } else {
        std::string tileValue = command.substr(TILE, POSITION);
        std::string gridPosition = command.substr(GRID_POSITION);
        char row;
        std::string colString;
        int col;
        row = gridPosition[FIRST_ELEMENT];
        //srt position of the substring is 1 to fetch col no
        colString = gridPosition.substr(COLUMN);
        if (isNum(colString)) {
          col = std::stoi(colString);
          // places it anywhere on the grid
          if (col <= 25 && row <= 'Z') {
            if (gameEngine -> board -> isEmpty()) {
              while (col >= gameEngine -> board -> getSize() ||
                    row - 'A' >= gameEngine -> board -> getSize()) {
                gameEngine -> board -> reSize();
              }
            }
          }
          std::string errorMsg = "";
          bool qwirkleFlag = false;
          bool winFlag = false;
          if (gameEngine -> placeTile(row, col, tileValue, errorMsg, qwirkleFlag, winFlag)) {
            if (col == gameEngine -> board -> getSize() - 1 ||
                (row - 'A') == gameEngine -> board -> getSize() - 1) {
              gameEngine -> board -> reSize();
            }
            if (qwirkleFlag) {
              std::cout << "Qwirkle!" << '\n';
            }
            if (winFlag) {
              std::cout << gameEngine -> gameWinDetails() << '\n';
              endGame();
            }
          } else {
            std::cout << errorMsg << '\n';
          }
        } else {
          std::cout << "Error: Invalid coordinate entered\n";
        }
      }
    }
  }
}
//fix
void GameMenu::playerInfo() {
  std::cout << "---------------------------------\n";
  std::cout << "Name: Elizabeth Tawaf\nStudent ID: s3723812\nEmail: s3723812@student.rmit.edu.au\n\n";
  std::cout << "Name: Abrar Al-Sagheer\nStudent ID: s3707180\nEmail: s3707180@student.rmit.edu.au\n\n";
  std::cout << "Name: Erick Blucher\nStudent ID: s3723054\nEmail: s3723054@student.rmit.edu.au\n\n";
    std::cout << "---------------------------------\n";
}
