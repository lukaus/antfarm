#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Entity
{
    
    public:
        std::string name = "<UNKNOWN>";
        sf::Vector3f pos = {0,0,0};

        Entity() {};
        virtual ~Entity() {};
        virtual void Update() = 0;
        virtual void Draw (sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) = 0;
        virtual void Status() = 0;

    private:
};
#endif
