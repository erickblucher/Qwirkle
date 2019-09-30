#include "Tile.h"
#include <iostream>
#include "Util.h"
#include "OperationModes.h"

Tile::Tile(Colour colour, Shape shape) :
      colour(colour), shape(shape) {
}

Tile::Tile() {
   colour = ' ';
   shape = ' ';
}

std::string Tile::toStringCombined() {
   return toStringGui() + toString();
}

std::string Tile::toString() {
   std::string tileString = colour + std::to_string(shape);
   return tileString;
}

std::string Tile::toStringGui() {
   std::string tileString;
   std::string shapeStr;

   if (EMOJI_CODE_ENABLED) {
      shapeStr = Util::shapeToEmoji(shape);
   } else {
      shapeStr = std::to_string(shape);
   }

   if (COLOR_CODE_ENABLED) {
      tileString = Util::colorToAnsi(colour) + shapeStr + " " + RESET_COLOUR;
   } else
      tileString = colour + shapeStr; //std::string(1,colour) +

   return tileString;
}

bool Tile::operator==(const Tile& otherTile) {
   return (otherTile.colour == this->colour && otherTile.shape == this->shape);
}

bool Tile::operator!=(const Tile& otherTile) {
   return (otherTile.colour != this->colour || otherTile.shape != this->shape);
}
