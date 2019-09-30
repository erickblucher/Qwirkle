
#include "Node.h"

Node::Node(Tile* tile, Node* next) :
tile(tile), next(next) {}

Node::Node(Node& other) :
tile(other.tile), next(other.next) {}
