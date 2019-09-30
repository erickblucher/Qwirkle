//
//  GridTest.cpp
//  liza
//
//  Created by Elizabeth Tawaf on 5/5/19.
//  Copyright © 2019 Elizabeth Tawaf. All rights reserved.
//

#include "../src/Grid.h"
#include "GridTest.h"

#include "../src/TileCodes.h"
#include <iostream>
#include "../src/GameMenu.h"


void GridTest::gridTest() {
   Grid* grid = new Grid();
   Tile* redCirTile = new Tile(RED, CIRCLE);

   Tile* expectedTile;
   Tile* actualTile;

   //--------------  Grid_Test, empty Grid
   std::string testName = "Grid_Test, empty Grid";
   int actualSize = grid->getSize();
   int expectedSize = INITIAL_SIZE;
   bool isEmpty = grid->isEmpty();
   bool expectedIsEmpty = true;
   std::cout
         << ((actualSize == expectedSize && isEmpty == expectedIsEmpty) ?
               "Pass: " : "Fail: ") << testName << ", expected Str :"
         << expectedSize << ", Actual:" << actualSize << std::endl;

   //--------------  Grid_Test, get non-existing tile
   testName = "Grid_Test, get non-existing tile";
   actualTile = grid->getTile(0, 0);
   expectedTile = nullptr;
   std::cout << ((actualTile == expectedTile) ? "Pass: " : "Fail: ")
         << testName
         << ", expected:" << expectedTile << ", Actual:" << actualTile
         << std::endl;

   //--------------  Grid_Test, addTile & get tile
   testName = "Grid_Test Add_Test, add 1 tile and !isEmpty";
   grid->setTile('A', 0, redCirTile);
   actualTile = grid->getTile(0, 0);
   expectedTile = redCirTile;
   isEmpty = grid->isEmpty();
   expectedIsEmpty = false;
   std::cout
         << ((actualTile == expectedTile && isEmpty == expectedIsEmpty) ?
               "Pass: " : "Fail: ") << testName << ", expected:"
         << expectedTile->toString() << ", Actual:" << actualTile->toString()
         << std::endl;

   //--------------  Grid_Test, isEmpty
   testName = "Grid_Test, isEmpty";
   grid->setTile('A', 0, nullptr);
   isEmpty = grid->isEmpty();
   expectedIsEmpty = true;
   std::cout << ((isEmpty == expectedIsEmpty) ? "Pass: " : "Fail: ") <<
         testName << ", expected:" << expectedIsEmpty << ", Actual:" <<
         isEmpty << std::endl;
}
