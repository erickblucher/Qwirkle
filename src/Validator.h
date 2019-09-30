/*
 * Validator.h
 *
 *      Author: Abrar
 */
#ifndef ASSIGN2_VALIDATOR_H
#define ASSIGN2_VALIDATOR_H

#include "Tile.h"
#include <string>

#include "Constants.h"
#include "Grid.h"

typedef int LineValidation;

class Validator {
public:
   /*
    * The validation should be done before placement
    * Return true for valid and false for invalid tile placement.
    * The errMessage string returns the identified invalid case
    */
   static bool validate(Grid* grid, Tile* newTile, char row, int col,
         std::string& errorMsg);

   /*
    * Note: This method assumes tile placement is validated!
    * It calculates the score and return it as an integer.
    * qwirkleFlag reference will return true if a "qwirkle" happens
    * and false otherwise
    */
   static int calcScore(Grid* grid, Tile* newTile, char row, int col,
         bool& qwirkleFlag);

private:
   /*
    * low level internal validation method that validate line related
    * aspects.
    * Return has 3 states:
    * *- Invalid
    * *- Potentially Invalid
    * *- Valid
    *
    * Potentially valid cases will be dependent on other scenarios and
    * responsibility of the caller to ascertain validity.
    */
   static LineValidation validateLineVertical(Grid* grid, Tile* newTile,
         char row, int col, std::string& errorMsg, bool isVerticalValidation);
   static int calcLineScore(Grid* grid, char row, int col,
         bool isVerticalValidation);
};

#endif // ASSIGN2_VALIDATOR_H
