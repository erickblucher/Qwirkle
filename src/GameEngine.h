#include <iostream>
#include <string>
#include <vector>

#include "LinkedList.h"
#include "Validator.h"


class GameEngine {
struct Player
{
  std::string name;
  LinkedList* hand;
  int score;
};
public:
  GameEngine();
  ~GameEngine();

  Tile*** tiles;
  LinkedList* tileBag;
  Grid* board;

  std::vector<Player> playerDetails;
  int players;
  int turn;

  // creates a new, random tile bag. It adds 2 copies of all tiles into the tilebag
  void createTileBag();

  // takes in a value >1 and <5 and creates a hand for each player,
  // initialises turn to 1 and sets players to number of players.
  void dealInPlayers(std::string names[], int numOfPlayers);

  // takes in a tile string that is present in the players hand
  // if the tile is in the players hand it adds it back to the tileBag
  // otherwise, returns false
  bool replace(std::string tile);

  // takes in a tile string, a row and col, all representing the location a
  // tile is to be placed, checking that the move is valid, before removing it
  // and adding it to the board
  bool placeTile(char row, int col, std::string tile,
    std::string& errorMsg, bool& qwirkleFlag, bool& winFlag);

    // provides a string input that contains a string consisting of 2 characters
    // First represets a character for a colour, the Second represents a
    // number for the shape
    Tile* getTile(std::string input);

    // returns all the data in the game formatted for a save file
    std::string toString();

    // returns true if valid file path provided, otherwise returns false
    // loads up a save file
    bool loadFile(std::string fileName);

    // returns a string containing the details showing the players turn,
    // all player's scores, the board and the hand of the player
    std::string turnDetails();

    // returns a string containing the details stating the scores of all players
    // and the winner of the game
    std::string gameWinDetails();

    // checks to see if the game is finished
    bool gameFinishCheck();
  private:
    void createTiles();
  };
