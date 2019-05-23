#include "node.h"
#include "nodelist.h"
#include <vector>

Node NodeList::operator[](int index)
{
    Node * cur = head;
    for(int i = 0; i < index; i++)
    {
        cur = cur->next;
    }   
    return *cur;
}
bool NodeList::AddNode(std::vector<std::string> part)
{
    Node* newNode = new Node();
    if(part.size() > 3)
    {
        newNode->entity->name = part[0];
        newNode->SetPos(stof(part[1]), stof(part[2]));

        if(part.size() > 5)
        {
            // entity color (3, 4, 5)
            newNode->SetColor(stoi(part[3]), stoi(part[4]), stoi(part[5]));
        }
        return AddNode(newNode);
    }
    else
        return false;
}

bool NodeList::AddNode(Node* newNode)
{
    if(head == nullptr)
    {
        head = newNode;
        head->next = nullptr;
        head->last = nullptr;
    }
    else
    {
        Node * cur = head;
        while (cur->next != nullptr)
            cur = cur->next;
        cur->next = newNode;

        newNode->last = cur;
        newNode->next = nullptr;
    }
    count++;
    return true;
}
