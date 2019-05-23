#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "node.h"

using std::cout, std::cerr, std::endl;

// Wraps entity and SFML circle


Node::Node()
{
    next =nullptr;
    last = nullptr;
    entity = new Entity();
    pix = new sf::CircleShape();
    pix->setRadius(1);
}

void Node::SetColor(sf::Color col)
{
    pix->setFillColor(col);
}
void Node::SetColor(int r, int g, int b, int a)
{
    pix->setFillColor(sf::Color(r,g,b,a));
}

void Node::SetPos(double long x, double long y)
{
    if(entity != nullptr)
    {
        entity->x = x;
        entity->y = y;
    }
    pix->setPosition(sf::Vector2f((float)x,(float)y));
}

void Node::Update(Simulation* sim)
{
    this->UpdatePos();
}

void Node::UpdatePos()
{

}

void Node::Status()
{
    cout << this->entity->name << " " << this->entity->x << ", " << this->entity->y << ")";
}

