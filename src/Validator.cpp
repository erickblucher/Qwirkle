/*
 * Validator.cpp
 *
 *      Author: Abrar
 */
#include "Validator.h"
#include <string>
#include "Constants.h"

LineValidation Validator::validateLineVertical(Grid* grid, Tile* newTile,
      char row, int col, std::string& errorMsg, bool isVerticalValidation) {

   bool isValid = true;
   LineValidation validityType = VALIDITY_TYPE_VALID;
   int verticalTilesInLine = 1;

   int rowCoefficient;
   int colCoefficient;
   if (isVerticalValidation) {
      rowCoefficient = 1;
      colCoefficient = 0;
   } else {
      rowCoefficient = 0;
      colCoefficient = 1;
   }

   char rowIndex = row - 'A';
   //Initialize values
   bool colorValidationFailed = false;
   bool shapeValidationFailed = false;
   bool reachedEndOfLine = false;

   //check vertical
   if (!grid->isEmpty()) {
      for (int i = 1;
            verticalTilesInLine <= MAX_LINE_SIZE && isValid
                  && rowIndex + (i * rowCoefficient) < MAX_GRID_SIZE
                  && col + (i * colCoefficient) < MAX_GRID_SIZE
                  && !reachedEndOfLine; ++i) {
         Tile* gridTile = grid->getTile(rowIndex + (i * rowCoefficient),
               col + (i * colCoefficient));
         if (gridTile == nullptr) {
            reachedEndOfLine = true;
         } else {
            if (gridTile->colour != newTile->colour) {
               colorValidationFailed = true;
            }
            if (gridTile->shape != newTile->shape) {
               shapeValidationFailed = true;
            }

            if (gridTile->colour == newTile->colour
                  && gridTile->shape == newTile->shape) {
               shapeValidationFailed = true;
               colorValidationFailed = true;
            }

            if (shapeValidationFailed && colorValidationFailed) {
               isValid = false;
               errorMsg =
                     "Validation Error: Shape and Color in this line are not matching the new tile";
            }
            ++verticalTilesInLine;
         }
      }

      colorValidationFailed = false;
      shapeValidationFailed = false;
      reachedEndOfLine = false;
      for (int i = 1;
            verticalTilesInLine <= MAX_LINE_SIZE && isValid
                  && rowIndex - (i * rowCoefficient) >= 0
                  && col - (i * colCoefficient) >= 0 && !reachedEndOfLine;
            ++i) {
         Tile* gridTile = grid->getTile(rowIndex - (i * rowCoefficient),
               col - (i * colCoefficient));
         if (gridTile == nullptr) {
            reachedEndOfLine = true;
         } else {
            if (gridTile->colour != newTile->colour) {
               colorValidationFailed = true;
            }
            if (gridTile->shape != newTile->shape) {
               shapeValidationFailed = true;
            }

            if (gridTile->colour == newTile->colour
                  && gridTile->shape == newTile->shape) {
               shapeValidationFailed = true;
               colorValidationFailed = true;
            }

            if (shapeValidationFailed && colorValidationFailed) {
               isValid = false;
               errorMsg =
                     "Validation Error: Shape and Color in this line are not matching the new tile";
            }
            ++verticalTilesInLine;
         }
      }

      if (isValid && verticalTilesInLine > MAX_LINE_SIZE) {
         isValid = false;

         errorMsg = "Validation Error: lines should not be longer than ";
         errorMsg += MAX_LINE_SIZE;

      }

      if (!isValid) {
         validityType = VALIDITY_TYPE_INVALID;
      } else if (verticalTilesInLine < MIN_LINE_SIZE) {
         validityType = VALIDITY_TYPE_SIZE1;
      } else {
         validityType = VALIDITY_TYPE_VALID;
      }
   }
   return validityType;
}

