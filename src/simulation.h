#ifndef SIMULATION_H
#define SIMULATION_H

#include "node.h"
#include <string>
#include "nodelist.h"
#include <SFML/Graphics.hpp>

class Node;

class Simulation
{
  private:
    long double dist(Node * a, Node * b);
    long double angle(Node * a, Node * b);
    long double x_part(long double angle, long double magnitude);
    long double y_part(long double angle, long double magnitude);
  public:
    Simulation();
    int tick = 0;
    int winX = 500;
    int winY = 500;
    int ticksPerSecond = 60;
    NodeList list;

    bool verbose = false;
    bool paused = false;

    void Simulate();
    void Draw(sf::RenderWindow& window);
    void LoadSettings(std::string filename);
    void LoadSave(std::string filename);
};
#endif
