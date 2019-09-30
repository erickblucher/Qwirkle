/*
 * LinkedListTest.h
 *
 *  Created on: 25 Apr 2019
 *      Author: Abrar
 */

#ifndef VALIDATOR_TEST_H_
#define VALIDATOR_TEST_H_

#include "../src/Grid.h"
#include <string>

class Validator_Test {
public:
   static void validatorTest();

   static void scoreTest();
private:
   static Grid* initialiseGrid();
};

#endif /* LINKEDLIST_TEST_H_ */
