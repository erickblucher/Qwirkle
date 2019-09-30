/*
 * TestAll.cpp
 *
 *  Created on: 25 Apr 2019
 *      Author: Abrar
 */

#include "TestAll.h"

#include "GridTest.h"
#include "LinkedList_test.h"
#include "Validator_test.h"

void TestAll::testAll() {

   std::cout << " **** Running all tests for Qwirkle ****" << std::endl;

   LinkedList_Test::linkedListTest();

   Validator_Test::validatorTest();

   Validator_Test::scoreTest();

   GridTest::gridTest();

   std::cout << " **** Completed all tests for Qwirkle ****" << std::endl;
}
