#include "TileCodes.h"
#include "GameEngine.h"
#include "Constants.h"
#include "OperationModes.h"

#include <random>
#include <fstream>

#define INITIAL_HAND_SIZE 6
#define TILE_STRING_CHARS 3
#define INVALID_COLOUR    6
#define UNIQUE_TILES      36

GameEngine::GameEngine() {
  createTiles();
  board = new Grid();
  tileBag = nullptr;
  players = 0;
  turn = 0;
}

GameEngine::~GameEngine() {
  delete board;
  if (tileBag != nullptr) {
    delete tileBag;
  }
  for (std::vector<Player>::iterator p = playerDetails.begin();
        p != playerDetails.end(); ++p) {
    delete p->hand;
  }
  playerDetails.clear();
  for (int i = 0; i != UNIQUE_SHAPES; ++i) {
    for (int j = 0; j != UNIQUE_COLOURS; ++j) {
      delete tiles[i][j];
    }
    delete[] tiles[i];
  }
  delete[] tiles;
}


void GameEngine::createTiles() {
  // Stores each unique tile in the heap
  tiles = nullptr;
  tiles = new Tile**[UNIQUE_COLOURS];
  for (int i = 0; i!= UNIQUE_COLOURS; ++i) {
    tiles[i] = new Tile*[UNIQUE_SHAPES];
  }
  char chars[UNIQUE_COLOURS] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
  for (int i = 0; i != UNIQUE_SHAPES; ++i) {
    for (int j = 0; j != UNIQUE_COLOURS; ++j) {
      tiles[j][i] = new Tile(chars[j], i + 1); // +1 to i since shapes are 1-6, not 0-5
    }
  }
}

void GameEngine::createTileBag() {
  tileBag = new LinkedList();
  std::random_device engine;
  bool tileInBag[TOTAL_TILES];
  for (int i = 0; i != TOTAL_TILES; ++i) {
    tileInBag[i] = false;
  }


  for (int i = TOTAL_TILES; i != 0; --i) {
    std::uniform_int_distribution<int> uniform_dist(1, i);
    int unaddedTile = uniform_dist(engine);
    int index = 0;
    while (unaddedTile != 1) {
      if (tileInBag[index++] == false) {
        --unaddedTile;
      }
    }
    while (tileInBag[index] == true) {
      index++;
    }

    tileInBag[index] = true;
    index = (index % UNIQUE_TILES);
    Tile* tileToAdd = tiles[index/UNIQUE_COLOURS][index%UNIQUE_SHAPES];

    tileBag->add(tileToAdd);
  }
}

void GameEngine::dealInPlayers(std::string names[], int numOfPlayers) {
  players = numOfPlayers;
  int handSize = INITIAL_HAND_SIZE;
  for (int i = 0; i != players; ++i) {
    Player newPlayer;
    newPlayer.hand = new LinkedList();
    newPlayer.name = names[i];
    newPlayer.score = 0;
    playerDetails.push_back(newPlayer);
  }

  for (int i = 0; i != handSize; ++i) {
    for (std::vector<Player>::iterator p = playerDetails.begin();
          p != playerDetails.end(); ++p) {
      p->hand->add(tileBag->removeFirst());
    }
  }
  turn = 1;
}

bool GameEngine::replace(std::string tile) {
  bool replaceSuccess = false;
  Tile* inputTile = getTile(tile);
  if (inputTile == nullptr)
  replaceSuccess = false;
  else {
    if (playerDetails[(turn - 1)].hand->remove(inputTile)) {
      tileBag->add(inputTile);
      playerDetails[(turn - 1)].hand->add(tileBag->removeFirst());

      turn = ((turn) % players) + 1;
      replaceSuccess = true;
    }
  }

  return replaceSuccess;
}

