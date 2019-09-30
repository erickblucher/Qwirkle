//
//  Grid.hpp
//  liza
//
//  Created by Elizabeth Tawaf on 3/5/19.
//  Copyright © 2019 Elizabeth Tawaf. All rights reserved.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Tile.h"

#define MAX_GRID_SIZE 26
#define INITIAL_SIZE 6
#define FIRST_ELEMENT 0

class Grid {
  std::vector < std::vector < Tile * > > board;

  public:
    //constructor
    Grid();
  //deconstructor
  ~Grid();
  //appends the board in the correct form
  std::string toString(bool isGui);
  //sets the tile
  void setTile(char row, int col, Tile * tile);
  //gets the tile
  Tile * getTile(int r, int c);
  // gets the size of the grid
  int getSize();
  //check the size is empty
  bool isEmpty();
  //resizes the grid if the user adds more tiles
  void reSize();
};
#endif /* Grid_hpp */
