/*
 * LinkedListTest.cpp
 *
 *  Created on: 25 Apr 2019
 *      Author: Abrar
 */

#include "Validator_test.h"
#include "../src/Validator.h"
#include "../src/Tile.h"
#include "../src/TileCodes.h"
#include <string>

#include <iostream>
#include "../src/Constants.h"

void Validator_Test::scoreTest() {
   Grid* grid = initialiseGrid();
   Tile* redCirTile = new Tile(RED, CIRCLE);
   Tile* redSt4Tile = new Tile(RED, STAR_4);
   Tile* redDiaTile = new Tile(RED, DIAMOND);
   Tile* redSquTile = new Tile(RED, SQUARE);
   Tile* redSt6Tile = new Tile(RED, STAR_6);
   Tile* redCloTile = new Tile(RED, CLOVER);

   std::string testName = "";
   int score = 0;
   bool qwirkleFlag;
   int expectedScore = -1;
   int expectedQFlg = false;

   //--------------  calc score for first tile placement
   testName = "Score_Test, calc score for first tile placement";
   score = Validator::calcScore(grid, redCirTile, 'B', 10, qwirkleFlag);
   expectedScore = 0;
   expectedQFlg = false;
   std::cout
         << ((score == expectedScore && qwirkleFlag == expectedQFlg) ?
               "Pass: " : "Fail: ") << testName << ", expected Score:"
         << expectedScore << ", Actual:" << score << std::endl;

   //-------------- calc score for 2nd tile in a row
   grid->setTile('B', 10, redCirTile);
   testName = "Score_Test, calc score for 2nd tile in a row";
   score = Validator::calcScore(grid, redSt4Tile, 'A', 10, qwirkleFlag);
   expectedScore = 2;
   expectedQFlg = false;
   std::cout
         << ((score == expectedScore && qwirkleFlag == expectedQFlg) ?
               "Pass: " : "Fail: ") << testName << ", expected Score:"
         << expectedScore << ", Actual:" << score << std::endl;

   //-------------- calc score for 2nd tile in a col
   testName = "Score_Test, calc score for 2nd tile in a col";
   score = Validator::calcScore(grid, redSt4Tile, 'B', 11, qwirkleFlag);
   expectedScore = 2;
   expectedQFlg = false;
   std::cout
         << ((score == expectedScore && qwirkleFlag == expectedQFlg) ?
               "Pass: " : "Fail: ") << testName << ", expected Score:"
         << expectedScore << ", Actual:" << score << std::endl;

   //-------------- calc score for 5th tile in a row (middle position)
   delete grid;
   grid = initialiseGrid();
   grid->setTile('A', 10, redCirTile);
   grid->setTile('C', 10, redDiaTile);
   grid->setTile('D', 10, redSquTile);
   grid->setTile('E', 10, redSt6Tile);

   testName = "Score_Test, calc score for 5th tile in a row (middle position)";
   score = Validator::calcScore(grid, redSt4Tile, 'B', 10, qwirkleFlag);
   expectedScore = 5;
   expectedQFlg = false;
   std::cout
         << ((score == expectedScore && qwirkleFlag == expectedQFlg) ?
               "Pass: " : "Fail: ") << testName << ", expected Score:"
         << expectedScore << ", Actual:" << score << std::endl;

   //-------------- calc score for 5th tile in a col (middle position)
   delete grid;
   grid = initialiseGrid();
   grid->setTile('Z', 0, redCirTile);
   grid->setTile('Z', 1, redDiaTile);
   grid->setTile('Z', 3, redSquTile);
   grid->setTile('Z', 4, redSt6Tile);

   testName = "Score_Test, calc score for 5th tile in a col (middle position)";
   score = Validator::calcScore(grid, redSt4Tile, 'Z', 2, qwirkleFlag);
   expectedScore = 5;
   expectedQFlg = false;
   std::cout
         << ((score == expectedScore && qwirkleFlag == expectedQFlg) ?
               "Pass: " : "Fail: ") << testName << ", expected Score:"
         << expectedScore << ", Actual:" << score << std::endl;

   //-------------- calc score for 6th tile in a row (qwirkle)
   delete grid;
   grid = initialiseGrid();
   grid->setTile('B', 0, redCirTile);
   grid->setTile('C', 0, redDiaTile);
   grid->setTile('D', 0, redSquTile);
   grid->setTile('E', 0, redSt6Tile);
   grid->setTile('F', 0, redCloTile);

   testName = "Score_Test, calc score for 6th tile in a row (qwirkle)";
   score = Validator::calcScore(grid, redSt4Tile, 'A', 0, qwirkleFlag);
   expectedScore = 12;
   expectedQFlg = true;
   std::cout
         << ((score == expectedScore && qwirkleFlag == expectedQFlg) ?
               "Pass: " : "Fail: ") << testName << ", expected Score:"
         << expectedScore << ", Actual:" << score << std::endl;

   //-------------- calc score for 6th tile in a col (qwirkle)
   delete grid;
   grid = initialiseGrid();
   grid->setTile('R', 20, redCirTile);
   grid->setTile('R', 21, redDiaTile);
   grid->setTile('R', 22, redSquTile);
   grid->setTile('R', 23, redSt6Tile);
   grid->setTile('R', 24, redCloTile);

   testName = "Score_Test, calc score for 6th tile in a col (qwirkle)";
   score = Validator::calcScore(grid, redSt4Tile, 'R', 25, qwirkleFlag);
   expectedScore = 12;
   expectedQFlg = true;
   std::cout
         << ((score == expectedScore && qwirkleFlag == expectedQFlg) ?
               "Pass: " : "Fail: ") << testName << ", expected Score:"
         << expectedScore << ", Actual:" << score << std::endl;

   //-------------- calc score for in two line formation (Col & Row)
   // with no qwirkle
   delete grid;
   grid = initialiseGrid();

   // test tile forming part of 2 lines
   Tile* purSquTile = new Tile(PURPLE, SQUARE);
   Tile* yelSquTile = new Tile(YELLOW, SQUARE);
   Tile* yelDiaTile = new Tile(YELLOW, DIAMOND);
   Tile* yelSt4Tile = new Tile(YELLOW, STAR_4);
   Tile* purSt4Tile = new Tile(PURPLE, STAR_4);
   Tile* purDiaTile = new Tile(PURPLE, DIAMOND);
   Tile* purCirTile = new Tile(PURPLE, CIRCLE);
   Tile* purSt6Tile = new Tile(PURPLE, STAR_6);
   Tile* purCloTile = new Tile(PURPLE, CLOVER);

   grid->setTile('Z', 20, redCirTile);
   grid->setTile('Z', 21, redSt4Tile);
   grid->setTile('Z', 22, redDiaTile);
   grid->setTile('Z', 23, redSquTile);
   grid->setTile('Z', 24, redSt6Tile);
   grid->setTile('Y', 23, purSquTile);
   grid->setTile('X', 23, yelSquTile);
   grid->setTile('X', 22, yelDiaTile);
   grid->setTile('X', 21, yelSt4Tile);
   grid->setTile('Y', 20, purCirTile);
   grid->setTile('Y', 22, purDiaTile);

   testName =
         "calc score for in two line formation (Col & Row) with no qwirkle";
   score = Validator::calcScore(grid, purSt4Tile, 'Y', 21, qwirkleFlag);
   expectedScore = 9;
   expectedQFlg = false;
   std::cout
         << ((score == expectedScore && qwirkleFlag == expectedQFlg) ?
               "Pass: " : "Fail: ") << testName << ", expected Score:"
         << expectedScore << ", Actual:" << score << std::endl;

   //-------------- calc score for in two line formation (Col & Row) with row
   //qwirkle

   Tile* oraSt4Tile = new Tile(ORANGE, STAR_4);
   Tile* greSt4Tile = new Tile(GREEN, STAR_4);
   Tile* bluSt4Tile = new Tile(BLUE, STAR_4);

   grid->setTile('U', 21, oraSt4Tile);
   grid->setTile('V', 21, greSt4Tile);
   grid->setTile('W', 21, bluSt4Tile);
   testName = "Score_Test, calc score for in two line formation (Col & Row) "
         "with row qwirkle";
   score = Validator::calcScore(grid, purSt4Tile, 'Y', 21, qwirkleFlag);
   expectedScore = 18;
   expectedQFlg = true;
   std::cout
         << ((score == expectedScore && qwirkleFlag == expectedQFlg) ?
               "Pass: " : "Fail: ") << testName << ", expected Score:"
         << expectedScore << ", Actual:" << score << std::endl;

   //-------------- calc score for in two line formation (Col & Row)
   // with col qwirkle
   delete grid;
   grid = initialiseGrid();
   grid->setTile('Z', 20, redCirTile);
   grid->setTile('Z', 21, redSt4Tile);
   grid->setTile('Z', 22, redDiaTile);
   grid->setTile('Z', 23, redSquTile);
   grid->setTile('Z', 24, redSt6Tile);
   grid->setTile('Y', 23, purSquTile);
   grid->setTile('X', 23, yelSquTile);
   grid->setTile('X', 22, yelDiaTile);
   grid->setTile('X', 21, yelSt4Tile);
   grid->setTile('Y', 20, purCirTile);
   grid->setTile('Y', 22, purDiaTile);
   grid->setTile('Y', 24, purSt6Tile);
   grid->setTile('Y', 25, purCloTile);

   testName = "Score_Test, calc score for in two line formation ";
   testName += "(Col & Row) with col qwirkle";
   score = Validator::calcScore(grid, purSt4Tile, 'Y', 21, qwirkleFlag);
   expectedScore = 17;
   expectedQFlg = true;
   std::cout
         << ((score == expectedScore && qwirkleFlag == expectedQFlg) ?
               "Pass: " : "Fail: ") << testName << ", expected Score:"
         << expectedScore << ", Actual:" << score << std::endl;

   //-------------- calc score for in two line formation (Col & Row)
   //with both Row & Col qwirkle

   grid->setTile('U', 21, oraSt4Tile);
   grid->setTile('V', 21, greSt4Tile);
   grid->setTile('W', 21, bluSt4Tile);
   testName = "Score_Test, calc score for in two line formation";
   testName += " (Col & Row) with both Row & Col qwirkle";
   score = Validator::calcScore(grid, purSt4Tile, 'Y', 21, qwirkleFlag);
   expectedScore = 26;
   expectedQFlg = true;
   std::cout
         << ((score == expectedScore && qwirkleFlag == expectedQFlg) ?
               "Pass: " : "Fail: ") << testName << ", expected Score:"
         << expectedScore << ", Actual:" << score << std::endl;

//   std::cout << grid->toString(true) << std::endl<< std::endl<< std::endl;

//-------------- clean up
   delete redCirTile;
   delete redSt4Tile;
   delete redDiaTile;
   delete redSquTile;
   delete redSt6Tile;
   delete redCloTile;
   delete purSquTile;
   delete yelSquTile;
   delete yelDiaTile;
   delete yelSt4Tile;
   delete purSt4Tile;
   delete purDiaTile;
   delete purCirTile;
   delete purSt6Tile;
   delete purCloTile;
   delete oraSt4Tile;
   delete greSt4Tile;
   delete bluSt4Tile;
   delete grid;
}

