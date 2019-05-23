#include "ant.h"
#include "random-number.h"

Ant::Ant()
{
    Init();
}

Ant::Ant(unsigned int x, unsigned int y, unsigned int z)
{
    pos = {x,y,z};
    Init();
}

void Ant::Init()
{
    name = "ant";
    sprite.setRadius(1);
    sprite.setOutlineColor(sf::Color::Red);
    sprite.setFillColor(sf::Color::Red);
    sprite.setOutlineThickness(1);
    sprite.setPosition(pos.x, pos.y);
}

void Ant::Update()
{
    UpdateState();
    sprite.setPosition(pos.x, pos.y);
}

void Ant::Status()
{

}

void Ant::UpdateState()
{
    switch(currentState)
    {
        case SEARCHING_FOR_FOOD:
            SearchingForFood();
            break;
        
        case FOLLOWING_TRAIL:
            FollowingTrail();
            break;
        
        default:
            SearchingForFood();
    }
}

void Ant::SearchingForFood()
{
    Move(Random::GetInt(0,3));
}

void Ant::FollowingTrail()
{
}

void Ant::Move(int dir)
{
    switch(dir)
    {
        case 0:
            pos.y++;
            break;
        case 1:
            pos.x++;
            break;
        case 2:
            pos.y--;
            break;
        case 3:
            pos.x--;
            break;
        default:
            break;
    }
}

void Ant::Draw(sf::RenderTarget &target, sf::RenderStates states)
{
    target.draw(sprite, states);
}