#ifndef ANT_H
#define ANT_H
#include <SFML/Graphics/CircleShape.hpp>

#include "entity.h"

class Ant : public Entity
{
    public:
        Ant();
        Ant(unsigned int x = 0, unsigned int y = 0, unsigned int z = 0);
        ~Ant() {};
        void Init();
        void Update();
        void Draw (sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default);
        void Status();

    private:
        void UpdateState();
        void SearchingForFood();
        void FollowingTrail();
        void Move(int dir);

        enum State
        {
            SEARCHING_FOR_FOOD,
            FOLLOWING_TRAIL
        };
        State currentState = SEARCHING_FOR_FOOD;

        sf::CircleShape sprite;
};


#endif