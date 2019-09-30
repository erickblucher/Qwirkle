/*
 * LinkedListTest.cpp
 *
 *  Created on: 25 Apr 2019
 *      Author: Abrar
 */

#include "../src/LinkedList.h"
#include "LinkedList_test.h"
#include <iostream>
#include "../src/TileCodes.h"
#include <exception>
#include "../src/Constants.h"

void LinkedList_Test::linkedListTest() {
   LinkedList* ll = new LinkedList();
   Tile* redCirTile = new Tile(RED, CIRCLE);
   Tile* redSt4Tile = new Tile(RED, STAR_4);
   Tile* redDiaTile = new Tile(RED, DIAMOND);
   Tile* redSquTile = new Tile(RED, SQUARE);
   Tile* redSt6Tile = new Tile(RED, STAR_6);

   std::string expectedStr;
   std::string testName;

   //--------------  Add_Test, empty String
   testName = "LinkedList Add_Test, empty String";
   std::string actualStr = ll->toString(false);
   expectedStr = "";
   std::cout << ((actualStr == expectedStr) ? "Pass: " : "Fail: ") << testName
         << ", expected Str :" << expectedStr << ", Actual:" << actualStr
         << std::endl;

   //--------------  Add_Test, add 1 tile to LinkedList
   testName = "LinkedList Add_Test, add 1 tile to LinkedList";
   ll->add(redCirTile);
   actualStr = ll->toString(false);
   expectedStr = "R1";
   std::cout << ((actualStr == expectedStr) ? "Pass: " : "Fail: ") << testName
         << ", expected Str :" << expectedStr << ", Actual:" << actualStr
         << std::endl;

   //--------------  remove_Test, remove 1 tile from LinkedList
   testName = "LinkedList removeFirst_Test, remove 1 tile from LinkedList";
   ll->removeFirst();
   actualStr = ll->toString(false);
   expectedStr = "";
   std::cout << ((actualStr == expectedStr) ? "Pass: " : "Fail: ") << testName
         << ", expected Str :" << expectedStr << ", Actual:" << actualStr
         << std::endl;

   //--------------  delete_Test, delete empty LinkedList
   testName = "LinkedList delete_Test, delete empty LinkedList";
   delete ll;
   std::cout << "Pass: " << testName << std::endl;

   ll = new LinkedList();
   //--------------  Add_Test, add 10 tile to LinkedList
   testName = "LinkedList Add_Test, add 10 tile to LinkedList";
   for (int i = 0; i < 2; ++i) {
      ll->add(redCirTile);
      ll->add(redSt4Tile);
      ll->add(redDiaTile);
      ll->add(redSquTile);
      ll->add(redSt6Tile);
   }

   actualStr = ll->toString(false);
   expectedStr = "R1,R2,R3,R4,R5,R1,R2,R3,R4,R5";
   std::cout << ((actualStr == expectedStr) ? "Pass: " : "Fail: ") << testName
         << ", expected Str :" << expectedStr << ", Actual:" << actualStr
         << std::endl;

   //--------------  remove_Test, removeTile_Test, remove 9 out of 10
   // tiles from LinkedList using remove(Tile)
   testName = "LinkedList removeFirst_Test, remove 9 out of 10 tiles from ";
   testName += "LinkedList using removeFirst";
   for (int i = 0; i < 9; ++i) {
      ll->removeFirst();
   }
   actualStr = ll->toString(false);
   expectedStr = "R5";
   std::cout << ((actualStr == expectedStr) ? "Pass: " : "Fail: ") << testName
         << ", expected Str :" << expectedStr << ", Actual:" << actualStr
         << std::endl;

   //--------------  delete_Test, delete 1 member LinkedList
   testName = "LinkedList delete_Test, delete 1 member LinkedList";
   delete ll;
   std::cout << "Pass: " << testName << std::endl;

   ll = new LinkedList();
   //--------------  remove_Test, removeFirst_Test, remove 9 out of 10
   // tiles from LinkedList using removeFirst
   testName = "LinkedList removeFirst_Test, remove 6 out of 10 tiles from ";
   testName += "LinkedList using removeFirst";
   for (int i = 0; i < 2; ++i) {
      ll->add(redCirTile);
      ll->add(redSt4Tile);
      ll->add(redDiaTile);
      ll->add(redSquTile);
      ll->add(redSt6Tile);
   }
   for (int i = 0; i < 1; ++i) {
      ll->remove(redCirTile);
      ll->remove(redCirTile);
      ll->remove(redSt4Tile);
      ll->remove(redDiaTile);
      ll->remove(redSt6Tile);
   }
   actualStr = ll->toString(false);
   expectedStr = "R4,R2,R3,R4,R5";
   std::cout << ((actualStr == expectedStr) ? "Pass: " : "Fail: ") << testName
         << ", expected Str :" << expectedStr << ", Actual:" << actualStr
         << std::endl;

   //--------------  delete_Test, delete 4 member LinkedList
   testName = "LinkedList delete_Test, delete 4 member LinkedList";
   delete ll;
   std::cout << "Pass: " << testName << std::endl;

}
