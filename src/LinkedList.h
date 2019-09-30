
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <string>

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   void add(Tile* tile);
   bool remove(Tile* tile);
   Tile* removeFirst();

   /*
    * return LinkedList details as a string. The boolean decides if the
    * result is intended for the GUI(Console) or not(Save file)
    */
   std::string toString(bool isGui);

private:
   Node* head;
};

#endif // ASSIGN2_LINKEDLIST_H