bool GameEngine::placeTile(char row, int col, std::string tile,
  std::string& errorMsg, bool& qwirkleFlag, bool& winFlag) {
    bool placeSuccess = false;
    Tile* inputTile = getTile(tile);
    if (inputTile == nullptr) {
      errorMsg = "Error: Input tile does not exist\n";
      placeSuccess = false;
    } else {
      if (Validator::validate(board, inputTile, row, col, errorMsg)) {
        if (playerDetails[turn - 1].hand->remove(inputTile)) {
          int points = Validator::calcScore(board, inputTile, row, col, qwirkleFlag);
          board->setTile(row, col, inputTile);

          playerDetails[turn - 1].score += points;
          playerDetails[turn - 1].hand->add(tileBag->removeFirst());
          if (playerDetails[turn - 1].hand->toString(false).length() == 0) {
            winFlag = true;
          }

          turn = ((turn) % players) + 1;
          placeSuccess = true;
        } else {
          errorMsg = "Error: Tile is not present in the current player's hand\n";
          placeSuccess = false;
        }
      } else {
        // Maintains errorMsg provided by the validator
        placeSuccess = false;
      }
    }
    return placeSuccess;
  }

  // Returns a nullptr if an invalid tile is presented in string
  Tile* GameEngine::getTile(std::string input) {
    char colour = input[0];
    int shape = std::atoi(&input[1]);
    // above verifies if int, non-int value returns 0, which is rejected
    int colourIndex;
    if (colour == RED) {
      colourIndex = 0;
    } else if (colour == ORANGE) {
      colourIndex = 1;
    } else if (colour == YELLOW) {
      colourIndex = 2;
    } else if (colour == GREEN) {
      colourIndex = 3;
    } else if (colour == BLUE) {
      colourIndex = 4;
    } else if (colour == PURPLE) {
      colourIndex = 5;
    } else {
      colourIndex = INVALID_COLOUR;
    }
    Tile* returnValue = nullptr;
    if (colourIndex < INVALID_COLOUR && shape <= 6 && shape > 0) {
      returnValue = tiles[colourIndex][shape - 1];
      // shape - 1 to account for how indexes start at 0 and shapes start at 1
    } else {
      returnValue = nullptr;
    }
    return returnValue;
  }

  std::string GameEngine::toString() {
    std::string output = "";
    bool isGui = false;
    for (std::vector<Player>::iterator p = playerDetails.begin();
          p != playerDetails.end(); ++p) {

      output.append(p->name);
      output.append("\n");
      output.append(std::to_string(p->score));
      output.append("\n");

      output.append(p->hand->toString(isGui));
      output.append("\n");
    }

    output.append(board->toString(isGui));
    output.append(tileBag->toString(isGui));
    output.append("\n");
    output.append(playerDetails[turn - 1].name);
    return output;
  }

  bool GameEngine::loadFile(std::string fileName) {
    bool loadSuccess = true;

    std::fstream loadedFile;
    loadedFile.open(fileName, std::ios::in | std::ios::binary);

    while (!loadedFile.eof() && loadSuccess) {
      std::string line = "";
      getline(loadedFile, line);
      if (line.substr(0, 10).compare("   0  1  2") == 0) { // first line of board
        if(!loadedFile.eof()) {
          getline(loadedFile, line); // should be hyphen line
          int lineLength = line.length();
          int gridSize = (lineLength / TILE_STRING_CHARS) - 1;
          // - 1 to take into account start of the line
          for (int i = board->getSize(); i < gridSize; ++i) {
            board->reSize();
          }
          bool gridLine = true;
          while (!loadedFile.eof() && gridLine) {
            getline(loadedFile, line);
            int currentLineLength = line.length();
            if (currentLineLength == lineLength) {
              char row = line[0];
              bool badTile = false;
              for (int i = 0; i != gridSize && !badTile; ++i) {
                // + 1 for below line due to start of line offset
                std::string tileString = line.substr((i + 1) * TILE_STRING_CHARS,2);
                if (tileString != "  ") {
                  Tile* tileToAdd = getTile(tileString);
                  if (tileToAdd != nullptr) {
                    board->setTile(row, i, tileToAdd);
                  } else {badTile = true;}
                } // end of if statement
              } // end of for loop
              if (badTile) {loadSuccess = false;}

            } else {gridLine = false;} // if check to make sure line is part of grid
          } // while loop

          // while statement to go to tileBag line
          bool tileBagLine = false;
          while (!loadedFile.eof() && !tileBagLine) {
            // if statement to check if 2nd charcter isn't a space, or if it's
            // an empty line, both meaning the line is the tileBag
            if (line.length() == 0) {
              tileBagLine = true;
            } else if (line.substr(1,1).compare(" ") != 0) {
              tileBagLine = true;
            } else {
              getline(loadedFile, line);
            }
          } // end while loop
          if (!loadedFile.eof()) {
            tileBag = new LinkedList();
            int numOfTiles = ((line.length() + 1)/TILE_STRING_CHARS);
            bool badTile = false;
            for (int i = 0; i != numOfTiles && !badTile; ++i) {
              Tile* tileToAdd = getTile(line.substr(i*TILE_STRING_CHARS,2));
              if (tileToAdd != nullptr) {
                tileBag->add(tileToAdd);
              } else {badTile = true;}
            }
            if (badTile) {loadSuccess = false;}

            if (!loadedFile.eof()) {
              getline(loadedFile, line);
              players = 0;
              for (std::vector<Player>::iterator p = playerDetails.begin();
                    p != playerDetails.end(); ++p) {

                ++players;
                if (line.compare(p->name) == 0) {
                  turn = players;
                }
              }
            } else {loadSuccess = false;} // third eof check
          } else {loadSuccess = false;} // second eof check
        } else {loadSuccess = false;}// first eof check
      } else if (line.length() != 0) {
        Player newPlayer;
        newPlayer.name = line;
        if (!loadedFile.eof()) {
          getline(loadedFile, line);
          newPlayer.score = std::stoi(line);

          if (!loadedFile.eof()) {
            getline(loadedFile, line);
            newPlayer.hand = new LinkedList();
            int numOfTiles = ((line.length() + 1)/TILE_STRING_CHARS);
            bool badTile = false;
            for (int i = 0; i != numOfTiles && !badTile; ++i) {
              Tile* tileToAdd = getTile(line.substr(i*TILE_STRING_CHARS,2));
              if (tileToAdd != nullptr) {
                newPlayer.hand->add(tileToAdd);
              } else {badTile = true;}
            }
          } else {loadSuccess = false;} // second eof check
        } else {loadSuccess = false;} // first eof check

        playerDetails.push_back(newPlayer);
      } // end of if else statement
    } // while loop
    return loadSuccess;
  }

  std::string GameEngine::turnDetails() {
    std::string returnValue = "";
    returnValue.append(playerDetails[(turn - 1)].name);
    returnValue.append(", it's your turn\n");
    for (std::vector<Player>::iterator p = playerDetails.begin();
          p != playerDetails.end(); ++p) {
      returnValue.append("Score for ");
      returnValue.append(p->name);
      returnValue.append(": ");
      returnValue.append(std::to_string(p->score));
      returnValue.append("\n");
    }
    bool isGui = (COLOR_CODE_ENABLED && EMOJI_CODE_ENABLED);
    returnValue.append(board->toString(isGui));
    returnValue.append("Your hand is\n");
    returnValue.append(playerDetails[(turn-1)].hand->toString(isGui));
    returnValue.append("\n");
    return returnValue;
  }

  bool GameEngine::gameFinishCheck() {
    bool gameFinished = true;
    bool isGui = false;
    if (tileBag->toString(false).compare("") == 0) { //check if tileBag is empty
      std::string tilesString = playerDetails[(turn - 1)].hand->toString(isGui);
      int numOfTiles = ((tilesString.length() + 1)/3);
      for (int i = 0; i != numOfTiles; ++i) {
        Tile* tileToCheck = getTile(tilesString.substr(i*3,2)); //gets tile in hand
        int boardSize = board->getSize();
        for (int j = 0; j != boardSize; ++j) {
          char rowChar = 'A' + j;
          for (int k = 0; k != boardSize; ++k) {
            std::string string = "";
            if (Validator::validate(board, tileToCheck, rowChar, k, string)) {
              gameFinished = false; //if move available, game isn't finished
            }
          } // end k for loop
        } // end j for loop
      } // end i for loop

    } else {gameFinished = false;} //Game only finishes if tilebag is empty)

    return gameFinished;
  }

  std::string GameEngine::gameWinDetails() {
    std::string returnValue = "";
    returnValue.append("Game Over\n\n");
    Player winner = playerDetails[0];
    for (std::vector<Player>::iterator p = playerDetails.begin();
          p != playerDetails.end(); ++p) {
      returnValue.append("Score for ");
      returnValue.append(p->name);
      returnValue.append(": ");
      returnValue.append(std::to_string(p->score));
      returnValue.append("\n");
      if (p->score > winner.score) {
        winner = (*p);
      }
    }
    returnValue.append("Player ");
    returnValue.append(winner.name);
    returnValue.append(" won!\n\n");
    return returnValue;
  }