bool Validator::validate(Grid* grid, Tile* newTile, char row, int col,
      std::string& errorMsg) {

   // Validation rules
   // *is tile valid and not null?,
   // *is placement out of bound for the Grid?
   // *is Grid empty ? then can place the tile anywhere
   //
   // *-should be the same colour of the tiles in the same line
   // or
   //   should be the same shape as the tiles in the same line
   // * formed lines should not be longer than 6 tiles
   // * formed lines should not be shorter than 2 unless this

   errorMsg = "";
   bool isValid = true;
   if (newTile == nullptr) {
      isValid = false;
      errorMsg = "Validation Error: Tile is null";
   }
   // if out of bound
   else if (row < 'A' || row > 'Z' || col < 0 || col > MAX_GRID_SIZE - 1) {
      isValid = false;
      errorMsg = "Validation Error: Placement is out of bound";
   }
   // if there is a tile already in target location
   else if (grid->getTile(row - 'A', col) != nullptr) {
      isValid = false;
      errorMsg = "Validation Error: The location is already occupied by a Tile";

   } else {

      //Initialize values
      bool isVerticalValidation = true;
      LineValidation validityTypeVertical = validateLineVertical(grid, newTile,
            row, col, errorMsg, isVerticalValidation);
      LineValidation validityTypeHorizontal;

      if (validityTypeVertical == VALIDITY_TYPE_INVALID) {
         isValid = false;
      } else {
         validityTypeHorizontal = validateLineVertical(grid, newTile, row, col,
               errorMsg, !isVerticalValidation);

         if (validityTypeHorizontal == VALIDITY_TYPE_INVALID) {
            isValid = false;
         } else if ((validityTypeVertical == VALIDITY_TYPE_SIZE1
               && validityTypeHorizontal == VALIDITY_TYPE_SIZE1)) {
            isValid = false;
            errorMsg =
               "Validation Error: The Tile is isolated and not forming a line";
         }
      }
   }
   return isValid;
}

int Validator::calcLineScore(Grid* grid, char row, int col,
      bool isVerticalValidation) {
   int rowCoefficient;
   int colCoefficient;
   if (isVerticalValidation) {
      rowCoefficient = 1;
      colCoefficient = 0;
   } else {
      rowCoefficient = 0;
      colCoefficient = 1;
   }
   int scoreCounter = 0;
   bool reachedEndOfLine = false;
   char rowIndex = row - 'A';
   for (int i = 1;
         rowIndex + (i * rowCoefficient) < MAX_GRID_SIZE
               && col + (i * colCoefficient) < MAX_GRID_SIZE
               && !reachedEndOfLine; ++i) {
      Tile* gridTile = grid->getTile(rowIndex + (i * rowCoefficient),
            col + (i * colCoefficient));
      if (gridTile == nullptr) {
         reachedEndOfLine = true;
      } else {
         ++scoreCounter;
      }
   }

   reachedEndOfLine = false;
   for (int i = 1;
         rowIndex - (i * rowCoefficient) >= 0 && col - (i * colCoefficient) >= 0
               && !reachedEndOfLine; ++i) {
      Tile* gridTile = grid->getTile(rowIndex - (i * rowCoefficient),
            col - (i * colCoefficient));
      if (gridTile == nullptr) {
         reachedEndOfLine = true;
      } else {
         ++scoreCounter;
      }
   }

   //if the tile is part of a line, then account for the tile itself
   if (scoreCounter > 0) {
      ++scoreCounter;
   }
   return scoreCounter;
}

int Validator::calcScore(Grid* grid, Tile* newTile, char row, int col,
      bool& qwirkleFlag) {
   // scoring rules,
   // * for every tile in the line, 1 point
   // * if the new tile is part of two lines, then add 2 points
   // * for every qwirkle, 6 points

   //pseudo code
   // check the horizontal line for points
   // check the vertical line for points
   // identify if the tile is part of two lines
   // identify if the tile is forming a qwirkle
   qwirkleFlag = false;

   int twoLinesScore = 0;
   int qwirkleScore = 0;

   bool isVerticalValidation = true;
   int verticalSCore = calcLineScore(grid, row, col, isVerticalValidation);
   int horizontalSCore = calcLineScore(grid, row, col, !isVerticalValidation);

   if (verticalSCore > 0 && horizontalSCore > 0) {
      twoLinesScore = TWO_LINES_BONUS_SCORE;
   }

   if (verticalSCore == 6) {
      qwirkleScore = QWIRKLE_BONUS_SCORE;
      qwirkleFlag = true;
   }

   if (horizontalSCore == 6) {
      qwirkleScore += QWIRKLE_BONUS_SCORE;
      qwirkleFlag = true;
   }

   int totalScore = verticalSCore + horizontalSCore + twoLinesScore
         + qwirkleScore;
   return totalScore;
}