void Validator_Test::validatorTest() {

   Grid* grid = initialiseGrid();

   Tile* redCirTile = new Tile(RED, CIRCLE);
   Tile* redDiaTile = new Tile(RED, DIAMOND);
   Tile* oraCirTile = new Tile(ORANGE, CIRCLE);
   std::string errMessage;

   // test valid placement in empty grid
   std::string testName = "Validator_Test, Valid tile in Empty Grid";
   bool isValid = Validator::validate(grid, redDiaTile, 'B', 10, errMessage);
   bool expected = true;
   if (isValid == expected) {
      std::cout << "Pass: " + testName << std::endl;
   } else {
      std::cout << "Fail: " + testName << ",      \t errMessage:" << errMessage
            << std::endl;
   }

   grid->setTile('B', 10, redCirTile);

   //--------------  test valid placement with matching colour, Horizontal
   testName = "Validator_Test, Valid tile with Correct color, Horizontal";
   isValid = Validator::validate(grid, redDiaTile, 'B', 11, errMessage);

   expected = true;
   if (isValid == expected) {
      std::cout << "Pass: " + testName << std::endl;
   } else {
      std::cout << "Fail: " + testName << ",      \t errMessage:" << errMessage
            << std::endl;
   }

   //--------------  test valid placement with matching shape, Horizontal
   testName = "Validator_Test, Valid tile with Correct shape, Horizontal";
   isValid = Validator::validate(grid, oraCirTile, 'B', 11, errMessage);

   expected = true;
   if (isValid == expected) {
      std::cout << "Pass: " + testName << std::endl;
   } else {
      std::cout << "Fail: " + testName << ",      \t errMessage:" << errMessage
            << std::endl;
   }

   //--------------  test valid placement with matching colour, Vertical
   testName = "Validator_Test, Valid tile with Correct color, Vertical";
   isValid = Validator::validate(grid, redDiaTile, 'C', 10, errMessage);

   expected = true;
   if (isValid == expected) {
      std::cout << "Pass: " + testName << std::endl;
   } else {
      std::cout << "Fail: " + testName << ",      \t errMessage:" << errMessage
            << std::endl;
   }

   //--------------  test valid placement with matching shape, Vertical
   testName = "Validator_Test, Valid tile with Correct shape, Vertical";
   isValid = Validator::validate(grid, oraCirTile, 'A', 10, errMessage);

   expected = true;
   if (isValid == expected) {
      std::cout << "Pass: " + testName << std::endl;
   } else {
      std::cout << "Fail: " + testName << ",      \t errMessage:" << errMessage
            << std::endl;
   }

   //--------------  test tile is null
   testName = "Validator_Test, Invalid placement of null Tile";
   isValid = Validator::validate(grid, nullptr, 'B', 10, errMessage);

   expected = false;
   if (isValid == expected) {
      std::cout << "Pass: " + testName << std::endl;
   } else {
      std::cout << "Fail: " + testName << ",      \t errMessage:" << errMessage
            << std::endl;
   }

   //--------------  test tile is out of bound horizontal
   testName = "Validator_Test, Invalid placement of Tile is out of bound";
   testName += " horizontally";

   isValid = Validator::validate(grid, oraCirTile, 'B', 26, errMessage);

   expected = false;
   if (isValid == expected) {
      std::cout << "Pass: " + testName << std::endl;
   } else {
      std::cout << "Fail: " + testName << ",      \t errMessage:" << errMessage
            << std::endl;
   }

   //--------------  test tile is out of bound vertical
   testName = "Validator_Test, Invalid placement of Tile is out of ";
   testName += "bound vertically";
   isValid = Validator::validate(grid, oraCirTile, 'Z' + 1, 25, errMessage);

   expected = false;
   if (isValid == expected) {
      std::cout << "Pass: " + testName << std::endl;
   } else {
      std::cout << "Fail: " + testName << ",      \t errMessage:" << errMessage
            << std::endl;
   }

   //--------------  test tile already in that place
   testName = "Validator_Test, Invalid placement of Tile on pre-Existing tile";
   isValid = Validator::validate(grid, oraCirTile, 'B', 10, errMessage);

   expected = false;
   if (isValid == expected) {
      std::cout << "Pass: " + testName << std::endl;
   } else {
      std::cout << "Fail: " + testName << ",      \t errMessage:" << errMessage
            << std::endl;
   }

   //--------------  test tile not connected to anything in a non-empty grid
   testName = "Validator_Test, Invalid placement of Tile not connecting to ";
   testName += "other tiles in non-empty grid";
   isValid = Validator::validate(grid, oraCirTile, 'B', 13, errMessage);

   expected = false;
   if (isValid == expected) {
      std::cout << "Pass: " + testName << std::endl;
   } else {
      std::cout << "Fail: " + testName << ",      \t errMessage:" << errMessage
            << std::endl;
   }

   delete grid;

   //--------------  test tile in line with duplicate shape
   grid = initialiseGrid();
   grid->setTile('B', 10, redCirTile);
   grid->setTile('A', 10, redDiaTile);

   testName =
         "Validator_Test, Invalid placement of a Tile with duplicate shape";
   isValid = Validator::validate(grid, oraCirTile, 'C', 10, errMessage);

   expected = false;
   if (isValid == expected) {
      std::cout << "Pass: " + testName << std::endl;
   } else {
      std::cout << "Fail: " + testName << ",      \t errMessage:" << errMessage
            << std::endl;
   }

   delete grid;

   //--------------  test tile in line with duplicate colour
   grid = initialiseGrid();
   grid->setTile('A', 10, oraCirTile);
   grid->setTile('B', 10, redCirTile);

   testName =
         "Validator_Test, Invalid placement of a Tile with duplicate color";
   isValid = Validator::validate(grid, redDiaTile, 'C', 10, errMessage);

   expected = false;
   if (isValid == expected) {
      std::cout << "Pass: " + testName << std::endl;
   } else {
      std::cout << "Fail: " + testName << ",      \t errMessage:" << errMessage
            << std::endl;
   }

   delete grid;

   //--------------  test tile forming a line of 6 same shape
   Tile* yelCirTile = new Tile(YELLOW, CIRCLE);
   Tile* greCirTile = new Tile(GREEN, CIRCLE);
   Tile* bluCirTile = new Tile(BLUE, CIRCLE);
   Tile* purCirTile = new Tile(PURPLE, CIRCLE);

   grid = initialiseGrid();
   grid->setTile('A', 0, oraCirTile);
   grid->setTile('C', 0, redCirTile);
   grid->setTile('D', 0, yelCirTile);
   grid->setTile('E', 0, greCirTile);
   grid->setTile('F', 0, bluCirTile);
   testName = "Validator_Test, Valid placement of a 6th Tile in ";
   testName += "same shape line";
   isValid = Validator::validate(grid, purCirTile, 'B', 0, errMessage);

   expected = true;
   if (isValid == expected) {
      std::cout << "Pass: " + testName << std::endl;
   } else {
      std::cout << "Fail: " + testName << ",      \t errMessage:" << errMessage
            << std::endl;
   }

   grid->setTile('B', 0, purCirTile);
   //--------------  test tile forming a line larger than than 6, same shape
   testName =
         "Validator_Test, Invalid placement of 7th Tile in same shape line";
   isValid = Validator::validate(grid, yelCirTile, 'G', 0, errMessage);
   expected = false;
   if (isValid == expected) {
      std::cout << "Pass: " + testName << std::endl;
   } else {
      std::cout << "Fail: " + testName << ",      \t errMessage:" << errMessage
            << std::endl;
   }

   delete grid;

   //--------------  test tile forming a line of 6 same colour
   Tile* redSt4Tile = new Tile(RED, STAR_4);
   Tile* redSquTile = new Tile(RED, SQUARE);
   Tile* redSt6Tile = new Tile(RED, STAR_6);
   Tile* redCloTile = new Tile(RED, CLOVER);

   grid = initialiseGrid();
   grid->setTile('Z', 20, redCirTile);
   grid->setTile('Z', 21, redSt4Tile);
   grid->setTile('Z', 22, redDiaTile);
   grid->setTile('Z', 23, redSquTile);
   grid->setTile('Z', 24, redSt6Tile);

   testName =
         "Validator_Test, Valid placement of a 6th Tile in same colour line";
   isValid = Validator::validate(grid, redCloTile, 'Z', 25, errMessage);

   expected = true;
   if (isValid == expected) {
      std::cout << "Pass: " + testName << std::endl;
   } else {
      std::cout << "Fail: " + testName << ",      \t errMessage:" << errMessage
            << std::endl;
   }

   //--------------  test tile forming a line larger than than 6, same colour
   grid->setTile('Z', 25, redCloTile);
   testName =
         "Validator_Test, Invalid placement of 7th Tile in same colour line";
   isValid = Validator::validate(grid, redSt4Tile, 'Z', 19, errMessage);
   expected = false;
   if (isValid == expected) {
      std::cout << "Pass: " + testName << std::endl;
   } else {
      std::cout << "Fail: " + testName << ",      \t errMessage:" << errMessage
            << std::endl;
   }

   //--------------  test tile forming part of 2 lines
   Tile* purSquTile = new Tile(PURPLE, SQUARE);
   Tile* yelSquTile = new Tile(YELLOW, SQUARE);
   Tile* yelDiaTile = new Tile(YELLOW, DIAMOND);
   Tile* yelSt4Tile = new Tile(YELLOW, STAR_4);
   Tile* purSt4Tile = new Tile(PURPLE, STAR_4);
   Tile* purDiaTile = new Tile(PURPLE, DIAMOND);

   grid->setTile('Y', 23, purSquTile);
   grid->setTile('X', 23, yelSquTile);
   grid->setTile('X', 22, yelDiaTile);
   grid->setTile('X', 21, yelSt4Tile);
   grid->setTile('Y', 20, purCirTile);
   grid->setTile('Y', 22, purDiaTile);

   testName = "Validator_Test, Valid placement of a Tile as part of 2 lines";
   isValid = Validator::validate(grid, purSt4Tile, 'Y', 21, errMessage);
   expected = true;
   if (isValid == expected) {
      std::cout << "Pass: " + testName << std::endl;
   } else {
      std::cout << "Fail: " + testName << ",      \t errMessage:" << "'"
            << errMessage << "'" << std::endl;
   }

   //--------------  test invalid tile forming part of 2 lines satisfying
   // colour requirement only
   Tile* purSt6Tile = new Tile(PURPLE, STAR_6);

   testName = "Validator_Test, Invalid placement of a Tile as part ";
   testName += "of 2 lines, satisfying colour requirement only";
   isValid = Validator::validate(grid, purSt6Tile, 'Y', 21, errMessage);
   expected = false;
   if (isValid == expected) {
      std::cout << "Pass: " + testName << std::endl;
   } else {
      std::cout << "Fail: " + testName << ",      \t errMessage:" << "'"
            << errMessage << "'" << std::endl;
   }

   //--------------  test invalid tile forming part of 2 lines satisfying
   // colour requirement only
   Tile* greSt4Tile = new Tile(GREEN, STAR_4);

   testName = "Validator_Test, Invalid placement of a ";
   testName += "Tile as part of 2 lines, satisfying shape requirement only";
   isValid = Validator::validate(grid, greSt4Tile, 'Y', 21, errMessage);
   expected = false;
   if (isValid == expected) {
      std::cout << "Pass: " + testName << std::endl;
   } else {
      std::cout << "Fail: " + testName << ",      \t errMessage:" << "'"
            << errMessage << "'" << std::endl;
   }

   //--------------  cleanup
   delete grid;
   delete redCirTile;
   delete redDiaTile;
   delete oraCirTile;
   delete yelCirTile;
   delete greCirTile;
   delete bluCirTile;
   delete purCirTile;

   delete redSt4Tile;
   delete redSquTile;
   delete redSt6Tile;
   delete redCloTile;

   delete purSquTile;
   delete yelSquTile;
   delete yelDiaTile;
   delete yelSt4Tile;
   delete purSt4Tile;
   delete purDiaTile;

   delete purSt6Tile;
   delete greSt4Tile;
}

Grid* Validator_Test::initialiseGrid() {
   Grid* grid = new Grid();
   // test initially implemented with grid set to maximum size
   // this loop will bring grid back to maxium size, as tests need extra space
   // in order to test all of the operations without interfering with
   // each other
   for (int i = grid->getSize(); i != MAX_GRID_SIZE; ++i) {
      grid->reSize();
   }
   return grid;
}
