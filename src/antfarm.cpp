#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "node.h"
#include "simulation.h"
#include <sys/stat.h>
#include <string>

#define VERSION_STRING "v0.1"

using namespace std;

bool fileExists(const string& fn)
{
    struct stat b;
    return(stat(fn.c_str(), &b) == 0);
}

int main(int argc, char* argv[])
{
    Simulation sim;
    bool dragging = false;
    if(argc > 3)
    {
        cerr << "Syntax is 'antfarm [save file] [settings file]'"
            << "\n\t [save file] and [settings file] are optional and default to settings.cfg and empty.dat respectively.\n";
        return 0;
    }
    string settingsFilename = "settings.cfg";
    string saveFile = "dat/empty.dat";
    if(argc > 1)
    {
        // Make sure files exist
        saveFile = (argv[1]);
        if(fileExists(saveFile) == false)
            saveFile = "dat/"+saveFile;
        if(fileExists(saveFile) == false)
        {
            cerr << "Cannot access save file \"" << (argv[1]) << "\" either in ./ or ./dat!";
            return -1;
        }
    }
    if(argc > 2)
    {
        settingsFilename = (argv[2]);
        if(fileExists(settingsFilename) == false)
            settingsFilename = "cfg/"+settingsFilename;
        if(fileExists(settingsFilename) == false)
        {
            cerr << "Cannot access configuration file \"" << (argv[2]) << "\" either in ./ or ./cfg!";
            return -1;
        }
    }
    sim.LoadSettings(settingsFilename);
    sim.LoadSave(saveFile);

    sf::RenderWindow window(sf::VideoMode(sim.winX, sim.winY), std::string("AntFarm") + std::string(VERSION_STRING));
    window.setFramerateLimit(sim.ticksPerSecond);

    cerr << "Window is (" << sim.winX << ", " << sim.winY << ")\n";
    cerr << "Beginning simulation at " << sim.ticksPerSecond << " ticks/s. \n"; 

    sf::Vector2f mPos = window.getView().getCenter();
    while (window.isOpen())
    {
        if(!sim.paused)
            sim.Simulate();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type ==sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            sf::View view = window.getView();
            if(event.type == sf::Event::MouseWheelMoved)
            {
                if(event.mouseWheel.delta < 0)
                {
                    view.zoom(1.25f);
                }
                else if(event.mouseWheel.delta > 0)
                {
                    view.zoom(0.8f);
                }
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Space)
                    sim.paused = !sim.paused;
                if(event.key.code == sf::Keyboard::Period && sim.paused)
                    sim.Simulate();
            }
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                mPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                dragging = true;
            }
            else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                dragging = false;
            }
            else if(event.type == sf::Event::MouseMoved && dragging)
            {
                sf::Vector2f curPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                float xMove = mPos.x - curPos.x;
                float yMove = mPos.y - curPos.y;
                view.move(xMove, yMove);
            }
            mPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            window.setView(view);
        }

        window.clear();
        sim.Draw(window);
        window.display();
    }

    return 0;
}
