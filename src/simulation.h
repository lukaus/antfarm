#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>
#include "entity.h"
#include <SFML/Graphics.hpp>

class Simulation
{
  public:
    Simulation(unsigned int numAnts = 100);
    ~Simulation();
    int tick = 0;
    int winX = 500;
    int winY = 500;
    int ticksPerSecond = 60;

    bool verbose = false;
    bool paused = false;

    void Simulate();
    void Draw(sf::RenderWindow& window);
    void LoadSettings(std::string filename);
    void LoadSave(std::string filename);

  private:
    long double dist(Entity* a, Entity* b);
    long double angle(Entity* a, Entity* b);
    long double x_part(long double angle, long double magnitude);
    long double y_part(long double angle, long double magnitude);

    std::vector<Entity*> entityList;
};
#endif
