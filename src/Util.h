/*
 * Util.h
 *
 *      Author: Abrar
 */
#ifndef ASSIGN2_UTIL
#define ASSIGN2_UTIL

#include "Tile.h"
#include "TileCodes.h"
#include <string>
#include "Constants.h"

class Util {
public:
   /*
    * return the equivalent string for a shape value
    */
   static std::string shapeToString(Shape shape);

   /*
    * return the equivalent string for a colour value
    */
   static std::string colourToString(Colour colour);

   /*
    * return the string for a given colour to display it visually
    * in a supported terminal
    */
   static std::string colorToAnsi(Colour colour);

   /*
    * return the string for a given shape to display it as Emoji
    */
   static std::string shapeToEmoji(Shape shape);
private:

};

#endif // ASSIGN2_UTIL
