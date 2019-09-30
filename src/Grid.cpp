//
//  Grid.cpp
//  liza
//
//  Created by Elizabeth Tawaf on 3/5/19.
//  Copyright © 2019 Elizabeth Tawaf. All rights reserved.
//

#include "Grid.h"

#include "Constants.h"

Grid::Grid() {
  int i, j;
  for (i = 0; i < INITIAL_SIZE; i++) {
    std::vector < Tile * > line;
    for (j = 0; j < INITIAL_SIZE; j++) {
      line.push_back(nullptr);
    }
    board.push_back(line);
  }
  // if no size is mentioned either take a default size or not let tehm play
}

void Grid::reSize() {
  int currentSize = getSize();
  int newSize = currentSize + 1;
  if (newSize <= MAX_GRID_SIZE) {
    int i = 0;
    while (i < currentSize) {
      board[i].push_back(nullptr);
      i++;
    }
    std::vector < Tile * > newRow;
    for (i = 0; i < newSize; i++)
      newRow.push_back(nullptr);

    board.push_back(newRow);
  }
  return;
}

bool Grid::isEmpty() {
  bool res = true;

  for (int i = 0; i < getSize(); i++)
    for (int j = 0; j < getSize(); j++)
      if (board[i][j] != nullptr)
        res = false;
  return res;
}
int Grid::getSize() {
  return (int) board.size();
}
void Grid::setTile(char row, int col, Tile * tile) {
  int boardSize = (int) board.size();
  if ((row - 'A') < boardSize && col < boardSize)
    board[row - 'A'][col] = tile;
  else
    std::cout << "\nInvalid position in Grid";
}
Tile * Grid::getTile(int row, int col) {
  int boardSize = (int) board.size();
  Tile * tile = nullptr;
  if (row < boardSize && col < boardSize)
    tile = board[row][col];
  return tile;
}

std::string Grid::toString(bool isGui) {
  std::string result = " ";
  int n, i, j;
  n = (int) board.size();
  for (j = 0; j < n; j++) {
    if (j > 10) {
      result.append(" ");
    } else {
      result.append("  ");
    }
    result.append(std::to_string(j));
  }
  result.append("\n");
  result.append("  -");
  for (j = 0; j < n; j++)
    result.append("---");
  result.append("\n");
  for (i = 0; i < n; i++) {
    char rowChar = 'A' + i;
    std::string rowNumber = " ";
    rowNumber[FIRST_ELEMENT] = rowChar;
    result.append(rowNumber);
    result.append(" |");
    for (j = 0; j < n; j++) {
      if (board[i][j] != nullptr) {
        if (isGui)
          result.append(board[i][j] -> toStringGui());
        else
          result.append(board[i][j] -> toString());

        result.append("|");
      } else
        result.append("  |");
    }
    result.append("\n");
  }
  return result;
}

Grid::~Grid() {

  int N = getSize();
  for (int i = 0; i < N; i++) {
    board[i].clear();
  }
  board.clear();

}
