/*
 * Util.cpp
 *
 *      Author: Abrar
 */
#include "Util.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>

std::string Util::shapeToString(Shape shape) {
   std::string shapeStr;
   if (shape == CIRCLE) {
      shapeStr = "CIRCLE";
   } else if (shape == STAR_4) {
      shapeStr = "STAR_4";
   } else if (shape == DIAMOND) {
      shapeStr = "DIAMOND";
   } else if (shape == SQUARE) {
      shapeStr = "SQUARE";
   } else if (shape == STAR_6) {
      shapeStr = "STAR_6";
   } else if (shape == CLOVER) {
      shapeStr = "CLOVER";
   }
   return shapeStr;
}

std::string Util::colourToString(Colour colour) {
   std::string colourStr;
   if (colour == RED) {
      colourStr = "RED";
   } else if (colour == ORANGE) {
      colourStr = "ORANGE";
   } else if (colour == YELLOW) {
      colourStr = "YELLOW";
   } else if (colour == GREEN) {
      colourStr = "GREEN";
   } else if (colour == BLUE) {
      colourStr = "BLUE";
   } else if (colour == PURPLE) {
      colourStr = "PURPLE";
   }
   return colourStr;
}

std::string Util::colorToAnsi(Colour colour) {
   std::string colorAnsiCode;
   if (colour == RED) {
      colorAnsiCode = RED_COLOUR;
   } else if (colour == ORANGE) {
      colorAnsiCode = ORANGE_COLOUR;
   } else if (colour == YELLOW) {
      colorAnsiCode = YELLOW_COLOUR;
   } else if (colour == GREEN) {
      colorAnsiCode = GREEN_COLOUR;
   } else if (colour == BLUE) {
      colorAnsiCode = BLUE_COLOUR;
   } else if (colour == PURPLE) {
      colorAnsiCode = PURPLE_COLOUR;
   }

   return colorAnsiCode;
}

std::string Util::shapeToEmoji(Shape shape) {
   std::string shapeEmojiCode;
   if (shape == CIRCLE) {
      shapeEmojiCode = CIRCLE_SHAPE;
   } else if (shape == STAR_4) {
      shapeEmojiCode = STAR_4_SHAPE;
   } else if (shape == DIAMOND) {
      shapeEmojiCode = DIAMOND_SHAPE;
   } else if (shape == SQUARE) {
      shapeEmojiCode = SQUARE_SHAPE;
   } else if (shape == STAR_6) {
      shapeEmojiCode = STAR_6_SHAPE;
   } else if (shape == CLOVER) {
      shapeEmojiCode = CLOVER_SHAPE;
   }
   return shapeEmojiCode;
}
