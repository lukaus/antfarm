#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include "node.h"
#include "nodelist.h"
#include "simulation.h"
#include <SFML/Graphics.hpp>

using namespace std;

        Simulation::Simulation()
{

}

// Distance between two points
long double Simulation::dist(Node* a, Node* b)
{
    return sqrt( pow(b->entity->x - a->entity->x, 2) + pow(b->entity->y - a->entity->y, 2));
}

// Angle relative x-axis between two points(in rads)
long double Simulation::angle(Node* a, Node* b)
{
    return atan2(b->entity->y - a->entity->y, b->entity->x - a->entity->x );
}

long double Simulation::x_part(long double angle, long double magnitude) // Get x part of magnitude with angle
{
    return magnitude * cos(angle);
}

long double Simulation::y_part(long double angle, long double magnitude) // Get y part of magnitude with angle
{
    return magnitude * sin(angle);
}

void Simulation::Simulate()
{
    tick++;
    cout << "\n===============================\nt= " << tick << endl; 
    Node* cur = list.head;
    for(int i = 0; i < list.count; i++)
    {
        cur = cur->next;
    }
    cout << endl;
}

bool startsWith(string a, string b) // does a start with b
{
    if(a.length() < b.length())
        return false;

    for(long unsigned int i = 0; i < b.length(); i++)
        if(a[i] != b[i])
            return false;

    return true;
}

void Simulation::LoadSettings(string filename)
{
    cerr << "Loading settings from " << filename << "...\t";
    ifstream in;
    in.open(filename);
    
    string line;
    getline(in, line);
    while(in)
    {
        if(line == "PAUSED")
            paused = true;

        if(line == "VERBOSE")
            verbose = true;

        if(startsWith(line, "X=") && line.length() > 2)
            winX = stoi(line.substr(2, line.length() - 2));

        if(startsWith(line, "Y=") && line.length() > 2)
            winY = stoi(line.substr(2, line.length() - 2));

        if(startsWith(line, "TPS=") && line.length() > 4)
            ticksPerSecond = stoi(line.substr(4, line.length() - 4));

        getline(in, line);
    }

    in.close();

    cerr << "done." << endl;
}

void Simulation::Draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);
    window.display();
}


void Simulation::LoadSave(string filename)
{
    cerr << "Loading save from " << filename << "...\t";

    ifstream in;
    in.open(filename);
    
    string line;
    getline(in, line);
    while(in)
    {
        if(line.length() > 0 && line[0] != '#')
        {
            istringstream iss(line);
            vector<string> results(istream_iterator<string>{iss},
                                     istream_iterator<string>());
            if(list.AddNode(results))
                cerr << ".";
            else
                cerr << "\nFailed to load entity! : \n" << line << endl;
        }        
        getline(in, line);
    }
    in.close();
    cerr << "done." << endl;
}
