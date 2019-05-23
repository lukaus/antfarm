#ifndef NODE_H
#define NODE_H
#include "entity.h"
#include <SFML/Graphics.hpp>

class Simulation;

class Node
{
  public:
      Node* next = nullptr;
      Node* last = nullptr;

      Entity* entity = nullptr;
      sf::CircleShape* pix = nullptr;

      Node();

      //void SetTrailColor(int r,int g, int b, int a=255);
      void SetColor(int r,int g, int b, int a=255);
      void SetColor(sf::Color col);
      void SetPos(double long x, double long y);
      void Update(Simulation* sim);
      void Status();

  private:
      void UpdatePos();
      //void UpdateTrail(Simulation* sim);
};

#endif