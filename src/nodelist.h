#ifndef NODELIST_H
#define NODELIST_H

#include <vector>
#include "node.h"

class NodeList
{
  public:
      Node* head = nullptr;
      int count = 0;

      Node operator[](int index);
      //bool AddNode(long double mass = 1.0); // not defined, have no idea what it's for, so commented out.
      bool AddNode(std::vector<std::string>);

      bool AddNode(Node* node);

  private:

};
#endif
