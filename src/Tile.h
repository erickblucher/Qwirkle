#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
   Tile(Colour colour, Shape shape);
   Tile();
   Colour colour;
   Shape shape;

   /*
    * return a string representation of the tile.
    */
   std::string toString();

   /*
    * return a string representation of the tile but supported by the
    * emojie and colouring
    * The colouring and emojie usage can be controlled by contansts
    */
   std::string toStringGui();
   /*
    * print both the graphic as well as text representation.
    */
   std::string toStringCombined();

   /*
    * overloaded Equal operator for Tile
    */
   bool operator==(const Tile& otherTile);

   /*
    * overloaded not Equal operator for Tile
    */
   bool operator!=(const Tile& otherTile);

};

#endif // ASSIGN2_TILE_H
