#ifndef NODELIST_H
#define NODELIST_H

#include "node.h"
#include <vector>

class Node;
class NodeList
{
  public:
      Node* head = nullptr;
      int count = 0;

      Node operator[](int idx);
      bool AddNode(long double mass = 1.0);
      bool AddNode(std::vector<std::string>);

      bool AddNode(Node*);

  private:

};
#endif
