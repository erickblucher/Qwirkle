
#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() {
    head = nullptr;
    // TODO
}

LinkedList::~LinkedList() {
    Node *ptr;
    Node *ptrTmp;
    ptr=head;
    while(ptr!=nullptr)
    {
       ptrTmp = ptr->next;
       delete ptr;
       ptr=ptrTmp;
    }

}

/*
 * add the new tile to the end of the linked list
 */
void LinkedList::add(Tile* tile) {
    if (tile == nullptr) {
    } else if (head == nullptr) {
        head = new Node(tile, nullptr);
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new Node(tile, nullptr);
    }
}

/*
 * loop through the linked list until finding the tile and remove it.
 */
bool LinkedList::remove(Tile* tile) {

    bool tileRemoved = false;
    Node* nodePtr;
    if (head != nullptr && head->tile == tile) {
        nodePtr = head;
        head = head->next;
        delete nodePtr;
        tileRemoved = true;
    } else if (head != nullptr) {
        Node* lastNodePtr = head;
        nodePtr = lastNodePtr->next;

        while (nodePtr != nullptr && !tileRemoved) {
            if (nodePtr->tile == tile) {
                lastNodePtr->next = nodePtr->next;
                delete nodePtr;
                tileRemoved = true;
            } else {
                lastNodePtr = nodePtr;
                nodePtr = nodePtr->next;
            }
        }
    }
    return tileRemoved;
}


/*
 * Removes the first node and returns a pointer to the tile that was
 * associated with the node
 */
Tile* LinkedList::removeFirst() {
    Tile* firstTile;
    if (head == nullptr) {
        firstTile = nullptr;
    } else {
        Node* temp = head->next;
        firstTile = head->tile;
        delete head;
        head = temp;
    }
    return firstTile;
}

/*
 * loop through the linked list and prints out all tiles
 */
std::string LinkedList::toString(bool isGui) {
    std::string hand = "";
    Node* nodePtr = head;
    while (nodePtr != nullptr) {
        if (nodePtr != head) {
            hand.append(",");
        }
        // hand.append(&(nodePtr->tile->colour));
        // hand.append(std::to_string(nodePtr->tile->shape));
        if (isGui) {
           hand.append("(");
           hand.append(nodePtr->tile->toStringCombined());
           hand.append(")");
        }
        else
           hand.append(nodePtr->tile->toString());
        nodePtr = nodePtr->next;
    }
    return hand;
}
